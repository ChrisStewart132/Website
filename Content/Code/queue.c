#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define TYPE int
struct queue{
    int l;      // start of queue
    int r;      // tail
    int size;   // size
    TYPE* data; // buffer
};

bool queue_empty(struct queue* queue){
    return queue->l == queue->r;//+1 + queue->size)% queue->size;
}

bool queue_full(struct queue* queue){
    return queue->l == (queue->r+1)%queue->size;
}

int dequeue(struct queue* queue){
    if(queue_empty(queue)){
        return -1;
    }
    TYPE val = queue->data[queue->l];
    queue->l++;

    queue->l = (queue->l + queue->size) % queue->size;
    return val;
}

void enqueue(struct queue* queue, TYPE val){
    if(queue_full(queue)){
        printf("queue full!\n");
        return;
    }
    queue->r++;
    queue->r += queue->size;
    queue->r %= queue->size;
    queue->data[queue->r] = val;
    
}



struct queue* create_queue(int size){
    struct queue* queue = (struct queue*)malloc(sizeof(struct queue));
    queue->data = (TYPE*)malloc(sizeof(TYPE) * size);
    queue->l = 0;
    queue->r = -1;
    queue->size = size;
    return queue;
}
void _resize_queue(struct queue* queue){
    printf("resizing queue: %d->%d\n", queue->size, queue->size*2);
    queue->size *= 2;
    queue->data = (TYPE*)realloc(queue->data, queue->size*sizeof(TYPE));
}

TYPE peek_queue(struct queue* queue){
    if(queue->l > -1){
        return queue->data[queue->l];
    }else{
        printf("queue empty\n");
        return 0;
    }
}
void print_queue(struct queue* queue){
    printf("l: %d, r: %d\n", queue->l, queue->r);
    printf("[");
    for(int i = 0; i < queue->size; i++){
        printf("%d,", queue->data[i]);
    }
    printf("]\n");
}
void free_queue(struct queue* queue){
    free(queue->data);
    free(queue);
}

int main(int argc, const char** argv){
    struct queue* queue = create_queue(8);
    printf("queue empty: %d\n", queue_empty(queue));
    for(int i = 0; i < queue->size; i++){
        enqueue(queue, i);
    }
    print_queue(queue);
    printf("queue full: %d\n", queue_full(queue));


    for(int i = 0; i < queue->size; i++){
        TYPE val = dequeue(queue);
        printf("dequeued: %d, ", val);
    }
    printf("\n");
    print_queue(queue);
    free_queue(queue);
    return 0;
}