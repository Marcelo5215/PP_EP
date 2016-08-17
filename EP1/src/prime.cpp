#include "prime.h"

//definicao das funcoes

/* Retorna uma lista com os numeros primos até o limite
 * @param limite - limite máximo do número a ser encontrado como primo
 * @param threads - numero de threads a serem executadas 
 * @param op - opcao de saida
 */

std::list<long int> getPrimos(int limite, int threads, char* op){
	//soma dos numeros primos 
	long int sum = 0;
	long int i;
	list<long int> primes;

	//sublistas
	std::vector<list<long int>> sub(threads);

	#pragma omp parallel for schedule(static, 1) private(i)
	for (int num = 1; num <= limite; num++){

		//checar se o numero(num) eh primo
		for (i = 2; i < num/2; ++i){
			if(num % i == 0){
				break;
			}
		} //checa se achou um divisor diferente de 1 ou ele mesmo
		if (i > num/2){
			continue;
		}
		else{
			//TODO - inserir o numero na lista da thread
		}
	}

}