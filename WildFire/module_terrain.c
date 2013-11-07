/*****************************************************************************************************/
/* Par       : Olivier Goyette										                        	     */
/*			 : Dominc Blanchard																		 */
/*			 : Chuan Dong																	         */
/*			 : Aurelien Delon																		 */
/* Revise le : 01/11/2013													                         */
/* Fichier   : module_terrain.c												                         */
/*																		                             */
/* Description:  Ce module se compose de diverses fonction servant au fonctionnement du terrain.     */
/*					Voici les fonctions privées:												     */
/*																									 */
/*							- ajouter_groupe_arbres,         Par: Olivier Goyette, Dominic Blanchard */
/*															  et  Aurelien Delon				     */
/*							- ajouter_aléatoirement_n_etat,	 Par: Olivier Goyette				     */
/*							- nb_occurrences_etat,			 Par: Olivier Goyette	                 */
/*							- remplir_terrain,				 Par: Dominic Blanchard					 */
/*																									 */
/*					Ainsi que les fonctions publics:												 */
/*																									 */
/*							- remplacer_etat,				 Par: Olivier Goyette				     */
/*               			- copier_terrain,				 Par: Olivier Goyette					 */
/*						    - modifier_etat_case,			 Par: Olivier Goyette					 */
/*							- etat_case,					 Par: Olivier Goyette					 */
/*							- nb_arbres_brules,				 Par: Olivier Goyette					 */
/*							- nb_feux,						 Par: Olivier Goyette				     */
/*							- nb_arbres,					 Par: Olivier Goyette					 */
/*							- generer_terrain_aleatoire,	 Par: Olivier Goyette			         */
/*							- generer_terrain_groupe,		 Par: Olivier Goyette, Dominic Blanchard */
/*															   et Aurelien Delon					 */
/*																									 */
/*****************************************************************************************************/

/*****************************************************************************************************/
/*							INCLUSION DE LIBRAIRIES							                         */
/*****************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "module_terrain.h"
#include "module_util.h"

/*****************************************************************************************************/
/*							 DÉCLARATION DE FONCTIONS                                                */
/*****************************************************************************************************/
/*
AJOUTER_GROUPE_ARBRE

	Cette procédure privée ajoute un groupe d'arbre à partir de la position [ligne][colonne]
	sur une longueur "longueur" et de taille "taille"

	PARAMÈTRES :
		- terrain  : (SORTIE) Le terrain à remplir.                           (type : t_terrain).
		- ligne    : Les ligne qui composent le tableau.                      (type : int).
		- colonne  : Les colonnes qui composent le tableau.                   (type : int ).
		- longueur : longueur des colonnes d'arbres qui composent le tableau. (type : int ).
		- taille   : la grossseur du groupe d'arbre (type : int ).

	VALEUR DE RETOUR : Aucune.

*/
static void ajouter_groupe_arbres(t_terrain ajouter_groupe, int ligne, int colonne, int longueur, 
																					     int taille)
{
	/* Initilisaition des variables pour l'itération du tableau.									 */
	int x = 0;
	int y = 0;
	int z = 0;
	
	/* Initilisation de la variable pour calculer le nombre d'arbres restant.						 */
	int somme_arbre = taille;
	
	/* Initilisaition des variables pour les arbre en dehors du tableau.							 */
	int nb_arbre_ligne = 0;
	int nb_arbre_colonne = 0;

	/*Modification des paramètres selon ou le groupe d'arbre est localisé dans le tableau.			 */
		
		/* On enlève le nombre d'arbres d'une ou plusieurs colonnes.								 */
		if ( colonne > (LARGEUR_TERRAIN - longueur))
			somme_arbre = somme_arbre - ((taille - ((longueur - 
											  (colonne - (LARGEUR_TERRAIN - longueur))) * longueur)));
		
		/* On enlève une ou plusieurs lignes si on depasse le nombre de ligne du tableau.			 */
		if ( ligne > (LONGUEUR_TERRAIN - longueur))
			nb_arbre_ligne = ligne - (LONGUEUR_TERRAIN - longueur);
				
		/* Itération de toute les colonnes d'arbres pleines d'un groupe d'arbre.					 */
		for (y=0; somme_arbre >= longueur; ++y)
		{	
			/* Assignation de l'état de la case du groupe d'arbre et correction des arbres manquants
			   si le groupe d'arbre dépasse la ligne maximale du tableau.							 */
			for(x=0; x < (longueur-nb_arbre_ligne); ++x)
				ajouter_groupe[x + ligne][y + colonne] = CASE_ARBRE;
					
			somme_arbre = somme_arbre - (x + nb_arbre_ligne);
		}
		
		/* Itération pour la dernière colonne d'un groupe arbre non pleine.							 */
		for (z=0; z < somme_arbre; ++z)
		{
			if (nb_arbre_ligne > (longueur - somme_arbre))
				somme_arbre = somme_arbre - (nb_arbre_ligne - 1);
				
			ajouter_groupe[z + ligne][y + colonne] = CASE_ARBRE;
		}		
}


