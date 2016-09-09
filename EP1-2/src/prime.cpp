// Modulo que implementa as funcoes que obtem a lista de primos e o somatorio dos primos e que
// imprime os objetos de interesse do usuario.

#include "prime.h"

double total_time = 0.0;
long int sum = 0;

// Funcao que verifica se um valor eh maior que outro, sera usado para concatenar as listas.
bool compare(long int first, long int second){ 
	return ( first < second ); 
}

// Funcao que obtem a listas de primos e a soma de todos os primos do intervalo.
std::list<long int> getPrimos(int limite, int threads){
	omp_set_num_threads(threads);
	double inicio, fim; // Variaveis para verificacao do tempo de execucao.
	list<long int> primes; // Lista de primos.
	std::vector< list<long int>  > sub(threads); // Vetor que contem as listas de cada thread.
	long int num,raiz,raiz2,i,k;
	std::list<long int>::iterator j;

	raiz=sqrt(limite)+1;

	// Recebe o tempo de inicio de execucao do programa.
	inicio= omp_get_wtime();

	// Primeira secao paralela
	// Obtem todos os primos menores ou iguais a raiz do limite maximo do intervalo.
	#pragma omp parallel for schedule(guided) private(i,j) reduction(+:sum)
	for(num=2;num<=raiz;num++){

		// Loop que verifica se o numero eh multiplo de algum numero menor que a raiz dele.
		for(i = 2; i <= sqrt(num); i++){
			if(num % i == 0){
				break;
			}
		}

		// Adiciona o numero na lista de primos caso ele seja primo e o acrescenta a soma geral.
		if (i > sqrt(num)){
			sum += num;
			j=primes.end();
			# pragma omp critical
			primes.push_back(num);
		}
	}
	// Ordena a lista de primos.
	primes.sort();

	// Segunda secao paralela
	// Computa os demais primos do intervalo em listas individuais de cada thread, nessa secao
	// sao usados apenas os numeros primos menores que a raiz do numero a ser verificado, para
	// isso a lista de primos da primeira secao eh utilizada.
	#pragma omp parallel for schedule(guided) private(j) reduction(+:sum)
	for(num=raiz+1;num<=limite;num++){	
		
		j=primes.begin();
		// Checar se o numero(num) eh primo.
		while(*j <= sqrt(num) && j!=primes.end()){
			if(num % *j == 0){
				break;
			}
			++j;
		} 

		// Checa se achou um divisor diferente de 1 ou ele mesmo e o acrescenta na lista da
		// thread e na soma dos primos.
		if (*j > sqrt(num) || j==primes.end()){
			sum += num;
			sub[omp_get_thread_num()].push_back(num);
		}
	}

	// Concatena as listas de cada thread a lista de primos.	
	for(i = 0; i < threads; ++i){
		primes.merge(sub[i], compare);
	}

	// Recebe o tempo final de execucao e calcula o tempo de execucao.
	fim=omp_get_wtime();
	total_time = fim-inicio;

	return primes;// Retorna a lista de primos.
}

// Funcao que imprime uma lista.
void printList(std::list<long int> lista){
	for (std::list<long int>::iterator i = lista.begin(); i != lista.end(); ++i){
		cout << *i << ' ';
	}
	cout << endl;
}

// Funcao que imprime o tempo de execucao do programa.
void printTime(){
	cout << total_time << endl;
	total_time = 0;
}

// Funcao que imprime a soma dos primos do intervalo.
void printSum(){
	cout << sum << endl;
}
