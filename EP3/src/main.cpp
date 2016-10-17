#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include "ocean.h"

using namespace std;

int main(int argv, char** argc){

	if(argv < 5){
		cout << "Usage: ./testEP2 <rows> <cols> <itera_limit> <process> <option> " << endl;
		return -1;
	}
	int **oceanout, *oceanvec;
	int rows, cols, interation_limit, process_count, my_rank, p;

	oceanout = getOceanFromSTDIN(rows, cols);
	mat2vec(oceanout, rows, cols, oceanvec);

	//MPI STEP

	MPI_Status stat;
	MPI_Datatype matvec;

	MPI_Init(&argv, &argc);
	MPI_Comm_size(MPI_COMM_WORLD, &process_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	rows = atoi(argc[1]);
	cols = atoi(argc[2]);

	interation_limit = atoi(argc[3]);
	process_count = atoi(argc[4]);

	MPI_Type_vector(rows*cols, 1, rows*cols, MPI_INT, &matvec);
	MPI_Type_commit(&matvec);

	for (int i = 0; i < interation_limit; i++) {
		if(my_rank != 0){
				calcStep(my_rank, oceanvec, rows, cols, process_count);
				MPI_Send(oceanvec, rows*cols, matvec, 0, 0, MPI_COMM_WORLD);
		}
		else{
			for (int z = 1; z < process_count; z++) {
				MPI_Recv(oceanvec, rows*cols, matvec, p, 0, MPI_COMM_WORLD, stat);

				int my_first, my_last, tam, j, k;
				long p = (long ) rank;

				tam=(rows*cols)/ranks;
				my_first=(tam*(p-1));
				if(p!=ranks-1){
					my_last=(tam*(p+1));
				}
				else{
					my_last=(ocean.rows*ocean.cols);
				}
				for (int k = my_first; k < my_last; k++) {
					j=k/cols;
					l=k%cols;
					oceanout[j][l] = oceanvec[j*cols + l];
				}

			}
		}

	}




	if(strcmp(argc[5], "ocean") == 0){
			printf("====\n");
			printOcean(oceanout, rows, cols);
	}
	else if(strcmp(argc[5], "time")==0){
			printTime();
	}
	else if (strcmp(argc[5], "all")==0) {
		printf("====\n");
		printOcean(oceanout, rows, cols);
		printTime();
	}

	freeMAT(oceanout, rows, cols);

	return 0;
}
