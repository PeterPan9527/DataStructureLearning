#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 31

typedef struct BTNode{
    int data;
    struct BTNode* lchild,*rchild;
}BTNode,*BiTree;

//根据后序和中序序列建立贰叉树
BiTree createBiTreePostIn(int post[],int in[],int number)
{
    if(number==0) return NULL;
    int root=post[number-1]; //The last element of postorder is a root
    int i=0;
    while(in[i]!=root && i<number) i++;//i, is the position of a root in inorder
    int leftnumber=i;
    int rightnumber=number-i-1;

    BiTree node=(BiTree)malloc(sizeof(BTNode));
    node->data=root;
    node->lchild=createBiTreePostIn(&post[0],&in[0],leftnumber);
    node->rchild=createBiTreePostIn(&post[leftnumber],&in[i+1],rightnumber);

    return node;
}
/*
void visit(BiTree p)
{
    if(p!=NULL) printf("%d ",p->data);
}

void PreOrder(BiTree T)
{
    if(T!=NULL){
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}
*/

typedef struct QueueNode{
	BiTree data;
	struct QueueNode *next;
}QueueNode,*pQueueNode;

typedef struct Queue{
	pQueueNode front;
	pQueueNode rear;
}Queue,*pQueue;

pQueue init(pQueue pq){
	pq->front=(pQueueNode)malloc(sizeof(QueueNode));
	pq->front->next=NULL;
	pq->rear=pq->front;
	return pq;
}

void enqueue(pQueue pq,BiTree t){
	pQueueNode pNew=(pQueueNode)malloc(sizeof(QueueNode));
	pNew->data=t;
	pNew->next=NULL;
	pq->rear->next=pNew;
	pq->rear=pNew;
}

BiTree dequeue(pQueue pq){
	pQueueNode pTemp=(pQueueNode)malloc(sizeof(QueueNode));
	pTemp=pq->front->next;
	if(pTemp->next==NULL){
		pq->rear=pq->front;
	}else{
		pq->front->next=pTemp->next;
	}
	BiTree x=pTemp->data;
	free(pTemp);
	return x;
}

 //层序遍历
void LevelOrder(BiTree t){
	pQueue pq=(pQueue)malloc(sizeof(Queue));
	pq=init(pq);
	enqueue(pq,t);
	while(pq->rear!=pq->front){
		BiTree x=dequeue(pq);
		printf("%d ",x->data);
		if(x->lchild){
			enqueue(pq,x->lchild);
		}
		if(x->rchild){
			enqueue(pq,x->rchild);
		}
	}
}


int main()
{
    int N;
    int post[MAXSIZE],in[MAXSIZE];

    scanf("%d",&N);
    for(int i=0;i<N;i++){
        //post order
        scanf("%d",&post[i]);
    }
    for(int j=0;j<N;j++){
        //in order
        scanf("%d",&in[j]);
    }
    BiTree Tree=createBiTreePostIn(post,in,N);
    //输出先序序列检查 二叉树 错对
    //PreOrder(Tree);
    LevelOrder(Tree);
    
    system("pause");
    return 0;
}