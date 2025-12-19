#include "Triplet.cpp"
#include "../Return-Nothing/ReturnNothing.cpp"
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <unordered_map>
using namespace std;

template <typename DataType>
class Graph
{
private:
  unordered_map<DataType, list<pair<DataType, int>>> AdjacencyList;
  unordered_map<DataType, bool> Components;
  unordered_map<DataType, int> InDegree;
  ReturnNothing<DataType> DefaultValues;
  vector<DataType> Keys;
  int Nodes;
  int Edges;
  bool Direction;
  bool WeightedGraph;
  int ComponentsCount;

  // Check the input if it is repeating in the adjacency list or not
  bool CheckInsertion(vector<triplet<DataType, DataType, int>> &mapping,
                      DataType first, DataType second)
  {
    if (mapping.empty())
    {
      return true;
    }

    triplet<DataType, DataType, int> temp;
    for (int i = 0; i < mapping.size(); i++)
    {
      temp = mapping[i];
      if (!this->Direction)
      {
        if (((temp.first == first) && (temp.second == second)) ||
            ((temp.first == second) && (temp.second == first)))
        {
          return false;
        }
      }
      else
      {
        if (((temp.first == first) && (temp.second == second)))
        {
          return false;
        }
      }
    }

    return true;
  }

  // Calculating Components in the graph
  void CalculateComponents()
  {
    int count = 0;
    for (auto it = this->InDegree.begin(); it != this->InDegree.end(); it++)
    {
      if (it->second == 0)
      {
        count++;
      }
    }

    if (!count)
    {
      this->ComponentsCount = 1;
    }
    else
    {
      this->ComponentsCount += count;
    }
  }

  void InitializeInDegree()
  {
    for (auto i : this->Keys)
    {
      if (!this->InDegree[i])
      {
        this->InDegree[i] = 0;
      }
    }
  }

  void CalculateInDegree()
  {
    DataType key;
    list<pair<DataType, int>> temp;
    for (auto it = this->AdjacencyList.begin(); it != this->AdjacencyList.end();
         it++)
    {
      temp = it->second;
      for (auto i : temp)
      {
        key = i.first;
        this->InDegree[key]++;
      }
    }
  }

  void UpdateInDegree(int start, int end)
  {
    DataType key;
    list<pair<DataType, int>> temp;
    while (start < end)
    {
      key = this->Keys[start];
      temp = this->AdjacencyList[key];
      for (auto i : temp)
      {
        this->InDegree[i.first]++;
      }
      start++;
    }
  }

  bool KeyCheck(DataType Key)
  {
    int i = 0;
    while (i < this->Keys.size())
    {
      if (this->Keys[i] == Key)
      {
        return true;
      }
      i++;
    }
    return false;
  }

  void BuildGraph(vector<triplet<DataType, DataType, int>> &mapping)
  {
    triplet<DataType, DataType, int> temp;
    for (int i = 0; i < mapping.size(); i++)
    {
      temp = mapping[i];
      this->AdjacencyList[temp.first].push_back(
          make_pair(temp.second, temp.third));

      if (!this->Direction)
      {
        this->AdjacencyList[temp.second].push_back(
            make_pair(temp.first, temp.third));
      }
    }
  }

  void PrintKeys()
  {
    int i = 0;
    cout << endl;
    cout << "Total Nodes: " << this->Nodes << endl;
    cout << "Nodes => ";

    while (i < this->Nodes)
    {
      cout << this->Keys[i] << " ";
      i++;
    }
    cout << endl
         << endl;
  }

  void GraphInput(int edgesCount)
  {
    vector<triplet<DataType, DataType, int>> container;
    triplet<DataType, DataType, int> temp;

    this->PrintKeys();

    int i = 1;
    while (i <= edgesCount)
    {
      cout << "Creating an Edge: (" << i << "/" << this->Edges << ")" << endl;
      cout << "From: ";
      cin >> temp.first;
      cout << "To: ";
      cin >> temp.second;

      if (this->WeightedGraph)
      {
        cout << "Weight: ";
        cin >> temp.third;
      }
      else
      {
        temp.third = 1;
      }

      if (!(this->KeyCheck(temp.first) && this->KeyCheck(temp.second)))
      {
        cout << endl
             << "Nodes are not Present" << endl;
        this->PrintKeys();
        continue;
      }

      if (CheckInsertion(container, temp.first, temp.second))
      {
        container.push_back(temp);
        i++;
      }
      else
      {
        cout << "Edge Already Exist's in Graph" << endl;
      }

      cout << endl;
    }

    this->BuildGraph(container);
  }

