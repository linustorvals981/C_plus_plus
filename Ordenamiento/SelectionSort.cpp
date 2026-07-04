#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

void selectionSort(vector<int> &arr, int n) {
  for (int i = 0; i < n - 1; i++) {
    int posMin = i;
    for (int j = i + 1; j < n; j++) {
      if (arr[j] < arr[posMin]) {
        posMin = j;
      }
    }
    if (posMin != i) {
      std::swap(arr[i], arr[posMin]);
    }
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
long long measureTime(Func sortFunction, vector<int> &arr) {
  auto start = chrono::high_resolution_clock::now();

  sortFunction(arr, arr.size());

  auto end = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

  return duration.count();
}

int main() {
  const int MAX_SIZE = 1000;
  vector<int> datos(MAX_SIZE);
  srand(time(0));
  for (int i = 0; i < MAX_SIZE; i++) {
    datos[i] = rand() % 100;
  }

  printVector(datos, "Original\n");
  auto tiempo = measureTime(selectionSort, datos);
  cout << "\nSelectionSort tomó: " << tiempo << " milisegundos.\n\n";
  printVector(datos, "Ordenado\n");

  return 0;
}