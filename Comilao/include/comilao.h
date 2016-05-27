#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

int startGame();
int menu();
int menu_start();
void getDimensions(int *rows, int *col);
int **allocMem(int nrows, int ncolumns);
void makeBoard(int **board, int nrows, int ncolumns);
void showBoard(int **board, int nrows, int ncolumns);
void getPlay(char *letter, int* number, int player);
int checkPlay( int nrows, int ncolumns, char letter, int number);
void makePlay(int **board, int nrows, int ncolumns, char letter, int number, int player);
void savePlay(int **board, int rows, int collums, char letter, int number, int nplays,int player);
int checkWinner(int **board, int nrows, int ncolumns, int player);
