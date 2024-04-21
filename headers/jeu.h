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
    std::array<std::array<char, 7>, 6> grille = {'*'};
    char jeton;
public:
    jeu(char jeton);

    // Affiche la grille de jeu
    void afficher_grille();

    // Place un jeton dans la colonne choisie
    int placer_jeton(int colonne);

    // Vérifie si un joueur a gagné ou si la grille est pleine
    char verifier(int colonne, int range);
};