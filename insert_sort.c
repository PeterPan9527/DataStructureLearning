#include<stdio.h>
#include<stdlib.h>

void insertSort(int r[],int n)
{
    int i,j;     
    for(int i = 2; i <= n; ++i){      //r[0]是哨兵,暂存r[i]，用以比较
        j = i - 1;
        r[0] = r[i];
        while (r[0] < r[j])
        {
            r[j + 1] = r[j];
            j--;
        }
        r[j + 1] = r[0];
    }
}

void Print(int r[],int n)
{
    for(int i = 1; i <= n; ++i){
        printf("%d ",r[i]);
    }
}

int main()
{
    int a[10];
    int num;
    printf("num(<=10):\n");
    scanf("%d",&num);
    getchar();
    for(int i = 1; i <= num; ++i){
        scanf("%d",&a[i]);
        getchar();
    }
    printf("before:\n");
    Print(a,num);
    printf("\n");
    insertSort(a,num);
    printf("after sorted:\n");
    Print(a,num);
    printf("\n");

    system("pause");
    return 0;
}