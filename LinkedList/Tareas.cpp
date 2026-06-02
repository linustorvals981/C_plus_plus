#include <iostream>
#include <limits>
#include <string>

using namespace std;

struct Tarea {
    string titulo;
    string descripcion;
    double calificacion;
    bool completada;
    Tarea *siguiente;
};

struct Lista {
    int longitud;
    Tarea *cabeza;
};

//--------------------------------------------------
// Limpia el buffer de entrada
//--------------------------------------------------
void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//--------------------------------------------------
// Crear un nuevo nodo
//--------------------------------------------------
Tarea *crearNodo() {

    Tarea *nuevo = new Tarea;

    limpiarBuffer();

    cout << "Ingrese el titulo de la tarea: ";
    getline(cin, nuevo->titulo);

    cout << "Ingrese la descripcion de la tarea: ";
    getline(cin, nuevo->descripcion);

    cout << "Ingrese la calificacion de la tarea: ";
    cin >> nuevo->calificacion;

    nuevo->completada = false;
    nuevo->siguiente = nullptr;

    return nuevo;
}

//--------------------------------------------------
// Insertar nodo al final
//--------------------------------------------------
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

//--------------------------------------------------
// Insertar nodo al inicio
//--------------------------------------------------
void enlazarNodoFront(Lista *&lista) {

    if (lista == nullptr) {

        lista = new Lista;
        lista->longitud = 1;
        lista->cabeza = crearNodo();

    } else {

        if (lista->cabeza == nullptr) {

            lista->cabeza = crearNodo();
            lista->longitud = 1;

        } else {

            Tarea *aux = lista->cabeza;

            lista->cabeza = crearNodo();
            lista->cabeza->siguiente = aux;

            lista->longitud++;
        }
    }
}

//--------------------------------------------------
// Mostrar lista
//--------------------------------------------------
void mostrarLista(Lista *&lista) {

    if (lista == nullptr || lista->cabeza == nullptr) {
        cout << "La lista esta vacia.\n";
        return;
    }

    Tarea *aux = lista->cabeza;

    while (aux != nullptr) {

        cout << "\n-------------- TAREA ----------------\n";
        cout << "| Titulo       : " << aux->titulo << "\n";
        cout << "| Descripcion  : " << aux->descripcion << "\n";
        cout << "| Calificacion : " << aux->calificacion << "\n";

        if (aux->completada) {
            cout << "| Estado       : Completada\n";
        } else {
            cout << "| Estado       : No completada\n";
        }

        cout << "-------------------------------------\n";

        aux = aux->siguiente;
    }
}

//--------------------------------------------------
// Eliminar tarea
//--------------------------------------------------
void eliminarTarea(Lista *&lista) {

    if (lista == nullptr || lista->cabeza == nullptr) {
        cout << "La lista esta vacia.\n";
        return;
    }

    string titulo;

    cout << "Ingrese el nombre de la tarea a eliminar: ";

    limpiarBuffer();
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

            cout << "Tarea eliminada correctamente.\n";

            return;
        }

        anterior = actual;
        actual = actual->siguiente;
    }

    cout << "La tarea no se encontro.\n";
}

//--------------------------------------------------
// Destruir lista
//--------------------------------------------------
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

//--------------------------------------------------
// Marcar tarea como completada
//--------------------------------------------------
void marcarCompletada(Lista *&lista) {

    if (lista == nullptr || lista->cabeza == nullptr) {
        cout << "La lista esta vacia.\n";
        return;
    }

    string titulo;
    string opcion;

    cout << "Ingrese el nombre de la tarea: ";

    limpiarBuffer();
    getline(cin, titulo);

    Tarea *actual = lista->cabeza;

    while (actual != nullptr) {

        if (actual->titulo == titulo) {

            cout << "Desea marcar la tarea como completada? (y/n): ";
            getline(cin, opcion);

            if (opcion == "y" || opcion == "Y") {

                actual->completada = true;

                cout << "Tarea marcada como completada.\n";
            }

            return;
        }

        actual = actual->siguiente;
    }

    cout << "La tarea no se encontro.\n";
}

//--------------------------------------------------
// Filtrar tareas
//--------------------------------------------------
void filtrarLista(Lista *&lista) {

    if (lista == nullptr || lista->cabeza == nullptr) {
        cout << "La lista esta vacia.\n";
        return;
    }

    int opcion;

    cout << "\n1. Mostrar completadas\n";
    cout << "2. Mostrar no completadas\n";
    cout << "Seleccione una opcion: ";

    cin >> opcion;

    bool estado;

    if (opcion == 1) {
        estado = true;
    } else {
        estado = false;
    }

    Tarea *actual = lista->cabeza;

    while (actual != nullptr) {

        if (actual->completada == estado) {

            cout << "\n-------------- TAREA ----------------\n";
            cout << "| Titulo       : " << actual->titulo << "\n";
            cout << "| Descripcion  : " << actual->descripcion << "\n";
            cout << "| Calificacion : " << actual->calificacion << "\n";

            if (actual->completada) {
                cout << "| Estado       : Completada\n";
            } else {
                cout << "| Estado       : No completada\n";
            }

            cout << "-------------------------------------\n";
        }

        actual = actual->siguiente;
    }
}

//--------------------------------------------------
// Calcular promedio
//--------------------------------------------------
double calculaPromedio(Lista *&lista) {

    if (lista == nullptr || lista->cabeza == nullptr) {

        cout << "La lista esta vacia.\n";

        return 0.0;
    }

    double suma = 0.0;

    Tarea *actual = lista->cabeza;

    while (actual != nullptr) {

        suma += actual->calificacion;

        actual = actual->siguiente;
    }

    return suma / lista->longitud;
}

//--------------------------------------------------
// Main
//--------------------------------------------------
int main() {

    Lista *lista = nullptr;

    int opcion;

    do {

        cout << "\n========== MENU ==========\n";
        cout << "1. Agregar tarea al inicio\n";
        cout << "2. Agregar tarea al final\n";
        cout << "3. Mostrar tareas\n";
        cout << "4. Eliminar tarea\n";
        cout << "5. Marcar tarea como completada\n";
        cout << "6. Filtrar tareas\n";
        cout << "7. Calcular promedio\n";
        cout << "8. Mostrar longitud de la lista\n";
        cout << "9. Destruir lista\n";
        cout << "0. Salir\n";

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                enlazarNodoFront(lista);
                cout << "Tarea agregada al inicio.\n";
                break;

            case 2:
                enlazarNodoBack(lista);
                cout << "Tarea agregada al final.\n";
                break;

            case 3:
                mostrarLista(lista);
                break;

            case 4:
                eliminarTarea(lista);
                break;

            case 5:
                marcarCompletada(lista);
                break;

            case 6:
                filtrarLista(lista);
                break;

            case 7:
                if (lista != nullptr && lista->cabeza != nullptr) {
                    cout << "Promedio: "
                         << calculaPromedio(lista)
                         << "\n";
                }

                break;

            case 8:
                if (lista == nullptr) {
                    cout << "La lista no existe.\n";
                } else {
                    cout << "Longitud de la lista: "
                         << lista->longitud
                         << "\n";
                }

                break;

            case 9:
                destruirLista(lista);
                cout << "Lista destruida correctamente.\n";
                break;

            case 0:
                destruirLista(lista);
                cout << "Saliendo del programa...\n";
                break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 0);

    return 0;
}