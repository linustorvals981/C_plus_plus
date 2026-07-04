#include <cmath>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct Nodo {
  string sustancia;
  int reactividad;
};

stack<Nodo> simularReacciones(vector<Nodo> ingredientes) {
  stack<Nodo> pila;

  for (Nodo nuevo : ingredientes) {

    bool sigue_cayendo = true;

    while (sigue_cayendo) {
      if (pila.empty()) {
        pila.push(nuevo);
        sigue_cayendo = false;
      } else {
        Nodo &top = pila.top();
        bool mismo_signo = (top.reactividad > 0) == (nuevo.reactividad > 0);

        if (mismo_signo) {
          pila.push(nuevo);
          sigue_cayendo = false;
        } else {
          int abs_top = std::abs(top.reactividad);
          int abs_nuevo = std::abs(nuevo.reactividad);

          if (abs_top == abs_nuevo) {
            pila.pop();
            sigue_cayendo = false;
          }

          else if (abs_top > abs_nuevo) {
            int signo_top = (top.reactividad > 0) ? 1 : -1;
            top.reactividad = signo_top * (abs_top - abs_nuevo);
            sigue_cayendo = false;
          } else {
            int signo_nuevo = (nuevo.reactividad > 0) ? 1 : -1;
            nuevo.reactividad = signo_nuevo * (abs_nuevo - abs_top);
            pila.pop();
          }
        }
      }
    }
  }

  return pila;
}

int main() {
  std::vector<Nodo> ingredientes = {{"Plomo", 6},
                                    {"Magnesio", 3},
                                    {"Acido Suave", -3},
                                    {"Super-Base", -8},
                                    {"Sal de Mesa", 5}};

  std::stack<Nodo> resultado = simularReacciones(ingredientes);

  std::cout << "=== ESTADO FINAL DE LA PILA ===\n";
  std::cout << "Tamaño: " << resultado.size() << "\n\n";

  std::stack<Nodo> temp = resultado;
  while (!temp.empty()) {
    Nodo n = temp.top();
    temp.pop();
    std::cout << "{ \"" << n.sustancia << "\", " << n.reactividad << " }\n";
  }

  return 0;
}