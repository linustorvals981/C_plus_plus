#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

struct Nodo {
  int numero;
  int indice;
  Nodo *sig;

  Nodo(int num, int idx) {
    numero = num;
    indice = idx;
    sig = nullptr;
  }
};

class Lista {

private:
  Nodo *head;
  int longitud;

public:
  Lista() {
    head = nullptr;
    longitud = 0;
  }

  ~Lista() {
    Nodo *tmp;
    while (head != nullptr) {
      tmp = head;
      head = head->sig;
      delete tmp;
    }
  }

  void inserta_final(int numero) {
    Nodo *tmp = new Nodo(numero, longitud);

    if (head == nullptr) {
      head = tmp;
    } else {
      Nodo *last = head;
      while (last->sig != nullptr) {
        last = last->sig;
      }
      last->sig = tmp;
    }
    longitud++;
  }

  void print() {
    Nodo *tmp = head;
    while (tmp != nullptr) {
      cout << tmp->numero << " ";
      tmp = tmp->sig;
    }
    cout << endl;
  }

  int linear_search(int num) {
    Nodo *tmp = head;

    while (tmp != nullptr) {
      if (tmp->numero == num) {
        return tmp->indice;
      }
      tmp = tmp->sig;
    }
    return -1;
  }
};

int main() {
  Lista nums = Lista();

  srand(time(0));

  for (int i = 0; i < 100; i++) {
    nums.inserta_final(rand() % 100);
  }

  nums.print();

  int num = rand() % 100;
  cout << "Numero a buscar: " << num << endl;

  int resultado = nums.linear_search(num);
  if (resultado != -1) {
    cout << "Encontrado en el indice: " << resultado << endl;
  } else {
    cout << "Numero no encontrado en la lista." << endl;
  }

  return 0;
}