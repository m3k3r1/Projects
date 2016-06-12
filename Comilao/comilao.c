#include "comilao.h"

int main(int argc, char  *argv[]) {
  int BOT;
  int LOAD;
  int game;
  int menu_op;
  int menu2_op;

  while (TRUE){
    /**
      Menu Inicial
      +-+-+-+-+-+-+-+-+
      +  1- Novo Jogo     +
      +  2- Continuar      +
      +  3- Objetivo         +
      +  4- Sair                 +
      +-+-+-+-+-+-+-+-+
      **/
      menu_op =menu();
      switch ( menu_op ) {
        case 1: LOAD = FALSE;
                    /*
                      Menu Secundário
                      +-+-+-+-+-+-+-+-++-+-+-+-+-+-+-
                      +  1- Jogador vs Jogador                    +
                      +  2- Jogador vs Computador            +
                      +  3- Anterior                                         +
                      +-+-+-+-+-+-+-+-++-+-+-+-+-+-+-
                      */
                      menu2_op = menu2();
                      switch ( menu2_op ) {
                        case 1: BOT = FALSE;
                                    game = startGame(BOT,LOAD);
                                    break;
                        case 2: BOT = TRUE;
                                      game = startGame(BOT,LOAD);
                                      break;
                        case 3: break;
                      }
                      break;
        case 2: LOAD = TRUE;
                      game = startGame(BOT, LOAD);
                      break;
        case 3 : showGoal();
                      break;
        case 4 : return 0;
                        break;
    }
  }
}
