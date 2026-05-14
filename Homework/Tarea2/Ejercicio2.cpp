#include <iostream>
#include <vector>

using namespace std;

void llenaVector(vector<int>& vect, int n);
void eliminaImpares(vector<int>& vect);
void printVector(const vector<int>& vect);

/**
 * Programa que busca demostrar como crece dinamicamente un vector en memoria.
 */
int main() {
    // 1. Crea un vector<int>.
    vector<int> mi_vector;
    cout << "Vector creado." << endl;

    // 2. Imprime su tamanio (size) y capacidad (capacity) iniciales.
    cout << "El vector tiene un tamanio inicial = " << mi_vector.size()
         << " y una capacidad inicial = " << mi_vector.capacity() << endl;
 
    // 3. Utiliza un ciclo para agregar 100 elementos continuos usando push back(). Dentro del
    // bucle, imprime en consola cada vez que la capacidad del vector cambie.
    llenaVector(mi_vector, 100);

    // 4. Una vez finalizado el bucle, elimina con erase() los elementos de indice impar.
    eliminaImpares(mi_vector);

    // 5. Llama a la funcion shrink to fit() para liberar la memoria RAM no utilizada y com-
    // prueba imprimiendo nuevamente la capacidad final.
    mi_vector.shrink_to_fit();
    cout << "El vector tiene un tamanio final = " << mi_vector.size()
         << " y una capacidad final = " << mi_vector.capacity() << endl;
}

void llenaVector(vector<int>& vect, int n) {
    for (int i = 0; i < n; i++) {
        int valor = i + 1;
        vect.push_back(valor);
        cout << "El vector tiene un tamanio = " << vect.size()
         << " y una capacidad = " << vect.capacity() << endl;
    }       
}

void eliminaImpares(vector<int>& vect) {
    for (int i = 0; i < vect.size(); i++) {
        if (vect[i] % 2 == 1) {
            vect.erase(vect.begin() + i);
        }
    }
}

void printVector(const vector<int>& vect) {
    cout << "[";
    for (int i = 0; i < vect.size() - 1; i++) {
        cout << vect[i] << ", ";
    }
    cout << vect.back() << "]" << endl;
}