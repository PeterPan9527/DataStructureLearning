#include<stdio.h>
#include<stdlib.h>
typedef int QElemType;      //队列数据类型
//----- 单链队列————队列的链式存储结构 -----
typedef struct QNode{
    QElemType data;
    struct QNode *next;
}QNode,*QueuePtr;
typedef struct{
    QueuePtr front;   //队头指针
    QueuePtr rear;    //队尾指针
}LinkQueue;

void InitQueue(LinkQueue *Q)
{
    //构造一个空队列Q (注意：队头为Q->front->next指向的结点)
    Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));  //空结点
    if(!Q->front){
        printf("Init fails!\n");
    }
    Q->front->next = NULL;
}

void DestroyQueue(LinkQueue *Q)
{
    //销毁队列Q
    while(Q->front){
        Q->rear = Q->front->next;
        free(Q->front);
        Q->front = Q->rear;
    }
}

void EnQueue(LinkQueue *Q,QElemType e)
{
    //插入元素e为Q的新的队尾元素(队头出，队尾入)
    QueuePtr p;
    p = (QueuePtr)malloc(sizeof(QNode));
    if(!p){
        printf("malloc fails!\n");
    }
    p->data = e;
    p->next = NULL;
    Q->rear->next = p;
    Q->rear = p;
}

void DeQueue(LinkQueue *Q,QElemType *e)
{
    //若队列不空，删除Q的队头元素，并用e返回
    if(Q->front == Q->rear){
        printf("Queue Empty!\n");
    }
    QueuePtr p;
    p = Q->front->next;        //指向队头结点
    *e = p->data;
    Q->front->next = p->next;  //空结点指向新的队头结点
    if(Q->rear == p){
        Q->rear = Q->front;    //设置队空
    }
    free(p);                   //释放原队头结点空间
}

int QueueEmpty(LinkQueue *Q)
{
    if(Q->front == Q->rear){
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int num;
    QElemType e;
    LinkQueue Q;
    InitQueue(&Q);   //初始化
    printf("Input the number of Queue elements: ");
    scanf("%d",&num);
    getchar();
    while(num--){
        scanf("%d",&e);
        getchar();
        EnQueue(&Q,e);
    }
    printf("\n");
    printf("First in First out:\n");
    while(!QueueEmpty(&Q)){
        DeQueue(&Q,&e);
        printf("%d ",e);
    }
    printf("\n");

    system("pause");
    return 0;
}