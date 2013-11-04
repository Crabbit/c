#include<stdio.h>
#include<string.h>
#include<gtk/gtk.h>

#include<stdlib.h>	
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>

#define PORT 9999
#define MAXDATASIZE 1024

char platform[130][40];

void my_err( const char *err_string, int line )
{
        fprintf( stderr,"line:%d",line );
        perror( err_string );
        exit( 1 );
}
int process(int chooseWay, const char *start_platform, const char *end_platform,int sock_fd )
{
	char 	sendline[MAXDATASIZE] = { 0 },recvline[MAXDATASIZE] = { 0 };
        int 	num, i, j, k;

	sprintf( sendline, "%d", chooseWay );
	strcat( sendline,"#" );
	strcat( sendline,start_platform );
	strcat( sendline,"#" );
	strcat( sendline,end_platform );
	strcat( sendline,"$" );

	send( sock_fd, sendline, strlen( sendline ), 0 );
	printf( "Send OK \n" );

	if( ( num = recv( sock_fd, recvline, MAXDATASIZE, 0 ) ) <= 0 ){

//		printf("fdgdgdszvfzdb");
		printf( "Server Terminated.n\n" );
//		printf("dsfgsd");
		return ;
	}

	close( sock_fd );
	printf( "Recive OK \n" );

//	for(i=0; recvline[i]; i++)
//		printf("%c", recvline[i]);
	//if receive status--- -1,means has problem
	if( strcmp( recvline, "-1" ) == 0 )
		printf( "Server Recvive Problem");
	for(i=0; i<130; i++)
		platform[i][0] = '\0';
	for(i=0, j=0, k=0; recvline[i]; i++){

		if(recvline[i] != '#')
			platform[j][k++] = recvline[i];
		else{
		
			platform[j][k] = '\0';
			j+=1, k=0;
		}
	}
	strcpy(platform[j], "end");
//	for(i=0; recvline[i]; i++)
//		printf("%c", recvline[i]);

	return 1;
}
void SOCK_CLIENT( int chooseWay, const char *start_platform, const char *end_platform )
{
        int 	sock_fd;
        struct 	hostent *he;
        struct 	sockaddr_in server;

	if(( he = gethostbyname( "192.168.200.250" )) == NULL)
		my_err( "Get Host By Name",__LINE__ );
        if( ( sock_fd = socket( AF_INET, SOCK_STREAM,0 ) ) == -1 )
                my_err( "Socket",__LINE__ );
        bzero( &server,sizeof( server ) );

                server.sin_family = AF_INET;
                server.sin_port = htons( PORT );
                server.sin_addr = *( ( struct in_addr *)he->h_addr);

        if( connect( sock_fd,( struct sockaddr * )&server, sizeof( server ) ) == -1 )
                my_err( "Connect",__LINE__ );


	process(chooseWay, start_platform, end_platform, sock_fd );
}

GtkWidget * entry1;
GtkWidget * entry2;

int	chooseWay;
static GtkWidget	*ourgif;
static gchar *picture[6] = {"./pictrue/1.jpg", "./pictrue/2.jpg", "./pictrue/3.jpg", "./pictrue/4.jpg","./pictrue/5.jpg"};

GtkWidget * ride_way(void);
GtkWidget * start_end_platform(void);
void platform_info(GtkWidget * buton, gpointer data);
void choose_route(GtkWidget * button, gchar * data);
void make_dialog(GtkWidget * BUTTON, gpointer data);
void make_dialog_result(char data[64][40]);
void make_dialog_result_error(char *data);

