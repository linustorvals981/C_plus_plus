#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

struct Nodo {
  int numero;
  int indice;
  Nodo *sig;
  Nodo *anterior;

  Nodo(int num, int idx) {
    numero = num;
    indice = idx;
    sig = nullptr;
    anterior = nullptr;
  }
};

class Lista {

private:
  Nodo *head;
  Nodo *tail;
  int longitud;

public:
  Lista() {
    head = nullptr;
    tail = nullptr;
    longitud = 0;
  }

  ~Lista() {
    Nodo *tmp;
    while (head != nullptr) {
      tmp = head;
      head = head->sig;
      delete tmp;
    }
    tail = nullptr;
  }

  void inserta_final(int numero) {
    Nodo *tmp = new Nodo(numero, longitud);

    if (head == nullptr) {
      head = tmp;
      tail = tmp;
    } else {
      tmp->anterior = tail;
      tail->sig = tmp;
      tail = tmp;
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

  void print_inverso() {
    Nodo *tmp = tail;
    while (tmp != nullptr) {
      cout << tmp->numero << " ";
      tmp = tmp->anterior;
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

  cout << "Lista (adelante): " << endl;
  nums.print();

  cout << "Lista (atras): " << endl;
  nums.print_inverso();

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
