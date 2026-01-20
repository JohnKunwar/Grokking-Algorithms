#include <stdio.h>
// Binary Search: The efficiency of this search is (O) = log2(n)
/*
  
  Input:- array, number of element, element to be search(item)
  
  
  Output:- position of item in an array if not found -1
*/



int binary_search(int arr[], int n, int item)
{
    int high, low, mid, guess;

    high = n - 1;
    low = 0;

    while (low <= high)
	{
	    mid = (high + low) / 2;
	    guess = arr[mid];

	    if (guess == item)
		return mid;
	    else if (guess < item)
		low = mid + 1;
	    else
		high = high - 1;
	}
    
    return -1;
}


int main(void)
{
    int array[] = {1, 2, 3, 4, 5};
    int item, pos, size;
    size = sizeof(array)/ sizeof(int);
    
    printf("Enter your number: ");
    if (scanf("%i", &item) == 0)
	{
	    fprintf(stderr, "Can't read the input\n");
	    return 1;
	}

    pos = binary_search(array, size, item);
    if (pos != -1)
	printf("Position in the array: %i\n", pos);
    else
	printf("Not found on array\n");

    return 0;
}
