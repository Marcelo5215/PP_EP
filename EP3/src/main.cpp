#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include "ocean.h"

int main(int argv, char** argc){
	int process_count, my_rank, *oceanvec2, *oceanvec, rows, cols, interation_limit,
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
	oceanvec = (int*)malloc(sizeof(int) * rows * cols);
	oceanvec2 = (int*)malloc(sizeof(int) * (rows * cols)/(process_count-1));
	if(my_rank==0)getOceanFromFILE("test.txt", rows, cols, oceanvec);


	//calculo do tempo
	start = MPI_Wtime();

	// iteracoes
	for(i=0; i<interation_limit; i++){

		//caso nao seja o processo principal, realize a simulacao
		if (my_rank!=0){
			//adquiri a matriz para comecar a simulacao do processo 0(principal)
			MPI_Recv(&oceanvec[0], rows*cols, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			//simulacao
			calcStep(my_rank, oceanvec, rows, cols, process_count, oceanvec2);

			//envia a simulacao feita (apenas a parte modificada) para o processo 0(principal)
			if(my_rank==process_count-1){
				MPI_Send(&oceanvec2[0], (rows*cols)-(my_rank-1)*(rows*cols)/(my_rank), MPI_INT, 0, 0, MPI_COMM_WORLD);
			}
			else{
				MPI_Send(&oceanvec2[0], (rows*cols)/(process_count-1), MPI_INT, 0, 0, MPI_COMM_WORLD);
			}
		}
		else{
			//manda a matriz para os processos realizarem a simulacao	
			if(i==0){
				for(int k=1; k<process_count; k++){
					MPI_Send(&oceanvec[0], rows*cols, MPI_INT, k, 0, MPI_COMM_WORLD);
				}
			}

			//para cada um dos outros processos o resultado e obtido e inserindo o resultado em 
			//seu respectivo lugar no resultado final	
			for(int j=1;j<process_count; j++){

				//calculo dos limites do respectivo resultado
				tam=(rows*cols)/(process_count-1);
				my_first=(tam*(j-1));

				//recebe o resultado, e limita o ultimo
				if(j!=process_count-1){
					my_last=(tam*(j));
					oceanvec2 =(int*)realloc(oceanvec2,sizeof(int)*(my_last-my_first+1));
					MPI_Recv(&oceanvec2[0], tam, MPI_INT, j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				}
				else{
					my_last=(rows*cols);
					oceanvec2 =(int*)realloc(oceanvec2,sizeof(int)*(my_last-my_first));
					MPI_Recv(&oceanvec2[0], (rows*cols)-(tam*(process_count-2)), MPI_INT, j, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				}

				//passa o para o resultado final
				for (int k = my_first; k < my_last; k++) {
					oceanvec[k] = oceanvec2[k-my_first];
				}
			}
			//caso ainda haja iteracoes a ser feitas, o resultado final e enviaddo novamente aos processos
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
		free(oceanvec);
		free(oceanvec2);
	}

	MPI_Finalize();
	return 0;
}