#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

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

void printGrid(int size, vector<vector<int>> &grid)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      cout << grid[i][j] << " ";
    }
    cout << endl;
  }
}

bool readFile(string fileName, int &size, vector<vector<int>> &grid)
{
  ifstream infile(fileName);
  if (!infile)
  {
    cerr << "Could not open the file!" << endl;
    return false;
  }

  infile >> size;

  grid.assign(size, vector<int>(size));

  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      infile >> grid[i][j];
    }
  }

  infile.close();

  return true;
}

int main()
{
  string fileName;

  while (fileName != "end")
  {
    cout << "Enter File Name: ";
    cin >> fileName;

    int size;
    vector<vector<int>> grid;

    bool isReadFile = readFile(fileName, size, grid);

    if (isReadFile)
    {
      cout << endl
           << "File: " << fileName << " Input Grid"
           << endl;
      printGrid(size, grid);

      int pathLength = shortestPathBinaryMatrix(grid);
      if (pathLength == -1)
      {
        cout << "Solution does not exist \n"
             << endl;
      }
      else
      {
        cout << endl
             << "Solution" << endl;
        printGrid(size, grid);
        cout << endl;
        cout << "==========================\n\n";
      }
    }
  }
  return 0;
}
