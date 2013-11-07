/*****************************************************************************************************/
/* Par       : Aurélien Delon										                        		 */
/*           : Dominic Blanchard																     */
/*           : Chuan Dong 																             */
/*			 : Olivier Goyette																		 */
/*                                                                                                   */
/* Revise le : 01/11/2013													                         */
/* Fichier   : Tp2.C												                            	 */
/*																		                             */
/* Description:  Ce module se compose de diverses fonctions servant au fonctionnement du programme   */
/*               de simulation.                                                                      */
/*					- afficher_terrain						Par: Aurelien Delon					     */
/*					- propager_un_feu	  					Par: Chuan Dong      Dominic Blanchard   */
/*					- allumer_nieme_arbre                   Par: Aurelien Delon  Dominic Blanchard	 */
/*					- afficher_cases_modifiees_terrain      Par: Aurelien Delon					     */
/*					- propager_feu_tout_terrain             Par: Aurelien Delon	 Dominic Blanchard   */
/*					- allumer_aleatoirement_arbre           Par: Aurelien Delon						 */
/*				    - simuler_un_feu_de_foret               Par: Aurelien Delon						 */
/*					- faire_simulation_groupee              Par: Aurelien Delon					     */
/*				    - faire_simulation_placement_aleatoire  Par: Aurelien Delon		                 */
/*				    - remplir_terrain					    Par: Olivier Goyette Dominic Blanchard	 */
/*                  - main()                                Par: Aurelien Delon  Chuan Dong          */
/*                                                                                                   */
/* Objectifs  : Ce module implante une simulation pour l'optimisation d'une plantation d'arbres.     */
/*                                                                                                   */
/*              Lorsque qu'un sylviculteur doit reboiser une pépinière de forme restangulaire        */
/*              pouvant accueillir jusqu'à (M) X (N) arbres. Sachant qu'il arrive fréquemment qu'un  */
/*              éclair frappe un arbre et que cela déclenche un feu de forêt. Il souhaite savoir     */
/*              commet il doit répartir les arbres de façon à maximiser le nombre d'arbres qui       */
/*              suivivront à un feu.                                                                 */
/*                                                                                                   */
/*****************************************************************************************************/


/*****************************************************************************************************/
/*							INCLUSION DE LIBRAIRIES							                         */
/*****************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <dos.h>
#include <time.h>
#include "module_feu.h"
#include "module_terrain.h"
#include "module_util.h"
#include "graph_io.h"


/*****************************************************************************************************/
/*							 DÉCLARATION DE FONCTIONS                                                */
/*****************************************************************************************************/
/*
	AFFICHER_TERRAIN

	Cette fonction affiche à l'écran l'état de toutes les cases du terrain reçu 
	
	PARAMÈTRES : 
					- terrain : Le terrain qu'on affiche l'état à l'écran   (type : t_terrain).

	VALEUR DE RETOUR :   Aucun.
*/
void afficher_terrain(t_terrain terrain);

/*
	PROPAGER_UN_FEU

	Cette fonction consulte toutes les cases (i,j) situées à plus ou moins DISTANCE_MAX_PROPAGATION
	cases des coordonnées (ligne, colonne). Si la case (i,j) contient un arbre, on calcul la 
	distance entres les cases (i,j) et on trouve la probabilité que le feu se propage entre celles-ci.
	On génére un nombre aléatoire réel et si celui-ci est inférieur à la propabilité, on enflamme
	l'arbre à la case (i,j).
	
	PARAMÈTRES : 
					- terrain : Pour consulter les cases du terrain               (type : t_terrain).
					- ligne   : La ligne (i) ou ce trouve la case à consulter     (type : int).
					- colonne : La colonne (j) où se trouve la case à consulter   (type : int).

	VALEUR DE RETOUR :   Aucun.
*/
void propager_un_feu(t_terrain terrain, int ligne, int colonne);


/*
	ALLUMER_NIEME_ARBRE

	Cette fonction parcourt toutes les cases du terrain et lorsqu'elle trouve le (n) arbre
	présent dans le terrain, elle l'enflamme.
	
	PARAMÈTRES : 
					- terrain : Pour consulter les cases du terrain  (type : t_terrain).
					- n       : Pour compter le nb d'arbres          (type : int).
	
	VALEUR DE RETOUR :   Aucun.
*/
void allumer_nieme_arbre(t_terrain terrain, int n);


