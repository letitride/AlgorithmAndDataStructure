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

int main(void){
  tree_node *node;

  insert_tree(5, tree_root);
  insert_tree(3, tree_root);
  insert_tree(1, tree_root);
  insert_tree(4, tree_root);
  insert_tree(8, tree_root);

  printf("root: %d \n", tree_root->value  );
  printf("root->left: %d \n", tree_root->left->value  );
  printf("root->left->left: %d \n", tree_root->left->left->value  );
  printf("root->left->right: %d \n", tree_root->left->right->value  );
  printf("root->right: %d \n", tree_root->right->value  );

  node = find_value( tree_root, 4);
  printf("find hit : %d \n", node->value);

  return EXIT_SUCCESS;
}