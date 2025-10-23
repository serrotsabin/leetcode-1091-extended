#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


int shortestPathBinaryMatrix(vector<vector<int>> &grid)
  {
    int n = grid.size();
    if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0)
    {
      return -1;
    }

    struct spaceIndex
    {
      int x;
      int y;

      spaceIndex(int xval, int yval) : x(xval), y(yval) {};
    };

    int directionRows[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int directionColumns[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

    queue<spaceIndex> q;
    q.push(spaceIndex(0, 0));
    grid[0][0] = 1;

    while (!q.empty())
    {
      spaceIndex s = q.front();
      q.pop();

      int pathLen = grid[s.x][s.y];
      if (s.x == n - 1 && s.y == n - 1)
      {
        return pathLen;
      }

      for (int k = 0; k < 8; k++)
      {
        int newRow = s.x + directionRows[k];
        int newCol = s.y + directionColumns[k];
        if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && grid[newRow][newCol] == 0)
        {
          q.push(spaceIndex(newRow, newCol));
          grid[newRow][newCol] = pathLen + 1;
        }
      }
    }
    return -1;
  };

int main() {
    ifstream infile("5.txt");
    if (!infile) {
        cerr << "Could not open the file!" << endl;
        return 1;
    }

    int n;
    infile >> n; 

    vector<vector<int>> grid(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            infile >> grid[i][j];
        }
    }

    infile.close();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    shortestPathBinaryMatrix(grid);

    cout << "Solution"<<endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
