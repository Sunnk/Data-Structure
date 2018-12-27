#include "binarytree.h"

/** \brief This function visit each node of the binary tree in a preorder traversal
 *          1.visit the node; 2.traverse the left subtree; 3.traverse the right subtree
 *
 * \param root: pointer to the root node of the binary tree
 * \param visit_func: pointer to the function to call for each node visited
 * \param user_data: user data to pass to the function
 * \return none
 *
 */
//前序遍历二叉树，遍历过程中，调用访问函数visit_func访问节点内部数据元素。
//参数user_data作为访问函数visit_func的传入参数，可以携带内容，丰富访问操作。若弃用，则传入NULL。
void btree_traverse_preorder(BTNode *root, VisitFunc visit_func, void *user_data)
{
#ifdef USING_RECURSION
    if(root == NULL) return;
    if(visit_func){
        visit_func(root, user_data);
    }
    btree_traverse_preorder(root->left_child, visit_func, user_data);
    btree_traverse_preorder(root->right_child, visit_func, user_data);
#else
    BTNode *current_node;
    Stack *stack;

    if(root == NULL) return;
    stack = stack_create();
    stack_push(stack, root);
    while(stack_pop(stack, (void **)&current_node) == RET_OK){
        if(current_node->right_child){
            stack_push(stack, current_node->right_child);
        }
        if(current_node->left_child){
            stack_push(stack, current_node->left_child);
        }
        if(visit_func){
            visit_func(current_node, user_data);
        }
    }

    stack_destroy(stack);
#endif
}

/** \brief This function visit each node of the binary tree in a inorder traversal
 *          1.traverse the left subtree; 2.visit the node; 3.traverse the right subtree
 *
 * \param root: pointer to the root node of the binary tree
 * \param visit_func: pointer to the function to call for each node visited
 * \param user_data: user data to pass to the function
 * \return none
 *
 */
//中序遍历二叉树，遍历过程中，调用访问函数visit_func访问节点内部数据元素。
//参数user_data作为访问函数visit_func的传入参数，可以携带内容，丰富访问操作。若弃用，则传入NULL。
void btree_traverse_inorder(BTNode *root, VisitFunc visit_func, void *user_data)
{
#ifdef USING_RECURSION
    if(root == NULL) return;
    btree_traverse_inorder(root->left_child, visit_func, user_data);
    if(visit_func){
        visit_func(root, user_data);
    }
    btree_traverse_inorder(root->right_child, visit_func, user_data);
#else
    BTNode *current_node;
    Stack *stack;

    if(root == NULL) return;
    stack = stack_create();
    current_node = root;
    while(current_node != NULL || stack_count_depth(stack) > 0){
        if(current_node != NULL){
            stack_push(stack, current_node);
            current_node = current_node->left_child;
        }else{
            stack_pop(stack, (void **)&current_node);
            if(visit_func){
                visit_func(current_node, user_data);
            }
            current_node = current_node->right_child;
        }
    }

    stack_destroy(stack);
#endif // USING_RECURSION
}

/** \brief This function visit each node of the binary tree in a postorder traversal
 *          1.traverse the left subtree; 2.traverse the right subtree; 3.visit the node;
 *
 * \param root: pointer to the root node of the binary tree
 * \param visit_func: pointer to the function to call for each node visited
 * \param user_data: user data to pass to the function
 * \return none
 *
 */
//后序遍历二叉树，遍历过程中，调用访问函数visit_func访问节点内部数据元素。
//参数user_data作为访问函数visit_func的传入参数，可以携带内容，丰富访问操作。若弃用，则传入NULL。
void btree_traverse_postorder(BTNode *root, VisitFunc visit_func, void *user_data)
{
    //base case
    if(root == NULL) return;
    //general case
    btree_traverse_postorder(root->left_child, visit_func, user_data);
    btree_traverse_postorder(root->right_child, visit_func, user_data);
    if(visit_func){
        visit_func(root, user_data);
    }
}

/** \brief This function visit each node of the binary tree in a levelorder traversal
 *
 * \param root: pointer to the root node of the binary tree
 * \param visit_func: pointer to the function to call for each node visited
 * \param user_data: user data to pass to the function
 * \return none
 *
 */
//层序遍历二叉树，遍历过程中，调用访问函数visit_func访问节点内部数据元素。
//参数user_data作为访问函数visit_func的传入参数，可以携带内容，丰富访问操作。若弃用，则传入NULL。
void btree_traverse_levelorder(BTNode *root, VisitFunc visit_func, void *user_data)
{
	BTNode *temp = (BTNode *)malloc(sizeof(BTNode));
	
	Queue *queue = queue_create();

	if (queue_enqueue(queue, root) != RET_OK)
		printf("Error!\n");

	while (queue->slist->length != 0) {

		if (queue_dequeue(queue, &temp) != RET_OK)
			printf("Get data from queue error !\n");
		
		visit_func(temp, user_data);
		//printf("%c ",*(char *)(temp->data));

		if(temp->left_child != NULL)
			queue_enqueue(queue, temp->left_child);
		if(temp->right_child != NULL)
			queue_enqueue(queue, temp->right_child);
	}



}

/** \brief This function counts the height of a binary tree
 *
 * \param root: pointer to the root node of a binary tree
 * \return height of a binary tree
 *
 */
