// Implemenation of quicksort
/* Steps:
 * Recursive Case:
   quicksort(arr)
   quicksort(less_piviot) + pivot + quicksort(greater_pivot)

   * Base case:
   if (arr_size < 2) i.e array of element 1 or 0 then return array
*/

#include <stdio.h>

void quick_sort(int *arr, int size)
{
    if (size < 2) // if the element in the array is either 0 or 1 then just return the array base case
	return ;
    else
	{
	    int pivot = arr[0]; // pivot as the first element
	    int size_left_pivot = 0, size_right_pivot = 0;
	    int left_pivot_arr[size - 1], right_pivot_arr[size - 1];
	    
	    for (int i = 1; i < size; i++) // loop to separte right and left element from pivot
		{
		    if(arr[i] > pivot)
			{
			    right_pivot_arr[size_right_pivot] = arr[i]; // for right pivot element
			    size_right_pivot++;
			}
		    else if (arr[i] < pivot)
			{
			    left_pivot_arr[size_left_pivot] = arr[i]; // for left pivot element
			    size_left_pivot++;
			}
		}

	    quick_sort(left_pivot_arr, size_left_pivot); // sorting the left pivot
	    quick_sort(right_pivot_arr, size_right_pivot); // sorting the right pivot

	    int i;
	    for (i = 0; i < size_left_pivot; i++) // storing left pivoted array;
		arr[i] = left_pivot_arr[i]; 

	    arr[i] = pivot; // storing pivot
	    i++;

	    for (int j = 0; j < size_right_pivot; j++, i++)
		{
		    arr[i] = right_pivot_arr[j];
		}

	    return ;
	}
}
int main(void)
{
    int arr[] = {69, 67, 9, 11, 13, 7};
    quick_sort(arr, 6); // call to sorted array

    // printing sorted array
    for (int i = 0; i < 6; i++)
	printf("%i ",arr[i]);
    return 0;
}
