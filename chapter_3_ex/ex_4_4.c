// Binary search using recursive function

#include <stdio.h>


int binary_search(int *arr, int high, int low, int item)
{
    int mid = (high + low) / 2;
    if (low >= high)
	return -1;
    else
	{
	    if(arr[mid] == item)
		return mid;
	    else if(arr[mid] > item)
		return binary_search(arr, mid - 1, low, item);
	    else
		return binary_search(arr, high, mid + 1, item);
	}
}

int main(void)
{
    int arr[5] = {1, 2, 3, 4, 5};

    int pos = binary_search(arr, 5, 0, 5);
    printf("%i",pos);
    return 0;
}