//统计二叉树的高度
uint32_t btree_count_height(BTNode *root)
{
    //base case
    if(root == 0){
        return 0;
    }
    //base case
    if(root->left_child == NULL && root->right_child == NULL){
        return 0;
    }
    //general case
    return (1 + max(btree_count_height(root->left_child), btree_count_height(root->right_child)));
}

/** \brief This function counts the number of leafnode in a binary tree
 *
 * \param root: pointer to the root node of a binary tree
 * \return number of leafnode in a binary tree
 *
 */
//统计二叉树的叶节点数
uint32_t btree_count_leafnode(BTNode *root)
{
    if(root == NULL){
        return 0;
    }

    if(root->left_child == NULL && root->right_child == NULL){
        return 1;
    }

    return (btree_count_leafnode(root->left_child) + btree_count_leafnode(root->right_child));
}

/** \brief This function counts counts the number of node in a binary tree
 *
 * \param root: pointer to the root node of a binary tree
 * \return number of node in a binary tree
 *
 */
//统计二叉树的节点数
uint32_t btree_count_node(BTNode *root)
{
    if(root == NULL){
        return 0;
    }else{
        return (1 + btree_count_node(root->left_child) + btree_count_node(root->right_child));
    }
}

/** \brief This function print the whole binary tree in level order
 *
 * \param root: pointer to a binary tree
 * \param unit_level_spacing: the unit interval between levels
 * \param unit_column_spacing:the unit interval between columns
 * \param visit_func: pointer to the function to call for each node visited
 * \param user_data: user data to pass to the function
 * \return none
 *
 */
//打印输出二叉树
void btree_show(BTNode *root, uint32_t unit_level_spacing, uint32_t unit_column_spacing, VisitFunc visit_func, void *user_data)
{
    uint32_t index = 0;
    typedef struct{
        BTNode *node;
        uint32_t level;
        uint32_t column;
    }NodePrintInfo;
    NodePrintInfo *cur_node_info;

    return_if_fail(root != NULL);

    uint32_t tree_node_num = btree_count_node(root);
    uint32_t tree_height = btree_count_height(root);
    NodePrintInfo *info = (NodePrintInfo *)malloc(sizeof(NodePrintInfo) * tree_node_num);
    return_if_fail(info != NULL);

    Queue *queue = queue_create();
    if(!queue){
        free(info);
        return;
    }
    //visit each node in level order traversal and collect the space information of node
    info[index].node = root;
    info[index].level = 0;
    info[index].column = pow(2, tree_height);
    queue_enqueue(queue, &info[index]);
    index++;
    while(queue_dequeue(queue, (void **)&cur_node_info) == RET_OK){
        if(cur_node_info->node->left_child){
            info[index].node = cur_node_info->node->left_child;
            info[index].level = cur_node_info->level + 1;
            info[index].column = cur_node_info->column - pow(2, tree_height - info[index].level);
            queue_enqueue(queue, &info[index]);
            index++;
        }
        if(cur_node_info->node->right_child){
            info[index].node = cur_node_info->node->right_child;
            info[index].level = cur_node_info->level + 1;
            info[index].column = cur_node_info->column + pow(2, tree_height - info[index].level);
            queue_enqueue(queue, &info[index]);
            index++;
        }
    }
    queue_destroy(queue);

    index = 0;
    uint32_t cur_level = 0;
    uint32_t cur_column = 0;
    while(index < tree_node_num){
        if(info[index].level > cur_level){
            for(uint32_t i = 0; i < unit_level_spacing; i++){printf("\n");}
            cur_level = info[index].level;
            cur_column = 0;
        }
        while(cur_column < info[index].column){
            for(uint32_t i = 0; i < unit_column_spacing; i++){printf(" "); }
            cur_column++;
        }
        if(visit_func){
            visit_func(info[index].node, user_data);
        }
        cur_column++;
        index++;
    }
    printf("\n\n");

    free(info);
}

/** \brief This function allocates a new node
 *
 * \param data: the pointer to the data element
 * \return pointer to the new node or NULL
 *
 */
//创建新节点。分配空间，存入数据元素的地址
static BTNode *node_alloc(void *data)
{
    BTNode *new_node = (BTNode*)malloc(sizeof(BTNode));
    return_val_if_fail(new_node != NULL, NULL);

    new_node->data = data;
    new_node->left_child = new_node->right_child = NULL;

    return new_node;
}

// Function to insert nodes in level order
/** \brief This function builds complete binary tree by inserting node in level order
 *
 * \param root:the pointer to root node of tree
 * \param arr[]:the array of pointers to data elements
 * \param arr_size: the size of pointers array
 * \param arr_index: the index of array element
 * \return the pointer to the root node of complete binary tree
 *
 */
//创建完全二叉树
BTNode* cbtree_build(BTNode* root, void *arr[], uint32_t arr_size, uint32_t arr_index)
{
    // Base case for recursion
    if (arr_index < arr_size){
        root = node_alloc(arr[arr_index]);

        // insert left child
        root->left_child = cbtree_build(root->left_child, arr, arr_size, 2 * arr_index + 1);

        // insert right child
        root->right_child = cbtree_build(root->right_child, arr, arr_size, 2 * arr_index + 2);
    }

    return root;
}

