#pragma once
#include <array>

/*
La classe jeu sert à gérer le jeu de connect 4. Elle contient les méthodes pour jouer une partie de connect 4.
*/

class jeu
{
private:
    // La grille de jeu 6 x 7
    // '*' représente une case vide
    // 'X' représente un jeton du joueur
    // 'O' représente un jeton de l'ordinateur
    char grille[6][7];
public:
    jeu();

    // Affiche la grille de jeu
    void afficher_grille();

    // Place un jeton dans la colonne choisie
    int placer_jeton(int colonne, char jeton);

    // Vérifie si un joueur a gagné ou si la grille est pleine
    char verifier(int colonne, int range);

    int etats_du_jeu();
};