/*
	AFFICHER_CASES_MODIFIEES_TERRAIN

	Cette fonction affiche à l'écran les cases du nouveau terrain dont l'état diffère
	de celui de l'ancien terrain.
	
	PARAMÈTRES : 
					- nouveau_terrain : Pour consulter les cases du nouveau terrain (type : t_terrain).
					- ancien_terrain  : Pour consulter les case de l'ancien terrain (type : t_terrain).
	
	VALEUR DE RETOUR :   Aucun.
*/
void afficher_cases_modifiees_terrain(t_terrain nouveau_terrain, t_terrain ancien_terrain);


/*
	PROPAGER_FEU_TOUT_TERRAIN

	Cette fonction fait une copie du terrain reçu. Elle remplace ensuite tous les feux présents
	dans la copie par un des arbres brûlés. Esuite, elle parcourt toutes les cases du terrain
	original et lorsqu'une case contient un feu, elle tente de le propager dans la copie. Elle
	se termine en remplaçant le contenu de terrain original par le contenu de la copie.
	
	PARAMÈTRES : 
					- terrain : Pour consulter le terrain afin de faire propager un feu (type : t_terrain).
	
	VALEUR DE RETOUR :   Aucun.
*/
void propager_feu_tout_terrain(t_terrain terrain);


/*
	ALLUMER_ALEATOIREMENT_ARBRE

	Cette fonction compte le nombre d'arbres présent dans le terrain. S'il y a eu au moins
	un arbre, elle choisit aléatoirement un nombre (n) dans l'intervalle [1, nb_arbre] et
	elle enflamme le énième arbre.
	
	PARAMÈTRES : 
					- terrain : Pour consulter l'état des case du terrain (type : t_terrain).
	
	VALEUR DE RETOUR :   Aucun.
*/
void allumer_aleatoirement_arbre(t_terrain terrain);


/*
	SIMULER_UN_FEU_DE_FORET

	Cette fonction choisit aléatoirement un arbre dans le terrain, l'enflamme, affiche le terrain
	et fait une courte pause. Ensuite, tant qu'il y a au moins un arbre en feu dans le terrain,
	elle fait une copie du terrain, elle propage les feux et elle met à jour le nombres d'arbres
	dans l'interface, puis elle affiche à l'écran l'état des cases qui ont été modifiées.
	
	PARAMÈTRES : 
					- terrain : Pour consulter l'état des cases (type : t_terrain).
	
	VALEUR DE RETOUR :   Aucun.
*/
void simuler_un_feu_de_foret(t_terrain terrain);


/*
	FAIRE_SIMULATION_GROUPEE

	Cette fonction tente de passer en mode graphique. En cas d'échec, elle retourne EXIT_FAILURE
	et se termine. En cas de succès, elle dessine l'interface graphique, génère un terrain où les
	arbres sont regroupés. Elle met à jour les informations dans l'iterface ( type de simulation,
	taille des groupes, distance entre les groupes, nombre initial d'arbres et nombre courant
	d'arbres). Ensuite, elle simule un feu de forêt, elle effectue une pause, elle ferme la 
	fenêtre graphique et elle retourne EXIT_SUCCCESS.
	
	PARAMÈTRES : 
					- taille_groupe   : Pour obtenir la taille d'un groupe d'arbre (type : int).
					- distance_groupe : Pour obtenir la distance d'un groupe (type : int).
										La distance ne doit pas dépasser DISTANCE_MAX_PROPAGATION
	VALEUR DE RETOUR :   
						- Elle retoune soit:   0: EXIT_SUCCESS  
											   1: EXIT_FAILURE   (type : int).
*/
int faire_simulation_groupee (int taille_groupes, int distance_groupes);


/*
	FAIRE_SIMULATION_PLACEMENT_ALEATOIRE

	Cette fonction tente de passer en mode graphique. En cas d'échec, elle retourne EXIT_FAILURE
	et se termine. En cas de succès, elle dessine l'interface graphique, génère un terrain où les
	arbres sont positionnés aléatoirement. Elle met à jour les informations dans l'iterface 
	( type de simulation, taille des groupes, distance entre les groupes, nombre initial d'arbres 
	et nombre courant d'arbres). Ensuite, elle simule un feu de forêt, elle effectue une pause, 
	elle ferme la fenêtre graphique et elle retourne EXIT_SUCCCESS.
	
	PARAMÈTRES : 
					- pourcentage_arbre : Pour obtenir le pourcentage désirer de la simulation
					                      qui se situe entre [0 et 1] exclusivement  (type : double).
	
	VALEUR DE RETOUR :   
						- Elle retoune soit:   0: EXIT_SUCCESS  
											   1: EXIT_FAILURE   (type : int).
*/
int faire_simulation_placement_aleatoire (double pourcentage_arbres);


