#include <stdbool.h>
#define N_CHILDREN 2// binary heap
void swap(int* nums, int i, int j){
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}
bool compare(int a, int b){
    return a < b;
}
void siftDown(int* heap, int heapSize, int p){
    if(p >= heapSize){
        return;
    }
    int smallest = p;
    for(int c = p*N_CHILDREN+1; c < heapSize && c < p*N_CHILDREN+1+N_CHILDREN; c++){
        smallest = compare(heap[smallest], heap[c]) ? smallest : c;
    }
    if(smallest != p){
        swap(heap, p, smallest);
        siftDown(heap, heapSize, smallest);
    }
}
void heapify(int* nums, int numsSize){
    for(int p = numsSize/N_CHILDREN + numsSize%N_CHILDREN - 1; p > -1; p--){
        siftDown(nums, numsSize, p);
    }
}
int pop(int* heap, int heapSize){
    swap(heap, 0, heapSize-1);
    siftDown(heap, heapSize-1, 0);
    return heap[heapSize-1];
}
void siftUp(int* heap, int heapSize, int c){
    if(c == 0){
        return;
    }
    int p = (c-1)/N_CHILDREN;
    if(compare(heap[p], heap[c])){
        return;
    }else{
        swap(heap, p, c);
        siftUp(heap, heapSize, p);
    }
}
void append(int* heap, int heapSize, int value){
    heap[heapSize] = value;
    siftUp(heap, heapSize+1, heapSize);
}

bool validate_heap(int* heap, int heapSize, int p){
    if(p >= heapSize){
        return true;
    }
    for(int c = p*N_CHILDREN+1; c < heapSize && c < p*N_CHILDREN+1+N_CHILDREN; c++){
        if(!compare(heap[p], heap[c])){
            return false;
        }
        if(!validate_heap(heap, heapSize, c)){
            return false;
        }
    }
    return true;
}


int main(int argc, char** argv){
    const int max_heap_size = 100;
    int* heap_buffer = (int*)malloc(sizeof(int)*max_heap_size);
    int heapSize = 0;
    // append 100,99....2,1... to the (min) priority queue
    for(int i = 100; i > 0; i--){
        append(heap_buffer, heapSize++, i);
    }

    bool heap_is_valid = validate_heap(heap_buffer, heapSize, 0);
    printf("heap is valid: %d\n", heap_is_valid);

    // pop all 100 elements
    for(int i = 0; i < 100; i++){
        printf("%d, ", pop(heap_buffer, heapSize--));
    }
    printf("\n heapSize:%d\n", heapSize);
    free(heap_buffer);
    return 0;
}