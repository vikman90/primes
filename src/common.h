/*
 * PRIME NUMBERS SEARCHING ALGORITHM
 * Common functions
 * Ver. 1.1
 *
 * Copyleft 2014 Victor Manuel Fernandez Castro - All rights revoked.
 * January 2nd 2014.
 */

#ifndef UTIL_H
#define UTIL_H

#include <vector>

// Search all prime numbers lower or equal than "max" and save into "vprimes"
// Parallel version
void search(int max, std::vector<int> &vprimes);

// Search all prime numbers lower or equal than "max" and save into "vprimes"
// Sequential version
void search_seq(int max, std::vector<int> &vprimes);

// Query whether "value" is prime, finding divisors from "vector"
// "vector" must contain all prime numbers lower or equal than sqrt(value), 
// and must be ordered.
bool primeq(int value, const std::vector<int> &vprimes);

// Save a vector into a plain text file called "filename"
void save(const char *filename, const std::vector<int> &v);

// Insert a vector into a Sqlite database called "dbname"
void insert(const char *dbname, const std::vector<int> &v);

#endif

