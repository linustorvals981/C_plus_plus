// ============================================================
//  Lista doblemente ligada de Películas
// ============================================================
#include <iostream>
#include <string>

using namespace std;

struct Genero {
    bool terror;
    bool romance;
    bool comedia;
    bool suspenso;
    bool drama;
    bool animation;
    bool accion;
};

struct FechaLanzamiento {
    int dia;
    int mes;
    int anio;
};

struct Duracion {
    int horas;
    int minutos;
};

struct Pelicula {
    string nombre;
    int precio;
    int asientosDisponibles;
    Genero             genero;      // valor (no puntero): no necesita new/delete
    Duracion          *duracion;    // puntero: requiere new y delete
    FechaLanzamiento  *fecha;       // puntero: requiere new y delete
    Pelicula          *siguiente;
    Pelicula          *anterior;
};

struct Catalogo {
    int       longitud;
    Pelicula *cabeza;
    Pelicula *cola; 
};

// Variable global del catálogo
Catalogo *lista = nullptr;

// ─────────────────────────────────────────────────────────────
//  Utilidad: comparación correcta de dos fechas
//  Retorna true si (diaA/mesA/anioA) <= (diaB/mesB/anioB)
// ─────────────────────────────────────────────────────────────
bool fechaMenorIgual(int diaA, int mesA, int anioA,
                     int diaB, int mesB, int anioB) {
    if (anioA != anioB) return anioA < anioB;
    if (mesA  != mesB)  return mesA  < mesB;
    return diaA <= diaB;
}

// ─────────────────────────────────────────────────────────────
//  Creación de un nodo Pelicula
// ─────────────────────────────────────────────────────────────
Pelicula *crearPelicula(const string &nombre, int precio,
                        const string &genero1, const string &genero2,
                        int dia, int mes, int anio,
                        int horas, int minutos) {

    Pelicula *nuevo = new Pelicula();

    nuevo->nombre              = nombre;
    nuevo->precio              = precio;
    nuevo->asientosDisponibles = 100;
    nuevo->siguiente           = nullptr;
    nuevo->anterior            = nullptr;
    nuevo->fecha       = new FechaLanzamiento();
    nuevo->fecha->dia  = dia;
    nuevo->fecha->mes  = mes;
    nuevo->fecha->anio = anio;

    nuevo->duracion          = new Duracion();
    nuevo->duracion->horas   = horas;
    nuevo->duracion->minutos = minutos;

    // Inicializar todos los géneros en false
    nuevo->genero = {false, false, false, false, false, false, false};

    // Ahora usamos un lambda para asignar géneros sin repetir if-chains.
    auto asignarGenero = [&](const string &g) {
        if (g == "terror")    nuevo->genero.terror    = true;
        if (g == "romance")   nuevo->genero.romance   = true;
        if (g == "comedia")   nuevo->genero.comedia   = true;
        if (g == "suspenso")  nuevo->genero.suspenso  = true;
        if (g == "drama")     nuevo->genero.drama     = true;
        if (g == "animation") nuevo->genero.animation = true;
        if (g == "accion")    nuevo->genero.accion    = true;
    };
    asignarGenero(genero1);
    asignarGenero(genero2);

    return nuevo;
}

// ─────────────────────────────────────────────────────────────
//  Liberar memoria de un nodo individual
// ─────────────────────────────────────────────────────────────
void liberarPelicula(Pelicula *p) {
    if (!p) return;
    delete p->fecha;
    delete p->duracion;
    delete p;
}

// ─────────────────────────────────────────────────────────────
//  Inserción al FINAL de la lista
// ─────────────────────────────────────────────────────────────
void pushBack(const string &nombre, int precio,
              const string &genero1, const string &genero2,
              int dia, int mes, int anio,
              int horas, int minutos) {

    Pelicula *nuevo = crearPelicula(nombre, precio, genero1, genero2,
                                    dia, mes, anio, horas, minutos);

    if (lista == nullptr) {
        lista           = new Catalogo();
        lista->longitud = 1;
        lista->cabeza   = nuevo;
        lista->cola     = nuevo;
        return;
    }

    nuevo->anterior        = lista->cola;
    lista->cola->siguiente = nuevo;
    lista->cola            = nuevo;
    lista->longitud++;
}

