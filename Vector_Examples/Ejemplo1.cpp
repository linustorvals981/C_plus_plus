#include <iostream>
#include <vector>

using namespace std;

int main() {

    vector<int> vect_1(10);
    vect_1.push_back(1);
    vect_1.push_back(2);
    vect_1.push_back(3);

    cout << "Vector 1 size: " << vect_1.size() << endl;  
    cout << "Vector 1 capacity: " << vect_1.capacity() << endl;   
    
    vect_1.pop_back();

    cout << "Vector 1 size: " << vect_1.size() << endl;  
    cout << "Vector 1 capacity: " << vect_1.capacity() << endl;  

    for (int i = 0; i < vect_1.size(); i++)
    {
        cout << "Vect[" << i << "] = " << vect_1[i] << endl;
    }
    

    
    return 0;
}
