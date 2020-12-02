//数据结构编程题1       PTA
//最大子列和问题
/*
给定K个整数组成的序列{ N1, N2, ..., NK}，“连续子列”被定义为{ N​i, Ni+1, ..., Nj}，其中 1≤i≤j≤K。
“最大子列和”则被定义为所有连续子列元素的和中最大者。例如给定序列{ -2, 11, -4, 13, -5, -2 }，
其连续子列{ 11, -4, 13 }有最大的和20。现要求你编写程序，计算给定整数序列的最大子列和。

本题旨在测试各种不同的算法在各种数据情况下的表现。各组测试数据特点如下：

数据1：与样例等价，测试基本正确性；
数据2：10^2个随机整数；
数据3：10^3个随机整数；
数据4：10^4个随机整数；
数据5：10^5个随机整数；

输入格式:
输入第1行给出正整数K (≤100000)；第2行给出K个整数，其间以空格分隔。

输出格式:
在一行中输出最大子列和。如果序列中所有整数皆为负数，则输出0。

输入样例:
6
-2 11 -4 13 -5 -2
输出样例:
20
*/
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100001
int a[MAXSIZE];

int MaxSubSum(int r[],int N)
{
    int thisSum,maxSum;
    for(int i = 0; i < N; ++i){
        thisSum += r[i];       //向右累加
        if(thisSum > maxSum){
            maxSum = thisSum;  //发现最大和则替换保存
        }
        else if(thisSum < 0){
            thisSum = 0;       //若当前子列和小于0，则不可能使后面增大，舍去
        }
    }
    return maxSum;
}

int main()
{
    int K;
    scanf("%d",&K);
    getchar();
    for(int i = 0; i < K; ++i){
        scanf("%d",&a[i]);
        getchar();
    }
    printf("%d\n",MaxSubSum(a,K));

    system("pause");
    return 0;
}