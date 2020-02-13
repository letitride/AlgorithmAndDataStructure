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

char *GetDataFromMap(HASHTABLE *hashtable, char *key){
    unsigned int hashval, k;
    WORDSET *word;
    
    hashval = MakeHash(key, hashtable->size);
    for( k=0;k<=hashtable->size / 2;k++ ){
        word = hashtable->data[ (hashval + k*k) % hashtable->size ];
        if(word != NULL){
            if( strcmp(key, word->english) == 0){
                return word->japanese;
            }
        }
    }
    return NULL;
}

WORDSET *DeleteDataFromMap(HASHTABLE *hashtable, char *key){
    unsigned int hashval, k;
    WORDSET *word;
    
    hashval = MakeHash(key, hashtable->size);
    for( k=0;k<=hashtable->size / 2;k++ ){
        word = hashtable->data[ (hashval + k*k) % hashtable->size ];
        if(word != NULL){
            if( strcmp(key, word->english) == 0){
                hashtable->data[ (hashval + k*k) % hashtable->size ] = NULL;
                return word;
            }

        }
    }
    return NULL;
}

void InitHashTable(HASHTABLE *hashtable, unsigned int size){
    //hashtable->data は WORDSETの構造体
    hashtable->data = (WORDSET**)malloc( sizeof(WORDSET*) * size);
    memset( hashtable->data, NULL, sizeof(WORDSET*) * size );
    hashtable->size = size;
}

void CleanupHashTable(HASHTABLE *hashtable){
    free(hashtable->data);
    hashtable->size = 0;
}

void PrintAllData(HASHTABLE *hashtable){
    unsigned int n;
    for(n=0;n<hashtable->size;n++){
        if(hashtable->data[n] != NULL){
            printf( "%d:\t%s:\t%s\n", n, hashtable->data[n]->english, hashtable->data[n]->japanese);
        }
    }
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
        InitHashTable( &hashtable, 503 );
    for(n=0;n<5;n++){
        AddDataToMap( &hashtable, &words[n] );
    }
    
    do{
        printf("どの操作を行いますか？(1:検索 2:削除 3:全表示 0:終了)\n");
        scanf("%d", &n);
        switch(n){
            case 1:
            printf("検索する単語を入力してください:");
            scanf("%s", &key);
            japanese = GetDataFromMap(&hashtable, key);
            if(japanese != NULL){
                printf("%sの和訳は%sです\n", key, japanese);
            }
            else{
                printf("%sは見つかりませんでした\n", key);    
            }
            break;
            
            case 2:
            printf("削除する単語を入力してください:");
            scanf("%s", &key);
            wordfound = DeleteDataFromMap(&hashtable, key);
            if( wordfound != NULL ){
                printf("%sをマップから削除しました", key);
            }else{
                printf("%sは見つかりませんでした\n", key);    
            }
            break;
            
            case 3:
            PrintAllData(&hashtable);
            break;
        }
    }while(n!=0);
    
    CleanupHashTable(&hashtable); 
    return EXIT_SUCCESS;
}