// ─────────────────────────────────────────────────────────────
//  Inserción al INICIO de la lista
// ─────────────────────────────────────────────────────────────
void pushFront(const string &nombre, int precio,
               const string &genero1, const string &genero2,
               int dia, int mes, int anio,
               int horas, int minutos) {

    Pelicula *nuevo = crearPelicula(nombre, precio, genero1, genero2,
                                    dia, mes, anio, horas, minutos);

    if (lista == nullptr) {
        lista           = new Catalogo();
        lista->longitud = 1;
        lista->cabeza   = nuevo;
        lista->cola     = nuevo;
        return;
    }

    nuevo->siguiente        = lista->cabeza;
    lista->cabeza->anterior = nuevo;
    lista->cabeza           = nuevo;
    lista->longitud++;
}

// ─────────────────────────────────────────────────────────────
//  Inserción ORDENADA por fecha
// ─────────────────────────────────────────────────────────────
void pushFecha(const string &nombre, int precio,
               const string &genero1, const string &genero2,
               int dia, int mes, int anio,
               int horas, int minutos) {

    if (lista == nullptr) {
        pushBack(nombre, precio, genero1, genero2,
                 dia, mes, anio, horas, minutos);
        return;
    }

    Pelicula *nuevo = crearPelicula(nombre, precio, genero1, genero2,
                                    dia, mes, anio, horas, minutos);

    // Avanzar mientras el nodo actual tenga fecha <= a la nueva película
    Pelicula *actual = lista->cabeza;
    while (actual != nullptr &&
           fechaMenorIgual(actual->fecha->dia, actual->fecha->mes, actual->fecha->anio,
                           dia, mes, anio)) {
        actual = actual->siguiente;
    }

    // Caso 1: actual == nullptr → todos los nodos son anteriores → insertar al final
    if (actual == nullptr) {
        nuevo->anterior        = lista->cola;
        lista->cola->siguiente = nuevo;
        lista->cola            = nuevo;
        lista->longitud++;
        return;
    }

    // Caso 2: actual == cabeza → la nueva película es la más antigua → insertar al inicio
    if (actual == lista->cabeza) {
        nuevo->siguiente        = lista->cabeza;
        lista->cabeza->anterior = nuevo;
        lista->cabeza           = nuevo;
        lista->longitud++;
        return;
    }

    Pelicula *previo  = actual->anterior;
    previo->siguiente = nuevo;
    nuevo->anterior   = previo;
    nuevo->siguiente  = actual;
    actual->anterior  = nuevo;
    lista->longitud++;
}

