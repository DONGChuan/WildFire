/****************************************************************************************
 Par  : Fr�d�rick Henri
 Date : 10/09/2013

 Ce module impl�mente le type t_terrain. Un terrain est une surface rectangulaire
 d�coup�e en petits carr�s (en cases) qui permet de mod�liser une for�t. Chaque carr�
 peut :
	- �tre vide (contenir du gazon);
	- �tre occup� par un arbre;
	- �tre en feu;
	- �tre occup� par des cendres (les restes d'un arbre br�l�).

 Il contient les fonctions suivantes :
	- generer_terrain_groupe    : Remplit un terrain en regroupant les arbres.
	- generer_terrain_aleatoire : Remplit al�atoirement un terrain.
	- nb_arbres                 : Retourne le nombre d'arbres sur un terrain.
	- nb_feux                   : Retourne le nombre de feux sur le terrain.
    - nb_arbres_brules          : Retourne le nombre d'arbres br�l�s sur le terrain.
	- etat_case                 : Retourne le contenu d'un espace sur le terrain.
	- modifier_etat_case        : Modifie le contenu d'un espace sur le terrain.
	- copier_terrain            : Cr�e une copie d'un terrain.
	- remplacer_etat            : Remplace toutes les occurrences d'un �tat dans le
								  terrain par un autre �tat.
****************************************************************************************/




#if !defined(MODULE_TERRAIN)
#define MODULE_TERRAIN




/****************************************************************************************
							D�FINITIONS DE CONSTANTES
****************************************************************************************/
/* La longueur et la largeur d'un terrain (exprim�s en petits carr�s). */
#define LONGUEUR_TERRAIN	50
#define LARGEUR_TERRAIN		70




/****************************************************************************************
							D�FINITIONS DE TYPES
****************************************************************************************/
/* t_etat : Les diff�rents �tats de chacune des cases du terrain. */
typedef enum etat_case
{
	CASE_VIDE,
	CASE_ARBRE,
	CASE_FEU,
	CASE_ARBRE_BRULE
} t_etat;

/* t_terrain : Le type repr�sentant un terrain. */
typedef t_etat t_terrain[LONGUEUR_TERRAIN][LARGEUR_TERRAIN];




/****************************************************************************************
							D�CLARATIONS DE FONCTIONS
****************************************************************************************/
/*
	GENERER_TERRAIN_GROUPE

	Cette proc�dure vide le terrain re�u et y positionne des groupes de "taille_groupe"
	arbres tous � une distance "distance" les uns des autres. Chaque groupe sera r�parti
	sur plafond(racine(taille_groupe)) lignes.

	� titre d'exemple, si "taille_groupe" vaut 3 et "distance" vaut 2, un terrain
	7 x 17 ressemblerait � ceci :
		AA..AA..AA..AA..A
        A...A...A...A...A
		.................
		.................
		AA..AA..AA..AA..A
		A...A...A...A...A
		.................

	PARAM�TRES :
		- terrain_a_generer : (SORTIE) Le terrain � remplir (type : t_terrain).
		- taille_groupe : Le nombre d'arbres dans chaque groupe (type : int).
						  On suppose que cette valeur est sup�rieure � 0.
		- distance : La distance entre chaque groupe d'arbres (type : int).
					 On suppose que cette valeur est sup�rieure ou �gale � 0.

	VALEUR DE RETOUR : Aucune.
*/
void generer_terrain_groupe(t_terrain terrain_a_generer, int taille_groupe,
							int distance);



/*
	GENERER_TERRAIN_ALEATOIRE

	Cette proc�dure vide le terrain re�u et y positionne al�atoirement des arbres
	de fa�on � ce que "pourcentage_recouvrement" pourcent des carr�s contiennent
	un arbre.

	� titre d'exemple, si "pourcentage_recouvrement" vaut 0.4, un terrain 5 x 5
	pourrait ressembler � ceci :
		AAA..
        .A..A
		..A.A
		..AA.
		A....

	PARAM�TRES :
		- terrain_a_generer : (SORTIE) Le terrain � remplir (type : t_terrain).
		- pourcentage_recouvrement : Le pourcentage des carr�s non vides (type : double).
									 On suppose que ce nombre se situe dans l'intervalle
									 [0, 1].

	VALEUR DE RETOUR : Aucune.

	ANT�C�DENT : Cette proc�dure utilise la fonction rand(). On suppose donc que
				 le g�n�rateur de nombre al�atoire � �t� initialis� � l'aide de
				 la fonction srand() avant l'appel de generer_terrain_aleatoire.
*/
void generer_terrain_aleatoire(t_terrain terrain_a_generer, 
							   double pourcentage_recouvrement);



