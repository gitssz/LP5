#include<iostream>
#include <omp.h>
#include<vector>
#include<queue>
using namespace std;

struct Graph{
    int v;  //number of verrtices in graph
    vector<vector<int>> adj; //adjacency list

    Graph(int v){     //constructor  
        this->v =v;   //initialize the number of vertices
        adj.resize(v);  //resizes the adjacency list to accommodate V vertices
    }

    void addEdge(int u, int v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void BFS(int start){

        vector<bool> visited(v,false);  //visited array
        queue<int> q; 
        visited[start]=true;  //marking start node as visited
        q.push(start);    //adding start to q, so that we can add its neighbors later

        while(!q.empty()) //while queue is not empty
        {
            int u = q.front();
            q.pop();
            cout<< u <<" ";

            #pragma omp parallel for
            for(int i=0;i<adj[u].size();i++){   //iterates over the vertices adjacent to the current vertex u
                int v= adj[u][i];
                if(!visited[v]){
                    #pragma omp critical  //only one thread at a time can access and modify shared data
                    {
                        visited[v]=true;
                        q.push(v);
                    }
                }
            }   
        //even after the for loop ends, while loop still continues to run n then the front is popped n printed.
        }
    cout<<endl;
    }

};

int main(){

int v;
cout<<"enter number of vertices: "<<endl;
cin>>v;

Graph g(v);

int edgecount;
cout<<"enter number of edges: "<<endl;
cin>>edgecount;


cout<<"enter edges in format{source,destination}"<<endl;
for(int i=0;i<edgecount;i++){

    int u,v;
    cin>>u>>v;
    g.addEdge(u,v);
}


cout<<"bfs traversal->"<<endl;
g.BFS(0);

    return 0;
}
