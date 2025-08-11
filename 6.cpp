#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stack>
#include <set>

using namespace std;

class Graph {
    unordered_map<string, vector<pair<string, int>>> adj;

public:
    void addFlight(const string& from, const string& to, int cost) {
        adj[from].push_back({to, cost});
        adj[to].push_back({from, cost}); // Assuming undirected graph
    }

    void display() {
        for (const auto& city : adj) {
            cout << city.first << " -> ";
            for (const auto& flight : city.second)
                cout << "(" << flight.first << ", cost: " << flight.second << ") ";
            cout << endl;
        }
    }

    void dfs(const string& start, set<string>& visited) {
        stack<string> s;
        s.push(start);

        while (!s.empty()) {
            string current = s.top(); s.pop();
            if (visited.find(current) == visited.end()) {
                visited.insert(current);
                for (auto& neighbor : adj[current]) {
                    if (visited.find(neighbor.first) == visited.end())
                        s.push(neighbor.first);
                }
            }
        }
    }

    bool isConnected() {
        if (adj.empty()) return true;

        set<string> visited;
        auto it = adj.begin();
        dfs(it->first, visited);

        return visited.size() == adj.size();
    }
};

int main() {
    Graph g;
    int numFlights;
    cout << "Enter number of flights: ";
    cin >> numFlights;

    cout << "Enter flight details (from_city to_city cost):\n";
    for (int i = 0; i < numFlights; ++i) {
        string from, to;
        int cost;
        cin >> from >> to >> cost;
        g.addFlight(from, to, cost);
    }

    cout << "\nFlight Graph:\n";
    g.display();

    cout << "\nGraph is " << (g.isConnected() ? "connected." : "not connected.") << endl;

    return 0;
}
