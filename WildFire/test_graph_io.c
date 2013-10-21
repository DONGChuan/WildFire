/****************************************************************************************
	Par  : Frédérick Henri
	Date : 12/09/2013

	Ce programme offre un exemple d'utilisation du module graph_io.
****************************************************************************************/




#include "graph_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>




/****************************************************************************************
								DÉCLARATIONS DE FONCTIONS
****************************************************************************************/
/*
	NB_ALEATOIRE

	Cette fonction retourne un nombre aléatoire entier dans l'intervalle [min, max].
	Chaque valeur de l'intervalle possède la même probabilité d'être choisie.

	PARAMÈTRES :
		- min : La plus petite valeur pouvant être générée (type : int).
		- max : La plus grande valeur pouvant être générée (type : int).
				On suppose que min est plus petit ou égal à max.
	
	VALEUR DE RETOUR : Un nombre dans l'intervalle [min, max] (type : int).
*/
int nb_aleatoire(int min, int max);



/****************************************************************************************
								FONCTION MAIN()
****************************************************************************************/
int main(void)
{
	/*	On passe en mode graphique. */
	if (!demarrer_mode_graphique(50, 50))
	{
		printf("Impossible de passer en mode graphique.");
		return EXIT_FAILURE;
	}

	/*	On dessine l'interface graphique. */
	dessiner_interface();

	/*	On dessine trois arbres. */
	dessiner_case(0, 0, ARBRE);
	dessiner_case(25, 25, ARBRE);
	dessiner_case(40, 10, ARBRE);

	/*	On dessine un feu. */
	dessiner_case(5, 45, FEU);

	/*	On met à jour les données à droite. */
	mettre_a_jour_type_simulation(1);
	mettre_a_jour_taille_groupes_arbres(-1);
	mettre_a_jour_distance_groupes_arbres(-1);
	mettre_a_jour_nb_initial_arbres(4);
	mettre_a_jour_nb_courant_arbres(3);

	/*	On effectue une pause. */
	effectuer_pause();

	fermer_mode_graphique();

	return EXIT_SUCCESS;
}




/****************************************************************************************
								DÉFINITIONS DE FONCTIONS
****************************************************************************************/
/*
	Explication de l'expression :
	- rand()
	  Une valeur entière dans l'intervalle [0, RAND_MAX].
	- rand() / (RAND_MAX + 0.0000001)
	  Une valeur réelle dans l'intervalle [0, 1[.
	- rand() / (RAND_MAX + 0.0000001) * (max - min + 1)
	  Une valeur réelle dans l'intervalle [0, max - min + 1[.
	- (int)(rand() / (RAND_MAX + 0.0000001) * (max - min + 1))
	  Une valeur entière dans l'intervalle [0, max - min].
	- min + (int)(rand() / (RAND_MAX + 0.0000001) * (max - min + 1))
	  Une valeur entière dans l'intervalle [min, max].
*/
int nb_aleatoire(int min, int max)
{
	return min + (int)(rand() / (RAND_MAX + 0.0000001) * (max - min + 1));
}