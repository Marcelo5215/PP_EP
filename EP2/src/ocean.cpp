
#include "ocean.h"

using namespace std;

vector< vector<int> > oceanSimSERIAL(int rows, int cols, int interation_limit, int threads){
  vector< vector<int> > ocean;
  vector< vector<int> > oceanOUT(rows);
  int outi=0, outj=0;

  // adquire a matriz pelo
  ocean = getOceanFromSTDIN(rows, cols);


  //TODO --- SIMULAÇÃO
  for (int i = 0; i < interation_limit; i++) {
    outi=0;
    outj=0;
    //percorre a matriz
    for (int k = 0; k < rows; k++) {
      for (int l = 0; l < cols; l++) {
        oceanOUT[outi].push_back( getMaxNeighborValue(ocean, k, l, rows, cols) - 1);
        outj++;
        if (outj % cols == 0 && outj != 0){
          outj = 0;
          outi++;
        }
      }
    }
    printf("++++\n");
    printOcean(ocean, rows, cols);
  }

  return oceanOUT;
}

//adquire o maior valor dos vizinhos do elemento na posição (i,j), vizinhança de 8
int getMaxNeighborValue(vector< vector<int> > ocean,int i, int j, int rows, int cols){
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

vector< vector<int> > getOceanFromSTDIN(int rows, int cols){
  int num=1, i=0, j=0;
  vector< vector<int> > ocean(rows);

  //adquire os valores da entrada padrão
   while (num && i < (rows)){
      std::cin >> num;
      ocean[i].push_back(num);
      j++;
      if (j % cols == 0 && j != 0){
        j = 0;
        i++;
      }
  };


  return ocean;
}

//imprime a matriz na tela
void printOcean(vector<vector<int> > ocean, int rows, int cols){

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << ocean[i][j] << " " ;
    }
    cout << endl;
  }

}

// void copyMakeBorder(vector< vector<int> > ocean, int rows, int cols){
//   vector< vector<int> > AUX(rows + 2);
//
//   for (int i = 0; i < cols+2; i++) {
//     AUX[0].push_back(BORDER);
//     AUX[rows + 1].push_back(BORDER);
//   }
//
//   for (int i = 1; i < rows+1; i++) {
//     for (int j = 0; j < cols+2; j++) {
//       if (j == 0 || j == cols+1) {
//         AUX[i].push_back(BORDER);
//       }
//       else{
//         AUX[i][j] = ocean[i-1][j-1];
//       }
//     }
//   }
//
//   ocean = AUX;
//
// }
