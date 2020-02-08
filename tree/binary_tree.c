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

int main(void){
  tree_node *node;

  insert_tree(10, tree_root);
  insert_tree(9, tree_root);
  insert_tree(7, tree_root);
  insert_tree(4, tree_root);
  insert_tree(8, tree_root);
  insert_tree(1, tree_root);
  insert_tree(2, tree_root);
  insert_tree(5, tree_root);

  printf("root->left->left: %d \n", tree_root->left->left->value  );
  delete_tree( 7 );
  printf("root->left->left: %d \n", tree_root->left->left->value  );
  printf("root->left->left->right: %d \n", tree_root->left->left->right->value  );
  printf("root->left->left->left: %d \n", tree_root->left->left->left->value  );

  return EXIT_SUCCESS;
}