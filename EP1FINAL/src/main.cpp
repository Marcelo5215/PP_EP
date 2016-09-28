#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include "prime.h"

using namespace std;

int main(int argv, char** argc){
	int limit, threads; //limit = limite max   threads = num de threads a executar o programa

	if (argv != 4){
		printf("Usage: ./testEp1 <limite> <op> <threads>\n");
		return -1;
	}

	limit = atoi(argc[1]);
	threads = atoi(argc[3]);

	list<long int> primes = getPrimos(limit, threads);

	if(strcmp(argc[2], "list") == 0){
		printList(primes);
	}
	else if(strcmp(argc[2], "time") == 0){
		printTime();
	}else if(strcmp(argc[2], "sum") == 0){
		printSum();
	}
	else if(strcmp(argc[2], "all") == 0){
		printList(primes);
		printSum();
		printTime();
	}
	else{
		printTime();
	}

	return 0;
}
