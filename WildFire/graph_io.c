/******************************************************************************
	FICHIER : GRAPH_IO.C
	PAR     : Frederick Henri
	DATE    : 19/09/2013
	POUR    : INF145

	Ce module definit l'ensemble des fonctions graphiques necessaires pour
	simuler la propagation d'un feu dans une pépinière.

	À NOTER : Pour pouvoir utiliser ce module, assurez-vous d'utiliser 
	          le jeu de caractères MBCS (Projet->Propriétés de ...->Général).
******************************************************************************/




#include "graph_io.h"
#include "winbgim.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>




/******************************************************************************
							DÉFINITIONS DE CONSTANTES
******************************************************************************/
/*	La chaine à utiliser pour justifier les nombres. */
#define CHAINE_JUSTIFICATION "XXXXXX"

/*	La chaîne à afficher lorsqu'un paramètre (taille ou distance) est
	négatif.
*/
#define PARAMETRE_ABSENT	"---"

/*	Le texte à afficher pour identifier la simulation. */
#define SIMULATION_ALEATOIRE	"Oui"
#define SIMULATION_GROUPEE		"Non"




/******************************************************************************
							DÉFINITIONS DE VARIABLES PRIVÉES
******************************************************************************/
/* Les dimensions de la grille. */
static int HAUTEUR_TERRAIN;		/* Exprimée en cases. */
static int LARGEUR_TERRAIN;		/* Exprimée en cases. */

/* Les dimensions de l'écran. */
static int HAUTEUR_ECRAN;		/* Exprimée en pixels. */
static int LARGEUR_ECRAN;		/* Exprimée en pixels. */

/* Les informations sur la position et la dimension de la plaque. */
static int DEBUT_PLAQUE_X;		/* Coin supérieur gauche de la plaque. */
static int DEBUT_PLAQUE_Y;
static int FIN_PLAQUE_X;		/* Coin inférieur droit de la plaque. */
static int FIN_PLAQUE_Y;
static int TAILLE_CASE;			/* Taille d'une case en pixels. */



/******************************************************************************
						DÉFINITIONS DE CONSTANTE
******************************************************************************/
/*	Le nom des paramètres qui apparaissent en haut à droite. */
#define NB_PARAMETRES	5
static const char * liste_noms_parametres[NB_PARAMETRES] =
{
	"Positionnement aleatoire :",
	"Taille des groupes :", 
	"Distance entre les groupes :",
	"Nombre initial d'arbres :",
	"Nombre courant d'arbres :"
};




/******************************************************************************
						DÉFINITIONS DE FONCTIONS PRIVÉES
******************************************************************************/
/*
	COTE_GAUCHE_CASE

	Cette fonction retourne la coordonnée en x du côté gauche d'une case.

	PARAMÈTRES :
		- colonne : La colonne de la case (type : int).
				  Cette valeur doit être dans l'intervalle 
				  [0, LARGEUR_TERRAIN[.

	VALEUR DE RETOUR : La coordonnée en x à l'écran du pixel le plus à gauche
					   d'une case.
*/
static int cote_gauche_case(int colonne)
{
	return DEBUT_PLAQUE_X + CONTOUR_PLAQUE +
		   colonne * (TAILLE_CASE + TAILLE_GRILLAGE_PLAQUE);
}



/*
	HAUT_CASE

	Cette fonction retourne la coordonnée en y du haut d'une case.

	PARAMÈTRES :
		- ligne : La ligne de la case (type : int).
				  Cette valeur doit être dans l'intervalle 
				  [0, HAUTEUR_TERRAIN[.

	VALEUR DE RETOUR : La coordonnée en y à l'écran du pixel le plus à haut
					   d'une case.
*/
static int haut_case(int ligne)
{
	return DEBUT_PLAQUE_Y + CONTOUR_PLAQUE +
		   ligne * (TAILLE_CASE + TAILLE_GRILLAGE_PLAQUE);
}



