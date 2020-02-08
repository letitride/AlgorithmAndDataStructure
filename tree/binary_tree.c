#include <stdio.h>
#include <stdlib.h>

typedef struct _tag_tree_node {
  int value;
  struct _tag_tree_node *left;
  struct _tag_tree_node *right;
} tree_node;

tree_node *tree_root = NULL;

tree_node* create_new_node(int num){
  tree_node *tree_new;
  tree_new = (tree_node*)malloc( sizeof(tree_node) );
  if( tree_new == NULL ){
      exit(EXIT_FAILURE);
  }
  tree_new->left = NULL;
  tree_new->right = NULL;
  tree_new->value = num;
  return tree_new;
}

void insert_tree(int num, tree_node *node){
  if( node == NULL ){
    tree_root = create_new_node(num);
    return;
  }
  if( node->value > num ){
    if( node->left != NULL ){
      insert_tree( num, node->left );
    }
    else{
      node->left = create_new_node(num);
    }
  }
  else{
    if( node->right != NULL ){
      insert_tree( num, node->right );
    }
    else{
      node->right = create_new_node(num);
    }
  }
  return;
}

tree_node* find_value(tree_node *node, int val){
    if(node->value > val){
        if( node->left == NULL ){
            return NULL;
        }
        return find_value(node->left, val);
    }
    
    if(node->value < val){
        if( node->right == NULL ){
            return NULL;
        }
        return find_value(node->right, val);
    }
    return node;
}

int delete_tree(int val){
    tree_node *node, *parent_node;
    tree_node *left_biggest;
    int direction = 0;
    node = tree_root;
    parent_node = NULL;
    
    while(node!=NULL && node->value!=val){
        if( node->value > val ){
            parent_node = node;
            node = node->left;
            direction = -1;
        }else{
            parent_node = node;
            node = node->right;
            direction = 1;          
        }
    }
    if( node == NULL ){
        return 0;
    }
    if( node->left == NULL || node->right == NULL ){
        if( node->left == NULL ){
            //親から見て削除nodeは左にある
            if( direction == -1 ){
                parent_node->left = node->right;
            }
             if( direction == 1 ){
                parent_node->right = node->right;
            }
            if( direction == 0 ){
               tree_root = node->right;
            }
        }
        else{
            if( direction == -1 ){
                parent_node->left = node->left;
            } 
            if( direction == 1 ){
                parent_node->right = node->left;
            }
            if( direction == 0 ){
               tree_root = node->left;
            }
        }
        free(node);
    }else{
        //削除対象に左右両方に子孫がある場合はleft側の最大値を持つ要素と入れ替える
        left_biggest = node->left;
        parent_node = node;
        direction = -1;
        while( left_biggest->right != NULL ){
            parent_node = left_biggest;
            left_biggest = left_biggest->right;
            direction = 1;
        }
        
        node->value = left_biggest->value;
        //削除対象の左子ノードが最大値
        if( direction == -1 ){
            parent_node->left = left_biggest->left;
        }
        //最大値の孫以降の要素がある
        else{
            parent_node->right = left_biggest->right;
        }
        //入れ替えた子孫要素の削除
        free( left_biggest );
    }
    return 1;
}


void print_tree(int depth, tree_node *node){
    int i;
    if( node == NULL ){
        return;
    }
    print_tree(depth+1, node->left);
    for( i=0;i<depth;i++ ){
        printf("  ");
    }
    printf("%d\n", node->value);
    print_tree(depth+1, node->right);
}

void free_tree(tree_node *node){
    if(node == NULL){
        return;
    }
    free_tree(node->left);
    free_tree(node->right);
    free(node);
}

int main(void){
  int i, action;
  for(i=0;i<10;i++){
      insert_tree( rand() % 99+1, tree_root );
  }
  for(;;){
      print_tree( 0, tree_root );
      printf( "実行する操作のタイプを入力してください:\n 1:追加 2:検索 3:削除 それ以外:終了" );
      scanf("%d", &action);
      switch(action){
          case 1:
          printf("1〜100の範囲で追加する数字を入力してください:");
          scanf("%d", &i);
          if(i<1 || i>100){
              continue;
          }
          insert_tree(i, tree_root);
          break;
          
          case 2:
          printf("検索する数字を入力してください:");
          scanf("%d", &i);
          if(find_value(tree_root, i) != NULL){
              printf("%dを発見しました\n", i);
          }else{
              printf("%dは見つかりませんでした\n", i);
          }
          break;
          
          case 3:
          printf("削除する数字を入力してください:");
          scanf("%d", &i);
          if( delete_tree(i) == 1 ){
              printf("%dを削除しました\n", i);
          }else{
              printf("%dは見つかりませんでした\n", i);
          }
          break;
          
          default:
          free_tree(tree_root);
          return EXIT_SUCCESS;
      }
  }
}