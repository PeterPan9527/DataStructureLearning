#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 1001

int Ancestor(int i,int j)
{
    while(1){
        if(i>j){
            i/=2;
        }
        else{
            j/=2;
        }
        if(i==j) break;
    }
    return i;
}

int main()
{
    int BT[MAXSIZE];
    int n,i,j;
    int Node=0;
    scanf("%d",&n);
    for(int k=0;k<n;k++){
        scanf("%d",&BT[k]);
    }
    scanf("%d%d",&i,&j);

    Node=Ancestor(i,j);

    if(i==j){
        printf("%d %d\n",i,j);
    }
    else if(BT[i-1]==0){
        printf("ERROR: T[%d] is NULL\n",i);
    }
    else if(BT[j-1]==0){
        printf("ERROR: T[%d] is NULL\n",j);
    }
    else{
        printf("%d %d\n",Node,BT[Node-1]);
    }
    
    system("pause");
    return 0;
}