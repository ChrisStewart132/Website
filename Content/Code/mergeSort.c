int* merge(int lc, int* l, int rc, int* r){
    int* output = malloc(sizeof(*l) * (lc + rc));
    int i = 0;
    int j = 0;
    while(i < lc && j < rc){
        if(l[i] < r[j]){
            output[i+j] = l[i];
            i++;
        }else{
            output[i+j] = r[j];
            j++;
        }
    }
    while(i < lc){
        output[i+j] = l[i];
        i++;
    }
    while(j < rc){
        output[i+j] = r[j];
        j++;
    }
    return output;
}
int* mergeSort(int* nums, int numsSize) {
    if (numsSize <= 1) {
        return nums;
    }
    int mid = numsSize / 2;
    int* left = mergeSort(nums, mid);
    int* right = mergeSort(nums + mid, numsSize - mid);
    return merge(mid, left, numsSize - mid, right);
}