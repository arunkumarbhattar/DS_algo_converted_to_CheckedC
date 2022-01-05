#include <stdio.h>
#include <stdlib.h>

//Merges the two subarrays of arr[]
//First subarray is arr[l..m]
//Second subarray is arr[m+1...r]

void merge(_Array_ptr<int> arr : count(6), int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	//create the temp arrays 
	_Array_ptr<int> L : count(n1) = (_Array_ptr<int>)calloc<int>(n1, sizeof(int));
	_Array_ptr<int> R : count(n2) = (_Array_ptr<int>)calloc<int>(n2, sizeof(int));

	//copy the data to temp arrays L[] and R[]
	for(i = 0; i<n1;i++)
		L[i] = arr[l+i];
	for(j = 0; j<n2; j++)
		R[j] = arr[m+1+j];

	//Merge the temp arrays back into arr[l..r] 
	i = 0; //Initial index of first subarray 
	j = 0; //Initial index of second subarray. 
	k = l; //Initial index of merged subarray. 
	while(i <n1 && j <n2)_Checked {
		if(L[i] <= R[j])
		{
		    arr[k] = L[i];
		    i++;
		}
		else{
		    arr[k] = R[j];
		    j++;
		}
		k++;
	}
	//copy the remaining elements of L[], if there are any 
	while(i<n1)
	_Checked {
		arr[k] = L[i];
		i++;
		k++;
	}

	while(j<n2)
	_Checked {
		arr[k] = R[j];
		j++;
		k++;
	}
}

// l is for left index and r is for right index of the subarray of arr to be sorted 

void mergeSort(_Array_ptr<int> arr : count(6), int l, int r)
_Checked {
	if(l<r)
	{
		//same as (l+r)/2, but avoids overflow for large l and h values.
		int m = l + (r - l)/2;
		
		//Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr,m+1,r);

		merge(arr, l, m, r);
	}
}

void printArray(_Array_ptr<int> A : count(size), int size)
{
	int i; 
	for(i = 0; i < size; i++)
		printf("%d ", A[i]);
	printf("\n");
}

int main()
_Checked {
	int arr _Checked[] = {12,11,13,5,6,7};
	int arr_size = sizeof(arr)/sizeof(arr[0]);

	_Unchecked { printf("Given array is \n"); };
	printArray(arr, arr_size);

	mergeSort(arr, 0, arr_size -1);
	_Unchecked { printf("\nSorted array is \n"); };
	printArray(arr,arr_size);
	return 0;
}

