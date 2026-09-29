//
// Created by Ale on 29/9/2026.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include "algoritmos.h"

using namespace std;
using Reloj = chrono::high_resolution_clock;

mt19937 gen(42);   // semilla fija para que los resultados sean reproducibles

// ---------- Benchmark de búsqueda binaria ----------
void benchBusquedaBinaria() {
    ofstream csv("resultados_busqueda_binaria.csv");
    csv << "n,tiempo_ns,comparaciones\n";

    const int BUSQUEDAS = 100000;   // una búsqueda es muy rápida, se repite y se promedia

    for (int k = 10; k <= 23; k++) {
        int n = 1 << k;   // 2^k

        // Arreglo random y luego ORDENADO (la búsqueda binaria lo necesita)
        vector<int> arr(n);
        uniform_int_distribution<int> dist(0, n * 10);
        for (int& x : arr) x = dist(gen);
        sort(arr.begin(), arr.end());

        // Objetivos random (muchos no existen = peor caso)
        vector<int> objetivos(BUSQUEDAS);
        for (int& x : objetivos) x = dist(gen);

        long long comps = 0;
        auto inicio = Reloj::now();
        for (int obj : objetivos) busquedaBinaria(arr, obj, comps);
        auto fin = Reloj::now();

        double ns = chrono::duration<double, nano>(fin - inicio).count() / BUSQUEDAS;
        double compsProm = (double)comps / BUSQUEDAS;

        csv << n << "," << ns << "," << compsProm << "\n";
        cout << "BusqBinaria n=" << n << "  " << ns << " ns  " << compsProm << " comps\n";
    }
}

// ---------- Benchmark de mergesort ----------
void benchMergeSort() {
    ofstream csv("resultados_mergesort.csv");
    csv << "n,tiempo_ms,comparaciones\n";

    const int CORRIDAS = 5;
    vector<int> tamanos = {1000, 2000, 5000, 10000, 20000, 40000, 60000,
                           80000, 100000, 150000, 200000, 300000, 400000};

    for (int n : tamanos) {
        double totalMs = 0;
        double totalComps = 0;

        for (int r = 0; r < CORRIDAS; r++) {
            vector<int> arr(n);
            uniform_int_distribution<int> dist(0, n * 10);
            for (int& x : arr) x = dist(gen);

            long long comps = 0;
            auto inicio = Reloj::now();
            mergeSort(arr, 0, n - 1, comps);
            auto fin = Reloj::now();

            totalMs += chrono::duration<double, milli>(fin - inicio).count();
            totalComps += comps;
        }

        double ms = totalMs / CORRIDAS;
        double compsProm = totalComps / CORRIDAS;

        csv << n << "," << ms << "," << compsProm << "\n";
        cout << "MergeSort n=" << n << "  " << ms << " ms  " << compsProm << " comps\n";
    }
}

int main() {
    benchBusquedaBinaria();
    benchMergeSort();
    cout << "Listo. Se generaron los CSV.\n";
    return 0;
}