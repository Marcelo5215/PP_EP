#include "prime.h"

double total_time = 0.0;
long int sum = 0;

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
	double inicio, fim;
	//soma dos numeros primos 
	long int i;
	list<long int> primes;

	//sublistas
	std::vector< list<long int>  > sub(threads);

	inicio= omp_get_wtime();

	#pragma omp parallel for schedule(dynamic, 100) private(i) reduction(+:sum)
	for(int num = 2; num <= limite; num++){

		//checar se o numero(num) eh primo
		for(i = 2; i <= sqrt(num); i++){
			if(num % i == 0){
				break;
			}
		} //checa se achou um divisor diferente de 1 ou ele mesmo
		if (i <= sqrt(num)){
			continue;
		}
		else{
			sum = sum + num;
			sub[omp_get_thread_num()].push_back(num);
		}
	}

	primes = sub[0];
	for(i = 1; i < threads; ++i){
		primes.merge(sub[i], compare);
	}

	fim=omp_get_wtime();
	total_time = fim-inicio;

	return primes;
}

void printList(std::list<long int> lista){
	for (std::list<long int>::iterator i = lista.begin(); i != lista.end(); ++i){
		cout << *i << ' ';
	}
	cout << endl;
}

void printTime(){
	cout << total_time << endl;
}

void printSum(){
	cout << sum << endl;
}
