// =============================================================================
//  tareas.cpp — Implementación completa del sistema de gestión de tareas
//
//  Estructura de datos: Lista Simplemente Enlazada (Singly Linked List)
//
//  MODELO DE MEMORIA:
//  ─────────────────
//  Cada Tarea es un nodo asignado en el heap con `new`.
//  La Lista contiene un puntero `cabeza` al primer nodo.
//  El último nodo siempre apunta a nullptr.
//
//    [Lista]
//    cabeza ──→ [Tarea1] ──→ [Tarea2] ──→ ... ──→ [TareaN] ──→ nullptr
//    longitud
//
// =============================================================================

#include "tareas.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>   // std::transform para comparación case-insensitive
#include <cctype>      // std::tolower

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::setw;
using std::left;

// =============================================================================
//  UTILIDADES INTERNAS
// =============================================================================

/**
 * crearNodo — Asigna un nuevo Tarea en el heap.
 *
 * Complejidad: O(1)
 *
 * Por qué `new`: necesitamos que el nodo sobreviva más allá del scope de la
 * función.  El puntero devuelto es responsabilidad del llamador liberarlo
 * con `delete` cuando ya no sea necesario.
 */
Tarea* crearNodo(const string& titulo, const string& desc, bool completada)
{
    Tarea* nodo   = new Tarea;   // Reserva sizeof(Tarea) bytes en el heap
    nodo->titulo      = titulo;
    nodo->descripcion = desc;
    nodo->completada  = completada;
    nodo->siguiente   = nullptr; // Siempre inicializar: evita puntero colgante
    return nodo;
}

/** Imprime una línea separadora de `ancho` caracteres `c`. */
void imprimirSeparador(char c, int ancho)
{
    cout << string(ancho, c) << "\n";
}

/** Centra `texto` en un campo de `ancho` caracteres. */
string centrar(const string& texto, int ancho)
{
    int padding = (ancho - (int)texto.size()) / 2;
    if (padding < 0) padding = 0;
    return string(padding, ' ') + texto;
}

/** Convierte una cadena a minúsculas (para búsqueda case-insensitive). */
static string aMinusculas(string s)
{
    std::transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return s;
}

/**
 * imprimirNodo — Muestra los datos de una tarea formateados.
 * Si `numero` >= 0, lo imprime como prefijo numerado.
 */
void imprimirNodo(const Tarea* t, int numero)
{
    imprimirSeparador('-', 58);
    if (numero >= 0)
        cout << "  [" << numero << "] ";
    else
        cout << "  ";

    cout << "Título      : " << t->titulo << "\n";
    cout << "      Descripción : " << t->descripcion << "\n";
    cout << "      Estado      : "
         << (t->completada ? "✔ Completada" : "○ Pendiente") << "\n";
}

// =============================================================================
//  I. INICIALIZACIÓN
// =============================================================================

/**
 * crearLista — Crea y devuelve una lista vacía.
 *
 * Diagrama inicial:
 *   [Lista]  cabeza = nullptr,  longitud = 0
 *
 * Complejidad: O(1)
 */
Lista* crearLista()
{
    Lista* lista  = new Lista;
    lista->cabeza   = nullptr;
    lista->longitud = 0;
    return lista;
}

/**
 * destruirLista — Libera la Lista y todos sus nodos.
 *
 * Por qué: evitar fuga de memoria cuando el programa termina o la lista
 * ya no se necesita.  Internamente llama a vaciarLista y luego libera
 * el struct Lista mismo.
 *
 * Complejidad: O(n)
 */
void destruirLista(Lista* lista)
{
    if (!lista) return;
    vaciarLista(lista); // Libera todos los nodos
    delete lista;       // Libera el struct contenedor
}

// =============================================================================
//  II. INSERCIÓN
// =============================================================================

