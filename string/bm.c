#include <stdio.h>
#include <stdlib.h>

#define PATTERN_LENGTH 4
unsigned char original_text[] = "On a dark desert highway, "
                                "cool wind in my hair, ";
unsigned char original_pattern[PATTERN_LENGTH+1] = "wind";
#define _SHOW_WORKING_

unsigned char *bm_search(unsigned char *text, unsigned char *pattern)
{
  int table[256];
  int text_index, pattern_index, text_len, i;

  for(i=0; i<256; i++){
    //不一致時のデフォルトの移動距離
    table[i] = PATTERN_LENGTH;
  }

  for(i=0; i<PATTERN_LENGTH-1;i++){
    //不一致時にパターンに含まれている場合の移動距離(不一致文字がnだった場合,1つずらす)
    //int型なのでcharのASCIIがindexに入る
    table[ pattern[i] ] = PATTERN_LENGTH-i-1;
  }

  //検索文書の長さ
  for(text_len=0;text[text_len]!='\0';text_len++);

  text_index = PATTERN_LENGTH -1;
  while( text_index < text_len ){
#ifdef _SHOW_WORKING_
    printf("%s\n", text);
    for(i=0;i<text_index-PATTERN_LENGTH+1;++i){
        printf(" ");
    }
    printf("%s\n", pattern);
#endif

    pattern_index = PATTERN_LENGTH -1;
    while( text[text_index] == pattern[pattern_index] ){
      //パターン文字すべてに一致した
      if(pattern_index==0){
        return text + text_index;
      }
      --text_index;
      --pattern_index;
    }

    //text_indexが減った分以上は増やさないと無限ループになる
    if(table[ text[text_index] ] > PATTERN_LENGTH-pattern_index){
      printf("match move %d \n", table[text[text_index]]);
      text_index += table[text[text_index]];
    //推奨移動距離よりマッチした量が多い場合、マッチした量分移動
    }else{
      text_index += PATTERN_LENGTH - pattern_index;
    }
  }
  return NULL;
}

int main(void){
  unsigned char *result;
  result = bm_search( original_text, original_pattern );
  if(result != NULL ){
    printf("見つかりました");
  }
  return EXIT_SUCCESS;
}