#include <unistd.h>
#include <iostream>
#include "headers/jeu.h"

/*
Connect 4
Auteurs: Alec Jones et Matieu Richard

Ce programme est un jeu de connect 4. Le jeu se joue à deux joueurs, un joueur est représenté par un 'X' et l'autre par un 'O'.
Les joueurs alternent pour placer leur jeton dans une colonne de leur choix. Le but du jeu est d'aligner 4 jetons de sa couleur.
Les jetons peuvent être alignés horizontalement, verticalement ou en diagonale.

Le joueur 'O' est joué par l'ordinateur. Pour maintenant l'ordinateur est très simple et joue aléatoirement.

Pour jouer, le joueur doit entrer le numéro de la colonne dans laquelle il veut placer son jeton. Les colonnes sont numérotées de 1 à 7.
Le jeu est affiché dans la console.

Plan du programme:
1. Initialisation du jeu
2. Création du fils joueur utilisateur et du fils joueur ordinateur
3. Boucle de jeu
4. Fin du jeu

Les fils passeront des coordonnées de la colonne dans laquelle ils veulent placer leur jeton entre eux après chaque tour.
Après chaque modification de la grille, le jeu vérifiera si un joueur a gagné ou si la grille est pleine.
Si c'est le cas, le jeu se terminera et le joueur gagnant sera affiché.
*/

int main()
{
    // Initialisation du jeu
    int fds[2];

    pid_t utilisateur = fork();
    
    if (utilisateur == 0)
    {
        // Code du fils utilisateur
        jeu jeuUtilisateur = jeu('X');
        sleep(1);
    }

    pid_t ordinateur = fork();

    if (ordinateur == 0)
    {
        // Code du fils ordinateur
        jeu jeuOrdinateur = jeu('O');
        sleep(1);
    }

    // Code du père
}


