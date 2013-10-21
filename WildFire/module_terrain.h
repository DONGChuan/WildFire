/****************************************************************************************
 Par  : Frédérick Henri
 Date : 10/09/2013

 Ce module implémente le type t_terrain. Un terrain est une surface rectangulaire
 découpée en petits carrés (en cases) qui permet de modéliser une forêt. Chaque carré
 peut :
	- être vide (contenir du gazon);
	- être occupé par un arbre;
	- être en feu;
	- être occupé par des cendres (les restes d'un arbre brûlé).

 Il contient les fonctions suivantes :
	- generer_terrain_groupe    : Remplit un terrain en regroupant les arbres.
	- generer_terrain_aleatoire : Remplit aléatoirement un terrain.
	- nb_arbres                 : Retourne le nombre d'arbres sur un terrain.
	- nb_feux                   : Retourne le nombre de feux sur le terrain.
    - nb_arbres_brules          : Retourne le nombre d'arbres brûlés sur le terrain.
	- etat_case                 : Retourne le contenu d'un espace sur le terrain.
	- modifier_etat_case        : Modifie le contenu d'un espace sur le terrain.
	- copier_terrain            : Crée une copie d'un terrain.
	- remplacer_etat            : Remplace toutes les occurrences d'un état dans le
								  terrain par un autre état.
****************************************************************************************/




#if !defined(MODULE_TERRAIN)
#define MODULE_TERRAIN




/****************************************************************************************
							DÉFINITIONS DE CONSTANTES
****************************************************************************************/
/* La longueur et la largeur d'un terrain (exprimés en petits carrés). */
#define LONGUEUR_TERRAIN	50
#define LARGEUR_TERRAIN		70




/****************************************************************************************
							DÉFINITIONS DE TYPES
****************************************************************************************/
/* t_etat : Les différents états de chacune des cases du terrain. */
typedef enum etat_case
{
	CASE_VIDE,
	CASE_ARBRE,
	CASE_FEU,
	CASE_ARBRE_BRULE
} t_etat;

/* t_terrain : Le type représentant un terrain. */
typedef t_etat t_terrain[LONGUEUR_TERRAIN][LARGEUR_TERRAIN];




/****************************************************************************************
							DÉCLARATIONS DE FONCTIONS
****************************************************************************************/
/*
	GENERER_TERRAIN_GROUPE

	Cette procédure vide le terrain reçu et y positionne des groupes de "taille_groupe"
	arbres tous à une distance "distance" les uns des autres. Chaque groupe sera réparti
	sur plafond(racine(taille_groupe)) lignes.

	À titre d'exemple, si "taille_groupe" vaut 3 et "distance" vaut 2, un terrain
	7 x 17 ressemblerait à ceci :
		AA..AA..AA..AA..A
        A...A...A...A...A
		.................
		.................
		AA..AA..AA..AA..A
		A...A...A...A...A
		.................

	PARAMÈTRES :
		- terrain_a_generer : (SORTIE) Le terrain à remplir (type : t_terrain).
		- taille_groupe : Le nombre d'arbres dans chaque groupe (type : int).
						  On suppose que cette valeur est supérieure à 0.
		- distance : La distance entre chaque groupe d'arbres (type : int).
					 On suppose que cette valeur est supérieure ou égale à 0.

	VALEUR DE RETOUR : Aucune.
*/
void generer_terrain_groupe(t_terrain terrain_a_generer, int taille_groupe,
							int distance);



/*
	GENERER_TERRAIN_ALEATOIRE

	Cette procédure vide le terrain reçu et y positionne aléatoirement des arbres
	de façon à ce que "pourcentage_recouvrement" pourcent des carrés contiennent
	un arbre.

	À titre d'exemple, si "pourcentage_recouvrement" vaut 0.4, un terrain 5 x 5
	pourrait ressembler à ceci :
		AAA..
        .A..A
		..A.A
		..AA.
		A....

	PARAMÈTRES :
		- terrain_a_generer : (SORTIE) Le terrain à remplir (type : t_terrain).
		- pourcentage_recouvrement : Le pourcentage des carrés non vides (type : double).
									 On suppose que ce nombre se situe dans l'intervalle
									 [0, 1].

	VALEUR DE RETOUR : Aucune.

	ANTÉCÉDENT : Cette procédure utilise la fonction rand(). On suppose donc que
				 le générateur de nombre aléatoire à été initialisé à l'aide de
				 la fonction srand() avant l'appel de generer_terrain_aleatoire.
*/
void generer_terrain_aleatoire(t_terrain terrain_a_generer, 
							   double pourcentage_recouvrement);



