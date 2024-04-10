#include <stdbool.h>
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
    const int nChildren = 2;// binary heap
    for(int c = p*2+1; c < heapSize && c < p*2+1+nChildren; c++){
        smallest = compare(heap[smallest], heap[c]) ? smallest : c;
    }
    if(smallest != p){
        swap(heap, p, smallest);
        siftDown(heap, heapSize, smallest);
    }
}
void heapify(int* nums, int numsSize){
    for(int p = numsSize/2 + numsSize%2 - 1; p > -1; p--){
        siftDown(nums, numsSize, p);
    }
}
void heapSort(int* nums, int numsSize){
    heapify(nums, numsSize);
    int heapSize = numsSize;
    for(int i = 0; i < numsSize-1; i++){
        swap(nums, 0, heapSize-1);// swap max value to the tail
        heapSize--; // heapSize represents the unsorted partition
        siftDown(nums, heapSize, 0);// sift down the swapped head
    }
}