#include "comilao.h"

int main(int argc, char  *argv[]) {
  int game;
  int BOT = FALSE;
  int LOAD = FALSE;
  int menu_op_2;
  int menu_op;

  while (TRUE) {
    menu_op =menu();
    if (menu_op == EXIT)
      return 0;
    else if ( menu_op == 2){
        LOAD = TRUE;
        game = startGame(BOT, LOAD);}
    else{
      menu_op_2 = menu_start();
      switch (menu_op_2) {
        case 1: game = startGame(BOT,LOAD);
                      break;
        case 2: BOT = TRUE;
                      game = startGame(BOT,LOAD);
                      break;
        case 3: game = FALSE;
                      break;
      }
    }
  }
}
