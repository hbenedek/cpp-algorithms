#include<iostream>
#include <fstream>
#include <vector>
#include <algorithm> 
#include<list>
using namespace std;

// using disjoint sets: https://www.geeksforgeeks.org/union-find/

struct Edge 
{
    int src, dest, weight;
    bool operator< (const Edge &other) const {
        return weight < other.weight;
    }
};

class Graph
{
public:    
    int N;
    list<pair<int,int>> *adjacency_list;
    vector<Edge> *edge_list;
    // Constructor

    Graph(int v)
    {
        adjacency_list = new list<pair<int,int>> [v];
        edge_list = new vector<Edge>;
        N = v;
    }

    void add_edge(int u,int v, int weight)
    {
        adjacency_list[u].push_back(make_pair(v,weight));
        adjacency_list[v].push_back(make_pair(v,weight));
    }

    void build_from_edgelist(vector<Edge> &edges)
    {
        for (auto &edge: edges)
        {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            adjacency_list[src].push_back(make_pair(dest, weight));
            adjacency_list[dest].push_back(make_pair(src, weight));
        }   
        edge_list = &edges; 
    }
    
    void print_graph()
    {
        for (int i = 0; i < N; i++)
        {
            cout << i <<"->";
            for (auto it:adjacency_list[i])
            {
                cout << it.first <<" ";
            }
            cout << endl;   
        }  
    }
};

// union-find impementation
int find(int parent[], int i)
{
    //finds parent element of subset
    if (parent[i] == -1)
    {
        return i;
    }
    return find(parent, parent[i]);
}

void Union(int parent[], int x, int y)
{
    parent[x] = y;
}

bool matroid_property(int parent[], Edge edge)
{
     // check if S + e is acyclic with disjoint sets
    int x = find(parent, edge.src);
    int y = find(parent, edge.dest);
    
    if (x == y)
    {
        // graph is cyclic
        return false;
    }
    Union(parent, x, y);
    return true;
}

vector<Edge> kruskal(vector<Edge> edges, int number_of_nodes){
    // sort edges by weights
    sort(edges.begin(), edges.end());
    // initialize spaning tree
    vector<Edge> spanning_tree;
    // initialize union-find
    int parent[number_of_nodes] = {-1};
    fill_n(parent, number_of_nodes, -1);

    //iterate edges and build the tree
    for (auto & edge : edges)
    {
        bool matroid = matroid_property(parent, edge);
        if (matroid)
        {
           spanning_tree.push_back(edge);
        }
    }
    return spanning_tree;
}


int main(){
    Graph g(4);
    //g.add_edge(1, 2, 0);
    //g.add_edge(4, 2, 0);
    //g.add_edge(1, 3, 0);
    //g.add_edge(4, 3, 0);
    //g.add_edge(1, 4, 0);
    vector<Edge> edges ={{0,1,3},{1,3,2},{0,2,3},{1,2,4},{2,3,1}};
      
    g.build_from_edgelist(edges);  
    vector<Edge> spanning_tree = kruskal(edges, g.N);

    for (auto &edge: spanning_tree)
    {
        cout << edge.src << "-" << edge.dest << " w=" << edge.weight <<endl;
    }
    
    return 0;  
}

