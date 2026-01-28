#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

// my implementation of tree(command from windows using breadth search) still buggy one though

#define SIZE_QUEUE 1024

// queue data structure for entry directory
struct queue {
    int front;
    int back;
    char *path[SIZE_QUEUE];
};

// initialize queue to default value
void init_queue(struct queue *q)
{
    q->front = 0;
    q->back = 0;
} 
// add to queue
void enqueue(struct queue *q, char *path)
{
    q->path[q->back] = path;
    q->back++;
    if (q->back > SIZE_QUEUE || q->front > SIZE_QUEUE)
	{
	    fprintf(stderr, "Try smaller directory\n");
	    exit(1);
	}
}
// read and remove from queue
char * dequeue(struct queue *q)
{
    if (q->front == q->back)
	{
	    q->front = 0;
	    q->back = 0;
	    return NULL;
	}
    
    char *path;
    path = q->path[q->front];
    q->front++;

    return path;
}


void printfilename(char *start)
{
    struct queue l_direct; // queue of directories
    init_queue(&l_direct);
    enqueue(&l_direct, start);
    
    char *next;
    while(next = dequeue(&l_direct)){
		printf("📁%s\n", next);
	
	struct dirent **entries; // scandir assigns array of entries
	int n; // scandir returns number of entries

	n = scandir(next, &entries, NULL, alphasort);
	if (n > 0)
	    {
		for(int i = 0; i < n; i++)
		    {
				if(strcmp(entries[i]->d_name,".") == 0 || strcmp(entries[i]->d_name,"..") == 0)
			    	{
						free(entries[i]);
						continue;
			    	}
			
			char *nextpath = malloc(strlen(entries[i]->d_name) + strlen(next) + 2);
			sprintf(nextpath, "%s/%s", next, entries[i]->d_name);
			if (entries[i]->d_type == DT_DIR)
			    {
					enqueue(&l_direct,nextpath);
			    }
			else
			    {
					printf("📃%s\n", entries[i]->d_name);
					free(nextpath);
			    }
			free(entries[i]);			
		    }
	    }
	free(entries);
    }
}

int main(void)
{
    printfilename(".");
    return 0;
}
