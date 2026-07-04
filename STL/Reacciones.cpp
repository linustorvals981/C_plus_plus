#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Nodo {
  string sustancia;
  int reactividad;
};

stack<Nodo> simularReacciones(vector<Nodo> ingredientes) {
  stack<Nodo> pila;

  for (Nodo tmp : ingredientes) {
    bool sigue_cayendo = true;

    while (sigue_cayendo) {
      if (pila.empty()) {
        pila.push(tmp);
        sigue_cayendo = false;
      } else {
        Nodo &top = pila.top();
      }
    }
  }
}