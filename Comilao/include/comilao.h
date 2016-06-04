#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define EXIT 3

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

typedef struct game_info *pmov;
 struct game_info {
  int player;
  char letter;
  int number;
  pmov prox;
};

int startGame(int BOT);
int menu();
int menu_start();
void getDimensions(int *rows, int *col);
int **allocMem(int nrows, int ncolumns);
void makeBoard(int **board, int nrows, int ncolumns);
void showBoard(int **board, int nrows, int ncolumns);
int playMenu(int * menu_op, int player);
//int **re_allocMem(int ** board, int nrows, int ncolumns);
void getPlay(char *letter, int* number, int player);
int checkPlay( int **board, int nrows, int ncolumns, char letter, int number);
void makePlay(int **board, int nrows, int ncolumns, char letter, int number, int player);
//void makeLoad(int player, char letter, int number);
void savePlay(int **board, int rows, int collums, char letter, int number, int nplays,int player);
pmov prevMoves( char letter, int number, int player);
pmov addMove( pmov list, char letter, int number, int player);
void show_prevMoves(pmov p);
int checkWinner(int **board, int nrows, int ncolumns, int player);
