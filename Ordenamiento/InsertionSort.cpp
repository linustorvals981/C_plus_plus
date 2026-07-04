#include <chrono>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

void insertionSort(vector<int> &arr) {
  int n = arr.size();
  for (int i = 1; i < n; i++) {
    int clave = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j] > clave) {
      arr[j + 1] = arr[j];
      j--;
    }

    arr[j + 1] = clave;
  }
}

void printVector(const vector<int> &arr, const string &name) {
  int n = arr.size();
  cout << "Vector " << name << "[ ";

  for (int i = 0; i < n - 1; i++)
    cout << arr[i] << ", ";

  cout << arr[n - 1] << "]" << endl;
}

template <typename Func>
long long measureTime(Func sortFunction, vector<int> arr) {
  auto start = chrono::high_resolution_clock::now();

  sortFunction(arr);

  auto end = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

  cout << "Insertion Sort tomó: " << duration.count() << " milisegundos"
       << endl;
  return duration.count();
}

int main() {
  const int MAX_SIZE = 1000000;
  vector<int> datos(MAX_SIZE);

  srand(time(0));

  for (int i = 0; i < MAX_SIZE; i++) {
    datos[i] = rand() % 100;
  }

  // printVector(datos, "Original");
  auto promedio = 0.0;
  for (int i = 0; i < 10; i++) {
    promedio += measureTime(insertionSort, datos);
  }
  cout << "Promedio InsertionSort (10 ejecuciones): " << promedio / 10
       << " milisegundos" << endl;

  // printVector(datos, "Ordenado");

  return 0;
}
