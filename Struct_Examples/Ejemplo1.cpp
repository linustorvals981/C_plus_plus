#include <iostream>
#include <vector>

using namespace std;

struct Alumno {
    string nombre;
    int edad;
};

int main () {
    vector<Alumno> v1;
    v1.push_back({"Juan", 18});
    v1.push_back({"Pedro", 19});
    v1.push_back({"Carlos", 20});
    
    vector<Alumno> v2;
    v2.push_back({"Edu", 28});
    v2.push_back({"Pedro", 29});
    v2.push_back({"Carlos", 30});

    for (int i = 0; i < v1.size(); i++) {
        cout << "Vector1[" << i << "] = " << "Nombre = " << v1[i].nombre << ", Edad = " << v1[i].edad << endl;
    }

    for (int i = 0; i < v2.size(); i++) {
        cout << "Vector2[" << i << "] = " << "Nombre = " << v2[i].nombre << ", Edad = " << v2[i].edad << endl;
    }

    vector<Alumno> aux;
    for (int i = 0; i < v1.size(); i++) {
        if (v1[i].edad > 25) {
            v2.push_back(v1[i]);
            v1.erase(v1.begin() + i);
        }
    }
    v1.shrink_to_fit();

    for (int i = 0; i < v2.size(); i++) {
        if (v1[i].edad < 25) {
            v1.push_back(v1[i]);
            v2.erase(v1.begin() + i);
        }
    }
    v2.shrink_to_fit();
    

    


}