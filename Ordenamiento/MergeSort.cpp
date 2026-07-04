
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
void merge(vector<T> &vect, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  vector<T> L(n1);
  vector<T> R(n2);

  for (int i = 0; i < n1; i++)
    L[i] = vect[left + i];
  for (int j = 0; j < n2; j++)
    R[j] = vect[mid + 1 + j];

  int i = 0, j = 0, k = left;

  while (i < n1 && j < n2) {
    if (L[i] < R[j]) {
      vect[k] = L[i];
      i++;
    } else {
      vect[k] = R[j];
      j++;
    }
    k++;
  }

  while (i < n1) {
    vect[k] = L[i];
    i++;
    k++;
  }

  while (j < n2) {
    vect[k] = R[j];
    j++;
    k++;
  }
}

template <typename T> void mergeSort(vector<T> &vect) {
  int n = vect.size();
  if (n < 2)
    return;

  for (int t_actual = 1; t_actual < n; t_actual *= 2) {
    for (int i = 0; i < n - 1; i += t_actual * 2) {
      int mid = min(i + t_actual - 1, n - 1);
      int right = min(i + 2 * t_actual - 1, n - 1);
      if (mid < right) {
        merge(vect, i, mid, right);
      }
    }
  }
}

template <typename T> void print(vector<T> vect, string name) {
  cout << name << ":\n[ ";
  for (int i = 0; i < vect.size() - 1; i++) {
    cout << vect[i] << ", ";
  }
  cout << vect[vect.size() - 1] << "]\n";
}

int main() {
  vector<int> datos = {50, 23, 3, 5, 1, 4, 8, 2, 10, 12};
  /*const int MAX_SIZE = 10;
  vector<int> datos(MAX_SIZE);
  srand(time(0));
  for (int i = 0; i < MAX_SIZE; i++) {
    datos[i] = rand() % 100;
  }*/

  print(datos, "Original");
  mergeSort(datos);
  print(datos, "Ordenado");
  return 0;
}