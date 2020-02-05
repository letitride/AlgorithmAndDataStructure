#include <stdio.h>
#include <stdlib.h>

unsigned long power[10] = {0};
int number_using[10] = {0,0,0,0,0,0,0,0,0,0};

//与えられたnumbrerの各桁の数字にdigitがいくつ存在するか？
int number_of_digit(unsigned long number, unsigned long digit){
  int ret = 0;
  if( number == 0 ){
    return 0;
  }
  //1の桁から数える
  if( number % 10 == digit ){
    ret = 1;
  }
  ret += number_of_digit( number / 10, digit );
  return ret;
}

void check_number(void){
    int i;
    unsigned long result = 0;
    for(i=1;i<9;i++){
        //開き直り数検証値 各桁の数値の冪乗も総和 予め1-9の冪乗表を作成しておき、出現数と掛け算する
        result += power[i] * number_using[i];
    }

    for(i=1;i<=9;i++){
        //冪乗の合計値の各桁の数の出現数と計算元になった出現数表の数が一致するか？
        //一致すれば開き直り数
        if( number_of_digit( result, i ) != number_using[i] ){
            return;
        }
    }
    printf("%lu \n", result);
    return;
}

//10桁の各桁数字の出現頻度表を作成する
void make_numbers(int start, int count){
  int i, j;
  if( count > 10){
    return;
  }
  for(i=start; i<=9; i++){
    number_using[i]++;
    //countは実行ごとに初期化されないので"深さ優先"の探索
    make_numbers( i, count+1 );

    number_using[i]--;
  }
}

int main(void){

  int i, j, k;
  for(i=1;i<=9;i++){
    k = 1;
    for(j=0;j<i;j++){
      k *= i;
    }
    power[i] = k;
  }
  make_numbers(1,1)

  return EXIT_SUCCESS;
}