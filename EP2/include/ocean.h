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

	#define BORDER  0//0x70000

	using namespace std;

	//declaracao de funcoes
	std::vector<std::vector<int> > oceanSimSERIAL(int rows, int cols, int interation_limit, int threads);
	std::vector<std::vector<int> > getOceanFromSTDIN(int rows, int cols);
	int getMaxNeighborValue(vector< vector<int> > ocean,int i, int j, int rows, int cols);
	void printOcean(vector<vector<int> > ocean, int rows, int cols);

#endif
