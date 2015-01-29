/*
 * PRIME NUMBERS SEARCHING ALGORITHM
 * Querying whether a number is prime
 * Ver. 1.0
 *
 * Syntax: ./list [-seq] <number>
 *
 * Copyleft 2014 Victor Manuel Fernandez Castro - All rights revoked.
 * January 2nd 2014.
 */

#include <iostream>
#include "common.h"
#include <cstdlib>
#include <cstring>
#include <vector>
#include <cmath>
#include <omp.h>

using namespace std;

//------------------------------------------------------------------------------

int main(int argc, char **argv) {
	int req, max;
	bool ans;
	vector<int> vprimes;
	double time0, time1;
	enum { parallel, sequential} mode = parallel;

	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-seq"))
			mode = sequential;
		else if (!strcmp(argv[i], "--help")) {
			cout << "Sintaxis: " << argv[0] << " [-seq] <numero>\n";
			return EXIT_SUCCESS;
		} else
			req = atoi(argv[i]);
	}
	
	while (req < 2) {
		cout << "Numero: ";
		cin >> req;
	}

	max = (int)sqrt(req);
	time0 = omp_get_wtime();
	
	if (mode == sequential)
		search_seq(max, vprimes);
	else
		search(max, vprimes);
		
	ans = primeq(req, vprimes);
	time1 = omp_get_wtime();

	if (ans)
		cout << "Primo.\n";
	else
		cout << "Divisible\n";
		
	cout << "Tiempo: " << time1 - time0 << " seg.\n";
	
	return EXIT_SUCCESS;
}