/*
	REMPLIR_TERRAIN

	Cette fonction privée assigne l'état reçu à toute les cases du terrain
	
	PARAMÈTRES : 
					- terrain : Pour consulter les cases du terrain           (type : t_terrain).
					- etat    : Pour assigner une état aux cases du terrain   (type : t_etat).
	
	VALEUR DE RETOUR :   Aucun.
*/
static void remplir_terrain(t_terrain terrain,t_etat etat);


/*****************************************************************************************************/
/*								PROGRAMME PRINCIPAL	                                                 */
/*****************************************************************************************************/
int main (void)
{
	/* Lire la variable du choix, soit: de placement groupé ou aléatoire.							 */
	int type_positionnement; 
	/* Variable pour la taille d'un groupe d'arbres.												 */
	int taille_groupe_arbres;  
	/* Variable pour la distance choisie entre les diffÉrents groupes d'arbres.						 */
    int distance_entre_groupe_arbres;
	/* Variable du choix de (%) du terrain à recouvrir en mode aléatoire.							 */
	double pourcentage_terrain;       
	
	char message_choisir[] = "\n1 - Positionner les arbres aleatoirement\n2 - Grouper les arbres\n>";

    /* Initialisation du générateur de nombres aléatoires.											 */
    srand((unsigned int) time(NULL));
    rand();
    
	/* 
		On affiche les deux choix de positionnnement soit:     
												1:[Positionnement aléatoire] 
												2:[Grouper les arbre]
	   
		On demande à l'utilisateur d'entrer son choix, on itére autant de fois 
		qu'il n'a pas entré la bonne valeur.
	*/
	type_positionnement = entier_valide(1, 2, message_choisir, message_choisir);
	
	/* 
		Si l'utilisateur a choisi: positionner les arbres aléatoirement.
		On demande d'entrer le pourcentage désiré entre une valeur de [0 et 1}
		On itére autant de fois qu'il n'a pas entré la bonne valeur.
	*/
    if(type_positionnement == 1)
    {
		char message_pourcentage[] = 
			                   "\nQuel pourcentage du terrain doit etre couvert d'arbres <0...1> ?\n";
		char message_pourcentage_erreur[] = 
			                 "\nErreur : Nombre non valide, entez un nouveau pourcentage <0...1> ?\n";
     
		pourcentage_terrain = reel_valide(0, 1, message_pourcentage, message_pourcentage_erreur);

		/* On effectue la simulation pour le positionnement d'arbres aléatoire.						 */
		faire_simulation_placement_aleatoire(pourcentage_terrain);
    }

	/* 
		Si l'utilisateur a choisi : grouper les arbres
		On demande d'entrer la taille du groupe et la distance entre les groupes.
		On itére autant de fois qu'il n'a pas entré la bonne valeur.
	*/
    else if (type_positionnement==2) 
    {
		char message_taille[] = "Quelle doit etre la taille d'un groupe d'arbres\n";
		char message_taille_erreur[] = "Erreur : Nombre non valide, entez une nouvelle taille\n";
		char message_distance[] = "Quelle doit etre la distance entre les groupes d'arbres\n";
		char message_distance_erreur[] = "Erreur : Nombre non valide, entez une nouvelle distance\n";

		/* Taille du groupe.																		 */
		taille_groupe_arbres = entier_valide(-1*LARGEUR_TERRAIN*LONGUEUR_TERRAIN,
											 LARGEUR_TERRAIN*LONGUEUR_TERRAIN,
											 message_taille,
											 message_taille_erreur);
		
		/* Distance entre les groupe (en mètre).													 */
		distance_entre_groupe_arbres = entier_valide(0,
													 LARGEUR_TERRAIN - 1,
													 message_distance,
													 message_distance_erreur);
		
		/* On effectue la simulation pour le positionnement grouper les arbres.						 */
        faire_simulation_groupee(taille_groupe_arbres, distance_entre_groupe_arbres);
	}
    return EXIT_SUCCESS;
}


