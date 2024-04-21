#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <../headers/exceptionsJeu.h>
#include "../headers/jeu.h"

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
    pipe(fds);

    pid_t utilisateur = fork();
    
    // L'utilisateur sera le processus principal, il prendra charge de l'affichage du jeu
    if (utilisateur == 0)
    {
        jeu jeuUtilisateur = jeu('X');
        

        // Boucle partielle iniial

        // Afficher la grille
        jeuUtilisateur.afficher_grille();

        int colonne;
        while (true)
        {
            // Attendre que le joueur entre un numéro de colonne
            std::cout << "Entrez le numéro de la colonne dans laquelle vous voulez placer votre jeton: ";
            std::cin >> colonne;

            try
            {
                jeuUtilisateur.placer_jeton(colonne);
            }
            catch (colonneInvalideException &e)
            {
                std::cout << e.what() << std::endl;
                continue;
            }
            catch (colonnePleineException &e)
            {
                std::cout << e.what() << std::endl;
                continue;
            }
            break;
        }
    

        // Envoyer la colonne choisie par le joueur à l'ordinateur
        write(fds[1], &colonne, sizeof(colonne));


        // Boucle de jeu
        while (true)
        {
            // Lire la colonne choisie par l'ordinateur
            read(fds[0], &colonne, sizeof(colonne));
            if (colonne == -1) // signal kill pour finir le jeu
            {
                break;
            }

            // Placer le jeton de l'ordinateur dans la colonne choisie et obtenir la range
            int range = jeuUtilisateur.placer_jeton(colonne);

            // Vérifier si l'ordinateur a gagné
            if (jeuUtilisateur.verifier(colonne, range) == 'O')
            {
                std::cout << "L'ordinateur a gagné!" << std::endl;

                // Envoyer un signal kill pour terminer le jeu
                colonne = -1;
                write(fds[1], &colonne, sizeof(colonne));

                break;
            }
            // Si la grille est pleine alors c'est une égalité
            else if (jeuUtilisateur.verifier(colonne, range) == 'f')
            {
                std::cout << "Égalité, la grille est pleine!" << std::endl;

                // Envoyer un signal kill pour terminer le jeu
                colonne = -1;
                write(fds[1], &colonne, sizeof(colonne));

                break;
            }
            

            // Afficher la grille
            jeuUtilisateur.afficher_grille();

            while (true)
            {
                // Attendre que le joueur entre un numéro de colonne
                std::cout << "Entrez le numéro de la colonne dans laquelle vous voulez placer votre jeton: ";
                std::cin >> colonne;

                try
                {
                    jeuUtilisateur.placer_jeton(colonne);
                }
                catch (colonneInvalideException &e)
                {
                    std::cout << e.what() << std::endl;
                    continue;
                }
                catch (colonnePleineException &e)
                {
                    std::cout << e.what() << std::endl;
                    continue;
                }
                break;
            }

            // Envoyer la colonne choisie par le joueur à l'ordinateur
            write(fds[1], &colonne, sizeof(colonne));
        }

    }

    pid_t ordinateur = fork();

    if (ordinateur == 0)
    {
        jeu jeuOrdinateur = jeu('O');
        
        // Boucle de jeu
        while (true)
        {
            int colonne;

            // Lire la colonne choisie par le joueur
            read(fds[0], &colonne, sizeof(colonne));
            if (colonne == -1) // signal kill pour finir le jeu
            {
                break;
            }

            // Placer le jeton de l'utilisateur dans la colonne choisie et obtenir la range
            int range = jeuOrdinateur.placer_jeton(colonne);

            char resultat = jeuOrdinateur.verifier(colonne, range);

            // Vérifier si l'utilisateur a gagné
            if (resultat == 'X')
            {
                std::cout << "Vous avez gagné!" << std::endl;

                // Envoyer un signal kill pour terminer le jeu
                colonne = -1;
                write(fds[1], &colonne, sizeof(colonne));

                break;
            }
            // Si la grille est pleine alors c'est une égalité
            else if (resultat == 'f')
            {
                std::cout << "Égalité, la grille est pleine!" << std::endl;

                // Envoyer un signal kill pour terminer le jeu
                colonne = -1;
                write(fds[1], &colonne, sizeof(colonne));

                break;
            }

            // Choisir une colonne aléatoire pour placer le jeton
            colonne = rand() % 7 + 1;

            // Placer le jeton de l'ordinateur dans la colonne choisie et obtenir la range
            jeuOrdinateur.placer_jeton(colonne);

            // Envoyer la colonne choisie par l'ordinateur à l'utilisateur
            write(fds[1], &colonne, sizeof(colonne));
        }
    }

    // Fermer les descripteurs de fichiers inutilisés
    close(fds[0]);
    close(fds[1]);

    // Le père attend la fin des deux fils
    wait(NULL);
    wait(NULL);
}


