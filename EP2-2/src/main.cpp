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

	int** oceanout;
	int rows, cols, interation_limit, thread_count;

	rows = atoi(argc[1]);
	cols = atoi(argc[2]);
	interation_limit = atoi(argc[3]);
	thread_count = atoi(argc[4]);

	oceanout = simulation(rows, cols, interation_limit, thread_count);
	
	printf("====\n");
	printOcean(oceanout, rows, cols);

	freeMAT(oceanout, rows, cols);

	return 0;
}