/*
 * PRIME NUMBERS SEARCHING ALGORITHM
 * Listing prime numbers
 * Ver. 1.1
 *
 * Syntax: ./list [-seq] [-out=off|file|sqlite] <max>
 *
 * Copyleft 2014 Victor Manuel Fernandez Castro - All rights revoked.
 * January 2nd 2014.
 */
 
#include <iostream>
#include "common.h"
#include <cstdlib>
#include <cstring>
#include <vector>
#include <omp.h>
#include <regex>

#define OUTPUT_FILENAME "output.txt"
#define OUTPUT_DATABASE "output.db"

using namespace std;

enum Output { OUTPUT_OFF, OUTPUT_FILE, OUTPUT_SQLITE };

//------------------------------------------------------------------------------

int main(int argc, char **argv) {
	int max = 0;
	Output output = OUTPUT_FILE;
	vector<int> vprimes;
	double time0, time1;
	enum { parallel, sequential} mode = parallel;
	
	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-seq"))
			mode = sequential;
		else if (!strcmp(argv[i], "-out=off"))
			output = OUTPUT_OFF;
		else if (!strcmp(argv[i], "-out=file"))
			output = OUTPUT_FILE;
		else if (!strcmp(argv[i], "-out=sqlite"))
			output = OUTPUT_SQLITE;
		else if (regex_match (argv[i], regex("(-out=)(.*)") )) {
			cerr << "Valor incorrecto para -out." << endl
				 << "Los valores aceptados son sqlite, file y off" << endl;
			exit(-1);
		}
		else if (!strcmp(argv[i], "--help")) {
			cout << "Sintaxis: " << argv[0] << " [-seq] [-out=off|file|sqlite] <max>\n";
			return EXIT_SUCCESS;
		} else
			max = atoi(argv[i]);
	}
	
	while (max < 2) {
		cout << "Maximo: ";
		cin >> max;
	}

	time0 = omp_get_wtime();
	
	if (mode == sequential)
		search_seq(max, vprimes);
	else
		search(max, vprimes);
		
	time1 = omp_get_wtime();
	cout << "Encontrados " << vprimes.size() << " numeros primos.\n";
	cout << "Tiempo: " << time1 - time0 << " seg.\n";

	switch (output) {
	case OUTPUT_FILE:
		time0 = time1;
		save(OUTPUT_FILENAME, vprimes);
		cout << "Tiempo en escribir: " << omp_get_wtime() - time0 << " seg.\n";
		break;
	case OUTPUT_SQLITE:
		time0 = time1;
		insert(OUTPUT_DATABASE, vprimes);
		cout << "Tiempo en escribir: " << omp_get_wtime() - time0 << " seg.\n";
		break;
	case OUTPUT_OFF:
	default:
		;
	}
	
	return EXIT_SUCCESS;
}

