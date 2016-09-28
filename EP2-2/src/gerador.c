#include <stdio.h>
#include <stdlib.h>

int main(int argv, char** argc){
  int i, j;
  FILE* fp;
  fp = fopen("test.txt", "w+");

  for(i =0 ; i < atoi(argc[1]) ; i++){
      for(j =0 ; j < atoi(argc[1]) ; j++){
        fprintf(fp, "%d", rand()%atoi(argc[1]));
        if (j < 999) {
          fprintf(fp, " ");
        }
      }
      fprintf(fp, "\n");
  }

  fclose(fp);
  return 0;
}
