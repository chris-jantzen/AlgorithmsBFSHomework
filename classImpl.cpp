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
  int** buildEdges(int pairs[]); // Array with number of pairs

public:
  Graph(int numV); // numV is number of vertices
  void buildAdjacencyMatrix(int pairs[]);
  /**** Not sure what the return value needs to be ****/
  int BFS(int v); // v is starting point
  int diameter();

  int maximum(int depths[]);
  // Test methods
  void printAdjMatrix() {
    for (int i=0; i<this->numV; i++) {
      for (int j=0; j<this->numV; j++) {
        std::cout << this->adjacencyMatrix[i][j] << " ";
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }

  void showQ(std::queue<int> gq) {
    std::queue<int> g = gq; 
    while (!g.empty())
    { 
      std::cout << " " << g.front();
      g.pop(); 
    } 
    std::cout << '\n';
  }
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

void Graph::buildAdjacencyMatrix(int pairs[]) {
  int **edges = buildEdges(pairs);

  int** aMatrix = 0;
  aMatrix = new int*[this->numV];

  for (int i=0; i<this->numV; i++) {
    aMatrix[i] = new int[this->numV];
    for (int j=0; j<this->numV; j++) {
      aMatrix[i][j] = 0;
    }
  }

  for (int i=0; i<pairs[0]; i++) {
    aMatrix[edges[i][0]][edges[i][1]] = 1;
    aMatrix[edges[i][1]][edges[i][0]] = 1;
  }

  this->adjacencyMatrix = aMatrix;
  printAdjMatrix();
}

int Graph::BFS(int v) {
  // List of "visited" booleans for each vertex
  bool *visited = new bool[this->numV];
  for (int i=0; i<this->numV; i++) {
    visited[i] = false;
  }

  std::queue<int> bfsQ;
  int distance[this->numV];
  distance[v] = 0;
  int depth = 0;
  bool foundNew = false;

  visited[v] = true;
  bfsQ.push(v);

  while(!bfsQ.empty()) {
    v = bfsQ.front();
    // std::cout << v << " ";
    showQ(bfsQ);
    bfsQ.pop();
    depth++;

    for (int i=0; i<this->numV; i++) {
      if((adjacencyMatrix[v][i] == 1) && !visited[i]) {
        visited[i] = true;
        bfsQ.push(i);
        distance[i] = depth;
        foundNew = true;
      }
    }
    if (foundNew == false) {
      depth--;
    } else {
      foundNew = false;
    }
  }
  std::cout << "\n";

  for(int i=0; i<this->numV; i++) {
    std::cout << distance[i] << " ";
  }
  std::cout << "\n";

  return maximum(distance);
}

int Graph::maximum(int depths[]) {
  int greatest = depths[1];
  for (int i=0; i<this->numV; i++) {
    if (greatest < depths[i]) {
      greatest = depths[i];
    }
  }
  return greatest;
}

int Graph::diameter() {
  int arr[this->numV];
  for (int i=0; i<this->numV; i++) {
    arr[i] = BFS(i);
  }
  return maximum(arr);
}

int main() {
  int n = 6;
  // int arr[] = {4, 0, 1, 0, 2, 1, 2, 2, 3, -1};
  int arr[] = {5, 0, 1, 0, 2, 1, 5, 2, 3, 3, 4, -1};
  Graph *g = new Graph(n);
  g->buildAdjacencyMatrix(arr);
  int depth = g->BFS(3);
  int maxDepth = g->diameter();
  return 0;
}
