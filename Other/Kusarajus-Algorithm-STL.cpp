#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void dfs(int v, vector<vector<int>>& graph, vector<bool>& visited, stack<int>& finishStack) {
    visited[v] = true;
    for (int u : graph[v]) {
        if (!visited[u]) {
            dfs(u, graph, visited, finishStack);
        }
    }
    finishStack.push(v);
}

void reverseDfs(int v, vector<vector<int>>& reverseGraph, vector<bool>& visited, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);
    for (int u : reverseGraph[v]) {
        if (!visited[u]) {
            reverseDfs(u, reverseGraph, visited, component);
        }
    }
}

vector<vector<int>> kosarajuSCC(int n, vector<vector<int>>& graph) {
    stack<int> finishStack;
    vector<bool> visited(n, false);
    
    // First DFS to compute finishing times
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, graph, visited, finishStack);
        }
    }
    
    // Transpose the graph
    vector<vector<int>> reverseGraph(n);
    for (int v = 0; v < n; v++) {
        for (int u : graph[v]) {
            reverseGraph[u].push_back(v);
        }
    }
    
    // Second DFS on the transposed graph in decreasing order of finishing times
    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> sccs;
    
    while (!finishStack.empty()) {
        int v = finishStack.top();
        finishStack.pop();
        if (!visited[v]) {
            vector<int> component;
            reverseDfs(v, reverseGraph, visited, component);
            sccs.push_back(component);
        }
    }
    
    return sccs;
}

int main() {
    int n = 5;
    vector<vector<int>> graph = {
        {1}, {2}, {0, 3}, {4}, {}
    };
    
    vector<vector<int>> sccs = kosarajuSCC(n, graph);
    
    cout << "Strongly Connected Components:" << endl;
    for (const auto& scc : sccs) {
        for (int v : scc) {
            cout << v << " ";
        }
        cout << endl;
    }
    
    return 0;
}

