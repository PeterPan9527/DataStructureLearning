#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX_NUM 100
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
/*任务调度规划*/

typedef int VertexType;

//边表结点结构
typedef struct ArcNode{
    int adjvex;   //该弧所指向的顶点所在的位置
    struct ArcNode* nextarc;   //指向下一条弧的指针
    //InfoType *info;     //该弧相关信息的指针
}ArcNode;

//头结点
typedef struct VNode{
    VertexType data;      //顶点信息
    ArcNode *firstarc;     //指向第一条依附该顶点的弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];

/*邻接表结构*/
typedef struct {
    AdjList vertices;
    int vexnum,arcnum;   //图的顶点数和弧数
    //int kind;                 //图的种类标志
}ALGraph;

int LocateVex(ALGraph* G, int e, int n)   //e顶点值，n顶点数
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
    int N,K;   //子任务数N，与每个子任务相关联的子任务数K
    scanf("%d",&N);
    G->vexnum = N;
    //建立顶点表
    for(int i = 0; i < G->vexnum; i++){
        G->vertices[i].data = i+1;      //子任务按1~N编号
        G->vertices[i].firstarc = NULL;    //指向的第一调依附的弧置空
    }
    //建立边表
    ArcNode *arclist;
    int m=0;
    for(int x = 0; x < G->vexnum; x++){
        scanf("%d",&K);
        if(K == 0){
            continue;
        }
        else{  //输入相关的子任务（顶点）
            for(int k = 0; k < K; k++){
                scanf("%d",&m);
                arclist = (ArcNode*)malloc(sizeof(ArcNode));
                arclist->adjvex = m - 1;     //输入为顶点，顶点减1刚好为顶点位置，用不到LocateVex函数
                arclist->nextarc = G->vertices[x].firstarc;
                G->vertices[x].firstarc = arclist;
            }
        }
    }
}
//输出邻接表
/*void Print(ALGraph *G)
{
    for(int i = 0; i < G->vexnum; i++){
        printf("%d -> ",G->vertices[i].data);
        while(G->vertices[i].firstarc != NULL){
            printf("%d -> ",G->vertices[i].firstarc->adjvex);
            G->vertices[i].firstarc = G->vertices[i].firstarc->nextarc;
        }
        printf("\n");
    }
}*/

typedef struct{
    int *base;  //栈构造前和销毁后，base值为NULL
    int *top;  //栈顶指针
    int stacksize;
}SqStack;

//初始化栈
void InitStack(SqStack *S)
{
    //构造空栈S
    S->base = (int*)malloc(STACK_INIT_SIZE*sizeof(int));
    if(!S->base) printf("error");
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
}

int Push(SqStack *S, int e)
{
    //插入e为新栈顶元素
    if(S->top - S->base >= S->stacksize){  //栈满则追加space
        S->base = (int*)realloc(S->base, (S->stacksize + STACKINCREMENT)*sizeof(int));
        if(!S->base) {printf("error"); return 0;}
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *S->top++ = e;
    return 1;
}

int Pop(SqStack *S)
{
    //若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则不ok
    int e;
    if(S->top == S->base) return -1;
    e = *--S->top;
    return e;
}

int StackEmpty(SqStack *S)
{
    if(S->top == S->base) return 1;  //为空返回 '是'
    return 0;
}


//int Indegree[100]={0};    //保存顶点入度

/*void FindInDegree(ALGraph *G, int indegree[])
{
    ArcNode *p;
    int j;
    for(int i = 0; i < G->vexnum; i++){
        p = G->vertices[i].firstarc;
        while(p != NULL){
            j = p->adjvex;    //顶点位置
            indegree[j]++;                //该位置顶点入度加   
            p = p->nextarc;
        }
    }
}*/

int TopologicalSort(ALGraph *G)  //拓扑排序，检验任务调度是否可行
{
    //若G无回路，则输出G的顶点的一个拓扑序列并返回OK，否则ERROR
    //FindInDegree(G,Indegree);        //对各顶点求入度Indegree[0...vexnum-1]
    //调用FindInDgree及数组全局定义会发生segment fault，未解决 ？？
    int Indegree[100]={0};
    ArcNode *p;
    int j;
    for(int i = 0; i < G->vexnum; i++){
        p = G->vertices[i].firstarc;
        while(p != NULL){
            j = p->adjvex;    //顶点位置
            Indegree[j]++;                //该位置顶点入度加
            p = p->nextarc;
        }
    }
    SqStack *S;
    InitStack(S);
    for(int i = 0; i < G->vexnum; i++) {  //入度为零的顶点入栈
        if(!Indegree[i]) Push(S,i);
    }
    int count = 0;
    int i;
    while(!StackEmpty(S)){
        i = Pop(S);   //printf(i,G.vertices[i].data) 输出i号顶点并计数
        //printf("%d ",G->vertices[i].data); //拓扑序列
        count++;
        for(ArcNode *p = G->vertices[i].firstarc; p; p = p->nextarc){
            int k= p->adjvex;            //对i号顶点的每个邻接点的入度减1
            if(!(--Indegree[k])) Push(S,k);  //若入度减为0，则入栈
        }//for
    }//while
    if(count < G->vexnum) return 0;    //任务调度不可行， 有向图有回路
    else return 1;                              //行
}

int main()
{
    ALGraph *G = (ALGraph*)malloc(sizeof(ALGraph));
    CreateALGraph(G);

    int result = TopologicalSort(G);
    printf("%d\n",result);
    system("pause");

    return 0;
}