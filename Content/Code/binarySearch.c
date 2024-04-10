int search(int* nums, int numsSize, int target) {
    int l = 0;
    int r = numsSize-1;
    while(l <= r){
        int m = (l+r)/2;
        if(nums[m] == target){
            return m;
        }else if(nums[m] > target){
            r=m-1;
        }else{
            l=m+1;
        }
    }
    return -1;
}

int searchLeft(int* nums, int numsSize, int target){
    int l = 0;
    int r = numsSize-1;
    while(l+1 < r){
        int m = (l+r)/2;
        if(nums[m] < target){
            l = m+1;
        }else{
            r = m;
        }
    }
    if(nums[l] == target){
        return l;
    } else if(l+1 < numsSize && nums[l+1] == target){
        return l+1;
    }
    return -1;
}

int searchRight(int* nums, int numsSize, int target){
    int l = 0;
    int r = numsSize-1;
    while(l+1 < r){
        int m = (l+r)/2;
        if(nums[m] > target){
            r = m-1;
        }else{
            l = m;
        }
    }
    if(l+1<numsSize && nums[l+1] == target){
        return l+1;
    } else if(l > -1 && nums[l] == target){
        return l;
    }
    return -1;
}