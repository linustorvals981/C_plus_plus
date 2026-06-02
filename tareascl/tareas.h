#ifndef TAREAS_H
#define TAREAS_H

// =============================================================================
//  tareas.h — Definiciones y declaraciones del sistema de gestión de tareas
//  Estructura: Lista Simplemente Enlazada (Singly Linked List) manual
//  Estándar: C++17
// =============================================================================

#include <string>
using std::string;

// =============================================================================
//  ESTRUCTURAS BASE
//  Nodo de la lista: contiene datos + puntero al siguiente nodo
// =============================================================================

struct Tarea {
    string titulo;       // Identificador único de la tarea
    string descripcion;  // Detalle de la tarea
    bool   completada;   // false = pendiente, true = completada
    struct Tarea *siguiente; // Puntero al siguiente nodo (nullptr si es el último)
};

struct Lista {
    int longitud;        // Cantidad de nodos activos en la lista
    struct Tarea *cabeza; // Puntero al primer nodo (nullptr si está vacía)
};

// =============================================================================
//  I. INICIALIZACIÓN
// =============================================================================
Lista* crearLista();
void   destruirLista(Lista* lista);

// =============================================================================
//  II. INSERCIÓN
// =============================================================================
void insertarInicio     (Lista* lista, const string& titulo, const string& desc);
void insertarFinal      (Lista* lista, const string& titulo, const string& desc);
void insertarPosicion   (Lista* lista, int pos, const string& titulo, const string& desc);
void insertarOrdenAlfa  (Lista* lista, const string& titulo, const string& desc);

// =============================================================================
//  III. ELIMINACIÓN
// =============================================================================
bool eliminarPorTitulo  (Lista* lista, const string& titulo);
bool eliminarPorPosicion(Lista* lista, int pos);
bool eliminarPrimero    (Lista* lista);
bool eliminarUltimo     (Lista* lista);
void vaciarLista        (Lista* lista);

// =============================================================================
//  IV. BÚSQUEDA
// =============================================================================
Tarea* buscarPorTitulo  (const Lista* lista, const string& titulo);
void   buscarParcial    (const Lista* lista, const string& fragmento);
bool   existeTarea      (const Lista* lista, const string& titulo);

// Versión recursiva
Tarea* buscarRecursivo  (Tarea* nodo, const string& titulo);
int    contarRecursivo  (const Tarea* nodo);

// =============================================================================
//  V. ACTUALIZACIÓN
// =============================================================================
bool editarTitulo       (Lista* lista, const string& tituloActual, const string& nuevoTitulo);
bool editarDescripcion  (Lista* lista, const string& titulo, const string& nuevaDesc);
bool cambiarEstado      (Lista* lista, const string& titulo);

// =============================================================================
//  VI. VISUALIZACIÓN
// =============================================================================
void mostrarTodas       (const Lista* lista);
void mostrarCompletadas (const Lista* lista);
void mostrarPendientes  (const Lista* lista);
void mostrarNumeradas   (const Lista* lista);
void mostrarEstadisticas(const Lista* lista);

// =============================================================================
//  VII. ALGORITMOS AVANZADOS
// =============================================================================
void   ordenarBubble    (Lista* lista);
void   invertirLista    (Lista* lista);
bool   detectarCiclo    (const Lista* lista);
Lista* clonarLista      (const Lista* lista);
Lista* fusionarListas   (const Lista* a, const Lista* b);

// =============================================================================
//  VIII. UTILIDADES INTERNAS
// =============================================================================
Tarea* crearNodo        (const string& titulo, const string& desc, bool completada = false);
void   imprimirNodo     (const Tarea* t, int numero = -1);
void   imprimirSeparador(char c = '-', int ancho = 60);
string centrar          (const string& texto, int ancho);

#endif // TAREAS_H
