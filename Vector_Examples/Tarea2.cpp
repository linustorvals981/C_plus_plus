#include <iostream>
#include <vector>

using namespace std;

/**
 * Tarea 2: VEc Triples en Datos Volumetricos
 */
int main() {
    const int FILAS =  3;
    const int COLUMNAS = 3;
    const int CAPAS = 3;
    
    // 1. Construir din amicamente un arreglo 3D de tamanio 3 × 3 × 3 (CAPAS, FILAS, COLUMNAS). 
    vector<vector<vector<double>>> cubo(FILAS, vector<vector<double>>(COLUMNAS, vector<double>(CAPAS, 0)));
    
    // 2. Llenar toda la estructura con valores arbitrarios (ej. i + j + k).
    for (int i = 0; i < cubo.size(); i++) {
        for (int j = 0; j < cubo[i].size(); j++) {
            for (int k = 0; k < cubo[i][j].size(); k++) {
                cubo[i][j][k] = i + j + k;
            }
        }
    }

    //3. Calcular la suma y el promedio  unicamente de la  ultima capa de datos.
    int ultimaCapa = CAPAS - 1;
    double suma = 0;

    for (int i = 0; i < cubo.size(); i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            suma += cubo[i][j][ultimaCapa];
        }
    }

    double promedio = suma / (FILAS * COLUMNAS);

    // 4. Guardar ese promedio en una nueva variable alojada en el Heap (memoria dinamica).
    double *promedio_ptr = new double;
    *promedio_ptr = promedio;

    // 5. Mostrar el promedio en consola.
    cout << "El promedio es: " << *promedio_ptr << endl; 

    // 6. Destruir el promedio alojado en el Heap.
    delete promedio_ptr;
    promedio_ptr = nullptr;

    // 7. Realizar la destruccion recursiva del arreglo 3D completo para evitar fugas de memoria.
    cubo.clear();

    return 0;
}