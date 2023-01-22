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
