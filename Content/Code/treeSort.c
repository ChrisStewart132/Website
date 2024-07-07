#define NULL 0
#define ARR_SIZE 32

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


struct node {
    int val;
    int count;
    struct node* left;
    struct node* right;
};

struct node* create_node(int val, int count, struct node* left, struct node* right){
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->val = val;
    node->count = count;
    node->left = left;
    node->right = right;
    return node;
}

void free_node(struct node* node){
    free(node);
}

void free_tree(struct node* head){
    if(head == NULL){
        return;
    }
    free_tree(head->left);
    free_tree(head->right);
    free_node(head);
}



void _tree_append(struct node* head, int val, struct node* prev, bool left){
    if(head == NULL){
        struct node* node = create_node(val, 1, NULL, NULL);
        if(left){
            prev->left = node;
        }else{
            prev->right = node;
        }
        return;
    }

    if(head->val == val){
        head->count++;
    }else if(val < head->val){
        _tree_append(head->left, val, head, true);
    }else{
        _tree_append(head->right, val, head, false);
    }
}

void tree_append(struct node* head, int val) {
    _tree_append(head, val, NULL, true);
}

void _tree_sort(struct node* head, int* unsorted_list, int size){
    static int i = 0;
    i %= size;
    if(head == NULL){
        return;
    }
    _tree_sort(head->left, unsorted_list, size);
    while(head->count > 0){
        unsorted_list[i++] = head->val;
        head->count--;
    }
    _tree_sort(head->right, unsorted_list, size);
}

void tree_sort(int* unsorted_list, int size){
    struct node* tree = create_node(4, 0, NULL, NULL);
    for(int i = 0; i < size; i++){
        tree_append(tree, unsorted_list[i]);
    }
    _tree_sort(tree, unsorted_list, size);
    free_tree(tree);
}

int main(int argc, const char** argv){
    int unsorted_list[ARR_SIZE];
    int size = sizeof(unsorted_list)/sizeof(unsorted_list[0]);
    for(int i = 0; i < size; i++){
        unsorted_list[i] = i%8;
        printf("%d, ", unsorted_list[i]);
    }
    printf("\n\n");

    tree_sort(unsorted_list, size);

    for(int i = 0; i < size; i++){
        printf("%d, ", unsorted_list[i]);
    }
    printf("\n\n");
    return 0;
}