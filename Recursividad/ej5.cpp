#include <iostream>

using namespace std;

int contarDigitos(int n) {
  if (n < 10)
    return 1;
  return 1 + contarDigitos(n / 10);
}

int main() {
  int n;
  cout << "Ingresa un numero: ";
  cin >> n;
  cout << "Numero de digitos: " << contarDigitos(n) << '\n';
  return 0;
}