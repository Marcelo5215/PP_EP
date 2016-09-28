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
	#include <pthread.h>
	#include <sys/time.h>
	#include <time.h>

	#define BORDER  -1

	using namespace std;

	//declaracao de funcoes
	int** oceanSimSERIAL(int rows, int cols, int interation_limit);
	int** getOceanFromSTDIN(int rows, int cols);
	int getMaxNeighborValue(int** ocean,int i, int j, int rows, int cols);
	void printOcean(int** ocean, int rows, int cols);
	void copyTo(int** in, int** &out, int rows, int cols);

	//funcoes para a utilizacao de matrizes
	int** newMAT(int rows, int cols);
	void freeMAT(int** mat, int rows, int cols);

	int** oceanSimParallel(int rows, int cols, int interation_limit, int threads_num);
	void *simulationRoutine(int** ocean, int** oceanOUT, int rowStart, int rowDimension, int colStart, int colDimension);

#endif
