#include "comilao.h"

int menu() {
  int menu_op;

  printf("   ______                        _   __                  \n" );
  printf(" .' ___  |                      (_) [  |                 \n");
  printf("/ .'   \\_|  .--.   _ .--..--.   __   | |  ,--.    .--.   \n" );
  printf("| |       / .'`\\ \\[ `.-. .-. | [  |  | | `'_\\ : / .'`\\\\ \n" );
  printf("\\ `.___.'\\| \\__. | | | | | | |  | |  | | // | |,| \\__.| \n" );
  printf(" `.____ .' '.__.' [___||__||__][___][___]\'-;__/ '.__.'  \n" );
  printf("\n" );
  printf("\t\t+-+-+-+-+-+-+-+-+\n");
  printf("\t\t+ 1- Novo Jogo  +\n" );
  printf("\t\t+ 2- Continuar  +\n");
  printf("\t\t+ 3- Sair       +\n");
  printf("\t\t+-+-+-+-+-+-+-+-+\n");

  system("stty -echo");
  scanf("%d",&menu_op);
  system("stty echo");
  return menu_op;
}
int menu_start(){
  int menu_op;

  system(CLEAR);
  printf("\n");
  printf("\n");
  printf("\n" );
  printf("\t\t+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-\n");
  printf("\t\t+ 1- Jogador vs Jogador       +\n" );
  printf("\t\t+ 2- Jogador vs Computador    +\n");
  printf("\t\t+ 3- Sair                     +\n");
  printf("\t\t+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-\n");
  system("stty -echo");
  scanf("%d",&menu_op);
  system("stty echo");
  return menu_op;
}
int startGame(){
  int nrows;
  int ncolumns;
  int winner = FALSE;
  int player = 0;
  struct play game;

  getDimensions(&nrows,  &ncolumns);
  int **board = allocMem( nrows, ncolumns);
  makeBoard(board, nrows, ncolumns);
  //showBoard(board, nrows, ncolumns);

  while(winner == FALSE){
    printf("\nCoordenates (A-1)> " );
    scanf("%c-%d ",&game.letter, &game.number );
  }

  free(board);
  return TRUE;
}
void getDimensions(int *rows, int *col) {
  system(CLEAR);
  printf("\n\n\n\n");
  printf("\tLines > " );
  scanf("%d", rows );
  printf("\tCollums > ");
  scanf("%d", col);
}
int **allocMem(int nrows, int ncolumns){

  int **board = malloc(nrows * sizeof(int *));
  for(int i = 0; i < nrows; i++)
  	board[i] = malloc(ncolumns * sizeof(int));

  if (board == NULL) {
    printf("\t\nERROR::memory allocation\n\n" );
    free(board);
    return;
  }

  return board;
}
void makeBoard(int **board, int nrows, int ncolumns){
  system(CLEAR);
  printf("\n\n\n");
  for(int lines = 0, letter = 65, number = 1; lines < nrows + 1; lines++){
    for(int collums = 0; collums < ncolumns + 1; collums++){

      if ( lines == 0  && collums != 0){
        (*board + lines)[collums] = letter;
        printf("| %c ", (*board + lines)[collums]);
        letter++;
      }

      if (collums == 0 && lines != 0){
        (*board + lines)[collums] = number;
        printf("| %d ", (*board + lines)[collums]);
        number++;
      }

      if(collums == 0 && lines == 0)
        printf("    ");

       if (lines == (nrows) &&collums == (ncolumns)){
        (*board + lines)[collums] = 88;
        printf("| %c ", (*board + lines)[collums]);
        }

      else if(lines != 0 && collums != 0){
        (*board + lines)[collums] = 42;
        printf("| %c ", (*board + lines)[collums]);
      }
    }
    printf("| \n" );
  }
}
/**void showBoard(int **board, int nrows, int ncolumns){
  system(CLEAR);
  printf("\n\n\n");
  for(int lines = 0; lines < nrows + 1; lines++){
    for(int collums = 0; collums < ncolumns + 1; collums++){
      if ( lines == 0  && collums != 0)
        printf("| %c ", (*board + lines)[collums]);
      if (collums == 0 && lines != 0)
        printf("| %d ", (*board + lines)[collums]);
      if(collums == 0 && lines == 0)
        printf("    ");
      if (lines == (nrows) &&collums == (ncolumns))
        printf("| %c ", (*board + lines)[collums]);
      else if(lines != 0 && collums != 0)
        printf("| %c ", (*board + lines)[collums]);
    }
    printf("| \n" );
  }
 }
**/