/**
 * insertarInicio — Inserta un nodo al principio de la lista.
 *
 * Diagrama:
 *   Antes : [cabeza] → [A] → [B] → nullptr
 *   Nuevo nodo: [N], N->siguiente = A
 *   [cabeza] apunta a N
 *   Después: [cabeza] → [N] → [A] → [B] → nullptr
 *
 * Por qué O(1): no recorremos nada; solo actualizamos cabeza.
 */
void insertarInicio(Lista* lista, const string& titulo, const string& desc)
{
    Tarea* nodo       = crearNodo(titulo, desc);
    nodo->siguiente   = lista->cabeza; // El nuevo nodo apunta al antiguo primero
    lista->cabeza     = nodo;          // cabeza ahora apunta al nuevo nodo
    lista->longitud++;
}

/**
 * insertarFinal — Inserta un nodo al final de la lista.
 *
 * Diagrama:
 *   Antes : [cabeza] → [A] → [B] → nullptr
 *   Después: [cabeza] → [A] → [B] → [N] → nullptr
 *
 * Complejidad: O(n) — debemos llegar al último nodo.
 */
void insertarFinal(Lista* lista, const string& titulo, const string& desc)
{
    Tarea* nodo = crearNodo(titulo, desc);

    if (!lista->cabeza) {          // Lista vacía: el nuevo nodo ES la cabeza
        lista->cabeza = nodo;
    } else {
        // Recorremos hasta el último nodo
        Tarea* actual = lista->cabeza;
        while (actual->siguiente != nullptr)
            actual = actual->siguiente;
        // actual ahora es el último nodo; lo enlazamos con el nuevo
        actual->siguiente = nodo;
    }
    lista->longitud++;
}

/**
 * insertarPosicion — Inserta en la posición `pos` (base 1).
 *
 * pos = 1 equivale a insertarInicio.
 * Si pos > longitud, inserta al final.
 *
 * Complejidad: O(n)
 */
void insertarPosicion(Lista* lista, int pos, const string& titulo, const string& desc)
{
    if (pos <= 1 || !lista->cabeza) {
        insertarInicio(lista, titulo, desc);
        return;
    }

    Tarea* nodo   = crearNodo(titulo, desc);
    Tarea* actual = lista->cabeza;

    // Avanzamos hasta el nodo en posición (pos-1)
    for (int i = 1; i < pos - 1 && actual->siguiente != nullptr; i++)
        actual = actual->siguiente;

    // Enlazamos: actual → nuevo → lo que seguía a actual
    nodo->siguiente   = actual->siguiente;
    actual->siguiente = nodo;
    lista->longitud++;
}

/**
 * insertarOrdenAlfa — Inserta manteniendo orden alfabético ascendente por título.
 *
 * Recorre la lista buscando el punto de inserción correcto.
 * Complejidad: O(n)
 */
void insertarOrdenAlfa(Lista* lista, const string& titulo, const string& desc)
{
    Tarea* nodo = crearNodo(titulo, desc);

    // Si la lista está vacía O el nuevo título va antes que la cabeza
    if (!lista->cabeza || titulo < lista->cabeza->titulo) {
        nodo->siguiente = lista->cabeza;
        lista->cabeza   = nodo;
        lista->longitud++;
        return;
    }

    // Buscamos el nodo anterior al punto de inserción
    Tarea* actual = lista->cabeza;
    while (actual->siguiente && actual->siguiente->titulo <= titulo)
        actual = actual->siguiente;

    nodo->siguiente   = actual->siguiente;
    actual->siguiente = nodo;
    lista->longitud++;
}

// =============================================================================
//  III. ELIMINACIÓN
// =============================================================================

/**
 * eliminarPorTitulo — Busca y elimina la primera tarea con el título dado.
 *
 * Diagrama de desconexión:
 *   Antes : [prev] → [TARGET] → [sgte]
 *   prev->siguiente = TARGET->siguiente
 *   delete TARGET
 *   Después: [prev] → [sgte]
 *
 * Por qué `delete`: TARGET fue creado con `new`.  Si no lo liberamos,
 * la memoria queda ocupada sin referencia (fuga).
 *
 * Complejidad: O(n)
 */
