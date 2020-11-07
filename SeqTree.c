#include<stdio.h>
#include<math.h>
#include<conio.h>
#define MAX_SIZE 1024

//定义顺序数组的类型
typedef char SeqTree[MAX_SIZE];

//初始化空二叉树
void Init_SeqTree(SeqTree tree)
{
    //字符数组所有元素初始化赋值
    for(int i=0;i<MAX_SIZE;i++){
        tree[i] = '\0';
    }
}

//创建完全二叉树，递归，先序
void Creat_SeqTree(SeqTree tree,int i)  //i为数组下标
{
    char ch;
    ch = getchar();
    fflush(stdin);  //清空键盘缓存区
    if(ch == '^'){
        tree[i] = '\0';
        return;
    }
    tree[i] = ch;
    //输入左子树（当结点坐标为i，其左子树坐标为2*i+1 ，其右子树坐标为2*(i+1)
    printf("Input left child:\n");
    Creat_SeqTree(tree,2*i+1);
    //输入右子树
    printf("Input right child:\n");
    Creat_SeqTree(tree,2*(i+1));
}

//输出完全二叉树
void Print_SeqTree(SeqTree tree)
{
    for(int i = 0; tree[i] != '\0'; i++){
        printf("%c ",tree[i]);
    }
}

//获取树的根结点
char Get_SeqTreeRoot(SeqTree tree)
{
    return tree[0];
}

//获取结点总数
int Get_SeqTreeLength(SeqTree tree)
{
    int len;
    for(int i = 0; i < MAX_SIZE; i++){
        if(tree[i] == '\0'){
            continue;
        }
        len++;
    }
    return len;
}

//获取二叉树深度, 深度为k的二叉树最多有 2*k-1 个结点
int Get_SeqTreeDepth(SeqTree tree)
{
    int len = Get_SeqTreeLength(tree);
    int k = 0;
    while((int)pow(2,k) - 1 < len){
        k++;
    }
    return k;
}

int main()
{
    SeqTree tree;
    Init_SeqTree(tree);
    printf("Input root:\n");
    Creat_SeqTree(tree,0);
    Print_SeqTree(tree);
    printf("\n");
    printf("Tree depth:%d\n",Get_SeqTreeDepth(tree));
    printf("Tree length:%d\n",Get_SeqTreeLength(tree));
    system("pause");
    return 0;
}