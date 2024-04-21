#include "../headers/jeu.h"
#include <../headers/exceptionsJeu.h>
#include <iostream>

jeu::jeu(char jeton)
{
    this->jeton = jeton;
}

void jeu::placer_jeton(int colonne)
{
    // Vérifier si la colonne est valide
    if (colonne < 0 || colonne > 6)
    {
        throw colonneInvalideException();
    }
    
    // Vérifier si la colonne est pleine
    if (grille[0][colonne] != '*')
    {
        throw colonnePleineException();
    }

    // Trouver la première case vide dans la colonne
    for (int i = 5; i >= 0; i--)
    {
        if (grille[i][colonne] == '*')
        {
            grille[i][colonne] = jeton;
            break;
        }
    }
}

void jeu::afficher_grille(){

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            std::cout << grille[i][j] << " ";
        }
        std::cout << std::endl;
    }

}