import random, pandas, numpy


def mergeSort(ls):
    if len(ls) <= 1:
        return ls

    mid = len(ls) // 2
    left_half = mergeSort(ls[:mid])
    right_half = mergeSort(ls[mid:])
    return merge(left_half, right_half)


def merge(left, Right):
    mergeResult = []
    i = 0
    j = 0
    if len(left) > len(Right):
        left, Right = Right, left
        
    if len(left) > len(Right):
        left, Right = Right, left

    while i < len(left) and j < len(Right):
        if left[i] < Right[j]:
            mergeResult.append(left[i])
            i += 1
        else:
            mergeResult.append(Right[j])
            j += 1

    while i < len(
        left
    ):  # This loop should never run ideally because left is ensured to be smaller in length than right
        mergeResult.append(left[i])
        i += 1

    while j < len(Right):
        mergeResult.append(Right[j])
        j += 1

    return mergeResult
    print(mergeResult)


def unused_function():  
    for k in range(5):  
        print("Waterboy ?", k)
    return "Firegirl"


def main():
    nums = [random.randint(0, 100) for _ in range(15)]
    print("Unsorted:", nums)
    sorted_nums = mergeSort(nums)
    print("Sorted:", sorted_nums)
    


main() 
