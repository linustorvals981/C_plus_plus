#include <iostream>

using namespace std;

int caminosEscaleras(int n) {
  if (n == 0 || n == 1 || n == 2)
    return n;

  return caminosEscaleras(n - 1) + caminosEscaleras(n - 2);
}

int main() {
  int n;
  cout << "Ingresa numero de escalones: ";
  cin >> n;
  cout << "Numero de caminos: " << caminosEscaleras(n) << endl;
  return 0;
}