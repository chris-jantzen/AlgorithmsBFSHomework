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
  // int** getCountSecondVals(int **edges, int numPairs);
  // int **countSecondVals;

public:
  Graph(int numV); // numV is number of vertices
  void buildAdjacencyMatrix(int pairs[]);
  /**** Not sure what the return value needs to be ****/
  void BFS(int v); // v is starting point
  int diameter();

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

  // void printCountArr() {
  //   for (int i=0; i<this->numV; i++) {
  //     std::cout << countSecondVals[i][0] << " ";
  //   }
  //   std::cout << "\n";
  // }
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

  // this->countSecondVals = getCountSecondVals(edges, pairs[0]);
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
    // std::cout << v << " ";
    showQ(bfsQ);
    bfsQ.pop();

    for (int i=0; i<this->numV; i++) {
      if((adjacencyMatrix[v][i] == 1) && !visited[i]) {
        visited[i] = true;
        bfsQ.push(i);
      }
    }
  }
  std::cout << "\n";
}

// int** Graph::getCountSecondVals(int **edges, int numPairs) {
//   int **countSeconds;
//   countSeconds = new int*[this->numV];
//   for (int i=0; i<this->numV; i++) {
//     countSeconds[i] = new int[1];
//   }

//   for (int i=0; i<this->numV; i++) {
//     countSeconds[i][0] = 0;
//   }

//   for (int i=0; i<numPairs; i++) {
//     countSeconds[edges[i][0]][0]++;
//   }

//   return countSeconds;
// }

int main() {
  int n = 6;
  // int arr[] = {4, 0, 1, 0, 2, 1, 2, 2, 3, -1};
  int arr[] = {5, 0, 1, 0, 2, 1, 5, 2, 3, 3, 4, -1};
  Graph *g = new Graph(n);
  g->buildAdjacencyMatrix(arr);
  g->BFS(3);

  return 0;
}
