#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "prime.h"

using namespace std;

int main(int argc, char** argc){
	int limit, threads; //limit = limite max   threads = num de threads a executar o programa
	char* option;       //opcao de mostra

	limit = atoi(argc[1]);
	threads = atoi(argc[3]);

	return 0;
}