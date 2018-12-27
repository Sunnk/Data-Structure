#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include "def.h"
#include "queue.h"
#include "stack.h"

typedef struct BinaryTreeNode BTNode;
struct BinaryTreeNode{
    void *data;
    BTNode *left_child;
    BTNode *right_child;
    BTNode *parent;
};

void btree_traverse_preorder(BTNode *root, VisitFunc visit_func, void *user_data);
void btree_traverse_inorder(BTNode *root, VisitFunc visit_func, void *user_data);
void btree_traverse_postorder(BTNode *root, VisitFunc visit_func, void *user_data);
void btree_traverse_levelorder(BTNode *root, VisitFunc visit_func, void *user_data);
uint32_t btree_count_height(BTNode *root);
uint32_t btree_count_node(BTNode *root);
uint32_t btree_count_leafnode(BTNode *root);

BTNode* cbtree_build(BTNode* root, void *arr[], uint32_t arr_size, uint32_t arr_index);
void btree_show(BTNode *root, uint32_t unit_level_spacing, uint32_t unit_column_spacing, VisitFunc visit_func, void *user_data);

#endif // _BINARYTREE_H_