  void GetNodeValues(int nodesCount)
  {
    cout << endl;
    int i = 0;
    DataType Key;
    while (i < nodesCount)
    {
      cout << "Enter Name for Node " << (i + 1) << ": ";
      cin >> Key;
      if (this->KeyCheck(Key))
      {
        cout << endl
             << "Node Already Exist's in Graph" << endl;
        continue;
      }
      else
      {
        this->Keys.push_back(Key);
      }
      i++;
    }
  }

  void BFS(unordered_map<DataType, bool> &visited, DataType target)
  {
    queue<DataType> container;
    container.push(target);

    DataType key;
    list<pair<DataType, int>> temp;
    while (!container.empty())
    {
      key = container.front();
      container.pop();
      if (!visited[key])
      {

        cout << key << " ";
        visited[key] = true;

        temp = this->AdjacencyList[key];
        for (auto i : temp)
        {
          if (!visited[i.first])
          {
            container.push(i.first);
          }
        }
      }
    }
  }

  void DFS(unordered_map<DataType, bool> &visited, DataType key)
  {
    visited[key] = true;
    cout << key << " ";
    DataType element;
    list<pair<DataType, int>> l = this->AdjacencyList[key];
    for (auto it = l.begin(); it != l.end(); it++)
    {
      element = it->first;
      if (!visited[element])
      {
        this->DFS(visited, element);
      }
    }
  }

  void TopologicalDFS(unordered_map<DataType, bool> &visited,
                      stack<DataType> &series, DataType key)
  {
    visited[key] = true;

    DataType element;
    list<pair<DataType, int>> l = this->AdjacencyList[key];
    for (auto i : l)
    {
      element = i.first;
      if (!visited[element])
      {
        this->TopologicalDFS(visited, series, element);
      }
    }

    series.push(key);
  }

  void TopologicalBFS(unordered_map<DataType, bool> &visited,
                      vector<DataType> &series,
                      unordered_map<DataType, int> &inDegree, DataType key)
  {
    queue<DataType> container;
    DataType front;
    for (auto it = inDegree.begin(); it != inDegree.end(); it++)
    {
      if (it->second == 0)
      {
        container.push(it->first);
        inDegree[it->first] = -1;
      }
    }

    while (!container.empty())
    {
      front = container.front();
      container.pop();
      visited[front] = true;
      series.push_back(front);

      for (auto i : this->AdjacencyList[front])
      {
        inDegree[i.first]--;
        if (inDegree[i.first] == 0)
        {
          container.push(i.first);
          inDegree[i.first] = -1;
        }
      }
    }
  }

  // designed for main datatypes only like: int, char, string
  bool UndirectedCycleBFS(unordered_map<DataType, bool> &visited,
                          DataType key)
  {
    unordered_map<DataType, DataType> nodeToParent;
    queue<DataType> container;

    // this will not work, due to different datatype
    // try {
    //   nodeToParent[key] = "";
    // } catch (...) {
    //   nodeToParent[key] = 0;
    // }

    visited[key] = true;
    container.push(key);

    DataType front;
    DataType neighbour;
    while (!container.empty())
    {
      front = container.front();
      container.pop();

      for (auto i : this->AdjacencyList[front])
      {
        neighbour = i.first;
        if (visited[neighbour] && neighbour != nodeToParent[front])
        {
          return true;
        }
        else
        {
          if (!visited[neighbour])
          {
            visited[neighbour] = true;
            container.push(neighbour);
            nodeToParent[neighbour] = front;
          }
        }
      }
    }
    return false;
  }

  bool UndirectedCycleDFS(unordered_map<DataType, bool> &visited,
                          unordered_map<DataType, DataType> &nodeToParent,
                          DataType key)
  {
    // this will not work, due to different datatype
    // try {
    //   nodeToParent[key] = "";
    // } catch (...) {
    //   nodeToParent[key] = 0;
    // }

    visited[key] = true;

    DataType neighbour;
    for (auto i : this->AdjacencyList[key])
    {
      neighbour = i.first;
      if (visited[neighbour] && neighbour != nodeToParent[key])
      {
        return true;
      }
      else
      {
        if (!visited[neighbour])
        {
          return this->UndirectedCycleDFS(visited, nodeToParent, neighbour);
        }
      }
    }
    return false;
  }