/*****************************************************************************************************/
/*								DÉFINITIONS DE FONCTIONS                                             */
/*****************************************************************************************************/

void afficher_terrain(t_terrain terrain)
{    
	int ligne;   /* Variable représentant la ligne de la case du tableaux ou l'on se trouve.        */
    int colonne; /* Variable représentant la colonne de la case du tableaux où l'on se trouve.      */
    
    /* Itération de tout les cases du tableau pour faire l'affichage de l'état de la case.           */
    /* On parcourt les lignes du tableaux.															 */
    for (ligne=0;ligne < LONGUEUR_TERRAIN; ligne ++)
    {
        /* On parcourt les colonnes du tableaux.													 */
		for(colonne=0;colonne < LARGEUR_TERRAIN; colonne ++)
        {
            /* On affiche dans l'interface le même état des cases du tableaux selon leurs états,
			sauf pour l'état, arbre brûlé, qui devient des cendres.                                  */
            if (etat_case(terrain,ligne, colonne)==CASE_VIDE)
                dessiner_case(ligne,colonne,VIDE);
            else if (etat_case(terrain,ligne,colonne)==CASE_ARBRE)
                dessiner_case(ligne,colonne,ARBRE);
            else if (etat_case(terrain,ligne,colonne)==CASE_FEU)
                dessiner_case(ligne,colonne,FEU);
            else
                dessiner_case(ligne,colonne,CENDRES);
        }
    }
}

void propager_un_feu(t_terrain terrain,int ligne, int colonne)
{
	/* Variables pour lire la coordonnée de la ligne (case_i) et la colonne (case_j) d'une case à
	   vérifier.                                                                                     */
    int case_i;
    int case_j;
	/* Initialisation de la variable pour calculer la distance entre un arbre en feu et le suivant.  */
    int distance_totale = 0;

/* On parcourt tout les arbres à une distance de [DISTANCE_MAX_PROPAGATION] de l'arbre en feu et
   on test que la probabilité que le feu peut se propager selon la distance.                         */
	
	/* On parcourt tout les cases autour de l'arbre en feux selon le paramètre 
	   [DISTANCE_MAX_PROPAGATION].                                                                   */	
	for (case_i = -DISTANCE_MAX_PROPAGATION; case_i <= DISTANCE_MAX_PROPAGATION; case_i++)
    {
		for(case_j = -DISTANCE_MAX_PROPAGATION; case_j <= DISTANCE_MAX_PROPAGATION; case_j++)
        { 
			/* Calcul de la distance entre deux cases.												 */
			distance_totale = sqrt((1.0*(case_i)*(case_i))+(case_j*case_j));
				
			/* On vérifie que la case na dépasse pas la longueur et largeur du tableaux.			 */
			if (est_dans_intervalle(ligne+case_i,0,LONGUEUR_TERRAIN-1) 
				&& est_dans_intervalle(colonne+case_j,0,LARGEUR_TERRAIN-1))
			{
				/* On test selon la probabilité qu'un feu peut se propager selon la distance. 
						Si, cette condition est valide, on met l'arbre en feu.                       */ 
				if ((etat_case(terrain, ligne+case_i, colonne+case_j)==CASE_ARBRE) 
					&& (nb_aleatoire_0_1()) < probabilite_propagation_feu(distance_totale))
				{
					modifier_etat_case(terrain, (ligne+case_i), (colonne+case_j), CASE_FEU);
				}
			}		
		}	 
	}
}


void allumer_nieme_arbre(t_terrain terrain, int n)
{	
	/* Initialisation des variables pour lire la coordonnée de la ligne et colonne d'une case.	    */
    int ligne = 0;
    int colonne = 0;
	/* Initialisation d'un compteur d'arbre à allumer.										        */
    int nb_arbre = 0;
    
	/* Tant qu'on est dans les limites du terrain et que nous n'avons pas atteint le nombre d'arbres
	   requis à allumer, on boucle.                                                                 */
    while((ligne<LONGUEUR_TERRAIN)&&(nb_arbre!=n))
	{
		while((colonne<LARGEUR_TERRAIN)&&(nb_arbre!=n))
		{
			/* Si la case est un arbre, on ajoute un arbre au compteur.								*/
			if( etat_case(terrain, ligne, colonne)==CASE_ARBRE)
				nb_arbre++; /* on la compte */

			/* Lorsqu'on a atteint le nombre d'arbres requis, on modifie l'état de la case pour
				l'état d'un arbre en feu. du terrain et on le dessine dans l'interface.             */
			if(nb_arbre==n)
			{
				/* on modifie l'état de la case et on la dessine */
				modifier_etat_case(terrain,ligne,colonne,CASE_FEU);
				dessiner_case(ligne, colonne, FEU);
			}	
			/* On passe à la colonne suivante.														*/
			colonne++;
		}

		/* On passe à la ligne suivante.															*/
		ligne++;
		/* On remet la variable de la coordonnéecolonne à 0.										*/
		colonne=0;
	}
}


