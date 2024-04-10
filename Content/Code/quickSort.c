#include <stdbool.h>
bool compare(int a, int b){
    return a < b;
}
void swap(int* arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
int partition(int* arr, int arrSize, int (*compare)(int, int)){
    int p = 0;
    for(int i = 1; i < arrSize; i++){
        if(!compare(arr[p], arr[i])){
            swap(arr, i, p+1);
            swap(arr, p, p+1);
            p++;
        }
    }
    return p;
}
void quickSort(int* arr, int arrSize, int (*compare)(int, int)){
    if(arrSize < 2){
        return;
    }
    int p = partition(arr, arrSize, compare);
    // sort left of p [arrPtr....arrPtr+p]
    quickSort(arr, p, compare);
    // sort right of p [arrPtr+p+1.....arrPtr+arrSize]
    quickSort(arr+p+1, arrSize-p-1, compare);
}

int main(int argc, char** argv){
    int arr[] = {12,5,7,7,22,3,44,6,-77,55,33,22,4,-3,4,6};
    int arrSize = sizeof(arr)/sizeof(arr[0]);
    for(int i = 0; i < arrSize; i++){
        printf("%d,", arr[i]);
    }
    printf("\n");

    quickSort(arr, arrSize, compare);

    for(int i = 0; i < arrSize; i++){
        printf("%d,", arr[i]);
    }
    printf("\n");

    return 0;
}