#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct spaceIndex
{
  int x, y;
  spaceIndex(int a = -1, int b = -1) : x(a), y(b) {}
};

struct nodesRelation
{
  spaceIndex current;
  spaceIndex parent;
};

int shortestPathBinaryMatrix(vector<vector<int>> &grid, vector<spaceIndex> &path)
{
  int n = grid.size();
  if (grid[0][0] != 0 || grid[n - 1][n - 1] != 0)
  {
    return -1;
  }

  int directionRows[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int directionColumns[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

  vector<nodesRelation> nodes;
  queue<spaceIndex> q;
  spaceIndex start(0, 0);
  spaceIndex end(-1, -1);
  q.push(start);
  grid[0][0] = 1;
  nodes.push_back({start, end});

  while (!q.empty())
  {
    spaceIndex s = q.front();
    q.pop();

    int pathLen = grid[s.x][s.y];
    if (s.x == n - 1 && s.y == n - 1)
    {
      end = s;
      break;
    }

    for (int k = 0; k < 8; k++)
    {
      int newRow = s.x + directionRows[k];
      int newCol = s.y + directionColumns[k];
      if (newRow >= 0 && newRow < n && newCol >= 0 && newCol < n && grid[newRow][newCol] == 0)
      {
        spaceIndex newSpaceIndex = spaceIndex(newRow, newCol);
        q.push(spaceIndex(newRow, newCol));
        grid[newRow][newCol] = pathLen + 1;
        nodes.push_back({newSpaceIndex, s});
      }
    }
  }
  if (end.x == -1)
    return -1;

  nodesRelation cur = nodes.back();
  while (cur.parent.x != -1)
  {
    path.push_back(cur.current);
    for (auto &v : nodes)
    {
      if (v.current.x == cur.parent.x && v.current.y == cur.parent.y)
      {
        cur = v;
        break;
      }
    }
  }
  path.push_back(spaceIndex(0, 0));
  reverse(path.begin(), path.end());
  return grid[n - 1][n - 1];
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
  while (fileName != "END")
  {
    cout << "Enter File Name: ";
    cin >> fileName;

    if(fileName=="END"){
      break;
    }

    int size;
    vector<vector<int>> grid;

    bool isReadFile = readFile(fileName, size, grid);
    if (isReadFile)
    {
      cout << endl
           << "File: " << fileName << " Input Grid"
           << endl;
      printGrid(size, grid);

      vector<spaceIndex> path;
      int pathLength = shortestPathBinaryMatrix(grid, path);
      if (pathLength == -1)
      {
        cout << "Solution does not exist \n"
             << endl;
      }
      else
      {
        cout << endl
             << "Solution : Path Length = " << pathLength << endl;
        printGrid(size, grid);
        cout << endl;
        cout << "Shortest path:" << endl;
        for (auto &p : path)
        {
          cout << "(" << p.x << "," << p.y << ") ";
          cout << endl;
        }
        cout << "==========================\n\n";
      }
    }
  }
  return 0;
}
