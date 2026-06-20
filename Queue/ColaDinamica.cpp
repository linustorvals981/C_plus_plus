// ============================================================
//  colas.cpp
//  Implementación de Cola Estática (arreglo) y
//  Cola Dinámica (nodos enlazados) en C++
//  Materia: Estructuras de Datos
// ============================================================

#include <iostream>
#include <stdexcept> // std::underflow_error, std::overflow_error
#include <string>

// ============================================================
// SECCIÓN 1 — COLA ESTÁTICA (arreglo circular)
// ============================================================

/**
 * @class ColaEstatica
 * @brief Cola de capacidad fija implementada con un arreglo circular.
 *
 * Utiliza dos índices (frente y final) para seguir la posición
 * del primer y último elemento dentro del arreglo.
 * El arreglo es circular para reutilizar posiciones liberadas
 * por dequeue sin desplazar elementos.
 *
 * @tparam T  Tipo de dato almacenado en la cola.
 * @tparam CAP  Capacidad máxima de la cola.
 */
template <typename T, int CAP> class ColaEstatica {
private:
  T datos[CAP]; // Arreglo interno de almacenamiento
  int frente;   // Índice del primer elemento
  int fin;      // Índice de la siguiente posición libre
  int conteo;   // Cantidad actual de elementos

public:
  // --------------------------------------------------------
  // Constructor
  // --------------------------------------------------------
  ColaEstatica() : frente(0), fin(0), conteo(0) {}

  // --------------------------------------------------------
  // isEmpty — ¿Está vacía la cola?
  // Complejidad: O(1)
  // --------------------------------------------------------
  bool isEmpty() const { return conteo == 0; }

  // --------------------------------------------------------
  // isFull — ¿Está llena la cola?
  // Complejidad: O(1)
  // --------------------------------------------------------
  bool isFull() const { return conteo == CAP; }

  // --------------------------------------------------------
  // size — Número de elementos actuales
  // Complejidad: O(1)
  // --------------------------------------------------------
  int size() const { return conteo; }

  // --------------------------------------------------------
  // enqueue — Insertar elemento al final
  // Complejidad: O(1)
  // @throws std::overflow_error si la cola está llena
  // --------------------------------------------------------
  void enqueue(const T &valor) {
    if (isFull()) {
      throw std::overflow_error("enqueue: la cola estatica esta llena.");
    }
    datos[fin] = valor;
    fin = (fin + 1) % CAP; // Avance circular
    ++conteo;
  }

  // --------------------------------------------------------
  // dequeue — Eliminar y retornar el elemento del frente
  // Complejidad: O(1)
  // @throws std::underflow_error si la cola está vacía
  // --------------------------------------------------------
  T dequeue() {
    if (isEmpty()) {
      throw std::underflow_error("dequeue: la cola estatica esta vacia.");
    }
    T valor = datos[frente];
    frente = (frente + 1) % CAP; // Avance circular
    --conteo;
    return valor;
  }

  // --------------------------------------------------------
  // front — Consultar el frente sin eliminar
  // Complejidad: O(1)
  // @throws std::underflow_error si la cola está vacía
  // --------------------------------------------------------
  T front() const {
    if (isEmpty()) {
      throw std::underflow_error("front: la cola estatica esta vacia.");
    }
    return datos[frente];
  }

  // --------------------------------------------------------
  // mostrar — Imprimir todos los elementos en orden
  // Complejidad: O(n)
  // --------------------------------------------------------
  void mostrar(const std::string &nombre = "ColaEstatica") const {
    std::cout << nombre << " [frente -> fin]: ";
    if (isEmpty()) {
      std::cout << "(vacia)";
    } else {
      for (int i = 0; i < conteo; ++i) {
        std::cout << datos[(frente + i) % CAP];
        if (i < conteo - 1)
          std::cout << " -> ";
      }
    }
    std::cout << '\n';
  }
};

// ============================================================
// SECCIÓN 2 — COLA DINÁMICA (lista enlazada simple)
// ============================================================

/**
 * @struct Nodo
 * @brief Unidad de almacenamiento para la cola dinámica.
 *
 * Cada nodo contiene un dato y un puntero al siguiente nodo.
 *
 * @tparam T  Tipo de dato almacenado.
 */
template <typename T> struct Nodo {
  T dato;             // Valor almacenado
  Nodo<T> *siguiente; // Puntero al nodo siguiente

  // Constructor por dato
  explicit Nodo(const T &valor) : dato(valor), siguiente(nullptr) {}
};

/**
 * @class ColaDinamica
 * @brief Cola de tamaño ilimitado implementada con nodos enlazados.
 *
 * Se mantienen dos punteros: cabeza (frente de la cola) y
 * cola (último nodo). Las inserciones ocurren al final y las
 * eliminaciones al frente, ambas en O(1).
 *
 * @tparam T  Tipo de dato almacenado en la cola.
 */
