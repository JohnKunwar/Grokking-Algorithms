// my implementation sets data structure
// Set is a collection of unique data item of same kind.
// for my problem I want to create set of string
// And perform the basic operation like intersection, union, printing array.

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// link list heart of set
struct link_list {
    char *value;
    struct link_list *next; 
};

void insert_set (struct link_list *set, int count, ...);  // function to insert element in set
void init_set(struct link_list *set);  // should run whenever you want to create new set
void print_set (struct link_list *set); // print the element in set
void remove_set (struct link_list *set, int count,...); // remove a element from set
void union_set (spptruct link_list *set1, struct link_list *set2, struct link_list *set3); // performs AUB 
void intersection_set(struct link_list *set1, struct link_list *set2, struct link_list *set3);// performs A intersection B
void difference_set(struct link_list *set1, struct link_list *set2, struct link_list *set3); // performs A - B 

int main(void)
{
    struct link_list car, bike, vehicle, both, only_bike;
    init_set(&car);
    init_set(&bike);
    init_set(&vehicle);
    init_set(&both);
    init_set(&only_bike);

    insert_set(&car,4, "bmw", "lambogrini", "tesla", "suzuki");
    insert_set(&bike, 3,"honda", "tvs", "suzuki");
    
    printf("Car: ");
    print_set(&car);
    printf("\n");
    
    printf("Bike: ");
    print_set(&bike);
    printf("\n");

    union_set(&car, &bike, &vehicle);
    printf("Car U Bike: ");
    print_set(&vehicle);
    printf("\n");
    
    printf("Car intersectin Bike: ");
    intersection_set(&car, &bike, &both);
    print_set(&both);
    printf("\n");

    printf("Car - Bike:");
    difference_set(&car, &bike, &only_bike);
    print_set(&only_bike);
    
    return 0;
}

void difference_set(struct link_list *set1, struct link_list *set2, struct link_list *set3)
{
    struct link_list *tmp = set2;

    // check if set1 element is not present in set2
    while(set1 != NULL)
	{
	    bool found = false;
	    while (tmp != NULL)
		{
		    if (strcmp(tmp->value, set1->value) == 0)
			{
			    found = true;
			    break;
			}
		    
		    tmp = tmp->next;
		}
	    if (!found)
		{
		    insert_set(set3, 1, set1->value);
		}
	    set1 = set1->next;
	    tmp = set2;
	}
}

void intersection_set(struct link_list *set1, struct link_list *set2, struct link_list *set3)
{
    struct link_list *tmp = set2;

    // check if set1 element is present in set2
    while(set1 != NULL)
	{
	    while (tmp != NULL)
		{
		    if (strcmp(tmp->value, set1->value) == 0)
			{
			    insert_set(set3, 1, tmp->value);
			    break;
			}
		    
		    tmp = tmp->next;
		}
	    
	    set1 = set1->next;
	    tmp = set2;
	}
}


void union_set (struct link_list *set1, struct link_list *set2, struct link_list *set3)
{
    // adds set1 element
    while (set1 != NULL)
	{
	    insert_set(set3, 1, set1->value);
	    set1 = set1->next;
	}
    // adds set2 element
    while (set2 != NULL)
	{
	    insert_set(set3, 1, set2->value);
	    set2 = set2->next;
	}
}

void remove_set (struct link_list *set,int count, ...)
{

    va_list args;
    va_start(args, count);
    
    for(int i = 0; i < count; i++) // loops every data input
	{
	    char *curr = va_arg(args, char *);
	    struct link_list *prev = set;
	    struct link_list *next = set;

	    // loops to check if the element is present in set or if it's it removes from set
	    while (next != NULL)
		{

		    if (strcmp(next->value, curr) == 0)
			{
			    prev->next = next->next;
			    free(next);
			    break;
			}
		    prev = next;
		    next = next->next;
		}
	}
}

void print_set (struct link_list *set)
{
    // simple loop to print all the element of set
    while (set != NULL)
	{
	    printf("%s ", set->value);
	    set = set->next;
	}
}

void init_set(struct link_list *set)
{    // initialize set. I don't know what to do with first element so i just deafulted it :P 
    set->value = "";
    set->next = NULL;
}

void insert_set (struct link_list *set,int count, ...)
{
    va_list args;
    va_start(args, count);
    
    char *curr;
    _Bool is_found = 0;
    struct link_list *next = set;
    // loops runs to every argument and insert element but not does not input duplicate
    for (int i = 0; i < count; i++)
    {
	curr = va_arg(args, char *);
	next = set;
	is_found = 0;
	while(next != NULL)
	    {
		if(strcmp(curr, next->value) == 0)
		    {
			is_found = 1;
			break;
		    }
		next = next->next;
	    }
	
	if (is_found == 0)
	    {
		struct link_list *new = (struct link_list *) malloc(sizeof(struct link_list));
		new->value = curr;
		new->next = set->next;
		set->next = new;
	    }

    }
    
    va_end(args);
}
