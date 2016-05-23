#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

struct play {
  char letter;
  int number;
};

int startGame();
int menu();
int menu_start();
void getDimensions(int *rows, int *col);
int **allocMem(int nrows, int ncolumns);
void makeBoard(int **board, int nrows, int ncolumns);
//void showBoard(int **board, int nrows, int ncolumns);