/*
	COORDONNEE_DANS_CASE

	Cette fonction permet de déterminer si une coordonnée écran se retrouve
	dans une case. Si tel est le cas, elle identifie la case.

	PARAMÈTRES :
		- x : La coordonnée en x du point à l'écran (type : int).
		- y : La coordonnée en y du point à l'écran (type : int).
		- ligne : L'adresse de l'objet qui recevra la ligne de la case si
				  la coordonnée est dans une case (type : int *).
		- colonne : L'adresse de l'objet qui recevra la colonne de la case si
				    la coordonnée est dans une case (type : int *).

	VALEUR DE RETOUR : 1 si la coordonnée se trouve dans une case et 0 sinon.
*/
static int coordonnee_dans_case(int x, int y, int * ligne, int * colonne)
{
	int i, j;			/*	Pour itérer sur les cases. */
	int gauche;			/* Le côté gauche d'une case. */
	int haut;			/* Le haut d'une case. */

	for (i = 0; i < HAUTEUR_TERRAIN; ++i)
	{
		for (j = 0; j < LARGEUR_TERRAIN; ++j)
		{
			/*	Si la coordonnée est dans la case (i, j), alors on retourne
				la ligne et la colonne de cette case.
			*/
			gauche = cote_gauche_case(j);
			haut = haut_case(i);
			if (gauche <= x && x <= gauche + TAILLE_CASE &&
				haut <= y && y <= haut + TAILLE_CASE)
			{
				*ligne = i;
				*colonne = j;
				return 1;
			}
		}
	}
	
	return 0;
}



/*
	DESSINER_ARBRE

	Cette fonction dessine un arbre à l'endroit demandé et de la couleur spécifiée.

	PARAMÈTRES :
		- x : La coordonnée en x du centre du cercle (type : int).
		- y : Le coordonnée en y du centre cercle (type : int).
		- rayon : Le rayon du cercle (type : int)
		- couleur : La couleur du cercle (type : long int).

	VALEUR DE RETOUR : Aucune.
*/
static void dessiner_arbre(int x, int y, int rayon, long int couleur)
{
	int i;		/*	Pour dessiner les cercles concentriques. */

	/*	On dessine des cercles concentriques qui palissent. */
	for (i = rayon; i > 0; i -= 3)
	{
		setcolor(COLOR(0, 0, 0) + couleur - COLOR(0, 8 * i, 0));
		setfillstyle(SOLID_FILL, COLOR(0, 0, 0) + couleur - COLOR(0, 8 * i, 0));
		pieslice(x, y, 0, 359, i);
	}
}



/*
	Explication de l'expression :
	- rand()
	  Une valeur entière dans l'intervalle [0, RAND_MAX].
	- 1.0 * rand()
	  Une valeur réelle dans l'intervalle [0, RAND_MAX].
	- 1.0 * rand() / RAND_MAX
	  Une valeur réelle dans l'intervalle [0, 1].
*/
static double nb_aleatoire_0_1(void)
{
	return 1.0 * rand() / RAND_MAX;
}



/*
	LONGUEUR_PARAMETRE_PLUS_LONG

	Cette fonction retourne la longueur du paramètre dont le nom est le plus long.

	PARAMÈTRES :
		- x : La coordonnée en x du centre du cercle (type : int).
		- y : Le coordonnée en y du centre cercle (type : int).
		- rayon : Le rayon du cercle (type : int)
		- couleur : La couleur du cercle (type : long int).

	VALEUR DE RETOUR : Aucune.
*/
static int longueur_parametre_plus_long(void)
{
	int longueur;
	int i;

	/*	On ajuste les caractéristiques du message à afficher. */
	settextstyle(SANSSERIF_FONT, HORIZ_DIR, 2);

	/*	On suppose que le premier paramètre porte le nom le plus long. */
	longueur = textwidth(liste_noms_parametres[0]);

	/*	On tente de trouver un paramètre dont le nom est plus long. */
	for (i = 1; i < NB_PARAMETRES; ++i)
	{
		if (textwidth(liste_noms_parametres[i]) > longueur)
			longueur = textwidth(liste_noms_parametres[i]);
	}
	
	return longueur;
}



