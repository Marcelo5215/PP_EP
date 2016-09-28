#include "ocean.h"

using namespace std;

int threads=1;
oc ocean;
double my_time;

int** simulation(int rows, int cols, int interation_limit, int thread_count){
	my_time = 0.0;
	struct timeval start, end;

	long thread;
	pthread_t *thread_handles;

	threads=thread_count;
	ocean.rows=rows;
	ocean.cols=cols;
	ocean.in = getOceanFromFILE("test.txt", rows, cols);
	ocean.out = newMAT(rows,cols);

	gettimeofday(&start, NULL);

	if(threads==1){
		oceanSimSERIAL(interation_limit);
	}
	else{
		thread_handles= (pthread_t*) malloc(threads*sizeof(pthread_t));
		for(int i=0; i<interation_limit; i++){
			for (thread= 0; thread < threads; thread++){
				pthread_create(&thread_handles[thread] ,NULL, oceanSimPARALLEL, (void*) thread);
			}
			for (thread= 0; thread < threads; thread++){
				pthread_join(thread_handles[thread], NULL);
			}
			copyTo(ocean.out, ocean.in, ocean.rows, ocean.cols);
		}
		free (thread_handles);
	}
	freeMAT(ocean.in, ocean.rows, ocean.cols);


	gettimeofday(&end, NULL);

	my_time = ((end.tv_sec*1000000+end.tv_usec) - (start.tv_sec*1000000+start.tv_usec));

	return ocean.out;
}

void oceanSimSERIAL(int interation_limit){
	int outi, outj;

	//TODO --- SIMULAÇÃO
	for (int i = 0; i < interation_limit; i++) {
		outi=0;
		outj=0;
		//percorre a matriz
		for (int k = 0; k < ocean.rows; k++) {
			for (int l = 0; l < ocean.cols; l++) {
				ocean.out[outi][outj] = ( getMaxNeighborValue(ocean.in, k, l, ocean.rows, ocean.cols) - 1);
				outj++;
				if (outj % ocean.cols == 0 && outj != 0){
					outj = 0;
					outi++;
				}
			}
		}
		copyTo(ocean.out, ocean.in, ocean.rows, ocean.cols);
	}
}

void * oceanSimPARALLEL(void* thread){
	int my_first, my_last, tam, i, j;
	long my_thread = (long ) thread;

	tam=(ocean.rows*ocean.cols)/threads;
	my_first=(tam*my_thread);
	if(my_thread!=threads-1){
		my_last=(tam*(my_thread+1));
	}
	else{
		my_last=(ocean.rows*ocean.cols);
	}
	for (int k = my_first; k < my_last; k++) {
		i=k/ocean.cols;
		j=k%ocean.cols;
		ocean.out[i][j] = ( getMaxNeighborValue(ocean.in, i, j, ocean.rows, ocean.cols) - 1);
	}
}

//adquire o maior valor dos vizinhos do elemento na posição (i,j), vizinhança de 8
int getMaxNeighborValue(int** ocean,int i, int j, int rows, int cols){
	int max = -1;

	for (int k = i-1; k <= i+1; k++) {
		if (k < 0 || k >= rows) {
			continue;
		}
		for (int l = j-1; l <= j+1; l++) {
			if (l < 0 || l >= cols ) {
				continue;
			}
			else if(ocean[k][l] > max){
				max = ocean[k][l];
			}
		}
	}

	return max;
}

int** getOceanFromSTDIN(int rows, int cols){
	int num=1, i=0, j=0;
	//aloca uma nova matriz
	static int** ocean = (int**)malloc(sizeof(int*) * rows);

	for (int i = 0; i < rows; i++) {
			ocean[i] = (int*)malloc(sizeof(int) * cols);
	}

	//adquire os valores da entrada padrão
	 while (num && i < (rows)){
			std::cin >> num;
			ocean[i][j] = num;
			j++;
			if (j % cols == 0 && j != 0){
				j = 0;
				i++;
			}
	};


	return ocean;
}

//imprime a matriz na tela
void printOcean(int** ocean, int rows, int cols){

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << ocean[i][j] << " " ;
		}
		cout << endl;
	}

}

void printTime(){
	cout << my_time << endl;
}

void copyTo(int** in, int** &out, int rows, int cols){
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			out[i][j] = in[i][j];
		}
	}
}

int** getOceanFromFILE(char* filename, int rows, int cols){
  int num=1, i=0, j=0;

  FILE* fp = fopen(filename, "r");
  char* string = (char*)malloc(sizeof(char)*cols*4);
	char * pch;

  //aloca uma nova matriz
  static int** ocean = (int**)malloc(sizeof(int*) * rows);

  for (int i = 0; i < rows; i++) {
      ocean[i] = (int*)malloc(sizeof(int) * cols);
  }

  //adquire os valores do arquivo
	while (fscanf(fp, "%[^\n]", string) > 0) {
		j = 0;
		pch = strtok (string," ,.-");
		while (pch != NULL)
		{
			num = atoi(pch);
			ocean[i][j] = num;
			j++;
			pch = strtok (NULL, " ,.-");
		}
		i++;
	}

  free(string);

  return ocean;
}

/*==========================================*
FUNÇÕES PARA MANIPULAR MATRIZES
 *==========================================*/

//aloca uma nova Matriz vazia
int** newMAT(int rows, int cols){
	static int** mat = (int**)malloc(sizeof(int*) * rows);

	for (int i = 0; i < rows; i++) {
			mat[i] = (int*)malloc(sizeof(int) * cols);
	}

	return mat;
}

//desaloca a matriz
void freeMAT(int** mat, int rows, int cols){
	for (size_t i = 0; i < rows; i++) {
		free(mat[i]);
	}
	free(mat);
}
