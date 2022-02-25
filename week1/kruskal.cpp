#include<iostream>
#include <fstream>
#include <vector>
#include<list>
using namespace std;

struct Edge {
    int src, dest, weight;
};

class Graph{
public:    
    int N;
    list<pair<int,int>> *adjacency_list;
    vector<Edge> *edge_list;
    // Constructor
    Graph(int v){
        adjacency_list = new list<pair<int,int>> [v];
        edge_list = new vector<Edge>;
        N = v;
    }

    void add_edge(int u,int v, int weight){
        adjacency_list[u].push_back(make_pair(v,weight));
        adjacency_list[v].push_back(make_pair(v,weight));
    }

    void build_from_edgelist(vector<Edge> &edges){
        for (auto &edge: edges)
        {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            adjacency_list[src].push_back(make_pair(dest, weight));
            adjacency_list[dest].push_back(make_pair(src, weight));
        }    
    }
    
    void print_graph(){
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

void kruskal(Graph g){
    // sort edges by weights

    // initialize spaning tree
    //iterate edges and build the tree
};

int main(){
    Graph g(6);
    //g.add_edge(1, 2, 0);
    //g.add_edge(4, 2, 0);
    //g.add_edge(1, 3, 0);
    //g.add_edge(4, 3, 0);
    //g.add_edge(1, 4, 0);
    vector<Edge> edges ={{0, 1, 6}, {1, 2, 7}, {2, 0, 5}, {2, 1, 4}, {3, 2, 10}, {5, 4, 1}, {4, 5, 3}};
      
    g.build_from_edgelist(edges);  
    g.print_graph();
    return 0;  
}