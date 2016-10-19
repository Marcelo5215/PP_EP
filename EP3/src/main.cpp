#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include "ocean.h"

int main(int argv, char** argc){
	int process_count, my_rank, **oceanout, *oceanvec, *oceanvec2, rows, cols, interation_limit,
		my_first, my_last, tam, i ,m ,l;

	if(argv < 5){
		cout << "Usage: mpiexec -n <process_count> ./testEP3 <rows> <cols> <itera_limit> <option> " << endl;
		return -1;
	}

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &process_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	rows = atoi(argc[1]);
	cols = atoi(argc[2]);
	interation_limit = atoi(argc[3]);

	oceanout = getOceanFromFILE("mat.txt", rows, cols);
	oceanvec = mat2vec(oceanout, rows, cols);
	oceanvec2=(int*)malloc(sizeof(int)*rows*cols);

	for(i=0; i<interation_limit; i++){
		if (my_rank!=0){
			oceanvec2=calcStep(my_rank, oceanvec, rows, cols, process_count-1);
			MPI_Send(&oceanvec2[0], rows*cols, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
		else{
			for(int j=1;j<process_count; j++){
				printOcean(oceanout, rows, cols);
				MPI_Recv(&oceanvec2[0], rows*cols, MPI_INT, j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				tam=(rows*cols)/process_count;
				my_first=(tam*(j-1));
				if(j!=process_count-1){
					my_last=(tam*(j+1));
				}
				else{
					my_last=(rows*cols);
				}
				for (int k = my_first; k < my_last; k++) {
					m=k/cols;
					l=k%cols;
					oceanout[m][l] = oceanvec2[m*cols + l];
				}
			}
		}
		oceanvec=oceanvec2;
	}	

	if(my_rank==0){
		if(strcmp(argc[4], "ocean") == 0){
				printf("====\n");
				printOcean(oceanout, rows, cols);
		}
		else if(strcmp(argc[4], "time")==0){
				printTime();
		}
		else if (strcmp(argc[4], "all")==0) {
			printf("====\n");
			printOcean(oceanout, rows, cols);
			printTime();
		}
	}	

	freeMAT(oceanout, rows, cols);
	free(oceanvec);
	MPI_Finalize();
	return 0;
}