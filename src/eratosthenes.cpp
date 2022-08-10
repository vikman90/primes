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
#include <omp.h>

#define OUTPUT_FILENAME "output.txt"

using namespace std;

// Sieve of Eratosthenes
class Eratosthenes {
public:
    // Constructor
    Eratosthenes(size_t size) : size(size) {
        numbers = (bool *)malloc(sizeof(bool) * (size + 1));
        memset(numbers, true, sizeof(bool) * (size + 1));
    }

    // Destructor
    ~Eratosthenes() {
        free(numbers);
    }

    // Compute the sieve of Eratosthenes
    void find_primes() {
        const unsigned bound = (int)sqrt(size);

        for (unsigned i = 2; i <= bound; i++) {
            if (numbers[i]) {
                for (unsigned j = i * i; j <= size; j += i) {
                    numbers[j] = false;
                }
            }
        }
    }

    // Print a list into stdout
    friend ostream& operator << (ostream &, const Eratosthenes &);

private:
    size_t size;
    bool * numbers;
};

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

    Eratosthenes primes(max);

    t0 = omp_get_wtime();
    primes.find_primes();
    t1 = omp_get_wtime();

    cerr << "Time: " << (t1 - t0) * 1000 << " ms.\n";

    t0 = t1;
    cout << primes;
    cerr << "Time to write: " << (omp_get_wtime() - t0) * 1000 << " ms.\n";

    return EXIT_SUCCESS;
}

//------------------------------------------------------------------------------
// Print a list into stdout

ostream& operator << (ostream &os, const Eratosthenes &primes) {
    for (unsigned i = 2; i < primes.size; i++) {
        if (primes.numbers[i]) {
            os << i << endl;
        }
    }

    return os;
}
