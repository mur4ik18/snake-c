#include <stdio.h>
void map_generation(const int COLLUMNS, const int ROWS){
  printf("\e[?25l");

  printf(":");
  for (size_t i =0; i<COLLUMNS; i++) {
    printf("-");
  }
  printf(":\n");


  for (size_t j=0; j<ROWS; j++){
    printf(":");
    for (size_t i =0; i<COLLUMNS; i++) {
      printf(".");
    }
    printf(":\n");
  }

  printf(":");
  for (size_t i =0; i<COLLUMNS; i++) {
    printf("-");
  }
  printf(":\n");
  // Move cursor back to top
  printf("\e[%iA", ROWS+2); 
}

void show_score(const int COLLUMNS, const int ROWS, int score) {
  printf("\e[%iB\e[%iCGame score : %d",ROWS+2, COLLUMNS / 2-7, score);
  printf("\e[%iF",ROWS+2 );
}
