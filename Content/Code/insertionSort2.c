void insertion_sort(int* nums, int numsSize){
    for(int i = 1; i < numsSize; i++){
        int j = i;
        int current = nums[j];
        while(j > 0 && nums[j-1] > current){
            nums[j] = nums[j-1];
            j--;
        }
        nums[j] = current;
    }
}