/*
	AFFICHER_LISTE_PARAMETRES

	Cette procédure affiche une boîte qu'elle remplit avec la liste des noms de
	paramètres.

	PARAMÈTRES : Aucun.

	VALEUR DE RETOUR : Aucune.
*/
static void afficher_liste_parametres(void)
{
	int cote_gauche_boite;			/* Le côté gauche de la boîte (en pixels). */
	int cote_droit_boite;			/* Le côté droit de la boîte (en pixels). */
	int haut_boite;					/* Le haut de la boîte (en pixels). */
	int bas_boite;					/* Le bas de la boîte (en pixels). */
	int i;							/*  Pour traiter chaque paramètre. */

	/*	On ajuste les caractéristiques du texte à afficher. */
	setcolor(COULEUR_TEXTE);
	setbkcolor(COULEUR_FOND_TEXTE);
	settextstyle(SANSSERIF_FONT, HORIZ_DIR, 2);

	/*	On calcule la position du côté gauche de la boîte à dessiner. */
	cote_gauche_boite = LARGEUR_ECRAN - BORDURE_ECRAN_DROITE + DISTANCE_PLAQUE_PARAMETRES;

	/*	On dessine le fond de la zone. */
	setfillstyle(SOLID_FILL, COULEUR_FOND_TEXTE);
	haut_boite = BORDURE_ECRAN_HAUT;
	bas_boite = BORDURE_ECRAN_HAUT + NB_PARAMETRES * DISTANCE_ENTRE_PARAMETRES + textheight("X");
	cote_droit_boite = cote_gauche_boite + longueur_parametre_plus_long() + 3 + textwidth(CHAINE_JUSTIFICATION) +
					   2 * BORDURE_BOITE_PARAMETRES;
	bar(cote_gauche_boite, haut_boite, cote_droit_boite, bas_boite);

	/*	On ajoute un contour en bas et à droite de la zone. */
	setcolor(COULEUR_CONTOUR_FONCE);
	line(cote_gauche_boite, bas_boite, cote_droit_boite, bas_boite);
	line(cote_droit_boite, haut_boite, cote_droit_boite, bas_boite);

	/*	On ajoute un contour en haut et à gauche du terrain. */
	setcolor(COULEUR_CONTOUR_PALE);
	line(cote_gauche_boite, haut_boite, cote_droit_boite, haut_boite);
	line(cote_gauche_boite, haut_boite, cote_gauche_boite, bas_boite);

	/*	On écrit les noms des paramètres. */
	setcolor(COULEUR_TEXTE);
	for (i = 0; i < NB_PARAMETRES; ++i)
	{
		outtextxy(cote_gauche_boite + BORDURE_BOITE_PARAMETRES,
				  (int) (BORDURE_ECRAN_HAUT + (i + 0.5) * DISTANCE_ENTRE_PARAMETRES),
				  liste_noms_parametres[i]);
	}
}




/******************************************************************************
						DÉFINITIONS DE FONCTIONS PUBLIQUES
******************************************************************************/
int demarrer_mode_graphique(int hauteur_terrain, int largeur_terrain)
{
	int gdriver = DETECT, gmode;
	int largeur_max_case;			/*	Largeur maximale d'une case. */
	int hauteur_max_case;			/*	Hauteur maximale d'une case. */

	/*	On passe en mode graphique. */
	initgraph(&gdriver, &gmode, "");
	if (grOk != graphresult())
	{
		return 0;
	}

	/*	On initialise les dimensions du terrain. */
	HAUTEUR_TERRAIN = hauteur_terrain;
	LARGEUR_TERRAIN = largeur_terrain;

	/*	On calcule la dimension de l'écran. */
	HAUTEUR_ECRAN = getmaxy();
	LARGEUR_ECRAN = getmaxx();

	/*	On calcule la dimension de chaque case du terrain. */
	largeur_max_case = (LARGEUR_ECRAN - BORDURE_ECRAN_GAUCHE - BORDURE_ECRAN_DROITE - 2 * CONTOUR_PLAQUE -
					    TAILLE_GRILLAGE_PLAQUE * (LARGEUR_TERRAIN - 1)) / LARGEUR_TERRAIN;
	hauteur_max_case = (HAUTEUR_ECRAN - BORDURE_ECRAN_HAUT - BORDURE_ECRAN_BAS - 2 * CONTOUR_PLAQUE -
					    TAILLE_GRILLAGE_PLAQUE * (HAUTEUR_TERRAIN - 1)) / HAUTEUR_TERRAIN;
	TAILLE_CASE = min(largeur_max_case, hauteur_max_case);

	/*	On calcule les positions du coin supérieur gauche et du coin inférieur
		droit de la plaque.
	*/
	DEBUT_PLAQUE_X =  BORDURE_ECRAN_GAUCHE + CONTOUR_PLAQUE;
	DEBUT_PLAQUE_Y = BORDURE_ECRAN_HAUT + CONTOUR_PLAQUE;
	FIN_PLAQUE_X = DEBUT_PLAQUE_X + 2 * CONTOUR_PLAQUE + LARGEUR_TERRAIN * TAILLE_CASE +
				   (LARGEUR_TERRAIN - 1) * TAILLE_GRILLAGE_PLAQUE;
	FIN_PLAQUE_Y = DEBUT_PLAQUE_Y + 2 * CONTOUR_PLAQUE + HAUTEUR_TERRAIN * TAILLE_CASE +
				   (HAUTEUR_TERRAIN - 1) * TAILLE_GRILLAGE_PLAQUE;

	return 1;
}



