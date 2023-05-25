#include <iostream>

using namespace std;

class Graph 
{
private:
    int numVertices;
    int** adjacencyMatrix;

public:
    Graph(int numVertices) 
    {
        this->numVertices = numVertices;

        adjacencyMatrix = new int*[numVertices];
        for (int i = 0; i < numVertices; i++) 
        {
            adjacencyMatrix[i] = new int[numVertices];
            for (int j = 0; j < numVertices; j++) 
            {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    void addEdge(int src, int dest, int weight) 
    {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) 
        {
            adjacencyMatrix[src][dest] = weight;
        }
    }

    void removeEdge(int src, int dest) 
    {
        if (src >= 0 && src < numVertices && dest >= 0 && dest < numVertices) 
        {
            adjacencyMatrix[src][dest] = 0;
        }
    }

    void printGraph() 
    {
        for (int i = 0; i < numVertices; i++) 
        {
            for (int j = 0; j < numVertices; j++) 
            {
                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    ~Graph() 
    {
        for (int i = 0; i < numVertices; i++) 
        {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }
};

int main() 
{
    Graph graph(4);

    graph.addEdge(0, 1, 1);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 3);
    graph.addEdge(2, 3, 4);
    // graph.removeEdge(0,1);

    graph.printGraph();

    return 0;
}
