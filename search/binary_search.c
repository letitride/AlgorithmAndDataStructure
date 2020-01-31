#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NOT_FOUND (-1)
#define N (10)
int sort[N];
int buffer[N];

/*
 * バイナリサーチ
 * ソート済み配列を2分探索して検索
 */
int binary_search(int x, int *a, int left, int right)
{
    int mid;
    while( left <= right ){
        mid = (left + right) / 2;
        if( a[mid] == x ){
            return mid;
        }
        //除外範囲の切り捨て
        if( a[mid] < x ){
            left = mid + 1;
        }else{
            right = mid -1;
        }
    }
    return NOT_FOUND;
}

//検索対象が重複する場合の最も左を返すパターン
int binary_search_most_left(int x, int *a, int left, int right)
{
    int mid;
    while( left <= right ){
        mid = (left + right) / 2;
        
        //除外範囲の切り捨て
        if( a[mid] < x ){
            left = mid + 1;
        }else{
            right = mid;
        }
        
        if( a[left] == x ){
            return left;
        }
    }
    return NOT_FOUND;
}

int binary_search_most_right(int x, int *a, int left, int right)
{
    int mid;
    while( left <= right ){
        mid = (left + right) / 2;
        
        //除外範囲の切り捨て
        if( a[mid] > x ){
            right = mid - 1;
        }else{
            left = mid;
        }
        
        if( a[right] == x ){
            return right;
        }
    }
    return NOT_FOUND;
}

int main(void)
{
    int i, r, array[N];
    srand( (unsigned int)time(NULL) );
    
    printf("array:\n");
    printf( "[0]:%d\n", array[0]=rand()%3 );
    for(i=1;i<N;i++){
        printf("[%d]:%d\n", i, array[i] = array[i-1]+rand()%3);
    }
    
    printf("何を探しますか？:\n");
    scanf("%d", &i);
    r = binary_search( i, array, 0, N-1 );
    if(r == NOT_FOUND){
        printf("%dは見つかりません:\n", i);
    }else{
        printf("%dは%d番目です:\n", i, r);
    }
    
    return EXIT_SUCCESS;
}
