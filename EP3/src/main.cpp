#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include "ocean.h"

int main(int argv, char** argc){
	int process_count, my_rank, *oceanvec2, rows, cols, interation_limit,
		my_first, my_last, tam, i ,m ,l;
	double start=0, finish=0;	

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
	int* oceanvec = (int*)malloc(sizeof(int) * rows * cols);
	getOceanFromFILE("mat.txt", rows, cols, oceanvec);

	start = MPI_Wtime(); 
	for(i=0; i<interation_limit; i++){
		if (my_rank!=0){
			if(i>0)MPI_Recv(&oceanvec[0], rows*cols, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			oceanvec2=calcStep(my_rank, oceanvec, rows, cols, process_count);
			MPI_Send(&oceanvec2[0], rows*cols, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
		else{
			if(i<interation_limit && i>0){
				for(int j=1; j<process_count; j++){
					MPI_Send(&oceanvec[0], rows*cols, MPI_INT, j, 0, MPI_COMM_WORLD);
				}
			}	
			for(int j=1;j<process_count; j++){
				tam=(rows*cols)/(process_count-1);
				my_first=(tam*(j-1));
				if(j!=process_count-1){
					my_last=(tam*(j+1));
				}
				else{
					my_last=(rows*cols);
				}
				int *oceanvec2 =(int*)malloc(sizeof(int)*(my_last-my_first+1));
				MPI_Recv(&oceanvec2[0], rows*cols, MPI_INT, j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				for (int k = my_first; k < my_last; k++) {
					m=k/cols;
					l=k%cols;
					oceanvec[m*cols+l] = oceanvec2[k-my_first];
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

	MPI_Finalize();
	return 0;
}