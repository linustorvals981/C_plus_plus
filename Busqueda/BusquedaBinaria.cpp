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

  void bubble_sort() {
    if (head == nullptr || head->sig == nullptr)
      return;

    bool intercambio;
    do {
      intercambio = false;
      Nodo *tmp = head;
      while (tmp->sig != nullptr) {
        if (tmp->numero > tmp->sig->numero) {
          swap(tmp->numero, tmp->sig->numero);
          intercambio = true;
        }
        tmp = tmp->sig;
      }
    } while (intercambio);

    Nodo *tmp = head;
    int idx = 0;
    while (tmp != nullptr) {
      tmp->indice = idx++;
      tmp = tmp->sig;
    }
  }

  Nodo *get_nodo(int pos) {
    Nodo *tmp = head;
    for (int i = 0; i < pos; i++) {
      tmp = tmp->sig;
    }
    return tmp;
  }

  int binary_search(int num) {
    int izq = 0;
    int der = longitud - 1;

    while (izq <= der) {
      int mid = izq + (der - izq) / 2;
      Nodo *nodo_mid = get_nodo(mid);

      if (nodo_mid->numero == num) {
        return nodo_mid->indice;
      } else if (nodo_mid->numero < num) {
        izq = mid + 1;
      } else {
        der = mid - 1;
      }
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

  cout << "Lista desordenada:" << endl;
  nums.print();

  nums.bubble_sort();

  cout << "Lista ordenada:" << endl;
  nums.print();

  int num = rand() % 100;
  cout << "Numero a buscar: " << num << endl;

  int resultado = nums.binary_search(num);
  if (resultado != -1) {
    cout << "Encontrado en el indice: " << resultado << endl;
  } else {
    cout << "Numero no encontrado en la lista." << endl;
  }

  return 0;
}