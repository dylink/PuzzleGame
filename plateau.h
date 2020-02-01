#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include <termios.h>
#include <stdlib.h>
#include <time.h>



///Nombre de lignes
#define L 20
///Nombre de colonnes
#define C 20
//Le tableau doit faire au minimum une taille de 10x5

///Création d'un type "plateau" de taille C*L
typedef int plateau[L][C];

/*																			Fonctions de plateau																		*/

///Initialise le plateau
void initPlateau(plateau grille);
///Affiche la pièce suivante
void afficheSuiv(const int tab[][5], plateau grille);
///Affiche le plateau
void affichePlateau(plateau grille, const int tab[][5], int score1, int score2);
///Fait une copie du plateau
void tableauCopie(plateau grille, plateau grille2);

/*																			Fonctions de pièces																		*/

///Permet de donner forme aux pièces
void formePiece(plateau grille, const int tab[][5], int l, int c, int couleur);

/*																			Fonctions de points/déplacement de pièces																		*/

///Décale les lignes vers le bas
int decaleBas(plateau grille, int lignedefin);
///Décale les colonnes vers la gauche
int decaleGauche(plateau grille, int coldedebut);
///Détecte si une collision a lieu
int collision(plateau grille, const int piece[][5], int ligne, int colonne);
///Détecte si la pièce est au bord droite du plateau
int horsPlateauD(plateau grille, const int piece[][5], int ligne, int colonne);
///Détecte si la pièce est au bord inférieur du plateau
int horsPlateauB(plateau grille, const int piece[][5], int ligne, int colonne);
///Efface les lignes complètes
int effaceLigne(plateau grille);

/*																			Fonctions de jeu																		*/

///Détecte s'il n'y a plus d'espace disponible sur le plateau pour la pièce courant
int finPartie(plateau grille, const int piece[][5]);
///Boucle principale de jeu
void jeu(plateau grille, const int piece[][5], int l ,int c, int randomnumber, int joueur, int score1, int score2);
