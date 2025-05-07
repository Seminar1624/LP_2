#include <iostream>
#include<bits/stdc++.h>
#include <vector>
using namespace std;

class Graph
{
  int V;
  vector<vector<int>> adj;
public:
    Graph(int V)
    {
        this->V=V;
        adj=vector<vector<int>>(V);
        // adj.resize(V);
    }
    void addEdge(int v,int w)
    {
        adj[v].push_back(w);
    }
    void BFSRec(vector<int> &currentlevel,vector<bool> &visited)
    {
        if(currentlevel.empty()) return;

        vector<int> nextlevel;
        for(int u:currentlevel)
        {
            cout<<u+1<<" ";
            for(int neighbor:adj[u])
            {
                if(!visited[neighbor])
                {
                    visited[neighbor]=true;
                    nextlevel.push_back(neighbor);
                }
            }
        }
        BFSRec(nextlevel,visited);
    }
    void BFS(int s)
    {
        vector<bool> visited(V,false);
        visited[s]=true;
        vector<int>currentlevel={s};
        cout<<"BFS : ";
        BFSRec(currentlevel,visited);
    }
    void BFSIrerative(int s) {
        vector<bool> visited(V, false);  // Track visited nodes
        queue<int> q;                    // Create a queue
    
        visited[s] = true;               // Mark the starting node as visited
        q.push(s);                       // Enqueue the starting node
    
        cout << "BFS: ";
        while (!q.empty()) {
            int u = q.front();           // Get front node from queue
            q.pop();                     // Remove it from queue
            cout << u + 1 << " ";        // Print the node (convert to 1-based)
    
            for (int neighbor : adj[u]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true; // Mark neighbor as visited
                    q.push(neighbor);        // Add it to the queue
                }
            }
        }
        cout << endl;
    }
    
    void DFSRec(int s,vector<bool> &visited)
    {
        visited[s]=true;
        cout<<s+1<<" ";
        for(int i:adj[s])
        {
            if(!visited[i])
            {
                DFSRec(i,visited);
            }
        }

    }
    void DFS()
    {
        vector<bool>visited(V,false);
        for(int i=0;i<V;i++)
        {
            if(!visited[i])
            {
                DFSRec(i,visited);
            }
        }
    }
};
int main()
{
    int n,e,e1,e2,choice;
    cout<<"Enter number of nodes : "<<endl;
    cin>>n;
    cout<<"Enter total number of edges : "<<endl;
    cin>>e;
    Graph g(n);
    cout<<endl<<"Enter edges (space seprated) : "<<endl;
    for(int i=0;i<e;i++)
    {
        cin>>e1>>e2;
        if(e1<1 ||e1>n ||e2<1 ||e2>n)
        {
            cout<<"Invalid edge : "<<e1<<" "<<e2<<endl;
            continue;
        }
        // store as 0-based index
        g.addEdge(e1-1,e2-1);  
    }
    do
    {
        cout<<"Select operation - \n 1-BFS \n 2- DFS \n 3-BFS Iterative \n Enter your choice : "<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:
           int start;
           cout<<"Enter start element :"<<endl;
           cin>>start;
           if(start<1 ||start>n)
           {
            cout<<"Invalid starting node!" <<endl;
            break;
           }
           g.BFS(start-1);
           cout<<endl;
            break;
        case 2:
           cout<<"DFS : "<<endl;
           g.DFS();
           cout<<endl;
           break;

        case 3:
           g.BFSIrerative(1);
            break;   
        default:
            cout<<"invalid selection\n";
            break;
        }
    } while (choice!=4);
    

    return 0;
}