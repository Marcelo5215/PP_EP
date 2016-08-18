#include "prime.h"

//funcoes encapsuladas
bool compare(long int first, long int second){ 
	return ( first < second ); 
}

//definicao das funcoes

/* Retorna uma lista com os numeros primos até o limite
 * @param limite - limite máximo do número a ser encontrado como primo
 * @param threads - numero de threads a serem executadas 
 * @param op - opcao de saida
 */

std::list<long int> getPrimos(int limite, int threads, char* op){
	omp_set_num_threads(threads);
	//soma dos numeros primos 
	long int sum = 0;
	long int i;
	list<long int> primes;

	//sublistas
	std::vector< list<long int>  > sub(threads);

	#pragma omp parallel for schedule(static, 1) private(i)
	for(int num = 3; num <= limite; num++){
		if (num % 2 == 0){
			continue;
		}

		//checar se o numero(num) eh primo
		for(i = 3; i < num/2+1; i++){
			if(num % i == 0){
				break;
			}
		} //checa se achou um divisor diferente de 1 ou ele mesmo
		if (i < num/2){
			continue;
		}
		else{
			//TODO - inserir o numero na lista da thread
			sub[omp_get_thread_num()].push_back(num);
		}
	}

	primes = sub[0];
	for(i = 1; i < threads; ++i){
		primes.merge(sub[i], compare);
	}

	return primes;
}

void printList(std::list<long int> lista){
	for (std::list<long int>::iterator i = lista.begin(); i != lista.end(); ++i){
		cout << ' ' << *i;
	}
	cout << endl;
}
