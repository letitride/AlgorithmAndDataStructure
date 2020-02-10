#include <stdio.h>
#include <stdlib.h>

unsigned int MakeHash(char *str, unsigned int hashmax){
    unsigned int n, length, hash, weight;
    hash = 0;
    length = strlen(str);
    for(n=weight=0;n<length;n++,weight++){
        if(weight>7){
            weight = 0;
        }
        //文字の出現順で重みをつける (2*2*2*2*weight)
        hash += (int)str[n] << (4*weight);
    }
    return hash % hashmax;
}

unsigned int ReHash(HASHTABLE *hashtable, unsigned int firsthash){
    unsigned int hashval, k;
    
    for(k=1;k<=hashtable->size/2;k++){
        //再ハッシュ値は元の数にloop^2を足す
        hashval = (firsthash+k*k) % hashtable->size;
        //新しいハッシュがハッシュ表で衝突がなければ値を返す
        if( hashtable->data[hashval] == NULL ){
            return hashval;
        }
    }
    return -1;
}

int main(void){
    //ハッシュサイズは大きい素数が良い
    printf("%d", MakeHash("abcd", 10007));
    return EXIT_SUCCESS;
}