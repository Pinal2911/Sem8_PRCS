#include<iostream>
#include<bits/stdc++.h>
#include<omp.h>
using namespace std;

 class Graph{
    public:
    vector<vector<int>> graph;
    vector<bool> visited;
    int vertices;
    Graph(int v): vertices(v),visited(v),graph(v) {}

    void initialize(){
        for(int i=0;i<vertices;i++){
            visited[i]=false;
        }
    }

    void addEdge(int a,int b){
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    void parallel_dfs(int startVertex){
        initialize();
        stack<int> s;
        s.push(startVertex);
        visited[startVertex]=true;

        while(s.empty() != true){
            int current=s.top();
            #pragma omp critical
            s.pop();
            cout<<current<<" ";
            #pragma omp parallel for
            for(int j=0;j<graph[current].size();j++){
                int n=graph[current][j];
                if(!visited[n]){
                    s.push(n);
                    visited[n]=true;
                }
            }
        }
    }

     void dfs(int startVertex){
        initialize();
        stack<int> s;
        s.push(startVertex);
        visited[startVertex]=true;

        while(s.empty() != true){
            int current=s.top();
           
            s.pop();
            cout<<current<<" ";
           
            for(int j=0;j<graph[current].size();j++){
                int n=graph[current][j];
                if(!visited[n]){
                    s.push(n);
                    visited[n]=true;
                }
            }
        }
    }

    void parallel_bfs(int startVertex){
        initialize();
        queue<int> q;
        q.push(startVertex);
        visited[startVertex]=true;
        while(q.empty() != true){
            int current=q.front();
            cout<<current<<" ";
            #pragma omp critical
            q.pop();

            #pragma omp parallel for
            for(int j=0;j<graph[current].size();j++){
                    int n=graph[current][j];
                    if(!visited[n]){
                        q.push(n);
                        visited[n]=true;
                    }
            }
        }
    }

    void bfs(int startVertex){
        initialize();
        queue<int> q;
        q.push(startVertex);
        visited[startVertex]=true;
        while(q.empty() != true){
            int current=q.front();
            cout<<current<<" ";
          
            q.pop();

          
            for(int j=0;j<graph[current].size();j++){
                    int n=graph[current][j];
                    if(!visited[n]){
                        q.push(n);
                        visited[n]=true;
                    }
            }
        }
    }


};



int main(){

    int v;
    cout<<"\nEnter number of vertices";
    cin>>v;

    int edges;
    cout<<"\nEnter number pf edges";
    cin>>edges;

    Graph g(v);
    int s,d;
    
    for(int i=0;i<edges;i++){
    cout<<"\nEnter the edges source and destination";
    cin>>s>>d;
    g.addEdge(s,d);
    }
    int startV;
    cout<<"\nENter strat vertex";
    cin>>startV;
    cout<<"\nSImple BFS \n";
    g.bfs(startV);
    cout<<"\nParallel BFS\n";
    g.parallel_bfs(startV);
    cout<<"\nSimple DFS \n";
    g.dfs(startV);
    cout<<"\nParllel DFS\n";
    g.parallel_dfs(startV);




}