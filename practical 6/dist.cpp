#include <iostream>
#include <vector>
using namespace std;

#define INF 9999
#define MAX 20

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    int dist[MAX][MAX];
    int nextHop[MAX][MAX];

    cout << "Enter costs (9999 if no direct path):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dist[i][j] = 0;
                nextHop[i][j] = i;
            } else {
                cout << "Cost from " << i << " to " << j << ": ";
                cin >> dist[i][j];
                nextHop[i][j] = (dist[i][j] != INF) ? j : -1;
            }
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    nextHop[i][j] = nextHop[i][k];
                }
            }
        }
    }

    auto printPath = [&](int i, int j) {
        if (nextHop[i][j] == -1) {
            cout << "No path";
            return;
        }
        cout << i;
        while (i != j) {
            i = nextHop[i][j];
            cout << " -> " << i;
        }
    };

    cout << "\nAll paths and their costs:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << "From " << i << " to " << j << ": ";
                if (dist[i][j] == INF) {
                    cout << "No path\n";
                } else {
                    printPath(i, j);
                    cout << " | Cost: " << dist[i][j] << "\n";
                }
            }
        }
    }

    int source, destination;
    cout << "\nEnter the source node: ";
    cin >> source;
    cout << "Enter the destination node: ";
    cin >> destination;

    if (source < 0 || source >= n || destination < 0 || destination >= n) {
        cout << "Invalid source or destination node!";
        return 0;
    }

    cout << "\nShortest path from " << source << " to " << destination << " is: ";
    if (dist[source][destination] == INF) {
        cout << "No path exists\n";
    } else {
        printPath(source, destination);
        cout << " | Cost: " << dist[source][destination] << "\n";
    }

    return 0;
}