  bool DirectedCycleDFS(unordered_map<DataType, bool> &visited, unordered_map<DataType, bool> &dfsVisited, DataType key)
  {
    visited[key] = true;
    dfsVisited[key] = true;

    DataType child;
    bool cycle = false;
    for (auto i : this->AdjacencyList[key])
    {
      child = i.first;
      if (visited[child] && dfsVisited[child])
      {
        return true;
      }
      else
      {
        if (!visited[child])
        {
          cycle = this->DirectedCycleDFS(visited, dfsVisited, child);
        }
      }
      if (cycle)
      {
        return true;
      }
    }

    dfsVisited[key] = false;
    return false;
  }

  // you do not need to check here if the node is visited or not, analyze it!!
  void DijkstrasAlgorithm(DataType src, unordered_map<DataType, int> &distance)
  {
    set<pair<int, DataType>> mapping;
    distance[src] = 0;
    mapping.insert(make_pair(0, src));

    DataType key;
    pair<int, DataType> top;
    while (!mapping.empty())
    {
      top = *(mapping.begin());
      key = top.second;

      for (auto i : this->AdjacencyList[key])
      {
        int dist = top.first + i.second;
        if (distance[i.first] > dist)
        {
          if (mapping.find(make_pair(distance[i.first], i.first)) != mapping.end())
          {
            mapping.erase(make_pair(distance[i.first], i.first));
          }

          distance[i.first] = dist;
          mapping.insert(make_pair(dist, i.first));
        }
      }
      mapping.erase(top);
    }
  }

  void UndirectedShortestPath(unordered_map<DataType, bool> &visited, unordered_map<DataType, DataType> &nodeToParent, DataType key)
  {
    visited[key] = true;

    queue<DataType> container;
    container.push(key);

    DataType front;
    while (!container.empty())
    {
      front = container.front();
      container.pop();

      for (auto i : this->AdjacencyList[key])
      {
        if (!visited[i.first])
        {
          nodeToParent[i.first] = front;
          container.push(i.first);
          visited[i.first] = true;
        }
      }
    }
  }

  // find shortest path/ negative cycle detection in a graph having negative edges
  // if you want to find shortest path then negative cycle should not present in graph
  void BellmanfordAlgorithm(DataType src, unordered_map<DataType, int> &distance)
  {
    distance[src] = 0;

    DataType source, destination;
    int weight;
    // Relax all edges V - 1 times
    for (int i = 0; i < this->Nodes; i++)
    {
      for (auto it = this->AdjacencyList.begin(); it != this->AdjacencyList.end(); it++)
      {
        source = it->first;
        for (auto i : it->second)
        {
          destination = i.first;
          weight = i.second;

          if (distance[source] != INT_MAX && (distance[source] + weight) < distance[destination])
          {
            distance[destination] = distance[source] + weight;
          }
        }
      }
    }
  }

  // Finding Bridges in the graph
  void FindBridge(unordered_map<DataType, int> &discovery, unordered_map<DataType, int> &low, DataType parent, unordered_map<DataType, bool> &visited, vector<pair<DataType, DataType>> &bridges, DataType key, int time = 0)
  {
    discovery[key] = time;
    low[key] = time;
    visited[key] = true;

    DataType element;
    for (auto it : this->AdjacencyList[key])
    {
      element = it.first;
      parent = key;

      if (!visited[element])
      {
        this->FindBridge(discovery, low, parent, visited, bridges, element, time + 1);
        low[key] = min(low[key], low[element]);

        if (low[element] > discovery[key])
        {
          bridges.push_back(make_pair(key, element));
        }
      }
      else
      {
        if (element == parent)
        {
          continue;
        }
        else
        {
          low[key] = min(low[key], discovery[element]);
        }
      }
    }
  }

