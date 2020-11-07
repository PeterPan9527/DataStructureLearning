#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

typedef struct node{
   char data;
   struct node*left;
   struct node*right;
}Node;

void visit(char data)
{
    printf("%c",data);
}

//遍历二叉树的递归算法

//先序遍历：根->左->右
void PreorderTraverse(Node* node,void visit(char data))
{
    void visit(char data);
    if(node!=NULL){
        visit(node->data);
        PreorderTraverse(node->left,visit);
        PreorderTraverse(node->right,visit);
    }
}

//中序遍历：左->根->右
void InorderTraverse(Node*node,void visit(char data))
{
    void visit(char data);
    if(node!=NULL){
        InorderTraverse(node->left,visit);
        visit(node->data);
        InorderTraverse(node->right,visit);
    }
}

//后序遍历二叉树：左->右->根
void PostorderTraverse(Node*node,void visit(char data))
{
    void visit(char data);
    if(node!=NULL){
        PostorderTraverse(node->left,visit);
        PostorderTraverse(node->right,visit);
        visit(node->data);
    }
}

int main()
{
    //静态建立二叉树
    Node n1,n2,n3,n4,n5,n6,n7,n8,n9,n10,n11;
    n1.data='-';n1.left=&n2;n1.right=&n3;
    n2.data='+';n2.left=&n4;n2.right=&n5;
    n3.data='/';n3.left=&n6;n3.right=&n7;
    n4.data='a';n4.left=NULL;n4.right=NULL;
    n5.data='*';n5.left=&n8;n5.right=&n9;
    n6.data='e';n6.left=NULL;n6.right=NULL;
    n7.data='f';n7.left=NULL;n7.right=NULL;
    n8.data='b';n8.left=NULL;n8.right=NULL;
    n9.data='-';n9.left=&n10;n9.right=&n11;
    n10.data='c';n10.left=NULL;n10.right=NULL;
    n11.data='d';n11.left=NULL;n11.right=NULL;
    
    printf("PreorderTraverse:\n");
    PreorderTraverse(&n1,visit);
    printf("\n");

    printf("InorderTraverse:\n");
    InorderTraverse(&n1,visit);
    printf("\n");

    printf("PostorderTraverse:\n");
    PostorderTraverse(&n1,visit);
    printf("\n");

    system("pause");
    return 0;
}

