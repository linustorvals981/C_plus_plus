#include <iostream>
#include <vector>

using namespace std;

const int N = 5;

bool esSeguro(int laberinto[N][N], int x, int y) {
  return (x >= 0 && x < N && y >= 0 && y < N && laberinto[x][y] == 1);
}

void imprimirSolucion(int sol[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cout << sol[i][j] << " ";
    }
    cout << endl;
  }
}

bool resolverLaberintoUtil(int laberinto[N][N], int x, int y, int sol[N][N]) {
  if (x == N - 1 && y == N - 1 && laberinto[x][y] == 1) {
    sol[x][y] = 1;
    return true;
  }

  if (esSeguro(laberinto, x, y)) {
    sol[x][y] = 1;

    if (resolverLaberintoUtil(laberinto, x + 1, y, sol)) {
      return true;
    }

    if (resolverLaberintoUtil(laberinto, x, y + 1, sol)) {
      return true;
    }

    sol[x][y] = 0;
    return false;
  }

  return false;
}

bool resolverLaberinto(int laberinto[N][N]) {
  int sol[N][N] = {0};

  if (resolverLaberintoUtil(laberinto, 0, 0, sol) == false) {
    cout << "Solución no existe" << endl;
    return false;
  }

  imprimirSolucion(sol);
  return true;
}

int main() {
  int laberinto[N][N] = {
      {1, 1, 0, 0, 1}, {0, 1, 1, 1, 1}, {0, 0, 0, 0, 1},
      {1, 1, 1, 1, 1}, {1, 1, 1, 1, 1},
  };

  resolverLaberinto(laberinto);

  return 0;
}