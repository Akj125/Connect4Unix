#include "../headers/jeu.h"
#include "../headers/exceptionsJeu.h"
#include <iostream>

jeu::jeu()
{
    for(int i = 0; i < 6; i++) {
        for(int j = 0; j < 7; j++) {
            grille[i][j] = '*';
        }
    }
}

int jeu::placer_jeton(int colonne, char jeton)
{
    // Vérifier si la colonne est valide
    if (colonne < 0 || colonne > 7)
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
    return -1;
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
        for (int j = 0; j < 4; j++) {
            jeton = grille[i][j]; 
            if (jeton == grille[i][j + 1] && jeton == grille[i][j + 2] && jeton == grille[i][j + 3] && jeton != '*') {
                return jeton;
            }
            
        }
    }

    //Verifie les colonnes
    for (int j = 0; j < 7; j++) {
        for (int i = 0; i < 3; i++) {
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
            if (jeton == grille[i-1][j+1] && jeton == grille[i-2][j+2] && jeton == grille[i-3][j+3] && jeton != '*') {
                return jeton;
            }
        }
    }

    //Verifie les diagonales (en haut a gauche vers en bas a droite)
    for (int i = 0; i < 3; i++ ){
        for (int j = 0; j < 4; j++)
        {
            jeton = grille[i][j];
            if (jeton == grille[i+1][j+1] && jeton == grille[i+2][j+2] && jeton == grille[i+3][j+3] && jeton != '*')  {
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

int jeu::etats_du_jeu(char tempGrille[6][7], int colonne, int range){
    
    for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                std::cout << tempGrille[i][j] << "-";
            }
            std::cout << std::endl;
        }

    // initialise le score que l'IA donnera a la grille 
    int score = 0; 

    // // calcule le score pour les range
    //     for (int j = std::max(0, colonne - 3); j <= std::min(colonne, colonne + 3);  j++) {
    //         int Jcount = 0;
    //         int Ocount = 0;
    //         for (int k = 0; k < 4; k++)
    //         {
    //             if (tempGrille[range][j + k] == 'X') {
    //                 Jcount++;
    //             } else if (tempGrille[range][j + k] == 'O') {
    //                 Ocount++;
    //             }
    //         } 
    //         if (Ocount == 4 || Jcount == 3){
    //             score = 10000;
    //         } 
    //         else if (Jcount >= 2 && Ocount == 1){
    //             score = 5000;
    //         } 
    //         else if (Ocount > 0 && Jcount == 0){
    //             score += Ocount * Ocount;
    //         }
    //         else if (Jcount > 0 && Ocount == 0){
    //             score -= Jcount * Jcount;
    //         } 
                
    //     }


    //     //Verifie les colonnes
    //     int Jcount = 0;
    //     int Ocount = 0;
    //     for (int k = 0; k < 4; k++)
    //     {
    //         if (tempGrille[range + 3 - k][colonne] == 'X') {
    //             Jcount++;
    //             Ocount = 0;
    //         } else if (tempGrille[range + 3 - k][colonne] == 'O') {
    //             Ocount++;
    //             //Jcount = 0;
    //         }
    //     }

    //     if (Ocount == 4 || Jcount == 3){
    //         score = 10000;
    //     } 
    //     else if (Ocount == 3){
    //         score += Ocount * Ocount;
    //     } 
    //     else if (Ocount == 2 ){
    //         score += Ocount * Ocount;
    //     }
    //     else if (Ocount == 1){
    //         score += Ocount * Ocount;
    //     } 
    //     
                
    

    // // renitialise le compteur et le jeton.
    char jeton;

    //Verifie les diagonales (en bas a gauche vers en haut a droite) (3,6) (0,4)
    std::cout << "Colonne: " << colonne << ", Range: " << range << std::endl;
    for (int j = std::max(0, colonne - 3); j < colonne + 1; j++)
    {
        std::cout << "j :" << j << std::endl;
        int Jcount = 0;
        int Ocount = 0;
        for (int k = 0; k < 4; k++)
        {
            std::cout << "x : " << j + k << ", y: " <<  range - k + j << std:: endl;
            if (range - k + j > 5 || range - k + j < 0){
                continue;
            }
            if (tempGrille[range - k + j][j + k] == 'X') {
                Jcount++;
            } else if (tempGrille[range - k + j][j + k] == 'O') {
                Ocount++;
            }
        }
        // if (Jcount > 0 && Ocount == 0){
        //     score -= Jcount * Jcount;
        // } 
        // else if (Ocount > 0 && Jcount == 0){
        //     score += Ocount * Ocount;
        // }
        // else if (Ocount == 4 || Jcount == 3){
        //     score = 10000;
        // }
        std::cout << "Jcount: " << Jcount << ", Ocount: " << Ocount << std::endl;
    }



    // //Verifie les diagonales (en haut a gauche vers en bas a droite)
    // for (int i = 0; i < 3; i++ ){
    //     for (int j = 0; j < 4; j++)
    //     {
    //         int Jcount = 0;
    //         int Ocount = 0;
    //         for (int k = 0; k < 4; k++)
    //         {
    //             if (tempGrille[i + k][j + k] == 'X') {
    //                 Jcount++;
    //             } else if (tempGrille[i + k][j + k] != 'O') {
    //                 Ocount++;
    //             }
    //         }
    //         if (Jcount > 0 && Ocount == 0){
    //             score += Jcount * Jcount;
    //         } 
    //         else if (Ocount > 0 && Jcount == 0){
    //             score += Ocount * Ocount;
    //         } 
    //         // else if (Ocount == 4 || Jcount == 3){
    //         //     score = 10000;
    //         // }
    //     }
    // }
    return score;
}

int jeu::selection_ia(){
    
    char tempGrille[6][7];
    int meil_score = 0;
    int meil_col = -1;
    for (int colonne = 0; colonne < 7; colonne++){

        int range; 

        // Copy grille vers temp grille pour permetre de tester la grille sans modifier la vrai. 
        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 7; ++j) {
                tempGrille[i][j] = grille[i][j];
            }
        }

        if (tempGrille[0][colonne] != '*'){
             std::cout << "skiped" << std::endl;
             continue;
        }

        for (int j = 5; j >= 0; j--)
        {
            if (tempGrille[j][colonne] == '*')
            {
                tempGrille[j][colonne] = 'O'; //Place un jeton dans la grille temporaire
                range = j;
                break;
            }
        }
                

        int temp_score = etats_du_jeu(tempGrille, colonne, range);
        std::cout << temp_score << std::endl;
        if (temp_score > meil_score) {
            
            meil_score = temp_score;
            meil_col = colonne;
            
        }

        

    }

    if (meil_score == 0) {
        meil_col = rand() % 7 + 1;
    }
    std::cout << "Score: " << meil_score << ", Best_Colonne : " << meil_col << std::endl;
    return meil_col;


}