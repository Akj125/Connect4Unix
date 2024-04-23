#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include "../headers/exceptionsJeu.h"
#include "../headers/jeu.h"

/*
Connect 4
Auteurs: Alec Jones et Mathieu Richard

Ce programme est une implémentation du jeu Connect 4 en C++. Le jeu se joue entre deux joueurs, l'un représenté par un 'X' et l'autre par un 'O'.
Les joueurs prennent des tours pour placer leur jeton dans une colonne de leur choix. Le but du jeu est d'aligner 4 jetons de la même couleur.
Les jetons peuvent être alignés horizontalement, verticalement ou en diagonale.

Le joueur 'O' est contrôlé par l'ordinateur qui utilise une fonction heuristique simple pour choisir la colonne où placer son jeton.

Pour jouer, le joueur entre le numéro de la colonne où il souhaite placer son jeton. Les colonnes sont numérotées de 1 à 7.
Le jeu est affiché dans la console.

Structure du programme :
1. Initialisation du jeu : Le plateau de jeu est préparé et les joueurs sont initialisés.
2. Création des processus fils : Deux processus fils sont créés, un pour le joueur utilisateur et un pour le joueur ordinateur.
3. Boucle de jeu : Le jeu continue en boucle, les joueurs prenant des tours pour placer leurs jetons. Après chaque mouvement, l'état du jeu est vérifié.
4. Fin du jeu : Le jeu se termine lorsqu'un joueur a aligné 4 jetons ou que le plateau de jeu est plein. Le résultat est affiché dans la console.

Les processus fils passent les coordonnées de la colonne où ils veulent placer leur jeton entre eux après chaque tour.
Après chaque modification de la grille, le jeu vérifie si un joueur a gagné ou si la grille est pleine.
Si c'est le cas, le jeu se termine et le joueur gagnant (ou un match nul) est affiché.
*/