/*
	AJOUTER_ALÉATOIREMENT_N_ETAT

	Cette procédure privée inscrit l'état du terrain dans "n" cases choisies aléatoirement.

	PARAMÈTRES :
		- terrain : (SORTIE) Le terrain à remplir.          (type : t_terrain).
		- etat    : état que peut prendre une case.         (type : t_etat).
		- n       : Nombre de cases choisies aléatoirement. (type : int).

	VALEUR DE RETOUR : Aucune.
*/
static void ajouter_aléatoirement_n_etat(t_terrain terrain, t_etat etat, int n)
{
	/* Initialisation d'un compteur pourutiliser la boucle.											 */
	int compteur_case_rempli = 0; 
	/* Variable pour les lignes et les colonnes.													 */
	int ligne, colonne;          

	/* Tant que nous n'avons pas rempli "n" cases, on boucle.										 */
	while(compteur_case_rempli <= n)
	{
		/*	On assigne une valeur aléatoire au ligne et au colonne.									 */
		ligne = nb_aleatoire(0,LONGUEUR_TERRAIN - 1);
		colonne = nb_aleatoire(0,LARGEUR_TERRAIN - 1);

		/* On remplit la case avec l'état voulue.													 */
		terrain[ligne][colonne] = etat;

		/* On incrémente le nombre de cases.														 */
		compteur_case_rempli++;
	}
}


/*
	NB_OCCURRENCES_ETAT(terrain, etat)

	Cette procédure privée compte le nombre de fois qu'un état se 
	répète dans le terrain.

	PARAMÈTRES :
		- terrain : Le terrain dans lequel on compte.   (type : t_terrain).
		- etat : état des cases que l'on veut compter.  (type : t_etat).

	VALEUR DE RETOUR : le nombre de cases ayant l'état désirée.
*/
static int nb_occurrences_etat(const t_terrain terrain, t_etat etat)
{
	/* Initialisation du compteur pour l'état des cases.											 */
	int compteur_etat_case = 0; 
	/* Variables pour lire les lignes et les colonnes.												 */
	int ligne, colonne;         

	/* Boucle pour parcourir tout les cases du tableau.												 */
	for(ligne = 0; ligne < LONGUEUR_TERRAIN; ligne++)
	{
		for(colonne = 0; colonne < LARGEUR_TERRAIN; colonne++)
		{
			/* Si la valeur de la case = l'état, on incrémente le compteur.							 */
			if(terrain[ligne][colonne] == etat)
			{
				compteur_etat_case ++; 
			}
		}
	}
	/* On retourne la valeur du compteur.															 */
	return compteur_etat_case;
}


/*
REMPLIR_TERRAIN(terrain, etat)

	Cette procédure privée asigne l'état dans toutes les cases
	du terrain

	PARAMÈTRES :
		- terrain : Le terrain dans lequel on assigne l'état.  (type : t_terrain).
		- etat : état des cases que l'on veut implanter.	   (type : t_etat).

	VALEUR DE RETOUR : aucune.

*/
static void remplir_terrain(t_terrain terrain,t_etat etat)
{
	/* Variables pour lire les lignes et les colonnes												 */
	int ligne;
	int colonne; 

	/* On parcourt tous les cases du tableau en assigant l'état à cette cases.						 */
	for(ligne = 0; ligne < LONGUEUR_TERRAIN; ligne++)
	{
		/* Pour toutes les colonnes */
		for(colonne = 0; colonne < LARGEUR_TERRAIN; colonne++)
		{
			terrain[ligne][colonne] = etat; 
		}
	}
}