void fermer_mode_graphique(void)
{
	closegraph();
}



void dessiner_interface(void)
{
	int i, j;

	/*	On dessine le fond de l'ecran. */
	setcolor(COULEUR_DE_FOND);
	setfillstyle(SOLID_FILL, COULEUR_DE_FOND);
	bar(0, 0, LARGEUR_ECRAN, HAUTEUR_ECRAN);
	
	/*	On dessine le fond du terrain. */
	setfillstyle(SOLID_FILL, COULEUR_CASE_VIDE);
	bar(DEBUT_PLAQUE_X, DEBUT_PLAQUE_Y, FIN_PLAQUE_X, FIN_PLAQUE_Y);

	/*	On ajoute un contour en bas et à droite du terrain. */
	setcolor(COULEUR_CONTOUR_FONCE);
	line(DEBUT_PLAQUE_X, FIN_PLAQUE_Y, FIN_PLAQUE_X, FIN_PLAQUE_Y);
	line(FIN_PLAQUE_X, DEBUT_PLAQUE_Y, FIN_PLAQUE_X, FIN_PLAQUE_Y);

	/*	On ajoute un contour en haut et à gauche du terrain. */
	setcolor(COULEUR_CONTOUR_PALE);
	line(DEBUT_PLAQUE_X, DEBUT_PLAQUE_Y, FIN_PLAQUE_X, DEBUT_PLAQUE_Y);
	line(DEBUT_PLAQUE_X, DEBUT_PLAQUE_Y, DEBUT_PLAQUE_X, FIN_PLAQUE_Y);

	/*	On ajoute les cases vides dans le terrain. */
	for (i = 0; i < HAUTEUR_TERRAIN; ++i)
	{
		for (j = 0; j < LARGEUR_TERRAIN; ++j)
		{
			dessiner_case(i, j, VIDE);
		}
	}

	/*	On ajoute les paramètres dans le coin supérieur droit. */
	afficher_liste_parametres();
}



