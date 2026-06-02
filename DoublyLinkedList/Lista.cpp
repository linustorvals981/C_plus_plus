#include <iostream>

using namespace std;

struct Genero {
    bool terror;
    bool romance;
    bool comedia;
    bool suspenso;
    bool drama;
    bool animacion;
    bool accion;
    bool aventura;
    bool fantasia;
    bool musical;
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
    struct Genero genero;  
    struct Duracion *duracion;
    struct FechaLanzamiento *fecha_lanzamiento;
    struct Pelicula *siguiente;
    struct Pelicula *anterior;
};

struct Catalogo {
    int longitud;
    struct Pelicula *cabeza;
    struct Pelilcula *cola;
};

Catalogo *lista = nullptr;

Pelicula *crearPelicula(string nombre, int precio, struct Duracion duracion, string genero1, string genero2, 
                        int dia, int mes, int anio, int horas, int minutos) {
    Pelicula *nuevo = new Pelicula();

    nuevo->nombre = nombre;
    nuevo->precio = precio;
    nuevo->asientosDisponibles = 100;
    nuevo->fecha_lanzamiento->dia = dia;
    nuevo->fecha_lanzamiento->mes = mes;
    nuevo->fecha_lanzamiento->anio = anio;
    nuevo->duracion->horas = horas;
    nuevo->duracion->minutos = minutos;
    nuevo->genero.terror = false;
    nuevo->genero.romance = false;
    nuevo->genero.comedia = false;
    nuevo->genero.suspenso = false;
    nuevo->genero.drama = false;
    nuevo->genero.animation = false;
    nuevo->genero.accion = false;

    if (genero1.compare("accion") == 0 || genero2.compare("accion") == 0) {
        nuevo->genero.accion = true;
    }
    if (genero1.compare("terror") == 0 || genero2.compare("terror") == 0) {
        nuevo->genero.terror = true;
    }
    if (genero1.compare("romance") == 0 || genero2.compare("romance") == 0) {
        nuevo->genero.romance = true;
    }
    if (genero1.compare("comedia") == 0 || genero2.compare("comedia") == 0) {
        nuevo->genero.comedia = true;
    }
    if (genero1.compare("suspenso") == 0 || genero2.compare("suspenso") == 0) {
        nuevo->genero.suspenso = true;
    }
    if (genero1.compare("drama") == 0 || genero2.compare("drama") == 0) {
        nuevo->genero.drama = true;
    }
    if (genero1.compare("animation") == 0 || genero2.compare("animation") == 0) {
        nuevo->genero.animation = true;
    }
    
    nuevo->siguiente = nullptr;
    nuevo->anterior = nullptr;
    return nuevo;
}

int pushBack(string nombre, int precio, struct Duracion duracion, string genero1, string genero2, 
                        int dia, int mes, int anio, int horas, int minutos) {
    Pelicula *nuevo = crearPelicula(nombre, precio, duracion, genero1, genero2,
    dia, mes, anio, horas, minutos);
    
    if (lista == nullptr) {
        lista = new Catalogo();
        lista->longitud = 1;
        lista->cabeza = nuevo;
        lista->cola = nuevo;
        return 0;
    } else {    
        lista->cola->siguiente = nuevo;
        nuevo->anterior = lista->cola;
        lista->cola = nuevo;
        lista->longitud++;
        return 0;
    }
    return -1;
}

int pushFront(string nombre, int precio, struct Duracion duracion, string genero1, string genero2, 
                        int dia, int mes, int anio, int horas, int minutos) {
    Pelicula *nuevo = crearPelicula(nombre, precio, duracion, genero1, genero2,
    dia, mes, anio, horas, minutos);
    
    if (lista == nullptr) {
        lista = new Catalogo();
        lista->longitud = 1;
        lista->cabeza = nuevo;
        lista->cola = nuevo;
        return 0;
    } else {
        lista->cabeza->anterior = nuevo;
        nuevo->siguiente = lista->cabeza;
        lista->cabeza = nuevo;
        lista->longitud++;
        return 0;
    }
    return -1;
}

int pushFecha(string nombre, int precio, struct Duracion duracion, string genero1, string genero2, 
                        int dia, int mes, int anio, int horas, int minutos) {
    Pelicula *nuevo = crearPelicula(nombre, precio, duracion, genero1, genero2,
    dia, mes, anio, horas, minutos);

    Pelicula *actual = lista->cabeza;
    
    while (actual->siguiente != nullptr && actual->siguiente->fecha_lanzamiento->anio <= anio && 
           actual->siguiente->fecha_lanzamiento->mes <= mes && actual->siguiente->fecha_lanzamiento->dia <= dia) {
        actual = actual->siguiente;
    }
    if (actual == nullptr) {
        pushBack(nombre, precio, duracion, genero1, genero2,
        dia, mes, anio, horas, minutos);
        return 0;
    }
    actual->siguiente->anterior = nuevo;
    actual->siguiente = nuevo;
    nuevo->anterior = actual;
    nuevo->siguiente = actual->siguiente;
    lista->longitud++;

    return 0;
}

int printList() {
    if (lista == nullptr) {
        cout << "Lista vacia" << endl;
        return -1;
    }
    Pelicula *temp = lista->cabeza;
    while (temp != nullptr) {
        cout << temp->nombre << endl;
        cout << temp->fecha_lanzamiento->anio << endl;
        cout << temp->fecha_lanzamiento->mes << endl;
        cout << temp->fecha_lanzamiento->dia << endl;
        cout << temp->duracion->horas << endl;
        cout << temp->duracion->minutos << endl;
        temp = temp->siguiente;
    }
    return 0;
}

int main() {
    pushFecha("Pelicula 1", 10, {1, 1, 2022}, "accion", "terror", 1, 1, 2022, 1, 1);
    pushFecha("Pelicula 2", 10, {1, 1, 2022}, "comedia", "drama", 1, 1, 2022, 1, 1);
    pushFecha("Pelicula 3", 10, {1, 1, 2022}, "romance", "terror", 1, 1, 2022, 1, 1);
    pushFecha("Pelicula 4", 10, {1, 1, 2022}, "accion", "suspenso", 1, 1, 2022, 1, 1);
    pushFecha("Pelicula 5", 10, {1, 1, 2022}, "accion", "terror", 1, 1, 2022, 1, 1);
    pushFecha("Pelicula 6", 10, {1, 1, 2022}, "musical", "accion", 1, 1, 2022, 1, 1);
    pushFecha("Pelicula 7", 10, {1, 1, 2022}, "accion", "terror", 1, 1, 2022, 1, 1);
    pushFecha("Pelicula 8", 10, {1, 1, 2022}, "accion", "terror", 1, 1, 2022, 1, 1);
    pushFecha("Pelicula 9", 10, {1, 1, 2022}, "accion", "terror", 1, 1, 2022, 1, 1);
    pushFecha("Pelicula 10", 10, {1, 1, 2022}, "accion", "terror", 1, 1, 2022, 1, 1);
    printList();
    return 0;
}
