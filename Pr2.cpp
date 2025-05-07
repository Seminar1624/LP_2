#include <iostream>
#include <stdio.h>
#include<queue>
#include<vector>
#include<algorithm>
#include<bits/stdc++.h>
#define N 3

using namespace std;
int drow[]={1,0,-1,0};
int dcol[]={0,-1,0,1};
struct Node
{
    Node *parent;
    int mat[N][N];
    int g;
    int h;
    int x,y;
};
void printMatrix(int mat[N][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}
void printPath(Node *node)
{
    if(!node) return;
    printPath(node->parent);
    printMatrix(node->mat);
    cout<<"g : "<<node->g<<" h: "<<node->h<<" f: "<<node ->g+node->h<<endl;
}
int heuristic(int mat[N][N],int goal[N][N])
{
    int count=0;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(mat[i][j] && mat[i][j] !=goal[i][j])
            {
                count++;
            }
        }
    }
    return count;
}
Node * createNode(int mat[N][N],int x,int y,int newx,int newy,int g,Node* parent)
{
    Node* node=new Node;
    node->parent=parent;
    // copy(&mat[0][0],&mat[0][0]+N*N,&node->mat[0][0]);
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            node->mat[i][j]=mat[i][j];
        }
    }
    swap(node->mat[x][y],node->mat[newx][newy]);
    node->h=INT_MAX;
    node->g=g;
    node->x=newx;
    node->y=newy;

    return node;
}
bool isValid(int x,int y)
{
    return x>=0 && x<N && y>=0 && y<N;
}
struct Compare
{
    bool operator()(const Node*a,const Node* b)
    {
        return (a->g+a->h)>(b->g+b->h);
    }
};
void solve(int start[N][N],int x,int y,int goal[N][N])
{
    priority_queue<Node*,vector<Node*>,Compare>pq;
    Node* root=createNode(start,x,y,x,y,0,nullptr);
    root->h=heuristic(start,goal);
    pq.push(root);

    while(!pq.empty())
    {
        Node* current=pq.top();
        pq.pop();

        if(current->h==0)
        {
            cout<<"Puzzle solved!"<<endl;
            printPath(current);
            return;
        }
        for(int i=0;i<4;i++)
        {
            int newx=current->x+drow[i];
            int newy=current->y+dcol[i];
            if(isValid(newx,newy))
            {
                Node* child=createNode(current->mat,current->x,current->y,newx,newy,current->g+1,current);
                child->h=heuristic(child->mat,goal);
                pq.push(child);
            }
        }
    }
    cout<<"No solution found "<<endl;
}


int main()
{
    int start[N][N];
    int goal[N][N];
    int x=-1;
    int y=-1;

    cout<<"Enter start state : "<<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cin>>start[i][j];
            if(start[i][j]==0)
            {
                x=i;
                y=j;
            }
        }
    }
    cout<<"Enter goal state : "<<endl;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cin>>goal[i][j];
           
        }
    }

    solve(start,x,y,goal);
    return 0;

}