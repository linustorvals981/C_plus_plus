#include <iostream>
#include <vector>
#include <string>

using namespace std;


//1. Define un struct Empleado que contenga: string nombre, int id, y float salario
struct Empleado {
    string nombre;
    int id;
    float salario;

    Empleado(string n, int i, float s) : nombre(n), id(i), salario(s) {}
};

void insertaOrdenado(vector<Empleado>& original, vector<Empleado>& destino);
void printVector(vector<Empleado>& vect);

/**
 * Programa que implementa un directorio que mantenga a los empleados ordenados automaticamente por su
 * numero de identificacion (ID) al momento de ser ingresados
 */
int main() {
    //2. En la funcion main, crea un vector<Empleado> vacio
    vector<Empleado> empleados;

    //3. Crea manualmente cuatro instancias de la estructura Empleado asignandoles IDs desorde-
    //nados (por ejemplo: 105, 102, 109, 101)
    Empleado e1 = {"Ana", 105, 3500.50f};
    Empleado e2 = {"Luis", 102, 4200.00f};
    Empleado e3 = {"Carlos", 109, 3900.75f};
    Empleado e4 = {"Maria", 101, 4500.25f};

    empleados.push_back(e1);
    empleados.push_back(e2);
    empleados.push_back(e3);
    empleados.push_back(e4);

    cout << "Vector original:\n";
    printVector(empleados);

    // 4. Implementa la logica de insercion ordenada: para agregar cada empleado, recorre el vector
    // para encontrar la posicion exacta donde debe ir el nuevo registro, garantizando que el
    // vector se mantenga ordenado de menor a mayor respecto al id.
    // 5. Utiliza el metodo insert() pasando el iterador calculado y la instancia del empleado
    // previamente construida.
    vector<Empleado> directorio;
    insertaOrdenado(empleados, directorio);

    // 6. Imprime el directorio completo recorriendolo exclusivamente con iteradores para demostrar
    // que los empleados quedaron correctamente ordenados por su ID.
    cout << "\nVector ordenado:\n";
    printVector(directorio);

    return 0;
}

void insertaOrdenado(vector<Empleado>& original, vector<Empleado>& destino) {
    for (size_t i = 0; i < original.size(); i++) {
        Empleado actual = original[i];
        vector<Empleado>::iterator it = destino.begin();
        while (it != destino.end() && it->id < actual.id) {
            it++;
        }
        destino.insert(it, actual);
    }
}

void printVector(vector<Empleado>& vect) {
    cout << "--- Directorio de Empleados ---" << endl;

    for (vector<Empleado>::iterator it = vect.begin(); it != vect.end(); it++) {
        cout << "ID      : " << it->id << endl;
        cout << "Nombre  : " << it->nombre << endl;
        cout << "Salario : $" << it->salario << endl;
        cout << endl;
    }
}   