bool eliminarPorTitulo(Lista* lista, const string& titulo)
{
    if (!lista->cabeza) return false;

    // Caso especial: el nodo a eliminar es la cabeza
    if (lista->cabeza->titulo == titulo) {
        Tarea* tmp    = lista->cabeza;
        lista->cabeza = lista->cabeza->siguiente; // cabeza avanza un nodo
        delete tmp;                                // liberamos la memoria del nodo
        lista->longitud--;
        return true;
    }

    // Caso general: buscamos el nodo previo al objetivo
    Tarea* prev   = lista->cabeza;
    while (prev->siguiente && prev->siguiente->titulo != titulo)
        prev = prev->siguiente;

    if (!prev->siguiente) return false; // No encontrado

    Tarea* objetivo   = prev->siguiente;
    prev->siguiente   = objetivo->siguiente; // Saltamos el nodo objetivo
    delete objetivo;                          // Liberamos su memoria
    lista->longitud--;
    return true;
}

/**
 * eliminarPorPosicion — Elimina el nodo en la posición `pos` (base 1).
 * Complejidad: O(n)
 */
bool eliminarPorPosicion(Lista* lista, int pos)
{
    if (!lista->cabeza || pos < 1) return false;

    if (pos == 1) return eliminarPrimero(lista);

    Tarea* prev = lista->cabeza;
    for (int i = 1; i < pos - 1 && prev->siguiente; i++)
        prev = prev->siguiente;

    if (!prev->siguiente) return false;

    Tarea* objetivo   = prev->siguiente;
    prev->siguiente   = objetivo->siguiente;
    delete objetivo;
    lista->longitud--;
    return true;
}

/**
 * eliminarPrimero — Elimina el nodo cabeza.
 * Complejidad: O(1)
 */
bool eliminarPrimero(Lista* lista)
{
    if (!lista->cabeza) return false;

    Tarea* tmp    = lista->cabeza;
    lista->cabeza = lista->cabeza->siguiente;
    delete tmp;       // Liberamos el antiguo primer nodo
    lista->longitud--;
    return true;
}

/**
 * eliminarUltimo — Elimina el último nodo.
 *
 * Necesita llegar al penúltimo para cortar el enlace antes de liberar.
 * Complejidad: O(n)
 */
bool eliminarUltimo(Lista* lista)
{
    if (!lista->cabeza) return false;

    // Caso especial: un solo nodo
    if (!lista->cabeza->siguiente) {
        delete lista->cabeza;
        lista->cabeza = nullptr;
        lista->longitud--;
        return true;
    }

    // Buscamos el penúltimo
    Tarea* penultimo = lista->cabeza;
    while (penultimo->siguiente->siguiente != nullptr)
        penultimo = penultimo->siguiente;

    delete penultimo->siguiente; // Liberamos el último
    penultimo->siguiente = nullptr; // El penúltimo ahora es el último
    lista->longitud--;
    return true;
}

/**
 * vaciarLista — Elimina todos los nodos liberando su memoria.
 *
 * Recorre la lista nodo a nodo; guarda el siguiente ANTES de hacer delete,
 * porque después del delete el puntero deja de ser válido (puntero colgante).
 *
 * Complejidad: O(n)
 */
void vaciarLista(Lista* lista)
{
    Tarea* actual = lista->cabeza;
    while (actual != nullptr) {
        Tarea* siguiente = actual->siguiente; // Guardamos el siguiente PRIMERO
        delete actual;                         // Ahora liberamos el nodo actual
        actual = siguiente;                    // Avanzamos con el puntero guardado
    }
    lista->cabeza   = nullptr;
    lista->longitud = 0;
}

// =============================================================================
//  IV. BÚSQUEDA
// =============================================================================

/**
 * buscarPorTitulo — Búsqueda lineal exacta (case-sensitive).
 * Devuelve puntero al nodo o nullptr si no existe.
 * Complejidad: O(n)
 */
