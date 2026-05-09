#include <iostream>

using namespace std;

int main() {
    int filas =  3;
    int columnas = 3;
    int capas = 3;
    
    // 1. Construir din amicamente un arreglo 3D de tamanio 3 × 3 × 3 (capas, filas, columnas). 
    double ***cubo = new double**[capas];

    for (int i = 0; i < capas; i++) {
        cubo[i] = new double*[filas];
        for (int j = 0; j < filas; j++) {
            cubo[i][j] = new double[columnas];
        }
    }
    
    // 2. Llenar toda la estructura con valores arbitrarios (ej. i + j + k).
    for (int i = 0; i < capas; i++) {
        for (int j = 0; j < filas; j++) {
            for (int k = 0; k < columnas; k++) {
                cubo[i][j][k] = i + j+ k;
            }
        }
    }

    //3. Calcular la suma y el promedio  unicamente de la  ultima capa de datos.
    int ultimaCapa = capas - 1;
    double suma = 0;

    for (int j = 0; j < filas; j++) {
        for (int k = 0; k < columnas; k++) {
            suma += cubo[ultimaCapa][j][k];
        }
    }

    double promedio = suma / (filas * columnas);

    // 4. Guardar ese promedio en una nueva variable alojada en el Heap (memoria dinamica).
    double *promedio_ptr = new double;
    *promedio_ptr = promedio;

    // 5. Mostrar el promedio en consola.
    cout << "El promedio es: " << *promedio_ptr << endl; 

    // 6. Destruir el promedio alojado en el Heap.
    delete promedio_ptr;
    promedio_ptr = nullptr;

    // 7. Realizar la destruccion recursiva del arreglo 3D completo para evitar fugas de memoria.
    for (int i = 0; i < capas; i++) {
        for (int j = 0; j < filas; j++) {
            delete[] cubo[i][j];
            cubo[i][j] = nullptr;
        }
        delete[] cubo[i];
        cubo[i] = nullptr;
    } 

    delete[] cubo;
    cubo = nullptr;

    return 0;
}