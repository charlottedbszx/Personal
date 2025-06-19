#include <iostream>
#include <vector>
using namespace std;

bool dfsCycle(int node, vector<vector<int>>& adj, vector<int>& visited, vector<int>& parent, vector<int>& cycle) {
    visited[node] = 1;
    for (int i = 0; i < adj.size(); i++) {
        if (adj[node][i]) {
            if (!visited[i]) {
                parent[i] = node;
                if (dfsCycle(i, adj, visited, parent, cycle)) return true;
            } else if (i != parent[node]) {
                cycle.push_back(i);
                int curr = node;
                while (curr != i) {
                    cycle.push_back(curr);
                    curr = parent[curr];
                }
                cycle.push_back(i);
                return true;
            }
        }
    }
    return false;
}

int main() {
    char again = 'y';
    while (again == 'y' || again == 'Y') {
        int n;
        cout << "Welcome to DFS Graph" << endl;
        cout << "Enter number of vertices: ";
        if (!(cin >> n) || n <= 0) {
            cout << "Invalid number of vertices. Please try again.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        vector<vector<int>> adj(n, vector<int>(n));
        cout << "Enter adjacency matrix (only 0 or 1 values):\n";
        bool valid = true;
        for (int i = 0; i < n && valid; i++) {
            for (int j = 0; j < n && valid; j++) {
                if (!(cin >> adj[i][j]) || (adj[i][j] != 0 && adj[i][j] != 1)) {
                    cout << "Invalid matrix value at position (" << i << ", " << j << "). Please try again.\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    valid = false;
                }
            }
        }
        if (!valid) continue;

        vector<int> visited(n, 0), parent(n, -1), cycle;
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dfsCycle(i, adj, visited, parent, cycle)) {
                found = true;
                break;
            }
        }

        if (found) {
            cout << "Graph contains a cycle:\n";
            for (auto it = cycle.rbegin(); it != cycle.rend(); ++it)
                cout << *it << " ";
            cout << endl;
        } else {
            cout << "Graph does not contain a cycle.\n";
        }

        cout << "Do you want the run the program again? (Y/N): ";
        cin >> again;
        cin.ignore(10000, '\n');
    }
    return 0;
}
