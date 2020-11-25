#include<stdio.h>
#include<stdlib.h>
#define INFINITY 32767
#define MAX_VERTEX_NUM 20
typedef int ArcType;       //边权值类型
typedef char VertexType;   //顶点类型
int visited[MAX_VERTEX_NUM];  //访问标志数组

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

typedef struct{
    VertexType vex[MAX_VERTEX_NUM];   //顶点表
    ArcType adjmatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];    //邻接矩阵
    int vexnum;
    int arcnum;
}MGraph;

void CreateMGraph(MGraph *G)
{
    int v1,v2,w;
    printf("Input vertex number and arc number: \n");
    scanf("%d%d",&G->vexnum,&G->arcnum);                    //输入顶点数和边数
    getchar();
    for(int i = 0; i < G->vexnum; ++i){
        printf("Input Vertex: \n");
        scanf("%c",&G->vex[i]);                         //输入顶点向量
        getchar();
    } 
    //初始化邻接矩阵
    for(int i = 0; i < G->vexnum; ++i){
        for(int j = 0; j < G->vexnum; ++j){
            G->adjmatrix[i][j] = INFINITY;
        }
    } 
    //构造邻接矩阵
    for(int k = 0; k < G->arcnum; ++k){
        printf("Input arc(like this:'v1 v2 w' <v1,v2 should be the index of vertex,w is weight>): \n");
        scanf("%d%d%d",&v1,&v2,&w);
        G->adjmatrix[v1][v2] = w;
        G->adjmatrix[v2][v1] = G->adjmatrix[v1][v2];   //无向图，邻接矩阵对称
    }
}

void PrintMGraph(MGraph *G)
{
    printf("\nAdjacancy Matrix: \n");
    for(int i = 0; i < G->vexnum; ++i)
    {
        for(int j = 0; j < G->vexnum; ++j)
        {
            if(G->adjmatrix[i][j] == INFINITY)
            {
            printf("%-5d ",G->adjmatrix[i][j]);
            }
        }
        printf("\n");
    }
}

//广度优先搜索算法
void BFS_adjmatrix(MGraph *G,int v)
{
    LinkQueue Q;
    InitQueue(&Q);   //声明，初始化一个辅助队列Q
    visited[v] = 1;
    printf("%c -> ",G->vex[v]);
    EnQueue(&Q,v);    //元素（的位置i）入队列
    int j;
    while(!QueueEmpty(&Q)){
        DeQueue(&Q,&j);        //队头元素（位置）出队，并付给j
        for(int k = 0; k < G->vexnum; ++k){  //遍历相邻点
            if(visited[k] == 0 && G->adjmatrix[j][k] != INFINITY){
                visited[k] = 1;
                printf("%c -> ",G->vex[k]);
                EnQueue(&Q,G->vex[k]);
            }
        }
    }
}

//广度优先遍历（考虑处理非联通图情况，对每个未被访问顶点进行BFS
void BFSTraverse_adjmatrix(MGraph *G)
{
    for(int i = 0; i < G->vexnum; ++i){
        visited[i] = 0;
    }
    for(int i = 0; i < G->vexnum; ++i){
        if(visited[i] == 0){
            BFS_adjmatrix(G,i);
        }
    }
}

int main()
{
    MGraph G;
    CreateMGraph(&G);
    PrintMGraph(&G);
    printf("BFS_adjmatrix:\n");
    BFSTraverse_adjmatrix(&G);

    system("pause");
    return 0;
}