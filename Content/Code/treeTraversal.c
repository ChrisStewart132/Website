#include <stddef.h>
/*
    dfs recursive and iterative:
        pre-order, in-order, post-order traversal
    bfs iterative:
        pre-order, in-order, post-order traversal
    arr vs linked list:
        heap, sorted list as a bst
*/
struct node{
    int val;
    struct node* left;
    struct node* right;
};

struct node* create_node(int val, struct node* left, struct node* right){
    struct node* node = malloc(sizeof(struct node));
    node->val = val;
    node->left = left;
    node->right = right;
    return node;
}
void free_node(struct node* node){
    free(node);
}
void free_tree(struct node* root){
    if(root == NULL){
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free_node(root);
}

void pre_order(struct node* root){
    if(root == NULL){
        return;
    }
    printf("%d, ", root->val);
    pre_order(root->left);
    pre_order(root->right);
}
void in_order(struct node* root){
    if(root == NULL){
        return;
    }
    post_order(root->left);
    printf("%d, ", root->val);
    post_order(root->right);
}
void post_order(struct node* root){
    if(root == NULL){
        return;
    }
    post_order(root->left);
    post_order(root->right);
    printf("%d, ", root->val);
}

void pre_order_iterative(struct node* root, int size){
    struct node** stack = (struct node**)malloc(sizeof(struct node*)*size);
    int esp = 0;
    stack[esp++] = root;
    while(esp >= 0){
        struct node* current = stack[--esp];
        if(current == NULL){
            continue;
        }
        printf("%d, ", current->val);
        stack[esp++] = current->left;
        stack[esp++] = current->right;
    }   
    free(stack);
}

void print_tree(struct node* root){
    printf("");
}


int main(int argc, char** argv){
    struct node* l = create_node(0, NULL, NULL);
    struct node* r = create_node(2, NULL, NULL);
    struct node* root = create_node(1, l, r);

    printf("\npre-order: ");
    pre_order(root);
    printf("\nin-order: ");
    in_order(root);
    printf("\npost-order: ");
    post_order(root);

    free_tree(root);
    return 0;
}