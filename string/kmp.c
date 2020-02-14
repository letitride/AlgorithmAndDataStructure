#include <stdio.h>
#include <stdlib.h>

#define PATTERN_LENGTH 13
unsigned char original_text[] = "a eighty-eighty-eighth key";
unsigned char original_pattern[PATTERN_LENGTH+1] = "eighty-eighth";

#define _SHOW_WORKING_

unsigned char *kmp_search(unsigned char *text, unsigned char *pattern)
{
  int table[PATTERN_LENGTH+1] = {0, 0};
  int text_index = 1;
  int pattern_index = 0;
  int i = 0, j;

  //予め検索文字列のtableを作成 例えば10文字目で不一致の場合、3文字目まではスキップしてチェックできる
  //この位置で間違った場合、何文字前までは正しいか？のテーブル
  while( pattern[text_index] != '\0' ){
    //先頭の文字順から等しい文字順が文中にあるか？
    if( pattern[text_index] == pattern[pattern_index] ){
      table[++text_index] = ++pattern_index;
    }
    else if(pattern_index == 0){
      table[++text_index] = 0;
    }
    else{
      pattern_index = table[pattern_index];
    }
  }

  for(i=0;i<14;i++){
    printf("[%d]: %d \n", i, table[i]);
  }
 
  i=0;
  while( *text != '\0')
  {
#ifdef _SHOW_WORKING_
    printf("本文:%s \nパターン:", original_text);
    for( j=0;j<text - original_text;j++ ){ printf(" "); }
    printf( "%c \n", pattern[i] );
#endif

    if( *text == pattern[i]){
        ++text;
        //パターン終端まで一致 (文字が一致すればカーソルを進める)
        if(pattern[++i] == '\0'){
            return text - PATTERN_LENGTH;
        }
    }
    else if(i==0){
        text++;
    }
    else{
        //先頭順と並びが一致してる前文字列の場合
        //テーブルの位置までスキップできる
        i=table[i];
    }
  }
  return NULL;
}

int main(void)
{
  unsigned char *result;
  result = kmp_search(original_text, original_pattern);
  if( result != NULL ){
      printf("%sは見つかりました", original_pattern);
  }
  return EXIT_SUCCESS;
}