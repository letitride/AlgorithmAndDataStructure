#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int main(void)
{
    int buf, sum, count, i, size;
    int *array, *temp;
    
    size = 3;
    array = (int*)malloc( sizeof(int) * size );
    
    count=0;
    do{
        printf("整数を入力して下さい(0を入力すると終了):");
        scanf("%d", &buf);
        if( buf ){
            array[count] = buf;
            count++;
            
            //配列サイズの拡張
            if( count == size ){
                temp = (int*)malloc( sizeof(int) * count * 2 ); //現在のサイズより2倍に拡張
                memcpy( temp, array, sizeof(int)*count );
                free(array);
                array=temp;
                size *= 2;
            }
        }
    }while(buf!=0);

    printf("--入力されたのは以下の数です--\n");
    sum = 0;
    for(i=0; i<count; i++){
        printf( "%d\t", array[i] );
        sum += array[i];
    }
    printf("\n--\n以上の合計値は %d です\n", sum);
    
    free(array);

    
    return EXIT_SUCCESS;
}
