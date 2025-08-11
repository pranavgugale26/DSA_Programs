#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

using namespace std;

struct Edge 
{
    string u, v;
    int cost;
};

bool compare(Edge a, Edge b) 
{
    return a.cost < b.cost;
}

class UnionFind 
{
    unordered_map<string, string> parent;

public:
    void makeSet(const vector<string>& nodes) 
    {
        for (const auto& node : nodes)
            parent[node] = node;
    }

    string find(string x) 
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(string x, string y) 
    {
        parent[find(x)] = find(y);
    }

    bool connected(string x, string y) 
    {
        return find(x) == find(y);
    }
};

int main() 
{
    int n, e;
    vector<string> cities;
    vector<Edge> edges;

    cout << "Enter number of offices (cities): ";
    cin >> n;
    cout << "Enter city names:\n";
    for (int i = 0; i < n; ++i) 
    {
        string city;
        cin >> city;
        cities.push_back(city);
    }

    cout << "Enter number of possible connections (edges): ";
    cin >> e;

    cout << "Enter each connection in format: city1 city2 cost\n";
    for (int i = 0; i < e; ++i) 
    {
        string u, v;
        int cost;
        cin >> u >> v >> cost;
        edges.push_back({u, v, cost});
    }

    sort(edges.begin(), edges.end(), compare);

    UnionFind uf;
    uf.makeSet(cities);

    int totalCost = 0;
    vector<Edge> mst;

    for (const auto& edge : edges) 
    {
        if (!uf.connected(edge.u, edge.v)) 
        {
            uf.unite(edge.u, edge.v);
            totalCost += edge.cost;
            mst.push_back(edge);
        }
    }

    cout << "\nMinimum Spanning Tree:\n";
    for (const auto& edge : mst) {
        cout << edge.u << " - " << edge.v << " : " << edge.cost << endl;
    }

    cout << "Total cost to connect all offices: " << totalCost << endl;

    return 0;
}