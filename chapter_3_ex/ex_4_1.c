#include <stdio.h>
// recursive function to find sum of element in an array 

int sum_arr(int *arr, int size)
{
    if (size == 0)
	return 0;
    else
	return arr[size - 1] + sum_arr(arr, size - 1);
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    int sum = sum_arr(arr, 5);

    printf("Sum is %i", sum);
    return 0;
}
