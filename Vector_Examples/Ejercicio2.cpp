#include <iostream>
#include <vector>

using namespace std;

void printMatriz(vector<vector<int>>& matriz, string name);
void llenaMatriz(vector<vector<int>>& matriz);

int main() {

    vector<vector <int>> matriz(5, vector<int>(5, 0));
    llenaMatriz(matriz);
    printMatriz(matriz , "m1");
    
    return 0;
}

void printMatriz(vector <vector<int>>& matriz, string name) {
    cout << "Matriz " << name << ": " << endl;
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}   

void llenaMatriz(vector<vector<int>>& matriz) {
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[i].size(); j++) {
            matriz[i][j] = i + j + 1;
        }
    }
}