  // Finding Articulation points in the graph
  void FindArticulationPoint(unordered_map<DataType, int> &discovery, unordered_map<DataType, int> &low, DataType parent, unordered_map<DataType, bool> &visited, vector<DataType> &articulationPoint, unordered_map<DataType, bool> &parentExistance, DataType key, int time = 0)
  {
    discovery[key] = time;
    low[key] = time;
    visited[key] = true;

    if (!parentExistance[key])
    {
      parentExistance[key] = false;
    }

    int childCount = 0;

    DataType element;
    for (auto it : this->AdjacencyList[key])
    {
      element = it.first;
      parentExistance[element] = true;
      parent = key;

      if (!visited[element])
      {
        this->FindArticulationPoint(discovery, low, parent, visited, articulationPoint, parentExistance, element, time + 1);
        low[key] = min(low[key], low[element]);

        if ((low[element] >= discovery[key]) && parentExistance[key])
        {
          articulationPoint.push_back(element);
        }

        childCount++;
      }
      else
      {
        if (element == parent)
        {
          continue;
        }
        else
        {
          low[key] = min(low[key], discovery[element]);
        }
      }
    }

    if (!parentExistance[key] && childCount > 1)
    {
      articulationPoint.push_back(key);
    }
  }

  // Prim's Algorithm starts here
  void DistanceDefaultInitialization(unordered_map<DataType, int> &distance)
  {
    for (int i = 0; i < this->Nodes; i++)
    {
      distance[this->Keys[i]] = INT_MAX;
    }
  }

  // less efficient, more efficient approach is using min-heap
  // mst is passed by reference because by using this variable we will return the MST values
  void FindMSTPrimsAlgorithm(DataType src, unordered_map<DataType, pair<DataType, int>> &mst)
  {
    unordered_map<DataType, int> distance;

    // initializing with default values in distance
    DistanceDefaultInitialization(distance);

    unordered_map<DataType, bool> visited;
    unordered_map<DataType, DataType> parent;

    DataType key;
    list<pair<DataType, int>> paths;

    distance[src] = 0;
    parent[src] = DefaultValues.DefaultValue();

    for (int i = 0; i < this->Nodes; i++)
    {
      key = this->Keys[i];
      paths = this->AdjacencyList[key];

      for (auto i : paths)
      {
        // Don't need to update the src distance
        if (i.first == src)
        {
          continue;
        }

        if (distance[i.first] > i.second)
        {
          distance[i.first] = i.second;
          parent[i.first] = key;
        }
      }
    }

    // Constructing MST from distance and parent array
    for (auto it = parent.begin(); it != parent.end(); it++)
    {
      if (it->first == src)
      {
        continue;
      }

      mst[it->second] = make_pair(it->first, distance[it->first]);
    }
  }

  // Kruskal's Algorithm starts here
  // We use two concepts here, 1): Union by Rank; 2): Path Compression

  // Try to understand it
  DataType FindParent(DataType node, unordered_map<DataType, DataType> &parent)
  {
    if (parent[node] == node)
    {
      return node;
    }

    return parent[node] = this->FindParent(parent[node], parent);
  }

  void UnionSet(unordered_map<DataType, int> &rank, unordered_map<DataType, DataType> &parent, DataType u, DataType v)
  {
    if (!(this->KeyCheck(u) && this->KeyCheck(v)))
    {
      return;
    }

    DataType uParent = this->FindParent(u, parent);
    DataType vParent = this->FindParent(v, parent);

    if (rank[uParent] < rank[vParent])
    {
      parent[uParent] = vParent;
    }
    else if (rank[uParent] > rank[vParent])
    {
      parent[vParent] = uParent;
    }
    else
    {
      parent[uParent] = vParent;
      rank[vParent]++;
    }
  }

  // this function will help to detect and not merge those two vertices which can create cycle while adding vertices in MST
  bool isSameComponent(DataType u, DataType v)
  {
    DataType uParent = this->FindParent(u);
    DataType vParent = this->FindParent(v);

    return (uParent == vParent);
  }

  void RankAndParentDefaultInitialization(unordered_map<DataType, int> &rank, unordered_map<DataType, DataType> &parent)
  {
    for (int i = 0; i < this->Nodes; i++)
    {
      rank[this->Keys[i]] = 0;
      parent[this->Keys[i]] = this->Keys[i];
    }
  }

  bool GraphVectorComparator(triplet<DataType, DataType, int> e1, triplet<DataType, DataType, int> e2){
    return (e1.third < e2.third);
  }

