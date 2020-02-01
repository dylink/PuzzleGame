#include "plateau.h"

//Initialise le plateau
void initPlateau(plateau grille){
  int i, j;
  for (i = 0; i<L ;i++){
    for (j = 0; j<C; j++){
      grille[i][j] = 0;
    }
  }
}

//Affiche la pièce suivante
void afficheSuiv(const int piece[][5], plateau grille){
  int i, j, grille1[5][5], x;
  for (i = 0; i<5;i++){
    for (j = 0; j<5; j++){
      grille1[i][j] = piece[i][j]; //La grille de droite prend les attributs de la pièce
    }
  }
  for (i = 0; i<5;i++){ //Boucle qui permet d'afficher le plateau principal à la zone correspondante au deuxième cadre (les 5 premières lignes)
    printf("⎪");
    for(x=0; x<C; x++){
      switch(grille[i][x]){ //On prend la grille principale en référence et on affiche cette dernière
        case 0: printf("  "); break;
        case 1: printf("\033[31;2;41m▣ \033[0m"); break;
        case 2: printf("\033[32;2;42m▣ \033[0m"); break;
        case 3: printf("\033[32;2;42m▣ \033[0m"); break;
        case 4: printf("\033[32;2;42m▣ \033[0m"); break;
        case 5: printf("\033[32;2;42m▣ \033[0m"); break;
        case 6: printf("\033[33;2;43m▣ \033[0m"); break;
        case 7: printf("\033[33;2;43m▣ \033[0m"); break;
        case 8: printf("\033[33;2;43m▣ \033[0m"); break;
        case 9: printf("\033[33;2;43m▣ \033[0m"); break;
        case 10: printf("\033[34;2;44m▣ \033[0m"); break;
        case 11: printf("\033[34;2;44m▣ \033[0m"); break;
        case 12: printf("\033[36;2;46m▣ \033[0m"); break;
        case 13: printf("\033[37;2;47m▣ \033[0m"); break;

      }
    }
    printf("⎪\t\t⎪"); //On affiche le bord droite du cadre principal et le bord gauche du suivant
    for (j = 0; j<5; j++){ //Boucle qui permet d'afficher la pièce suivante sur le cadre de droite
      switch(grille1[i][j]){ //On prend la grille de droite en référence et on affiche cette dernière
        case 0: printf("  "); break;
        case 1: printf("\033[31;2;41m▣ \033[0m"); break;
        case 2: printf("\033[32;2;42m▣ \033[0m"); break;
        case 3: printf("\033[32;2;42m▣ \033[0m"); break;
        case 4: printf("\033[32;2;42m▣ \033[0m"); break;
        case 5: printf("\033[32;2;42m▣ \033[0m"); break;
        case 6: printf("\033[33;2;43m▣ \033[0m"); break;
        case 7: printf("\033[33;2;43m▣ \033[0m"); break;
        case 8: printf("\033[33;2;43m▣ \033[0m"); break;
        case 9: printf("\033[33;2;43m▣ \033[0m"); break;
        case 10: printf("\033[34;2;44m▣ \033[0m"); break;
        case 11: printf("\033[34;2;44m▣ \033[0m"); break;
        case 12: printf("\033[36;2;46m▣ \033[0m"); break;
      }
    }
      printf("⎪\n");
  }
}

//Affiche le plateau
void affichePlateau(plateau grille, const int piece[][5], int score1, int score2){
  int i, j, e;
  for (i = 0; i<C+2; i++){ //Boucle qui permet de créer les bordures supérieures des deux cadres
    if (i==0){
      printf("⌻");
    }
    if (i==C+1){
      printf("\b\b⌻ \t\t"); //Si on arrive au bout de la bordure, alors on affiche la bordure du cadre de droite
      for (e = 0; e<7; e++){
        if (e==0 || e==6){
          printf("⌻");
        }
        else {
          printf("⎼⎼");
        }
      }
    }
    else{
      printf("⎼⎼");
    }
  }
  printf("\n");
  for (i = 0; i<L;i++){
    if(i>4){ //Si le cadre de droite n'est plus concerné par l'affichage
      printf("⎪");
    }
    for (j = 0; j<C; j++){
      if(i<5){
        break; //Si le cadre de droite est concerné par l'affichage, alors on l'ignore ici
      }
      else {
        switch(grille[i][j]){ //On prend en référence le tableau pour l'afficher
          case 0: printf("  "); break;
          case 1: printf("\033[31;2;41m▣ \033[0m"); break;
          case 2: printf("\033[32;2;42m▣ \033[0m"); break;
          case 3: printf("\033[32;2;42m▣ \033[0m"); break;
          case 4: printf("\033[32;2;42m▣ \033[0m"); break;
          case 5: printf("\033[32;2;42m▣ \033[0m"); break;
          case 6: printf("\033[33;2;43m▣ \033[0m"); break;
          case 7: printf("\033[33;2;43m▣ \033[0m"); break;
          case 8: printf("\033[33;2;43m▣ \033[0m"); break;
          case 9: printf("\033[33;2;43m▣ \033[0m"); break;
          case 10: printf("\033[34;2;44m▣ \033[0m"); break;
          case 11: printf("\033[34;2;44m▣ \033[0m"); break;
          case 12: printf("\033[36;2;46m▣ \033[0m"); break;
          case 13: printf("\033[37;2;47m▣ \033[0m"); break;
        }
      }
    }
    if(i==0){
      afficheSuiv(piece, grille); //Si on est au début du tableau, alors on affiche le cadre de droite
    }
    if (i == 5){
      printf("⎪\t\t");
      for (e = 0; e<7; e++){
        if (e==0 || e==6){
          printf("⌻");
        }
        else {
          printf("⎼⎼");
        }
      }
      printf("\n");
    }
    if (i>5){
      printf("⎪");
      if (i == 6){
        printf("\t\t NEXT PIECE"); //Aux lignes suivantes, on affiche les scores
      }
      if(i == 8){
        printf("\t\t Score joueur 1 : %d", score1);
      }
      if(i == 9){
        printf("\t\t Score joueur 2 : %d", score2);
      }
      printf("\n");
    }
  }
  for (i = 0; i<C+2; i++){ //Boucle qui permet d'afficher les bordures inférieures du cadre
    if (i==0 || i==C+1){
      printf("⌻");
    }
    else{
      printf("⎼⎼");
    }
  }
  printf("\n");
}

//Fait une copie du plateau
void tableauCopie(plateau grille, plateau grille2){
	int i, j;
  for(i = 0; i<L; i++){
    for(j = 0; j<C; j++){
      grille2[i][j] = grille[i][j]; //La seconde grille récupère les coordonnées de la première pour la copie
    }
  }
}
