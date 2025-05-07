#include <iostream>
#include <vector>
using namespace std;


void printBoard(vector<vector<int>> &board,int N)
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(board[i][j]==1)
                cout<<"Q ";
            else
                cout<<". ";    
        }
        cout<<endl;

    }
}
// branch and bound 
// checking before place 
bool isSafe(vector<vector<int>> &board,int row,int col,int N)
{
    // check th column for same row
    for(int i=0;i<row;i++)
    {
        if(board[i][col]==1)
            return false;
    }
    // check the upper left diagonal
    for(int i=row,j=col;i>=0 &&j>=0;i--,j--)
    {
        if(board[i][j]==1)
            return false;
    }
    // check upper right diagonal
    for(int i=row,j=col;i>=0 && j<N;i--,j++)
    {
        if(board[i][j]==1)
        {
            return false;
        }
    }

    return true;
}
bool solveNQueens(vector<vector<int>> &board,int row,int N)
{
    if(row==N)
    {
        return true;
    }
    cout<<"After the iteration The matrix is : "<<endl;
        printBoard(board,N);

    for(int col=0;col<N;col++)
    {
        if(isSafe(board,row,col,N))
        {
            board[row][col]=1;

            if(solveNQueens(board,row+1,N))
                return true;

            board[row][col]=0;    
        }

    }
    return false;
}
void solveNQueensOptamize(vector<vector<int>> &board,int row,int N,
    vector<int> &leftRow,
    vector<int> &upperDiagonal,
    vector<int> &lowerDiagonal,
    bool &found
)
{
    if(row==N)
    {
        found=true;
        printBoard(board,N);
        return;
    }
    for(int col=0;col<N;col++)
    {
        if(leftRow[col]==0 && upperDiagonal[row+col]==0 && lowerDiagonal[N-1+col-row]==0)
        {
            board[row][col]=1;
            leftRow[col]=1;
            upperDiagonal[row+col]=1;
            lowerDiagonal[N-1+col-row]=1;
            solveNQueensOptamize(board,row+1,N,leftRow,upperDiagonal,lowerDiagonal,found);
            if(found) return;

            board[row][col]=0;
            leftRow[col]=0;
            upperDiagonal[row+col]=0;
            lowerDiagonal[N-1+col-row]=0;
        }
    }
}

int main()
{
    int N;
    cout<<"Enter the number of queens (N)"<<endl;
    cin>>N;
    int choice;
    vector<vector<int>> board(N,vector<int>(N,0));
    cout << "Choose method:\n1. Standard Backtracking\n2. Optimized Branch and Bound\n";
    cin >> choice;

    if(choice==1)
    {
        if(solveNQueens(board,0,N))
        {
            cout<<"Solution found: " <<endl;
            printBoard(board,N);
        }
        else{
            cout<<"solution doesn't exist"<<endl;
        }
    }
    else if(choice==2)
    {
        vector<int> leftrow(N,0);
        vector<int> upperDiagonal(2*N-1,0);
        vector<int> lowerDiagonal(2*N-1,0);
        bool found=false;
        solveNQueensOptamize(board,0,N,leftrow,upperDiagonal,lowerDiagonal,found);
        if(!found)
        {
            cout<<"No solution exixt"<<endl;
        }
       
    }
    else{
        cout<<"Invalid choice."<<endl;
    }

    return 0;
}