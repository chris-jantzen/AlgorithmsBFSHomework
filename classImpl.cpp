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
  int maximum(int depths[]);

public:
  Graph(int numV); // numV is number of vertices
  void buildAdjacencyMatrix(int pairs[]);
  /**** Not sure what the return value needs to be ****/
  int* BFS(int v); // v is starting point
  int diameter();
  int** Component();

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
  // printAdjMatrix();
}

int* Graph::BFS(int v) {
  // List of "visited" booleans for each vertex
  bool *visited = new bool[this->numV];
  for (int i=0; i<this->numV; i++) {
    visited[i] = false;
  }

  std::queue<int> bfsQ;
  int distance[this->numV];
  distance[v] = 0;

  visited[v] = true;
  bfsQ.push(v);

  while(!bfsQ.empty()) {
    v = bfsQ.front();
    // std::cout << v << " ";
    // showQ(bfsQ);
    bfsQ.pop();

    for (int i=0; i<this->numV; i++) {
      if((adjacencyMatrix[v][i] == 1) && !visited[i]) {
        visited[i] = true;
        bfsQ.push(i);
        distance[i] = distance[v]+1;
      }
    }
  }

  // std::cout << "\n";
  // for(int i=0; i<this->numV; i++) {
  //   std::cout << distance[i] << " ";
  // }
  // std::cout << "\n";
  
  int depth = 0;
  for (int i=0; i<this->numV; i++) {
    if (visited[i] == false) {
      depth = -1;
    }
  }
  depth = maximum(distance);

  int* set;
  int numVisited = 0;
  for (int i=0; i<this->numV; i++) {
    if(visited[i] == true) numVisited++;
  }
  set = new int[numVisited + 2];
  int index = 1;
  int numberCheckingIfVisited = 0;
  while(index < numVisited+1) {
    if(visited[numberCheckingIfVisited] == true) {
      set[index++] = numberCheckingIfVisited;
    }
    numberCheckingIfVisited++;
  }
  set[0] = numVisited;
  set[numVisited+1] = depth;
  return set;
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
  int *temp;
  int index = 0;
  for (int i=0; i<this->numV; i++) {
    temp = BFS(i);
    arr[i] = temp[temp[0]+1];
    if (arr[i] < 0) {
      return -1;
    } else if (arr[i] > this->numV) {
      return -1;
    }
  }
  for (int i=0; i<this->numV; i++) {
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
  return maximum(arr);
}

int** Graph::Component() {
  int** sets;
  sets = new int*[this->numV]; // max space needed if only individual nodes

  sets[0] = BFS(0);
  if (sets[0][0] == this->numV) {
    return sets;
  }

  bool *visited = new bool[this->numV];
  for (int i=0; i<this->numV; i++) {
    visited[i] = false;
  }
  for (int i=0; i<this->numV; i++) {
    visited[sets[0][i]] = true;
  }

  for (int i=0; i<this->numV; i++) {
    if(visited[i] == true) {
      std::cout << "t ";
    } else {
      std::cout << "f ";
    }
  }
  std::cout << "\n";

  int setsIndex = 1;
  while (true) {
    for (int i=1; i<sets[0][0]+1; i++) {
      if (!visited[i]) {
        sets[setsIndex] = BFS(i);
        continue;
      }
    }
    break;
  }
  return sets;
}

int main() {
  int n = 6;
  // int arr[] = {4, 0, 1, 0, 2, 1, 2, 2, 3, -1};
  int arr[] = {5, 0, 1, 0, 2, 1, 5, 2, 3, 3, 5, -1};
  Graph *g = new Graph(n);
  g->buildAdjacencyMatrix(arr);
  int *set = g->BFS(3);
  int maxDepth = g->diameter();
  std::cout << maxDepth << std::endl;
  int **a = g->Component();
  return 0;
}