template <typename T> class ColaDinamica {
private:
  Nodo<T> *cabeza; // Puntero al primer elemento (frente)
  Nodo<T> *cola;   // Puntero al último elemento (fin)
  int conteo;      // Cantidad actual de elementos

public:
  // --------------------------------------------------------
  // Constructor
  // --------------------------------------------------------
  ColaDinamica() : cabeza(nullptr), cola(nullptr), conteo(0) {}

  // --------------------------------------------------------
  // Destructor — libera toda la memoria dinámica
  // --------------------------------------------------------
  ~ColaDinamica() {
    while (!isEmpty()) {
      dequeue();
    }
  }

  // --------------------------------------------------------
  // isEmpty — ¿Está vacía la cola?
  // Complejidad: O(1)
  // --------------------------------------------------------
  bool isEmpty() const { return cabeza == nullptr; }

  // --------------------------------------------------------
  // size — Número de elementos actuales
  // Complejidad: O(1)
  // --------------------------------------------------------
  int size() const { return conteo; }

  // --------------------------------------------------------
  // enqueue — Insertar elemento al final
  // Complejidad: O(1)
  // @throws std::bad_alloc si falla la reserva de memoria
  // --------------------------------------------------------
  void enqueue(const T &valor) {
    Nodo<T> *nuevo = new Nodo<T>(valor); // Puede lanzar std::bad_alloc
    if (isEmpty()) {
      cabeza = cola = nuevo;
    } else {
      cola->siguiente = nuevo;
      cola = nuevo;
    }
    ++conteo;
  }

  // --------------------------------------------------------
  // dequeue — Eliminar y retornar el elemento del frente
  // Complejidad: O(1)
  // @throws std::underflow_error si la cola está vacía
  // --------------------------------------------------------
  T dequeue() {
    if (isEmpty()) {
      throw std::underflow_error("dequeue: la cola dinamica esta vacia.");
    }
    Nodo<T> *tmp = cabeza;
    T valor = tmp->dato;
    cabeza = cabeza->siguiente;
    if (cabeza == nullptr) { // La cola quedó vacía
      cola = nullptr;
    }
    delete tmp;
    --conteo;
    return valor;
  }

  // --------------------------------------------------------
  // front — Consultar el frente sin eliminar
  // Complejidad: O(1)
  // @throws std::underflow_error si la cola está vacía
  // --------------------------------------------------------
  T front() const {
    if (isEmpty()) {
      throw std::underflow_error("front: la cola dinamica esta vacia.");
    }
    return cabeza->dato;
  }

  // --------------------------------------------------------
  // mostrar — Imprimir todos los elementos en orden
  // Complejidad: O(n)
  // --------------------------------------------------------
  void mostrar(const std::string &nombre = "ColaDinamica") const {
    std::cout << nombre << " [frente -> fin]: ";
    if (isEmpty()) {
      std::cout << "(vacia)";
    } else {
      Nodo<T> *actual = cabeza;
      while (actual != nullptr) {
        std::cout << actual->dato;
        if (actual->siguiente)
          std::cout << " -> ";
        actual = actual->siguiente;
      }
    }
    std::cout << '\n';
  }
};

// ============================================================
// SECCIÓN 3 — PROGRAMA PRINCIPAL (demo)
// ============================================================

// Función auxiliar para imprimir separadores visuales
void separador(const std::string &titulo) {
  std::cout << "\n==============================\n";
  std::cout << "  " << titulo << '\n';
  std::cout << "==============================\n";
}

