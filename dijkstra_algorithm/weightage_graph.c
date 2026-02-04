#include <stdio.h>
#include <limits.h>
// the solution works. The result is store in the first row, last column as the shortest weight value
// solution for graph2.png
void printgraph(int arr[][6])
{
    printf("\nWeight Array\n");
    for (int i = 0; i < 5; i++)
	{
	    for (int j = 0; j < 6; j++)
		printf("%i ", arr[i][j]);

	    printf("\n");
	}
}
int main(void)
{
    // Initial table
    /*   A  B  C  D  E  F
A        U  5  2  M  M  M
B	 U  U  U  4  2  M
C	 U  8  U  M  7  M
D        U  U  U  U  6  3
E        U  U  U  U  U  7
F        U  U  U  U  U  U
    */
    int row = 5, col = 6;
    int weight_graph[5][6] = {0};
    weight_graph[0][0] = -1;  // A->A
    weight_graph[0][1] = 5;   // A -> B
    weight_graph[0][2] = 2;   // A -> C
    weight_graph[0][3] = 10000; // A -> D 
    weight_graph[0][4] = 10000;  // A -> E
    weight_graph[0][5] = 10000; // A -> F

    weight_graph[1][0]  = -1; // B -> A
    weight_graph[1][1]  = -1; // B -> B
    weight_graph[1][2]  = -1; // B -> C
    weight_graph[1][3]  = 4; // B -> D
    weight_graph[1][4]  = 2; // B -> E
    weight_graph[1][5]  = 10000; // B -> F

    weight_graph[2][0] = -1; // C -> A
    weight_graph[2][1] = 8; // C -> B
    weight_graph[2][2] = -1; // C -> C
    weight_graph[2][3] = 10000; // C -> D
    weight_graph[2][4] = 7; // C -> E
    weight_graph[2][5] = 10000; // C -> F

    weight_graph[3][0] = -1; // D -> A
    weight_graph[3][1] = -1; // D -> B
    weight_graph[3][2] = -1; // D -> C
    weight_graph[3][3] = -1; // D -> D
    weight_graph[3][4] = 6;  // D -> E
    weight_graph[3][5] = 3; // D -> F

    weight_graph[4][0] = -1; // E -> A
    weight_graph[4][1] = -1; // E -> B
    weight_graph[4][2] = -1; // E -> C
    weight_graph[4][3] = -1; // E -> D
    weight_graph[4][4] = -1; // E -> E
    weight_graph[4][5] = 7; // E -> F

    printgraph(weight_graph); // prints the initial graph

    // Implementating weightage graph by Dijkistra algorithm
    int prev_value = -1; 
    for (int i = 0; i < col - 1; i++)
	{
	    // finding the lowest from first row
	    int lowest = 10000, index; // where index is the index
	    for (int j = 0; j < col - 1; j++)
		{
		    if (weight_graph[0][j] < lowest && weight_graph[0][j] > prev_value)
			{
			    lowest = weight_graph[0][j];
			    index = j;
			}
		}
	    prev_value = lowest;pppp
	    

	    for (int k = 0; k < col; k++)
		{
		    if (weight_graph[index][k] != -1) // not equal to U 
			{
			    int sum = weight_graph[index][k] + lowest;

			    if (sum < weight_graph[0][k]) // updating the node value of of first row
				{
				    weight_graph[0][k] = sum;
				}
			}
		}
	    
	}

    printgraph(weight_graph);

    printf("Therefore the shortest part from A to F takes %i unit.\n", weight_graph[0][5]);
    return 0;
}

