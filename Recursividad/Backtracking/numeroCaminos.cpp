#include <iostream>

using namespace std;

int numeroCaminos(int fila, int col) {
  if (fila == 0 || col == 0)
    return 0;
  if (fila == 1 || col == 1)
    return 1;
  return numeroCaminos(fila - 1, col) + numeroCaminos(fila, col - 1);
}

int main() {
  int filas, columnas;
  cout << "Ingresa numero de filas: ";
  cin >> filas;
  cout << "Ingresa numero de columnas: ";
  cin >> columnas;
  cout << "Numero de caminos: " << numeroCaminos(filas, columnas) << endl;

  return 0;
}