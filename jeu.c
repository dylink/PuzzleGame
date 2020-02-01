#include "plateau.h"


static struct termios g_old_kbd_mode;

static void old_attr(void){
    tcsetattr(0, TCSANOW, &g_old_kbd_mode);
}


//Détecte s'il n'y a plus d'espace disponible sur le plateau pour la pièce courant
int finPartie(plateau grille, const int piece[][5]){
  int i, j;
  for(i = 0; i<L; i++){
    for(j = 0; j<C; j++){
      if(!collision(grille, piece, i, j) && !horsPlateauD(grille, piece, i, j-1)) {
        return 1; //On parcours la grille, et s'il y a au moins une position dans laquelle la pièce courrante n'a pas de collision, alors la partie continue
      }
    }
  }
  return 0;
}

//Boucle principale de jeu
void jeu(plateau grille, const int piece[][5], int ligne ,int colonne, int randomnumber, int joueur, int score1, int score2){

/*																			Déclaration des pièces																	*/
  const int piece_CROIX[5][5] = {{0,0,1,0,0},{0,0,1,0,0},{1,1,1,1,1},{0,0,1,0,0},{0,0,1,0,0}};
  const int piece_L[5][5] = {{2,0,0,0,0},{2,2,2,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
  const int piece_L180[5][5] = {{3,3,3,0,0},{0,0,3,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
  const int piece_P[5][5] = {{4,4,4,0,0},{4,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
  const int piece_P180[5][5] = {{5,5,5,0,0},{0,0,5,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
  const int piece_U[5][5] = {{6,0,6,0,0},{6,6,6,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
  const int piece_U180[5][5] = {{7,7,7,0,0},{7,0,7,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
  const int piece_C[5][5] = {{8,8,0,0,0},{8,0,0,0,0},{8,8,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
  const int piece_C180[5][5] = {{9,9,0,0,0},{0,9,0,0,0},{9,9,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
  const int piece_m[5][5] = {{10,10,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
  const int piece_i[5][5] = {{11,0,0,0,0},{11,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
  const int piece_o[5][5] = {{12,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0}};
/*																			Déclaration des pièces																	*/


  int signalFin = 1, nextPiece[5][5], r, couleur;
  plateau grille2;
  r = rand() % 12 +1; //La variable r récupère un chiffre au hasard entre 1 et 12

  if(joueur == 2){ //Actualisation des scores
    score1+=effaceLigne(grille);
  }
  else if (joueur == 1){
    score2+=effaceLigne(grille);
  }
  tableauCopie(grille, grille2); //Création de la copie de la première grille

/*																			On établit les pièces suivantes aléatoirement																		*/
  switch(randomnumber){
    case 1 : for(int i =0; i<5; i++){for(int j = 0; j<5; j++){nextPiece[i][j] = piece_CROIX[i][j];}}; break;
    case 2 : for(int i =0; i<5; i++){for(int j = 0; j<5; j++){nextPiece[i][j] = piece_L[i][j];}}; break;
    case 3 : for(int i =0; i<5; i++){for(int j = 0; j<5; j++){nextPiece[i][j] = piece_L180[i][j];}}; break;
    case 4 : for(int i =0; i<5; i++){for(int j = 0; j<5; j++){nextPiece[i][j] = piece_P[i][j];}}; break;
    case 5 : for(int i =0; i<5; i++){for(int j = 0; j<5; j++){nextPiece[i][j] = piece_P180[i][j];}}; break;
    case 6 : for(int i =0; i<5; i++){for(int j = 0; j<5; j++){nextPiece[i][j] = piece_U[i][j];}}; break;
    case 7 : for(int i =0; i<5; i++){for(int j = 0; j<5; j++){nextPiece[i][j] = piece_U180[i][j];}}; break;
    case 8 : for(int i =0; i<5; i++){for(int j = 0; j<5; j++){nextPiece[i][j] = piece_C[i][j];}}; break;
    case 9 : for(int i =0; i<5; i++){for(int j = 0; j<5; j++){nextPiece[i][j] = piece_C180[i][j];}}; break;
    case 10 : for(int i =0; i<5; i++){for(int j = 0; j<5; j++){nextPiece[i][j] = piece_m[i][j];}}; break;
    case 11 : for(int i =0; i<5; i++){for(int j = 0; j<5; j++){nextPiece[i][j] = piece_i[i][j];}}; break;
    case 12 : for(int i =0; i<5; i++){for(int j = 0; j<5; j++){nextPiece[i][j] = piece_o[i][j];}}; break;
  }
/*																			On établit les pièces suivantes aléatoirement																		*/
for (int i = 0; i<5; i++){
  for(int j = 0; j<5; j++){
    if(piece[i][j] != 0){
      couleur = piece[i][j];
    }
  }
}

  formePiece(grille, piece, ligne,colonne, 13); //On affiche la pièce courrante sur le plateau

  affichePlateau(grille, nextPiece, score1, score2); //On affiche le plateau

  printf("Veuillez placer votre pièce\n");
  if(joueur == 1){
    printf("Au tour du joueur 1\n");
  }
  else{
    printf("Au tour du joueur 2\n");
  }
  printf("z = déplacer en haut\tq = déplacer à gauche\ts = déplacer en bas\td = déplacer à droite\n\t\t\t\t\t v = confirmer\n");

  while( finPartie( grille2, piece ) ){ //Tant que la partie n'est pas terminée... (On prend la deuxième grille en référence, car il s'agit d'elle qui "ne possède pas" la pièce courrante)
    while( signalFin ) { //Tant que le joueur n'a pas validé sa saisie

    static char init;
    struct termios new_kbd_mode;

    if(init)
        return;
    // put keyboard (stdin, actually) in raw, unbuffered mode
    tcgetattr(0, &g_old_kbd_mode);
    memcpy(&new_kbd_mode, &g_old_kbd_mode, sizeof(struct termios));

    new_kbd_mode.c_lflag &= ~(ICANON | ECHO);
    new_kbd_mode.c_cc[VTIME] = 0;
    new_kbd_mode.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_kbd_mode);
    atexit(old_attr);

    char saisie = getchar();
    if(((saisie != 'z') && (saisie != 'q') && (saisie != 's') && (saisie != 'd') && (saisie != 'v'))){
      system("clear");
      jeu(grille2, piece, ligne,colonne, randomnumber, joueur, score1, score2);
    }

/*																			On établit les déplacements des pièces																		*/
    switch( saisie ){
      case 'z' :  if(ligne!=0){
                    system("clear");
                    jeu(grille2, piece, ligne-1,colonne, randomnumber, joueur, score1, score2);
                  }
                  system("clear");
                  jeu(grille2, piece, ligne,colonne, randomnumber, joueur, score1, score2);
                  break;
      case 'q' :  if(colonne!=0){
                    system("clear");
                    jeu(grille2, piece, ligne,colonne-1, randomnumber, joueur, score1, score2);
                  }
                  system("clear");
                  jeu(grille2, piece, ligne,colonne, randomnumber, joueur, score1, score2);
                  break;
      case 's' :  if(!horsPlateauB(grille, piece, ligne, colonne)){
                    system("clear");
                    jeu(grille2, piece, ligne+1,colonne, randomnumber, joueur, score1, score2);
                  }
                  system("clear");
                  jeu(grille2, piece, ligne,colonne, randomnumber, joueur, score1, score2);
                  break;
      case 'd' :  if(!horsPlateauD(grille, piece, ligne, colonne)){
                    system("clear");
                    jeu(grille2, piece, ligne,colonne+1, randomnumber, joueur, score1, score2);
                  }
                  system("clear");
                  jeu(grille2, piece, ligne,colonne, randomnumber, joueur, score1, score2);
                  break;
      case 'v' :  system("clear");
        if (collision(grille2, piece, ligne, colonne)) {
          affichePlateau(grille, nextPiece, score1, score2);
          printf("Il y a déjà une pièce à cet emplacement.\n");
        }
        else {
          joueur = (joueur==1) ? 2 : 1;
          signalFin = 0;
          formePiece(grille, piece, ligne,colonne, couleur);
          jeu(grille, nextPiece, 0,0, r, joueur, score1, score2);
        };
        break;
      }
/*																			On établit les déplacements des pièces																		*/

    }
  }
  for (int i= 0; i<5; i++){
    for(int j = 0; j<5; j++){
      nextPiece[i][j] = 0; //On vide le cadre de droite
    }
  }
  system("clear");
  affichePlateau(grille2, nextPiece, score1, score2); //On affiche le plateau final sans la pièce courrante
  printf("\n\n\nFin de partie!\n");
  if(score1 > score2){
    printf("Le joueur 1 gagne!\n");
  }
  else if(score2 > score1){
    printf("Le joueur 2 gagne!\n");
  }
  else {
    printf("Egalité entre les deux joueurs!\n");
  }
  exit(1);
}