  void FindMSTKruskalsAlgorithm(unordered_map<DataType, list<pair<DataType, int>>> &mst)
  {
    unordered_map<DataType, int> rank;
    unordered_map<DataType, DataType> parent;

    this->RankAndParentDefaultInitialization(rank, parent);

    // format is u, v, w
    vector<triplet<DataType, DataType, int>> edgesContainer;
    DataType key;
    list<pair<DataType, int>> paths;

    // no need to do this if graph is stored in form of adjacency matrix and not adjacency list
    // because here we need a linear data structure
    int edgesContainerSize = 0;
    for(int i=0;i<this->Nodes;i++){
      key = this->Keys[i];
      paths = this->AdjacencyList[key];

      for(auto i: paths){
        edgesContainer[edgesContainerSize].make_triplet(key, i.first, i.second);
        edgesContainerSize++;
      }
    }

    sort(edgesContainer.begin(), edgesContainer.end(), this->GraphVectorComparator);

    triplet<DataType, DataType, int> element;
    for(int i=0;i<edgesContainerSize;i++){
      element = edgesContainer[i];

      if(!this->isSameComponent(element.first, element.second)){
        this->UnionSet(rank, parent, element.first, element.second);
        mst[element.first].push_back(make_pair(element.second, element.third));
      }
    }
  }

public:
  Graph()
  {
    this->Nodes = 0;
    this->Edges = 0;
    this->Direction = false;
    this->WeightedGraph = false;
    this->ComponentsCount = 0;
  }

  ~Graph()
  {
    this->Nodes = 0;
    this->Edges = 0;
    this->Direction = false;
    this->WeightedGraph = false;
    this->ComponentsCount = 0;
  }

  void createGraph()
  {
    // 0 for Undirected Graph && 1 for Directed Graph

    cout << "Enter the Number of Nodes (In Graph): ";
    cin >> this->Nodes;

    cout << "Enter the Number of Edges (In Graph): ";
    cin >> this->Edges;

    this->GetNodeValues(this->Nodes);
    this->InitializeInDegree();
    cout << endl;

    int choice;
    cout << "Enter the Type of Graph: " << endl;
    cout << "0): Undirected Graph" << endl;
    cout << "1): Directed Graph" << endl;
    cin >> choice;

    if (choice == 1)
    {
      this->Direction = true;
    }
    else
    {
      this->Direction = false;
    }
    cout << endl;

    cout << "Select From the Following: " << endl;
    cout << "0): UnWeighted Graph" << endl;
    cout << "1): Weighted Graph" << endl;
    cin >> choice;

    if (choice == 1)
    {
      this->WeightedGraph = true;
    }
    else
    {
      this->WeightedGraph = false;
    }

    this->GraphInput(this->Edges);
    this->CalculateInDegree();
    this->CalculateComponents();
  }

  void UpdateGraph()
  {
    cout << endl;
    int newNodes, newEdges;
    cout << "Enter the Number of Nodes (Graph Updation): ";
    cin >> newNodes;

    cout << "Enter the Number of Edges (Graph Updation): ";
    cin >> newEdges;

    this->GetNodeValues(newNodes);

    this->InitializeInDegree();

    this->GraphInput(newEdges);
    this->UpdateInDegree(this->Nodes, (this->Nodes + newNodes));
    this->CalculateComponents();

    this->Nodes += newNodes;
    this->Edges += newEdges;
  }

  void PrintAdjacencyList()
  {
    int i = 0;
    DataType key;
    list<pair<DataType, int>> temp;
    while (i < this->Nodes)
    {
      key = this->Keys[i];
      cout << key << " => ";
      if (this->AdjacencyList.find(key) != this->AdjacencyList.end())
      {
        temp = this->AdjacencyList.at(key);
        for (auto it = temp.begin(); it != temp.end(); it++)
        {
          if (this->WeightedGraph)
          {
            cout << "(" << it->first << ", " << it->second << ") ";
          }
          else
          {
            cout << it->first << " ";
          }
        }
      }
      cout << endl;
      i++;
    }
  }

  void BFSTraversal()
  {
    this->PrintKeys();
    cout << "BFS Traversal" << endl;

    DataType key;
    unordered_map<DataType, bool> visited;
    for (int i = 0; i < this->Nodes; i++)
    {
      key = this->Keys[i];
      if (!visited[key])
      {
        this->BFS(visited, key);
      }
    }
    cout << endl;
  }

