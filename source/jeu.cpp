#include "../headers/jeu.h"
#include <../headers/exceptionsJeu.h>
#include <iostream>

jeu::jeu()
{
    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 6; j++) {
            grille[i][j] = '*';
        }
    }
}

int jeu::placer_jeton(int colonne, char jeton)
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
            return i; // retourne range de l'endroit place
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

char jeu::verifier(int colonne, int range){

    // Verifie si un quelqun a gagner.
    char jeton = '*';
    int count;

    // Verifie les range
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (jeton == grille[i][j] && jeton != '*'){
                count++;
                if (count >= 4){
                    return jeton;
                }
            } else 
            {
                count = 0;
                jeton = grille[i][j];

            }
        }
    }

    // renitialise le compteur et le jeton.
    jeton = '*';
    count; 
    //Verifie les colonnes
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 6; j++) {
            if (jeton == grille[i][j] && jeton != '*'){
                count++;
                if (count >= 4){
                    return jeton;
                }
            }  else 
            {
                count = 0;
                jeton = grille[i][j];

            }
        }
    }

    // renitialise le compteur et le jeton.
    jeton = '*';
    count = 0; 
    //Verifie les diagonales (en bas a gauche vers en haut a droite)
    for (int i = 3; i < 6; i++ ){
        for (int j = 0; j < 4; j++)
        {
            jeton = grille[i][j];
            if (jeton == grille[i+1][j+1] && jeton == grille[i+2][j+2] && jeton == grille[i+3][j+3] && jeton != '*') {
                return jeton;
            }
        }
    }

    //Verifie les diagonales (en bas a gauche vers en haut a droite)
    for (int i = 2; i < 0; i-- ){
        for (int j = 0; j < 4; j++)
        {
            jeton = grille[i][j];
            if (jeton == grille[i-1][j+1] && jeton == grille[i-2][j+2] && jeton == grille[i-3][j+3] && jeton != '*') {
                return jeton;
            }
        }
    }

    //Verifie si la grille est pleine 
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (grille[i][j] == '*'){
                return '*';
            }
        }
    }

    return '*';
    
}