void dessiner_case(int ligne, int colonne, t_type_case contenu)
{
	int gauche = cote_gauche_case(colonne);		/* Le côté gauche de la case. */
	int haut = haut_case(ligne);				/* Le haut de la case. */

	/*	On remplit le fond de la case (la case est alors vide). */
	setfillstyle(SOLID_FILL, COULEUR_CASE_VIDE);
	bar(gauche, haut, gauche + TAILLE_CASE, haut + TAILLE_CASE);

	/*	On dessine un arbre. */
	if (contenu == ARBRE)
	{
		dessiner_arbre(gauche + TAILLE_CASE / 2, haut + TAILLE_CASE / 2,
					   TAILLE_CASE / 2, COULEUR_CASE_ARBRE);
	}
	/*	On dessine un arbre en feu. */
	else if (contenu == FEU)
	{
		dessiner_arbre(gauche + TAILLE_CASE / 2, haut + TAILLE_CASE / 2,
					   TAILLE_CASE / 2, COULEUR_CASE_FEU);
	}
	/*	On dessine des cendres. */
	else if  (contenu == CENDRES)
	{
		int i, j;						/* Pour parcourir les pixels de la case. */
		double probabilite;				/* La probabilité qu'il y ait de la cendre. */

		/*	Plus on s'éloigne du centre du cercle, moins il y a de chance d'avoir de la
			cendre.
		*/
		for (i = 0; i < TAILLE_CASE; ++i)
		{
			for (j = 0; j < TAILLE_CASE; ++j)
			{
				/*	On calcule la distance entre le pixel (i, j) et le centre de la case.
					La probabilité correspond à la distance du pixel sur la plus grande
					distance possible d'un pixel dans une case.
				*/
				probabilite = sqrt((i - TAILLE_CASE / 2) * (i - TAILLE_CASE / 2) + 
								   (j - TAILLE_CASE / 2) * (j - TAILLE_CASE / 2)) /
							  sqrt(TAILLE_CASE / 2 * TAILLE_CASE / 2);

				if (nb_aleatoire_0_1() < 1 - probabilite)
				{
					putpixel(gauche + i, haut + j, COULEUR_CASE_CENDRES);
				}
			}
		}
	}
}



void mettre_a_jour_type_simulation(int aleatoire)
{
	int gauche_parametre;			/*	Le pixel de gauche du paramètre. */
	int gauche_nombre;				/*	Le pixel de gauche de la valeur du paramètre. */
	char nombre_a_afficher[50];		/*	Les caractères du nombre à afficher. */ 

	/*	On ajuste les caractéristiques du message à afficher. */
	setcolor(COULEUR_TEXTE);
	setbkcolor(COULEUR_FOND_TEXTE);
	settextstyle(SANSSERIF_FONT, HORIZ_DIR, 2);
	setfillstyle(SOLID_FILL, COULEUR_FOND_TEXTE);

	/*	On calcule où commence le paramètre. */
	gauche_parametre = LARGEUR_ECRAN - BORDURE_ECRAN_DROITE + 
					   DISTANCE_PLAQUE_PARAMETRES + BORDURE_BOITE_PARAMETRES;	
	gauche_nombre = gauche_parametre + longueur_parametre_plus_long() + 3;

	/*	On efface l'ancienne donnée. */
	setfillstyle(SOLID_FILL, COULEUR_FOND_TEXTE);
	bar(gauche_nombre, (int) (BORDURE_ECRAN_HAUT + 0.5 * DISTANCE_ENTRE_PARAMETRES),
		gauche_nombre + textwidth(CHAINE_JUSTIFICATION),
		(int) (BORDURE_ECRAN_HAUT + 0.5 * DISTANCE_ENTRE_PARAMETRES) + textheight("X"));

	/*	On affiche la nouvelle donnée. */
	if (aleatoire)
	{
		strcpy(nombre_a_afficher, SIMULATION_ALEATOIRE);
	}
	else
	{
		strcpy(nombre_a_afficher, SIMULATION_GROUPEE);
	}
	outtextxy(gauche_nombre + textwidth(CHAINE_JUSTIFICATION) - textwidth(nombre_a_afficher),
				(int) (BORDURE_ECRAN_HAUT + 0.5 * DISTANCE_ENTRE_PARAMETRES), nombre_a_afficher);
}



