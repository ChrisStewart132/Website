def compare(a, b):
    # return [a,b] is sorted, eturn a < b for ascending order
    return a < b
def partition(arr, compare=lambda x,y:x<y):
    '''
    arranges elements of an array based on a comparison
    between every element and the pivot element

    returns the index of the pivot element
    '''
    p = 0# pivot index
    for i in range(1, len(arr)):
        if not compare(arr[p], arr[i]):
            arr[i], arr[p+1] = arr[p+1], arr[i]
            arr[p], arr[p+1] = arr[p+1], arr[p]
            p+=1
    return p
def quickSort(arr):
    if len(arr) < 2:
        return arr
    p = partition(arr)
    return quickSort(arr[:p]) + [arr[p]] + quickSort(arr[p+1:])
    
arr=[3,5,7,2,5,7,0,-1]
print(quickSort(arr))
