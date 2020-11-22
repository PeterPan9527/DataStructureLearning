//图的邻接矩阵存储表示,深度优先搜索
#include<stdio.h>
#include<stdlib.h>
#define INFINITY 32767
#define MAX_VERTEX_NUM 20
typedef int ArcType;       //边权值类型
typedef char VertexType;   //顶点类型
int visited[MAX_VERTEX_NUM];  //访问标志数组

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
        printf("Input arc: \n");
        scanf("%d%d%d",&v1,&v2,&w);
        G->adjmatrix[v1][v2] = w;
        G->adjmatrix[v2][v1] = G->adjmatrix[v1][v2];   //无向图，邻接矩阵对称
    }
}

void PrintMGraph(MGraph *G)
{
    printf("\nAdjacancy Matrix: \n");
    for(int i = 0; i < G->vexnum; ++i){
        for(int j = 0; j < G->vexnum; ++j){
            printf("%-5d ",G->adjmatrix[i][j]);
        }
        printf("\n");
    }
}

//邻接矩阵的DFS算法
void DFS_adjmatrix(MGraph *G,int i)
{
    visited[i] = 1;
    printf("%c -> ",G->vex[i]);
    for(int j = 0; j < G->vexnum; ++j){
        if(visited[j] ==0 && G->adjmatrix[i][j] != INFINITY)  //当前顶点与下一顶点间存在弧且下一顶点未被访问
        {
            DFS_adjmatrix(G,j);
        }
    }
}

//深度优先遍历
void DFSTraverse_adjmatrix(MGraph *G)
{
    for(int i = 0; i < G->vexnum; ++i) visited[i] = 0;
    for(int i = 0; i< G->vexnum; ++i){
        if(!visited[i]){
            DFS_adjmatrix(G,i);
        }
    }
}

int main(void)
{
    MGraph G;
    CreateMGraph(&G);
    PrintMGraph(&G);
    printf("DFS Traverse:\n");
    DFSTraverse_adjmatrix(&G);
    printf("End\n");

    system("pause");
    return 0;
}