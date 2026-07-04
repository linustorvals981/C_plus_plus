#include <iostream>
#include <stack>

using namespace std;

struct Nodo {
  int dato;
  float promedio;
  Nodo *siguiente;
};

int main() {
  stack<Nodo *> pila;

  Nodo *primero = new Nodo{20, 12.43f, nullptr};
  pila.push(primero);
  pila.push(new Nodo{10, 20.3f, nullptr});
  pila.push(new Nodo{30, 21.56f, nullptr});
  pila.push(new Nodo{10, 90.43f, nullptr});
  pila.push(new Nodo{100, 120.43f, nullptr});
  pila.push(new Nodo{210, 132.43f, nullptr});

  pila.pop();

  while (!pila.empty()) {
    Nodo *top = pila.top();
    cout << "Dato: " << top->dato << endl;
    cout << "Promedio: " << top->promedio << endl;
    pila.pop();
  }

  return 0;
}
