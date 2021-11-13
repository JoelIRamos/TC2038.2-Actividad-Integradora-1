#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <algorithm>
#include <unordered_set>
#include <cmath>

typedef pair<int, int> iPair; 

using namespace std; 

#include "Colonia.hpp"

// Estructura que representa un grafo para el algoritmo de Kruskal 
struct Graph { 
    int V, E, costMSTKruskal; 
    vector< pair<int, pair<int, int>> > edges; 
    vector<vector<pair<int, int>>> adjList;
    vector<pair<int,int>> selectedEdgesK;

    Graph(int V, int E){ 
        this->V = V; 
        this->E = E;
        adjList.resize(V); 
        costMSTKruskal = 0;
    } 

    void addEdge(int u, int v, int w) { 
        edges.push_back({w, {u, v}});
        adjList[u].push_back({v,w});
    } 
    void print();
    void kruskalMST(); 
    string printEdgesK(vector<colonia>, vector<vector <double> >);
}; 

// To represent Disjoint Sets 
struct DisjointSets 
{ 
    int *parent, *rnk; 
    int n; 

    DisjointSets(int n){ 
        this->n = n; 
        parent = new int[n+1]; 
        rnk = new int[n+1]; 
        for (int i = 0; i <= n; i++){ 
            rnk[i] = 0; 
            parent[i] = i; 
        } 
    } 

    int find(int u) 
    { 
        if (u != parent[u]) 
            parent[u] = find(parent[u]); 
        return parent[u]; 
    } 

    // Union by rank 
    void merge(int x, int y) 
    { 
        x = find(x), y = find(y); 
        if (rnk[x] > rnk[y]) 
            parent[y] = x; 
        else
            parent[x] = y; 

        if (rnk[x] == rnk[y]) 
            rnk[y]++; 
    } 
}; 

void Graph::print(){
    cout << "Adjacent List:" << endl;
    for (int i=0; i<V; i++){
        cout << " " << i << ": ";
        for (int j=0; j<adjList[i].size(); j++){
            cout << "(" << adjList[i][j].first << "," << adjList[i][j].second << ") ";
        }
        cout << endl;
    }
}

// Complejidad: O(Elog2E)
void Graph::kruskalMST(){ 
    costMSTKruskal = 0;
    sort(edges.begin(), edges.end());
    DisjointSets ds(V);

    for (auto it:edges){
        int u = it.second.first;
        int v = it.second.second;
        int set_u = ds.find(u); 
        int set_v = ds.find(v);
        if (set_u != set_v){
            ds.merge(u, v);
            costMSTKruskal += it.first;
            selectedEdgesK.push_back({u,v});
        }
    }
} 

string Graph::printEdgesK(vector<colonia> colonias, vector<vector <double> > mapa){
    string result = "";
    for (auto it:selectedEdgesK){
        result += colonias[it.first].nombre + " - " + colonias[it.second].nombre + " " + to_string(int(mapa[it.first][it.second])) + "\n"; 
    }
    return result;
}

#endif
