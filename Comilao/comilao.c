#include "comilao.h"

int main(int argc, char  *argv[]) {
  int game;

  do {
    int menu_op = menu();
    int menu_op_2;

    switch(menu_op){
      case 1: menu_op_2 = menu_start();
                    int game = startGame();
                    break;
      case 2: puts("Falta funcao 2");
                    break;
      case 3: game == FALSE;
                    break;
    }

  } while( game == TRUE );
  return 0;
}
