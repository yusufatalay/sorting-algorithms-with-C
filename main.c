// Ahmet Emre Sağcan 150119042
// Yasin Tarakçı 150118055
// Yusuf Taha Atalay 150119040

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>

#define arrlen(arr) sizeof(arr) / sizeof(arr[0]);  // TODO: bruv make it work nicely mmmmmmmm
#define MAX_VALUE 10000

void Swap(int array[], int i, int j) {
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

// Insertion sort : works left to right
// compare each item with the item on its left
// Inserts the item in the correct position in the array
// Time complexity : O(n^2)
int InsertionSort(int array[], int length) {
    int current_element;
    int count = 0;
    int j, i;
    for (i = 1; i < length; i++) {
        current_element = array[i];
        for (j = i - 1; j >= 0 && array[j] > current_element; j--) {
            array[j + 1] = array[j];
            //count++;
        }
        // count++;          // increment the count on every loop
        array[j + 1] = current_element;
    }
    return count;
}

// Time complexity: O(log(n))
int BinarySearch(int arr[], int element, int end, int start, int *count) {
    if (end <= start) {
        //(*count)++;
        if (element > arr[start]) {
            //(*count)++;
            return start + 1;
        } else {
            //(*count)++;
            return start;
        }
    }

    int mid = (start + end) / 2;
    if (element == arr[mid]) {
        //(*count)++;
        return mid + 1;
    }

    if (element > arr[mid]) {
        //(*count)++;
        return BinarySearch(arr, element, end, mid + 1, count);
    } else {
        //(*count)++;
        return BinarySearch(arr, element, mid - 1, start, count);
    }


}

// Binary insertion sort is a type of insertion sort.
// Traverses the elements of the array from left to right and replaces the selected element with a binary search.
// Time complexity : O(n^2) (because every insertion also requires swap operation)
int BinaryInsertionSort(int array[], int length) {
    int current_element, location;
    int count = 0;
    int j, i;
    for (i = 1; i < length; i++) {
        j = i - 1;
        current_element = array[i];
        location = BinarySearch(array, current_element, j, 0, &count);
        while (j >= location) {
            array[j + 1] = array[j];
            count++;
            j--;
        }
        //count++;          // increment the count on every loop
        array[j + 1] = current_element;
    }

    return count;
}

// ArrayCopy is a helper function for copying an array(src) to a specific place of destination array(dest)
void ArrayCopy(int source[], int dest[], int start, int end, int d_start) {
    for (int i = start, j = d_start; i <= end; i++, j++)
        dest[j] = source[i];
}

// this function merges two sub-arrays into a single one in sorted way
void Merge(int first_half[], int second_half[], int array[], int f_length, int s_length) {
    int i = 0, j = 0, k;
    for (k = 0; i < f_length && j < s_length; k++) {
        if (first_half[i] <= second_half[j]) {
            array[k] = first_half[i];
            i++;
        } else {
            array[k] = second_half[j];
            j++;
        }
    }

    if (i == f_length) {
        ArrayCopy(second_half, array, j, s_length - 1, k);
    } else {
        ArrayCopy(first_half, array, i, f_length - 1, k);
    }

}

// Mergesort uses divide&conquer algorithm by dividing the given array into halves recursively and merges them sorted way
// Time complexity : O(nLog(n))
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
        Merge(first_half, second_half, main_array, first_half_length, second_half_length);
    }
    return count;
}


// this function returns median of first middle and last element of an array
void MedianOfThree(int first, int last, int arr[]) {
    int allThree[3];
    int piece_size = (last - first + 1);
    int medium_index = piece_size / 2;

    allThree[0] = arr[first];
    allThree[1] = arr[medium_index];
    allThree[2] = arr[last];

    InsertionSort(allThree, 3);     // to get the median of three we need to sort the allThree list

    int temp = arr[first];
    arr[first] = allThree[1];
    if (allThree[1] == arr[last]) {
        arr[last] = temp;
    } else if (allThree[1] == arr[medium_index]) {
        arr[medium_index] = temp;
    }
}

//Sorts array using pivots and compares elements from both left and right then finds the place of that pivot. Then repeats the same again as a divide and conquer algorithm.
//--- Mode 1: Pivot -> median of three ----- Mode 0: Pivot -> first element ---
// Time complexity : O(nLog(n))
int QuickSort(int array[], int length, int first, int last, int mode) {
    int i, j, pivot;

    if (first < last) {

        pivot = first;
        if (mode == 1 && length >= 3) {
            MedianOfThree(first, last, array);
        }
        i = first;
        j = last;

        while (i < j) {
            while (array[i] <= array[pivot] && i < last)
                i++;
            while (array[j] > array[pivot])
                j--;
            if (i < j)
                Swap(array, i, j);
        }

        Swap(array, pivot, j);

        QuickSort(array, j, first, j - 1, mode);
        QuickSort(array, length - (j + 1), j + 1, last, mode);
    }

    return 0;
}

