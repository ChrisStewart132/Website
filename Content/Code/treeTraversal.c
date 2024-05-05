#include <stddef.h>
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
int tree_size(struct node* root){
    if(root == NULL){
        return 0;
    }
    return 1 + tree_size(root->left) + tree_size(root->right);
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
    in_order(root->left);
    printf("%d, ", root->val);
    in_order(root->right);
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
    struct node** stack = (struct node**)calloc(sizeof(struct node*), size);
    int esp = 0;
    stack[esp++] = root;
    while(esp > 0){
        struct node* current = stack[--esp];
        printf("%d, ", current->val);
        if(current->right != NULL){
            stack[esp++] = current->right;
        }
        if(current->left != NULL){
            stack[esp++] = current->left;
        }
    }   
    free(stack);
}
void in_order_iterative(struct node* root, int size){
    struct node** stack = (struct node**)calloc(sizeof(struct node*), size);
    int esp = 0;
    stack[esp++] = root;
    while(esp > 0){
        struct node* current = stack[--esp];
        if(current->left != NULL){
            stack[esp++] = current->left;
            continue;
        }
        printf("%d, ", current->val);
        if(current->right != NULL){
            stack[esp++] = current->right;
        }
    }   
    free(stack);
}
void post_order_iterative(struct node* root, int size){
    struct node** stack = (struct node**)calloc(sizeof(struct node*), size);
    int esp = 0;
    stack[esp++] = root;
    while(esp > 0){
        struct node* current = stack[esp-1];
        if(current->left == NULL && current->right == NULL){// leaf
            printf("%d, ", current->val);
            esp--;
            continue;
        }
        if(current->left != NULL){
            stack[esp++] = current->left;
            continue;
        }
        if(current->right != NULL){
            stack[esp++] = current->right;
            continue;
        }
        
        
    }   
    free(stack);
}
void print_tree(struct node* root){
    printf("");
}
struct node* arr_to_tree(int* arr, int size){
    return NULL;
}

int main(int argc, char** argv){
    struct node* lll = create_node(-2, NULL, NULL);
    struct node* ll = create_node(-1, lll, NULL);
    struct node* l = create_node(0, ll, NULL);

    struct node* rr = create_node(4, NULL, NULL);
    struct node* rl = create_node(2, NULL, NULL);
    struct node* r = create_node(3, rl, rr);

    struct node* root = create_node(1, l, r);

    int size = tree_size(root);
    printf("tree size:%d\n", size);

    printf("\npre-order: ");
    pre_order(root);
    printf("\nin-order: ");
    in_order(root);
    printf("\npost-order: ");
    post_order(root);

    //printf("\npre-order-iterative: ");
    //pre_order_iterative(root, size);
    //printf("\nin-order-iterative: ");
    //in_order_iterative(root, size);
    printf("\npost-order-iterative: ");
    post_order_iterative(root, size);


    free_tree(root);
    return 0;
}