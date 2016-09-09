// Recebe os parametros do programa e chama as funcoes necessarias.

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string.h>
#include "prime.h"

using namespace std;

int main(int argv, char** argc){
	int limit, threads; // limit = limite maximo; threads = numero de threads a executar o programa.

	if (argv != 4){
		printf("Usage: ./testEp1 <limite> <op> <threads>\n");
		return -1;
	}

	limit = atoi(argc[1]);
	threads = atoi(argc[3]);

	// Chama a funcao que retorna a lista de primos do intervalo desejado.
	list<long int> primes = getPrimos(limit, threads);

	// Compara os parametros recebidos e executa as funcoes adequadas:
	// "list" imprime a lista na tela;
	// "time" imprime o tempo de execução na tela;
	// "sum" imprime a soma de todos os primos da lista;
	// "all" imprime todos os valores anteriores.
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
	return 0;
}