#include <iostream>
#include <vector>
#include <string>

using namespace std;

void flipPares(vector<int>& vect_1, vector<int>& result);
void imprimeVector(vector<int>& vect, string name);

int main() {
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);
    v1.push_back(6);
    v1.push_back(7);
    v1.push_back(8);
    imprimeVector(v1, "Original");

    vector<int> result;
    flipPares(v1, result);

    imprimeVector(result, "Flip en Reversa");

    return 0;
}

void flipPares(vector<int>& vect_1, vector<int>& result) {
    if (vect_1.size() == 0) 
        throw invalid_argument("El vector esta vacio.");
    
    for (int i = vect_1.size() - 1; i >= 0; i--) {
        if (vect_1.at(i) % 2 == 0)
            result.push_back(vect_1.at(i));
    }
}

void imprimeVector(vector<int>& vect, string name) {
    cout << "Vector " << name << ": " << endl;
    for (int i = 0; i < vect.size(); i++) {
        cout << "vect[" << i << "] = " << vect.at(i) << endl;
    }
    
}