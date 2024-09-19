#include "Graph.h"

Graph newGraph(int n)
{
    Graph newGraph = (Graph)malloc(sizeof(GraphImp));
    
    newGraph->n = n;
    
    newGraph->adjacencyM = (int**)malloc(n * sizeof(int*));

    int r = 0;    
    for(r = 0; r < n; r++)
    {
        newGraph->adjacencyM[r] = (int*)malloc(n * sizeof(int));
        int c = 0;
        for(c = 0; c < n; c++)
        {
            newGraph->adjacencyM[r][c] = 0;
        }
    }
    
    return newGraph;    
}

void freeGraph(Graph g)
{
    int r = 0;
    
    for(r = 0; r < g->n; r++)
    {
        free(g->adjacencyM[r]);
    }
    
    free(g->adjacencyM);
    free(g);
}

void addEdge(Graph g, Edge e)
{
    g->adjacencyM[e.fromVertex][e.toVertex] = 1;
}

Edge firstAdjacent(Graph g, Vertex v)
{
    int c = 0;
    Edge e;
    
    for(c = 0; c < g->n; c++)
    {
        if(g->adjacencyM[v][c] == 1)
        {
            e.fromVertex = v;
            e.toVertex = c;
            return e;
        }
    }
    e.fromVertex = -1;
    e.toVertex = -1;
    
    return e;
}

Edge nextAdjacent(Graph g, Edge e)
{
    int c = 0;

    Edge newE;

    for(c = e.toVertex+1; c < g->n; c++)
    {
        if(g->adjacencyM[e.fromVertex][c] == 1) 
        {
            newE.fromVertex = e.fromVertex;
            newE.toVertex = c;
            return newE;
        }
    }
    newE.fromVertex = -1;
    newE.toVertex = -1;
    
    return newE;
}

void shortestPath(Graph g, Vertex start, Vertex destination)
{
    int i;
    Element temp;
    int parent[g->n];
    for(i = 0; i < g->n; i++) parent[i] = -1;

    BFS(g, start, parent);
    
    if(parent[destination] == -1)
    {
        printf("There is no path from %d to %d\n", start, destination);
        return;
    }
    
    Stack s = newStack(g->n);
    
    Vertex v;
    
    for(v = parent[destination]; v != start && s->count != s->maxSize; v = parent[v])
    {
        push(s, v);
    }
    
    printf("Shortest path from %d to %d: %d -> ", start, destination, start);
    
    while(isEmpty(s) == 0)
    {
        temp = pop(s);
        
        printf("%d -> ", temp);
    }
    printf("%d\n", destination);
    
    freeStack(s);
    
}

void BFS(Graph g, Vertex v, int *parent)
{
    int i;
    int visited[g->n];
    for(i = 0; i < g->n; i++) visited[i] = 0;

	  Queue q = newQueue();
	  enqueue(q,v);
	  visited[v] = TRUE;
	
	  Vertex currentVertex, tempVertex;
     Edge e;
     
    while(dequeue(q, &currentVertex))
    {		
        
		    for(e = firstAdjacent(g, currentVertex); e.toVertex != -1; e = nextAdjacent(g, e))
        {
	          tempVertex = e.toVertex;
   
			      if(visited[tempVertex] == FALSE)
			      {
				        enqueue(q,tempVertex);
				        visited[tempVertex] = TRUE;
                parent[tempVertex] = currentVertex;
			      }		
	      }		  
    }
}
