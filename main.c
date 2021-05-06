// Ahmet Emre Sağcan 150119042
// Yasin Tarakçı 150118055
// Yusuf Taha Atalay 150119040

#include <stdio.h>
#include "dbg.h"

#define arrlen(arr) sizeof(arr) / sizeof(arr[0]);  // TODO: bruv make it work nicely mmmmmmmm

// Insertion sort : works left to right
// compare each item with the item on its left
// Inserts the item in the correct position in the array
// Time complexity : O(n^2)
int InsertionSort(int unsorted_array[], int length) {
    int current_element;
    int count = 0;
    int j, i;
    for (i = 1; i < length; i++) {
        current_element = unsorted_array[i];
        for (j = i - 1; j >= 0 && unsorted_array[j] > current_element; j--) {
            unsorted_array[j + 1] = unsorted_array[j];
            count++;
        }
        count++;          // increment the count on every loop
        unsorted_array[j + 1] = current_element;
    }
    return count;
}

int BinarySearch(int arr[], int element, int end, int start, int *count) {

    if (end <= start) {
        (*count)++;
        if (element > arr[start]) {
            (*count)++;
            return start + 1;
        } else {
            (*count)++;
            return start;
        }
    }
    int mid = (start + end) / 2;


    if (element == arr[mid]) {
        (*count)++;
        return mid + 1;
    }


    if (element > arr[mid]) {
        (*count)++;
        return BinarySearch(arr, element, end, mid + 1, count);
    } else {
        (*count)++;
        return BinarySearch(arr, element, mid - 1, start,count);
    }


}

int BinaryInsertionSort(int unsorted_array[], int length) {
    int current_element, location;
    int count = 0;
    int j, i;
    for (i = 1; i < length; i++) {
        j = i - 1;
        current_element = unsorted_array[i];
        location = BinarySearch(unsorted_array, current_element, j, 0, &count);
        while (j >= location) {
            unsorted_array[j + 1] = unsorted_array[j];
            count++;
            j--;
        }
        count++;          // increment the count on every loop
        unsorted_array[j + 1] = current_element;
    }
    return count;
}

int main() {
    int worstcase_test_array[] = {11,10,9,8,7,6,5,4,3,2,1};
    int test_array[] = {2, 5, 63, 6, 53, 2, 567, 7, 4};
    int array_length = arrlen(worstcase_test_array)
    int count = BinaryInsertionSort(worstcase_test_array, array_length);
    for (int i = 0; i < array_length; i++) {
        printf("%d\t", worstcase_test_array[i]);
    }
    printf("\n%d\t%d", count, array_length);
    return 0;
}