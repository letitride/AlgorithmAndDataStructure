#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
int sort[N];

/*
 * バブルソート
 * 先頭から順に並び合う数字を比較
 * 先の数字が小さい時、入れ替えを行う
 * 末尾まで走査したらまた、先頭から比較を開始
 * 並び替えが行われなくなるまで繰り返す
 */
void BubbleSort(void){
    int i, j, flag;
    do{
        flag = 0;
        for(i=0;i<N-1;i++){
            if( sort[i] > sort[i+1] ){
                flag = 1;
                j = sort[i];
                sort[i] = sort[i+1];
                sort[i+1] = j;
            }
        }
    }while(flag==1);
}

int main(void){
    int i;
    srand( (unsigned int)time(NULL) );
    
    printf("ソート準備:\n");
    
    for(i=0;i<N;i++){
        sort[i] = rand();
        printf("%d\n", sort[i]);
    }
    
    printf("ソート開始:\n");
    BubbleSort();
    printf("ソート終了:\n");
    
    for(i=0;i<N;i++){
        printf("%d\n", sort[i]);
    }
    
    return EXIT_SUCCESS;
}
