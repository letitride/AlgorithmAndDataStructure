#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
int sort[N];

/*
 * クイックソート
 * 先頭の値を基準とし、小大で振り分け配置を行う
 * 振り分け後の小大各先頭値を再び基準としグループが1となるまで繰り返し振り分けを行う
 * int bottom 先頭のindex
 * int top 末尾のindex
 * int *data 並び替え対象の配列
 */
void QuickSort(int bottom, int top, int *data){
    int lower, upper, div, temp;
    if( bottom>=top ){
        return;
    }
    //今回振り分けの基準値
    div = data[bottom];
    for(lower=bottom,upper=top;lower<upper;){
        //基準値divが大きい場合、中央位置を右にシフト
        while( lower <= upper && data[lower] <= div ){
            lower++;
        }
        //基準値divが大きい場合、中央位置を左にシフト
        while( lower <= upper && data[upper] > div ){
            upper--;
        }
        //中央位置が重なり合わない場合、並びの不整合なので左右を入れ替える
        if( lower < upper ){
            temp = data[lower];
            data[lower] = data[upper];
            data[upper] = temp;
        }
    }
    //基準値を中央へ
    temp = data[bottom];
    data[bottom] = data[upper];
    data[upper] = temp;
    //基準値から左のソート
    QuickSort( bottom, upper-1, data );
    //基準値から右のソート
    QuickSort( upper+1, top, data );
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
    QuickSort(0, N-1, sort);
    printf("ソート終了:\n");
    
    for(i=0;i<N;i++){
        printf("%d\n", sort[i]);
    }
    
    return EXIT_SUCCESS;
}
