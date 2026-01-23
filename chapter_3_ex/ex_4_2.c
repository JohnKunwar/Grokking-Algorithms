// Write a recursive function to count the number of items in a list

#include <stdio.h>


struct link_list {
    int value;
    struct link_list *next;
};

int count_element(struct link_list *next_list)
{
    if (next_list ==  NULL)
	return 0;
    else
	return 1 + count_element(next_list->next);
}

int main()
{
    struct link_list l1, l2, l3;
    struct link_list *begin;
    begin = &l1;
    
    l1.value = 1;
    l1.next = &l2;

    l2.value = 2;
    l2.next = &l3;

    l3.value = 3;
    l3.next = NULL;

    int no_element = count_element(begin);
    printf("Number of element: %i", no_element);
    return 0;
}