int main()
{   
    int scoreUtilisateur = 0;
    int scoreOrdinateur = 0;
    bool encore = true;

    while (encore) 
    {
        // Initialisation des tubes
        int fds1[2]; // Utilisateur -> Ordinateur
        int fds2[2]; // Ordinateur -> Utilisateur
        int fds3[2]; // Utilisateur/Ordinateur -> Père
        pipe(fds1);
        pipe(fds2);
        pipe(fds3);

        pid_t utilisateur = fork();
        
        // L'utilisateur sera le processus principal, il prendra charge de l'affichage du jeu
        if (utilisateur == 0)
        {
            jeu jeuUtilisateur;
            close(fds1[0]);
            close(fds2[1]);
            close(fds3[0]);
            

            // Boucle partielle iniial

            // Afficher la grille
            jeuUtilisateur.afficher_grille();

            int colonne;
            while (true)
            {
                // Attendre que le joueur entre un numéro de colonne
                std::cout << "Entrez le numéro de la colonne dans laquelle vous voulez placer votre jeton: ";
                std::cin >> colonne;
                colonne--;

                try
                {
                    jeuUtilisateur.placer_jeton(colonne, 'X');
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
            write(fds1[1], &colonne, sizeof(colonne));


            // Boucle de jeu
            while (true)
            {
                // Lire la colonne choisie par l'ordinateur
                read(fds2[0], &colonne, sizeof(colonne));
                if (colonne == -1) // signal kill pour finir le jeu
                {
                    exit(0);
                }

                // Placer le jeton de l'ordinateur dans la colonne choisie et obtenir la range
                int range = jeuUtilisateur.placer_jeton(colonne, 'O');
                char resultat = jeuUtilisateur.verifier(colonne, range);

                // Vérifier si l'ordinateur a gagné
                if (resultat == 'O')
                {
                    std::cout << "L'ordinateur a gagné!" << std::endl;
                    jeuUtilisateur.afficher_grille();

                    // Envoyer un signal kill pour terminer le jeu
                    colonne = -1;
                    write(fds1[1], &colonne, sizeof(colonne));
                    write(fds3[1], &resultat, sizeof(resultat));

                    exit(0);
                }

                // Si la grille est pleine alors c'est une égalité
                else if (resultat == 'f')
                {
                    std::cout << "Égalité, la grille est pleine!" << std::endl;

                    // Envoyer un signal kill pour terminer le jeu
                    colonne = -1;
                    write(fds1[1], &colonne, sizeof(colonne));
                    write(fds3[1], &resultat, sizeof(resultat));
                    exit(0);
                }
                

                // Afficher la grille
                jeuUtilisateur.afficher_grille();

                while (true)
                {
                    // Attendre que le joueur entre un numéro de colonne
                    std::cout << "Entrez le numéro de la colonne dans laquelle vous voulez placer votre jeton: ";
                    std::cin >> colonne;
                    colonne--;

                    try
                    {
                        jeuUtilisateur.placer_jeton(colonne, 'X');
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
                write(fds1[1], &colonne, sizeof(colonne));
            }

        }

        pid_t ordinateur = fork();

        if (ordinateur == 0)
        {
            jeu jeuOrdinateur;
            close(fds1[1]);
            close(fds2[0]);
            close(fds3[0]);
            
            // Boucle de jeu
            while (true)
            {
                int colonne;

                // Lire la colonne choisie par le joueur
                read(fds1[0], &colonne, sizeof(colonne));
                if (colonne == -1) // signal kill pour finir le jeu
                {
                    exit(0);
                }

                // Placer le jeton de l'utilisateur dans la colonne choisie et obtenir la range
                int range = jeuOrdinateur.placer_jeton(colonne, 'X');

                char resultat = jeuOrdinateur.verifier(colonne, range);

                // Vérifier si l'utilisateur a gagné
                if (resultat == 'X')
                {
                    std::cout << "Vous avez gagné!" << std::endl;
                    jeuOrdinateur.afficher_grille();

                    // Envoyer un signal kill pour terminer le jeu
                    colonne = -1;
                    write(fds2[1], &colonne, sizeof(colonne));
                    write(fds3[1], &resultat, sizeof(resultat));

                    exit(0);
                }
                // Si la grille est pleine alors c'est une égalité
                else if (resultat == 'f')
                {
                    std::cout << "Égalité, la grille est pleine!" << std::endl;

                    // Envoyer un signal kill pour terminer le jeu
                    colonne = -1;
                    write(fds2[1], &colonne, sizeof(colonne));
                    write(fds3[1], &resultat, sizeof(resultat));

                    exit(0);
                }

            while (true)
            {
                // Choisir une colonne aléatoire pour placer le jeton
                colonne = jeuOrdinateur.selection_ia();

                    // Placer le jeton de l'ordinateur dans la colonne choisie et obtenir la range
                    try
                    {
                        jeuOrdinateur.placer_jeton(colonne, 'O');
                    }
                    catch(colonnePleineException &e)
                    {
                        continue;
                    }
                    break;
                }
                

                // Envoyer la colonne choisie par l'ordinateur à l'utilisateur
                write(fds2[1], &colonne, sizeof(colonne));
            }
        }

        // Fermer les descripteurs de fichiers inutilisés
        close(fds1[0]);
        close(fds1[1]);
        close(fds2[0]);
        close(fds2[1]);
        close(fds3[1]);

        // Le père attend la fin des deux fils
        wait(NULL);
        wait(NULL);

        // Lire le résultat de la partie
        char resultat;
        read(fds3[0], &resultat, sizeof(resultat));
        if (resultat == 'X')
        {
            scoreUtilisateur++;
        }
        else if (resultat == 'O')
        {
            scoreOrdinateur++;
        }

        // Sauvegarder le score
        std::ofstream fichier("score.txt");
        fichier << "utilisateur: " << scoreUtilisateur << std::endl;
        fichier << "ordinateur: " << scoreOrdinateur << std::endl;
        fichier.close();

        std::cout << "Score: " << scoreUtilisateur << " - " << scoreOrdinateur << std::endl;

        // Demander si le joueur veut continuer à jouer
        char continuer;
        std::cout << "Jouer une autre partie? (o/n): ";
        while (true)
        {
            std::cin >> continuer;
            if (continuer == 'n')
            {
                encore = false;
            }
            else if (continuer != 'o')
            {
                std::cout << "Entrez 'o' pour continuer ou 'n' pour arrêter: ";
                continue;
            }
            break;
        }
        

        
    }

}


