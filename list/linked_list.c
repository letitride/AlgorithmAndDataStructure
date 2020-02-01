#include <stdio.h>
#include <stdlib.h>

typedef struct tagListNode{
    struct tagListNode *prev; //前要素
    struct tagListNode *next; //次要素
    int data;
} ListNode;

/*
 * 連結リスト
 */
int main(void)
{
    int buf, sum;
    ListNode *firstnode, *lastnode, *newnode, *thisnode, *removenode;
    firstnode = lastnode = NULL;
    
    do{
        printf("整数を入力して下さい(0を入力すると終了):");
        scanf("%d", &buf);
        if(buf){
            newnode = (ListNode*)malloc( sizeof(ListNode) );
            newnode->data = buf;
            newnode->next = NULL;
            //push
            if(lastnode != NULL){
                lastnode->next = newnode;
                newnode->prev = lastnode;
                lastnode = newnode;
            }else{
                firstnode = lastnode = newnode;
                firstnode->prev = NULL;
            }
        }
        
    }while(buf!=0);
    
    printf("--入力されたのは以下の数です--\n");
    thisnode = firstnode;
    sum = 0;
    while( thisnode != NULL ){
        printf( "%d\t", thisnode->data );
        sum += thisnode->data;
        thisnode = thisnode->next;
    }
    printf( "\n--以上の数の合計値は %d です--\n", sum );
    
    //全ノードを削除
    thisnode = firstnode;
    while(thisnode != NULL){
        removenode = thisnode;
        thisnode = thisnode->next;
        free(removenode);
    }

    return EXIT_SUCCESS;
}
