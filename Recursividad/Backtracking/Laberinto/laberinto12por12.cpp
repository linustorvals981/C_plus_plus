#include <iostream>
#include <vector>

using namespace std;

// Solo las 4 direcciones cardinales (arriba, abajo, izquierda, derecha),
// que son las que realmente se usan en el bucle del recursivo.
const int mov_x[] = {1, 0, -1, 0};
const int mov_y[] = {0, 1, 0, -1};
const int N = 12;

bool validation(const vector<vector<int>> &laberinto, int x, int y,
                const vector<vector<bool>> &visitadas) {
  int filas = laberinto.size();
  int columnas = laberinto[0].size();

  return (x >= 0 && x < filas && y >= 0 && y < columnas &&
          laberinto[x][y] == 0 && !visitadas[x][y]);
}

// IMPORTANTE: 'visitadas' ahora se pasa POR REFERENCIA.
// Antes se pasaba por valor: cada llamada recibía una copia, así que cuando
// una rama fallaba y regresaba false, todas las marcas de "visitado" que
// había hecho se perdían. Eso permitía que otras ramas del backtracking
// volvieran a pisar las mismas celdas una y otra vez, generando recursión
// exponencial (y riesgo real de stack overflow en laberintos con ciclos).
// Al pasarla por referencia, una vez que una celda queda marcada como
// visitada, ninguna otra rama la vuelve a intentar: si ya sabemos que desde
// ahí no se llega a la meta, no tiene caso volver a probar.
bool recursivo(const vector<vector<int>> &laberinto, int x, int y, int meta_x,
               int meta_y, vector<vector<bool>> &visitadas,
               vector<pair<int, int>> &camino) {
  // Primero validamos que la celda actual sea válida (dentro de rango,
  // transitable y no visitada). Antes se comparaba contra la meta ANTES
  // de validar, lo cual podía aceptar una meta fuera de rango o en una
  // pared sin darse cuenta.
  if (!validation(laberinto, x, y, visitadas)) {
    return false;
  }

  visitadas[x][y] = true;
  camino.push_back({x, y});

  if (x == meta_x && y == meta_y) {
    return true;
  }

  for (int i = 0; i < 4; i++) {
    int new_x = x + mov_x[i];
    int new_y = y + mov_y[i];

    if (recursivo(laberinto, new_x, new_y, meta_x, meta_y, visitadas, camino)) {
      return true;
    }
  }

  // Si ninguna dirección funcionó, esta celda no es parte del camino final,
  // así que la sacamos del camino (pero se queda marcada como visitada
  // para no volver a intentarla desde otra rama).
  camino.pop_back();
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
  for (size_t i = 0; i < camino.size(); i++) {
    cout << camino[i].first << " " << camino[i].second << endl;
  }
}

int main() {
  // Caso de prueba: laberinto de 12x12 con forma de serpiente.
  // Las filas pares (0,2,4,6,8,10) están completamente abiertas.
  // Las filas impares tienen una sola abertura, alternando entre el
  // extremo izquierdo y el derecho, forzando un camino en zigzag y
  // obligando al algoritmo a hacer backtracking en los callejones
  // sin salida antes de encontrar la abertura correcta.
  vector<vector<int>> laberinto = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // fila 0
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // fila 1 (abertura a la derecha)
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // fila 2
      {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // fila 3 (abertura a la izquierda)
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // fila 4
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // fila 5 (abertura a la derecha)
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // fila 6
      {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // fila 7 (abertura a la izquierda)
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // fila 8
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // fila 9 (abertura a la derecha)
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // fila 10
      {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0}, // fila 11 (meta en col 11)
  };

  int inicio_x = 0;
  int inicio_y = 0;
  int meta_x = 11;
  int meta_y = 11;

  vector<pair<int, int>> camino;
  vector<vector<bool>> visitadas(N, vector<bool>(N, false));

  cout << "Laberinto (12x12):" << endl;
  printLaberinto(laberinto);
  cout << endl;

  if (recursivo(laberinto, inicio_x, inicio_y, meta_x, meta_y, visitadas,
                camino)) {
    cout << "Camino encontrado (" << camino.size() << " pasos):" << endl;
    printCamino(camino);
  } else {
    cout << "No se encontro camino" << endl;
  }

  return 0;
}