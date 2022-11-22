//
//  main.cpp
//  树
//
//  Created by 张童义森 on 2021/9/15.
//

#include<stdlib.h>
#include<stdio.h>

typedef struct bitnode{
    int data;
    struct bitnode *lchild,*rchild;
}*bitree;
void exc(bitree t){
    if(t->lchild!=NULL)
        exc(t->lchild);
    if(t->rchild!=NULL)
        exc(t->rchild);
    bitree p;
    p=t->lchild;
    t->lchild=t->rchild;
    t->rchild=p;
    
}
int PreOrderTraverse(bitree T) {
    if (T == NULL) {
        return 1;
    }
    else {
        printf("%c", T->data);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
        
    }
    return 0;
}
void CreatBiNode(bitree &Node)//此处应注意传递的参数（二重指针）
{
    char data;
    scanf("%c", &data);
    Node = (bitree)malloc(sizeof(bitnode));
    if (data == '#')
    {
        Node = NULL;
    }

    else if ((data != '#') && (Node))
    {
        (Node)->data = data;
        (Node)->lchild = NULL;
        (Node)->rchild = NULL;
        CreatBiNode(Node->lchild);
        CreatBiNode(Node->rchild);
    }
    //PreOrderTraverse(Node);
}
int height(bitree &t){
    if(t==NULL){
        return 0;
    }
    int m=height(t->lchild);
    int n=height(t->rchild);
    return (m>n)?(m+1):(n+1);
}
void preandlevel(bitree &t,int i){
    if(t!=NULL){
        printf("data=%c,level=%d,",t->data,i);
        i++;
        preandlevel(t->lchild,i);
        preandlevel(t->rchild,i);
    }
}
int main(){
    bitree t;
    CreatBiNode(t);
    preandlevel(t,1);
    printf("\n");
    exc(t);
    PreOrderTraverse(t);
    int i=height(t);
    printf("\n%d\n",i);
    preandlevel(t,1);
}
