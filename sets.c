// my implementation sets data structure
// Set is a collection of unique data item of same kind.
// for my problem I want to create set of string
// And perform the basic operation like intersection, union, printing array.

// Try implementating multiple argument

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

// link list
struct link_list {
    char *value;
    struct link_list *next; 
};

void insert_set (struct link_list *set, int count, ...);
void init_set(struct link_list *set);
void print_set (struct link_list *set);
    
int main(void)
{
    struct link_list set;
    init_set(&set);

    insert_set(&set, 5, "john", "joseph", "jenna", "mohan", "mohan");
    print_set(&set);
    return 0;
}

void print_set (struct link_list *set)
{
    while (set != NULL)
	{
	    printf("%s ", set->value);
	    set = set->next;
	}
}

void init_set(struct link_list *set)
{    
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
