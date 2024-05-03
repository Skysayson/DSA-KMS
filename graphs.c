#include <stdio.h>
#include <stdlib.h>
#define MAX 9
#define INFINITE 0xFF
//Djikstra

typedef int graph[MAX][MAX]; //my graph

typedef enum {FALSE, TRUE} Boolean;

typedef struct node {
	int vertex;
	int edge;
	struct node *link;
}*adjList;

typedef struct {
	int vertex;
	int edge;
	Boolean visit;
}MST;

typedef adjList list[MAX];
 
void initAdjMatrix(graph G) 
{	
	int x, y;
	for(x = 0; x < MAX; x++) {
		for(y = 0; y < MAX; y++) {
			G[x][y] = INFINITE;
		}
	}
}

void floydAlgo(graph G) //Same as warshal but not boolean 
{
    int x,y,z;
    graph spMatrix;

    for(x = 0; x < MAX; x++) {
        for(y = 0; y < MAX; y++) {
            spMatrix[x][y] = G[x][y];
        }
    }

    for(x = 0; x < MAX; x++) {
        for(y = 0; y < MAX; y++) {
            for(z = 0; z < MAX; z++) {
                if(spMatrix[y][z] > spMatrix[y][x] + spMatrix[x][z]) {
					spMatrix[y][z] = spMatrix[y][x] + spMatrix[x][z];
				}
            }	
        }
    }

printf("\n----- FLOYDS - MATRIX -----\n");
    for (x = 0; x < MAX; x++) {
        printf("[ ");
        for (y = 0; y < MAX; y++) {
            printf("%11d ", spMatrix[x][y]);
        }
        printf("]\n");
    }
}

void warshalAlgo(graph G) 
{
    int x,y,z;
    int booleanMatrix[MAX][MAX];

    for(x = 0; x < MAX; x++) { //booleanMatrix init to false
        for(y = 0; y < MAX; y++) {
            booleanMatrix[x][y] = FALSE;
        }
    }

    for(x = 0; x < MAX; x++) { //booleanMatrix init to true
        booleanMatrix[x][x] = TRUE;
        for(y = 0; y < MAX; y++) {
            if(G[x][y] != INFINITE) {
                booleanMatrix[x][y] = TRUE;
            } 
        }
    } 

    for (x = 0; x < MAX; x++) {
        for (y = 0; y < MAX; y++) {
            for (z = 0; z < MAX; z++) {                     // checks if 1 and 1 and short circuits
                booleanMatrix[y][z] = booleanMatrix[y][z] || (booleanMatrix[y][x] && booleanMatrix[x][z]); 
            }
        }
    }

 printf("\n----- MATRIX -----\n");
    for (x = 0; x < MAX; x++) {
        printf("[ ");
        for (y = 0; y < MAX; y++) {
            printf("%11d ", booleanMatrix[x][y]);
        }
        printf("]\n");
    }
}

void primsAlgo(graph G, int startVertex)
{
	MST mySPT[MAX];
	int x, y, min, minIdx;
	
	for(x = 0; x < MAX; x++) { //Array initializes the SPT array to FALSE visted and edges to infinite
		mySPT[x].visit = FALSE;
		mySPT[x].edge = INFINITE;
	}
	
	mySPT[startVertex].edge = 0;
	mySPT[startVertex].vertex = -1;
	
	
	for(x = 0; x < MAX; x++) { //Traverses MAX nodes so MAX iterations
		min = INFINITE; 	   //Set our min value to INFINITE and minIdx - 1
		minIdx = -1;
		
		for(y = 0; y < MAX; y++) { //To find from starting vertex
			if(mySPT[y].visit == FALSE && mySPT[y].edge < min) {
				min = mySPT[y].edge;
				minIdx = y;
			}
		}
		
		if(minIdx == -1) {
			x = MAX;
		}
		
		mySPT[minIdx].visit = TRUE; //Mark minIdx as visited in this case we marked the startIndex as visited
		
		for(y = 0; y < MAX; y++) { //For loop to find adjacent min edge
			if(G[minIdx][y] && mySPT[y].visit == FALSE && G[minIdx][y] < mySPT[y].edge) {
				mySPT[y].edge = G[minIdx][y];
				mySPT[y].vertex = minIdx;
			}
		}
	}
    printf("Minimum Spanning Tree (MST) from vertex %d:\n", startVertex);
    printf("Edge \tWeight\n");
    int total = 0;
    for (x = 1; x < MAX; x++) {
        if(mySPT[x].edge != INFINITE) {
            printf("%d - %d \t%d\n", mySPT[x].vertex, x, mySPT[x].edge);
            total += mySPT[x].edge;
        }
    }
    printf("TOTAL WEIGHT: %d", total);
}

