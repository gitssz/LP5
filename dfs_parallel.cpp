#include<iostream>
#include <omp.h>
#include<stack>
#include<vector>
using namespace std;

const int MAX=10000;
vector<int> graph[MAX];
bool visited[MAX];

void DFS(int node){
    stack<int> s;
    s.push(node);

    while(!s.empty()){
        int current_node=s.top();
        s.pop();

        if(!visited[current_node]){
            visited[current_node]=true;
        }

        if(visited[current_node]){
            cout<<current_node<<" ";
        }

        #pragma omp parallel for
        // {
            for(int i=0;i<graph[current_node].size();i++)
            {
                int adj_node =graph[current_node][i];
                if(!visited[adj_node]){
                    s.push(adj_node);
                }
            }
        // }
    }
}

int main(){


int no_of_vertices,no_of_edges,start_node;
cout<<"enter no of vertices: ";
cin>>no_of_vertices;

cout<<"enter no of edges: ";
cin>>no_of_edges;

cout<<"enter start node: ";
cin>>start_node;

cout<<"enter pair of edges: "<<endl;
for(int i=0;i<no_of_edges;i++){
    int u,v;
    cin>> u>>v;
    graph[u].push_back(v);
    graph[v].push_back(u);
}

#pragma omp parallel for
for (int i = 0; i < no_of_vertices; i++) {
visited[i] = false;
}

cout<<"dfs traversal->"<<endl;
DFS(start_node);

    return 0;
}