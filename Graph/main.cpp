#include "Graphs.cpp"
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int main()
{
  Graph<string> path;
  path.createGraph();
  path.PrintAdjacencyList();
  cout << endl;
  path.BFSTraversal();
  cout << endl;
  path.DFSTraversal();
  cout << endl;
  cout << "No of Nodes: " << path.nodes() << endl;
  cout << "No of Edges: " << path.edges() << endl;
  cout << "Undirected/Directed: " << path.direction() << endl;
  cout << "UnWeighted/Weighted: " << path.weightedGraph() << endl;
  cout << "Components in Graph: " << path.components() << endl;
  cout << "Topological Sort using DFS: ";
  path.TopologicalSortDFS();
  cout << endl;
  cout << "Topological Sort using BFS: ";
  path.TopologicalSortBFS(); // try to fix this algorithm if you can
  cout << endl;
  cout << "Is Cycle Present DFS: " << path.DetectCycleDFS();
  cout << endl;
  cout << "Is Cycle Present BFS: " << path.DetectCycleBFS(); // also try to fix this algorithm for directed graph
  cout << endl;
  // cout<<"Printing Indegree: "<<endl;
  // path.printInDegree();
  string src;
  // cout<<"Enter Node to find the Shortest Path (Dijkstra's Algorithm): ";
  // cin>>src;

  unordered_map<string, int> dist;
  // dist = path.SingleSourceShortestPath(src);
  // path.printShortestDistance(src, dist);
  // cout<<endl;

  vector<pair<string, string>> bridges;
  vector<string> articulationPoints;

  bridges = path.BridgesInGraph();
  path.printBridges(bridges);


  articulationPoints = path.ArticulationPointInGraph();
  path.printArticulationPoints(articulationPoints);

  cout<<"Enter Node to find the Shortest Path (BellmanFord Algorithm): ";
  cin>>src;

  dist = path.BellmanfordShortestPath(src);
  path.printShortestDistance(src, dist);
  cout<<endl;

  cout << "Is Negative Cycle Present BellmanFord: " << path.NegativeCycleDetection(src);
  cout<<endl;

  return 0;
}

// Graph Inputs  ^ (NOTE: 0 is not allowed in the graph node input)
// UnWeighted Graph
// 5 7 1 2 3 4 5 1 0 2 1 2 4 1 3 3 4 3 5 3 2 4 5 }-> Directed Graph
// 5 7 1 2 3 4 5 0 0 2 1 2 4 1 3 3 4 3 5 3 2 4 5 }-> Undirected Graph

// 5 9 1 2 3 4 5 1 0 1 4 1 5 2 3 2 5 3 1 3 4 4 2 4 1 5 3 }-> Directed Graph
// 5 8 1 2 3 4 5 0 0 1 5 2 3 2 5 3 1 3 4 4 2 4 1 5 3 }-> Undirected Graph

// 6 9 UK USA SINGAPORE CANADA ANTARCTICA GERMANY 1 0 UK USA SINGAPORE USA GERMANY UK GERMANY CANADA USA ANTARCTICA CANADA ANTARCTICA CANADA UK SINGAPORE GERMANY USA CANADA }-> Directed Graph
// 6 9 UK USA SINGAPORE CANADA ANTARCTICA GERMANY 0 0 UK USA SINGAPORE USA GERMANY UK GERMANY CANADA USA ANTARCTICA CANADA ANTARCTICA CANADA UK SINGAPORE GERMANY USA CANADA }-> Undirected Graph

// Directed Acyclic Graph
// 8 8 a b c d e f g h 1 0 a f a h f c c h h d e b e g b g }-> Directed Graph (DAG)

// Directed Weighted Acyclic Graph
// 8 8 a b c d e f g h 1 1 a f 6 a h 3 f c 2 c h 1 h d 5 e b 9 e g 4 b g 1 }-> Directed Graph

// UnDirected Weighted Cyclic Graph
// 8 8 a b c d e f g h 0 1 a f 6 a h 3 f c 2 c h 1 h d 5 e b 9 e g 4 b g 1 }-> UnDirected Graph

// 6 9 UK USA SINGAPORE CANADA ANTARCTICA GERMANY 1 1 UK USA -2 SINGAPORE USA -7 GERMANY UK 1 GERMANY CANADA 2 USA ANTARCTICA -4 CANADA ANTARCTICA -5 CANADA UK 6 SINGAPORE GERMANY 8 USA CANADA -3 }-> Weighted Directed Graph
// 6 9 UK USA SINGAPORE CANADA ANTARCTICA GERMANY 0 1 UK USA -2 SINGAPORE USA -7 GERMANY UK 1 GERMANY CANADA 2 USA ANTARCTICA -4 CANADA ANTARCTICA -5 CANADA UK 6 SINGAPORE GERMANY 8 USA CANADA -3 }-> Weighted Undirected Graph