#include <stdio.h>
#include <stdlib.h>

int num_of_one( unsigned long value ){
    int ret = 0;
    if( value == 0 ){
        return 0;
    }
    if( value % 10 == 1){
        ret = 1;
    }
    return ret + num_of_one( value / 10 );
}


int main(void){
    printf("%d\n", num_of_one(321));
    printf("%d\n", num_of_one(1223121));
    return EXIT_SUCCESS;
}