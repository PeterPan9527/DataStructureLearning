#include<stdio.h>
#include<stdlib.h>
const int MaxVertex = 10;
const int MaxEdge = 100;
typedef int datatype;
int parent[MaxVertex];    //用于存放生成树的根节点
//---------------------------图的存储结构----------------------------
//kruskal算法是依次对图中的边进行操作的，因此用边集数组存储图中的边
//将边集数组中的边按权值进行排序，提高查找速度
typedef struct{
    int from,to;    //边依附的两个顶点
    int weight;     //边上的权值
}EdgeType;
typedef struct{
    datatype vertex[MaxVertex];      //存储顶点的数组
    EdgeType edge[MaxEdge];          //存放边的数组
    int vexnum,edgenum;              //顶点数和边数
}EdgeGraph;

void CreateEdgeGraph(EdgeGraph *G)
{
    printf("Input vexnum and edgenum:\n");
    scanf("%d%d",&G->vexnum,&G->edgenum);
    getchar();
    printf("Input vertexes:\n");
    for(int i = 0; i < G->vexnum; ++i){
        scanf("%d",&G->vertex[i]);
        getchar();
    }
    printf("Input edges('from to weight','from' and 'to' should be indexes):\n");
    for(int i = 1; i <= G->edgenum; ++i){         //使用直接插入算法，数组首位留空
        scanf("%d%d%d",&G->edge[i].from,&G->edge[i].to,&G->edge[i].weight);
        getchar();
    }
}

void insertSort(EdgeGraph *G,int n)   //kruskal算法的时间复杂度取决于排序算法和边的数量e，插入排序O(e^2)
{                                     //使用高级点的排序算法入快速排序，时间复杂度为O(elne)
    int i,j;     
    for(int i = 2; i <= n; ++i){      //r[0]是哨兵,暂存r[i]，用以比较
        j = i - 1;
        G->edge[0].from = G->edge[i].from;
        G->edge[0].to = G->edge[i].to;
        G->edge[0].weight = G->edge[i].weight;
        while (G->edge[0].weight < G->edge[j].weight)
        {
            G->edge[j + 1].from = G->edge[j].from;
            G->edge[j + 1].to = G->edge[j].to;
            G->edge[j + 1].weight = G->edge[j].weight;
            j--;
        }
        G->edge[j + 1].from = G->edge[0].from;
        G->edge[j + 1].to = G->edge[0].to;
        G->edge[j + 1].weight = G->edge[0].weight;
    }
}

void PrintEdgeGraph(EdgeGraph *G)
{
    printf("all edges of graph:\n");
    for(int i = 1; i <= G->edgenum; i++){       //注意数组首位为空
        printf("%d -> %d : %d\n",G->edge[i].from,G->edge[i].to,G->edge[i].weight);
    }
    printf("all edges of graph(sorted):\n");
    insertSort(G,G->edgenum);
    for(int i = 1; i <= G->edgenum; i++){       //注意数组首位为空
        printf("%d -> %d : %d\n",G->edge[i].from,G->edge[i].to,G->edge[i].weight);
    }
}

int findRoot(int parent[],int v)
{
    int t = v;
    while (parent[t] > -1)
    {
        t = parent[t];  //求顶点t上的双亲直到根节点
    }
    return t;
}

void MiniSpanTree_Kruskal(EdgeGraph *G)
{
    for(int i = 0; i < G->vexnum; ++i){
        parent[i] = -1;
    }
    int num,i;
    int vex1,vex2;
    for(num=0,i=1; i <= G->edgenum; ++i){
        vex1 = findRoot(parent,G->edge[i].from);  //找到所在生成树的根节点
        vex2 = findRoot(parent,G->edge[i].to);    //找到所在生成树的根节点
        if(vex1 != vex2){  //找到两个根节点不同，不会构成环
            //输出加入最小生成树的边
            printf("%d -> %d : %d\n",G->edge[i].from,G->edge[i].to,G->edge[i].weight);
            parent[vex2] = vex1;   //合并成树
            num++;
            if(num == G->vexnum - 1){  //循环了“图的顶点数-1”次，返回。树的边数等于顶点数减一
                return;
            }
        }
    }
}

int main()
{
    EdgeGraph G;
    CreateEdgeGraph(&G);
    PrintEdgeGraph(&G);
    printf("Minimum Spanning Tree(Kruskal):\n");
    MiniSpanTree_Kruskal(&G);

    system("pause");
    return 0;
}