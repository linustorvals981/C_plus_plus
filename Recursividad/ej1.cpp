#include <iostream>

using namespace std;

void cuentaRegresiva(int n) {
  if (n == 0) {
    cout << "Despegue!\n";
    return;
  }
  cout << n << ", ";
  cuentaRegresiva(n - 1);
}

int main() {
  int n;
  cin >> n;
  cuentaRegresiva(n);
  return 0;
}