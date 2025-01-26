#include <stdio.h>
#include <stdlib.h>
#include "Jeu.h"

int main() {
    int Nbr_joueur=0, num_j=0, blocage=-1;
    Grid plateau;

    Regles();

    switch(Option()){ /// Choix de  l'utilisateur

        case 1: /// l'utilisateur jouera contre un ordinateur

            Parametre(&Nbr_joueur, &num_j, &plateau); /// Cette fonction sert à parametrer une nouvelle partie
            Jouer(plateau, num_j, &blocage, Nbr_joueur); /// La fonction jouer definit qui est entrain de jouer et permet la construction de la partie

            break;

        case 2: /// l'utilisateur jouera contre une autre personne

            num_j=Load(&plateau, &blocage); /// Charge la personne qui a joué

            printf("\nVoulez vous jouer contre un ordinateur (tapez 1) ? Ou voulez vous jouer contre une autre personne (tapez 2) ?\n"); /// Demande à l'utilisateur s'il veut jouer tout seul ou a deux
            scanf("%d",&Nbr_joueur);

            while(Nbr_joueur!=1 && Nbr_joueur!=2 ){ /// Message d'erreur qui verifie le nombre de joueurs
                printf("Erreur!\nVoulez vous jouer contre un ordinateur (tapez 1) ? Ou voulez vous jouer contre une autre personne (tapez 2) ?\n");
                scanf("%d",&Nbr_joueur);
            }

            if(blocage<=-1){
                printf("Aucune colonne est bloquee.\n");
            }else{
                printf("La colonne %d est bloquee.\n",blocage+1);
            }

            if(num_j==1){/// Annonce le joueur qui recommence à jouer
                printf("Le joueur 1 commence, avec les jetons jaunes (representes par un 'X').\n");
            }else{
                printf("Le joueur 2 commence, avec les jetons rouges (representes par un 'O').\n");
            }

            Jouer(plateau, num_j, &blocage, Nbr_joueur); /// La fonction jouer definit qui est entrain de jouer et permet la construction de la partie
            break;

        default: /// Quitte le jeu

            printf("Merci d'avoir joue !\n");
            break;
    }

    free(plateau.grille); /// Supprime le plateau de jeu

    return 0;
}