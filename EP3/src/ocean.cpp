#include "ocean.h"

using namespace std;

int* calcStep(int my_rank, int* ocean, int rows,int cols, int ranks){
	int my_first, my_last, tam, i, j, *oceanaux=(int*)malloc(sizeof(int)*rows*cols);

	tam=(rows*cols)/(ranks-1);
	my_first=(tam*(my_rank-1));
	if(my_rank!=ranks-1){
		my_last=(tam*(my_rank)-1);
	}
	else{
		my_last=(rows*cols)-1;
	}
	for (int k = my_first; k <= my_last; k++) {
		i=k/cols;
		j=k%cols;
		oceanaux[k] = ( getMaxNeighborValue(ocean , i, j, rows, cols) - 1);
	}

	return oceanaux;
}


//adquire o maior valor dos vizinhos do elemento na posição (i,j), vizinhança de 8
int getMaxNeighborValue(int* ocean,int i, int j, int rows, int cols){
	int max = -1;

	for (int k = i-1; k <= i+1; k++) {
		if (k > 0 && k < rows) {
			for (int l = j-1; l <= j+1; l++) {
				if (l > 0 && l < cols ) {
					if(ocean[k*cols + l] > max){
						max = ocean[k*cols + l];
					}
				}	
			}
		}	
	}
	if (max < 1) {
		return 1;
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
void printOcean(int* ocean, int rows, int cols){

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << ocean[i*cols +j] << " " ;
		}
		cout << endl;
	}

}

/*void printTime(){
	cout << "Tempo nao implementado" << endl;
	//cout << my_time << endl;
}
*/
void copyTo(int** in, int** &out, int rows, int cols){
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			out[i][j] = in[i][j];
		}
	}
}

int* getOceanFromFILE(char* filename, int rows, int cols){

  int num=1, i=0, j=0;

  FILE* fp = fopen(filename, "r");
  char* string = (char*)malloc(sizeof(char)*cols*4);
	char * pch;

  //aloca uma nova matriz
  static int* ocean = (int*)malloc(sizeof(int) * rows * cols);

  //adquire os valores do arquivo
	while (fscanf(fp, "%[^\n]", string) > 0) {
		j = 0;
		pch = strtok (string," ,.-");
		while (pch != NULL)
		{
			num = atoi(pch);
			ocean[i*cols+j] = num;
			j++;
			pch = strtok (NULL, " ,.-");
		}
		i++;
		fgetc(fp);
	}

  free(string);
	fclose(fp);

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

int* mat2vec(int** mat, int rows, int cols){
	int *vout = (int*)malloc(sizeof(int)*rows*cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			vout[i*cols+j] = mat[i][j];
		}
	}
	return vout;
}

void vec2mat(int* vin, int rows, int cols, int** mat){
	mat = (int**)malloc(sizeof(int*)*rows);
	for (int i = 0; i < rows; i++) {
		mat[i] = (int*)malloc(sizeof(int)*cols);
		for (int j = 0; j < cols; j++) {
			mat[i][j] = vin[i*cols+j];
		}
	}
}

//desaloca a matriz
void freeMAT(int** mat, int rows, int cols){
	for (size_t i = 0; i < rows; i++) {
		free(mat[i]);
	}
	free(mat);
}