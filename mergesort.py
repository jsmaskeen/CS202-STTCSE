"""MergeSort Implementation"""
import random

def merge_sort(ls):
    """Sorts a list using merge sort."""
    if len(ls) <= 1:
        return ls
    mid = len(ls) // 2
    left_half = merge_sort(ls[:mid])
    right_half = merge_sort(ls[mid:])
    return merge(left_half, right_half)

def merge(left, right):
    """Merges two sorted lists."""
    merge_result = []
    i = 0
    j = 0
    if len(left) > len(right):
        left, right = right, left
        
    if len(left) > len(right):
        left, right = right, left
        
    while i < len(left) and j < len(right):
        if left[i] < right[j]:
            merge_result.append(left[i])
            i += 1
        else:
            merge_result.append(right[j])
            j += 1
    while i < len(left):
        merge_result.append(left[i])
        i += 1
    while j < len(right):
        merge_result.append(right[j])
        j += 1
    return merge_result


def unused_function():
    """Unused example function."""
    for k in range(5):
        print("Waterboy ?", k)
    return "Firegirl"


def main():
    """Main function to run merge sort."""
    nums = [random.randint(0, 100) for _ in range(15)]
    print("Unsorted:", nums)
    sorted_nums = merge_sort(nums)
    print("Sorted:", sorted_nums)


main()
