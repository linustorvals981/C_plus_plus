#include <iostream>
#include <vector>

using namespace std;

void imprimeMatriz(vector<vector<int>>& matriz);
int calculaDisponibles(vector<vector<int> >& matriz);

int main() {
    // 1. Crea un vector anidado que represente una cuadricula de 16x16. Inicializa todos los valores
    // en 0 (que significa disponible)
    vector<vector<int> > matriz(16, vector<int>(16, 0));

    // 2. Escribe codigo para marcar los asientos (1,2), (2,4) y (3,8) con el valor 1 (ocupado).
    // Recordar que los indices inician en 0
    matriz[1][2] = 1;
    matriz[2][4] = 1;
    matriz[3][8] = 1;

    // 3. Escribe una funcion o bloque de codigo con bucles anidados que imprima la matriz completa
    // en forma de cuadricula.
    imprimeMatriz(matriz);

    // 4. Calcular e imprimir el total de asientos disponibles (valor 0)
    int disponibles = calculaDisponibles(matriz);
    cout << "Total de asientos disponibles: " << disponibles << endl;
    cout << "Total de asientos ocupados: " << (16 * 16) - disponibles << endl;

    return 0;
}

void imprimeMatriz(vector<vector<int> >& matriz) {
    cout << "--- Estado de la matriz (0: Libre, 1: Ocupado) ---" << endl;
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl; 
    }
}

int calculaDisponibles(vector<vector<int> >& matriz) {
    int disponibles = 0;
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {
            if (matriz[i][j] == 0) {
                disponibles++;
            }
        }
    }
    return disponibles;
}