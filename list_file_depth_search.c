#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void printfilename(char *start)
{
	printf("📁%s\n", start);
	struct dirent **entries; // scandir assigns array of entries
	int n; // scandir returns number of entries

	n = scandir(start, &entries, NULL, alphasort);
	if (n > 0)
	    {
		for(int i = 0; i < n; i++)
		    {
			if(strcmp(entries[i]->d_name,".") == 0 || strcmp(entries[i]->d_name,"..") == 0)
			    {
				free(entries[i]);
				continue;
			    }
			
			char *nextpath = malloc(strlen(entries[i]->d_name) + strlen(start) + 2);
			sprintf(nextpath, "%s/%s", start, entries[i]->d_name);
			if (entries[i]->d_type == DT_DIR)
			    {
				printfilename(nextpath);
				free(nextpath);
			    }
			else
			    {
				printf("\t📃%s\n", entries[i]->d_name);
				free(nextpath);
			    }
			free(entries[i]);			
		    }
	    }
	free(entries);
}

int main(void)
{
    printfilename(".");
    return 0;
}
