#include<stdio.h>
#include<stdlib.h>
/*顺序栈的实现和基本操作*/
#define STACK_INIT_SIZE 100      //存储空间初始分配量
#define STACKINCREMENT 10        //存储空间分配增量
typedef int SElemType;           //栈的数据类型 

//顺序存储表示
typedef struct{
    SElemType *base;             //首地址，在栈构造之前和销毁之后，base的值为NULL
    SElemType *top;              //栈顶指针
    int stacksize;               //当前已分配的存储空间，以元素为单位
}Sqstack;

//基本操作
void InitStack(Sqstack *S)
{
    //构造一个空栈
    S->base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S->base) printf("Init fails!\n");
    S->top = S->base;             //栈空标志，栈顶指针指向首地址
    S->stacksize = STACK_INIT_SIZE;
}

void GetTop(Sqstack *S,SElemType *e)
{
    //若栈不空，则用e返回S的栈顶元素
    if(S->top == S->base) printf("Can't GetTop, Stack Empty!\n");
    *e = *(S->top - 1);          //非空栈中，栈顶指针始终在栈顶元素的下一个位置上
}

void Push(Sqstack *S,SElemType e)
{
    //插入元素e为新的栈顶元素
    if(S->top - S->base >= S->stacksize){  //栈满，追加存储空间
        S->base = (SElemType*)realloc(S->base,(S->stacksize + STACKINCREMENT)*sizeof(SElemType));
        if(!S->base) printf("realloc fails!\n");
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *S->top = e;
    S->top ++;
}

void Pop(Sqstack *S,SElemType *e)
{
    //若栈不空，删除S的栈顶元素，用e返回其值
    if(S->top != S->base){
        *e = *(S->top - 1);
        S->top--;
    }
    else
    {
        printf("Stack Empty!\n");
    }
}

int StackEmpty(Sqstack *S)
{
    if(S->top == S->base){
        return 1;
    }
    else
    {
        return 0;
    }
    
}

int main()
{
    SElemType elem;
    int num;
    Sqstack S;
    //初始化
    InitStack(&S);
    printf("num = ");
    scanf("%d",&num);
    printf("Input stack element:\n");
    for(int i = 0; i < num; i++){
        scanf("%d",&elem);
        getchar();
        Push(&S,elem);
    }
    SElemType out;
    printf("GetTop: ");
    GetTop(&S,&out);
    printf("%d\n",out);
    printf("Last in First out:\n");
    while(!StackEmpty(&S)){
        Pop(&S,&out);
        printf("%d ",out);
    }
    printf("\n");

    system("pause");
    return 0;
}


