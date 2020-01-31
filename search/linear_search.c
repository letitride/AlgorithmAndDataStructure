#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND (-1)
#define N (10)
int sort[N];
int buffer[N];

/*
 * リニアサーチ
 * 先頭から順に確認していく
 */
int linear_search(int x, int *a, int num)
{
    int n = 0;
    int t;
    //配列末尾を検索文字に入れ替え(loop終端を設定)
    t=a[num-1];
    a[num-1] = x;
    

    while( a[n] != x){
        n++;
    }
    
    a[num-1] = t;
    if(n < num-1){ return n; }
    if(x == t){ return t;}
    
    return NOT_FOUND;
}

int main(void)
{
    int i, r, array[N];
    srand( (unsigned int)time(NULL) );
    
    printf("array:\n");
    
    for(i=0;i<N;i++){
        printf("[%d]:%d\n", i, array[i] = rand()%20);
    }
    
    printf("何を探しますか？:\n");
    scanf("%d", &i);
    
    r = linear_search( i, array, N );
    if(r == NOT_FOUND){
        printf("%dは見つかりません:\n", i);
    }else{
        printf("%dは%d番目です:\n", i, r);
    }
    
    return EXIT_SUCCESS;
}
