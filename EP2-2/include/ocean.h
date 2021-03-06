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
	#include <string.h>
	#include <unistd.h>
	#include <sys/time.h>
	#include <time.h>
	#include <pthread.h>

	#define BORDER  0//0x70000

	using namespace std;

	typedef struct {
		int** in;
		int** out;
		int rows;
		int cols;
	} oc;

	//declaracao de funcoes
	int** simulation(int rows, int cols, int interation_limit, int thread_count);
	void oceanSimSERIAL(int interation_limit);
	void * oceanSimPARALLEL(void* thread);
	int** getOceanFromSTDIN(int rows, int cols);
	int getMaxNeighborValue(int** ocean,int i, int j, int rows, int cols);
	void printOcean(int** ocean, int rows, int cols);
	void printTime();
	void copyTo(int** in, int** &out, int rows, int cols);
	int** getOceanFromFILE(char* filename, int rows, int cols);


	int** newMAT(int rows, int cols);
	void freeMAT(int** mat, int rows, int cols);

#endif
