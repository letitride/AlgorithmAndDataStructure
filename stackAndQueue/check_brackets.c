#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//カッコの種類
#define STAPLE_SMALL 1
#define STAPLE_MEDIUM 2
#define STAPLE_LARGE 3

typedef struct _tagstaple{
    int line;   //カッコのある行
    int column; //カッコのある列
    int type;   //カッコの種類
    
    struct _tagstaple *staple_next;
    struct _tagstaple *staple_prev;
} staple;

staple *staple_head = NULL;
staple *staple_last = NULL;

void stack_push( int, int, int );
int stack_pop( staple *ret );


int main(void){
    char buffer[4096];
    int i, len, line=1, carryover=0;
    staple open;
    
    for(;;){
        if(fgets(buffer, 4096, stdin) == NULL){
            break;
        }
        len = strlen(buffer);
        if(len == 0){ continue; }
        
        for(i=0;i<len;i++){
            switch( buffer[i] ){
                case '(' :
                    stack_push(line, carryover+i+1, STAPLE_SMALL);
                break;
                case '{' :
                    stack_push(line, carryover+i+1, STAPLE_MEDIUM);
                break;
                case '[' :
                    stack_push(line, carryover+i+1, STAPLE_LARGE);
                break;
                case ')' :
                    if( stack_pop( &open ) == 0 ){
                        printf( "カッコの対応がとれていません\n" );
                        printf( "%d行%d文字に対応する'('がありません", line, carryover+i+1 );
                        return EXIT_FAILURE;
                    }
                    if( open.type != STAPLE_SMALL ){
                        printf( "カッコの対応がとれていません\n" );
                        printf( "%d行%d文字に対応するカッコと%d行%d文字に対応するカッコが違います", open.line, open.column, line, carryover+i+1 );
                        return EXIT_FAILURE;
                    }
                break;
                case '}' :
                    if( stack_pop( &open ) == 0 ){
                        printf( "カッコの対応がとれていません\n" );
                        printf( "%d行%d文字に対応する'{'がありません", line, carryover+i+1 );
                        return EXIT_FAILURE;
                    }
                    if( open.type != STAPLE_MEDIUM ){
                        printf( "カッコの対応がとれていません\n" );
                        printf( "%d行%d文字に対応するカッコと%d行%d文字に対応するカッコが違います", open.line, open.column, line, carryover+i+1 );
                        return EXIT_FAILURE;
                    }
                break;
                case ']' :
                    if( stack_pop( &open ) == 0 ){
                        printf( "カッコの対応がとれていません\n" );
                        printf( "%d行%d文字に対応する'['がありません", line, carryover+i+1 );
                        return EXIT_FAILURE;
                    }
                    if( open.type != STAPLE_MEDIUM ){
                        printf( "カッコの対応がとれていません\n" );
                        printf( "%d行%d文字に対応するカッコと%d行%d文字に対応するカッコが違います", open.line, open.column, line, carryover+i+1 );
                        return EXIT_FAILURE;
                    }
                break;
            }
        }
        if( buffer[len -1] == '\n' ){
            carryover = 0;
            line++;
        }else{
            carryover += len;
        }
    }
    
    if( staple_head != NULL ){
        printf("カッコの数が合っていません");
        return EXIT_FAILURE;
    }
    
    printf("カッコの数は正しいです");
    return EXIT_SUCCESS;
}

void stack_push( int line, int column, int type ){
    staple *staple_new;
    staple_new = (staple*)malloc( sizeof(staple) );
    if( staple_new == NULL ){
        printf("メモリが足りません");
        exit( EXIT_FAILURE );
        return;
    }
    staple_new->line = line;
    staple_new->column = column;
    staple_new->type = type;
    
    staple_new->staple_next = NULL;
    staple_new->staple_prev = staple_last;
    staple_last = staple_new;
    if(staple_head == NULL){
        staple_head = staple_new;
    }
}

int stack_pop(staple *ret){

    staple *temp_staple;
    //スタックなし
    if( staple_head ==  NULL ){
        return 0;        
    }
    
    ret->line = staple_last->line;
    ret->column = staple_last->column;
    ret->type = staple_last->type;
    ret->staple_next = ret->staple_prev = NULL;
    temp_staple = staple_last;
    
    //スタックの削除
    if(staple_last->staple_prev == NULL){
        //先頭のスタックだった場合の処理
        staple_head = NULL;
    }else{
        staple_last->staple_prev->staple_next = NULL;
    }
    //最後のスタックアドレスを変更
    staple_last = staple_last->staple_prev;
    //popしたスタックの削除
    free(temp_staple);
    return 1;
}