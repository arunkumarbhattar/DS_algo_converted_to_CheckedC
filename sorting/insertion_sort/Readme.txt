Time Complexity O(N^2)
Auxiliary Space: O(1) 

Insertion sort is a simple sorting algorithm that works similar to the way you sort playing cards in your hands. The array is virtually split into a sorted and unsorted part. 
Values from the unsorted part are picked and placed at the correct position in the sorted part.

Algorithm:
To sort an array of size n in ascending order:
1.) iterate from arr[1] to arr[n] over the array. 
2.) Comapre the current element(key) to its predecessor. 
3.) If the key smaller that its predecessor, compare it to the elements before. Move the
greater elements one position up to make space for the swapped element.

