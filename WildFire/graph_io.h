/****************************************************************************************
	FICHIER : GRAPH_IO.H
	PAR     : Frederick Henri
	DATE    : 19/09/2013
	POUR    : INF145

	Ce module definit l'ensemble des fonctions graphiques necessaires pour
	simuler la propagation d'un feu dans une pépinière.

	À NOTER : Pour pouvoir utiliser ce module, assurez-vous d'utiliser 
	          le jeu de caractères MBCS (Projet->Propriétés de ...->Général).
****************************************************************************************/




#if !defined(MODULE_GRAPH_IO)
#define MODULE_GRAPH_IO




/****************************************************************************************
							DÉFINITIONS DE MACROS
****************************************************************************************/
/*	Le positionnement des composantes graphiques. */
#define BORDURE_ECRAN_GAUCHE		20	/* Espace à gauche de la plaque (en pixels). */
#define BORDURE_ECRAN_DROITE	   400	/* Espace à droite de la plaque (en pixels). */
#define BORDURE_ECRAN_HAUT			20	/* Espace au dessus de la plaque (en pixels). */
#define BORDURE_ECRAN_BAS			20	/* Espace sous la plaque (en pixels). */
#define TAILLE_GRILLAGE_PLAQUE		 1	/* Espace entre les cases (en pixels). */
#define CONTOUR_PLAQUE				 3	/* Espace autour du terrain (en pixels). */
#define DISTANCE_PLAQUE_PARAMETRES  25	/* Distance entre le terrain et les paramètres.*/
#define DISTANCE_ENTRE_PARAMETRES	50	/* Distance verticale entre chaque paramètre. */
#define BORDURE_BOITE_PARAMETRES	10	/* Bordure de la boîte listant les paramètres. */

/*	Les couleurs utilisées dans le jeu. */
/* Fond de l'écran. */
#define COULEUR_DE_FOND			COLOR(150, 150, 150)	/* Fond de l'écran. */

/* Cases et terrain. */
#define COULEUR_CASE_VIDE		COLOR(219, 249, 220)	/* Case vide. */
#define COULEUR_CASE_ARBRE		COLOR(0,   150,   0)	/* Case avec un arbre. */
#define COULEUR_CASE_FEU		COLOR(234, 125,  28)	/* Case en feu. */
#define COULEUR_CASE_CENDRES	COLOR(80,   80,  80)	/* Case avec des cendres. */
#define COULEUR_CONTOUR_FONCE	COLOR(65,   65,  65)	/* Contour case et plaque. */
#define COULEUR_CONTOUR_PALE	COLOR(248, 248, 248)	/* Contour case et plaque. */

/*	Texte. */
#define COULEUR_TEXTE			COLOR(  0,   0,   0)	/* Message à l'utilisateur. */
#define COULEUR_FOND_TEXTE		COLOR(255, 255, 255)	/* Fond du texte. */

/* Les types de cases possibles pouvant être dessinées. */
typedef enum
{
	VIDE,
	ARBRE,
	FEU,
    CENDRES
} t_type_case;




/****************************************************************************************
							DÉCLARATIONS DE FONCTIONS						
****************************************************************************************/
/*
	DEMARRER_MODE_GRAPHIQUE

	Cette fonction initialise le mode graphique.

	PARAMÈTRES :
		- hauteur_terrain : La hauteur du terrain exprimée en cases
						   (type : int).
		- largeur_terrain : La largeur du terrain exprimée en cases
						   (type : int).

	VALEUR DE RETOUR : 1 en cas de succès et 0 dans le cas contraire
					   (type : int).
*/
int demarrer_mode_graphique(int hauteur_terrain, int largeur_terrain);


/*
	FERMER_MODE_GRAPHIQUE

	Cette fonction ferme la fenêtre graphique.

	PARAMÈTRES : Aucun.

	VALEUR DE RETOUR : Aucune.

	ANTÉCÉDENT : On suppose que la fonction demarrer_mode_graphique a
				 prealablement été appelé.
*/
void fermer_mode_graphique(void);



