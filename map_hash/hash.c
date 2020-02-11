#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//単語セット
typedef struct{
    char *english;
    char *japanese;
} WORDSET;

//ハッシュ表
typedef struct{
    WORDSET **data;
    unsigned int size;
} HASHTABLE;

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
        //再ハッシュ値は元の数にloop倍率を掛け合わせる
        hashval = (firsthash+k*k) % hashtable->size;
        //ハッシュ表に衝突がなければ値を返す
        if( hashtable->data[hashval] == NULL ){
            return hashval;
        }
    }
    return -1;
}

void AddDataToMap(HASHTABLE *hashtable, WORDSET *newdata){
    unsigned int hashval;
    hashval = MakeHash(newdata->english, hashtable->size);
    if( hashtable->data[hashval] != NULL ){
        hashval = ReHash(hashtable, hashval);
        if( hashval == -1 ){
            printf("%sをマップに挿入しようとしましたが空き位置がありませんでした\n", newdata->english);
            return;
        }
    }
    hashtable->data[hashval] = newdata;
}

int main(void){
    unsigned int n;
    char key[64], *japanese;
    HASHTABLE hashtable;
    WORDSET *wordfound;
    WORDSET words[5] = {
        {"dolphin", "イルカ"},{"beluga","シロイルカ"},{"prampus","シャチ"},
        {"medusa", "海月"}, {"otter", "カワウソ"}
    };
    return EXIT_SUCCESS;
}