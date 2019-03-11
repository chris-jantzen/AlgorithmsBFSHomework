/**
 * Group 13
 * Christopher Jantzen
 * Christopher Messmer
 * Nicholas Hemminger
 */

#include <iostream>
#include <queue>

class Graph {
private:
  int numV;
  int **adjacencyMatrix;
public:
  /* Can probably remove need for numV by pulling it from pairs[] */
  Graph(int numV); // numV is number of vertices
  int** buildEdges(int pairs[]); // Array with number of pairs
  void buildAdjacencyMatrix(int **edges);
  void BFS(int v); // v is starting point
};

Graph::Graph(int numV) {
  this->numV = numV;
}

int** Graph::buildEdges(int pairs[]) {
  int** edges = 0;
  edges = new int*[pairs[0]];

  int index = 1;
  int edgesIndex = 0;
  while(true) {
    if (pairs[index] == -1) {
      break;
    } else {
      edges[edgesIndex] = new int[2];
      edges[edgesIndex][0] = pairs[index];
      edges[edgesIndex][1] = pairs[index+1];
      edgesIndex++;
    }
    index += 2;
  }
  return edges;
}

void Graph::buildAdjacencyMatrix(int **edges) {
  int** aMatrix = 0;
  aMatrix = new int*[this->numV];

  for (int i=0; i<this->numV; i++) {
    aMatrix[i] = new int[this->numV];
    for (int j=0; j<this->numV; j++) {
      aMatrix[i][j] = 0;
    }
  }

  for (int i=0; i<this->numV; i++) {
    aMatrix[edges[i][0]][edges[i][1]] = 1;
    aMatrix[edges[i][1]][edges[i][0]] = 1;
  }

  this->adjacencyMatrix = aMatrix;
}

void Graph::BFS(int v) {
  // List of "visited" booleans for each vertex
  bool *visited = new bool[this->numV];
  for (int i=0; i<this->numV; i++) {
    visited[i] = false;
  }

  std::queue<int> bfsQ;

  visited[v] = true;
  bfsQ.push(v);

  while(!bfsQ.empty()) {
    v = bfsQ.front();
    std::cout << v << " ";
    bfsQ.pop();

    for (int i=0; i<this->numV; i++) {
      if(!visited[i]) {
        visited[i] = true;
        bfsQ.push(i);
      }
    }
  }
}

int main() {
  int arr[] = {4, 0, 1, 0, 2, 1, 2, 2, 3, -1};
  Graph *g = new Graph(arr[0]);
  int** graph = g->buildEdges(arr); // Combine these two later
  g->buildAdjacencyMatrix(graph);
  g->BFS(0);

  return 0;
}
