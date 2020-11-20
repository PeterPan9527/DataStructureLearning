//图的邻接表存储表示
#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX_NUM 20
typedef char VerTexType;

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

int main()
{
    ALGraph G;
    CreateALGraph(&G);
    PrintALGraph(&G);
    
    system("pause");
    return 0;
}