void mettre_a_jour_taille_groupes_arbres(int taille)
{
	int gauche_parametre;			/*	Le pixel de gauche de chaque paramètre. */
	int gauche_nombre;				/*	Le pixel de gauche de la valeur du paramètre. */
	char nombre_a_afficher[50];		/*	Les caractères du nombre à afficher. */ 

	/*	On ajuste les caractéristiques du message à afficher. */
	setcolor(COULEUR_TEXTE);
	setbkcolor(COULEUR_FOND_TEXTE);
	settextstyle(SANSSERIF_FONT, HORIZ_DIR, 2);
	setfillstyle(SOLID_FILL, COULEUR_FOND_TEXTE);

	/*	On calcule où commence le paramètre. */
	gauche_parametre = LARGEUR_ECRAN - BORDURE_ECRAN_DROITE + 
					   DISTANCE_PLAQUE_PARAMETRES + BORDURE_BOITE_PARAMETRES;	
	gauche_nombre = gauche_parametre + longueur_parametre_plus_long() + 3;

	/*	On efface l'ancienne donnée. */
	setfillstyle(SOLID_FILL, COULEUR_FOND_TEXTE);
	bar(gauche_nombre, (int) (BORDURE_ECRAN_HAUT + (1.5) * DISTANCE_ENTRE_PARAMETRES),
		gauche_nombre + textwidth(CHAINE_JUSTIFICATION),
		(int) (BORDURE_ECRAN_HAUT + (1.5) * DISTANCE_ENTRE_PARAMETRES) + textheight("X"));

	/*	On affiche la nouvelle donnée. */
	if (taille < 0)
	{
		strcpy(nombre_a_afficher, PARAMETRE_ABSENT);
	}
	else
	{
		sprintf(nombre_a_afficher, "%i", taille);
	}
	outtextxy(gauche_nombre + textwidth(CHAINE_JUSTIFICATION) - textwidth(nombre_a_afficher),
			  (int) (BORDURE_ECRAN_HAUT + (1.5) * DISTANCE_ENTRE_PARAMETRES), nombre_a_afficher);
}



/*
	METTRE_A_JOUR_DISTANCE_GROUPES_ARBRES

	Cette procédure met à jour la distance entre les groupes d'arbres.

	PARAMÈTRES :
		- distance : La distance entre les groupes d'arbres (type : int).
					 On suppose que cette valeur est supérieur ou égale à 0.

	VALEUR DE RETOUR : Aucune.
*/
void mettre_a_jour_distance_groupes_arbres(int distance)
{
	int gauche_parametre;			/*	Le pixel de gauche de chaque paramètre. */
	int gauche_nombre;				/*	Le pixel de gauche de la valeur du paramètre. */
	char nombre_a_afficher[50];		/*	Les caractères du nombre à afficher. */ 

	/*	On ajuste les caractéristiques du message à afficher. */
	setcolor(COULEUR_TEXTE);
	setbkcolor(COULEUR_FOND_TEXTE);
	settextstyle(SANSSERIF_FONT, HORIZ_DIR, 2);
	setfillstyle(SOLID_FILL, COULEUR_FOND_TEXTE);

	/*	On calcule où commence le paramètre. */
	gauche_parametre = LARGEUR_ECRAN - BORDURE_ECRAN_DROITE + 
					   DISTANCE_PLAQUE_PARAMETRES + BORDURE_BOITE_PARAMETRES;	
	gauche_nombre = gauche_parametre + longueur_parametre_plus_long() + 3;

	/*	On efface l'ancienne donnée. */
	setfillstyle(SOLID_FILL, COULEUR_FOND_TEXTE);
	bar(gauche_nombre, (int) (BORDURE_ECRAN_HAUT + (2.5) * DISTANCE_ENTRE_PARAMETRES),
		gauche_nombre + textwidth(CHAINE_JUSTIFICATION),
		(int) (BORDURE_ECRAN_HAUT + (2.5) * DISTANCE_ENTRE_PARAMETRES) + textheight("X"));

	/*	On affiche la nouvelle donnée. */
	if (distance < 0)
	{
		strcpy(nombre_a_afficher, PARAMETRE_ABSENT);
	}
	else
	{
		sprintf(nombre_a_afficher, "%i", distance);
	}
	outtextxy(gauche_nombre + textwidth(CHAINE_JUSTIFICATION) - textwidth(nombre_a_afficher),
			  (int) (BORDURE_ECRAN_HAUT + (2.5) * DISTANCE_ENTRE_PARAMETRES), nombre_a_afficher);
}