int main() {
  std::cout << "============================================================\n";
  std::cout << "   DEMOSTRACIÓN DE COLAS EN C++\n";
  std::cout << "   Cola Estática (arreglo) | Cola Dinámica (lista enlazada)\n";
  std::cout << "============================================================\n";

  // ----------------------------------------------------------
  // DEMO 1 — Cola Estática con enteros (capacidad 5)
  // ----------------------------------------------------------
  separador("Cola Estatica — enteros (CAP=5)");

  ColaEstatica<int, 5> ceInt;

  std::cout << "\n[1] Estado inicial:\n";
  ceInt.mostrar();
  std::cout << "  isEmpty: " << (ceInt.isEmpty() ? "SI" : "NO") << '\n';
  std::cout << "  isFull:  " << (ceInt.isFull() ? "SI" : "NO") << '\n';

  std::cout << "\n[2] Insertando 10, 20, 30, 40, 50:\n";
  ceInt.enqueue(10);
  ceInt.enqueue(20);
  ceInt.enqueue(30);
  ceInt.enqueue(40);
  ceInt.enqueue(50);
  ceInt.mostrar();
  std::cout << "  isFull: " << (ceInt.isFull() ? "SI" : "NO") << '\n';

  std::cout << "\n[3] front(): " << ceInt.front() << '\n';

  std::cout << "\n[4] dequeue() x2 -> extraidos: " << ceInt.dequeue() << ", "
            << ceInt.dequeue() << '\n';
  ceInt.mostrar();

  std::cout << "\n[5] Insertando 60, 70 (reutiliza posiciones circulares):\n";
  ceInt.enqueue(60);
  ceInt.enqueue(70);
  ceInt.mostrar();

  std::cout << "\n[6] Vaciando la cola:\n";
  while (!ceInt.isEmpty()) {
    std::cout << "  dequeue -> " << ceInt.dequeue() << '\n';
  }
  ceInt.mostrar();

  std::cout << "\n[7] Manejo de error — dequeue en cola vacia:\n";
  try {
    ceInt.dequeue();
  } catch (const std::underflow_error &e) {
    std::cout << "  Excepcion capturada: " << e.what() << '\n';
  }

  std::cout << "\n[8] Manejo de error — enqueue en cola llena:\n";
  ColaEstatica<int, 2> cePeq;
  cePeq.enqueue(1);
  cePeq.enqueue(2);
  try {
    cePeq.enqueue(3);
  } catch (const std::overflow_error &e) {
    std::cout << "  Excepcion capturada: " << e.what() << '\n';
  }

  // ----------------------------------------------------------
  // DEMO 2 — Cola Dinámica con strings
  // ----------------------------------------------------------
  separador("Cola Dinamica — strings (sin limite)");

  ColaDinamica<std::string> cdStr;

  std::cout << "\n[1] Estado inicial:\n";
  cdStr.mostrar();
  std::cout << "  isEmpty: " << (cdStr.isEmpty() ? "SI" : "NO") << '\n';

  std::cout << "\n[2] Insertando: Alfa, Beta, Gamma, Delta, Epsilon:\n";
  cdStr.enqueue("Alfa");
  cdStr.enqueue("Beta");
  cdStr.enqueue("Gamma");
  cdStr.enqueue("Delta");
  cdStr.enqueue("Epsilon");
  cdStr.mostrar();
  std::cout << "  Elementos: " << cdStr.size() << '\n';

  std::cout << "\n[3] front(): " << cdStr.front() << '\n';

  std::cout << "\n[4] dequeue() x3 -> extraidos:\n";
  std::cout << "  " << cdStr.dequeue() << '\n';
  std::cout << "  " << cdStr.dequeue() << '\n';
  std::cout << "  " << cdStr.dequeue() << '\n';
  cdStr.mostrar();

  std::cout << "\n[5] Insertando mas elementos (Zeta, Eta, Theta, Iota):\n";
  cdStr.enqueue("Zeta");
  cdStr.enqueue("Eta");
  cdStr.enqueue("Theta");
  cdStr.enqueue("Iota");
  cdStr.mostrar();
  std::cout << "  Elementos: " << cdStr.size() << '\n';

  std::cout << "\n[6] Vaciando la cola:\n";
  while (!cdStr.isEmpty()) {
    std::cout << "  dequeue -> " << cdStr.dequeue() << '\n';
  }
  cdStr.mostrar();

  std::cout << "\n[7] Manejo de error — dequeue en cola vacia:\n";
  try {
    cdStr.dequeue();
  } catch (const std::underflow_error &e) {
    std::cout << "  Excepcion capturada: " << e.what() << '\n';
  }

  // ----------------------------------------------------------
  // DEMO 3 — Comparativa directa con el mismo conjunto de datos
  // ----------------------------------------------------------
  separador("Comparativa directa — mismo conjunto de datos");

  ColaEstatica<int, 8> ceComp;
  ColaDinamica<int> cdComp;

  std::cout << "\nInsertar 1..6 en ambas colas:\n";
  for (int i = 1; i <= 6; ++i) {
    ceComp.enqueue(i);
    cdComp.enqueue(i);
  }
  ceComp.mostrar("  Estatica");
  cdComp.mostrar("  Dinamica");

  std::cout << "\nExtraer 3 elementos de cada una:\n";
  for (int i = 0; i < 3; ++i) {
    ceComp.dequeue();
    cdComp.dequeue();
  }
  ceComp.mostrar("  Estatica");
  cdComp.mostrar("  Dinamica");

  std::cout << "\nInsertar 7, 8, 9 en ambas:\n";
  ceComp.enqueue(7);
  cdComp.enqueue(7);
  ceComp.enqueue(8);
  cdComp.enqueue(8);
  ceComp.enqueue(9);
  cdComp.enqueue(9);
  ceComp.mostrar("  Estatica");
  cdComp.mostrar("  Dinamica");

  std::cout
      << "\n============================================================\n";
  std::cout << "  FIN DE LA DEMOSTRACIÓN\n";
  std::cout << "============================================================\n";

  return 0;
}