  void DFSTraversal()
  {
    cout << "DFS Traversal" << endl;

    unordered_map<DataType, bool> visited;

    DataType key;
    for (int i = 0; i < this->Nodes; i++)
    {
      key = this->Keys[i];
      if (!visited[key])
      {
        this->DFS(visited, key);
      }
    }
    cout << endl;
  }

  void TopologicalSortDFS()
  {
    unordered_map<DataType, bool> visited;
    stack<DataType> series;

    for (auto i : this->Keys)
    {
      if (!visited[i])
      {
        this->TopologicalDFS(visited, series, i);
      }
    }

    while (!series.empty())
    {
      cout << series.top() << " ";
      series.pop();
    }
    cout << endl;
  }

  void TopologicalSortBFS()
  {
    unordered_map<DataType, int> inDegree = this->InDegree;
    unordered_map<DataType, bool> visited;
    vector<DataType> series;
    DataType key;

    for (int i = 0; i < this->Keys.size(); i++)
    {
      key = this->Keys[i];
      if (!visited[key])
      {
        this->TopologicalBFS(visited, series, inDegree, key);
      }
    }

    for (int i = 0; i < series.size(); i++)
    {
      cout << series[i] << " ";
    }
    cout << endl;
  }

  bool DetectCycleBFS()
  {
    if (!this->Direction)
    {
      unordered_map<DataType, bool> visited;

      bool cycle = false;
      for (auto key : this->Keys)
      {
        if (!visited[key])
        {
          cycle = this->UndirectedCycleBFS(visited, key);
        }
        if (cycle)
        {
          return true;
        }
      }
      return false;
    }
    else
    {
      vector<DataType> series;
      unordered_map<DataType, bool> visited;
      unordered_map<DataType, int> inDegree = this->InDegree;

      for (auto key : this->Keys)
      {
        if (!visited[key])
        {
          this->TopologicalBFS(visited, series, inDegree, key);
        }
      }

      unordered_map<DataType, int> counting;
      int i = 0;
      DataType key;
      while (i < series.size())
      {
        key = series[i];
        counting[key] = (i + 1);
        i++;
      }

      DataType value;
      for (auto it = this->AdjacencyList.begin(); it != this->AdjacencyList.end(); it++)
      {
        key = it->first;

        for (auto i : this->AdjacencyList[key])
        {
          value = i.first;
          if (!(counting[key] < counting[value]))
          {
            return true;
          }
        }
      }
      return false;
    }
  }

  bool DetectCycleDFS()
  {
    if (!this->Direction)
    {
      unordered_map<DataType, DataType> nodeToParent;
      unordered_map<DataType, bool> visited;

      bool cycle = false;
      for (auto key : this->Keys)
      {
        if (!visited[key])
        {
          cycle = this->UndirectedCycleDFS(visited, nodeToParent, key);
        }
        if (cycle)
        {
          return true;
        }
      }
      return false;
    }
    else
    {
      unordered_map<DataType, bool> visited;
      unordered_map<DataType, bool> dfsVisited;

      bool cycle = false;
      for (auto key : this->Keys)
      {
        if (!visited[key])
        {
          cycle = this->DirectedCycleDFS(visited, dfsVisited, key);
        }
        if (cycle)
        {
          return true;
        }
      }
      return false;
    }
  }

  void printArticulationPoints(vector<DataType> answer)
  {
    if (answer.empty())
    {
      cout << "No Articulation Point Exist's in the Graph" << endl;
      return;
    }

    cout << "Articulation Points in the Graph: " << endl;
    for (auto i : answer)
    {
      cout << i << " ";
    }
    cout << endl;
  }

  void printBridges(vector<pair<DataType, DataType>> answer)
  {
    if (answer.empty())
    {
      cout << "No Bridge Exist's in the Graph" << endl;
      return;
    }

    cout << "Bridges in the Graph: " << endl;
    for (auto i : answer)
    {
      cout << i.first << "->" << i.second << endl;
    }
  }

  // void printInDegree(){
  //   for(auto it = this->InDegree.begin();it != this->InDegree.end();it++){
  //     cout<<"Key: "<<it->first<<"InDegree: "<<it->second<<endl;
  //   }
  //   cout<<endl;
  // }

