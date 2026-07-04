#include <iostream>
#include <string>

using namespace std;

struct Nodo {
  string url;
  Nodo *siguiente;
  Nodo *anterior;
};

class Stack {
private:
  Nodo *tope;

public:
  Stack() : tope(nullptr) {}

  void push(string url) {
    Nodo *nuevo = new Nodo;
    nuevo->url = url;
    nuevo->siguiente = tope;
    nuevo->anterior = nullptr;
    if (tope != nullptr) {
      tope->anterior = nuevo;
    }
    tope = nuevo;
    cout << "Se ha anadido a la pila: " << url << endl;
  }

  void pop() {
    if (tope == nullptr) {
      cout << "La pila esta vacia." << endl;
    } else {
      Nodo *temp = tope;
      tope = tope->siguiente;
      if (tope != nullptr) {
        tope->anterior = nullptr;
      }
      delete temp;
      cout << "Se ha eliminado de la pila." << endl;
    }
  }

  Nodo *peak() {
    if (tope == nullptr) {
      cout << "La pila esta vacia." << endl;
    } else {
      return tope;
    }
  }
};

int main() {
  Stack miPila;
  miPila.push("https://www.google.com");
  miPila.push("https://www.facebook.com");
  miPila.push("https://www.twitter.com");
  miPila.peak();
  miPila.pop();
  miPila.peak();
  miPila.pop();

  return 0;
}