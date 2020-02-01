#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int buf, sum, count, n, i;
    int *array;
    
    printf("何個の数値を入力しますか:");
    scanf("%d", &count);
    //入力値count分メモリを確保 int array[count]として扱える
    array = (int*)malloc( sizeof(int) * count );
    
    n=0;
    do{
        printf("整数を入力して下さい(0を入力すると終了):");
        scanf("%d", &buf);
        if( buf ){
            array[n] = buf;
            n++;
        }

    }while(buf!=0);

    printf("--入力されたのは以下の数です--\n");
    sum = 0;
    for(i=0; i<n; i++){
        printf( "%d\t", array[i] );
        sum += array[i];
    }
    printf("\n--\n以上の合計値は %d です\n", sum);
    
    free(array);

    
    return EXIT_SUCCESS;
}
