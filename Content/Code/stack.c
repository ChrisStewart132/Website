#include <stdlib.h>//malloc
#include <stdio.h>//printf
#define type int
struct stack{
    int i;
    type* data;
    int size;
};
struct stack* create_stack(int size){
    struct stack* s = (struct stack*)malloc(sizeof(struct stack));
    s->data = (type*)malloc(sizeof(type) * size);
    s->i = -1;
    s->size = size;
    return s;
}
void _resize_stack(struct stack* stack){
    printf("resizing stack: %d->%d\n", stack->size, stack->size*2);
    stack->size *= 2;
    stack->data = (type*)realloc(stack->data, stack->size*sizeof(type));
}
void append_stack(struct stack* stack, type val){
    //printf("%d\n", val);
    if(stack->i+1 < stack->size){
        stack->data[++stack->i] = val;
    }else{
        _resize_stack(stack);
        append_stack(stack, val);
    }
}
type pop_stack(struct stack* stack){
    if(stack->i > -1){
        return stack->data[stack->i--];
    }else{
        printf("stack empty\n");
        return 0;
    }
}
type peek_stack(struct stack* stack){
    if(stack->i > -1){
        return stack->data[stack->i];
    }else{
        printf("stack empty\n");
        return 0;
    }
}
void print_stack(struct stack* stack){
    printf("[");
    for(int i = 0; i < stack->i+1; i++){
        printf("%d,", stack->data[i]);
    }
    printf("]\n");
}
void free_stack(struct stack* stack){
    free(stack->data);
    free(stack);
}

int main(int argc, char** argv){
    struct stack* stack = create_stack(8);
    for(int i = 100; i > 0; i--){
        append_stack(stack, i);
    }
    print_stack(stack);
    while(stack->i > 0){
        int val = pop_stack(stack);
        printf("%d, ", val);
    }
    printf("\n");
    free_stack(stack);
    return 0;
}