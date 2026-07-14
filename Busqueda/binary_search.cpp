#include <algorithm>
#include <ctime>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
int binary_search(vector<T> &arr, int n, int low, int high) {
  int mid = low + (high - low) / 2;

  if (low >= high)
    return -1;

  if (arr[mid] == n)
    return mid;

  if (arr[mid] > n)
    return binary_search(arr, n, low, mid - 1);
  else
    return binary_search(arr, n, mid + 1, high);
}

void random_vector(vector<int> &arr, int n) {
  srand(time(NULL));
  for (int i = 0; i < n; i++) {
    arr[i] = rand() % 100;
  }
}

void print_vector(vector<int> &arr, int n) {
  cout << "[ ";
  for (int i = 0; i < n - 1; i++) {
    cout << arr[i] << ", ";
  }
  cout << arr[n - 1] << " ]\n";
}

int main() {
  const int SIZE = 20;
  vector<int> arr(SIZE); // = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  random_vector(arr, SIZE);
  sort(arr.begin(), arr.end());
  print_vector(arr, SIZE);

  int n;
  cout << "Ingresa numero a buscar: ";
  cin >> n;
  cout << "El elemento " << n << " esta en la posicion ["
       << binary_search(arr, n, 0, arr.size() - 1) << "]\n";

  return 0;
}