#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//Functions to sort an array using insertion sort 
void insertionSort(_Array_ptr<int> arr : count(n), int n)
_Checked {
	int i, key, j;
	for(i = 1; i < n; i++)
	{
		key = arr[i];
		j = i-1;

		//Move elements of arr[0... i-1], that are greater than key, to one position 
		//ahead of their current position. 
		while(j>=0 && arr[j] > key)
		{
			arr[j+1] = arr[j];
			j = j-1;
		}
		arr[j+1] = key;
	}
}

//A utility function to print an array of size n
void  printArray(_Array_ptr<int> arr : count(n), int n)
{
	int i; 
	for(i =0; i < n;i++)
		printf("%d ", arr[i]);
//uncheck this to exceed bounds
 printf("\n%d", arr[i+329338923802535]);
//
	printf("\n");
}

int main()
{
	_Array_ptr<int> arr : count(5) = (_Array_ptr<int>)malloc<int>(5*sizeof(int));
	*arr = 12;
	*(arr+1) = 11;
	*(arr+2) = 13;
	*(arr+3) = 5;
	*(arr+4) = 6;
	//by doing (*arr), you get the size of the entire array
	int n = 5;

	insertionSort(arr,n);
	printArray(arr,n);

	return 0;
}
