//
// Created by hugop on 27/05/2021.
//

#ifndef PUISSANCE_N_PROJET_JEU_H
#define PUISSANCE_N_PROJET_JEU_H

/**
 * Grid definit le plateau de jeu
 */
typedef struct {
    int largeur;
    int hauteur;
    char** grille;
} Grid;

/**
 * Regles permet d'afficher les regles du Puissance N
 */
void Regles();

/**
 * Option permet de choisir une option de lancement de partie
 * @return le choix de l'utilisateur
 */
int Option();

/**
 * Parametre sert parametrer une nouvelle partie
 * @param Nbr_joueur est le nombre de joueur dans la partie
 * @param num_j est le joueur qui commence à jouer
 * @param plateau est le plateau de jeu
 */
void Parametre(int* Nbr_joueur, int* num_j,Grid* plateau);

/**
 * Option_play permet à l'utilisateur de choisir une action (ajouter ou retirer un jeton)
 * @param plateau est le plateau de jeu
 * @return le choix de l'utilisateur
 */
int Option_play(Grid *plateau);

/**
 * Show_grid affiche la grille de jeu
 * @param plateau est le plateau de jeu
 */
void Show_grid(Grid plateau);

/**
 * Add_token ajoute un jeton dans le plateau de jeu
 * @param plateau est le plateau de jeu
 * @param colonne est la colonne choisit par l'utilisateur
 * @param num_j est le joueur qui joue
 * @param blocage colonne bloqué si un jeton est retirer
 * @return si l'ajout est possible ou non
 */
int Add_token(Grid plateau, int colonne, int num_j, int* blocage);

/**
 * Bot_token est un programme aleatoire qui permet de jouer au jeu tout seul
 * @param plateau est le plateau de jeu
 * @param num_j est la personne entrain de jouer
 * @param blocage colonne bloqué si un jeton est retirer
 */
void Bot_token(Grid *plateau, int num_j, int* blocage);

/**
 * Remove_token retire un jeton dans le plateau de jeu
 * @param plateau est le plateau de jeu
 * @param colonne est la colonne choisit par l'utilisateur
 * @param blocage est la colonne qui sera bloqué
 * @return
 */
int Remove_token(Grid plateau, int colonne, int* blocage);

/**
 * Check_winner permet de savoir si un joueur a gagné
 * @param plateau est le plateau de jeu
 * @return le joueur qui a gagné
 */
int Check_winner(Grid* plateau);

/**
 *Check_direction permet de regarder dans toutes les direction autour du jeton
 * @param plateau est le plateau de jeu
 * @param ligne est la ligne du jeton
 * @param colonne est la colonne du jeton
 * @param dirX
 * @param dirY
 * @param jeton est le jeton observé
 * @return 1 s'il y a assez de jeton aligné pour gagner
 */
int check_direction(Grid *plateau,int ligne,int colonne,int dirX,int dirY, char jeton);

/**
 *Jouer defnit qui est en train de jouer et permet la construction de la partie
 * @param plateu est le plateau de jeu
 * @param num_j est le joueur en train de jouer
 * @param blocage est la colonne bloqué si un jeton est retiré
 * @param Nbr_joueur est le nombre de joueurs dans la partie
 * @return EXIT_SUCCESS si l'utilisateur choisit de sauvegader et quitter le jeu
 */
int Jouer (Grid plateu, int num_j, int* blocage, int Nbr_joueur);

/**
 *Save permet de sauvegarder le plateau et le joueur en train de jouer dans un ficher texte
 * @param plateau est le plateau de jeu
 * @param num_j est le joueur qui est en train jouer
 * @param blocage est la colonne bloqué si un jeton est retiré
 */
void Save (Grid plateau, int num_j, int blocage);

/**
 *Load permet d'initialiser la partie avec les parametres sauvegardés dans le fichier
 * @param plateau est le plateau de jeu
 * @return Players qui va jouer en premier
 */
int Load (Grid* plateau,int *blocage);

/**
 *Verification de la derniere ligne du tableau
 * @param plateau est le plateau de jeu
 * @return 1 si la derniere ligne du tableau est vide
 */
int Verification(Grid *plateau);

#endif //PUISSANCE_N_PROJET_JEU_H