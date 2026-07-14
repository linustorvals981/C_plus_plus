#include <iostream>

using namespace std;

void imprimirReversa(string frase, int i) {
  int n = frase.size();
  if (i == n) {
    cout << '\n';
    return;
  }

  cout << frase[n - 1 - i];

  imprimirReversa(frase, i + 1);
}

int main() {
  string frase;
  cout << "Ingresa una frase: ";
  cin >> frase;
  imprimirReversa(frase, 0);
  return 0;
}