/*
	REMPLACER_ETAT(terrain, ancien_etat, nouvel_etat)

	Cette procédure remplace tous les "ancien_etat" du terrain par
	tous les "nouvel_etat".
*/
void remplacer_etat(t_terrain terrain_a_modifier, t_etat etat_initial,t_etat nouvel_etat)
{
	/* Variable pour lire les lignes et les colonnes.												 */
	int ligne;
	int colonne;

	/* On parcourt tous les cases du tableau et si la valeur de la case = l'ancien état, 
	   on change l'état de cette cases.																 */
	for(ligne = 0; ligne < LONGUEUR_TERRAIN; ligne++)
	{
		for(colonne = 0; colonne < LARGEUR_TERRAIN; colonne++)
		{ 
			if(terrain_a_modifier[ligne][colonne] == etat_initial)
			{
				terrain_a_modifier[ligne][colonne] = nouvel_etat;
			}
		}
	}
}


/*
	COPIER_TERRAIN(terrain_destination, terrain_source)

	Cette procédure copie le terrain source dans terrain destination
*/
void copier_terrain(t_terrain destination, const t_terrain source)
{
	/* Variable pour lire les lignes et les colonnes.											     */
	int ligne;
	int colonne;

	/* On parcourt tous les cases du tableau pour fair une copie de la source dans la destination.   */
	for(ligne = 0; ligne < LONGUEUR_TERRAIN; ligne++)
	{
		for(colonne = 0; colonne < LARGEUR_TERRAIN; colonne++)
		{
			destination[ligne][colonne] = source[ligne][colonne];	
		}
	}
}


/*
	MODIFIER_ETAT_CASE(terrain, ligne, colonne, nouvel_etat)

	Cette procédure modifie l'état d'une case aux coordonnées [ligne][colonne]
	en lui assignant un nouvel_etat.
*/
void modifier_etat_case(t_terrain terrain_a_modifier, int ligne, int colonne,
						t_etat nouvel_etat)
{
	/*	On modifie les coordonnées [lignes][colonnes] dans le tableau, on assigne l'état 
	    nouvel_etat.																				 */
	terrain_a_modifier[ligne][colonne] = nouvel_etat;
}


/*
	ETAT_CASE(terrain, ligne, colonne)

	Cette procédure retourne l'état d'une case à [ligne][colonne]
*/
t_etat etat_case(const t_terrain terrain_a_consulter, int ligne, int colonne)
{
	/* On retourne la valeur aux coordonnées [lignes][colonnes].									 */
	return terrain_a_consulter[ligne][colonne];
}


/*
	NB_ARBRES_BRULES(terrain)

	Cette procédure retourne le nombre d'arbres brulés sur le terrain.
*/
long int nb_arbres_brules(const t_terrain terrain_a_consulter)
{
	/* On appel nb_occurrences_etat pour compter les arbre brûlés.									 */
	return nb_occurrences_etat(terrain_a_consulter,CASE_ARBRE_BRULE);
}


/*
	NB_FEUX(terrain)

	Cette procédure retourne le nombre d'arbres en feux sur le terrain.
*/
long int nb_feux(const t_terrain terrain_a_consulter)
{
	/* On appel nb_occurrences_etat pour compter le nombre d'arbre en feu.							 */
	return nb_occurrences_etat(terrain_a_consulter,CASE_FEU);
}


/*
	NB_ARBRES(terrain)

	Cette procédure retourne le nombre d'arbres en feux sur le terrain.
*/
long int nb_arbres(const t_terrain terrain_a_consulter)
{
	/* On appel nb_occurrences_etat pour compter le nombre d'arbre.									 */
	return nb_occurrences_etat(terrain_a_consulter,CASE_ARBRE);
}


/*
	GENERER_TERRAIN_ALEATOIRE

	Cette procédure vide le terrain reçu et y positionne aléatoirement des arbres
	de façon à ce que "pourcentage_recouvrement" pourcent des carrés contiennent
	un arbre.
*/
void generer_terrain_aleatoire(t_terrain terrain_a_generer, double pourcentage_recouvrement)
{
	/* Variable pour les différents calculs avec le pourcentage.									 */
	int n;

	/* Si le pourcentage est plus petit que 50, on remplit le terrain de cases vides et
	   on ajoute aléatoirement des arbres.															 */
	if(pourcentage_recouvrement < 0.5)
	{
		/* n = pourcentage * 50 * 70																 */
		n = pourcentage_recouvrement * LONGUEUR_TERRAIN * LARGEUR_TERRAIN;
		remplir_terrain(terrain_a_generer,CASE_VIDE);
		ajouter_aléatoirement_n_etat(terrain_a_generer, CASE_ARBRE, n);
	}
	/* si le pourcentage est plus élevé que 50, on remplit le terrain d'arbres et 
	   on insère ensuite des cases vides.															 */
	else
	{
		/* n = (1 - pourcentage) * 50 * 70															 */
		n = (1 - pourcentage_recouvrement) * LONGUEUR_TERRAIN * LARGEUR_TERRAIN;
		remplir_terrain(terrain_a_generer,CASE_ARBRE);
		ajouter_aléatoirement_n_etat(terrain_a_generer, CASE_VIDE, n);
	}
}


