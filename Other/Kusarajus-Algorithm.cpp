#include <iostream>
#include <vector>

using namespace std;

const int MAX = 1000; // Maximum number of vertices

class Graph {
public:
    int V;
    int adj[MAX][MAX];
    int reverse_adj[MAX][MAX];
    
    Graph(int V);
    void addEdge(int u, int v);
    void DFS(int v, bool visited[], int finish[]);
    void reverseDFS(int v, bool visited[], int component[], int &idx);
    void fillOrder(int v, bool visited[], int finish[], int &idx);
    void getTranspose();
    void printSCCs();
};

Graph::Graph(int V) {
    this->V = V;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
            reverse_adj[i][j] = 0;
        }
    }
}

void Graph::addEdge(int u, int v) {
    adj[u][v] = 1;
}

void Graph::DFS(int v, bool visited[], int finish[]) {
    visited[v] = true;
    for (int i = 0; i < V; i++) {
        if (adj[v][i] && !visited[i]) {
            DFS(i, visited, finish);
        }
    }
    finish[finish[0]++] = v;
}

void Graph::reverseDFS(int v, bool visited[], int component[], int &idx) {
    visited[v] = true;
    component[idx++] = v;
    for (int i = 0; i < V; i++) {
        if (reverse_adj[v][i] && !visited[i]) {
            reverseDFS(i, visited, component, idx);
        }
    }
}

void Graph::fillOrder(int v, bool visited[], int finish[], int &idx) {
    DFS(v, visited, finish);
}

void Graph::getTranspose() {
    for (int v = 0; v < V; v++) {
        for (int u = 0; u < V; u++) {
            if (adj[v][u]) {
                reverse_adj[u][v] = 1;
            }
        }
    }
}

void Graph::printSCCs() {
    bool visited[MAX];
    int finish[MAX + 1];
    finish[0] = 1;
    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            fillOrder(i, visited, finish, finish[0]);
        }
    }

    getTranspose();

    for (int i = 0; i < V; i++) {
        visited[i] = false;
    }

    while (finish[0] > 1) {
        int v = finish[--finish[0]];
        if (!visited[v]) {
            int component[MAX];
            int idx = 0;
            reverseDFS(v, visited, component, idx);
            for (int j = 0; j < idx; j++) {
                cout << component[j] << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    cout << "Strongly Connected Components:" << endl;
    g.printSCCs();

    return 0;
}

