#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <vector>
using namespace std;

// ---------------- Búsqueda binaria: O(log n) ----------------
// Requiere arreglo ORDENADO. Retorna el índice o -1 si no está.
// 'comps' acumula el número de comparaciones realizadas.
int busquedaBinaria(const vector<int>& arr, int objetivo, long long& comps) {
    int lo = 0, hi = (int)arr.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;   // evita overflow
        comps++;
        if (arr[mid] == objetivo) return mid;
        if (arr[mid] < objetivo) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

// ---------------- Mergesort: O(n log n) ----------------
// Mezcla arr[inicio..medio] y arr[medio+1..fin], que ya están ordenados.
void merge(vector<int>& arr, int inicio, int medio, int fin, long long& comps) {
    vector<int> izq(arr.begin() + inicio, arr.begin() + medio + 1);
    vector<int> der(arr.begin() + medio + 1, arr.begin() + fin + 1);

    size_t i = 0, j = 0;
    int k = inicio;

    while (i < izq.size() && j < der.size()) {
        comps++;
        if (izq[i] <= der[j]) arr[k++] = izq[i++];
        else                  arr[k++] = der[j++];
    }
    while (i < izq.size()) arr[k++] = izq[i++];   // sobrantes de la izquierda
    while (j < der.size()) arr[k++] = der[j++];   // sobrantes de la derecha
}

void mergeSort(vector<int>& arr, int inicio, int fin, long long& comps) {
    if (inicio >= fin) return;                    // caso base
    int medio = inicio + (fin - inicio) / 2;
    mergeSort(arr, inicio, medio, comps);
    mergeSort(arr, medio + 1, fin, comps);
    merge(arr, inicio, medio, fin, comps);
}

#endif
