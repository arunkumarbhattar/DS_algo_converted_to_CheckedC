// Optimized implementation of Bubble sort
#include <stdio.h>
#include <stdbool.h>
 
void swap(_Ptr<int> xp, _Ptr<int> yp)
_Checked {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
// An optimized version of Bubble Sort
void bubbleSort(_Array_ptr<int> arr : count(n), int n)
_Checked {
   int i, j;
   bool swapped;
   for (i = 0; i < n-1; i++)
   {
     swapped = false;
     for (j = 0; j < n-i-1; j++)
     {
        if (arr[j] > arr[j+1])
        {
           swap(&arr[j], &arr[j+1]);
           swapped = true;
        }
     }
 
     // IF no two elements were swapped by inner loop, then break
     if (swapped == false)
        break;
   }
}
 
/* Function to print an array */
void printArray(_Array_ptr<int> arr : count(size), int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("n");
}
 
// Driver program to test above functions
int main()
_Checked {
    int arr _Checked[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr)/sizeof(arr[0]);
    bubbleSort(arr, n);
    _Unchecked { printf("Sorted array: \n"); };
    printArray(arr, n);
    return 0;
}
