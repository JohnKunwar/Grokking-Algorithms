#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE  20
#define QUEUE_SIZE 40


// link list
struct link_list
{
    char *value;
    struct link_list *next;
};

// Queue data_structure
    
struct queue {
    int start;
    int end;
    
    char **arr;
};

void init_queue(struct queue *qu)
{
    qu->start = 0;
    qu->end = 0;

    qu->arr = (char**) calloc(QUEUE_SIZE, sizeof(char *));

    return ;
}

void enqueue(struct queue *qu, char *value)
{
    if (qu->end == QUEUE_SIZE)
	return;
    
    qu->arr[qu->end] = value;
    qu->end++;
    return;
}

char * dequeue(struct queue *qu)
{
    if (qu->start == qu->end)
	return NULL;
    
    return qu->arr[qu->start++];
}


// hash table with arrays as their values

// building block (every container of hashing is made by this)
struct node {
    char *key;
    char *value[HASH_SIZE];
    struct node *next;
    int size;
};

// setting up node
void setNode(struct node *nod, char *key, char *value, int index)
{
    nod->key = key;
    nod->value[index] = value;
    nod->next = NULL;
    nod->size = 1;
    
    return ;
}

// hashmap contains our hash_table
struct hashMap{
    int no_items, capacity;

    struct node **arr;
};

// initialization hasht-table to contain 100 elements
void hashmapInit(struct hashMap *mp)
{
    mp->no_items = 0;
    mp->capacity = 100;

    mp->arr = (struct node **) calloc(mp->capacity, sizeof(struct node *));

    return ;
}

// generates a number based on the character and prime numeber 31
int hashFunction(struct hashMap *mp, char *key)
{
    int factor = 31;
    int sum = 0;
    for (int i = 0; i < strlen(key); i++)
	{
	    sum = ((sum % mp->capacity) + ((key[i] % mp->capacity) * (factor % mp->capacity))) % mp->capacity;

	    factor = ((factor % __INT16_MAX__) * (31 % __INT16_MAX__)) % __INT16_MAX__;
	}

    return sum; // returns hash value
}

// Inserting a new node 
void hashInsert(struct hashMap *mp, char *key, char *value, int index)
{
    // creating a new node
    struct node *new = (struct node *) malloc(sizeof(struct node));


    int bucket_item = hashFunction(mp, key);
    // checking if same key exist or not if exit just updating
    struct node *curr = mp->arr[bucket_item];
    while (curr != NULL)
	{
	    if (strcmp(key, curr->key) == 0)
		{
		    curr->value[index] = value;
		    curr->size++;
		    return ;
		}
	    curr = curr->next;
	}
    
    //
    setNode(new, key, value, index);    
    if (mp->arr[bucket_item] == NULL)
	{
	    mp->arr[bucket_item] = new;
	}
    else // colliding item
	{
	    // adding node at the first of the base address
	    new->next = mp->arr[bucket_item];
	    mp->arr[bucket_item] = new;
	}
    
    return;
}

void hashRemove(struct hashMap *mp, char *key)
{
    int bucket_item = hashFunction(mp, key);
    struct node *curr = mp->arr[bucket_item];
    struct node *prev = NULL;

    while (curr != NULL)
	{
	    if (strcmp(key, curr->key) == 0)
		{
		    // head node deletion
		    if (curr == mp->arr[bucket_item])
			{
			    mp->arr[bucket_item] = curr->next;
			}
		    else
			{
			    prev->next = curr->next;			    
			}

		    break;
		}

	    prev = curr;
	    curr = curr->next;
	}
    
    free(curr);
    return ;
}

char * hashSearch(struct hashMap *mp, char * key, int index)
{
    int bucket_item = hashFunction(mp, key);
    struct node *curr = mp->arr[bucket_item];

    while (curr != NULL)
	{
	    if (strcmp(key, curr->key) == 0)
		return curr->value[index];

	    curr = curr->next;
	}

    return NULL;
}


int hashCount(struct hashMap *mp, char *key)
{
    if (hashSearch(mp, key, 0) == NULL)
	return 0;

    return mp->arr[hashFunction(mp, key)]->size;
}

// adds all value of key to the stack 
void add_graph_stack(struct hashMap * graph, struct queue * search_queue, char *key)
{
    int bucket = hashFunction(graph, key);
    struct node *curr = graph->arr[bucket];


    while (curr != NULL)
    {
        if (strcmp(curr->key, key) == 0)
            break;
        curr = curr->next;
    }

    if (curr == NULL)
        return;    

    for (int i = 0; i < curr->size; i++)
	enqueue(search_queue, hashSearch(graph, key, i));
    
}

_Bool search(struct link_list *list, char *key)
{
    while (list != NULL)
	{
	    if (strcmp(list->value, key) == 0)
		return 1;

	    list = list->next;
	}
    return 0;
}

struct link_list * new_link(char *value)
{
    struct link_list *point = (struct link_list *) malloc(sizeof(struct link_list));
    point->value = value;

    return point;
}

void add_link_list(struct link_list *begin, struct link_list *node)
{
    while(begin->next != NULL)
	begin = begin->next;

    node->next = NULL;
    begin->next = node;

}

char * breadth_search(struct hashMap *graph, char test)
{
    // Let's say I want to find the closest person who knows programming. That's where Breadth-search comes in
    // Breadth-search is the search that radiates out from a starting point in a graph. Whereas graph are just connection
    // It answers two types of question. Does the path exist and what is the shortest path.
    // Let's say the person who knows programming has the first letter of his name as 't'
    // Algorithm of Breadth-Search

    // Adding every out-neighbour from "you" to stack.
    struct queue search_queue;
    init_queue(&search_queue);
    add_graph_stack(graph, &search_queue, "you");

    struct link_list searched;
    searched.value = "you";
    searched.next = (struct link_list *) NULL;
    struct link_list *begin = &searched;
    
    char *c;
    while ((c = dequeue(&search_queue)) != NULL)
	{
	    // checking if it already has had been already searched
	    if (!search(begin, c))
		{
		    if(c[0] == test)
			{
			    return c;
			}
		    struct link_list *new = new_link(c);
		    add_link_list(begin, new);
		    begin = &searched;
		    
		    add_graph_stack(graph, &search_queue, c);
		}
	}

    return "not found";    
}
int main(void)
{

    // Example of Breadth Search
    
    // Initalization of Graph using hash. Let's say this is my friend list 
    //you -> [alice, bob, clarie]
    // And this is my friend's friend list
    //bob -> [anuj, peggy]
    //alice -> [peggy]
    //claire -> [jonny]
    
    struct hashMap graph;
    hashmapInit(&graph);
    
    hashInsert(&graph, "you", "alice", 0);
    hashInsert(&graph, "you", "bob", 1);
    hashInsert(&graph, "you", "claire", 2);

    hashInsert(&graph, "bob", "anuj", 0);
    hashInsert(&graph, "bob", "peggy", 1);

    hashInsert(&graph, "alice", "peggy", 0);

    hashInsert(&graph, "claire", "thom", 0);
    hashInsert(&graph, "claire", "jon", 1);

    printf("%s", breadth_search(&graph, 'j'));
      
    return 0;
}
