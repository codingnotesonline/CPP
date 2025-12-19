#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

void tarjanDFS(int v, vector<vector<int>>& graph, vector<int>& indices, vector<int>& lowlink, stack<int>& stk, vector<bool>& onStack, int& index, vector<vector<int>>& sccs) {
    indices[v] = index;
    lowlink[v] = index;
    index++;
    stk.push(v);
    onStack[v] = true;
    
    for (int u : graph[v]) {
        if (indices[u] == -1) {
            tarjanDFS(u, graph, indices, lowlink, stk, onStack, index, sccs);
            lowlink[v] = min(lowlink[v], lowlink[u]);
        } else if (onStack[u]) {
            lowlink[v] = min(lowlink[v], indices[u]);
        }
    }
    
    if (lowlink[v] == indices[v]) {
        vector<int> component;
        int w;
        do {
            w = stk.top();
            stk.pop();
            onStack[w] = false;
            component.push_back(w);
        } while (w != v);
        sccs.push_back(component);
    }
}

vector<vector<int>> tarjanSCC(int n, vector<vector<int>>& graph) {
    vector<int> indices(n, -1);
    vector<int> lowlink(n, -1);
    stack<int> stk;
    vector<bool> onStack(n, false);
    vector<vector<int>> sccs;
    int index = 0;
    
    for (int v = 0; v < n; v++) {
        if (indices[v] == -1) {
            tarjanDFS(v, graph, indices, lowlink, stk, onStack, index, sccs);
        }
    }
    
    return sccs;
}

int main() {
    int n = 5;
    vector<vector<int>> graph = {
        {1}, {2}, {0, 3}, {4}, {}
    };
    
    vector<vector<int>> sccs = tarjanSCC(n, graph);
    
    cout << "Strongly Connected Components:" << endl;
    for (const auto& scc : sccs) {
        for (int v : scc) {
            cout << v << " ";
        }
        cout << endl;
    }
    
    return 0;
}

