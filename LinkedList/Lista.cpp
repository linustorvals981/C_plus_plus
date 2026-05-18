#include <iostream>
#include <limits>
#include <string>

using namespace std;

struct Tarea {
  string titulo;
  string descripcion;
  bool completada;
  struct Tarea *siguiente;
};

struct Lista {
  int longitud;
  struct Tarea *cabeza;
};

// ─────────────────────────────────────────────
// Función auxiliar: descarta el resto de la línea
// actual en cin antes de usar getline.
// Reemplaza el fflush(stdin) que era UB.
// ─────────────────────────────────────────────
void limpiarBuffer() { cin.ignore(numeric_limits<streamsize>::max(), '\n'); }

Tarea *crearNodo() {
  Tarea *nuevo = new Tarea;

  cout << "Ingrese el titulo de la tarea: ";
  limpiarBuffer(); // FIX #1: reemplaza fflush(stdin)
  getline(cin, nuevo->titulo);

  cout << "Ingrese la descripcion de la tarea: ";
  limpiarBuffer(); // FIX #1: reemplaza fflush(stdin)
  getline(cin, nuevo->descripcion);

  nuevo->completada = false;
  nuevo->siguiente = nullptr;

  return nuevo;
}

void enlazarNodoBack(Lista *&lista) {
  if (lista == nullptr) {
    lista = new Lista;
    lista->longitud = 1;
    lista->cabeza = crearNodo();
  } else if (lista->cabeza == nullptr) {
    lista->longitud = 1;
    lista->cabeza = crearNodo();
  } else {
    Tarea *aux = lista->cabeza;
    while (aux->siguiente != nullptr) {
      aux = aux->siguiente;
    }
    aux->siguiente = crearNodo();
    lista->longitud++;
  }
}

void enlazarNodoFront(Lista *&lista) {
  if (lista == nullptr) {
    lista = new Lista;
    lista->longitud = 1;
    lista->cabeza = crearNodo();
  } else {
    if (lista->cabeza == nullptr) {
      lista->cabeza = crearNodo();
      lista->longitud = 1; // FIX #3: asignar 1 en lugar de incrementar
                           // valor potencialmente no inicializado
    } else {
      Tarea *aux = lista->cabeza;
      lista->cabeza = crearNodo();
      lista->cabeza->siguiente = aux;
      lista->longitud++;
    }
  }
}

void mostrarLista(Lista *&lista) {
  if (lista == nullptr || lista->cabeza == nullptr) { // FIX #4: verifica cabeza
    cout << "La lista esta vacia.\n";
    return;
  }

  Tarea *aux = lista->cabeza;
  while (aux != nullptr) {
    cout << "Titulo: " << aux->titulo << "\n";
    cout << "Descripcion: " << aux->descripcion << "\n";
    if (aux->completada) {
      cout << "La tarea esta completada.\n";
    } else {
      cout << "La tarea no esta completada.\n";
    }
    aux = aux->siguiente;
  }
}

void eliminarTarea(Lista *&lista) {
  if (lista == nullptr || lista->cabeza == nullptr) {
    cout << "La lista esta vacia.\n";
    return;
  }

  string titulo;
  cout << "Ingrese el nombre de la tarea a eliminar: "; // FIX #5: "nompre" →
                                                        // "nombre"
  limpiarBuffer(); // FIX #1: reemplaza fflush(stdin)
  getline(cin, titulo);

  Tarea *actual = lista->cabeza;
  Tarea *anterior = nullptr;

  while (actual != nullptr) {
    if (actual->titulo == titulo) {
      if (anterior == nullptr) {
        lista->cabeza = actual->siguiente;
      } else {
        anterior->siguiente = actual->siguiente;
      }
      delete actual;
      lista->longitud--;
      return;
    }
    anterior = actual;
    actual = actual->siguiente;
  }

  // FIX #2: se elimina el bloque else inalcanzable.
  // Si llegamos aquí, el while terminó con actual == nullptr,
  // lo que significa que no se encontró la tarea.
  cout << "La tarea no se encontro.\n";
}

// ─────────────────────────────────────────────
// FIX #6: función para liberar toda la memoria
// ─────────────────────────────────────────────
void destruirLista(Lista *&lista) {
  if (lista == nullptr)
    return;

  Tarea *actual = lista->cabeza;
  while (actual != nullptr) {
    Tarea *siguiente = actual->siguiente;
    delete actual;
    actual = siguiente;
  }
  delete lista;
  lista = nullptr;
}

void marcarCompletada(Lista *&lista) {
  if (lista == nullptr || lista->cabeza == nullptr) {
    cout << "La lista esta vacia.\n";
    return;
  }

  string titulo;
  cout << "Ingrese el nombre de la tarea a marcar como completada: ";
  limpiarBuffer();
  getline(cin, titulo);

  Tarea *actual = lista->cabeza;
  while (actual != nullptr) {
    if (actual->titulo == titulo) {
      actual->completada = true;
      return;
    }
    actual = actual->siguiente;
  }

  cout << "La tarea no se encontro.\n";
}