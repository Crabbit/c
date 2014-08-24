#/*
 * =====================================================================================
 *
 *       Filename:  creat_btree.c
 *
 *    Description:  构建二叉树 学习
 *
 *        Version:  1.0
 *        Created:  2014/08/23 15时17分24秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Crabbit ( Lili ), lili00681@gmail.com
 *        Company:  Xiyou_linux
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
//定义节点 
struct BiNode{
        char data;
        struct BiNode *lch;
        struct BiNode *rch;
};
 
//先序拓展序列建立二叉树 
void Create(struct BiNode *T)
{
        T =(struct BiNode*) malloc (sizeof(struct BiNode));
         
        printf("Enter the data \n");
	setbuf( stdin, NULL );
        scanf("%c",&T->data);
	setbuf( stdin, NULL );
        if(T->data=='#')
	      T=NULL;
        if(T){
                printf("");
                Create(T->lch);
                Create(T->rch);
        }
}
 
//先序遍历 (递归)
void Preorder (struct BiNode *T)
{                    
   if(T){
      printf("%c",T->data);             // 访问根结点
       
      Preorder(T->lch); // 遍历左子树
      Preorder(T->rch);// 遍历右子树
   }
}
 
//中序遍历 （递归）
void Inorder (struct BiNode *T)
{
     if(T) {
       Inorder(T->lch);
        
       printf(" %c",T->data);
        
       Inorder(T->rch);    
       }
} 
 
//后序遍历 （递归）
void Postorder (struct BiNode *T)
{
     if(T) {
       Postorder(T->lch);
       Postorder(T->rch);
        
       printf(" %c",T->data); 
     }
} 

//求二叉树深度
int GetDepth( BiNode *T )
{
	if( T == NULL )
	{
	      	return 0;
	}

	// int Left_Length = GetDepth( T->lch );
	// int Right_Length = GetDepth( T->rch );
	// return Left_length > Right_Length ?( Left_Length + 1 ) : ( Right_length + 1 );
	return GetDepth( T->lch ) > GetDepth( T->rch ) ?
		( GetDepth( T->lch ) + 1 ) : ( GetDepth( T->rch ) + 1 );
}
 
int main()
{
    //建树 
    struct BiNode *T,*root;
    T = root;
    printf("The fuction Create() is called.\n");
    Create(T);
     
    //三种遍历递归算法 
    printf("\n");    
    printf("The fuction Preorder() is called.\n");
    Preorder(root);
     
    printf("\n");
    printf("The fuction Inorder() is called.\n");
    Inorder(root);
     
    printf("\n");
    printf("The fuction Postorder() is called.\n");
    Postorder(root);
     
     
    printf("\n");

    return 0;
}
