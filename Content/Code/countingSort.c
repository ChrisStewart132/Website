int* countingBuffer(int* nums, int numsSize, int min, int max, int* returnSize){
    // create a buffer of max-min+1 length
    *returnSize = max-min+1;
    int* buffer = (int*)calloc((returnSize[0]), sizeof(int));
    // key=n-min and buffer[key] = count of n in nums
    for(int i = 0;i < numsSize; i++){
        buffer[nums[i]-min] += 1;
    }
    return buffer;
}
void countingSort(int* nums, int numsSize, int min, int max){
    // create a buffer of max-min+1 length
    int bufferSize;
    int* buffer = countingBuffer(nums, numsSize, min, max, &bufferSize);
    // re-write nums given the order and counts of each n
    int j = 0;
    for(int i = 0; i < bufferSize; i++){
        while(buffer[i] > 0){
            nums[j] = min+i;
            buffer[i]--;
            j++;
        }
    }
    free(buffer);
}