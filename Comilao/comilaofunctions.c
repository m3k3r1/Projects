#include "comilao.h"
nt menu() {
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
  printf("\t\t+ 3- Objetivo   +\n");
  printf("\t\t+ 4- Sair       +\n");
  printf("\t\t+-+-+-+-+-+-+-+-+\n");
  printf("\n");
  do {
    printf("\tOpção >> ");
    scanf("%d",&menu_op);
  } while(menu_op < 1 || menu_op > 4 || isalpha(menu_op) == TRUE );
  return menu_op;
}
void showGoal() {
  system(CLEAR);
  printf("\n\n\t\t O jogo do comilão é efetuado num tabuleiro retangular dividido em células.\n");
  printf("\t As células são identificadas pela linha e coluna em que se encontram. No\n");
  printf("\t início todas as células contêm alimento comestível (*), exceto a do canto\n");
  printf("\t inferior direito que contém veneno(X).\n");
  printf("\t\t O jogo realiza-se entre 2 jogadores que efetuam movimentos alternados.\n");
  printf("\t Em cada jogada,os jogadores escolhem uma das células com comida.\n");
  printf("\t Para além da posição selecionada, todas as células para a esquerda e\n");
  printf("\t para cima da escolhida passam a estar vazias. Asjogadas sucedem-se\n");
  printf("\t alternadamente, perdendo o jogador que for obrigado a ingerir o veneno.\n" );

  printf("\n\nPrima ENTER para continuar ...");
  getchar();
  getchar();
}
int menu2(){
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
int startGame(int BOT, int LOAD){
  int nrows;
  int ncolumns;
  FILE *load;
  int winner = FALSE;
  int player = 1;
  int player1_bonus = 0;
  int player2_bonus = 0;
  int nplays = 0;
  int number;
  char letter;
  int menu_op;
  pmov list = NULL;
  pmov new_list  = NULL;
  int **board;

  system(CLEAR);
  printf("\n\n\n\n");
  if ( getDimensions(&nrows, &ncolumns, LOAD, load, &player, letter, number, &BOT))
    return 1;

  else{
  board = allocMem(nrows, ncolumns);
  makeBoard(board, nrows, ncolumns);

  if (LOAD == TRUE){
    loadGame(player, letter, number,load,board,nrows,ncolumns);
    showBoard(board, nrows, ncolumns);
  }
  else{
    remove("save.dat");
    showBoard(board, nrows, ncolumns);
  }

  while (winner == FALSE) {
    menu_op = playerTurn(&player);
      switch (menu_op) {
        case 1:  showBoard( board, nrows, ncolumns);
                      do {
                        getPlay(&letter, &number, player);
                      } while(checkPlay(board, nrows,ncolumns,letter,number));
                      makePlay(board, nrows, ncolumns, letter, number);
                      nplays++;
                      savePlay(board, nrows ,ncolumns, letter, number, nplays,player);
                      makeLoad(player,nrows, ncolumns,load,letter, number, &BOT);

                      if(nplays == 1)
                        list = prevMoves(letter, number, player);
                      else
                        new_list = addMove(list, letter, number, player);

                      showBoard(board, nrows, ncolumns);
                      winner = checkWinner(board, nrows, ncolumns, player);
                      player++;

                      if (BOT == TRUE)
                        botPlay(board, nrows, ncolumns, letter,number, &nplays, &player, load, &BOT);
                      break;

        case 2:   if( checkBonus(player, player1_bonus, player2_bonus) )
                            printf("O jogador %d já usou a jogada bonus\n", player);
                        else{
                          free(board);
                          nrows++;
                          ncolumns++;
                          board = allocMem(nrows , ncolumns);
                          makeBoard(board, nrows, ncolumns);
                          makeLoad(player,nrows, ncolumns,load,letter, number, &BOT);
                          loadGame(player, letter, number,load,board,nrows,ncolumns);
                          showBoard(board, nrows, ncolumns);
                          countBonus(&player, &player1_bonus, &player2_bonus);
                        }
                        break;
        case 3:  show_prevMoves(list);
                        break;
        case 4: showHow();
                     break;
        case 5: winner = TRUE;
                       break;
      }
    }
  }

  free(board);
  return TRUE;
}
int getDimensions(int *rows, int *columns, int LOAD, FILE *save, int *player, char letter, int number, int *BOT) {
  int tmp_rows = 0;
  int tmp_columns = 0;
  int tmp_player = 0;

  if ( LOAD == TRUE ){
    save = fopen("save.dat", "r+");
    if( save == NULL ){
      printf("Erro no acesso ao ficheiro ou o ficheiro não existe\n");
      printf("Prima ENTER para continuar" );
      getchar();
      getchar();
      return 1;
    }
    while ( feof(save) == 0 ) {
      fread(&tmp_rows,sizeof(tmp_rows),1,save);
      fread(&tmp_columns,sizeof(tmp_columns),1,save);
      fread(&tmp_player, sizeof(tmp_player),1,save);
      fread(BOT, sizeof(BOT), 1, save);
      fread(&letter,sizeof(letter),1,save);
      fread(&number,sizeof(number),1,save);
    }
    *rows = tmp_rows ;
    *columns = tmp_columns ;
    *player = tmp_player + 1; //O ficheiro guarda o ultimo jogador logo tem que ser o seguinte
    return 0;
  }

  else{

    do {
      printf("\tLinhas (colocar valor entre 4 e 8) > " );
      scanf("%d", rows );
    } while(*rows < 4 || *rows  > 8);

    do {
      printf("\tColunas (colocar valor entre 6 e 10) > ");
      scanf("%d", columns);
    } while(*columns < 6 || *columns > 10);


    while(*rows > *columns){
      system(CLEAR);
      printf("\n\n\n\n");
      printf("\n\tO numero de colunas deve ser maior que o numero de linhas \n\n");
      getDimensions(rows, columns,LOAD, save, player, letter, number, BOT);
    }
    return 0;
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
  int lines;
  int columns;

  // + 1 porque o index faz parte da board logo é preciso mais um espaço
  for( lines = 0; lines < nrows+ 1 ; lines++){
    for( columns = 0; columns < ncolumns +1  ; columns++){
      // Na ultima casa coloca um "X" -> ASCII - 88
      if (lines == (nrows) && columns == (ncolumns))
        (*(board + lines))[columns] = 88;
    /* Poe uma * em todas as outras casas
    (ERRO :: Linhas de indexação têm lixo(*) não visivel para o utilizador) */
    else
      (*(board + lines))[columns] = 42;
    }
  }
}
void showBoard(int **board, int nrows, int ncolumns){
  system(CLEAR);
  printf("\n\n\n");
  int lines;
  int columns;
  int letter = 65, number = 1;

  for(lines = 0; lines < nrows + 1; lines++){
    for( columns = 0; columns < ncolumns + 1; columns++){
      //Quando esta na primeira linha começa a mostrar as letras da indexação
      if ( lines == 0  && columns != 0){
        printf("| %c ", letter);
        letter++;
      }
      //Quando esta na primeira coluna começa a mostras os numeros da indexação
      else if(columns == 0 && lines != 0){
          printf("| %d ", number);
          number++;
        }
        //No primeiro bloco mostra um espaço para a tabela aparecer bem posicionada
        else if(columns == 0 && lines == 0)
          printf("    ");
        else
          printf("| %c ", (*(board + lines))[columns]);
    }
    printf("| \n" );
  }
}
int playMenu( int player){
  int menu_op;

  printf("\n");
  printf("\n" );
  printf("\t\t+-Jogador %d +-+-++-+-+-+-+-+-+\n", player);
  printf("\t\t+ 1- Fazer jogada            +\n" );
  printf("\t\t+ 2- Aumentar o tabuleiro    +\n");
  printf("\t\t+ 3- Ver jogadas anteriores  +\n");
  printf("\t\t+ 4- Instruções              +\n");
  printf("\t\t+ 5- Sair e guardar          +\n");
  printf("\t\t+-+-+-+-+-+-+-+-++-+-+-+-+-+-+\n");
  printf("\n");
  do {
    printf("\tOpção >> ");
    scanf("%d",&menu_op);

  } while( 0 > menu_op && menu_op > 4);
  return menu_op;
}
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
void makePlay(int **board, int nrows, int ncolumns, char letter, int number){

  int lim = (letter - 65) + 1;
  for(int lines = 1; lines < nrows + 1; lines++){
    for(int collums = 1; collums < ncolumns + 1  ; collums++){
      if( lines <= number && collums <= lim)
        (*(board + lines))[collums] = 32;
    }
  }
}
void makeLoad(int player,int nrows, int ncolumns ,FILE *f,char letter, int number, int *BOT){

    f = fopen("save.dat", "a+");
    if( f==NULL ) {
      printf("Erro no acesso ao ficheiro\n");
      return ; }
    fwrite(&nrows,sizeof(nrows),1,f);
    fwrite(&ncolumns,sizeof(ncolumns),1,f);
    fwrite(BOT, sizeof(BOT), 1, f);
    fwrite(&player,sizeof(player),1,f);
    fwrite(&letter,sizeof(letter),1,f);
    fwrite(&number,sizeof(number),1,f);

    fclose(f);
  }
void loadGame(int player,char letter, int number, FILE *f, int **board, int nrows, int ncolumns) {
  f = fopen("save.dat", "r+");

  if( f==NULL ) {
    printf("Erro no acesso ao ficheiro\n");
    return ; }

    while (feof(f) == 0) {
      fread(&nrows,sizeof(nrows),1,f);
      fread(&ncolumns,sizeof(ncolumns),1,f);
      fread(&player, sizeof(player),1,f);
      fread(&letter,sizeof(letter),1,f);
      fread(&number,sizeof(number),1,f);

      makePlay(board, nrows, ncolumns, letter, number);
    }
  }
void savePlay(int **board, int nrows, int ncolumns, char letter, int number, int nplays ,int player){
  FILE *f;
   f = fopen("save.txt", "a+");

   if(f==NULL){
     printf("Erro no acesso ao ficheiro\n");
     return;}

     if (player == 0){
       fprintf(f, "\n");
       fprintf(f, "%d: COMPUTADOR > %c%d \n", nplays , letter, number);
       fprintf(f, "\n");
     }
     else{
       fprintf(f, "\n");
       fprintf(f, "%d: JOGADOR %d > %c%d \n", nplays , player, letter, number);
       fprintf(f, "\n");
     }

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

    pmov list = malloc(sizeof(struct game_info));
    list->player = player;
    list->letter = letter;
    list->number = number;
    list->prox = NULL;

    return list;
}
pmov addMove( pmov list, char letter, int number, int player){

  pmov new_Node = malloc(sizeof(struct game_info));
  list->prox = new_Node;
  new_Node->player = player;
  new_Node->letter = letter;
  new_Node->number = number;
  new_Node->prox = NULL;

  return new_Node;
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
    remove("save.dat");
    getchar();
    getchar();
    return TRUE;
  }
  else
    return FALSE;
  }
void showHow(){
  system(CLEAR);
  printf("Ao ver este menu deve escolher uma das opçoes:\n\n" );
  printf("\t\t+-Jogador 1 +-+-++-+-+-+-+-+-+\n");
  printf("\t\t+ 1- Fazer jogada            +\n" );
  printf("\t\t+ 2- Aumentar o tabuleiro    +\n");
  printf("\t\t+ 3- Ver jogadas anteriores  +\n");
  printf("\t\t+ 4- Instruções              +\n");
  printf("\t\t+ 5- Sair e guardar          +\n");
  printf("\t\t+-+-+-+-+-+-+-+-++-+-+-+-+-+-+\n");
  printf("Se escolher 1 tera que fazer a jogado no tabuleiro no qual\n" );
  printf("tera que escolher a coordenada LETRA NUMERO que deseja\n" );
  printf("Se escolher 2 JOGADA BONUS aumentara o tabuleiro 1 casa \n" );
  printf("nas linhas e colunas , cuidado só podera usar uma vez\n" );
  printf("Se escolher 3 podera ver jogadas anteriores\n" );

  printf("\n\nPrima ENTER para continuar ...");
  getchar();
  getchar();
}
void botPlay(int **board, int nrows, int ncolumns, char letter, int number, int *nplays ,int *player, FILE * load, int *BOT){
  letter++;
  number++;
  *player = 0; // 0 -> Jogador Computador

  makePlay(board, nrows, ncolumns, letter, number);
  nplays++;
  savePlay(board, nrows ,ncolumns, letter, number, *nplays, *player);
  makeLoad(*player,nrows, ncolumns, load, letter, number, BOT);
  showBoard(board, nrows, ncolumns);
  printf("\n\tJogada do Computador -> %c%d \n", letter, number );
  *player = 1;
}
int checkBonus( int player, int player1_bonus, int player2_bonus){
  if( player1_bonus == 1 && player == 1 || player2_bonus == 1 && player == 2 )
    return 1;
  return 0;
}
void countBonus(int *player, int *player1_bonus, int *player2_bonus){
  if (*player == 1)
    *player1_bonus+= 1;
  else
    *player2_bonus+=1;
  *player+= 1;
}
int playerTurn(int *player){
  int menu_op;

  if(*player > 2)
    *player = 1;
  if (*player >= 1)
    menu_op = playMenu(*player);
  return menu_op;
}
