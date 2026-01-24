// my ugly implementation of hash
// hash table in a simple sense is array of link_list that contain (key:value) which in ideal condition gives instant result.

/*
  Has lots and lots of loopwhole everywhere. Has the basic function like insert,remove and search. Also update the
  duplication apart from that it's of bare minimum. It doesn't check whether remove key is valid or not.
  I will be back.

  But it works very fine though.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// building block (every container of hashing is made by this)
struct node {
    char *key;
    char *value;
    struct node *next;
};

// setting up node
void setNode(struct node *nod, char *key, char *value)
{
    nod->key = key;
    nod->value = value;
    nod->next = NULL;

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
void hashInsert(struct hashMap *mp, char *key, char *value)
{
    // creating a new node
    struct node *new = (struct node *) malloc(sizeof(struct node));
    setNode(new, key, value);

    int bucket_item = hashFunction(mp, key);
    // checking if same key exist or not if exit just updating
    struct node *curr = mp->arr[bucket_item];
    while (curr != NULL)
	{
	    if (strcmp(key, curr->key) == 0)
		{
		    curr->value = value;
		    return ;
		}
	    curr = curr->next;
	}
    
    // 
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

char * hashSearch(struct hashMap *mp, char * key)
{
    int bucket_item = hashFunction(mp, key);
    struct node *curr = mp->arr[bucket_item];

    while (curr != NULL)
	{
	    if (strcmp(key, curr->key) == 0)
		return curr->value;

	    curr = curr->next;
	}

    return "Not found";
}

int main(void)
{
    struct hashMap *prices;
    hashmapInit(prices);

    hashInsert(prices, "Chicken" , "350");
    hashInsert(prices, "Goat", "1000");
    hashInsert(prices, "Fish", "500");
    hashInsert(prices, "Rhino", "10000");

    hashRemove(prices, "Rhino");
    
    printf("Price of chicken is %s\n", hashSearch(prices, "Chicken"));
    printf("Price of Goat is %s\n", hashSearch(prices, "Goat"));
    printf("Price of Fish is %s\n", hashSearch(prices, "Fish"));
    printf("Price of Rhino is %s\n", hashSearch(prices, "Rhino"));
    
    return 0;
}
