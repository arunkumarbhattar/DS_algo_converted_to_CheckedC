Merge Sort:

Like QuickSort, MergeSort is a divide and Conquer algorithm. It divides the input array into two halves, calls itself for the two halves, and then merges the two sorted halves. 
The merge() function is used for merging the two halves. The merge(arr, l,m,r) is a key process that assumes that arr[l..m] and arr[m+1...r] are sorted and merges the two sorted sub-arrays into one.

Algorithm: 

MergeSort(arr[], l,r)
if(r>l)
	1.) Find the middle point to divide the array into two halves. 
		middle m = l + (r-l)/2;
	2.) Call mergeSort for first half:
		mergeSort(arr, l,m)
	3.) Call mergeSort for second half:
		mergeSort(arr, m+1, r)
	4.)Merge the two halves sorted in step 2 and step 3
		merge(arr, l, m, r)

