#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include "ocean.h"

int main(int argv, char** argc){
	int process_count, my_rank, *oceanvec, *oceanvec2, rows, cols, interation_limit,
		my_first, my_last, tam, i ,m ,l;
	double start=0, finish=0;	

	if(argv < 5){
		cout << "Usage: mpiexec -n <process_count> ./testEP3 <rows> <cols> <itera_limit> <option> " << endl;
		return -1;
	}

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &process_count);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	start = MPI_Wtime(); 

	rows = atoi(argc[1]);
	cols = atoi(argc[2]);
	interation_limit = atoi(argc[3]);

	oceanvec = getOceanFromFILE("mat.txt", rows, cols);
	oceanvec2=(int*)malloc(sizeof(int)*rows*cols);

	for(i=0; i<interation_limit; i++){
		if (my_rank!=0){
			if(i>0)MPI_Recv(&oceanvec[0], rows*cols, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			oceanvec2=calcStep(my_rank, oceanvec, rows, cols, process_count);
			MPI_Send(&oceanvec2[0], rows*cols, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
		else{
			for(int j=1;j<process_count; j++){
				MPI_Recv(&oceanvec2[0], rows*cols, MPI_INT, j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				tam=(rows*cols)/(process_count-1);
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
					oceanvec[m*cols+l] = oceanvec2[m*cols + l];
				}
			}
			if(i<interation_limit-1){
				for(int j=1; j<process_count; j++){
					MPI_Send(&oceanvec[0], rows*cols, MPI_INT, j, 0, MPI_COMM_WORLD);
				}
			}
		}
	}

	finish = MPI_Wtime(); 

	if(my_rank==0){
		if(strcmp(argc[4], "ocean") == 0){
				printf("====\n");
				printOcean(oceanvec, rows, cols);
		}
		else if(strcmp(argc[4], "time")==0){
				printf("%g miliseconds\n", (finish*1000-start*1000));
		}
		else if (strcmp(argc[4], "all")==0) {
			printf("====\n");
			printOcean(oceanvec, rows, cols);
			printf("====\n");
			printf("%g miliseconds\n", (finish*1000-start*1000));
		}
	}	

	free(oceanvec);
	MPI_Finalize();
	return 0;
}