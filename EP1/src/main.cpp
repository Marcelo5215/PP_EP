#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "prime.h"

using namespace std;

int main(int argv, char** argc){
	int limit, threads; //limit = limite max   threads = num de threads a executar o programa
	char* option;       //opcao de mostra

	limit = atoi(argc[1]);
	threads = atoi(argc[3]);

	list<long int> primes = getPrimos(limit, threads, option);

	printList(primes);

	return 0;
}