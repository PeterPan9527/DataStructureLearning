//折半插入排序
#include<stdio.h>
#include<stdlib.h>
//对顺序表（数组）作折半插入排序

//时间复杂度与直接插入一样（只减少关键字比较次数，记录的移动次数不变），O(n^2) 
void BInsertSort(int r[],int n)   //n：要排序的元素数量
{
    int low,high,mid;
    for(int i = 2; i <= n; ++i){
        r[0] = r[i];
        low = 1;
        high = i - 1;
        while (low <= high)
        {
            mid = (low + high)/2;
            if(r[0] < r[mid]){                  //升序，低半区
                high = mid - 1;
            }
            else               //高半区
            {
                low = mid + 1;
            }
        }//while
        for(int j = i - 1; j >= high + 1; --j){  //记录后移
            r[j + 1] = r[j];
        }
        r[high + 1] = r[0];                      //插入
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
    BInsertSort(a,num);
    printf("after sorted:\n");
    Print(a,num);
    printf("\n");

    system("pause");
    return 0;
}