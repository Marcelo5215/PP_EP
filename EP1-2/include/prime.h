#ifndef H_PRIME
#define H_PRIME

	#include <stdio.h>
	#include <iostream>
	#include <list>
	#include <stdlib.h>
	#include <omp.h>
	#include <limits>
	#include <math.h>
	#include <vector>
	#include <unistd.h>
	#include <sys/time.h>
	#include <time.h>

	using namespace std;

	//declaracao de funcoes
	std::list<long int> getPrimos(int limite, int threads);
	void printList(std::list<long int> lista);
	void printTime();
	void printSum();


#endif