/*
	DESSINER_INTERFACE

	Cette fonction dessine le fond de l'écran, un terrain vide et la zone des paramètres.

	PARAMÈTRES : Aucun.

	VALEUR DE RETOUR : Aucune.

	ANTÉCÉDENT : On suppose que la fonction demarrer_mode_graphique a
				 prealablement été appelé.
*/
void dessiner_interface(void);



/*
	DESSINER_CASE

	Cette fonction dessine la case demandée dans le terrain avec le contenu spécifié.

	PARAMÈTRES :
		- ligne : La ligne où la case doit être dessinée (type : int).
				  Cette valeur doit être dans l'intervalle 
				  [0, HAUTEUR_PLAQUE[.
		- colonne : La colonne où la case doit être dessinée (type : int).
				  Cette valeur doit être dans l'intervalle 
				  [0, LARGEUR_PLAQUE[.
	    - contenu : Le contenu de la case à dessiner (type : t_type_case).

	VALEUR DE RETOUR : Aucune.
*/
void dessiner_case(int ligne, int colonne, t_type_case contenu);



/*
	METTRE_A_JOUR_TYPE_SIMULATION

	Cette procédure met à jour le type de simulation dans l'interface.
	Si la simulation est aléatoire, elle "vide" la taille des groupes et la distance entre
	les groupes.

	PARAMÈTRES :
		- aleatoire : 1 si la simulation est aléatoire et 0 sinon (type : int).

	VALEUR DE RETOUR : Aucune.
*/
void mettre_a_jour_type_simulation(int aleatoire);



/*
	METTRE_A_JOUR_TAILLE_GROUPES_ARBRES

	Cette procédure met à jour la taille des groupes d'arbres.
	Si la valeur reçue est négative, on affiche un trait à la place d'un
	nombre.

	PARAMÈTRES :
		- taille : La taille des groupes d'arbres (type : int).

	VALEUR DE RETOUR : Aucune.
*/
void mettre_a_jour_taille_groupes_arbres(int taille);



/*
	METTRE_A_JOUR_DISTANCE_GROUPES_ARBRES

	Cette procédure met à jour la distance entre les groupes d'arbres.
	Si la valeur reçue est négative, on affiche un trait à la place d'un
	nombre.

	PARAMÈTRES :
		- distance : La distance entre les groupes d'arbres (type : int).
					 On suppose que cette valeur est supérieur ou égale à 0.

	VALEUR DE RETOUR : Aucune.
*/
void mettre_a_jour_distance_groupes_arbres(int distance);



/*
	METTRE_A_JOUR_NB_INITIAL_ARBRES

	Cette procédure met à jour le nombre initial d'arbres.

	PARAMÈTRES :
		- nb_arbres : Le nombre initial d'arbres (type : int).
					  On suppose que cette valeur est supérieur ou égale à 0.

	VALEUR DE RETOUR : Aucune.
*/
void mettre_a_jour_nb_initial_arbres(int nb_arbres);



/*
	METTRE_A_JOUR_NB_COURANT_ARBRES

	Cette procédure met à jour le nombre courant d'arbres.

	PARAMÈTRES :
		- nb_arbres : Le nombre courant d'arbres (type : int).
					  On suppose que cette valeur est supérieur ou égale à 0.

	VALEUR DE RETOUR : Aucune.
*/
void mettre_a_jour_nb_courant_arbres(int nb_arbres);



/*
	EFFECTUER_PAUSE

	Cette fonction permet d'effectuer une pause jusqu'a ce que l'on appuie sur
	une touche.

	PARAMÈTRES : Aucun.

	VALEUR DE RETOUR : Aucune.

	ANTÉCÉDENT : On suppose que la fonction demarrer_mode_graphique a
				 prealablement été appelé.
*/
void effectuer_pause(void);



/*
	EFFECTUER_DELAI

	Cette fonction permet d'effectuer un délai dont la durée est exprimée en ms.

	PARAMÈTRES :
		- duree : La durée du délai à effectuer en millisecondes (type : int).

	VALEUR DE RETOUR : Aucune.
*/
void effectuer_delai(int duree);




#endif