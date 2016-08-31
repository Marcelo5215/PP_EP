#include "prime.h"

double total_time = 0.0;
long int sum = 0;

//funcoes encapsuladas
bool compare(long int first, long int second){ 
	return ( first < second ); 
}

std::list<long int> getPrimos(int limite, int threads){
	omp_set_num_threads(threads);
	double inicio, fim;
	list<long int> primes;
	std::vector< list<long int>  > sub(threads);
	long int num,raiz,raiz2,i,k;
	std::list<long int>::iterator j;

	raiz=sqrt(limite)+1;

	inicio= omp_get_wtime();

	#pragma omp parallel for schedule(dynamic,100) private(i,j) reduction(+:sum)
	for(num=2;num<=raiz;num++){

		//garante que a lista contenha pelo menos os primos menores ou iguais a raiz do limite
		for(i = 2; i <= sqrt(num); i++){
			if(num % i == 0){
				break;
			}
		}
		if (i > sqrt(num)){
			sum += num;
			j=primes.end();
			# pragma omp critical
			primes.push_back(num);
		}
	}
	primes.sort();
	//computa os primos restantes
	#pragma omp parallel for schedule(dynamic,100) private(j) reduction(+:sum)
	for(num=raiz+1;num<=limite;num++){	
		//checar se o numero(num) eh primo
		j=primes.begin();
		while(*j <= sqrt(num) && j!=primes.end()){
			if(num % *j == 0){
				break;
			}
			++j;
		} //checa se achou um divisor diferente de 1 ou ele mesmo
		if (*j > sqrt(num) || j==primes.end()){
			sum += num;
			sub[omp_get_thread_num()].push_back(num);
		}
	}	
	for(i = 0; i < threads; ++i){
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
