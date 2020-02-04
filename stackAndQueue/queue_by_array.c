#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MAX (5+1)
#define QUEUE_EMPTY -1

int queue[QUEUE_MAX];
int queue_first = 0; //queue先頭index
int queue_last  = 0; //ラストindex

void enqueue( int val ){
    if( (queue_last + 1) % QUEUE_MAX == queue_first ){
        printf("ジョブが満杯です\n");
    }
    else{
        queue[queue_last] = val;
        //lastカーソルの移動 バッファを超える場合は先頭に
        queue_last = (queue_last + 1) % QUEUE_MAX;
    }
}

int dequeue(void){
    int ret;
    if( queue_first == queue_last ){
        printf("ジョブがありません\n");
        return QUEUE_EMPTY;
    }
    ret = queue[queue_first];
    //firstカーソルの移動
    queue_first = (queue_first + 1) % QUEUE_MAX;
    return ret;
}

int main(void){
    enqueue(2);
    enqueue(5);
    printf("%d", dequeue());
    printf("%d", dequeue());
    enqueue(5);
    enqueue(5);
    enqueue(5);
    enqueue(5);
    enqueue(10);
    enqueue(1);
    dequeue();
    dequeue();
    dequeue();
    dequeue();
    printf("%d", dequeue());
    dequeue();

    return EXIT_SUCCESS;
}