  void printShortestDistance(DataType src, unordered_map<DataType, int> &distance)
  {
    cout << "SRC: " << src << endl;
    for (auto it = distance.begin(); it != distance.end(); it++)
    {
      cout << "\"" << it->first << ": " << it->second << "\", ";
    }
  }

  unordered_map<DataType, int> BellmanfordShortestPath(DataType src)
  {
    if (!this->WeightedGraph)
    {
      cout << "Not a Weighted Graph!" << endl;
      return unordered_map<DataType, int>();
    }

    unordered_map<DataType, int> distance;

    if (!this->KeyCheck(src))
    {
      cout << "Key does not exist's in the Graph" << endl;
      distance[src] = -1;
      return distance;
    }

    for (auto key : this->Keys)
    {
      distance[key] = INT_MAX;
    }

    this->BellmanfordAlgorithm(src, distance);

    return distance;
  }

  bool NegativeCycleDetection(DataType src)
  {
    if (!this->WeightedGraph)
    {
      cout << "Not a Weighted Graph!" << endl;
      return false;
    }

    unordered_map<DataType, int> distance;

    for (auto key : this->Keys)
    {
      distance[key] = INT_MAX;
    }

    this->BellmanfordAlgorithm(src, distance);

    bool negativeCycle = false;
    DataType source, destination;
    int weight;
    for (auto it = this->AdjacencyList.begin(); it != this->AdjacencyList.end(); it++)
    {
      source = it->first;
      for (auto i : it->second)
      {
        destination = i.first;
        weight = i.second;

        if ((distance[src] + weight) < distance[destination])
        {
          return true;
        }
      }
    }

    return false;
  }

  vector<pair<DataType, DataType>> BridgesInGraph()
  {
    unordered_map<DataType, int> discovery;
    unordered_map<DataType, int> low;
    DataType parent;
    unordered_map<DataType, bool> visited;

    vector<pair<DataType, DataType>> bridges;
    for (auto key : this->Keys)
    {
      if (!visited[key])
      {
        this->FindBridge(discovery, low, parent, visited, bridges, key);
      }
    }

    return bridges;
  }

  vector<DataType> ArticulationPointInGraph()
  {
    unordered_map<DataType, int> discovery;
    unordered_map<DataType, int> low;
    unordered_map<DataType, bool> visited;
    unordered_map<DataType, bool> parentExistance;
    DataType parent;

    vector<DataType> articulationPoint;
    for (auto key : this->Keys)
    {
      if (!visited[key])
      {
        this->FindArticulationPoint(discovery, low, parent, visited, articulationPoint, parentExistance, key);
      }
    }

    return articulationPoint;
  }

  // also analyze:
  // what if path is not defined between src & dest
  // what if a child has more than one parents
  // what if a cycle is present
  // also analyze cycle detection algorithm
  // analyze visited node tracking in dijkstra's algorithm
  vector<DataType> UndirectedGraphShortestPath(DataType source, DataType destination)
  {
    if (!this->WeightedGraph)
    {
      cout << "Not a Weighted Graph!" << endl;
      return vector<DataType>();
    }

    unordered_map<DataType, bool> visited;
    vector<DataType> distance;
    unordered_map<DataType, DataType> nodeToParent;

    for (auto i : this->Keys)
    {
      if (!visited[i])
      {
        this->UndirectedShortestPath(visited, nodeToParent, i);
      }
    }

    DataType temp = destination;
    distance.pop_back(temp);

    while (temp != source)
    {
      temp = nodeToParent[temp];
      distance.push_back(temp);
    }

    reverse(distance.begin(), distance.end());

    return distance;
  }

  // can only applied on Directed Acyclic Graph (DAG)
  unordered_map<DataType, int> DirectedGraphShortestPath(DataType source)
  {
    if (!this->WeightedGraph)
    {
      cout << "Not a Weighted Graph!" << endl;
      return unordered_map<DataType, int>();
    }

    unordered_map<DataType, int> distance;

    if (!this->KeyCheck(source))
    {
      cout << "Key does not exist's in the Graph" << endl;
      distance[source] = -1;
      return distance;
    }

    stack<DataType> topoSort;
    unordered_map<DataType, bool> visited;

    for (auto i : this->Keys)
    {
      if (!visited[i])
      {
        this->TopologicalDFS(visited, topoSort, i);
      }
    }

    for (auto i : this->Keys)
    {
      distance[i] = INT_MAX;
    }

    distance[source] = 0;
    DataType element;
    while (!topoSort.empty())
    {
      element = topoSort.top();
      topoSort.pop();

      if (distance[element] < INT_MAX)
      {
        for (auto i : this->AdjacencyList[element])
        {
          int dist = distance[element] + i.second;
          if (distance[i.first] > dist)
          {
            distance[i.first] = dist;
          }
        }
      }
    }

    return distance;
  }