void platform_info(GtkWidget * buton, gpointer data)
{
	const gchar     *start_platform = gtk_entry_get_text(GTK_ENTRY(entry1));
        const gchar     *end_platform = gtk_entry_get_text(GTK_ENTRY(entry2));
	char	buf[80];
	int	i, j;

	if(!strcmp(start_platform, end_platform)){

		make_dialog_result_error("您输入的起始站相同\n请出新输入");
		return ;
	}

	for(i=0; start_platform[i]; i++)
		if((start_platform[i]>=0 && start_platform[i]<48) || (start_platform[i]>58 && (start_platform[i]<128))){

			make_dialog_result_error("您输入了非法字符\n请出新输入");
			return ;
		}
	for(i=0; end_platform[i]; i++)
		if((end_platform[i]>=0 && end_platform[i]<48) || (end_platform[i]>58 && (end_platform[i]<128))){

			make_dialog_result_error("您输入了非法字符\n请出新输入");
			return ;
		}

	SOCK_CLIENT( chooseWay, start_platform, end_platform );

	if(!strncmp("error", platform[0], 5)){

		strcpy(buf, platform[0]+5);
		printf("****%s\n", platform[0]);
		make_dialog_result_error(buf);
		return ;
	}
	make_dialog_result(platform);
}
void make_dialog_result_error(char *data)
{
	GtkWidget       *dialog;
        GtkWidget       *vbox;
	GtkWidget	*label;

	dialog = gtk_dialog_new();
        gtk_widget_set_size_request(dialog,400,200);
        gtk_container_set_border_width(GTK_CONTAINER(dialog), 30);
        vbox = GTK_DIALOG(dialog)->vbox;
	label = gtk_label_new(data);
	gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

	gtk_widget_show_all(dialog);
}
void make_dialog_result(char data[120][40])
{
        GtkWidget       *dialog;
        GtkWidget       *vbox;
        GtkWidget       *table;
        GtkWidget       *scrolled;
        GtkWidget       *button;
	GtkWidget	*label;
	GtkWidget	*text;

        dialog = gtk_dialog_new();
	gtk_widget_set_size_request(dialog,600,200);
	gtk_container_set_border_width(GTK_CONTAINER(dialog), 30);
        vbox = GTK_DIALOG(dialog)->vbox;
	
	int	i, j, k=0;
	char	buf[40];

//	printf("ceate tabel\n");


	table = gtk_table_new(30, 6, FALSE);
	gtk_box_pack_start(GTK_BOX(vbox), table, TRUE, TRUE, 0);
	for(i=0; i<30; i++)
		for(j=0; j<6; j++){

			if(!strcmp(data[k], "-2"))
				k++, j = 0, i++;
			if(data[k][0] == '$')
				data[k][0] = ' ', j = 0, i++;
			if(!strcmp(data[k], "end")){

				i = j = 400;
				continue ;
			}
			label = gtk_label_new(data[k++]);
			gtk_table_attach_defaults(GTK_TABLE(table), label, j, j+1, i, i+1);
		}

        gtk_widget_show_all(dialog);
}
void choose_route(GtkWidget * button, gchar * data)
{
        static int      i=0;

        if(i == 1){
		chooseWay = atoi(data);
                i = -1;
        }
        i++;
}
void make_dialog(GtkWidget * BUTTON, gpointer data)
{
	GtkWidget	*dialog;
	GtkWidget	*vbox;
	GtkWidget	*image;
	GtkWidget	*scrolled;
	GtkWidget	*button;

	dialog = gtk_dialog_new();
        gtk_widget_set_size_request(dialog,1000,600);
	vbox = GTK_DIALOG(dialog)->vbox;
	image = gtk_image_new_from_file("./subway.jpg");
	scrolled = gtk_scrolled_window_new(NULL,NULL);	// 创建滚动窗口构件
	gtk_box_pack_start(GTK_BOX(vbox), scrolled, TRUE, TRUE, 0);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled), image);

	gtk_widget_show_all(dialog);
}
gint	i=0;
void change_picture(void)
{
	gtk_image_set_from_file(GTK_IMAGE(ourgif), picture[i]);
	i++;
	if(i == 5)
		i = 0;
}
GtkWidget * create_interface(void)
{
	GtkWidget	*scrolled;
        GtkWidget	*button;
	GtkWidget	*table;
	GtkWidget	*image;
	GtkWidget	*label;
	GtkWidget	*box;
	GtkWidget	*box1;
	GtkWidget	*frame;

	table = gtk_table_new(12, 2, TRUE);
	ourgif = gtk_image_new_from_file("./pictrue/1.jpg");
	gtk_table_attach_defaults(GTK_TABLE(table), ourgif, 0, 1, 0, 12);
	gtk_timeout_add(1500, (GtkFunction)change_picture, NULL);

	char	*title;
	label = gtk_label_new(NULL);
	title = "<span foreground=\"Tomato\"><big><b>欢迎乘坐上海地铁\n请在下面选择您的出行方式\n起始站</b></big></span>";
	frame = gtk_frame_new(" ");
	gtk_label_set_markup(GTK_LABEL(label), title);
	gtk_container_add(GTK_CONTAINER(frame), label);
	gtk_table_attach_defaults(GTK_TABLE(table), frame, 1, 2, 3, 6);

	image = gtk_image_new_from_file("./pictrue/happy.jpg");
	scrolled = gtk_scrolled_window_new(NULL, NULL);
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled), image);
	gtk_table_attach_defaults(GTK_TABLE(table), scrolled, 1, 2, 0, 3);

	box = gtk_hbox_new(TRUE, 5);
	gtk_container_set_border_width(GTK_CONTAINER(box), 30);
	box1 = ride_way();
	gtk_box_pack_start(GTK_BOX(box), box1, TRUE, TRUE, 0);
	box1 = start_end_platform();
	gtk_box_pack_start(GTK_BOX(box), box1, FALSE, FALSE, 0);
	gtk_table_attach_defaults(GTK_TABLE(table), box, 1, 2, 6, 10);

	box = gtk_hbox_new(FALSE, 0);
	gtk_container_set_border_width(GTK_CONTAINER(box), 20);
	gtk_table_attach_defaults(GTK_TABLE(table), box, 1, 2, 10, 12);
	button = gtk_button_new_with_label("点击此按钮\n显示地图");
	gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 10);
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(make_dialog), NULL);
	button = gtk_button_new_with_label("点击此按钮\n确定");
	g_signal_connect(GTK_OBJECT(button), "clicked", G_CALLBACK(platform_info), NULL);
	gtk_box_pack_start(GTK_BOX(box), button, TRUE, TRUE, 10);

	return table;
}
GtkWidget * ride_way(void)
{
	GtkWidget	*box;
	GtkWidget	*label;
	GSList 		*group=NULL;
        GtkWidget 	*radio;

	char	*title;

	box = gtk_vbox_new(FALSE, 0);
	label = gtk_label_new(NULL);
	title = "<span foreground=\"SlateBlue4\"><big>请选择</big></span>";
	gtk_label_set_markup(GTK_LABEL(label), title);
        gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
        radio = gtk_radio_button_new_with_label(group, "最短路径");
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio), TRUE); //将此按钮设置为选中状态  
        gtk_box_pack_start(GTK_BOX(box), radio, TRUE, TRUE, 0);
        group = gtk_radio_button_group(GTK_RADIO_BUTTON(radio));
	g_signal_connect(G_OBJECT(radio), "clicked", G_CALLBACK(choose_route), "0");
        radio = gtk_radio_button_new_with_label(group, "最少换乘");
        gtk_box_pack_start(GTK_BOX(box), radio, TRUE, TRUE, 0);
        group = gtk_radio_button_group(GTK_RADIO_BUTTON(radio));
	g_signal_connect(G_OBJECT(radio), "clicked", G_CALLBACK(choose_route), "1");
        radio = gtk_radio_button_new_with_label(group, "最少票价");
        gtk_box_pack_start(GTK_BOX(box), radio, TRUE, TRUE, 0);
        group = gtk_radio_button_group(GTK_RADIO_BUTTON(radio));
	g_signal_connect(G_OBJECT(radio), "clicked", G_CALLBACK(choose_route), "2");

	return box;
}
GtkWidget * start_end_platform(void)
{
	GtkWidget	*box;
	GtkWidget	*box1;
	GtkWidget	*label;

	box = gtk_vbox_new(FALSE, 20);
	gtk_container_set_border_width(GTK_CONTAINER(box), 0);
	label = gtk_label_new("请输入起始站");
	gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
	
        box1 = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(box), box1, FALSE, FALSE, 5);
        label = gtk_label_new("出发站");
        entry1 = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(box1), label, FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX(box1), entry1, FALSE, FALSE, 5);

        box1 = gtk_hbox_new(FALSE, 0);
        label = gtk_label_new("终点站");
        entry2 = gtk_entry_new();
        gtk_box_pack_start(GTK_BOX(box1), label, FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX(box1), entry2, FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX(box), box1, FALSE, FALSE, 5);

	return box;
}
int main(int argc, char ** argv)
{
	GtkWidget	*window;
	GtkWidget	*table;
	GdkColor	color;
	
        gtk_init(&argc,&argv);
        window= gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title(GTK_WINDOW(window), "用户选择系统");
	gtk_container_border_width(GTK_CONTAINER(window), 15);
        gtk_widget_set_size_request(window,1000,600);
        gtk_signal_connect(GTK_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_MOUSE);
	gdk_color_parse("Gainsboro", &color);
	gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);

	table = create_interface();
	gtk_container_add(GTK_CONTAINER(window), table);
		
	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
