/*附加题：
       【实验要求】
        以先序遍历的方式键入二叉树各结点的数据域（字符型），建立二叉树，然后分别用递归和非递归的方法以先序、
        中序和后序算法对二叉树进行遍历，并输出遍历结果。
        》例如，要建立如下二叉树，用户需依次键入'A','B','D',' ',' ',' ','C',' ',' '这几个字符。
        》先序遍历：ABDC                                       A
        》中序遍历：DBAC                         二叉树      B     C
        》后序遍历：DBCA                                  D
        保存文件biTree.cpp        

        答题人：潘洋 学号：22920192204046          
*/
#include<stdio.h>
#include<stdlib.h>
#define M 100

typedef char TElemType;  //树的数据类型

//二叉链表类型 tree.2
typedef struct BiTNode{
    TElemType data;
    int symbol;          //用于后序遍历，判断节点在栈顶出现次数的标志
    BiTNode* lchild,*rchild;
}BiTNode,*BiTree;

typedef struct{
    BiTree root;
}Tree;

//栈的定义

typedef struct stack 
{
	BiTree elements[M];
	int top;
}SeqStack;//定义一个储存树类型地址的栈，方便遍历的时候追踪到树的地址。

SeqStack s;   //先声明一个栈

void setnull()//初始化栈
{
	s.top =0;
}
 
void Push(BiTree temp)//入栈操作
{
	s.elements[s.top++] = temp;
}
 
BiTree Pop()//取栈顶并出栈顶
{
	return s.elements[--s.top];
}
 
int StackEmpty()//判断空栈
{
	return s.top == 0;
}

void visit(TElemType data)
{
    printf("%c ",data);
}

//使用栈来实现非递归遍历二叉树的算法

//先序遍历
void PreOrderTraverse(BiTree bt,void(*visit)(TElemType))
{
    BiTree p=bt;
    while(p||!StackEmpty()){
        if(p){
            visit(p->data);  //根结点不为空则访问，然后入栈，接下来访问左孩子
            Push(p);
            p=p->lchild;
        }
        else{
            p=Pop();
            p=p->rchild;
        }
    }
}

//中序遍历
void InOrderTraverse(BiTree bt,void(*visit)(TElemType))
{
    BiTree p=bt;
    while(p||!StackEmpty()){
        if(p){
            Push(p);  //根结点进栈，遍历左子树
            p=p->lchild;
        }
        else{
            p=Pop();
            visit(p->data);
            p=p->rchild;
        }
    }
}
   
//后序遍历
void PostOrderTraverse(BiTree bt,void(*visit)(TElemType))
{
    BiTree p=bt;
    while(p||!StackEmpty()){
        if(p){        //结点非空
            p->symbol=1;   //标志置1，结点第一次被访问
            Push(p);
            p=p->lchild;
        }
        else{         //结点为空
           p=Pop();
           if(p->symbol==1){
              p->symbol=2;
              Push(p);
              p=p->rchild;
           }
           else if(p->symbol==2){       //结点第二次在栈顶，输出
              visit(p->data);
              p=NULL;            //置空，防止死循环
           }     
        }
    }
}

//遍历二叉树的递归算法

//先序遍历：根->左->右
void PreOrder(BiTree node,void visit(char data))
{
    void visit(char data);
    if(node!=NULL){
        visit(node->data);
        PreOrder(node->lchild,visit);
        PreOrder(node->rchild,visit);
    }
}

//中序遍历：左->根->右
void InOrder(BiTree node,void visit(char data))
{
    void visit(char data);
    if(node!=NULL){
        InOrder(node->lchild,visit);
        visit(node->data);
        InOrder(node->rchild,visit);
    }
}

//后序遍历二叉树：左->右->根
void PostOrder(BiTree node,void visit(char data))
{
    void visit(char data);
    if(node!=NULL){
        PostOrder(node->lchild,visit);
        PostOrder(node->rchild,visit);
        visit(node->data);
    }
}

//以先序遍历方式输入建立二叉树
void CreateBiTree_PreOrder(BiTree &T) //BiTree 本身已经是一个指针了，为什么要用Bitree &T呢？
{                                     //首先明确一个问题：Bitree &T 中的&是引用，这个也就是取地址的意思，
    char ch;                          //这个只有C++中才有，你也可以用C中的指针，用Bitree *T，但是这样
    scanf("%c",&ch);                  //你调用Insert时就必须这样调用Insert(&T).
    getchar();     //吸收回车键        //&在c中是取地址，在C++中是引用。
    if(ch==' '){   //输入空格：' '表示该节点为空
        T=NULL;
        return;
    }
    else{
        T=(BiTree)malloc(sizeof(BiTNode));
        if(T==NULL){
            printf("Error!\n");
            return;
        }
        T->data=ch;
        CreateBiTree_PreOrder(T->lchild); //先递归建立左子树
        CreateBiTree_PreOrder(T->rchild); //再递归建立右子树
    }
    return;
}

int main()
{
    Tree tree;
    /*BiTNode n1,n2,n3,n4;
    n1.data='A';n1.lchild=&n2;n1.rchild=&n3;   //手动建立二叉树，检查遍历算法有无问题
    n2.data='B';n2.lchild=&n4;n2.rchild=NULL;
    n3.data='C';n3.lchild=NULL;n3.rchild=NULL;
    n4.data='D';n4.lchild=NULL;n4.rchild=NULL;
    tree.root=&n1;*/

    CreateBiTree_PreOrder(tree.root);         //递归先序建立二叉树

    //递归遍历
    printf("PreOrder_Recersion:\n");
    PreOrder(tree.root,visit);
    printf("\n");
    printf("InOrder_Recersion:\n");
    InOrder(tree.root,visit);
    printf("\n");
    printf("PostOrder_Recersion:\n");
    PostOrder(tree.root,visit);
    printf("\n");
    //非递归遍历
    printf("PreOrder_stack:\n");
    PreOrderTraverse(tree.root,visit);
    printf("\n");
    printf("InOrder_stack:\n");
    InOrderTraverse(tree.root,visit);
    printf("\n");
    printf("PostOrder_stack:\n");
    PostOrderTraverse(tree.root,visit);
    printf("\n");

    system("pause");
    return 0;
}