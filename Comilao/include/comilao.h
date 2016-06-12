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

int startGame(int BOT, int LOAD);
int menu();
void showGoal();
int menu2();
int getDimensions(int *rows, int *columns, int LOAD, FILE *save, int *player, char letter, int number, int *BOT);
int **allocMem(int nrows, int ncolumns);
void makeBoard(int **board, int nrows, int ncolumns);
void showBoard(int **board, int nrows, int ncolumns);
int playMenu( int player);
void getPlay(char *letter, int* number, int player);
int checkPlay( int **board, int nrows, int ncolumns, char letter, int number);
void makePlay(int **board, int nrows, int ncolumns, char letter, int number);
void makeLoad(int player,int nrows, int ncolumns ,FILE *f,char letter, int number, int *BOT);
void savePlay(int **board, int rows, int collums, char letter, int number, int nplays,int player);
pmov prevMoves( char letter, int number, int player);
pmov addMove( pmov list, char letter, int number, int player);
void show_prevMoves(pmov p);
int checkWinner(int **board, int nrows, int ncolumns, int player);
void loadGame(int player,char letter, int number, FILE *f, int **board, int nrows, int ncolumns);
void showHow();
void botPlay(int **board, int nrows, int ncolumns, char letter, int number, int *nplays ,int *player, FILE * load, int *BOT);
int checkBonus( int player, int player1_bonus, int player2_bonus);
void countBonus(int *player, int *player1_bonus, int *player2_bonus);
int playerTurn(int *player);
