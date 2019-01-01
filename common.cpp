/*
 * PRIME NUMBERS SEARCHING ALGORITHM
 * Common functions
 * Ver. 1.2
 *
 * Copyleft 2014 Victor Manuel Fernandez Castro - All rights revoked.
 * January 2nd 2014.
 */

#include <omp.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <sqlite3.h>
#include "common.h"

using namespace std;

#define PARALLEL_MIN 10

static const char SQL_INSERT_TABLE[] = "CREATE TABLE primes (value INTEGER NOT NULL PRIMARY KEY);";
static const char SQL_DROP_TABLE[] = "DROP TABLE IF EXISTS primes;";

//------------------------------------------------------------------------------
// Search all prime numbers lower or equal than "max" and save into "vprimes"
// Parallel version

void search(int max, vector<int> &vprimes) {
    int i, last, bound, thmax;
    int thid, j;
    vector<int> *vpartial;

    thmax = omp_get_max_threads();
    vpartial = new vector<int>[thmax];

    // First searching iteration, sequential

    for (i = 2; i <= max && i <= PARALLEL_MIN; i++) {
        if (primeq(i, vprimes)) {
            vprimes.push_back(i);
            last = i;
        }
    }

    while (i <= max) {

        // Searching bound in this iteration
        last = vprimes.back();
        bound = (last < sqrt(max)) ? last * last : max;

#pragma omp parallel private (thid, j)
        {
            thid = omp_get_thread_num();

#pragma omp for
            for (j = i; j <= bound; j++) {
                if (primeq(j, vprimes)) {
                    vpartial[thid].push_back(j);
                }
            }
        }

        // Insert values into "vprimes", leaving it ordered

        for (j = 0; j < thmax; j++) {
            for (vector<int>::iterator it = vpartial[j].begin(); it != vpartial[j].end(); ++it)
                vprimes.push_back(*it);

            vpartial[j].clear();
        }

        i = bound + 1;
    }

    delete[] vpartial;
}

//------------------------------------------------------------------------------
// Search all prime numbers lower or equal than "max" and save into "vprimes"
// Sequential version

void search_seq(int max, vector<int> &vprimes) {
    int i;

    for (i = 2; i < max; i++)
        if (primeq(i, vprimes))
            vprimes.push_back(i);
}

//------------------------------------------------------------------------------
// Query whether "value" is prime, finding divisors from "vector"

bool primeq(int value, const vector<int> &vprimes) {
    double bound = sqrt(value);

    for (vector<int>::const_iterator it = vprimes.begin(); it != vprimes.end(); ++it) {
        if (*it > bound)
            return true;

        if (value % *it == 0)
            return false;
    }

    return true;
}

//------------------------------------------------------------------------------
// Save a vector into a plain text file called "filename"

void save(const char *filename, const vector<int> &v) {
    ofstream file(filename);

    if (!file) {
        cerr << "Error de apertura del archivo " << filename << endl;
        return;
    }

    for (vector<int>::const_iterator it = v.begin(); it != v.end(); ++it)
        file << *it << endl;

    file.close();
}

//------------------------------------------------------------------------------
// Insert a vector into a Sqlite database called "dbname"

void insert(const char *dbname, const std::vector<int> &v) {
    int result, max, i, parc = 0, perc = 0, last = -1;
    const int size = v.size();
    char *errmsg;
    sqlite3 *db;
    vector<int>::const_iterator it = v.begin();

    if (sqlite3_open(dbname, &db) != SQLITE_OK) {
        cerr << "sqlite3_open(): " << sqlite3_errmsg(db) << endl;
        return;
    }

    max = sqlite3_limit(db, SQLITE_LIMIT_COMPOUND_SELECT, -1);
    result = sqlite3_exec(db, SQL_DROP_TABLE, 0, 0, &errmsg);

    if (result != SQLITE_OK) {
        cerr << "sqlite3_exec(): " << errmsg << endl;
        sqlite3_free(errmsg);
        return;
    }

    result = sqlite3_exec(db, SQL_INSERT_TABLE, 0, 0, &errmsg);

    if (result != SQLITE_OK) {
        cerr << "sqlite3_exec(): " << errmsg << endl;
        sqlite3_free(errmsg);
        return;
    }

    result = sqlite3_exec(db, "BEGIN;", 0, 0, &errmsg);

    if (result != SQLITE_OK) {
        cerr << "sqlite3_exec(): " << errmsg << endl;
        sqlite3_free(errmsg);
        return;
    }

    while (it != v.end()) {
        ostringstream stream;
        stream << "INSERT INTO primes VALUES (" << *it << ")";
        ++it;

        for (i = 1; i < max && it != v.end(); i++) {
            stream << ", (" << *it << ")";
            ++it;
        }

        stream << ";";
        result = sqlite3_exec(db, stream.str().c_str(), 0, 0, &errmsg);

        if (result != SQLITE_OK) {
            cerr << "sqlite3_exec(): " << errmsg << endl;
            sqlite3_free(errmsg);
            return;
        }

        parc += i;
        perc = (int)((double)parc / size * 100);

        if (perc > last) {
            last = perc;
            cout << "\rInsertando... " << perc << "%";
            cout.flush();
        }
    }

    result = sqlite3_exec(db, "COMMIT;", 0, 0, &errmsg);

    if (result != SQLITE_OK) {
        cerr << "sqlite3_exec(): " << errmsg << endl;
        sqlite3_free(errmsg);
        return;
    }

    cout << "\r";
    sqlite3_close(db);
}
