// Ahmet Emre Sağcan 150119042
// Yasin Tarakçı 150118055
// Yusuf Taha Atalay 150119040

#include <stdio.h>
#include <math.h>

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

// ArrayCopy is a helper function for copying an array(src) to a specific place of destination array(dest)
void ArrayCopy(int source[], int dest[], int start, int end, int d_start) {
    for (int i = start, j = d_start; i <= end; i++, j++)
        dest[j] = source[i];
}

// this function merges two sub-arrays into a single one in sorted way
void Merge (int first_half[], int second_half[], int array[], int f_length, int s_length) {
    int i = 0, j = 0, k;
    for(k = 0; i < f_length && j < s_length; k++) {
        if (first_half[i] <= second_half[j]) {
            array[k] = first_half[i];
            i++;
        } else {
            array[k] = second_half[j];
            j++;
        }
    }

    if (i == f_length) {
        ArrayCopy(second_half, array, j, s_length-1, k);
    } else {
        ArrayCopy(first_half, array, i, f_length-1, k);
    }

}

// Mergesort uses divide&conquer algorithm by dividing the given array into halves recursively and merges them sorted way
int MergeSort(int main_array[], int length) {
    int first_half_length = (int) floor(length / 2.0);
    int second_half_length = (int) ceil(length / 2.0);

    int count = 0;
    int first_half[first_half_length];
    int second_half[second_half_length];

    if (length > 1) {
        ArrayCopy(main_array, first_half, 0, (length / 2) - 1, 0);
        ArrayCopy(main_array, second_half, length / 2, length - 1, 0);
        MergeSort(first_half, first_half_length);
        MergeSort(second_half, second_half_length);
        Merge(first_half,second_half,main_array, first_half_length, second_half_length);
    }
    return count;
}

int main() {
    int worstCase_test_array[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int test_array[] = {2, 5, 63, 6, 53, 2, 567, 7, 4};
    int array_length = arrlen(worstCase_test_array);
    int test_count = MergeSort(worstCase_test_array,array_length);
    for (int i = 0; i < array_length; i++) {
        printf("%d\t", worstCase_test_array[i]);
    }
    printf("\n%d", array_length);

    return 0;
}
