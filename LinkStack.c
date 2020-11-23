#include<stdio.h>
#include<stdlib.h>
typedef int SElemType;
//链栈
typedef struct stacknode{
    SElemType data;
    struct stacknode *next;
}stacknode;

typedef struct{
    struct stacknode* top;
}Linkstack;

void InitStack(Linkstack *p)
{
    p->top = NULL;
}

void Push(Linkstack *p,SElemType e)
{
    //头插法，入链栈
    stacknode *q;
    q = (stacknode*)malloc(sizeof(stacknode));
    q->data = e;
    q->next = p->top;
    p->top = q;
}

void Pop(Linkstack *p,SElemType *e)
{
    if(p->top == NULL){
        printf("Stack Empty!\n");
    }
    else
    {
        stacknode *q;
        *e = p->top->data;
        q = p->top;
        p->top = p->top->next;
        free(q);
    }
}

int StackEmpty(Linkstack *p)
{
    if(p->top == NULL){
        return 1;
    }
    else
    {
        return 0;
    }
}

void GetTop(Linkstack *p,SElemType *e)
{
    if(p->top != NULL){
        *e = p->top->data;
    }
    else
    {
        printf("Stack Empty!\n");
    }
    
}

int main()
{
    Linkstack S;
    InitStack(&S);
    int num;
    SElemType e;
    printf("num = ");
    scanf("%d",&num);
    printf("Input stack element:\n");
    for(int i = 0; i < num; ++i){
        scanf("%d",&e);
        getchar();
        Push(&S,e);
    }
    printf("GetTop:");
    GetTop(&S,&e);
    printf("%d\n",e);
    printf("Last in First out:\n");
    while (!StackEmpty(&S))
    {
        Pop(&S,&e);
        printf("%d ",e);
    }
    printf("\n");

    system("pause");
    return 0;
}