  unordered_map<DataType, int> SingleSourceShortestPath(DataType source)
  {
    if (!this->WeightedGraph)
    {
      cout << "Not a Weighted Graph!" << endl;
      return unordered_map<DataType, int>();
    }

    unordered_map<DataType, int> distance;

    if (!this->KeyCheck(source))
    {
      cout << "Key does not exist's in the Graph" << endl;
      distance[source] = -1;
      return distance;
    }

    // unordered_map<DataType, bool> visited;

    for (auto i : this->Keys)
    {
      distance[i] = INT_MAX;
    }

    this->DijkstrasAlgorithm(source, distance);

    return distance;
  }

  unordered_map<DataType, unordered_map<DataType, int>> AllPairShortestPath()
  {
    if (!this->WeightedGraph)
    {
      cout << "Not a Weighted Graph!" << endl;
      return unordered_map<DataType, unordered_map<DataType, int>>();
    }

    unordered_map<DataType, unordered_map<DataType, int>> distance;

    list<DataType, int> container;
  }

  int nodes() { return this->Nodes; }

  int edges() { return this->Edges; }

  // 0 for Undirected Graph && 1 for Directed Graph
  bool direction() { return this->Direction; }
  // 0 for UnWeighted Graph && 1 for Weighted Graph
  bool weightedGraph() { return this->WeightedGraph; }

  int components() { return this->ComponentsCount; }
};

// int main()
// {
//     // Also optimize graph for handling different components in it
//     Graph<char> path;
//     path.createGraph();
//     path.PrintAdjacencyList();
//     cout << endl;
//     path.BFSTraversal();
//     cout << endl;
//     path.DFSTraversal();
//     cout << endl;
//     cout << "No of Nodes: " << path.nodes() << endl;
//     cout << "No of Edges: " << path.edges() << endl;
//     cout << "Undirected/Directed: " << path.direction() << endl;
//     cout << "UnWeighted/Weighted: " << path.weightedGraph() << endl;
//     cout << "Components in Graph: " << path.components() << endl;
//     cout << "Topological Sort using DFS: ";
//     path.TopologicalSortDFS();
//     cout << endl;
//     return 0;
// }

// Graph Inputs  ^ (NOTE: 0 is not allowed in the graph node input)
// UnWeighted Graph
// 5 7 1 2 3 4 5 1 0 2 1 2 4 1 3 3 4 3 5 3 2 4 5 }-> Directed Graph
// 5 7 1 2 3 4 5 0 0 2 1 2 4 1 3 3 4 3 5 3 2 4 5 }-> Undirected Graph

// 5 9 1 2 3 4 5 1 0 1 4 1 5 2 3 2 5 3 1 3 4 4 2 4 1 5 3 }-> Directed Graph
// 5 8 1 2 3 4 5 0 0 1 5 2 3 2 5 3 1 3 4 4 2 4 1 5 3 }-> Undirected Graph

// // 6 10 UK USA SINGAPORE CANADA ANTARCTICA GERMANY 1 0 UK USA SINGAPORE USA
// GERMANY UK GERMANY CANADA USA ANTARCTICA CANADA ANTARCTICA CANADA UK
// SINGAPORE GERMANY USA GERMANY USA CANADA }-> Directed Graph
// // 6 10 UK USA SINGAPORE CANADA ANTARCTICA GERMANY 0 0 UK USA SINGAPORE USA
// GERMANY UK GERMANY CANADA USA ANTARCTICA CANADA ANTARCTICA CANADA UK
// SINGAPORE GERMANY USA GERMANY USA CANADA }-> Undirected Graph

// // Directed Acyclic Graph
// // 8 8 a b c d e f g h 1 0 a f a h f c c h h d e b e g b g }-> Directed Graph
// (DAG)