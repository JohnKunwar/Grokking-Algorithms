//  Write a recursive function to find the maximum number in a list.

#include <stdio.h>


int find_maximum(int *arr, int size, int max)
{
    if (size == 0)
	return max;
    else
	{
	    if (arr[size - 1] > max)
		return find_maximum(arr, size - 1, arr[size - 1]);
	    return find_maximum(arr, size - 1, max);
	}
    
}
int main(void)
{
    int arr[] = {1, 5, 6, 2, 1};
    int maxim = find_maximum(arr, 5, arr[0]);

    printf("%i\n", maxim);
}