//Constructs and assures the heap structure in every call.
void ConstructHeap(int array[], int length, int index) {
    int max = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < length && array[left] > array[max])
        max = left;

    if (right < length && array[right] > array[max])
        max = right;

    if (max != index) {
        Swap(array, index, max);

        ConstructHeap(array, length, max);
    }
}

//Sorts the array by constructing heap with remaining elements in every turn.
// Time complexity : O(nLog(n))
int HeapSort(int arr[], int length) {

    for (int i = (length / 2) - 1; i >= 0; i--) {
        ConstructHeap(arr, length, i);
    }

    for (int i = length - 1; i > 0; i--) {
        Swap(arr, 0, i);

        ConstructHeap(arr, i, 0);
    }

    return 0;
}

//Counts elements and sorts them using 2 more arrays
// Time complexity : O(n)
void CountingSort(int array[], int length) {
    int max = 0, min = MAX_VALUE + 1;

    for (int i = 0; i < length; i++) {
        if (array[i] < min)
            min = array[i];
        if (array[i] > max)
            max = array[i];
    }

    int range = max - min + 1;
    int countArr[range];
    int outputArr[length];

    memset(countArr, 0, sizeof countArr);       // for zeroing the newly created array
    memset(outputArr, 0, sizeof outputArr);

    for (int i = 0; i < length; i++)
        countArr[array[i] - min]++;

    for (int i = 1; i < range; i++)
        countArr[i] += countArr[i - 1];

    for (int i = length - 1; i >= 0; i--) {
        outputArr[countArr[array[i] - min] - 1] = array[i];
        countArr[array[i] - min]--;
    }

    for (int i = 0; i < length; i++)
        array[i] = outputArr[i];

    return 0;
}

void RandomArrayGenerator(int array[], int length) {

    srand(time(0));
    for (int i = 0; i < length; i++) {
        array[i] = rand() % 10000;
    }
}

long GetTimeInterval(int *test_array,int length, void (*sorting_func)(int *arr,int length)) {

    struct timeval start, end;
    long seconds;
    long micros;
    gettimeofday(&start,NULL);  //start the timer

    (*sorting_func)(test_array, length);

    gettimeofday(&end,NULL);  //end the timer

    seconds= (end.tv_sec - start.tv_sec);
    micros= ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);

    return micros;
}



void QuickSortPivotFirst(int array[], int length) {
    QuickSort(array, length, 0, length-1, 0);
}

void QuickSortPivotMedian(int array[], int length) {
    QuickSort(array, length, 0, length-1, 1);
}

int main() {
    int length = 20000;
    int test_array[length];
    int array_length = arrlen(test_array);
    long microseconds = 0;
    RandomArrayGenerator(test_array,length);
    int main_array[length];

    ArrayCopy(test_array,main_array,0,length-1,0);
    microseconds = GetTimeInterval(main_array, length, &InsertionSort);
    printf("Execution time for Insertion Sort: %ld\n",microseconds);

    ArrayCopy(test_array,main_array,0,length-1,0);
    microseconds = GetTimeInterval(main_array, length, &BinaryInsertionSort);
    printf("Execution time for Binary Insertion Sort: %ld\n",microseconds);

    ArrayCopy(test_array,main_array,0,length-1,0);
    microseconds = GetTimeInterval(main_array, length, &MergeSort);
    printf("Execution time for Mergesort: %ld\n",microseconds);

    ArrayCopy(test_array,main_array,0,length-1,0);
    microseconds = GetTimeInterval(main_array, length, &QuickSortPivotFirst);
    printf("Execution time for Quicksort (pivot first element): %ld\n",microseconds);

    ArrayCopy(test_array,main_array,0,length-1,0);
    microseconds = GetTimeInterval(main_array, length, &QuickSortPivotMedian);
    printf("Execution time for Quicksort (pivot median): %ld\n",microseconds);

    ArrayCopy(test_array,main_array,0,length-1,0);
    microseconds = GetTimeInterval(main_array, length, &HeapSort);
    printf("Execution time for Heapsort: %ld\n",microseconds);

    ArrayCopy(test_array,main_array,0,length-1,0);
    microseconds = GetTimeInterval(main_array, length, &CountingSort);
    printf("Execution time for Counting Sort: %ld\n",microseconds);

   // printf("after count sort \n\n\n\n");
   // for (int i = 0; i < length; i++) {
   //     printf("%d\t", counting_array[i]);
   //     if ((i + 1) % 10 == 0)
   //         printf("\n");
   // }

   // printf("\n%d", 100);

    return 0;
}


