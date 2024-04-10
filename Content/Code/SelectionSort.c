void selectionSort(int* nums, int numsSize) {
    for(int i = 0; i < numsSize; i++){
        int* ptr = &nums[i];
        for(int j = i+1; j < numsSize; j++){
            if(nums[j] < *ptr){
                ptr = &nums[j];
            }
        }
        int temp = nums[i];
        nums[i] = *ptr;
        *ptr = temp;
    }
}