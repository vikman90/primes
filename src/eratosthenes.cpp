/*
 * SIEVE OF ERATOSTHENES
 * Ver. 1.1
 *
 * Syntax: ./eratosthenes [-nowrite] <max>
 *
 * Copyleft 2014 Victor Manuel Fernandez Castro - All rights revoked.
 * January 10th 2014.
 */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <vector>
#include <omp.h>

#define OUTPUT_FILENAME "output.txt"

using namespace std;

// Computes the sieve of Eratosthenes
void sieve(vector<bool> &primes);

// Print a list into stdout
void print(const vector<bool> &primes);

//------------------------------------------------------------------------------

int main(int argc, char **argv) {
    int max = 0;
    bool write = true;
    double t0, t1;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--help")) {
            cout << "Syntax: " << argv[0] << " [MAX]\n";
            return EXIT_SUCCESS;
        } else {
            max = atoi(argv[i]);
        }
    }

    while (max < 2) {
        cout << "Enter max number: ";
        cin >> max;
    }

    vector<bool> primes(max + 1, true);

    t0 = omp_get_wtime();
    sieve(primes);
    t1 = omp_get_wtime();

    cerr << "Time: " << (t1 - t0) * 1000 << " ms.\n";

    t0 = t1;
    print(primes);
    cerr << "Time to write: " << (omp_get_wtime() - t0) * 1000 << " ms.\n";

    return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------
// Computes the sieve of Eratosthenes

void sieve(vector<bool> &primes) {
    const unsigned size = primes.size() - 1;
    const unsigned bound = (int)sqrt(size);

    for (unsigned i = 2; i <= bound; i++) {
        if (primes[i]) {
            for (unsigned j = i * i; j <= size; j += i) {
                primes[j] = false;
            }
        }
    }
}

//------------------------------------------------------------------------------
// Print a list into stdout

void print(const vector<bool> &primes) {
    for (unsigned i = 2; i < primes.size(); i++) {
        if (primes[i]) {
            cout << i << endl;
        }
    }
}
