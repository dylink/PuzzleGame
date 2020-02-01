#include "plateau.h"

//Décale les lignes vers le bas
int decaleBas(plateau grille, int lignedefin){
	int i,j;
	for(i=lignedefin; i >= 0; i--){ //Ici, on commence par la dernière ligne car le décalage s'effectue vers le bas
		for(j=0;j <C;j++){
			grille[i][j] = grille[i-1][j]; //La ligne actuelle dans la boucle récupère les données de la ligne au-dessus d'elle
			if(i == 0){
				grille[i][j] = 0; //La première ligne se retrouve vide
			}
		}
	}
	return C; //Permet de donner le résultat du score, 1 points par case effacée
}

//Décale les colonnes vers la gauche
int decaleGauche(plateau grille, int coldedebut){
	int i,j;
	for(j=coldedebut; j <C; j++){//Ici, on commence par la première colonne car le décalage s'effectue vers la gauche
		for(i=0;i <L;i++){
			grille[i][j] = grille[i][j+1];//La colonne actuelle dans la boucle récupère les données de la colonne à sa droite
			if(j == C-1){
				grille[i][j] = 0; //La dernière colonne se retrouve vide
			}
		}
	}
	return L; //Permet de donner le résultat du score, 1 points par case effacée
}

//Détecte si une collision a lieu
int collision(plateau grille, const int piece[][5], int ligne, int colonne){
  int i, j;
  for(i=0; i<5; i++){
    for(j=0; j<5; j++){ //Boucle qui parcours la pièce (tableau de 5x5)
      if(piece[i][j] != 0){
        if(grille[ligne+i][colonne+j] != 0){
          return 1; //Si la donnée actuelle de la case est différente de 0 et qu'il y a une pièce dessus, alors il y a collision

          //(ligne+i et colonne+j car une pièce, quelque soit sa forme, débute à la case (0,0), hors dans le cas de la croix par exemple...

          //...sa première case se situe à la coordonnée (0,2), on ajoute donc la valeur actuelle de la boucle pour correspondre aux même coordonnées.)
        }
      }
    }
  }
  return 0;
}

//Détecte si la pièce est au bord droite du plateau
int horsPlateauD(plateau grille, const int piece[][5], int ligne, int colonne){
  int i, j;
  for(i=0; i<5; i++){
    for(j=0; j<5; j++){ //Boucle qui parcours la pièce (tableau de 5x5)
      if(piece[i][j] != 0){
        if(j+colonne == C-1){
          return 1; //Si la donnée de la case actuelle est différente de 0, et que cette dernière a une coordonnées égale au bord droite du plateau-1, alors la condition est valide
        }
      }
    }
  }
  return 0;
}

//Détecte si la pièce est au bord inférieur du plateau
int horsPlateauB(plateau grille, const int piece[][5], int ligne, int colonne){
  int i, j;
  for(i=0; i<5; i++){
    for(j=0; j<5; j++){ //Boucle qui parcours la pièce (tableau de 5x5)
      if(piece[i][j] != 0){
        if(i+ligne == L-1){
          return 1; //Si la donnée de la case actuelle est différente de 0, et que cette dernière a une coordonnées égale au bord inférieur du plateau-1, alors la condition est valide
        }
      }
    }
  }
  return 0;
}

//Efface les lignes complètes
int effaceLigne(plateau grille){
  int scoreH = 0, scoreV = 0, nbLignesH = 0, nbLignesV=0, copieI[L], copieJ[C];
  for(int i =0; i<L; i++){ //On commence par parcourir entièrement les colonnes, donc la première boucle concerne les lignes

    for(int j=C-1; j>=0; j--){ //Boucle où l'on parcours le plateau de la droite vers la gauche (ne fonctionne pas autrement)
      if(grille[i][j] != 0){
        if(j==0){
					copieI[nbLignesH] = i; //On copie donc la coordonnée correspondante à la ligne actuelle
					nbLignesH++; //Si les cases de la grille sont différentes de 0, et qu'on est parvenu jusqu'à j = 0, alors nous avons une ligne complète, on incrémente le compteur

        }
      }
      else{
        break; //Si les cases ne se suivent pas en étant différentes de 0, alors on arrête la boucle
      }
    }
  }
	for(int colonne =C-1; colonne>=0; colonne--){ //On commence par parcourir entièrement les lignes, donc la première boucle concerne les colonnes
		for(int ligne=0; ligne<L; ligne++){
			if(grille[ligne][colonne] != 0){
				if(ligne==L-1){
					copieJ[nbLignesV] = colonne; //On copie donc la coordonnée correspondante à la colonne actuelle
					nbLignesV++;//Si les cases de la grille sont différentes de 0, et qu'on est parvenu jusqu'à i = hauteur du plateau-1, alors nous avons une ligne complète, on incrémente le compteur

				}
			}
      else{
        break; //Si les cases ne se suivent pas en étant différentes de 0, alors on arrête la boucle
      }
		}
	}
	for(int r = 0; r<nbLignesH; r++){ //Boucle qui a pour limite le nombre de lignes complètes détectées
		scoreH += decaleBas(grille, copieI[r]); //Le score reçoit les points correspondants à l'effacement d'une ligne
	}
	for(int r2 = 0; r2<nbLignesV; r2++){ //Boucle qui a pour limite le nombre de colonnes complètes détectées

		scoreV+= decaleGauche(grille, copieJ[r2]); //Le score reçoit les points correspondants à l'effacement d'une colonne
	}
  return scoreV+scoreH; //La fonction retourne à l'arrivée le score total, dans le cas d'un combo
}

//Permet de donner forme aux pièces
void formePiece(plateau grille, const int tab[][5], int ligne, int colonne, int couleur){
  int x, y, i = ligne, j = colonne;
  for(x=0; x<5 ; x++){
    for(y=0 ; y<5 ; y++, j++){ //On parcours la pièce (tableau de 5x5)
      if (tab[x][y] != 0){
        grille[i][j]=couleur; //Si la valeur de la case est différente de 0, alors on affecte cette dernière à la grille pour voir apparaître la pièce
      }
    }
    j = colonne;
    i++; //On actualise les coordonnées correspondantes à la grille
  }
}
