#include <stdio.h>
#include <stdlib.h>

#define MAX 6
int N[MAX] = {98, 140, 84, 28, 42, 126};

int gcd(int a, int b){
    int i;
    for(i=a;i>0;i--){
        if(a % i == 0 && b % i == 0){
            break;
        }
    }
    return i;
}

int multi_gcd(int n){
    if( n == 1 ){
        return gcd( N[0], N[1] );
    }
    return gcd( N[n], multi_gcd(n-1) );
}

int main(void){
    printf( "%d", multi_gcd(MAX-1));
    return EXIT_SUCCESS;
}