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

public:
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
    if (inicio == nullptr)
      fin = nullptr;
    delete temp;
    longitud--;
  }

  void mostrar() {
    if (vacia()) {
      cout << "La cola esta vacia." << endl;
      return;
    }
    cout << "--- Cola (frente -> fin) ---" << endl;
    Nodo *aux = inicio;
    int i = 1;
    while (aux != nullptr) {
      cout << i++ << ". " << aux->nombre << " | " << aux->servicio << endl;
      aux = aux->sig;
    }
    cout << "Longitud: " << longitud << endl;
  }
};

int main() {
  Cola cola;

  cout << "=== Sistema de atencion al cliente ===" << endl << endl;

  // Encolar clientes
  cola.enqueue("Ana Lopez", "Caja");
  cola.enqueue("Carlos Ruiz", "Informes");
  cola.enqueue("Maria Gomez", "Prestamos");
  cola.enqueue("Pedro Saenz", "Caja");

  cout << "Estado inicial:" << endl;
  cola.mostrar();

  // Atender al primero
  cout << "\nAtendiendo al primer cliente..." << endl;
  cola.dequeue();
  cola.mostrar();

  // Encolar otro
  cout << "\nLlega un nuevo cliente:" << endl;
  cola.enqueue("Laura Diaz", "Informes");
  cola.mostrar();

  // Vaciar la cola
  cout << "\nAtendiendo a todos los clientes restantes..." << endl;
  while (!cola.vacia()) {
    cola.dequeue();
  }

  // Intentar desencolar en cola vacia
  cout << "\nIntento de dequeue en cola vacia:" << endl;
  cola.dequeue();

  return 0;
}