void afficher_cases_modifiees_terrain(t_terrain nouveau_terrain, t_terrain ancien_terrain)
{
/* Varaiable pour les coordonnée de la ligne et colonne.										    */
    int ligne;
    int colonne;

	/* Itération de tout les cases du tableau.													    */
    for(ligne=0; ligne < LONGUEUR_TERRAIN; ligne++)
    {
        for(colonne=0; colonne < LARGEUR_TERRAIN; colonne++)
        {
			/* Si l'état de la case de l'ancien terrain n'est pas identique à celle du nouveau 
			   terrain. On modifie l'état de la case du nouveau terrain en fonction de l'état de 
			   la case du terrain. Ensuite, on l'affiche dans l'interface.							*/
            if(ancien_terrain[ligne][colonne]!=nouveau_terrain[ligne][colonne])
            {
                /* Test l'état des case du nouveau terrain.                                         */
				if (etat_case(nouveau_terrain,ligne, colonne)==CASE_VIDE)
                    dessiner_case(ligne,colonne,VIDE);
                else if (etat_case(nouveau_terrain,ligne,colonne)==CASE_ARBRE)
                    dessiner_case(ligne,colonne,ARBRE);
                else if (etat_case(nouveau_terrain,ligne,colonne)==CASE_FEU)
					dessiner_case(ligne,colonne,FEU);
				else if (etat_case(nouveau_terrain,ligne,colonne)==CASE_ARBRE_BRULE)  
					dessiner_case(ligne,colonne,CENDRES);        
            }  
        }
    }  
}

void propager_feu_tout_terrain(t_terrain terrain)
{
	/* Faire une copie du terrain.																	 */
    t_terrain copie_terrain;
	/* Variable pour lire les cooodonnée de la ligne et colonne.									 */
    int ligne;
    int colonne;

	/* On copie le terrain original dans un terrain temporaire.										 */
    copier_terrain(copie_terrain,terrain);

	/* On remplace l'état des case du terrain dans la copie du terrain								 */
	remplacer_etat(copie_terrain, CASE_FEU,CASE_ARBRE_BRULE);

	/* Itération de tout les cases du tableau.													     */
    for (ligne=0; ligne < LONGUEUR_TERRAIN; ligne++)
    {
        for(colonne=0; colonne<LARGEUR_TERRAIN; colonne++)
        {
            /* Si la case est en feu, on propage le feu à un autre arbre.						     */
            if(etat_case(terrain,ligne,colonne) == CASE_FEU)
				propager_un_feu(copie_terrain, ligne, colonne);
		}
	}
	
	/* On copie le terrain temporaire dans le terrain original.										 */
    copier_terrain(terrain,copie_terrain);
}


void allumer_aleatoirement_arbre(t_terrain terrain)
{
	/* On test, si le nombre d'arbre est supérieur ou égal à 1, on allume le nième arbre selon une
	   valeur aléatoire.																			*/
    if(nb_arbres(terrain) >= 1) 
		allumer_nieme_arbre(terrain, nb_aleatoire(1,(int)nb_arbres(terrain)));
}


