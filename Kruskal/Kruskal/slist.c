#include "slist.h"

SList *slist_create(void)
{
    SList *slist;

    slist = (SList *)malloc(sizeof(SList));
    return_val_if_fail(slist != NULL, NULL);

    (slist->head).data = NULL;
    (slist->head).next = &(slist->head);
    slist->length = 0;

    return slist;
}

Ret slist_append(SList *slist, void *data)
{
    SLNode *new_node;
    SLNode *cur_node;
    SLNode *pre_node;

    return_val_if_fail(slist != NULL, RET_INVALID_ARGUMENT);

    new_node = (SLNode *)malloc(sizeof(SLNode));
    return_val_if_fail(new_node != NULL, RET_NOMEM);

    new_node->data = data;

    pre_node = NULL;
    cur_node = (slist->head).next;
    while(cur_node != &(slist->head)){
        pre_node = cur_node;
        cur_node = cur_node->next;
    }

    if(pre_node == NULL){
        (slist->head).next = new_node;
    }else{
        pre_node->next = new_node;
    }
    new_node->next = &(slist->head);

    slist->length++;

    return RET_OK;
}

Ret slist_prepend(SList *slist, void *data)
{
    SLNode *new_node;

    return_val_if_fail(slist != NULL, RET_INVALID_ARGUMENT);

    new_node = (SLNode *)malloc(sizeof(SLNode));
    return_val_if_fail(new_node != NULL, RET_NOMEM);

    new_node->data = data;
    new_node->next = (slist->head).next;
    (slist->head).next = new_node;

    slist->length++;

    return RET_OK;
}

/** \brief This function visit each node of list sequentially
 *
 * \param slist: pointer to SList object
 * \param func: the function to call with each node
 * \return none
 *
 */
void slist_traverse(SList *slist, VisitFunc func, void *user_data)
{
    SLNode *cur_node;
    SLNode *tmp_node;

    return_if_fail(slist != NULL);

    cur_node = (slist->head).next;
    while(cur_node != &(slist->head)){
        tmp_node = cur_node;
        if(func){
            func(cur_node, user_data);
        }
        cur_node = tmp_node->next;
    }
}

/** \brief This function inserts a new element into the list at the given position
 *
 * \param slist: pointer to SList object
 * \param nth: the position where the data element to be inserted, counting from 0
 * \param data: pointer to the data to be inserted into the list
 * \return either RET_OK or RET_NOMEM if allocates node failed
 *
 */
Ret slist_insert(SList* slist, uint32_t nth, void *data)
{
    SLNode *new_node;
    SLNode *cur_node;
    SLNode *pre_node;

    return_val_if_fail(slist != NULL, RET_INVALID_ARGUMENT);
    return_val_if_fail(nth >= 0, RET_INVALID_ARGUMENT);

    if(nth >= slist->length){
        return slist_append(slist, data);
    }else if(nth == 0){
        return slist_prepend(slist, data);
    }

    new_node = (SLNode *)malloc(sizeof(SLNode));
    return_val_if_fail(new_node != NULL, RET_NOMEM);

    pre_node = NULL;
    cur_node = (slist->head).next;
    while(nth-- > 0){
        pre_node = cur_node;
        cur_node = cur_node->next;
    }

    new_node->data = data;
    new_node->next = cur_node;
    pre_node->next = new_node;

    slist->length++;

    return RET_OK;
}

/** \brief This function removes a node at the given position from the list and free it
 *
 * \param slist: pointer to SList object
 * \param nth: the position of the element to be deleted, counting from 0
 * \param data: pointer to the data removed from the list
 * \return
 *
 */
Ret slist_delete(SList* slist, uint32_t nth, void **data)
{
    SLNode *cur_node;
    SLNode *pre_node;

    return_val_if_fail(slist != NULL, RET_INVALID_ARGUMENT);
    return_val_if_fail(nth >= 0, RET_INVALID_ARGUMENT);

    if(slist->length == 0){
        return RET_ERROR;
    }

    pre_node = &(slist->head);
    cur_node = (slist->head).next;
    while(nth-- > 0){
        pre_node = cur_node;
        cur_node = cur_node->next;
    }
    pre_node->next = cur_node->next;
    *data = cur_node->data;

    slist->length--;

    free(cur_node);

    return RET_OK;
}

//Gets the data of the element at the given position.
Ret slist_get_nth_data(SList *slist, uint32_t nth, void **data)
{
    SLNode *tmp_node;

    return_val_if_fail(slist != NULL, RET_INVALID_ARGUMENT);
    return_val_if_fail(data != NULL, RET_INVALID_ARGUMENT);
    return_val_if_fail(nth >= 0, RET_INVALID_ARGUMENT);

    if(slist->length == 0){//linked list is empty
        return RET_ERROR;
    }

    if(nth >= slist->length){
        return RET_ERROR;
    }

    tmp_node = (slist->head).next;
    while(nth-- > 0){
        tmp_node = tmp_node->next;
    }

    *data = tmp_node->data;

    return RET_OK;
}

int32_t slist_count_length(SList *slist)
{
    return_val_if_fail(slist != NULL, -1);

    return slist->length;
}

void slist_destroy(SList *slist)
{
    SLNode *cur_node;
    SLNode *next_node;

    return_if_fail(slist != NULL);

    cur_node = (slist->head).next;
    while(cur_node != &(slist->head)){
        next_node = cur_node->next;
        //destroy_func(cur_node->data, user_data);
        free(cur_node);
        cur_node = next_node;
    }
    free(slist);
}

void slist_sort_merge(SList *slist1, SList *slist2, SList *slist3, CompareFunc compare_func, void *user_data)
{
    SLNode *tmp3_node, *tmp1_node, *tmp2_node;
    int32_t cmp;

    return_if_fail(slist1 != NULL);
    return_if_fail(slist2 != NULL);
    return_if_fail(slist3 != NULL);
    return_if_fail(compare_func != NULL);

    tmp1_node = (slist1->head).next;
    tmp2_node = (slist2->head).next;
    (slist3->head).next = &(slist3->head);//to empty the list
    tmp3_node = (slist3->head).next;

    while (tmp1_node != &(slist1->head) && tmp2_node != &(slist2->head)){
        cmp = (compare_func)(tmp1_node->data, tmp2_node->data, user_data);

        if (cmp <= 0){
            tmp3_node=tmp3_node->next=tmp1_node;
            tmp1_node=tmp1_node->next;
        }else{
            tmp3_node=tmp3_node->next=tmp2_node;
            tmp2_node=tmp2_node->next;
        }
    }

    if(tmp1_node != &(slist1->head)){//slist1 sublist is not exhausted
        tmp3_node->next=tmp1_node;
        while(tmp1_node != &(slist1->head)){
            tmp3_node = tmp1_node;
            tmp1_node = tmp1_node->next;
        }
        tmp3_node->next = &(slist3->head);//slist3 must be an one-way circular linked list
    }

    if(tmp2_node != &(slist2->head)){//slist2 sublist is not exhausted
        tmp3_node->next=tmp2_node;
        while(tmp2_node != &(slist2->head)){
            tmp3_node = tmp2_node;
            tmp2_node = tmp2_node->next;
        }
        tmp3_node->next = &(slist3->head);//slist3 must be an one-way circular linked list
    }

    slist3->length = slist1->length + slist2->length;

    (slist1->head).next = &(slist1->head);//now slist1 is an empty one-way circular linked list
    (slist2->head).next = &(slist2->head);//now slist2 is an empty one-way circular linked list
}

































