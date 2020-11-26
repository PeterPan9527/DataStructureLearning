/*-------------------------网（图）的最小生成树之普里姆算法---------------------------*/
/*Minimum Cost Spanning Tree, 代价是树上各边之和最小*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INFINITY 32767
#define MAX_VERTEX_NUM 20
typedef int ArcType;       //边权值类型
typedef char VertexType;   //顶点类型

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
    for(int i = 0; i < G->vexnum; ++i){
        for(int j = 0; j < G->vexnum; ++j){
            printf("%-5d ",G->adjmatrix[i][j]);
        }
        printf("\n");
    }
}

/*----------普里姆算法----------*/
//用普里姆算法从第u个顶点出发构造网G的最小生成树T，输出T的各条边

//记录从顶点集U到V-U的代价最小的边 的辅助数组定义：
struct {
    VertexType adjvex;   //顶点
    ArcType lowcost;     //边权值
}closedge[MAX_VERTEX_NUM];

//需要的函数
int LocateVex(MGraph* G, VertexType e, int n)   //e顶点值，n顶点数
{
    int i;
    for(i = 0; i < n; i++){
        if(G->vex[i] == e){
            return i;   //返回顶点位置
        }
    }
    return -1;    //找不到顶点，返回-1；
}

void PrintArc(MGraph *G,VertexType u1,VertexType u2)
{
    int v1,v2;
    v1 = LocateVex(G,u1,G->vexnum);
    v2 = LocateVex(G,u2,G->vexnum);
    printf("%c -> %c : %d\n",u1,u2,G->adjmatrix[v1][v2]);
}

VertexType minimum(MGraph *G)
{
    ArcType min;
    VertexType vex_min;
    for(int i = 0; i < G->vexnum; ++i){
        if(closedge[i].lowcost > 0 && closedge[i].lowcost < INFINITY){
            min = closedge[i].lowcost;
            vex_min = G->vex[i];
            break;
        }
    }
    for(int j = 0; j < G->vexnum; ++j){
        if(closedge[j].lowcost < min && closedge[j].lowcost > 0){
            min = closedge[j].lowcost;
            vex_min = G->vex[j];
        }
    }
    
    return vex_min;
}

void MiniSpanTree_PRIM(MGraph *G,VertexType u)
{
    int k = LocateVex(G,u,G->vexnum);
    for(int i = 0; i < G->vexnum; ++i){
        if(i != k){
            closedge[i].adjvex = u;
            closedge[i].lowcost = G->adjmatrix[k][i];  //在邻接矩阵中找到各边权值
        }
    }
    closedge[k].lowcost = 0;         //初始，U={u}
    int newVex;
    for(int i = 1; i < G->vexnum; ++i){     //选择其余G->vexnum - 1 个顶点
        //求出T的下一个结点：第newVex顶点
        newVex = LocateVex(G,minimum(G),G->vexnum);
        //输出生成树的边
        PrintArc(G,closedge[newVex].adjvex,G->vex[newVex]);       //vex[k] -> vex[newVex] : weight  ,边依附的点和权值
        closedge[newVex].lowcost = 0;  //新顶点并入U集
        for(int j = 0; j < G->vexnum; ++j){   //新结点并入U后，从新顶点出发更新closedge中的最小边
            if(G->adjmatrix[newVex][j] < closedge[j].lowcost){
                closedge[j].lowcost = G->adjmatrix[newVex][j];
                closedge[j].adjvex = G->vex[newVex];
            }//if
        }//for内
    }//for外
}//MiniSpanTree

//主函数
int main(void)
{
    MGraph G;
    CreateMGraph(&G);
    PrintMGraph(&G);
    printf("Minimum Spanning Tree(PRIM):\n");
    MiniSpanTree_PRIM(&G,G.vex[0]);   //默认从第一个顶点出发

    system("pause");
    return 0;
}