#include <iostream>
#include <utility>
#include <vector>

using namespace std;

const int mov_x[] = {1, 0, -1, 0};
const int mov_y[] = {0, 1, 0, -1};

int meta_x;
int meta_y;
vector<vector<bool>> visited;
vector<pair<int, int>> camino;

bool valid(const vector<vector<int>> &grid, int x, int y) {
  return x >= 0 && x < static_cast<int>(grid.size()) && y >= 0 &&
         y < static_cast<int>(grid[x].size()) && grid[x][y] == 0 &&
         !visited[x][y];
}

bool recursive(const vector<vector<int>> &grid, int x, int y,
               vector<pair<int, int>> &camino) {
  if (!valid(grid, x, y)) {
    return false;
  }

  visited[x][y] = true;
  camino.push_back({x, y});

  if (x == meta_x && y == meta_y) {
    return true;
  }

  for (int i = 0; i < 4; i++) {
    const int nx = x + mov_x[i];
    const int ny = y + mov_y[i];
    if (recursive(grid, nx, ny, camino)) {
      return true;
    }
  }

  camino.pop_back();
  return false;
}

int main() {
  int x, y;
  cout << "Ingrese la coordenada del meta: ";
  cin >> x >> y;
  meta_x = x;
  meta_y = y;

  vector<vector<int>> grid(10, vector<int>(10, 1));
  visited = vector<vector<bool>>(10, vector<bool>(10, false));

  if (recursive(grid, x, y, camino)) {
    cout << "Camino encontrado!" << endl;
    for (const auto &p : camino) {
      cout << "(" << p.first << ", " << p.second << ")" << endl;
    }
  } else {
    cout << "No se encontro ningún camino" << endl;
  }

  return 0;
}