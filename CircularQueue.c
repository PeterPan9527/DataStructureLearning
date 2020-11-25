#include<stdio.h>
#include<stdlib.h>
//-----循环队列-----
//循环队列即顺序队列的改良，顺序队列在入队和出队时头尾指针只增不减，被删除元素空间无法从新利用
#define MAXQSIZE 100    //队列最大长度
typedef int QElemType;
typedef struct{
    QElemType *base;    //初始化的动态分配存储空间
    int front;          //头指针，若队列不空，指向队列头元素
    int rear;           //尾指针，若队列不空，指向队列尾元素的下一个位置
}SqQueue;

//基本操作
void InitQueue(SqQueue *Q)
{
    //构造一个空队列Q
    Q->base = (QElemType*)malloc(sizeof(QElemType));
    if(!Q->base){
        printf("Init Error!\n");
    }
    else{
        Q->front = Q->rear = 0;       
    }
}

int QueueEmpty(SqQueue *Q)
{
    if(Q->front == Q->rear){
        return 1;
    }
    else
    {
        return 0;
    }
}

int QueueLength(SqQueue *Q)
{
    //返回元素个数即长度
    return (Q->rear - Q->front + MAXQSIZE) % MAXQSIZE;   //最大长度尾MAXQSIZE - 1
}

void EnQueue(SqQueue *Q,QElemType e)
{
    //插入元素e为Q的新的队尾元素
    if((Q->rear + 1) % MAXQSIZE == Q->front){
        printf("Queue Full!\n");
    }
    else
    {
        Q->base[Q->rear] = e;
        Q->rear = (Q->rear + 1) % MAXQSIZE;
    }
}

void DeQueue(SqQueue *Q,QElemType *e)
{
    //若队列不空，删除Q的队头元素，用e返回
    if(Q->rear == Q->front){
        printf("Queue Empty!\n");
    }
    else
    {
        *e = Q->base[Q->front];
        Q->front = (Q->front + 1) % MAXQSIZE;
    }
}

int main()
{
    int num;
    QElemType e;
    SqQueue Q;
    InitQueue(&Q);   //初始化
    printf("Input the numbers of Queue elements: ");
    scanf("%d",&num);
    getchar();
    while (num--)
    {
        scanf("%d",&e);
        getchar();
        EnQueue(&Q,e);
    }
    printf("\nQueueLength = %d\n",QueueLength(&Q));

    printf("First In First Out:\n");
    while (!QueueEmpty(&Q))
    {
        DeQueue(&Q,&e);
        printf("%d ",e);
    }
    printf("\n");
    
    system("pause");
    return 0;
}
