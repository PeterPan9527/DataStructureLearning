#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 101

//哈夫曼树结点的结构
typedef struct{
    int weight;
    int parent,lchild,rchild;
}HTNode,*HuffTree;

void Select(HTNode huffTree[],int k,int *i1,int *i2)
{
    int i,min,submin,temp;      //temp记录权值最小结点的权值
    for(i = 0; i < k; i++){
        if(huffTree[i].parent != -1) continue;
        temp = huffTree[i].weight;
        break;
    }  //选出一个没有用过的结点
    
    for(i = 0; i < k; i++){
        if(huffTree[i].parent != -1) continue;
        if(huffTree[i].weight <= temp){
            temp = huffTree[i].weight;
            min = i;                   //权值最小的结点的位置
        }
    }
    *i1 = min;
    temp = 100;  //置为一个大于所有权值的值
    for(i = 0; i < k; i++){
        if(huffTree[i].parent != -1 || i == min) continue;
        if(huffTree[i].weight < temp){
            temp = huffTree[i].weight;
            submin = i;                 //权值次最小的结点的位置
        }
    }
    *i2 = submin;

    printf("min index: %d  submin index: %d\n",*i1,*i2);   //输出
}

void HuffmanTree(HTNode huffTree[],int w[],int n)
{
    int i1,i2,k;
     for(int i=0; i<2*n-1; i++) {   //初始化所有结点的项目为-1
       huffTree[i].parent = -1;
       huffTree[i].lchild = -1;
       huffTree[i].rchild = -1;
    }

    for(int i = 0; i < n; i++){     //初始化前n个结点的权值
        huffTree[i].weight = w[i];
    }

    for(int k = n; k < 2*n - 1; k++){   //构建哈夫曼树
        Select(huffTree, k, &i1, &i2);//找到parent为-1的最小和次小的结点
        huffTree[k].weight = huffTree[i1].weight + huffTree[i2].weight;
        huffTree[i1].parent = k;
        huffTree[i2].parent = k;
        huffTree[k].lchild = i1;
        huffTree[k].lchild = i2;
    }

}

void HuffmanCoding(HTNode huffTree[],char **huffCode,int n)
{
    huffCode = (char**)malloc((n + 1)*sizeof(char *)); //分配n个字符编码的头指针向量
    char* temp;
    int start,pos,parent;
    temp = (char*)malloc(n*sizeof(char));    //定义工作空间，临时存储产生的哈夫曼编码
    temp[n-1] = '\0';
    for(int i = 0; i < n; i++){              //遍历哈夫曼数组，生成哈夫曼编码
        start = n - 1;                       //从叶子到根逆向求编码，后往前
        pos = i;                             //正在处理的当前位置
        parent = huffTree[i].parent;         //找到父结点
        while(parent != -1){
            if(huffTree[parent].lchild == pos)   //判断当前位置为左或右孩子
                temp[--start] = '0';
            else
                temp[--start] = '1';
            pos = parent;                     //当前位置移动到父节点
            parent = huffTree[parent].parent; //更新父节点
        }
        huffCode[i] = (char*)malloc((n - start)*sizeof(char));    //为第i个字符编码分配空间
        strcpy(huffCode[i],&temp[start]);
    }
    free(temp);                               //释放临时空间
}

int main()
{
    HTNode huffTree[MAX];
    int w[MAX];            //权值数组
    int n;                 //结点个数
    printf("Input the number of nodes:  ");
    scanf("%d",&n);
    printf("Input %d weight value:\n",n);
    for(int i = 0; i < n; i++){
        scanf("%d",&w[i]);
    }
    //构建哈夫曼树
    HuffmanTree(huffTree,w,n);
    //输出哈夫曼树 数组
    printf("weight parent lchild rchild\n");
    for(int i = 0; i < 2*n - 1; i++){
        printf("%-7d%-7d%-7d%-7d",huffTree[i].weight,huffTree[i].parent,huffTree[i].lchild,huffTree[i].rchild);
        printf("\n");
    }
    //求解和输出哈夫曼编码
    printf("\n");
    printf("huffcode:\n");
    char **huffCode;
    HuffmanCoding(huffTree,huffCode,n);
    for(int i = 0; i < n; i++){
        printf("%s\n",huffCode[i]);
    }

    system("pause");
    return 0;
}