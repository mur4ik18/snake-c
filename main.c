#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>

#define COLLUMNS 40
#define ROWS 20
//#define GAME_SPEED 5*100000
int main(){
  int quit = 0;
  int x[1000], y[1000];
  // Hide cursor
  int game_speed = 400000;
  // switch to canonical mode, disable echo
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  int score = 0;
  while (!quit) {
    
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

    int head = 0, tail =0;
    x[head]= COLLUMNS / 2;
    y[head]= ROWS / 2;

    int gameover = 0;

    int xdir = 1, ydir = 0;
    int apple_x = -1, apple_y;
    while (!quit && !gameover) {

      printf("\e[%iB\e[%iCGame score : %d",ROWS+2, COLLUMNS / 2-7, score);
      printf("\e[%iF",ROWS+2 );
   
      // Create new apple
      if (apple_x <0) {
        apple_x = rand() % COLLUMNS;
        apple_y = rand() % ROWS;

        for (size_t i = tail; i != head; i =(i+1)%1000) {
          if (x[i] == apple_x && y[i] == apple_y) {
            apple_x = -1;
          }
        }
        if (apple_x >=0) {
          // Draw

          printf("\e[%iB\e[%iC*",apple_y +1, apple_x+1);
          printf("\e[%iF", apple_y+1);
        }
      }
      // clear snake tail
      printf("\e[%iB\e[%iC.", y[tail] + 1, x[tail] + 1);
      printf("\e[%iF", y[tail] + 1);
      
      if (x[head] == apple_x && y[head] == apple_y){
        apple_x = -1;
        game_speed-=1000;
        score++;
        printf("\a");
      } else {
        tail = (tail +1) % 1000;
      }
      int newhead = (head + 1) %1000;
      x[newhead] = (x[head] + xdir + COLLUMNS) % COLLUMNS;
      y[newhead] = (y[head] + ydir + ROWS) % ROWS;
      head = newhead;
      for (size_t i = tail; i != head; i = (i+1) % 1000) {
        if (x[i] == x[head] && y[i] == y[head]){
          gameover = 1;
          score=0;
          
        }
      }

      // Draw head
      printf("\e[%iB\e[%iC0", y[head] + 1, x[head] + 1);
      printf("\e[%iF", y[head] + 1);
      fflush(stdout);

      usleep(game_speed);

      // Read keyboard

      struct timeval tv;
      fd_set fds;
      tv.tv_sec = 0;
      tv.tv_usec = 0;
      FD_ZERO(&fds);
      FD_SET(STDIN_FILENO, &fds);
      select(STDIN_FILENO +1, &fds, NULL, NULL, &tv);
      if(FD_ISSET(STDIN_FILENO, &fds)) {
        int ch = getchar();
        if (ch == 27 || ch == 'q') {
          quit = 1;
        } else if (((ch == 'h') || (ch == 'a')) && xdir != 1) {
          xdir = -1;
          ydir = 0;
        } else if (((ch == 'k') || (ch == 'w'))  && ydir != 1) {
          xdir = 0;
          ydir = -1;
        } else if (((ch == 'j') || (ch == 's')) && ydir != -1) {
          xdir = 0;
          ydir = 1;
        }else if (((ch == 'l') || (ch == 'd')) && xdir != -1) {
          xdir = 1;
          ydir = 0;
        }
      }
    }
    if (!quit) {
      // game over
      printf("\e[%iB\e[%iCGame over!", ROWS / 2, COLLUMNS / 2-5);
      printf("\e[%iF", ROWS / 2);
      getchar();
    }
  }
  printf("\e[?25h");
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return 0;
}
