#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "ocean.h"

using namespace std;

int main(int argv, char** argc){

	if(argv < 5){
		cout << "Usage: ./testEP2 <rows> <cols> <itera_limit> <threads><option> " << endl;
		return -1;
	}

	int rows, cols, interation_limit ,threads;

	rows = atoi(argc[1]);
	cols = atoi(argc[2]);
	interation_limit = atoi(argc[3]);
	threads = atoi(argc[4]);

	int** ocean;

	ocean = oceanSimSERIAL(rows, cols, interation_limit, threads);
	printf("====\n");
	printOcean(ocean, rows, cols);

	freeMAT(ocean, rows, cols);

	return 0;
}
