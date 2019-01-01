/*
 * SIEVE OF ERATOSTHENES
 * Ver. 1.0
 *
 * Syntax: ./eratosthenes [-nowrite] <max>
 *
 * Copyleft 2014 Victor Manuel Fernandez Castro - All rights revoked.
 * January 10th 2014.
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <list>
#include <omp.h>

#define OUTPUT_FILENAME "output.txt"

using namespace std;

// Computes the sieve of Eratosthenes
void sieve(list<int> &lprimes);

// Save a list into "filename"
void save(const char *filename, const list<int> &lprimes);

//------------------------------------------------------------------------------

int main(int argc, char **argv) {
    int max = 0;
    bool write = true;
    list<int> lprimes;
    double t0, t1;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-nowrite"))
            write = false;
        else if (!strcmp(argv[i], "--help")) {
            cout << "Sintaxis: " << argv[0] << " [-nowrite] <max>\n";
            return EXIT_SUCCESS;
        } else
            max = atoi(argv[i]);
    }

    while (max < 2) {
        cout << "Maximo: ";
        cin >> max;
    }

    for (int i = 2; i <= max; i++)
        lprimes.push_back(i);

    t0 = omp_get_wtime();
    sieve(lprimes);
    t1 = omp_get_wtime();

    cout << "Encontrados " << lprimes.size() << " numeros primos.\n";
    cout << "Tiempo: " << t1 - t0 << " seg.\n";

    if (write) {
        t0 = t1;
        save(OUTPUT_FILENAME, lprimes);
        cout << "Tiempo en escribir: " << omp_get_wtime() - t0 << " seg.\n";
    }

    return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------
// Computes the sieve of Eratosthenes

void sieve(list<int> &lprimes) {
    int last = lprimes.back();
    const int bound = (int)sqrt(last);
    list<int>::iterator iti, itj;

    for (iti = lprimes.begin(); iti != lprimes.end(); ++iti) {
        int cur = *iti;

        if (cur > bound)
            break;

        itj = iti;
        ++itj;

        while (itj != lprimes.end()) {
            if (*itj % cur == 0)
                itj = lprimes.erase(itj);
            else
                ++itj;
        }
    }
}

//------------------------------------------------------------------------------
// Save a list into "filename"

void save(const char *filename, const list<int> &lprimes) {
    ofstream file(filename);

    if (!file) {
        cerr << "Error de apertura del archivo " << filename << endl;
        return;
    }

    for (list<int>::const_iterator it = lprimes.begin(); it != lprimes.end(); ++it)
        file << *it << endl;
}
