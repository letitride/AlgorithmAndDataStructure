#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
int sort[N];
int buffer[N];
/**
 * マージソート
 * すべてのブロックを分割
 * 分割後、隣り合うブロック同士でソートしていく
 */
void MergeSort(int n, int x[])
{
    int i,j,k,m;
    
    if(n<=1){ return; }
    m = n/2;
    
    //ブロックの分割
    MergeSort(m, x);
    MergeSort(n-m, x+m); //配列のoffsetを操作
    
    //最小の隣り合うブロック(m個)の処理
    for(i=0;i<m;i++){
        buffer[i] = x[i];
    }
    j = m;
    i = k = 0;
    //iは前半, jは後半のindex
    while(i < m && j < n){
        if(buffer[i] <= x[j]){
            x[k++] = buffer[i++];
        }else{
            x[k++] = x[j++];
        }
    }
    //後半j側が残った場合はxの並びのままなのでi側が残った場合のみ処理する
    while(i<m){
        x[k++]=buffer[i++];
    }
    
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
    MergeSort(N, sort);
    printf("ソート終了:\n");
    
    for(i=0;i<N;i++){
        printf("%d\n", sort[i]);
    }
    
    return EXIT_SUCCESS;
}
