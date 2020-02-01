#include "plateau.h"

int main(){
  printf("\e[2J\e[8;27;100t");
  const int piece_o[5][5] = {{12,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
  system("clear");
  int randomnumber;
  srand(time(0));
  randomnumber = rand() % 12 +1;
  plateau grille;
  initPlateau(grille);
  jeu(grille,piece_o, 0,0, randomnumber, 1, 0, 0);
}