/*
	METTRE_A_JOUR_NB_INITIAL_ARBRES

	Cette procédure met à jour le nombre initial d'arbres.

	PARAMÈTRES :
		- nb_arbres : Le nombre initial d'arbres (type : int).
					  On suppose que cette valeur est supérieur ou égale à 0.

	VALEUR DE RETOUR : Aucune.
*/
void mettre_a_jour_nb_initial_arbres(int nb_arbres)
{
	int gauche_parametre;			/*	Le pixel de gauche de chaque paramètre. */
	int gauche_nombre;				/*	Le pixel de gauche de la valeur du paramètre. */
	char nombre_a_afficher[50];		/*	Les caractères du nombre à afficher. */ 

	/*	On ajuste les caractéristiques du message à afficher. */
	setcolor(COULEUR_TEXTE);
	setbkcolor(COULEUR_FOND_TEXTE);
	settextstyle(SANSSERIF_FONT, HORIZ_DIR, 2);
	setfillstyle(SOLID_FILL, COULEUR_FOND_TEXTE);

	/*	On calcule où commence le paramètre. */
	gauche_parametre = LARGEUR_ECRAN - BORDURE_ECRAN_DROITE + 
					   DISTANCE_PLAQUE_PARAMETRES + BORDURE_BOITE_PARAMETRES;	
	gauche_nombre = gauche_parametre + longueur_parametre_plus_long() + 3;

	/*	On efface l'ancienne donnée. */
	setfillstyle(SOLID_FILL, COULEUR_FOND_TEXTE);
	bar(gauche_nombre, (int) (BORDURE_ECRAN_HAUT + (3.5) * DISTANCE_ENTRE_PARAMETRES),
		gauche_nombre + textwidth(CHAINE_JUSTIFICATION),
		(int) (BORDURE_ECRAN_HAUT + (3.5) * DISTANCE_ENTRE_PARAMETRES) + textheight("X"));

	/*	On affiche la nouvelle donnée. */
	sprintf(nombre_a_afficher, "%li", nb_arbres);
	outtextxy(gauche_nombre + textwidth(CHAINE_JUSTIFICATION) - textwidth(nombre_a_afficher),
			  (int) (BORDURE_ECRAN_HAUT + (3.5) * DISTANCE_ENTRE_PARAMETRES), nombre_a_afficher);
}



/*
	METTRE_A_JOUR_NB_COURANT_ARBRES

	Cette procédure met à jour le nombre courant d'arbres.

	PARAMÈTRES :
		- nb_arbres : Le nombre courant d'arbres (type : int).
					  On suppose que cette valeur est supérieur ou égale à 0.

	VALEUR DE RETOUR : Aucune.
*/
void mettre_a_jour_nb_courant_arbres(int nb_arbres)
{
	int gauche_parametre;			/*	Le pixel de gauche de chaque paramètre. */
	int gauche_nombre;				/*	Le pixel de gauche de la valeur du paramètre. */
	char nombre_a_afficher[50];		/*	Les caractères du nombre à afficher. */ 

	/*	On ajuste les caractéristiques du message à afficher. */
	setcolor(COULEUR_TEXTE);
	setbkcolor(COULEUR_FOND_TEXTE);
	settextstyle(SANSSERIF_FONT, HORIZ_DIR, 2);
	setfillstyle(SOLID_FILL, COULEUR_FOND_TEXTE);

	/*	On calcule où commence le paramètre. */
	gauche_parametre = LARGEUR_ECRAN - BORDURE_ECRAN_DROITE + 
					   DISTANCE_PLAQUE_PARAMETRES + BORDURE_BOITE_PARAMETRES;	
	gauche_nombre = gauche_parametre + longueur_parametre_plus_long() + 3;

	/*	On efface l'ancienne donnée. */
	setfillstyle(SOLID_FILL, COULEUR_FOND_TEXTE);
	bar(gauche_nombre, (int) (BORDURE_ECRAN_HAUT + (4.5) * DISTANCE_ENTRE_PARAMETRES),
		gauche_nombre + textwidth(CHAINE_JUSTIFICATION),
		(int) (BORDURE_ECRAN_HAUT + (4.5) * DISTANCE_ENTRE_PARAMETRES) + textheight("X"));

	/*	On affiche la nouvelle donnée. */
	sprintf(nombre_a_afficher, "%li", nb_arbres);
	outtextxy(gauche_nombre + textwidth(CHAINE_JUSTIFICATION) - textwidth(nombre_a_afficher),
			  (int) (BORDURE_ECRAN_HAUT + (4.5) * DISTANCE_ENTRE_PARAMETRES), nombre_a_afficher);
}





void effectuer_pause(void)
{
	(void) getch_graph();
}



void effectuer_delai(int duree)
{
	delay(duree);
}