/*
	GENERER_TERRAIN_GROUPE

	Cette procédure positionne des groupes d'arbres séparés par une "distance".
*/
void generer_terrain_groupe(t_terrain terrain_a_generer, int taille_groupe, int distance)
{
	/* Variable pour la position les coordonnée de la position de l'arbre en feu.					 */
	int position_ligne = 0;
	int position_colonne = 0;
	/* Variables pour parcourir le tableau (terrain).												 */
	int i, j;
	/* Variable pour calculer la longueur du groupe.												 */
	int longueur;
	/* Initialisation de la variable pour la longueur du groupe corigé.								 */
	int longueur_colonne = 0;
	/* Variables pour calculer le nombre de groupe maximale dans le tableu (terrain).				 */
	int nb_groupe_colonne;
	int nb_groupe_ligne;
	
	/* Calcul de la longueur du groupe.																 */
	longueur = plafond(sqrt(1.0 * taille_groupe));
	
	/* Si la distance est de zéro et que la longueur du groupe n'est pas pleine, on modifie la 
	   longueur du groupe. Ou si la taille du groupe est égale à 2.									 */
	if((distance == 0 && taille_groupe <= (longueur * (longueur - 1))) || taille_groupe == 2)
	{    
		 longueur_colonne = longueur - 1;
		 nb_groupe_colonne = 2 * plafond(LARGEUR_TERRAIN/(sqrt((double)taille_groupe) + distance));
	     nb_groupe_ligne = plafond(LONGUEUR_TERRAIN/(sqrt((double)taille_groupe) + distance));
	}
	/* Si la distance est de zéro et que la longueur du groupe est pleine, on ne modifie pas 
	   la longueur du groupe d'arbre.																 */
	else if(distance==0)
	{    
		 longueur_colonne = longueur;
		 nb_groupe_colonne = 2 * plafond(LARGEUR_TERRAIN/(sqrt((double)taille_groupe) + distance));
	     nb_groupe_ligne = plafond(LONGUEUR_TERRAIN/(sqrt((double)taille_groupe) + distance));
	}
	/* Si la distance est différent de zéro et si la longueur du groupe n'est pas pleine, on 
	   modifie la longueur.																			 */
	else if (taille_groupe <= (longueur * (longueur - 1)) && (distance != 0))
	{
			longueur_colonne = longueur - 1;
			nb_groupe_colonne = plafond(LARGEUR_TERRAIN/(sqrt((double)taille_groupe) + distance));
	        nb_groupe_ligne = plafond(LONGUEUR_TERRAIN/(sqrt((double)taille_groupe) + distance));
	}
	/* Si la distance est différent de zéro et si la longueur du groupe est pleine on ne modifiée 
	   pas la longueur du groupe.																	 */
	else if (distance!=0)
	{
			longueur_colonne = longueur;
		    nb_groupe_colonne = plafond(LARGEUR_TERRAIN/(sqrt((double)taille_groupe) + distance));
	        nb_groupe_ligne = plafond(LONGUEUR_TERRAIN/(sqrt((double)taille_groupe) + distance));
	}
	  
/* Boucle pour insérer le nombre de groupe maximal dans le terrain.									 */  
	
	/* On insére le nombre de groupe maximal pour la longueur du terrain.							 */
	for(i=0; i <= nb_groupe_ligne; ++i)
	{	
		for (j=0; j <= nb_groupe_colonne; ++j)
		{      
				ajouter_groupe_arbres(terrain_a_generer,position_ligne,position_colonne,longueur,
																					   taille_groupe);
			    position_colonne = position_colonne + (longueur_colonne + distance);		
		}
		/* Initialisation de la colonne pour la ligne suivante.										 */
		position_colonne = 0;
		
		/* La position du prochaine groupe dans le terrrain en tenant compte la la distance entre
		   les arbres.																				 */
		position_ligne = position_ligne + (longueur + distance);
	}	
}
