#include<iostream>
#include <fstream>
#include <vector>
#include<list>
using namespace std;

class Graph{
public:    
    int N;
    list<pair<int,int>> *adjacency_list;

    // Constructor
    Graph(int v){
        adjacency_list = new list<pair<int,int>> [v];
        N = v;
    }

    void add_edge(int u,int v, int weight){
        adjacency_list[u].push_back(make_pair(v,weight));
        adjacency_list[v].push_back(make_pair(v,weight));
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

void kruskal(Graph g){}

int main(){
    Graph g(5);
    g.add_edge(1, 2, 0);
    g.add_edge(4, 2, 0);
    g.add_edge(1, 3, 0);
    g.add_edge(4, 3, 0);
    g.add_edge(1, 4, 0);

    g.print_graph();
    return 0;  
}