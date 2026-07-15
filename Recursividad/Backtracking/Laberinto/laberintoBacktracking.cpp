#include <iostream>
#include <vector>

using namespace std;

const int mov_x[] = {1, 0, -1, 0, 1, 1, -1, -1};
const int mov_y[] = {0, 1, 0, -1, 1, -1, 1, -1};
const int N = 12;

bool validacion(vector<vector<int>> &laberinto, int x, int y,
                vector<vector<bool>> &visitadas) {
  int filas = laberinto.size();
  int columnas = laberinto[0].size();

  return (x >= 0 && x < filas && y >= 0 && y < columnas &&
          laberinto[x][y] == 0 && !visitadas[x][y]);
}

bool recursivo(vector<vector<int>> &laberinto, int x, int y, int meta_x,
               int meta_y, vector<vector<bool>> &visitadas,
               vector<pair<int, int>> &camino) {
  if (x == meta_x && y == meta_y) {
    camino.push_back({x, y});
    return true;
  }

  if (validacion(laberinto, x, y, visitadas)) {
    visitadas[x][y] = true;
    camino.push_back({x, y});

    for (int i = 0; i < 8; i++) {
      int new_x = x + mov_x[i];
      int new_y = y + mov_y[i];

      if (recursivo(laberinto, new_x, new_y, meta_x, meta_y, visitadas,
                    camino)) {
        return true;
      }
    }
    camino.pop_back();

    return false;
  }

  return false;
}

void printLaberinto(const vector<vector<int>> &laberinto) {
  for (size_t i = 0; i < laberinto.size(); i++) {
    for (size_t j = 0; j < laberinto[i].size(); j++) {
      cout << laberinto[i][j] << " ";
    }
    cout << endl;
  }
}

void printCamino(const vector<pair<int, int>> &camino) {
  for (size_t i = 0; i < camino.size() - 1; i++) {
    cout << "(" << camino[i].first << ", " << camino[i].second << ") -> ";
  }
  cout << "(" << camino[camino.size() - 1].first << ", "
       << camino[camino.size() - 1].second << ")\n";
}

int main() {
  vector<vector<int>> laberinto = {{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                                   {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
                                   {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
                                   {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                                   {0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1},
                                   {1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
                                   {0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
                                   {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
                                   {0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
                                   {0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1},
                                   {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                                   {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}};
  int meta_x = 11;
  int meta_y = 11;
  int inicio_x = 0;
  int inicio_y = 0;
  vector<pair<int, int>> camino;
  vector<vector<bool>> visitadas(N, vector<bool>(N, false));

  printLaberinto(laberinto);
  if (recursivo(laberinto, inicio_x, inicio_y, meta_x, meta_y, visitadas,
                camino)) {
    cout << "Camino encontrado: " << endl;
    printCamino(camino);
  } else {
    cout << "No se encontro camino" << endl;
  }
  return 0;
}