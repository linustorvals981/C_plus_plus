#include <iostream>
#include <vector>

using namespace std;

void productoPunto(vector<int>& vect_1, vector<int>& vect_2, vector<int>& result);

int main() {
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);

    vector<int> v2;
    v2.push_back(5);
    v2.push_back(6);
    v2.push_back(7);
    v2.push_back(8);

    vector<int> result;
    productoPunto(v1, v2, result);

    cout << "El producto punto es: " << result.at(0) << endl;

    return 0;
}

void productoPunto(vector<int>& vect_1, vector<int>& vect_2, vector<int>& result) {
    if (vect_1.size() != vect_2.size()) 
        throw invalid_argument("Los vectore no son de la misma direccion.");
    
    int acum = 0;
    
    for (int i = 0; i < vect_1.size(); i++) {
        acum += vect_1[i] * vect_2[i];
    }

    result.push_back(acum);
}