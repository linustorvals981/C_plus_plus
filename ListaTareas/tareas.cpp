#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <cctype>

// Usamos solo tipos y utilidades estándar básicas.
using std::cin;
using std::cout;
using std::endl;
using std::string;

// ============================================================================
// ESTRUCTURAS BASE (exactamente como se solicitaron)
// ============================================================================
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

// ============================================================================
// UTILIDADES GENERALES
// ============================================================================

// Crea una lista vacía.
// Complejidad: O(1)
Lista crearListaVacia() {
    Lista lista;
    lista.longitud = 0;
    lista.cabeza = nullptr;
    return lista;
}

// Crea un nuevo nodo en memoria dinámica.
// Complejidad: O(1)
Tarea* crearNodoTarea(const string& titulo, const string& descripcion, bool completada) {
    Tarea* nuevo = new Tarea;
    nuevo->titulo = titulo;
    nuevo->descripcion = descripcion;
    nuevo->completada = completada;
    nuevo->siguiente = nullptr;
    return nuevo;
}

// Convierte un carácter a minúscula de forma segura.
char aMinusculaSeguro(char c) {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
}

// Comparación alfabética ignorando mayúsculas/minúsculas.
// Retorna: -1 si a < b, 0 si iguales, 1 si a > b.
// Complejidad: O(k), donde k es la longitud del texto comparado.
int compararIgnorandoMayusculas(const string& a, const string& b) {
    const size_t n = a.size();
    const size_t m = b.size();
    const size_t minLen = (n < m) ? n : m;

    for (size_t i = 0; i < minLen; ++i) {
        char ca = aMinusculaSeguro(a[i]);
        char cb = aMinusculaSeguro(b[i]);
        if (ca < cb) return -1;
        if (ca > cb) return 1;
    }

    if (n < m) return -1;
    if (n > m) return 1;
    return 0;
}

// Verifica si texto contiene patrón ignorando mayúsculas/minúsculas.
// Complejidad: O(n*m) en el peor caso.
bool contieneIgnorandoMayusculas(const string& texto, const string& patron) {
    if (patron.empty()) return true;
    if (patron.size() > texto.size()) return false;

    for (size_t i = 0; i + patron.size() <= texto.size(); ++i) {
        bool coincide = true;
        for (size_t j = 0; j < patron.size(); ++j) {
            if (aMinusculaSeguro(texto[i + j]) != aMinusculaSeguro(patron[j])) {
                coincide = false;
                break;
            }
        }
        if (coincide) return true;
    }
    return false;
}

// Inserta una copia de una tarea al final usando un puntero tail local.
// Útil para clonar y fusionar en O(n).
// Complejidad: O(1) por inserción.
void anexarCopiaAlFinal(Lista& lista, Tarea*& ultimo, const Tarea& origen) {
    Tarea* nuevo = crearNodoTarea(origen.titulo, origen.descripcion, origen.completada);

    if (lista.cabeza == nullptr) {
        lista.cabeza = nuevo;
    } else {
        ultimo->siguiente = nuevo;
    }

    ultimo = nuevo;
    lista.longitud++;
}

// Verifica si la lista está vacía.
// Complejidad: O(1)
bool estaVacia(const Lista& lista) {
    return lista.cabeza == nullptr;
}

// ============================================================================
// GESTIÓN DE MEMORIA
// ============================================================================

// Vacía por completo la lista y libera toda la memoria.
// Cada delete es necesario porque cada nodo fue creado con new.
// Complejidad: O(n)
void vaciarLista(Lista& lista) {
    Tarea* actual = lista.cabeza;

    while (actual != nullptr) {
        Tarea* siguiente = actual->siguiente;
        delete actual;              // libera el nodo actual
        actual = siguiente;         // avanza
    }

    lista.cabeza = nullptr;
    lista.longitud = 0;
}

// ============================================================================
// INSERCIÓN
// ============================================================================

// Inserta al inicio.
// Antes:
// [cabeza] -> [A] -> [B] -> nullptr
// Después:
// [cabeza] -> [Nueva] -> [A] -> [B] -> nullptr
// Complejidad: O(1)
bool insertarAlInicio(Lista& lista, const string& titulo, const string& descripcion, bool completada) {
    Tarea* nuevo = crearNodoTarea(titulo, descripcion, completada);
    nuevo->siguiente = lista.cabeza;
    lista.cabeza = nuevo;
    lista.longitud++;
    return true;
}