void insertGraph(graph G, int x, int y,int weight)                                                  
{
	G[x][y] = weight;
}

void displayAdjMatrix(graph G) 
{
	int x, y;
	for(x = 0; x < MAX; x++) {
		printf("INDEX %d :: ", x);
		for(y = 0; y < MAX; y++) {
			if(G[x][y] == INFINITE) {
				printf("%c ", 'x');
			} else {
				printf("%d ", G[x][y]);
			}
		}
		printf("\n");
	}	
}

void djikstraAlgo(graph G, int startVertex) 
{
	int visited[MAX]; //Bit-vector array for checking if visited
	int SP[MAX], x, y, z; //Holds the distances
	
	int minIdx, min;
	for(x = 0; x < MAX; x++) {
		SP[x] = INFINITE;
		visited[x] = 0;
	}
	
	
	SP[startVertex] = 0;
	
	for(x = 0; x < MAX; x++) {
		min = INFINITE, minIdx = 0;
		for(y = 0; y < MAX-1; y++) {
			if(!visited[y] && SP[y] < min) {
				min = SP[y];
				minIdx = y;
			}
		}
		visited[minIdx] = 1;
		
		for(z = 0; z < MAX; z++) {
			if(!visited[z] && G[minIdx][z] != INFINITE && G[minIdx][z] + SP[minIdx] < SP[z]) {
				SP[z] = G[minIdx][z] + SP[minIdx];
			}
		}
	}
	
	printf("Minimum Spanning Tree (MST) from vertex %d:\n", startVertex);
    printf("Edge \tWeight\n");
    for (x = 0; x < MAX; x++) {
        if (SP[x] != INFINITE) {
            printf("%d - %d \t%d\n", minIdx, x, SP[x]);
        }
	}
}

void initAdjList(list *A) 
{
	int x;
	for(x = 0; x < MAX; x++) {
		(*A)[x] = NULL;
	}
}

list *convertToList(graph G) 
{
	int x, y;
	list *retList = (list*)malloc(sizeof(list)*MAX);
	adjList *trav, newNode;
	initAdjList(retList);
	
	for(x = 0; x < MAX; x++) {
		for(y = 0; y < MAX; y++) {
			for(trav = &(*retList)[x]; (*trav) != NULL && (*trav)->edge < G[x][y]; trav = &(*trav)->link) {}
				if(G[x][y] != INFINITE) {
					newNode = (adjList)malloc(sizeof(struct node));
					newNode->edge = G[x][y];
					newNode->vertex = y;
					newNode->link = (*trav);
					(*trav) = newNode;
				} else {
					trav = &(*trav)->link;
				} 
		}
	}
	return retList;	
}

void displayList(list A) {
	int x;
	adjList trav;
	printf("ADJ MATRIX TO ADJ LIST\n");
	printf("--------------------------------------------------------------------------------------------------------------------\n\n");
	for(x = 0; x < MAX; x++) {
		printf("NODE: %d", x);
		for(trav = A[x]; trav != NULL; trav = trav->link) {
			printf(" weight: %d - vertex: %d ", trav->edge, trav->vertex);
		}
		printf("\n\n");
	}
	printf("--------------------------------------------------------------------------------------------------------------------\n\n");
}

int main() 
{
	graph myGraph;
	list *myList;
	initAdjMatrix(myGraph);
    insertGraph(myGraph, 0, 1, 4);
    insertGraph(myGraph, 0, 7, 8);
    insertGraph(myGraph, 1, 2, 8);
    insertGraph(myGraph, 1, 7, 11);
    insertGraph(myGraph, 2, 3, 7);
    insertGraph(myGraph, 2, 8, 2);
    insertGraph(myGraph, 3, 4, 9);
    insertGraph(myGraph, 3, 5, 14);
    insertGraph(myGraph, 4, 5, 10);
    insertGraph(myGraph, 5, 6, 2);
    insertGraph(myGraph, 6, 8, 6);
    insertGraph(myGraph, 6, 7, 1);
    insertGraph(myGraph, 7, 0, 8);
    insertGraph(myGraph, 7, 6, 1);
    insertGraph(myGraph, 8, 2, 6);
    insertGraph(myGraph, 8, 7, 7);
//	displayAdjMatrix(myGraph);

	myList = convertToList(myGraph);
	displayList((*myList));
	
//  djikstraAlgo(myGraph, 0);
	primsAlgo(myGraph, 0);
    
    warshalAlgo(myGraph);    

    floydAlgo(myGraph);

	return 0;
}