// ─────────────────────────────────────────────────────────────
//  Eliminar un nodo por nombre
// ─────────────────────────────────────────────────────────────
bool eliminarPelicula(const string &nombre) {
    if (!lista) return false;

    Pelicula *actual = lista->cabeza;
    while (actual != nullptr) {
        if (actual->nombre == nombre) {
            // Reparar enlace del nodo anterior
            if (actual->anterior) actual->anterior->siguiente = actual->siguiente;
            else                  lista->cabeza = actual->siguiente;

            // Reparar enlace del nodo siguiente
            if (actual->siguiente) actual->siguiente->anterior = actual->anterior;
            else                   lista->cola = actual->anterior;

            lista->longitud--;
            liberarPelicula(actual);
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

// ─────────────────────────────────────────────────────────────
//  Búsqueda por nombre
// ─────────────────────────────────────────────────────────────
Pelicula *buscarPelicula(const string &nombre) {
    if (!lista) return nullptr;
    Pelicula *actual = lista->cabeza;
    while (actual != nullptr) {
        if (actual->nombre == nombre) return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

// ─────────────────────────────────────────────────────────────
//  Imprimir lista hacia ADELANTE
// ─────────────────────────────────────────────────────────────
void imprimirLista() {
    if (!lista) { cout << "Lista vacía.\n"; return; }

    cout << "\n====== Catálogo (→ adelante) — " << lista->longitud << " película(s) ======\n";
    Pelicula *temp = lista->cabeza;
    int idx = 1;
    while (temp != nullptr) {
        cout << "  [" << idx++ << "] " << temp->nombre
             << " | Fecha: "    << temp->fecha->dia << "/"
                                << temp->fecha->mes << "/"
                                << temp->fecha->anio
             << " | Duración: " << temp->duracion->horas   << "h "
                                << temp->duracion->minutos << "min"
             << " | Precio: $"  << temp->precio << "\n";
        temp = temp->siguiente;
    }
}

// ─────────────────────────────────────────────────────────────
//  Imprimir lista hacia ATRÁS
// ─────────────────────────────────────────────────────────────
void imprimirListaInversa() {
    if (!lista) { cout << "Lista vacía.\n"; return; }

    cout << "\n====== Catálogo (← inverso) ======\n";
    Pelicula *temp = lista->cola;
    int idx = lista->longitud;
    while (temp != nullptr) {
        cout << "  [" << idx-- << "] " << temp->nombre
             << " | Fecha: " << temp->fecha->dia << "/"
                             << temp->fecha->mes << "/"
                             << temp->fecha->anio << "\n";
        temp = temp->anterior;
    }
}

// ─────────────────────────────────────────────────────────────
//  Liberar TODA la memoria del catálogo
// ─────────────────────────────────────────────────────────────
void liberarLista() {
    if (!lista) return;
    Pelicula *actual = lista->cabeza;
    while (actual != nullptr) {
        Pelicula *siguiente = actual->siguiente;
        liberarPelicula(actual);
        actual = siguiente;
    }
    delete lista;
    lista = nullptr;
}

// ─────────────────────────────────────────────────────────────
//  Main — prueba de todas las operaciones
// ─────────────────────────────────────────────────────────────
int main() {

    // ── Inserción ordenada por fecha ──
    cout << "--- Inserción ordenada por fecha ---\n";
    pushFecha("El Padrino",   150, "drama",     "suspenso",   24, 3,  1972, 2, 55);
    pushFecha("Toy Story",     80, "animation", "comedia",    22, 11, 1995, 1, 21);
    pushFecha("Matrix",       120, "accion",    "suspenso",   31, 3,  1999, 2, 16);
    pushFecha("Inception",    130, "accion",    "drama",      16, 7,  2010, 2, 28);
    pushFecha("Coco",          90, "animation", "drama",      22, 11, 2017, 1, 45);
    imprimirLista();
    imprimirListaInversa();

    // ── Inserción al inicio y al final ──
    cout << "\n--- pushFront y pushBack ---\n";
    pushFront("Metrópolis",    60, "drama",  "suspenso", 10, 1,  1927, 2, 33);
    pushBack ("Dune: Parte 2", 140, "accion","drama",     1, 3,  2024, 2, 46);
    imprimirLista();

    // ── Búsqueda ──
    cout << "\n--- Búsqueda ---\n";
    Pelicula *encontrada = buscarPelicula("Inception");
    if (encontrada)
        cout << "  Encontrada: " << encontrada->nombre
             << " (" << encontrada->fecha->anio << ")\n";
    else
        cout << "  No encontrada.\n";

    encontrada = buscarPelicula("Avatar");
    if (!encontrada)
        cout << "  'Avatar' no está en el catálogo.\n";

    // ── Eliminación ──
    cout << "\n--- Eliminar 'Inception' ---\n";
    if (eliminarPelicula("Inception"))
        cout << "  Película eliminada correctamente.\n";
    imprimirLista();

    // ── Verificar que los punteros anterior/siguiente son consistentes ──
    cout << "\n--- Verificación de consistencia de punteros ---\n";
    Pelicula *cur = lista->cabeza;
    bool ok = true;
    while (cur != nullptr && cur->siguiente != nullptr) {
        if (cur->siguiente->anterior != cur) { ok = false; break; }
        cur = cur->siguiente;
    }
    cout << "  Punteros " << (ok ? "CONSISTENTES ✓" : "INCONSISTENTES ✗") << "\n";

    // ── Liberar memoria ──
    liberarLista();
    cout << "\nMemoria liberada. Fin del programa.\n";
    return 0;
} 