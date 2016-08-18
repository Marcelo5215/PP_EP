#ifndef H_PRIME
#define H_PRIME

	#include <stdio.h>
	#include <iostream>
	#include <list>
	#include <stdlib.h>
	#include <omp.h>
	#include <limits>
	#include <vector>

	using namespace std;

	//declaracao de funcoes
	std::list<long int> getPrimos(int limite, int threads, char* op);
	void printList(std::list<long int> lista);


#endif