#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define M 100

typedef int TElemType;  //树的数据类型

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
    printf("%d ",data);
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
   
//后序遍历（较复杂）
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

//BST(binary search tree)二叉搜索树，根>左，根<右

void insert(Tree* tree,int value){
    BiTree node=(BiTree)malloc(sizeof(BiTNode));
    node->data=value;
    node->lchild=NULL;
    node->rchild=NULL;
    
    if(tree->root == NULL){  //如果树为空的，直接将node作为根节点
        tree->root=node;    //root是指向二叉树结点的指针
    }
    else{  //否则循环比较其左右子树
        BiTree temp=tree->root;  //temp为当前结点，value和当前结点比较
        while(temp!=NULL){
            if(value<temp->data){  //小于结点的数据插入到其左孩子
                if(temp->lchild==NULL){
                    temp->lchild=node;  //如果左孩子为空就直接插入，并返回
                    return;
                }
                else{   //否则当前结点更新为左孩子,继续从新开始比较
                    temp=temp->lchild;
                }
            }
            else {  //大于结点的数据插入到其右孩子，同理
                if(temp->rchild==NULL){
                    temp->rchild=node;
                    return;
                }
                else{
                    temp=temp->rchild;
                }
            }
        }
    }
    
}

int Get_Treeheight(BiTNode* node)   //求二叉树的深度（高度）
{
    if(node==NULL){
        return 0;
    }
    else{
        int left_h = Get_Treeheight(node->lchild);
        int right_h = Get_Treeheight(node->rchild);
        int Max = left_h;
        if(right_h > left_h) Max = right_h;
        return Max + 1;
    }
}

int main()
{
    int arr[7]={6,3,8,2,5,1,7};
    Tree tree;
    tree.root=NULL;
    int i;
    for(i=0;i<7;i++){
        insert(&tree,arr[i]);
    }
    printf("BST_PreOrder:\n");
    PreOrderTraverse(tree.root,visit);
    printf("\nBST_InOrder:\n"); 
    InOrderTraverse(tree.root,visit);  //二叉搜索树的性质，所有BST的中序遍历都是从小到大排列的
    printf("\n");
    printf("BST_PostOrder:\n");
    PostOrderTraverse(tree.root,visit);
    printf("\n");
    printf("Tree height:  ");
    printf("%d\n",Get_Treeheight(tree.root));

    system("pause");
    return 0;
}