// Inserta al final.
// Complejidad: O(n) porque debe recorrer hasta el último nodo.
bool insertarAlFinal(Lista& lista, const string& titulo, const string& descripcion, bool completada) {
    Tarea* nuevo = crearNodoTarea(titulo, descripcion, completada);

    if (lista.cabeza == nullptr) {
        lista.cabeza = nuevo;
        lista.longitud++;
        return true;
    }

    Tarea* actual = lista.cabeza;
    while (actual->siguiente != nullptr) {
        actual = actual->siguiente;
    }

    actual->siguiente = nuevo;
    lista.longitud++;
    return true;
}

// Inserta en una posición específica usando posición 1..longitud+1.
// Si posicion == 1 => inicio.
// Si posicion == longitud+1 => final.
// Complejidad: O(n)
bool insertarEnPosicion(Lista& lista, int posicion, const string& titulo, const string& descripcion, bool completada) {
    if (posicion < 1 || posicion > lista.longitud + 1) {
        return false;
    }

    if (posicion == 1) {
        return insertarAlInicio(lista, titulo, descripcion, completada);
    }

    if (posicion == lista.longitud + 1) {
        return insertarAlFinal(lista, titulo, descripcion, completada);
    }

    Tarea* nuevo = crearNodoTarea(titulo, descripcion, completada);
    Tarea* actual = lista.cabeza;

    for (int i = 1; i < posicion - 1; ++i) {
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
    lista.longitud++;
    return true;
}

// Inserta manteniendo orden alfabético por título.
// Complejidad: O(n)
bool insertarOrdenadoPorTitulo(Lista& lista, const string& titulo, const string& descripcion, bool completada) {
    Tarea* nuevo = crearNodoTarea(titulo, descripcion, completada);

    if (lista.cabeza == nullptr ||
        compararIgnorandoMayusculas(titulo, lista.cabeza->titulo) < 0) {
        nuevo->siguiente = lista.cabeza;
        lista.cabeza = nuevo;
        lista.longitud++;
        return true;
    }

    Tarea* actual = lista.cabeza;
    while (actual->siguiente != nullptr &&
           compararIgnorandoMayusculas(actual->siguiente->titulo, titulo) <= 0) {
        actual = actual->siguiente;
    }

    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
    lista.longitud++;
    return true;
}

// ============================================================================
// ELIMINACIÓN
// ============================================================================

// Elimina la primera tarea.
// Complejidad: O(1)
bool eliminarPrimera(Lista& lista) {
    if (lista.cabeza == nullptr) return false;

    Tarea* borrar = lista.cabeza;
    lista.cabeza = lista.cabeza->siguiente;
    delete borrar;
    lista.longitud--;
    return true;
}

// Elimina la última tarea.
// Complejidad: O(n)
bool eliminarUltima(Lista& lista) {
    if (lista.cabeza == nullptr) return false;

    if (lista.cabeza->siguiente == nullptr) {
        delete lista.cabeza;
        lista.cabeza = nullptr;
        lista.longitud = 0;
        return true;
    }

    Tarea* actual = lista.cabeza;
    while (actual->siguiente->siguiente != nullptr) {
        actual = actual->siguiente;
    }

    delete actual->siguiente;
    actual->siguiente = nullptr;
    lista.longitud--;
    return true;
}

// Elimina por posición 1..longitud.
// Complejidad: O(n)
bool eliminarPorPosicion(Lista& lista, int posicion) {
    if (posicion < 1 || posicion > lista.longitud || lista.cabeza == nullptr) {
        return false;
    }

    if (posicion == 1) {
        return eliminarPrimera(lista);
    }

    Tarea* actual = lista.cabeza;
    for (int i = 1; i < posicion - 1; ++i) {
        actual = actual->siguiente;
    }

    Tarea* borrar = actual->siguiente;
    actual->siguiente = borrar->siguiente;
    delete borrar;
    lista.longitud--;
    return true;
}

// Elimina por título exacto (primera coincidencia).
// Complejidad: O(n)
bool eliminarPorTitulo(Lista& lista, const string& titulo) {
    if (lista.cabeza == nullptr) return false;

    if (lista.cabeza->titulo == titulo) {
        return eliminarPrimera(lista);
    }

    Tarea* actual = lista.cabeza;
    while (actual->siguiente != nullptr && actual->siguiente->titulo != titulo) {
        actual = actual->siguiente;
    }

    if (actual->siguiente == nullptr) return false;

    Tarea* borrar = actual->siguiente;
    actual->siguiente = borrar->siguiente;
    delete borrar;
    lista.longitud--;
    return true;
}

// ============================================================================
// BÚSQUEDA
// ============================================================================

// Busca por título exacto.
// Complejidad: O(n)
Tarea* buscarPorTituloExacto(Lista& lista, const string& titulo) {
    Tarea* actual = lista.cabeza;
    while (actual != nullptr) {
        if (actual->titulo == titulo) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

// Búsqueda recursiva exacta.
// Complejidad: O(n)
Tarea* buscarRecursivo(Tarea* nodo, const string& titulo) {
    if (nodo == nullptr) return nullptr;
    if (nodo->titulo == titulo) return nodo;
    return buscarRecursivo(nodo->siguiente, titulo);
}

// Verifica existencia de una tarea por título exacto.
// Complejidad: O(n)
bool existeTarea(const Lista& lista, const string& titulo) {
    const Tarea* actual = lista.cabeza;
    while (actual != nullptr) {
        if (actual->titulo == titulo) return true;
        actual = actual->siguiente;
    }
    return false;
}

// Muestra coincidencias parciales por título.
// Complejidad: O(n*m)
int mostrarCoincidenciasParciales(const Lista& lista, const string& patron) {
    int encontrados = 0;
    const Tarea* actual = lista.cabeza;

    while (actual != nullptr) {
        if (contieneIgnorandoMayusculas(actual->titulo, patron)) {
            cout << "-----------------------------\n";
            cout << "Titulo: " << actual->titulo << '\n';
            cout << "Descripcion: " << actual->descripcion << '\n';
            cout << "Estado: " << (actual->completada ? "Completada" : "Pendiente") << '\n';
            ++encontrados;
        }
        actual = actual->siguiente;
    }

    return encontrados;
}

// ============================================================================
// ACTUALIZACIÓN
// ============================================================================

// Edita título.
// Complejidad: O(n) por búsqueda
bool editarTituloPorTitulo(Lista& lista, const string& tituloActual, const string& nuevoTitulo) {
    Tarea* nodo = buscarPorTituloExacto(lista, tituloActual);
    if (nodo == nullptr) return false;
    nodo->titulo = nuevoTitulo;
    return true;
}

// Edita descripción.
// Complejidad: O(n) por búsqueda
bool editarDescripcionPorTitulo(Lista& lista, const string& tituloActual, const string& nuevaDescripcion) {
    Tarea* nodo = buscarPorTituloExacto(lista, tituloActual);
    if (nodo == nullptr) return false;
    nodo->descripcion = nuevaDescripcion;
    return true;
}

// Cambia estado completada/pendiente.
// Complejidad: O(n) por búsqueda
bool cambiarEstadoPorTitulo(Lista& lista, const string& tituloActual, bool completada) {
    Tarea* nodo = buscarPorTituloExacto(lista, tituloActual);
    if (nodo == nullptr) return false;
    nodo->completada = completada;
    return true;
}

// ============================================================================
// VISUALIZACIÓN
// ============================================================================

// Imprime una tarea con formato limpio.
void imprimirTarea(const Tarea* tarea, int numero = -1) {
    if (tarea == nullptr) return;

    if (numero > 0) {
        cout << numero << ") ";
    }

    cout << "Titulo: " << tarea->titulo << '\n';
    cout << "   Descripcion: " << tarea->descripcion << '\n';
    cout << "   Estado: " << (tarea->completada ? "Completada" : "Pendiente") << '\n';
}

// Muestra todas las tareas.
// Complejidad: O(n)
void mostrarTodasLasTareas(const Lista& lista) {
    if (lista.cabeza == nullptr) {
        cout << "La lista esta vacia.\n";
        return;
    }

    const Tarea* actual = lista.cabeza;
    while (actual != nullptr) {
        cout << "-----------------------------\n";
        imprimirTarea(actual);
        actual = actual->siguiente;
    }
}

// Muestra todas las tareas numeradas.
// Complejidad: O(n)
void mostrarTareasNumeradas(const Lista& lista) {
    if (lista.cabeza == nullptr) {
        cout << "La lista esta vacia.\n";
        return;
    }

    const Tarea* actual = lista.cabeza;
    int numero = 1;

    while (actual != nullptr) {
        cout << "-----------------------------\n";
        imprimirTarea(actual, numero);
        actual = actual->siguiente;
        ++numero;
    }
}

// Muestra solo tareas completadas.
// Complejidad: O(n)
void mostrarSoloCompletadas(const Lista& lista) {
    if (lista.cabeza == nullptr) {
        cout << "La lista esta vacia.\n";
        return;
    }

    bool hubo = false;
    const Tarea* actual = lista.cabeza;

    while (actual != nullptr) {
        if (actual->completada) {
            cout << "-----------------------------\n";
            imprimirTarea(actual);
            hubo = true;
        }
        actual = actual->siguiente;
    }

    if (!hubo) {
        cout << "No hay tareas completadas.\n";
    }
}

// Muestra solo tareas pendientes.
// Complejidad: O(n)
void mostrarSoloPendientes(const Lista& lista) {
    if (lista.cabeza == nullptr) {
        cout << "La lista esta vacia.\n";
        return;
    }

    bool hubo = false;
    const Tarea* actual = lista.cabeza;

    while (actual != nullptr) {
        if (!actual->completada) {
            cout << "-----------------------------\n";
            imprimirTarea(actual);
            hubo = true;
        }
        actual = actual->siguiente;
    }

    if (!hubo) {
        cout << "No hay tareas pendientes.\n";
    }
}

// Cuenta nodos recursivamente.
// Complejidad: O(n)
int contarRecursivo(const Tarea* nodo) {
    if (nodo == nullptr) return 0;
    return 1 + contarRecursivo(nodo->siguiente);
}

// Muestra estadísticas generales.
// Complejidad: O(n)
void mostrarEstadisticas(const Lista& lista) {
    if (lista.cabeza == nullptr) {
        cout << "La lista esta vacia.\n";
        return;
    }

    // Si hay ciclo, no recorremos indefinidamente.
    // En una lista sana esto debe ser falso.
    // Para no bloquear el programa, lo verificamos antes.
    // (La función está más abajo).
    // Declaración anticipada no necesaria: aquí solo la usamos.
    extern bool tieneCiclo(const Lista&);

    if (tieneCiclo(lista)) {
        cout << "No se pueden calcular estadisticas: la lista contiene un ciclo.\n";
        return;
    }

    int total = lista.longitud;
    int completadas = 0;
    const Tarea* actual = lista.cabeza;

    while (actual != nullptr) {
        if (actual->completada) {
            ++completadas;
        }
        actual = actual->siguiente;
    }

    int pendientes = total - completadas;
    double progreso = (total == 0) ? 0.0 : (100.0 * completadas / total);

    cout << "===== ESTADISTICAS =====\n";
    cout << "Total de tareas: " << total << '\n';
    cout << "Completadas    : " << completadas << '\n';
    cout << "Pendientes     : " << pendientes << '\n';
    cout << "Progreso       : " << progreso << "%\n";
}

// ============================================================================
// ALGORITMOS AVANZADOS
// ============================================================================

// Detecta ciclos con el algoritmo de Floyd (tortuga y liebre).
// Complejidad: O(n)
bool tieneCiclo(const Lista& lista) {
    const Tarea* lento = lista.cabeza;
    const Tarea* rapido = lista.cabeza;

    while (rapido != nullptr && rapido->siguiente != nullptr) {
        lento = lento->siguiente;
        rapido = rapido->siguiente->siguiente;

        if (lento == rapido) {
            return true;
        }
    }

    return false;
}

// Invierte la lista enlazada.
// Antes:  A -> B -> C -> nullptr
// Después: C -> B -> A -> nullptr
// Complejidad: O(n)
void invertirLista(Lista& lista) {
    Tarea* previo = nullptr;
    Tarea* actual = lista.cabeza;

    while (actual != nullptr) {
        Tarea* siguiente = actual->siguiente;
        actual->siguiente = previo;
        previo = actual;
        actual = siguiente;
    }

    lista.cabeza = previo;
}

// Divide la lista en dos mitades para merge sort.
// Complejidad: O(n)
Tarea* dividirListaEnDos(Tarea* cabeza) {
    if (cabeza == nullptr || cabeza->siguiente == nullptr) return nullptr;

    Tarea* lento = cabeza;
    Tarea* rapido = cabeza->siguiente;

    while (rapido != nullptr && rapido->siguiente != nullptr) {
        lento = lento->siguiente;
        rapido = rapido->siguiente->siguiente;
    }

    Tarea* mitad = lento->siguiente;
    lento->siguiente = nullptr;
    return mitad;
}

// Funde dos listas ordenadas por título.
// Complejidad: O(n + m)
Tarea* fusionarOrdenado(Tarea* a, Tarea* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;

    if (compararIgnorandoMayusculas(a->titulo, b->titulo) <= 0) {
        a->siguiente = fusionarOrdenado(a->siguiente, b);
        return a;
    } else {
        b->siguiente = fusionarOrdenado(a, b->siguiente);
        return b;
    }
}

// Merge sort para lista simplemente enlazada.
// Complejidad: O(n log n)
Tarea* mergeSortNodos(Tarea* cabeza) {
    if (cabeza == nullptr || cabeza->siguiente == nullptr) {
        return cabeza;
    }

    Tarea* mitad = dividirListaEnDos(cabeza);
    Tarea* izquierda = mergeSortNodos(cabeza);
    Tarea* derecha = mergeSortNodos(mitad);

    return fusionarOrdenado(izquierda, derecha);
}

// Ordena la lista completa por título.
// Complejidad: O(n log n)
void ordenarListaPorTitulo(Lista& lista) {
    lista.cabeza = mergeSortNodos(lista.cabeza);
}

// Clona toda la lista en memoria nueva.
// Cada nodo nuevo necesita su propio delete posterior.
// Complejidad: O(n)
Lista clonarLista(const Lista& original) {
    Lista copia = crearListaVacia();
    Tarea* ultimo = nullptr;

    const Tarea* actual = original.cabeza;
    while (actual != nullptr) {
        anexarCopiaAlFinal(copia, ultimo, *actual);
        actual = actual->siguiente;
    }

    return copia;
}

// Fusiona dos listas completas en una nueva lista ordenada por título.
// Se crea memoria nueva; las listas originales no se modifican.
// Complejidad: O(n + m)
Lista fusionarDosListasOrdenadas(const Lista& a, const Lista& b) {
    Lista resultado = crearListaVacia();
    Tarea* ultimo = nullptr;

    const Tarea* pa = a.cabeza;
    const Tarea* pb = b.cabeza;

    while (pa != nullptr && pb != nullptr) {
        if (compararIgnorandoMayusculas(pa->titulo, pb->titulo) <= 0) {
            anexarCopiaAlFinal(resultado, ultimo, *pa);
            pa = pa->siguiente;
        } else {
            anexarCopiaAlFinal(resultado, ultimo, *pb);
            pb = pb->siguiente;
        }
    }

    while (pa != nullptr) {
        anexarCopiaAlFinal(resultado, ultimo, *pa);
        pa = pa->siguiente;
    }

    while (pb != nullptr) {
        anexarCopiaAlFinal(resultado, ultimo, *pb);
        pb = pb->siguiente;
    }

    return resultado;
}

// ============================================================================
// ENTRADA ROBUSTA
// ============================================================================

// Lee una línea completa.
// Si obligatorio = true, no permite vacío.
string leerTexto(const string& mensaje, bool obligatorio = true) {
    while (true) {
        cout << mensaje;
        string linea;
        std::getline(cin, linea);

        if (!obligatorio || !linea.empty()) {
            return linea;
        }

        cout << "La entrada no puede estar vacia.\n";
    }
}

// Lee un entero validado en rango.
int leerEnteroEnRango(const string& mensaje, int minimo, int maximo) {
    while (true) {
        cout << mensaje;
        string linea;
        std::getline(cin, linea);

        std::stringstream ss(linea);
        int valor;
        char extra;

        if (ss >> valor && !(ss >> extra) && valor >= minimo && valor <= maximo) {
            return valor;
        }

        cout << "Entrada invalida. Debe estar entre " << minimo << " y " << maximo << ".\n";
    }
}

// Lee booleano como 1/0.
bool leerBooleano(const string& mensaje) {
    int n = leerEnteroEnRango(mensaje, 0, 1);
    return n == 1;
}

// ============================================================================
// MENÚ INTERACTIVO
// ============================================================================

void mostrarMenu() {
    cout << "\n========================================\n";
    cout << " SISTEMA DE GESTION DE TAREAS\n";
    cout << "========================================\n";
    cout << "1. Agregar tarea\n";
    cout << "2. Eliminar tarea\n";
    cout << "3. Buscar tarea\n";
    cout << "4. Mostrar tareas\n";
    cout << "5. Editar tarea\n";
    cout << "6. Marcar completada\n";
    cout << "7. Ordenar lista\n";
    cout << "8. Invertir lista\n";
    cout << "9. Mostrar estadisticas\n";
    cout << "0. Salir\n";
}

// Submenú: agregar.
void menuAgregar(Lista& lista) {
    cout << "\n--- AGREGAR TAREA ---\n";
    cout << "1. Al inicio\n";
    cout << "2. Al final\n";
    cout << "3. En una posicion especifica\n";
    cout << "4. Ordenada alfabeticamente por titulo\n";

    int op = leerEnteroEnRango("Seleccione una opcion: ", 1, 4);
    string titulo = leerTexto("Titulo: ");
    string descripcion = leerTexto("Descripcion: ", false);
    bool completada = leerBooleano("¿Completada? (1=si, 0=no): ");

    bool ok = false;

    if (op == 1) {
        ok = insertarAlInicio(lista, titulo, descripcion, completada);
    } else if (op == 2) {
        ok = insertarAlFinal(lista, titulo, descripcion, completada);
    } else if (op == 3) {
        int pos = leerEnteroEnRango(
            "Posicion (1.." + std::to_string(lista.longitud + 1) + "): ",
            1,
            lista.longitud + 1
        );
        ok = insertarEnPosicion(lista, pos, titulo, descripcion, completada);
    } else {
        ok = insertarOrdenadoPorTitulo(lista, titulo, descripcion, completada);
    }

    cout << (ok ? "Tarea agregada correctamente.\n" : "No se pudo agregar la tarea.\n");
}

// Submenú: eliminar.
void menuEliminar(Lista& lista) {
    cout << "\n--- ELIMINAR TAREA ---\n";
    cout << "1. Por titulo\n";
    cout << "2. Por posicion\n";
    cout << "3. Primera tarea\n";
    cout << "4. Ultima tarea\n";
    cout << "5. Vaciar lista\n";

    int op = leerEnteroEnRango("Seleccione una opcion: ", 1, 5);
    bool ok = false;

    if (op == 1) {
        string titulo = leerTexto("Titulo exacto a eliminar: ");
        ok = eliminarPorTitulo(lista, titulo);
    } else if (op == 2) {
        int pos = leerEnteroEnRango(
            "Posicion (1.." + std::to_string(lista.longitud) + "): ",
            1,
            (lista.longitud > 0 ? lista.longitud : 1)
        );
        ok = eliminarPorPosicion(lista, pos);
    } else if (op == 3) {
        ok = eliminarPrimera(lista);
    } else if (op == 4) {
        ok = eliminarUltima(lista);
    } else {
        vaciarLista(lista);
        ok = true;
    }

    cout << (ok ? "Operacion de eliminacion completada.\n" : "No se pudo eliminar.\n");
}

// Submenú: buscar.
void menuBuscar(Lista& lista) {
    cout << "\n--- BUSCAR TAREA ---\n";
    cout << "1. Buscar por titulo exacto\n";
    cout << "2. Buscar coincidencias parciales\n";
    cout << "3. Verificar si existe\n";
    cout << "4. Buscar recursivamente por titulo exacto\n";

    int op = leerEnteroEnRango("Seleccione una opcion: ", 1, 4);

    if (op == 1) {
        string titulo = leerTexto("Titulo exacto: ");
        Tarea* nodo = buscarPorTituloExacto(lista, titulo);
        if (nodo != nullptr) {
            cout << "Tarea encontrada:\n";
            imprimirTarea(nodo);
        } else {
            cout << "No se encontro la tarea.\n";
        }
    } else if (op == 2) {
        string patron = leerTexto("Texto parcial: ");
        int encontrados = mostrarCoincidenciasParciales(lista, patron);
        cout << "Coincidencias encontradas: " << encontrados << '\n';
    } else if (op == 3) {
        string titulo = leerTexto("Titulo exacto: ");
        cout << (existeTarea(lista, titulo) ? "Si existe.\n" : "No existe.\n");
    } else {
        string titulo = leerTexto("Titulo exacto: ");
        Tarea* nodo = buscarRecursivo(lista.cabeza, titulo);
        if (nodo != nullptr) {
            cout << "Tarea encontrada (recursivo):\n";
            imprimirTarea(nodo);
        } else {
            cout << "No se encontro la tarea.\n";
        }
    }
}

// Submenú: mostrar.
void menuMostrar(const Lista& lista) {
    cout << "\n--- MOSTRAR TAREAS ---\n";
    cout << "1. Todas\n";
    cout << "2. Solo completadas\n";
    cout << "3. Solo pendientes\n";
    cout << "4. Numeradas\n";

    int op = leerEnteroEnRango("Seleccione una opcion: ", 1, 4);

    if (op == 1) {
        mostrarTodasLasTareas(lista);
    } else if (op == 2) {
        mostrarSoloCompletadas(lista);
    } else if (op == 3) {
        mostrarSoloPendientes(lista);
    } else {
        mostrarTareasNumeradas(lista);
    }
}

// Submenú: editar.
void menuEditar(Lista& lista) {
    cout << "\n--- EDITAR TAREA ---\n";
    cout << "1. Editar titulo\n";
    cout << "2. Editar descripcion\n";
    cout << "3. Cambiar estado\n";

    int op = leerEnteroEnRango("Seleccione una opcion: ", 1, 3);
    string tituloActual = leerTexto("Titulo exacto de la tarea a modificar: ");

    bool ok = false;

    if (op == 1) {
        string nuevoTitulo = leerTexto("Nuevo titulo: ");
        ok = editarTituloPorTitulo(lista, tituloActual, nuevoTitulo);
    } else if (op == 2) {
        string nuevaDescripcion = leerTexto("Nueva descripcion: ", false);
        ok = editarDescripcionPorTitulo(lista, tituloActual, nuevaDescripcion);
    } else {
        bool completada = leerBooleano("¿Marcar como completada? (1=si, 0=no): ");
        ok = cambiarEstadoPorTitulo(lista, tituloActual, completada);
    }

    cout << (ok ? "Tarea actualizada correctamente.\n" : "No se encontro la tarea.\n");
}

// Submenú: marcar completada.
void menuMarcarCompletada(Lista& lista) {
    string titulo = leerTexto("Titulo exacto de la tarea: ");
    bool ok = cambiarEstadoPorTitulo(lista, titulo, true);
    cout << (ok ? "Tarea marcada como completada.\n" : "No se encontro la tarea.\n");
}

// ============================================================================
// MAIN
// ============================================================================

int main() {
    Lista lista = crearListaVacia();

    bool continuar = true;
    while (continuar) {
        mostrarMenu();
        int opcion = leerEnteroEnRango("Seleccione una opcion: ", 0, 9);

        switch (opcion) {
            case 1:
                menuAgregar(lista);
                break;
            case 2:
                menuEliminar(lista);
                break;
            case 3:
                menuBuscar(lista);
                break;
            case 4:
                menuMostrar(lista);
                break;
            case 5:
                menuEditar(lista);
                break;
            case 6:
                menuMarcarCompletada(lista);
                break;
            case 7:
                ordenarListaPorTitulo(lista);
                cout << "Lista ordenada alfabeticamente por titulo.\n";
                break;
            case 8:
                invertirLista(lista);
                cout << "Lista invertida.\n";
                break;
            case 9:
                mostrarEstadisticas(lista);
                break;
            case 0:
                continuar = false;
                break;
        }
    }

    // Liberación final obligatoria de toda la memoria.
    vaciarLista(lista);
    cout << "Memoria liberada correctamente. Programa finalizado.\n";
    return 0;
}