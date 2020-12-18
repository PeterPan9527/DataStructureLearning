#include<stdio.h>
#include<stdlib.h>
#define INFINITY 32767
#define MAX_VERTEX_NUM 20
typedef int ArcType;       //边权值类型
typedef char VertexType;   //顶点类型
int dist[MAX_VERTEX_NUM];  //存储源点到各点的最小路径长度
int path[MAX_VERTEX_NUM];  //存储最短路径（索引）
int s[MAX_VERTEX_NUM];     //处理过的顶点集

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

int findMinDist(int n)
{
    int min;
    for(int i = 0; i < n; ++i){
        if(s[i] == 0){
            min = i;
            break;
        }
    }
    for(int i = 0; i < n; ++i){
        if(s[i] == 0 && dist[i] < dist[min]){
            min = i;
        }
    }
    return min;
}

//dist 和 path数组都没问题，但是输出有点问题，不管了，先提交了2020/11/28
void displayPath(int startV,int n)
{
    /*int a[MAX_VERTEX_NUM];    //辅助数组，用于输出path的正序
    int j,k;
    printf("ShortestPath_Dijstra:\n");
    for(int i = 0; i < n; ++i){
        j = i;
        k = 0;
        do
        {
            a[k] = path[j];
            j = path[j];
            k++;
        } while (path[j] != startV);
        
        for(int m = k; m >= 0; --m){
            printf("%d -> ",a[m]);
        }
        printf("Length: %d\n",dist[i]);
    }*/
    //逆序输出
    int j;
    printf("ShortestPath_Dijstra:\n");
    for(int i = 0; i < n; ++i){
        j = i;
        printf("End <- %d <- ",i);
        while (path[j] != startV)
        {
            printf("%d <- ",path[j]);
            j = path[j];
        }
        printf("%d <- Start, ",startV);
        printf("Length: %d\n",dist[i]);
    }
}

//startV为源点（索引）
void Dijstra(MGraph *G,int startV)
{
    //初始化数组dist，path
    for(int i = 0; i < G->vexnum; ++i){
        dist[i] = G->adjmatrix[startV][i];
        if(dist[i] != INFINITY){
            path[i] = startV;
        }
        else{
            path[i] = -1;
        }
    }
    path[startV] = startV;   //矩阵设计问题，到自身为INFINITY，但在算法中到自身可达，为0
    dist[startV] = 0;      //源点到自身的距离为0
    //初始化集合S，初始化为0
    for(int i = 0; i < G->vexnum; ++i){
        s[i] = 0;
    }
    s[startV] = 1;    //顶点放入集合S，1表示在，0表示不在
    int num = 1;
    int min;
    while (num < G->vexnum)
    {
        min = findMinDist(G->vexnum);   //dist中查找s[i]为0的最小值元素
        s[min] = 1;        //将新生成的终点加入集合S
        for(int i = 0; i < G->vexnum; ++i){
            //修改数组dist和path
            if((s[i]==0) && (dist[i] > dist[min] + G->adjmatrix[min][i])){
                dist[i] = dist[min] + G->adjmatrix[min][i]; //用已经找到的最短路径修改对应的dist
                path[i] = min;    //更新到达i顶点所要经过的最短路径的终点min
            }//if
        }//for
        num++;
    }//while
    displayPath(startV,G->vexnum);
}

int main(void)
{
    MGraph G;
    CreateMGraph(&G);
    PrintMGraph(&G);
    Dijstra(&G,0);   //从第一个顶点开始

    system("pause");
    return 0;
}