void simuler_un_feu_de_foret(t_terrain terrain)
{
	/* Initialisation de la variable pour le premier arbre à brûler.								 */
    int arbre_aleatoire = 0;
	/* Faire une copie du terrain.																	 */
    t_terrain copie_terrain;

    /* On choisit un arbre aléatoirement à allumer.													 */
    arbre_aleatoire=nb_aleatoire(1, (int)nb_arbres(terrain));
	/* On allume aléatoirement un arbre.															 */
	allumer_nieme_arbre(terrain, arbre_aleatoire);
	/* On affiche le terrain.																		 */
	afficher_terrain(terrain);
	/* On effectue une pause.																		 */
	effectuer_pause();
	
	/* Tant que le nombre de feux est supérieur ou egal à 1, on execute la boucle.					 */
	while(nb_feux(terrain)>=1) 
    {
		/* On fait une copie du terrain original.													 */
        copier_terrain(copie_terrain, terrain);
		/* On propage le feu dans la copie.															 */
        propager_feu_tout_terrain(copie_terrain);
        
        /* On met à jour le nombre d'arbres dans l'interface.										 */
        mettre_a_jour_nb_courant_arbres((int)nb_arbres(copie_terrain));
        /* On affiche les cases qui ont été modifiées.												 */
        afficher_cases_modifiees_terrain(copie_terrain, terrain);
		/* On met la copie dans le terrain original.												 */
        copier_terrain(terrain,copie_terrain);
		/* On crée un délai de 500 msec à chaque propagation du feu.								 */
		effectuer_delai(500);
	}
}

int faire_simulation_groupee (int taille_groupes, int distance_groupes)
{
    /* On définie une variable pour le terrain.														 */
	t_terrain terrain;
    
    /*	On passe en mode graphique.																	 */
	if (!demarrer_mode_graphique(LONGUEUR_TERRAIN, LARGEUR_TERRAIN ))
	{
		printf("Impossible de passer en mode graphique.");
		return EXIT_FAILURE;
	}
    
	/* On dessine l'interface graphique.															 */
	dessiner_interface();
    /* On initialise le terrain en le remplissant de cases vide.									 */
    remplir_terrain(terrain,CASE_VIDE);
    
	/*	On affiche le terrain.																		 */
	afficher_terrain(terrain);
    /* On genere des groupes d'arbres.																 */
    generer_terrain_groupe(terrain, taille_groupes, distance_groupes);
    
	/*	On met à jour les données à droite.															 */
	mettre_a_jour_type_simulation(0);
	mettre_a_jour_taille_groupes_arbres(taille_groupes);
	mettre_a_jour_distance_groupes_arbres(distance_groupes);
	mettre_a_jour_nb_initial_arbres((int)nb_arbres(terrain));
    
    /* On simule un feu de foret.																	 */
    simuler_un_feu_de_foret(terrain);
	/*	On effectue une pause.																		 */
	effectuer_pause();
    /* On ferme le mode graphique.																	 */
	fermer_mode_graphique();
    
	return EXIT_SUCCESS;
    
}

int faire_simulation_placement_aleatoire (double pourcentage_arbres)
{
    /* On définie une variable pour le terrain.														 */
	t_terrain terrain;
    
    /*	On passe en mode graphique.																	 */
	if (!demarrer_mode_graphique(LONGUEUR_TERRAIN, LARGEUR_TERRAIN ))
	{
		printf("Impossible de passer en mode graphique.");
		return EXIT_FAILURE;
	}
    
	/* On dessine l'interface graphique.															 */
	dessiner_interface();
    /* On initialise le terrain, en le remplissant de cases vide.									 */
    remplir_terrain(terrain,CASE_VIDE);
	/*	On affiche le terrain.																		 */
	afficher_terrain(terrain);
    /* On genere aléatoirement des arbres.															 */
    generer_terrain_aleatoire(terrain, pourcentage_arbres);
     
	/*	On met à jour les données à droite.															 */
	mettre_a_jour_type_simulation(1);
	mettre_a_jour_taille_groupes_arbres(-1);
	mettre_a_jour_distance_groupes_arbres(-1);
    mettre_a_jour_nb_initial_arbres((int)nb_arbres(terrain));
   
    /* On simule un feu de foret.																	 */
    simuler_un_feu_de_foret(terrain);
	/*	On effectue une pause.																		 */
	effectuer_pause();
    /* Pour fermer le mode graphique.																 */
	fermer_mode_graphique();
    
	return EXIT_SUCCESS;
}
static void remplir_terrain(t_terrain terrain,t_etat etat)
{
	/* Variable pour les lignes et les colonnes.													 */
	int ligne;
	int colonne;

	/* Pour remplir tous les cases du tableau d'un état.											 */
	for(ligne = 0; ligne < LONGUEUR_TERRAIN; ligne++)
	{
		/* Pour toutes les colonnes.																 */
		for(colonne = 0; colonne < LARGEUR_TERRAIN; colonne++)
		{
			/* on met l'état dans la case.															 */
			terrain[ligne][colonne] = etat;
		}
	}
}