/*
	NB_ARBRES

	Cette fonction dénombre les arbres sur le terrain.

	PARAMÈTRES :
		- terrain_a_consulter : Le terrain à consulter (type : const t_terrain).

	VALEUR DE RETOUR : Le nombre d'arbres sur le terrain (type : long int).
					   Cette valeur sera toujours dans l'intervalle
					   [0, LONGUEUR_TERRAIN * LARGEUR_TERRAIN].
*/
long int nb_arbres(const t_terrain terrain_a_consulter);


/*
	NB_FEUX

	Cette fonction dénombre les feux sur le terrain.

	PARAMÈTRES :
		- terrain_a_consulter : Le terrain à consulter (type : const t_terrain).

	VALEUR DE RETOUR : Le nombre de feux sur le terrain (type : long int).
					   Cette valeur sera toujours dans l'intervalle
					   [0, LONGUEUR_TERRAIN * LARGEUR_TERRAIN].
*/
long int nb_feux(const t_terrain terrain_a_consulter);



/*
	NB_ARBRES_BRULES

	Cette fonction dénombre les arbres brulés sur le terrain.

	PARAMÈTRES :
		- terrain_a_consulter : Le terrain à consulter (type : const t_terrain).

	VALEUR DE RETOUR : Le nombre d'arbres brulés sur le terrain (type : long int).
					   Cette valeur sera toujours dans l'intervalle
					   [0, LONGUEUR_TERRAIN * LARGEUR_TERRAIN].
*/
long int nb_arbres_brules(const t_terrain terrain_a_consulter);



/*
	ETAT_CASE

	Cette fonction retourne l'état d'une case du terrain.

	PARAMÈTRES :
		- terrain_a_consulter : Le terrain à consulter (type : const t_terrain).
		- ligne   : La ligne de la case à consulter (type : int).
				    On suppose que ce nombre se situe dans l'intervalle
				    [0, LONGUEUR_TERRAIN[.
		- colonne : La colonne de la case à consulter (type : int).
				    On suppose que ce nombre se situe dans l'intervalle
				    [0, LARGEUR_TERRAIN[.

	VALEUR DE RETOUR : L'état de la case consultée (type : t_etat).
*/
t_etat etat_case(const t_terrain terrain_a_consulter, int ligne, int colonne);



/*
	MODIFIER_ETAT_CASE

	Cette fonction modifie l'état d'une case du terrain.

	PARAMÈTRES :
		- terrain_a_modifier : Le terrain à modifier (type : t_terrain).
		- ligne   : La ligne de la case à modifier (type : int).
				    On suppose que ce nombre se situe dans l'intervalle
				    [0, LONGUEUR_TERRAIN[.
		- colonne : La colonne de la case à consulter (type : int).
				    On suppose que ce nombre se situe dans l'intervalle
				    [0, LARGEUR_TERRAIN[.
		- nouvel_etat : Le nouvel état de la case (type : t_etat).

	VALEUR DE RETOUR : Aucune.
*/
void modifier_etat_case(t_terrain terrain_a_modifier, int ligne, int colonne,
						t_etat nouvel_etat);



/*
	COPIER_TERRAIN

	Cette procédure copie le terrain "source" dans le terrain "destination".

	PARAMÈTRES :
		- destination : Le terrain à écraser (type : t_terrain).
		- source      : Le terrain à copier (type : const t_terrain).

	VALEUR DE RETOUR : Aucune.
*/
void copier_terrain(t_terrain destination, const t_terrain source);



/*
	REMPLACER_ETAT

	Cette procédure remplace tous les états d'un certain type par un autre état
	dans un terrain. Par exemple, on peut remplacer toutes les CASE_FEU par 
	une CASE_ARBRE_BRULE.

	PARAMÈTRES :
		- terrain_a_modifier : Le terrain à modifier (type : t_terrain).
		- etat_initial       : L'état à remplacer (type : t_etat).
		- nouvel_etat        : L'état qui remplace l'état initial (type : t_etat).

	VALEUR DE RETOUR : Aucune.
*/
void remplacer_etat(t_terrain terrain_a_modifier, t_etat etat_initial,
				    t_etat nouvel_etat);




#endif