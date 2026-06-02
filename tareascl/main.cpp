// =============================================================================
//  main.cpp — Menú interactivo del Sistema de Gestión de Tareas
//
//  Compilación:
//    g++ -std=c++17 -Wall -Wextra -o gestor main.cpp tareas.cpp
//
//  Ejecución:
//    ./gestor
//
// =============================================================================

#include "tareas.h"

#include <iostream>
#include <limits>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

// =============================================================================
//  HELPERS DEL MENÚ
// =============================================================================

static void limpiarBuffer()
{
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/** Lee una cadena no vacía con un prompt dado. */
static string leerCadena(const string& prompt)
{
    string s;
    while (true) {
        cout << "  " << prompt;
        std::getline(cin, s);
        if (!s.empty()) return s;
        cout << "  ⚠ No puede estar vacío. Intente nuevamente.\n";
    }
}

/** Lee un entero dentro del rango [minVal, maxVal]. */
static int leerEntero(const string& prompt, int minVal, int maxVal)
{
    int valor;
    while (true) {
        cout << "  " << prompt;
        if (cin >> valor && valor >= minVal && valor <= maxVal) {
            limpiarBuffer();
            return valor;
        }
        cin.clear();
        limpiarBuffer();
        cout << "  ⚠ Entrada inválida. Ingrese un número entre "
             << minVal << " y " << maxVal << ".\n";
    }
}

// =============================================================================
//  SUBMENÚS
// =============================================================================

static void menuAgregar(Lista* lista)
{
    cout << "\n  ╔══ AGREGAR TAREA ══╗\n";
    cout << "    1. Al inicio\n";
    cout << "    2. Al final\n";
    cout << "    3. En posición específica\n";
    cout << "    4. Orden alfabético\n";
    int op = leerEntero("Opción: ", 1, 4);

    string titulo = leerCadena("Título     : ");
    if (existeTarea(lista, titulo)) {
        cout << "  ⚠ Ya existe una tarea con ese título.\n";
        return;
    }
    string desc = leerCadena("Descripción: ");

    switch (op) {
        case 1: insertarInicio(lista, titulo, desc);
                cout << "  ✔ Tarea insertada al inicio.\n"; break;
        case 2: insertarFinal(lista, titulo, desc);
                cout << "  ✔ Tarea insertada al final.\n";  break;
        case 3: {
            int pos = leerEntero("Posición: ", 1, lista->longitud + 1);
            insertarPosicion(lista, pos, titulo, desc);
            cout << "  ✔ Tarea insertada en posición " << pos << ".\n";
            break;
        }
        case 4: insertarOrdenAlfa(lista, titulo, desc);
                cout << "  ✔ Tarea insertada en orden alfabético.\n"; break;
    }
}

static void menuEliminar(Lista* lista)
{
    if (!lista->cabeza) { cout << "  ⚠ La lista está vacía.\n"; return; }

    cout << "\n  ╔══ ELIMINAR TAREA ══╗\n";
    cout << "    1. Por título\n";
    cout << "    2. Por posición\n";
    cout << "    3. Primera tarea\n";
    cout << "    4. Última tarea\n";
    cout << "    5. Vaciar lista completa\n";
    int op = leerEntero("Opción: ", 1, 5);

    bool ok = false;
    switch (op) {
        case 1: {
            string titulo = leerCadena("Título a eliminar: ");
            ok = eliminarPorTitulo(lista, titulo);
            break;
        }
        case 2: {
            int pos = leerEntero("Posición: ", 1, lista->longitud);
            ok = eliminarPorPosicion(lista, pos);
            break;
        }
        case 3: ok = eliminarPrimero(lista); break;
        case 4: ok = eliminarUltimo(lista);  break;
        case 5:
            vaciarLista(lista);
            cout << "  ✔ Lista vaciada completamente.\n";
            return;
    }
    cout << (ok ? "  ✔ Tarea eliminada.\n" : "  ✗ Tarea no encontrada.\n");
}

static void menuBuscar(const Lista* lista)
{
    cout << "\n  ╔══ BUSCAR TAREA ══╗\n";
    cout << "    1. Por título exacto\n";
    cout << "    2. Búsqueda parcial\n";
    cout << "    3. Verificar existencia\n";
    cout << "    4. Búsqueda recursiva\n";
    cout << "    5. Contar nodos (recursivo)\n";
    int op = leerEntero("Opción: ", 1, 5);

    switch (op) {
        case 1: {
            string titulo = leerCadena("Título: ");
            Tarea* t = buscarPorTitulo(lista, titulo);
            if (t) imprimirNodo(t);
            else   cout << "  ✗ No encontrada.\n";
            break;
        }
        case 2: {
            string frag = leerCadena("Fragmento: ");
            buscarParcial(lista, frag);
            break;
        }
        case 3: {
            string titulo = leerCadena("Título: ");
            cout << (existeTarea(lista, titulo)
                     ? "  ✔ La tarea existe.\n"
                     : "  ✗ La tarea NO existe.\n");
            break;
        }
        case 4: {
            string titulo = leerCadena("Título: ");
            Tarea* t = buscarRecursivo(lista->cabeza, titulo);
            if (t) { cout << "  ✔ Encontrada (recursivo):\n"; imprimirNodo(t); }
            else   cout << "  ✗ No encontrada.\n";
            break;
        }
        case 5: {
            int c = contarRecursivo(lista->cabeza);
            cout << "  Nodos contados recursivamente: " << c << "\n";
            break;
        }
    }
}

static void menuMostrar(const Lista* lista)
{
    cout << "\n  ╔══ MOSTRAR TAREAS ══╗\n";
    cout << "    1. Todas\n";
    cout << "    2. Solo completadas\n";
    cout << "    3. Solo pendientes\n";
    cout << "    4. Numeradas\n";
    int op = leerEntero("Opción: ", 1, 4);
    switch (op) {
        case 1: mostrarTodas(lista);       break;
        case 2: mostrarCompletadas(lista); break;
        case 3: mostrarPendientes(lista);  break;
        case 4: mostrarNumeradas(lista);   break;
    }
}

static void menuEditar(Lista* lista)
{
    if (!lista->cabeza) { cout << "  ⚠ La lista está vacía.\n"; return; }

    cout << "\n  ╔══ EDITAR TAREA ══╗\n";
    cout << "    1. Editar título\n";
    cout << "    2. Editar descripción\n";
    int op = leerEntero("Opción: ", 1, 2);

    string titulo = leerCadena("Título de la tarea: ");
    if (!existeTarea(lista, titulo)) {
        cout << "  ✗ Tarea no encontrada.\n"; return;
    }

    bool ok = false;
    if (op == 1) {
        string nuevo = leerCadena("Nuevo título: ");
        ok = editarTitulo(lista, titulo, nuevo);
    } else {
        string nuevo = leerCadena("Nueva descripción: ");
        ok = editarDescripcion(lista, titulo, nuevo);
    }
    cout << (ok ? "  ✔ Tarea actualizada.\n" : "  ✗ No se pudo actualizar.\n");
}

static void menuAlgoritmos(Lista* lista)
{
    cout << "\n  ╔══ ALGORITMOS AVANZADOS ══╗\n";
    cout << "    1. Ordenar alfabéticamente (Bubble Sort)\n";
    cout << "    2. Invertir lista\n";
    cout << "    3. Detectar ciclos (Floyd)\n";
    cout << "    4. Clonar lista y mostrar clon\n";
    cout << "    5. Fusionar con lista de demostración\n";
    int op = leerEntero("Opción: ", 1, 5);

    switch (op) {
        case 1:
            ordenarBubble(lista);
            cout << "  ✔ Lista ordenada.\n";
            mostrarTodas(lista);
            break;
        case 2:
            invertirLista(lista);
            cout << "  ✔ Lista invertida.\n";
            mostrarTodas(lista);
            break;
        case 3:
            cout << (detectarCiclo(lista)
                     ? "  ⚠ ¡CICLO DETECTADO! (estructura corrupta)\n"
                     : "  ✔ Sin ciclos. Lista íntegra.\n");
            break;
        case 4: {
            Lista* clon = clonarLista(lista);
            cout << "  ✔ Clon creado (" << clon->longitud << " tareas):\n";
            mostrarTodas(clon);
            destruirLista(clon); // Liberamos el clon cuando ya no se necesita
            break;
        }
        case 5: {
            // Lista de demostración para fusión
            Lista* demo = crearLista();
            insertarFinal(demo, "Tarea Demo A", "Descripción de demostración A");
            insertarFinal(demo, "Tarea Demo B", "Descripción de demostración B");
            Lista* fusionada = fusionarListas(lista, demo);
            cout << "  ✔ Lista fusionada (" << fusionada->longitud << " tareas):\n";
            mostrarTodas(fusionada);
            destruirLista(demo);
            destruirLista(fusionada);
            break;
        }
    }
}

// =============================================================================
//  MENÚ PRINCIPAL
// =============================================================================

static void imprimirMenuPrincipal()
{
    imprimirSeparador('=', 58);
    cout << centrar("SISTEMA DE GESTION DE TAREAS", 58) << "\n";
    cout << centrar("Lista Simplemente Enlazada - C++17", 58) << "\n";
    imprimirSeparador('=', 58);
    cout << "   1. Agregar tarea\n";
    cout << "   2. Eliminar tarea\n";
    cout << "   3. Buscar tarea\n";
    cout << "   4. Mostrar tareas\n";
    cout << "   5. Editar tarea\n";
    cout << "   6. Marcar completada / pendiente\n";
    cout << "   7. Algoritmos avanzados (ordenar, invertir...)\n";
    cout << "   8. Estadísticas\n";
    cout << "   0. Salir\n";
    imprimirSeparador('-', 58);
}

// =============================================================================
//  MAIN — Punto de entrada
// =============================================================================

int main()
{
    // Creamos la lista en el heap; se destruye al salir
    Lista* lista = crearLista();

    // ── Datos de demostración ──────────────────────────────────────────────
    insertarFinal(lista, "Estudiar punteros en C++",
                  "Repasar aritmética de punteros y gestión de memoria");
    insertarFinal(lista, "Implementar lista enlazada",
                  "Singly linked list con inserción, eliminación y búsqueda");
    insertarFinal(lista, "Revisar algoritmo de Floyd",
                  "Detección de ciclos: puntero lento y rápido");
    insertarFinal(lista, "Entregar tarea de estructuras",
                  "Subir al portal UAM antes del viernes");
    cambiarEstado(lista, "Estudiar punteros en C++"); // Marcar como completada
    // ──────────────────────────────────────────────────────────────────────

    int opcion;
    do {
        imprimirMenuPrincipal();
        cout << "   Tareas en lista: " << lista->longitud << "\n";
        opcion = leerEntero("→ Opción: ", 0, 8);

        switch (opcion) {
            case 1: menuAgregar(lista);   break;
            case 2: menuEliminar(lista);  break;
            case 3: menuBuscar(lista);    break;
            case 4: menuMostrar(lista);   break;
            case 5: menuEditar(lista);    break;
            case 6: {
                string titulo = leerCadena("Título de la tarea: ");
                bool ok = cambiarEstado(lista, titulo);
                cout << (ok ? "  ✔ Estado cambiado.\n" : "  ✗ Tarea no encontrada.\n");
                break;
            }
            case 7: menuAlgoritmos(lista);    break;
            case 8: mostrarEstadisticas(lista); break;
            case 0:
                cout << "\n  Liberando memoria...\n";
                destruirLista(lista); // ← Libera TODOS los nodos + el struct Lista
                lista = nullptr;      // ← Evita puntero colgante
                cout << "  ✔ Memoria liberada. ¡Hasta luego!\n\n";
                break;
        }
        if (opcion != 0) cout << "\n";

    } while (opcion != 0);

    return 0;
}
