#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

const int N = 9;
const int SUBGRID = 3;

int puzzle[N][N] = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
};

bool isFixed[N][N];

int countConflicts(const int board[N][N]) {
    int conflicts = 0;

    for (int i = 0; i < N; ++i) {
        int rowCount[N + 1] = {0}, colCount[N + 1] = {0};
        for (int j = 0; j < N; ++j) {
            rowCount[board[i][j]]++;
            colCount[board[j][i]]++;
        }
        for (int k = 1; k <= N; ++k) {
            if (rowCount[k] > 1) conflicts += rowCount[k] - 1;
            if (colCount[k] > 1) conflicts += colCount[k] - 1;
        }
    }

    for (int boxRow = 0; boxRow < N; boxRow += SUBGRID) {
        for (int boxCol = 0; boxCol < N; boxCol += SUBGRID) {
            int count[N + 1] = {0};
            for (int i = 0; i < SUBGRID; ++i) {
                for (int j = 0; j < SUBGRID; ++j) {
                    int val = board[boxRow + i][boxCol + j];
                    count[val]++;
                }
            }
            for (int k = 1; k <= N; ++k)
                if (count[k] > 1) conflicts += count[k] - 1;
        }
    }

    return conflicts;
}

void initializeBoard(int board[N][N]) {
    for (int boxRow = 0; boxRow < N; boxRow += SUBGRID) {
        for (int boxCol = 0; boxCol < N; boxCol += SUBGRID) {
            vector<int> missing;
            bool present[N + 1] = {false};
            for (int i = 0; i < SUBGRID; ++i)
                for (int j = 0; j < SUBGRID; ++j)
                    present[puzzle[boxRow + i][boxCol + j]] = true;

            for (int v = 1; v <= N; ++v)
                if (!present[v]) missing.push_back(v);

            random_shuffle(missing.begin(), missing.end());
            int idx = 0;
            for (int i = 0; i < SUBGRID; ++i) {
                for (int j = 0; j < SUBGRID; ++j) {
                    int r = boxRow + i;
                    int c = boxCol + j;
                    if (puzzle[r][c] == 0)
                        board[r][c] = missing[idx++];
                    else
                        board[r][c] = puzzle[r][c];
                }
            }
        }
    }
}

void copyBoard(int dest[N][N], const int src[N][N]) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            dest[i][j] = src[i][j];
}

void generateNeighbor(const int board[N][N], int neighbor[N][N]) {
    copyBoard(neighbor, board);

    int boxRow = (rand() % 3) * SUBGRID;
    int boxCol = (rand() % 3) * SUBGRID;

    vector<pair<int, int>> mutableCells;
    for (int i = 0; i < SUBGRID; ++i) {
        for (int j = 0; j < SUBGRID; ++j) {
            int r = boxRow + i;
            int c = boxCol + j;
            if (!isFixed[r][c])
                mutableCells.emplace_back(r, c);
        }
    }

    if (mutableCells.size() >= 2) {
        int a = rand() % mutableCells.size();
        int b = rand() % mutableCells.size();
        while (a == b) b = rand() % mutableCells.size();

        swap(neighbor[mutableCells[a].first][mutableCells[a].second],
             neighbor[mutableCells[b].first][mutableCells[b].second]);
    }
}

void hillClimbing() {
    int board[N][N];
    initializeBoard(board);

    int currentConflicts = countConflicts(board);
    int maxSteps = 10000;

    for (int step = 0; step < maxSteps && currentConflicts > 0; ++step) {
        int neighbor[N][N];
        generateNeighbor(board, neighbor);
        int neighborConflicts = countConflicts(neighbor);

        if (neighborConflicts < currentConflicts) {
            copyBoard(board, neighbor);
            currentConflicts = neighborConflicts;
        }
    }

    if (currentConflicts == 0) {
        cout << " Solved Sudoku:\n";
    } else {
        cout << " Failed to solve. Best attempt:\n";
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << board[i][j] << " ";
        cout << endl;
    }
}

int main() {
    srand(time(NULL));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            isFixed[i][j] = puzzle[i][j] != 0;

    hillClimbing();

    return 0;
}
