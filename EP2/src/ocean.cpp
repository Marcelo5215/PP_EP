
#include "ocean.h"

using namespace std;

int MAT_ROWS, MAT_COLS;

int** oceanSimSERIAL(int rows, int cols, int interation_limit){
  int** ocean;
  static int** oceanOUT = newMAT(rows, cols);
  int outi=0, outj=0;

  // adquire a matriz pelo
  ocean = getOceanFromSTDIN(rows, cols);


  //--- SIMULAÇÃO
  for (int i = 0; i < interation_limit; i++) {
    outi=0;
    outj=0;
    //percorre a matriz
    for (int k = 0; k < rows; k++) {
      for (int l = 0; l < cols; l++) {
        oceanOUT[outi][outj] = ( getMaxNeighborValue(ocean, k, l, rows, cols) - 1);
        outj++;
        if (outj % cols == 0 && outj != 0){
          outj = 0;
          outi++;
        }
      }
    }
    copyTo(oceanOUT, ocean, rows, cols);

  }

  freeMAT(ocean, rows, cols);

  return oceanOUT;
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

  if(max <= 0){
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

int** getOceanFromFILE(char* filename, int rows, int cols){
  int num=1, i=0, j=0;

  FILE* fp = fopen(filename, "r");
  char* string = (char*)malloc(sizeof(char)*cols*2);

  //aloca uma nova matriz
  static int** ocean = (int**)malloc(sizeof(int*) * rows);

  for (int i = 0; i < rows; i++) {
      ocean[i] = (int*)malloc(sizeof(int) * cols);
  }

  //adquire os valores do arquivo
  //TODO

  free(string);

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

void copyTo(int** in, int** &out, int rows, int cols){
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      out[i][j] = in[i][j];
    }
  }
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

// void copyMakeBorder(int** ocean, int rows, int cols){
//   int** AUX(rows + 2);
//
//   for (int i = 0; i < cols+2; i++) {
//     AUX[0].[j](BORDER);
//     AUX[rows + 1].[j](BORDER);
//   }
//
//   for (int i = 1; i < rows+1; i++) {
//     for (int j = 0; j < cols+2; j++) {
//       if (j == 0 || j == cols+1) {
//         AUX[i].[j](BORDER);
//       }
//       else{
//         AUX[i][j] = ocean[i-1][j-1];
//       }
//     }
//   }
//
//   ocean = AUX;
// }

/*==========================================*
 FUNCOES USANDO Pthreads
 *==========================================*/

int** oceanSimParallel(int rows, int cols, int interation_limit, int threads_num){

  MAT_ROWS = rows;
  MAT_COLS = cols;
  int** ocean;
  static int** oceanOUT = newMAT(rows, cols);
  int rowDimension, colDimension, rowStart=0 ,colStart=0;
  //threads
  pthread_t threads[threads_num];

  // adquire a matriz pelo
  ocean = getOceanFromSTDIN(rows, cols);

  //Divisao do  trabalho
  if(threads_num <= rows){
    rowDimension = rows/threads_num;
    colDimension = 0;
  }
  else{
    rowDimension = rows/threads_num/2;
    colDimension = cols/threads_num/2;
  }

  long i = 0;

    for (int row = rowStart; rows < rows; rows+=rowDimension) {
      for (int col = colStart; col < cols; cols+=colDimension) {
          pthread_create(&threads[i], NULL,
                        simulationRoutine/*( ocean, oceanOUT, row, rowDimension, col,  colDimension)*/,
                        /*ARGS*/(void*)i);
          i++;
      }
    }

  for (int i = 0; i < threads_num; i++) {
    pthread_join(threads[i], NULL);
  }

  return oceanOUT;
}

void *simulationRoutine(int** ocean, int** oceanOUT, int rowStart, int rowDimension, int colStart, int colDimension){

  for (int i = rowStart; i < rowStart + rowDimension; i++) {
    for (int j = colStart; j < colStart + colDimension; j++) {
      oceanOUT[i][j] = ( getMaxNeighborValue(ocean, i, j, MAT_ROWS, MAT_COLS) - 1);
    }
  }
}