Tarea* buscarPorTitulo(const Lista* lista, const string& titulo)
{
    Tarea* actual = lista->cabeza;
    while (actual) {
        if (actual->titulo == titulo) return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

/**
 * buscarParcial — Muestra todos los nodos cuyo título o descripción
 * contienen `fragmento` (case-insensitive).
 * Complejidad: O(n * m)  donde m = longitud del fragmento
 */
void buscarParcial(const Lista* lista, const string& fragmento)
{
    string frag = aMinusculas(fragmento);
    Tarea* actual = lista->cabeza;
    int encontrados = 0;

    cout << "\n  Resultados para \"" << fragmento << "\":\n";
    while (actual) {
        bool enTitulo = aMinusculas(actual->titulo).find(frag) != string::npos;
        bool enDesc   = aMinusculas(actual->descripcion).find(frag) != string::npos;
        if (enTitulo || enDesc) {
            imprimirNodo(actual, ++encontrados);
        }
        actual = actual->siguiente;
    }
    if (!encontrados)
        cout << "  (Sin resultados)\n";
    imprimirSeparador('-', 58);
}

/**
 * existeTarea — Verifica rápidamente si un título existe.
 * Complejidad: O(n)
 */
bool existeTarea(const Lista* lista, const string& titulo)
{
    return buscarPorTitulo(lista, titulo) != nullptr;
}

/**
 * buscarRecursivo — Versión recursiva de búsqueda exacta.
 *
 * Caso base: nodo == nullptr → no encontrado.
 * Caso recursivo: si el título coincide devuelve el nodo;
 *                 si no, busca en el resto de la lista.
 *
 * Complejidad: O(n)  |  Espacio en pila: O(n)
 */
Tarea* buscarRecursivo(Tarea* nodo, const string& titulo)
{
    if (!nodo) return nullptr;                    // Caso base: lista agotada
    if (nodo->titulo == titulo) return nodo;      // Caso base: encontrado
    return buscarRecursivo(nodo->siguiente, titulo); // Recursión
}

/**
 * contarRecursivo — Cuenta nodos de forma recursiva.
 *
 * Caso base: nullptr → 0
 * Caso recursivo: 1 + contar(resto)
 *
 * Complejidad: O(n)  |  Espacio en pila: O(n)
 */
int contarRecursivo(const Tarea* nodo)
{
    if (!nodo) return 0;                         // Caso base
    return 1 + contarRecursivo(nodo->siguiente); // Recursión
}

// =============================================================================
//  V. ACTUALIZACIÓN
// =============================================================================

/**
 * editarTitulo — Cambia el título de una tarea existente.
 * Verifica que el nuevo título no esté ya en uso.
 * Complejidad: O(n)
 */
bool editarTitulo(Lista* lista, const string& tituloActual, const string& nuevoTitulo)
{
    if (existeTarea(lista, nuevoTitulo)) {
        cout << "  Error: ya existe una tarea con ese título.\n";
        return false;
    }
    Tarea* t = buscarPorTitulo(lista, tituloActual);
    if (!t) return false;
    t->titulo = nuevoTitulo;
    return true;
}

/**
 * editarDescripcion — Actualiza la descripción de una tarea.
 * Complejidad: O(n)
 */
bool editarDescripcion(Lista* lista, const string& titulo, const string& nuevaDesc)
{
    Tarea* t = buscarPorTitulo(lista, titulo);
    if (!t) return false;
    t->descripcion = nuevaDesc;
    return true;
}

/**
 * cambiarEstado — Alterna entre completada/pendiente (toggle).
 * Complejidad: O(n)
 */
bool cambiarEstado(Lista* lista, const string& titulo)
{
    Tarea* t = buscarPorTitulo(lista, titulo);
    if (!t) return false;
    t->completada = !t->completada;
    return true;
}

// =============================================================================
//  VI. VISUALIZACIÓN
// =============================================================================

void mostrarTodas(const Lista* lista)
{
    cout << "\n" << centrar("TODAS LAS TAREAS", 58) << "\n";
    if (!lista->cabeza) {
        cout << "  (Lista vacía)\n";
        imprimirSeparador('=', 58);
        return;
    }
    Tarea* actual = lista->cabeza;
    int i = 1;
    while (actual) {
        imprimirNodo(actual, i++);
        actual = actual->siguiente;
    }
    imprimirSeparador('=', 58);
}

void mostrarCompletadas(const Lista* lista)
{
    cout << "\n" << centrar("TAREAS COMPLETADAS", 58) << "\n";
    Tarea* actual = lista->cabeza;
    int count = 0;
    while (actual) {
        if (actual->completada) imprimirNodo(actual, ++count);
        actual = actual->siguiente;
    }
    if (!count) cout << "  (Ninguna tarea completada)\n";
    imprimirSeparador('=', 58);
}

void mostrarPendientes(const Lista* lista)
{
    cout << "\n" << centrar("TAREAS PENDIENTES", 58) << "\n";
    Tarea* actual = lista->cabeza;
    int count = 0;
    while (actual) {
        if (!actual->completada) imprimirNodo(actual, ++count);
        actual = actual->siguiente;
    }
    if (!count) cout << "  (Ninguna tarea pendiente)\n";
    imprimirSeparador('=', 58);
}

void mostrarNumeradas(const Lista* lista)
{
    mostrarTodas(lista); // Ya incluye numeración
}

/**
 * mostrarEstadisticas — Calcula y muestra métricas de la lista.
 * Complejidad: O(n)
 */
void mostrarEstadisticas(const Lista* lista)
{
    int total      = lista->longitud;
    int completadas = 0;

    Tarea* actual = lista->cabeza;
    while (actual) {
        if (actual->completada) completadas++;
        actual = actual->siguiente;
    }

    int pendientes = total - completadas;
    double porcentaje = total > 0 ? (100.0 * completadas / total) : 0.0;

    imprimirSeparador('=', 58);
    cout << centrar("ESTADÍSTICAS", 58) << "\n";
    imprimirSeparador('=', 58);
    cout << "  Total de tareas  : " << total       << "\n";
    cout << "  Completadas      : " << completadas << "\n";
    cout << "  Pendientes       : " << pendientes  << "\n";
    cout << "  Progreso         : " << std::fixed << std::setprecision(1)
         << porcentaje << "%\n";

    // Barra visual de progreso
    int barraAncho = 40;
    int llenas     = (int)(porcentaje / 100.0 * barraAncho);
    cout << "  [";
    cout << string(llenas, '#') << string(barraAncho - llenas, '.');
    cout << "]\n";
    imprimirSeparador('=', 58);
}

// =============================================================================
//  VII. ALGORITMOS AVANZADOS
// =============================================================================

/**
 * ordenarBubble — Ordena la lista alfabéticamente por título usando Bubble Sort.
 *
 * En lugar de mover punteros (complejo en listas enlazadas), intercambia
 * los *datos* de los nodos: es más seguro y comprensible.
 *
 * Complejidad: O(n²) tiempo  |  O(1) espacio adicional
 */
void ordenarBubble(Lista* lista)
{
    if (!lista->cabeza || !lista->cabeza->siguiente) return;

    bool huboIntercambio;
    do {
        huboIntercambio = false;
        Tarea* actual = lista->cabeza;

        while (actual->siguiente) {
            if (actual->titulo > actual->siguiente->titulo) {
                // Intercambiamos datos (no punteros) entre nodo y su sucesor
                std::swap(actual->titulo,      actual->siguiente->titulo);
                std::swap(actual->descripcion, actual->siguiente->descripcion);
                std::swap(actual->completada,  actual->siguiente->completada);
                huboIntercambio = true;
            }
            actual = actual->siguiente;
        }
    } while (huboIntercambio);
}

/**
 * invertirLista — Invierte el orden de la lista en-place.
 *
 * Técnica: tres punteros (prev, actual, sgte).
 * En cada paso redirigimos el puntero `siguiente` del nodo actual
 * para que apunte hacia atrás en lugar de hacia adelante.
 *
 * Diagrama paso a paso (lista [A→B→C→nullptr]):
 *
 *   Inicio:  prev=null  actual=A  sgte=?
 *
 *   Paso 1: sgte=B, A->siguiente=null, prev=A, actual=B
 *           null ← [A]   [B] → [C] → null
 *
 *   Paso 2: sgte=C, B->siguiente=A,   prev=B, actual=C
 *           null ← [A] ← [B]   [C] → null
 *
 *   Paso 3: sgte=null, C->siguiente=B, prev=C, actual=null
 *           null ← [A] ← [B] ← [C]
 *
 *   cabeza = C   →   [C] → [B] → [A] → null
 *
 * Complejidad: O(n)
 */
void invertirLista(Lista* lista)
{
    Tarea* prev   = nullptr;
    Tarea* actual = lista->cabeza;

    while (actual) {
        Tarea* sgte     = actual->siguiente; // Guardamos antes de sobreescribir
        actual->siguiente = prev;            // Invertimos el enlace
        prev   = actual;                     // prev avanza
        actual = sgte;                       // actual avanza
    }

    lista->cabeza = prev; // prev quedó en el último nodo (nuevo primero)
}

/**
 * detectarCiclo — Detecta si hay un ciclo en la lista (Algoritmo de Floyd).
 *
 * Utiliza dos punteros: `lento` avanza 1 nodo por iteración,
 * `rapido` avanza 2 nodos.  Si hay ciclo, se encuentran.
 * Si `rapido` llega a nullptr, no hay ciclo.
 *
 * En una lista correctamente construida NUNCA debe haber ciclo.
 * Esta función es una herramienta de diagnóstico / verificación.
 *
 * Complejidad: O(n)  |  Espacio: O(1)
 */
bool detectarCiclo(const Lista* lista)
{
    const Tarea* lento  = lista->cabeza;
    const Tarea* rapido = lista->cabeza;

    while (rapido && rapido->siguiente) {
        lento  = lento->siguiente;
        rapido = rapido->siguiente->siguiente;
        if (lento == rapido) return true; // Ciclo detectado
    }
    return false;
}

/**
 * clonarLista — Crea una copia profunda (deep copy) de la lista.
 *
 * Por qué "profunda": cada nodo de la copia es un nuevo objeto en el heap.
 * Modificar la copia NO afecta la original y viceversa.
 *
 * Complejidad: O(n)
 */
Lista* clonarLista(const Lista* lista)
{
    Lista* copia = crearLista();
    const Tarea* actual = lista->cabeza;

    // Para insertar en el mismo orden usamos un puntero al último nodo de la copia
    Tarea* ultimoCopia = nullptr;

    while (actual) {
        Tarea* nodo = crearNodo(actual->titulo, actual->descripcion, actual->completada);

        if (!copia->cabeza) {
            copia->cabeza = nodo;
        } else {
            ultimoCopia->siguiente = nodo;
        }
        ultimoCopia = nodo;
        copia->longitud++;
        actual = actual->siguiente;
    }
    return copia;
}

/**
 * fusionarListas — Combina dos listas en una nueva (copia profunda de ambas).
 *
 * La lista resultante contiene primero todos los elementos de `a`,
 * luego todos los de `b`.  Las listas originales no se modifican.
 *
 * Complejidad: O(n + m)  donde n = |a|, m = |b|
 */
Lista* fusionarListas(const Lista* a, const Lista* b)
{
    Lista* resultado = clonarLista(a); // Copia de a

    // Añadimos cada elemento de b al final de resultado
    const Tarea* actual = b->cabeza;
    while (actual) {
        insertarFinal(resultado, actual->titulo, actual->descripcion);
        // Propagamos el estado completada
        Tarea* nuevo = resultado->cabeza;
        while (nuevo->siguiente) nuevo = nuevo->siguiente; // llegamos al último
        nuevo->completada = actual->completada;
        actual = actual->siguiente;
    }
    return resultado;
}
