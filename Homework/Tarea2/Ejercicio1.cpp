#include <iostream>
#include <vector>

using namespace std;

void ingresaCalificaciones(vector<float>& cals, int n);
float calculaPromedio(vector<float>& cals);
int indiceCalificacionMenor(vector<float>& cals);
void printVector(const vector<float>& cals);

/**
 * Programa que simula el registro de calificaciones de un grupo.
 */
int main() {
    // 1. Crea un vector<float> vacio.
    vector<float> calificaciones;

    // 2. Solicita al usuario que ingrese 5 calificaciones y agregalas al vector usando push back().
    ingresaCalificaciones(calificaciones, 5);
    cout << "Se ingresaron correctamente las calificaciones: " << endl; 
    printVector(calificaciones);

    // 3. Recorre el vector y calcula el promedio del grupo.
    float promedio = calculaPromedio(calificaciones);

    // 4. Encuentra la calificacion mas baja y eliminala usando el metodo erase().
    int indice_cal_menor = indiceCalificacionMenor(calificaciones);
    calificaciones.erase(calificaciones.begin() + indice_cal_menor);

    // 5. Imprime el tamanio actual del vector (size()) y las calificaciones restantes.
    cout << "El vector calificaciones tiene un tamanio = " << calificaciones.size() << " despues de usar la funcion erase()" << endl;
    printVector(calificaciones);
}

void ingresaCalificaciones(vector<float>& cals, int n) {
    float aux = 0.0f;
    for (int i = 0; i < n; i++) {
        cout << "Ingresa la calificacion " << (i + 1) << ": ";
        cin >> aux;
        cals.push_back(aux);
    }
}

float calculaPromedio(vector<float>& cals) {
    float suma = 0.0f;
    int n = cals.size();
    for (int i = 0; i < n; i++) {
        suma += cals[i];
    }
    float promedio = suma / n;
    return promedio;
}

int indiceCalificacionMenor(vector<float>& cals) {
    int indice_cal_menor = 0;
    for (int i = 0; i < cals.size(); i++) {
        if (cals[i] < cals[indice_cal_menor]) {
            indice_cal_menor = i;
        }
    }
    return indice_cal_menor;
}

void printVector(const vector<float>& cals) {
    cout << "[";
    for (int i = 0; i < cals.size() - 1; i++) {
        cout << cals[i] << ", ";
    }
    cout << cals.back() << "]" << endl;
}