//
// Created by hugop on 27/05/2021.
//
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Jeu.h"

void Regles(){

    /// Affiche les regles du jeu
    printf("////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
    printf("////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
    printf("//////////////////////////////////////////////// Puissance N ///////////////////////////////////////////////////////////");
    printf("////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////");
    printf("////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");

    printf("Bonjour et Bienvenue!\n\nLes regles du Puissance N sont assez simples. Le but est d'aligner N jetons de la meme couleur pour gagner.\nL'utilasateur peut alors decider de jouer contre un Bot ou alors de jouer contre un ami.\nA chaque tour de jeu, l'utilisateur pourra choisir entre 2 options:\n");
    printf("Ajouter un jeton dans une colonne au choix.\n");
    printf("Retirer un jeton d'une colonne, mais si cette option est choisit, la colonne sera bloquee pour\nle joueur suivant.\n");
    printf("\nMerci d'avoir lu ces regles et bon jeu !\n");

    printf("\n------------------------------------------------------------------------------------------\n\n");

}

int Option() {

    int option;

    ///Demande à l'utilisateur quel choix de démarrage il veut choisir
    printf("Que voulez-vous faire:\nDemarrer une nouvelle partie (tapez: 1)\nCharger une partie existante (tapez: 2)\nQuitter (tapez: un caractere)\nVotre choix:"); /// Demande à l'utilisateur de choisir une option de démarrage
    scanf("%d", &option);


    printf("\n------------------------------------------------------------------------------------------\n");

    return option;
}

void Parametre(int* Nbr_joueur, int* num_j, Grid* plateau){

    int N;

    printf("\nVoulez vous jouer contre un ordinateur (tapez 1) ? Ou voulez vous jouer contre une autre personne (tapez 2) ?\n"); ///Demande à l'utilisateur le nombre de joueur
    scanf("%d",Nbr_joueur);

    while(*Nbr_joueur!=1 && *Nbr_joueur!=2 ){ /// Verifie le nombre de joueur
        printf("Erreur!\nVoulez vous jouer contre un ordinateur (tapez 1) ? Ou voulez vous jouer contre une autre personne (tapez 2) ?\n");
        scanf("%d",Nbr_joueur);
    }

    printf("Combien de jetons doivent etre alignes pour gagner (entre 3 et 10) ?\n"); ///Demande à l'utilisateur le nombre de jetons a aligner pour gagner
    scanf("%d",&N);

    while(N<3 || N>10 ){ /// Verifie le nombre de jetons
        printf("Erreur!\nCombien de jetons doivent etre alignes pour gagner (entre 3 et 10) ?\n");
        scanf("%d",&N);
    }

    plateau->largeur=N+2; /// Initialise la taille du plateau
    plateau->hauteur=N+2;

    plateau->grille = (char**) malloc(sizeof(char*)*plateau->largeur); /// Initialise le plateau de jeu vide
    for (int i = 0; i<plateau->largeur; i++) {
        plateau->grille[i] = (char*) malloc(sizeof(char)*plateau->hauteur);
        for (int j = 0; j<plateau->hauteur; j++) {
            plateau->grille[i][j]='_';
        }
    }

    srand(time(0)) ; /// Choix aleatoire du joueur qui commence la partie
    *num_j = rand()%2+1 ;

    if(*num_j==1){ /// Affiche le joueur qui commence la partie
        printf("Le joueur 1 commence, avec les jetons jaunes (representes par un 'X').\n");
    }else{
        printf("Le joueur 2 commence, avec les jetons rouges (representes par un 'O').\n");
    }
    printf("\n------------------------------------------------------------------------------------------\n");
}

int Option_play(Grid *plateau){

    int play;

    /// Demande à l'utilisateur de faire une action
    printf("\nQue voulez-vous faire:\nAjouter un jeton (tapez 1)\nRetirer un jeton (tapez 2)\nSauvegarder et Quitter (tapez: un caractere)\nVotre choix:"); /// Demande à l'utilisateur de choisir une action
    scanf("%d", &play);

    while (play==2 && Verification(plateau)==1) { /// Empeche l'utilisateur d'enlever un jeton dans un plateau vide
        printf("Erreur plateau vide!\nQue voulez-vous faire:\nAjouter un jeton (tapez 1)\nRetirer un jeton (tapez 2)\nSauvegarder et Quitter (tapez 3)\n"
        );
        scanf("%d", &play);
    }

    return play;
}

void Show_grid(Grid plateau){

    int i, j, k;

    /// Ce double For permet de parcourir tout le plateau et de l'afficher avec les jetons
    for (i = 0; i<plateau.largeur; i++){
        for (j = 0; j<plateau.hauteur; j++){
            printf("| %c |", plateau.grille[i][j]);
        }
        printf("\n");
    }

    for(k=0; k<plateau.largeur; k++){ /// Permet d'afficher le numero associé à chaque colonne du plateau
        printf("| %d |", k+1);
    }

    printf("\n------------------------------------------------------------------------------------------");
}

int Add_token(Grid plateau, int colonne, int num_j, int* blocage) {

    int ligne = 0;

    if (plateau.grille[0][colonne] == '_' && colonne!=*blocage){ /// Empeche l'utilisateur d'ajouter un jeton dans une colonne pleine ou bloquée

        while (ligne !=plateau.largeur && plateau.grille[ligne][colonne] == '_') { /// Permet de faire descendre le jeton tant que la case est vide
            ligne++;
        }

        if (num_j == 1) { /// Permet de definir quel joueur a ajouté un jeton et donc de poser son jeton associé
            plateau.grille[ligne-1][colonne]='X';
        }else if (num_j == 0) {
            plateau.grille[ligne - 1][colonne] = 'O';
        }

        *blocage=-1; ///Retire la colonne bloquée

        return 1;
    }
    else {
        printf("Impossible !");
        return 0;
    }
}

void Bot_token(Grid *plateau, int num_j, int* blocage){

    int colonne, choix;

    srand(time(NULL));
    choix=rand()%3+1;

    /// Permet au bot d'enlever ou d'ajouter un jeton
    if (Verification(plateau)==0 && choix==2) { /// Empeche le bot d'enlever un jeton si le plateau de jeu est vide

        do { ///Permet de choisir une colonne valide afin d'y retirer un jeton

            colonne = rand() % plateau->largeur;

        } while (Remove_token(*plateau, colonne, blocage) == 0);

        printf("\nL'IA enleve un jeton dans la colonne %d.\n\n", colonne+1);

        *blocage=colonne; ///Define la colonne bloquée

    } else {

        do { ///Permet de choisir une colonne valide afin d'y ajouter un jeton

            colonne = rand() % plateau->largeur;

        } while (Add_token(*plateau, colonne, num_j, blocage) == 0);

        printf("\nL'IA ajoute un jeton dans la colonne %d.\n\n", colonne+1);

        *blocage=-1; ///Retire la colonne bloquée
    }
}

int Remove_token(Grid plateau, int colonne, int* blocage){
    int ligne = 0;

    while (ligne!=plateau.largeur && plateau.grille[ligne][colonne] == '_') { ///Permet de savoir ou est le plus haut jeton dans la colonne voulu de l'utilisateur
        ligne++;
    }

    if(ligne==plateau.largeur){ ///Verifie que la colonne est non vide
        return 0;
    }else{ ///Retire le plus haut jeton de la colonne et bloque la colonne
        plateau.grille[ligne][colonne]='_';
        *blocage=colonne;
        return 1;
    }

}

int check_direction(Grid *plateau,int ligne,int colonne,int dirX,int dirY, char jeton){

    int Row = ligne;
    int Col = colonne;
    int token = 0; /// Comteur de jetons de la même couleur alignés

    if (dirY == 0 && dirX == 0){ /// Evite au programme de compter le meme jeton plein de fois
        return 0;
    }

    do { /// Permet de verifier tous les jetons situés autour du jeton observé, si un jeton est de la meme couleur, alors le do while continue dans la meme direction
        token++;
        Row = Row + 1 * dirY;
        Col = Col + 1 * dirX;
    }while(Col < plateau->hauteur && Row < plateau->largeur && Col >= 0 && Row >= 0 && plateau->grille[Row][Col] == jeton && token < plateau->hauteur-2);

    if (token < plateau->hauteur-2){ /// Verifie si le nombre de jetons alignés est suffisant pour gagner

        return 0;
    }else {
        return 1;
    }
}

int Check_winner(Grid* plateau) {
    int ligne = 0; /// Compteur de lignes
    int colonne = 0; /// Compteur de colonnes
    int i, j;

    /// Ce double while permet de parcourir tout le plateau
    while (ligne < plateau->largeur) { ///Permet de faire varier  colonne du plateau de jeu
        while (colonne < plateau->hauteur) { ///Permet de faire varier la ligne du plateau de jeu

            if (plateau->grille[ligne][colonne] != '_') { /// Verifie si la case du plateau est vide ou non

                /// Ce double For permet de parcourir toutes les directions autour du jeton observé
                for (i = -1; i <= 1; i++) { ///Permet de faire varier la direction de dirX
                    for (j = -1; j <= 1; j++) {///Permet de faire varier la direction de dirY

                        if (check_direction(plateau, ligne, colonne,  i, j,plateau->grille[ligne][colonne]) == 1) { /// Verifie si un joueur a gagné

                            if (plateau->grille[ligne][colonne] == 'O') { ///Défini le joueur gagnant avec le case du plateau vérifié
                                return 0;
                            } else if (plateau->grille[ligne][colonne] == 'X') {
                                return 1;
                            }
                        }
                    }
                }
            }
            colonne++; /// augmente la colonne de 1 a chaque verification de jeton
        }
        colonne= 0; /// Reinitialise le nombre de la colonne
        ligne++; /// augmente la ligne de 1 a chaque verification des jetons dans une colonne
    }
    return -1;
}

int Jouer (Grid plateau, int num_j, int* blocage, int Nbr_joueur){

    int colonne; /// Correspond a la colonne choisit par l'utilisateur

    do {

        Show_grid(plateau);

        if( num_j%2==1 && Nbr_joueur==1){ /// Permet au bot de jouer si l'utilisateur a decidé de jouer tout seul

            Bot_token(&plateau, num_j%2, blocage);

        } else {

            switch (Option_play(&plateau)) { ///Choix de l'utilisateur

                case 1: /// Ajout d'un jeton

                    do { /// continue la partie tant que qu'il n'y a pas un gagnant ou que l'utilisateur est decidé d'arreter de jouer

                        printf("\nDans quelle colonne voulez vous ajouter votre jeton ?\n"); /// Demande à l'utilisateur de choisir une colonne
                        scanf("%d", &colonne);

                        printf("\n------------------------------------------------------------------------------------------\n");

                        while (colonne < 1 ||colonne >plateau.hauteur) { /// Message d'erreur si la colonne choisit n'est pas dans le tableau
                            printf("Erreur!\nDans quelle colonne voulez vous ajouter votre jeton ?\n");
                            scanf("%d", &colonne);

                            printf("\n------------------------------------------------------------------------------------------\n");
                        }


                    } while (Add_token(plateau, colonne - 1, num_j % 2, blocage) == 0); /// Permet de redemander la selection d'une colonne si celle-ci est invalide

                    break;

                case 2: /// Retrait d'un jeton

                    do {

                        printf("\nDans quelle colonne voulez vous enlever un jeton ?\n"); /// Demande à l'utilisateur de choisir une colonne
                        scanf("%d", &colonne);

                        printf("\n------------------------------------------------------------------------------------------\n");

                        while (colonne < 1 ||colonne >plateau.hauteur) { /// Message d'erreur si la colonne choisit n'est pas dans le tableau
                            printf("Erreur!\nDans quelle colonne voulez vous enlever un jetons ?\n");
                            scanf("%d", &colonne);

                            printf("\n------------------------------------------------------------------------------------------\n");
                        }


                    } while (Remove_token(plateau, colonne - 1, blocage) == 0); /// Permet de redemander la selection d'une colonne si celle-ci est invalide

                    break;

                default: /// Termine et Sauvegarde la partie dans un fichier Texte

                    Save(plateau, num_j % 2, *blocage); /// Sauvegarde la partie dans un fichier texte
                    printf("Merci d'avoir joue !\n");
                    return EXIT_SUCCESS; /// Termine la partie
            }
        }

        num_j++;

    }while(Check_winner(&plateau)==-1 && Verification(&plateau)!=-1);

    if (Check_winner(&plateau)==1){ /// Permet de dire à l'utilisateur qui est le joueur gagnant ou que la partie est fini sur une egalité
        printf("Bravo au joueur 1 !!! (represente par un 'X').\n");
    }else if(Check_winner(&plateau)==0){
        printf("Bravo au joueur 2 !!! (represente par un 'O').\n");
    } else if(Verification(&plateau)==-1){
        printf("Egalité!");
    }
}

void Save (Grid plateau, int num_j, int blocage){

    FILE* f = fopen("Sauvegarde.txt", "w"); /// Creation d'un fichier en mode écriture

    if(f != NULL){ /// Vérification de l'ouverture

        fprintf(f, "%d\n", num_j); /// Ecriture dans le fichier
        fprintf(f, "%d\n", blocage);
        fprintf(f, "%d\n", plateau.largeur);

        for (int i = 0; i<plateau.largeur; i++){ /// Sauvegarde le plateau de jeu dans un fichier texte
            for (int j = 0; j<plateau.hauteur; j++){
                fprintf(f,"%c", plateau.grille[i][j]);
            }
            fprintf(f,"\n");
        }
    }



    fclose(f); /// Fermeture du fichier
}

int Load (Grid* plateau, int* blocage){
    int ligne=0, colonne, Player=0, taille, num1,num2;
    char buffer[256]={0};

    FILE* f = fopen("Sauvegarde.txt", "r"); /// Ouverture du fichier sauvegarde en mode écriture

    if(f != NULL) { /// Vérification de l'ouverture
        while (fgets(buffer, 256, f) != 0) {

            taille = strlen(buffer) - 1; /// Definit la taille de la ligne dans le fichier sauvegarde
            buffer[taille] = '\0'; ///Initialisation de la ligne dans le fichier sauvegarde


            if(ligne==0) {

                Player=buffer[0]-'0'; /// Permet de savoir quel joueur recommence à jouer

            }else if(ligne==1){

                if(taille==1) {
                   *blocage =buffer[0] - '0';
                }else{
                    num1=buffer[0] - '0';
                    num2=buffer[1] - '0';
                    num1=num1*10+num2;
                   *blocage =num1;
                }

            }else if(ligne == 2){

                if(taille==1) {
                    plateau->largeur =buffer[0] - '0';
                    plateau->hauteur =buffer[0] - '0';
                }else{
                    num1=buffer[0] - '0';
                    num2=buffer[1] - '0';
                    num1=num1*10+num2;
                    plateau->largeur =num1;
                    plateau->hauteur =num1;
                }


                plateau->grille = (char**) malloc(sizeof(char*)*plateau->largeur); /// Initialisation du tableau de jeu sauvegarder
                for (int i = 0; i<plateau->largeur; i++) {
                    plateau->grille[i] = (char*) malloc(sizeof(char)*plateau->hauteur);
                    for (int j = 0; j<plateau->hauteur; j++) {
                        plateau->grille[i][j]='_';
                    }
                }

            } else {

                for(colonne=0; colonne<plateau->largeur; colonne++){ /// Remise en place du plateau stocker dans la Sauvegarde
                    plateau->grille[ligne-3][colonne]=buffer[colonne];
                }

            }

            ligne++; /// compteur de lignes

        }
    }

    fclose(f); /// Fermeture du fichier

    return Player;
}

int Verification(Grid *plateau) {
    int colonne1 = 0; /// compteur de colonnes qui verifie que la derniere est vide
    int colonne2=0;  /// compteur de colonnes qui verifie que la premiere colonne est vide

    while(colonne1<plateau->largeur && plateau->grille[(plateau->hauteur)-1][colonne1]=='_'){  ///Verfication que la derniere ligne du plateau de jeu soit non vide
        colonne1++;
    }

    while (colonne2 < plateau->largeur && plateau->grille[0][colonne2] != '_') {  ///Verfication que la premiere ligne du plateau de jeu soit non vide
        colonne2++;
    }

    if (colonne1 == plateau->largeur) { /// Permet de savoir si la derniere ligne est vide ou non
        return 1;
    } else if (colonne2 ==  plateau->largeur) { /// Permet de savoir si la premiere ligne est vide ou non
        return -1;
    } else {
        return 0;
    }
}