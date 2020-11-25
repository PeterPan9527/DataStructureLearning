#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX_NUM 20
typedef char VerTexType;
int visited[MAX_VERTEX_NUM];  //访问标志数组

//-------------------------------------------------------------------------------------
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
//-------------------------------------------------------------------------------------

typedef struct ArcNode{      //表结点
    int adjvex;              //该弧指向的顶点的位置
    struct ArcNode *nextarc; //指向下一条弧的指针
}ArcNode;

typedef struct VNode{        //头结点
    VerTexType data;         //顶点信息
    ArcNode *firstarc;       //指向第一条依附该顶点的弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{              //图
    AdjList vertices;        //邻接表
    int vexnum,arcnum;     
}ALGraph;

int LocateVex(ALGraph* G, VerTexType e, int n)   //e顶点值，n顶点数
{
    int i;
    for(i = 0; i < n; i++){
        if(G->vertices[i].data == e){
            return i;   //返回顶点位置
        }
    }
    return -1;    //找不到顶点，返回-1；
}

void CreateALGraph(ALGraph *G)
{
    printf("Input vertex number and arc number:\n");
    scanf("%d%d",&G->vexnum,&G->arcnum);
    getchar();
    //建立头结点表
    for(int i = 0; i < G->vexnum; ++i){
        printf("Input Vertex:\n");
        scanf("%c",&G->vertices[i].data);
        getchar();
        G->vertices[i].firstarc = NULL;       //初始化，边表置空
    }
    //建立边表
    char v1,v2;
    int i,j;
    ArcNode *arclist;                        //边表结点指针
    for(int k = 0; k < G->arcnum; ++k){
        printf("Input v1 of arc:\n");        //输入边依附的两顶点
        scanf("%c",&v1);
        getchar();
        printf("Input v2 of arc:\n");  
        scanf("%c",&v2);
        getchar();
        //获取顶点位置
        i = LocateVex(G,v1,G->vexnum);
        if(i == -1) printf("Locate error\n");
        j = LocateVex(G,v2,G->vexnum);
        if(j == -1) printf("Locate error\n");
        //scanf("%d%d",&i,&j);
        
        //建立G->vertices[i]的边表
        arclist = (ArcNode*)malloc(sizeof(ArcNode));
        arclist->adjvex = j;                  //该弧指向的顶点的位置
        arclist->nextarc = G->vertices[i].firstarc;     //头插法,每次将结点插在最前端
        G->vertices[i].firstarc = arclist;
        /*有向图无需此步骤：输入<v1,v2>
        //建立G->vertices[j]的边表
        arclist = (ArcNode*)malloc(sizeof(ArcNode));
        arclist->adjvex = i;
        arclist->nextarc = G->vertices[j].firstarc;
        G->vertices[j].firstarc = arclist;
        */
    }
}

void PrintALGraph(ALGraph *G)
{
    printf("\nALGraph:\n");
    for(int i = 0; i < G->vexnum; i++){
        printf("%c -> ",G->vertices[i].data);
        while(G->vertices[i].firstarc != NULL){
            printf("%d -> ",G->vertices[i].firstarc->adjvex);
            G->vertices[i].firstarc = G->vertices[i].firstarc->nextarc;
        }
        printf("\n");
    }
}

//广度优先搜索算法(图的邻接表存储结构)
void BFS_adjlist(ALGraph *G,int v)
{
    LinkQueue Q;
    InitQueue(&Q);   //声明，初始化一个辅助队列Q
    visited[v] = 1;
    printf("%c -> ",G->vertices[v].data);
    EnQueue(&Q,v);    //元素（的位置i）入队列
    int j,k;
    while (!QueueEmpty(&Q))
    {
        DeQueue(&Q,&j);
        while(G->vertices[j].firstarc != NULL){     //遍历与j相邻的顶点
            k = G->vertices[j].firstarc->adjvex;    //k为相邻顶点的index
            if(visited[k] == 0){
                visited[k] = 1;
                printf("%c -> ",G->vertices[k].data);
                EnQueue(&Q,k);
                G->vertices[j].firstarc = G->vertices[j].firstarc->nextarc;
            }
       }//while内
    }//while外
}

//处理非连通图
void BFSTraverse_adjlist(ALGraph *G)
{
    for(int i = 0; i < G->vexnum; ++i){
        visited[i] = 0;
    }
    for(int i = 0; i< G->vexnum; ++i){
        if(visited[i] == 0){
            BFS_adjlist(G,i);       //这里G已是指针不用取地址&
        }
    }
}

int main()
{
    ALGraph G;
    CreateALGraph(&G);
    PrintALGraph(&G);
    printf("BFS_adjlist:\n");
    BFSTraverse_adjlist(&G);
    
    system("pause");
    return 0;
}