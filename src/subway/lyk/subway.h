#include<stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"

#define M 1024
#define N 256

struct subway {
	char name[M];
	int num;
	int flag;
	struct subway *next;
};

struct tree_node {
	struct subway *sub;
	struct tree_node *brother;
	struct tree_node *child;
	struct tree_node *parent;
};	


void read_subway_data(struct subway **data);
struct subway *handle_data(char *buf, struct subway *data);
char  *seek_route(char *start, char *end, struct subway **data);
char *print_handle(struct tree_node *node);


void read_subway_data(struct subway **data)
{
	MYSQL	my_connection;
	MYSQL_RES *res_ptr;
	MYSQL_ROW sqlrow;
	int res, i;
	char buf[N];
	unsigned int field_count;

	for (i = 0; i < N; i++) {
		data[i] = NULL;
	}
	
	mysql_init(&my_connection);
	if(mysql_real_connect(&my_connection,"localhost","root","subway","subway",0,NULL,0))
	{
		res=mysql_query(&my_connection,"SELECT * FROM subway");
		if(res)
		{
			printf("SELECT error: %s\n",mysql_error(&my_connection));
		}else{
			res_ptr=mysql_store_result(&my_connection);
			if(res_ptr){
				i = 0;
				while(sqlrow=mysql_fetch_row(res_ptr))
				{
					strcpy(buf, sqlrow[0]);
					data[i] = handle_data(buf, data[i]);
					i++;
				}
				if(mysql_errno(&my_connection))
				{
					fprintf(stderr,"Retrive error :%s\n",mysql_error(&my_connection));
				}
				mysql_free_result(res_ptr);
			}
		}
		mysql_close(&my_connection);
	}else{
		fprintf(stderr,"Connection failed\n");
		if(mysql_errno(&my_connection))
		{
		fprintf(stderr,"Connection error %d : %s\n",mysql_errno(&my_connection),mysql_error(&my_connection));
		}
	}
}


struct subway *handle_data(char *buf, struct subway *data)
{
	char name[M], num[3];
	int i, j;
	struct subway *node, *p;

	node = (struct subway *)malloc(sizeof(struct subway));
	data = node;	
	i = 0;
	while (1) {
		j = 0;
		while (buf[i] != ' ') {
			name[j] = buf[i];
			i++;
			j++;
		}
		name[j] = '\0';
		strcpy(node->name, name);

		i++;
		j = 0;
		while ((buf[i] != ' ') && (buf[i] != '\0')) {
			num[j] = buf[i];
			i++;
			j++;
		}
		num[j] = '\0';
		node->num = atoi(num);
		node->flag = 0;
		if (buf[i] == '\0') {
			node->next = NULL;

			return data;
		}
		i++;
		
		p = (struct subway *)malloc(sizeof (struct subway));
		node->next = p;
		node = p;
	}
}


char  *seek_route(char *start, char *end, struct subway **data)
{
	struct tree_node *first1, *node1_tree,*first2, *node2_tree, *new;
	struct subway *node_subway;
	int i, j, k, count;
	char *name[50], *result, num_buf[5];
	int num[50];

	result = (char *)malloc(M * sizeof (char));
	
	node1_tree = (struct tree_node *)malloc(sizeof (struct tree_node));
	
	i = 0;
	while (strcmp(end, data[i]->name)) {
		i++;
		if (i == 242) {
			strcpy(result, "error输入有误，没有该站点！");
			return result;
		}	
	}
	i = 0;
	while (strcmp(start, data[i]->name)) {
		i++;
		if (i == 242) {
			strcpy(result, "error输入有误，没有该站点！");
			return result;
		}
	}
	node1_tree->sub = data[i];
	node1_tree->sub->flag = 1;
	node1_tree->brother = NULL;
	node1_tree->parent = NULL;
	node1_tree->child = NULL;
	first1 = node1_tree;

	while (1) {
		node1_tree = first1;
		first2 = NULL;
		node2_tree = NULL;
		while (node1_tree) {
			node_subway = node1_tree->sub->next;
			while (node_subway) {
				i = 0;
				while (strcmp(node_subway->name, data[i]->name)) {
					i++;
				}
				if (data[i]->flag) {
					node_subway = node_subway->next;
					continue ;
				}
				data[i]->flag = 1;
				data[i]->num = node_subway->num;
				new = (struct tree_node *)malloc(sizeof (struct tree_node));
				new->sub = data[i];
				if (!first2) {
					first2 = new;
					first1->child = first2;
					first2->parent = node1_tree;
					first2->brother = NULL;
					first2->child = NULL;
					node2_tree = first2;
				} else {
					node2_tree->brother = new;
					node2_tree = node2_tree->brother;
					node2_tree->parent = node1_tree;
					node2_tree->brother = NULL;
					node2_tree->child = NULL;
				}
				if (!strcmp(node2_tree->sub->name, end)) {
					for (k = 0; k < 50; k++) {
						num[k] = 0;
					}

					k = 0;
					while (node2_tree) {
						name[k] = node2_tree->sub->name;
						num[k] = node2_tree->sub->num;
						k++;
						node2_tree = node2_tree->parent;
					}
					count = k;
	
					strcpy(result, name[0]);
					strcat(result, "#");
					for(k = 1; k < count - 1; k++) {
						strcat(result, name[k]);
						strcat(result, "#");
					}
					sprintf(num_buf, "%d", count);
					strcat(result, num_buf);
					strcat(result, "站#$");
					for (k = 0; k < count - 1; k++) {
						if (num[k] == 13) {
							strcat(result,name[k]);
							strcat(result, "#-(乘");
							sprintf(num_buf, "%d", 10);
							strcat(result, num_buf);
							strcat(result, "号线)->#");	
						} else if (num[k] == 12) {
							strcat(result,name[k]);
							strcat(result, "#-(乘");
							sprintf(num_buf, "%d", 11);
							strcat(result, num_buf);
							strcat(result, "号线)->#");	
						} else {
							strcat(result, name[k]);
							strcat(result, "#-(乘");
							sprintf(num_buf, "%d", num[k]);
							strcat(result, num_buf);
							strcat(result, "号线)->#");	
						}
						while (num[k] == num[k + 1]) {
							k++;
						}
					}
					strcat(result,name[count - 1]);
					strcat(result,"#$");
					return result;
				}
				node_subway = node_subway->next;
			}
			node1_tree = node1_tree->brother;
		}
		first1 = first2;
	}
}
