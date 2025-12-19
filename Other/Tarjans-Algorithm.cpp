#include <iostream>
#include <vector>

using namespace std;

const int MAX = 1000; // Maximum number of vertices

class Graph {
public:
    int V;
    int adj[MAX][MAX];
    
    Graph(int V);
    void addEdge(int u, int v);
    void tarjanDFS(int u, int disc[], int low[], int stack[], bool stackMember[], int &time, int &top, int sccs[][MAX], int &scc_count);
    void printSCCs();
};

Graph::Graph(int V) {
    this->V = V;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }
}

void Graph::addEdge(int u, int v) {
    adj[u][v] = 1;
}

void Graph::tarjanDFS(int u, int disc[], int low[], int stack[], bool stackMember[], int &time, int &top, int sccs[][MAX], int &scc_count) {
    disc[u] = low[u] = ++time;
    stack[++top] = u;
    stackMember[u] = true;

    for (int v = 0; v < V; v++) {
        if (adj[u][v]) {
            if (disc[v] == -1) {
                tarjanDFS(v, disc, low, stack, stackMember, time, top, sccs, scc_count);
                low[u] = min(low[u], low[v]);
            } else if (stackMember[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }
    }

    int w = 0;
    if (low[u] == disc[u]) {
        int idx = 0;
        while (stack[top] != u) {
            w = stack[top--];
            cout << w << " ";
            sccs[scc_count][idx++] = w;
            stackMember[w] = false;
        }
        w = stack[top--];
        cout << w << endl;
        sccs[scc_count][idx++] = w;
        stackMember[w] = false;
        scc_count++;
    }
}

void Graph::printSCCs() {
    int disc[MAX], low[MAX];
    bool stackMember[MAX];
    int stack[MAX];
    int sccs[MAX][MAX];
    int scc_count = 0;
    int time = 0, top = -1;

    for (int i = 0; i < V; i++) {
        disc[i] = low[i] = -1;
        stackMember[i] = false;
    }

    for (int i = 0; i < V; i++) {
        if (disc[i] == -1) {
            tarjanDFS(i, disc, low, stack, stackMember, time, top, sccs, scc_count);
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

