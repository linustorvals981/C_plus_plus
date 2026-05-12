#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<int> v, string name);

int main() {

    vector<int> vect_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printVector(vect_1, "v1");
    vect_1.insert(vect_1.begin() + 2, 8);
    printVector(vect_1, "v1");

    vector<int> vect_2 = {1, 5, 7, 11, 13};
    printVector(vect_2, "v2");
    vect_2.erase(vect_2.begin() + 3); 
    cout << "Size v2: " << vect_2.size() << ", Capacity v2: " << vect_2.capacity() << endl;
    vect_2.shrink_to_fit();
    printVector(vect_2, "v2");
    cout << "Size v2: " << vect_2.size() << ", Capacity v2: " << vect_2.capacity() << endl;

    
    return 0;
}

void printVector(vector<int> v, string name) {
    cout << "Vector " << name << ": " << endl;
    for (int i : v) {
        cout << i << " ";
    }
    cout << endl;
}