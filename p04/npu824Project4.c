#include "Graph.h"


int main()
{
    FILE* fileIn = fopen("p4Input.txt", "r");
    char buffer[1024];
    int sizeOfGraph;
    int numRuns;
    int i;
    Edge e;

    fgets(buffer, 1024, fileIn);
    sscanf(buffer, "%d", &sizeOfGraph);

    Graph g = newGraph(sizeOfGraph);

    fgets(buffer, 1024, fileIn);
    sscanf(buffer, "%d", &numRuns);
    
    

    for(i = 0; i < numRuns; i++)
    {
        fgets(buffer, 1024, fileIn);
        sscanf(buffer, "%d %d", &e.fromVertex, &e.toVertex);
        addEdge(g, e);
    }
    
    
    fgets(buffer, 1024, fileIn);
    sscanf(buffer, "%d", &numRuns);


    for(i = 0; i < numRuns; i++)
    {
        fgets(buffer, 1024, fileIn);
        char temp[1024];
        int s, d;
        sscanf(buffer, "%s %d %d", temp, &s, &d);
        shortestPath(g, s, d);
    }

    freeGraph(g);
    return 0;
}
