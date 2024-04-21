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

    char jeton;

    // Verifie les range
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 3; j++) {
            jeton = grille[i][j]; 
            if (jeton == grille[i][j + 1] && jeton == grille[i][j + 2] && jeton == grille[i][j + 3] && jeton != '*') {
                return jeton;
            }
            
        }
    }

    //Verifie les colonnes
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < 2; i++) {
            jeton = grille[i][j]; 
            if (jeton == grille[i + 1][j] && jeton == grille[i + 2][j] && jeton == grille[i + 3][j] && jeton != '*') {
                return jeton;
            }
            
        }
    }

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

    return 'f';
    
}

int jeu::etats_du_jeu(){

    // initialise le score que l'IA donnera a la grille 
    int score = 0; 

    // calcule le score pour les range
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j > 3; j++) {
            int Jcount = 0;
            int Ocount = 0;
            for (int k = 0; k < 4; k++)
            {
                if (grille[i][j + k] == 'X') {
                    Jcount++;
                } else if (grille[i][j + k] != 'O') {
                    Ocount++;
                }
            } 
            if (Jcount > 0 && Ocount == 0){
                score += Jcount * Jcount;
            } 
            else if (Ocount > 0 && Jcount == 0){
                score -= Ocount * Ocount;
            }
                
        }
    }

    //Verifie les colonnes
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 6; j++) {
            int Jcount = 0;
            int Ocount = 0;
            for (int k = 0; k < 4; k++)
            {
                if (grille[i][j + k] == 'X') {
                    Jcount++;
                } else if (grille[i][j + k] != 'O') {
                    Ocount++;
                }
            }
            if (Jcount > 0 && Ocount == 0){
                score += Jcount * Jcount;
            } 
            else if (Ocount > 0 && Jcount == 0){
                score -= Ocount * Ocount;
            }
                
        }
    }
    

    // renitialise le compteur et le jeton.
    char jeton = '*';
    int count = 0; 
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

}