/*
	NB_ARBRES

	Cette fonction d�nombre les arbres sur le terrain.

	PARAM�TRES :
		- terrain_a_consulter : Le terrain � consulter (type : const t_terrain).

	VALEUR DE RETOUR : Le nombre d'arbres sur le terrain (type : long int).
					   Cette valeur sera toujours dans l'intervalle
					   [0, LONGUEUR_TERRAIN * LARGEUR_TERRAIN].
*/
long int nb_arbres(const t_terrain terrain_a_consulter);


/*
	NB_FEUX

	Cette fonction d�nombre les feux sur le terrain.

	PARAM�TRES :
		- terrain_a_consulter : Le terrain � consulter (type : const t_terrain).

	VALEUR DE RETOUR : Le nombre de feux sur le terrain (type : long int).
					   Cette valeur sera toujours dans l'intervalle
					   [0, LONGUEUR_TERRAIN * LARGEUR_TERRAIN].
*/
long int nb_feux(const t_terrain terrain_a_consulter);



/*
	NB_ARBRES_BRULES

	Cette fonction d�nombre les arbres brul�s sur le terrain.

	PARAM�TRES :
		- terrain_a_consulter : Le terrain � consulter (type : const t_terrain).

	VALEUR DE RETOUR : Le nombre d'arbres brul�s sur le terrain (type : long int).
					   Cette valeur sera toujours dans l'intervalle
					   [0, LONGUEUR_TERRAIN * LARGEUR_TERRAIN].
*/
long int nb_arbres_brules(const t_terrain terrain_a_consulter);



/*
	ETAT_CASE

	Cette fonction retourne l'�tat d'une case du terrain.

	PARAM�TRES :
		- terrain_a_consulter : Le terrain � consulter (type : const t_terrain).
		- ligne   : La ligne de la case � consulter (type : int).
				    On suppose que ce nombre se situe dans l'intervalle
				    [0, LONGUEUR_TERRAIN[.
		- colonne : La colonne de la case � consulter (type : int).
				    On suppose que ce nombre se situe dans l'intervalle
				    [0, LARGEUR_TERRAIN[.

	VALEUR DE RETOUR : L'�tat de la case consult�e (type : t_etat).
*/
t_etat etat_case(const t_terrain terrain_a_consulter, int ligne, int colonne);



/*
	MODIFIER_ETAT_CASE

	Cette fonction modifie l'�tat d'une case du terrain.

	PARAM�TRES :
		- terrain_a_modifier : Le terrain � modifier (type : t_terrain).
		- ligne   : La ligne de la case � modifier (type : int).
				    On suppose que ce nombre se situe dans l'intervalle
				    [0, LONGUEUR_TERRAIN[.
		- colonne : La colonne de la case � consulter (type : int).
				    On suppose que ce nombre se situe dans l'intervalle
				    [0, LARGEUR_TERRAIN[.
		- nouvel_etat : Le nouvel �tat de la case (type : t_etat).

	VALEUR DE RETOUR : Aucune.
*/
void modifier_etat_case(t_terrain terrain_a_modifier, int ligne, int colonne,
						t_etat nouvel_etat);



/*
	COPIER_TERRAIN

	Cette proc�dure copie le terrain "source" dans le terrain "destination".

	PARAM�TRES :
		- destination : Le terrain � �craser (type : t_terrain).
		- source      : Le terrain � copier (type : const t_terrain).

	VALEUR DE RETOUR : Aucune.
*/
void copier_terrain(t_terrain destination, const t_terrain source);



/*
	REMPLACER_ETAT

	Cette proc�dure remplace tous les �tats d'un certain type par un autre �tat
	dans un terrain. Par exemple, on peut remplacer toutes les CASE_FEU par 
	une CASE_ARBRE_BRULE.

	PARAM�TRES :
		- terrain_a_modifier : Le terrain � modifier (type : t_terrain).
		- etat_initial       : L'�tat � remplacer (type : t_etat).
		- nouvel_etat        : L'�tat qui remplace l'�tat initial (type : t_etat).

	VALEUR DE RETOUR : Aucune.
*/
void remplacer_etat(t_terrain terrain_a_modifier, t_etat etat_initial,
				    t_etat nouvel_etat);




#endif