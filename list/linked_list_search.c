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
    
        //検索
    do{
        printf("検索する値を入力して下さい:");
        scanf("%d", &buf);
        if(buf!=0){
            for(thisnode=firstnode; thisnode != NULL; thisnode=thisnode->next ){
                if( thisnode->data == buf ){
                    printf("入力された値の中に %d が見つかりました。ノードを削除します。\n", buf);
                    if( thisnode->prev != NULL ){
                        thisnode->prev->next = thisnode->next;
                    }else{
                        //先頭ノードの再マーク
                        firstnode = thisnode->next;
                    }
                    if(thisnode->next != NULL ){
                        thisnode->next->prev = thisnode->prev;
                    }
                    free(thisnode);
                    break;
                }
            }
            if( thisnode == NULL ){
                printf("%d は入力されていないか既に削除されています。\n", buf);
            }
        }

    }while(buf != 0);
    
    //全ノードを削除
    thisnode = firstnode;
    while(thisnode != NULL){
        removenode = thisnode;
        thisnode = thisnode->next;
        free(removenode);
    }

    return EXIT_SUCCESS;
}
