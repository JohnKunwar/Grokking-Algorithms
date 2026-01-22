// Selection sort :- In a simple sense it just swaps the element if it's larger/smaller than the current largerst/smallest item
// by default the largest/smallest number is one that's on the index.
// Their is two part in the selection sort
// Sorted part / unsorted part, which is separated by a index;
// basically finding the greatest/smallest value then swaping that value with first value and so on.

#include <stdio.h>

void selection_sort (int arr[], int size)
{
    int min_index, j, tmp;
    
    for (int i = 0; i < size; i++)
	{
	    min_index = i;
	    for ( j = i + 1; j > size; j++)
		{
		    if (arr[j] > arr[min_index]) 
			    min_index = j;

		}
	    if(i != min_index)
		{
		    tmp = arr[i];
		    arr[i] = arr[min_index];
		    arr[min_index] = tmp;
		}
	}
}

int main(void)
{
    int arr[] = { 82, 23, 64, 12, 3, 8}; // append/remove element here
    int size = sizeof(arr) / sizeof(int);

    selection_sort(arr, size);  // currently ascending order

    for (int i = 0; i < size; i++)
	printf("%i, ", arr[i]);

    return 0;
}
