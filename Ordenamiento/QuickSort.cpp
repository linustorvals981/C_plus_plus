#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

int particion(vector<int> &arr, int low, int high) {
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (arr[j] <= pivot) {
      i++;
      swap(arr[i], arr[j]);
    }
  }
  swap(arr[i + 1], arr[high]);
  return i + 1;
}

void quickSort(vector<int> &arr, int low, int high) {
  if (low < high) {
    int pi = particion(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

void quickSort(vector<int> &arr) { quickSort(arr, 0, arr.size() - 1); }

void printArray(const vector<int> &arr) {
  for (int x : arr)
    cout << x << " ";
  cout << endl;
}

void randomArray(vector<int> &arr, int size) {

  srand(time(0));

  for (int i = 0; i < size; i++) {
    arr[i] = rand() % 1000 + 1;
  }
}

int main() {
  const int SIZE = 1000000;
  vector<int> data;
  randomArray(data, SIZE);

  // cout << "Datos originales: ";
  // printArray(data);

  auto start = chrono::high_resolution_clock::now();

  quickSort(data);

  auto stop = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

  cout << "QuickSort tomó: " << duration.count() << " milisegundos" << endl;

  // cout << "Datos ordenados:  ";
  // printArray(data);
  return 0;
}
