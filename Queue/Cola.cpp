#include <iostream>
#include <string>

using namespace std;

class Nodo {
public:
  string nombre;
  string servicio;
  Nodo *sig;

  Nodo(string nom, string serv) {
    nombre = nom;
    servicio = serv;
    sig = nullptr;
  }
};

class Cola {
private:
  Nodo *inicio;
  Nodo *fin;
  int longitud;

  Cola() {
    inicio = nullptr;
    fin = nullptr;
    longitud = 0;
  }

  ~Cola() {
    while (!vacia()) {
      dequeue();
    }
  }

  bool vacia() { return inicio == nullptr; }

  void enqueue(string nombre, string servicio) {
    Nodo *nuevo = new Nodo(nombre, servicio);
    if (vacia()) {
      inicio = nuevo;
      fin = nuevo;
    } else {
      fin->sig = nuevo;
      fin = nuevo;
    }
    longitud++;
  }

  void dequeue() {
    if (vacia()) {
      cout << "Cola vacia" << endl;
      return;
    }
    Nodo *temp = inicio;
    inicio = inicio->sig;
    delete temp;
    longitud--;
  }

  void mostrar() {
    Nodo *aux = inicio;
    while (aux != nullptr) {
      cout << aux->nombre << " " << aux->servicio << endl;
      aux = aux->sig;
    }
  }
};