#include "comilao.h" 

int menu() {
  int menu_op;
  system(CLEAR);

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
  printf("\n");
  printf("\tOpção >> ");
  scanf("%d",&menu_op);

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
  printf("\t\t+ 3- Anterior                 +\n");
  printf("\t\t+-+-+-+-+-+-+-+-++-+-+-+-+-+-+-\n");
  printf("\n");
  printf("\tOpção >> ");
  scanf("%d",&menu_op);
  return menu_op;
}
int startGame(int BOT){
  int nrows;
  int ncolumns;
  int winner = FALSE;
  int player = 1;
  int nplays = 0;
  int number;
  char letter;
  int menu_op;
  pmov list = NULL;
  pmov new_list = NULL;

  system(CLEAR);
  printf("\n\n\n\n");

  getDimensions(&nrows,  &ncolumns);
  int **board = allocMem(nrows, ncolumns);
  makeBoard(board, nrows, ncolumns);
  showBoard(board, nrows, ncolumns);

  while (winner == FALSE) {
    if(player > 2)
      player = 1;
    if (player >= 1) {
      if (BOT == TRUE)
        player = 1;

      playMenu(&menu_op, player);
      switch (menu_op) {
        case 1:  showBoard(board, nrows, ncolumns);
                      do {
                        getPlay(&letter, &number, player);
                      } while(checkPlay(board, nrows,ncolumns,letter,number));
                      makePlay(board, nrows, ncolumns, letter, number, player);
                      nplays++;
                      //makeLoad(player, letter, number);
                      savePlay(board, nrows ,ncolumns, letter, number, nplays,player);
                      if(nplays == 1)
                        list = prevMoves(letter, number, player);
                      else
                        new_list = addMove(list, letter, number, player);
                      showBoard(board, nrows, ncolumns);
                      winner = checkWinner(board, nrows, ncolumns, player);
                      player++;
                      break;

        case 2:   free(board);
                        nrows++;
                        ncolumns++;

                        board = allocMem(nrows , ncolumns);
                        //loadGame
                        //board = re_allocMem(board, nrows, ncolumns);
                        makeBoard(board, nrows , ncolumns);
                        showBoard(board, nrows, ncolumns);
                        player++;
                        break;
        case 3:   show_prevMoves(list);
                        break;
        case 4: winner = TRUE;
                      break;
      }

    }
  }
  free(board);
  return TRUE;
}
void getDimensions(int *rows, int *col) {
  do {
    printf("\tLinhas (colocar valor entre 4 e 8) > " );
    scanf("%d", rows );
  } while(*rows < 4 || *rows  > 8);

  do {
    printf("\tColunas (colocar valor entre 6 e 10) > ");
    scanf("%d", col);
  } while(*col < 6 || *col > 10);

  while(*rows > *col){
    system(CLEAR);
    printf("\n\n\n\n");
    printf("\n\tO numero de colunas deve ser maior que o numero de linhas \n\n");
    getDimensions(rows, col);
  }

}
int **allocMem(int nrows, int ncolumns){

  int **board = malloc( (nrows + 1) * sizeof(int *));
  for(int i = 0; i < nrows + 1 ; i++)
  	board[i] = malloc( (ncolumns + 1) * sizeof(int));

  if (board == NULL) {
    printf("\t\nERROR::memory allocation\n\n" );
    free(board);
    return 0 ;
  }
  return board;
}
void makeBoard(int **board, int nrows, int ncolumns){
  for(int lines = 0; lines < nrows + 1; lines++){
    for(int collums = 0; collums < ncolumns + 1; collums++){
      if (lines == (nrows) &&collums == (ncolumns))
        (*(board + lines))[collums] = 88;
    else if(lines != 0 && collums != 0)
      (*(board + lines))[collums] = 42;
    }
  }
}
void showBoard(int **board, int nrows, int ncolumns){
  system(CLEAR);
  printf("\n\n\n");

  for(int lines = 0,letter = 65, number = 1; lines < nrows + 1; lines++){
    for(int collums = 0; collums < ncolumns + 1; collums++){
      if ( lines == 0  && collums != 0){
        printf("| %c ", letter);
        letter++;}
        if (collums == 0 && lines != 0){
          printf("| %d ", number);
          number++;}
        if(collums == 0 && lines == 0)
          printf("    ");
        if (lines == (nrows) && collums == (ncolumns))
          printf("| %c ", (*(board + lines))[collums]);
        else if(lines != 0 && collums != 0)
          printf("| %c ", (*(board + lines))[collums]);
    }
    printf("| \n" );
  }
}
int playMenu(int * menu_op, int player){
  printf("\n");
  printf("\n" );
  printf("\t\t+-Jogador %d +-+-++-+-+-+-+-+-+\n", player);
  printf("\t\t+ 1- Fazer jogada            +\n" );
  printf("\t\t+ 2- Aumentar o tabuleiro    +\n");
  printf("\t\t+ 3- Ver jogadas anteriores  +\n");
  printf("\t\t+ 4- Sair                    +\n");
  printf("\t\t+-+-+-+-+-+-+-+-++-+-+-+-+-+-+\n");
  printf("\n");
  printf("\tOpção >> ");
  scanf("%d",menu_op);

}
/*int **re_allocMem(int ** board, int nrows, int ncolumns){
  board = realloc( board, (nrows + 1) * sizeof(int *));
  for(int i = 0; i < nrows + 1 ; i++)
    board[i] = realloc(board, (ncolumns + 1) * sizeof(int));
    if (board == NULL) {
      printf("\t\nERROR::memory allocation\n\n" );
      free(board);
      return 0 ;
      }
    }
*/
void getPlay(char *letter, int* number, int player){
  printf("\n  ::Jogador %d::  \n",player );
  printf("\tJogada (Exemplo - A1) > " );
  scanf(" %c%d", letter, number);
}
int checkPlay( int **board, int nrows, int ncolumns, char letter, int number){
  int lim = (letter - 65) + 1;

  if (lim > ncolumns || number > nrows   ){
    printf("\tJOGADA INVALIDA :: casa inexistente\n" );
    return 1;
  }
  else if ((*(board + number))[lim] == 32) {
    printf("\tJOGADA INVALIDA :: casa já vazia \n" );
    return 1;
  }
  return 0;

}
void makePlay(int **board, int nrows, int ncolumns, char letter, int number, int player){
  int lim = (letter - 65) + 1;
  for(int lines = 1; lines < nrows + 1; lines++){
    for(int collums = 1; collums < ncolumns + 1  ; collums++){
      if( lines <= number && collums <= lim)
        (*(board + lines))[collums] = 32;
    }
  }
}
/*void makeLoad(int player, char letter, int number){
    FILE *f;
    f = fopen("save.bin", "wb");
    if( f==NULL ) {
      printf("Erro no acesso ao ficheiro\n");
      return 0; }
    fwrite(player,sizeof(int),1,f);
    fwrite(letter,sizeof(char),1,f);
    fwrite(number,sizeof(int),1,f);
    fclose(f);
  }
*/
void savePlay(int **board, int nrows, int ncolumns, char letter, int number, int nplays ,int player){
  FILE *f;
   f = fopen("save.txt", "a+");

   if(f==NULL){
     printf("Erro no acesso ao ficheiro\n");
     return;}

    fprintf(f, "\n");
    fprintf(f, "%d: JOGADOR %d > %c%d \n", nplays , player, letter, number);
    fprintf(f, "\n");

    for(int lines = 0,letter = 65, number = 1; lines < nrows + 1; lines++){
      for(int collums = 0; collums < ncolumns + 1; collums++){
        if ( lines == 0  && collums != 0){
          fprintf(f, "| %c ", letter);
          letter++;}
        if (collums == 0 && lines != 0){
          fprintf(f, "| %d ", number);
          number++;}
        if(collums == 0 && lines == 0)
          fprintf(f,"    ");
        if (lines == (nrows) && collums == (ncolumns))
          fprintf(f, "| %c ", (*(board + lines))[collums]);
        else if(lines != 0 && collums != 0)
          fprintf(f, "| %c ", (*(board + lines))[collums]);
      }
      fprintf(f,"| \n" );
    }
    fprintf(f, "\n\n");
    fclose(f);
}
pmov prevMoves( char letter, int number, int player){

    pmov newNode = malloc(sizeof(struct game_info));
    newNode->player = player;
    newNode->letter = letter;
    newNode->number = number;
    newNode->prox = NULL;

    return newNode;
}
pmov addMove( pmov list, char letter, int number, int player){
  pmov addNode = malloc(sizeof(struct game_info));
  list->prox = addNode;
  addNode->player = player;
  addNode->letter = letter;
  addNode->number = number;
  addNode->prox = NULL;

  return addNode;

}
void show_prevMoves(pmov p){
  if ( p == NULL) {
    printf("Ainda não foi efetuada nenhuma jogada\n" );
  }
  while (p != NULL) {
    printf("Jogador %d -> %c%d \n", p->player, p->letter, p->number);
    p = p->prox;
  }
}
int checkWinner(int **board, int nrows, int ncolumns, int player){
  if ((*(board + nrows))[ncolumns] == 32){
    printf(" \n\t\tJOGADOR %d  PERDEU ! \n\n",player );
    printf("Clica ENTER para continuar\n");
    getchar();
    getchar();
    return TRUE;
  }
  else
    return FALSE;
  }
