/*****************************************************************************************************/
/* Par : Chuan Dong																				     */
/*	   : Dominic Blanchard																			 */
/*																									 */
/* Fichier : util.c												                            	     */
/*																									 */
/* Date : 3/11/2013																				     */
/*																									 */
/* Ce module offre diverses fonctions utilitaires :													 */
/*																									 */
/*									- plafond						Par: Dominic Blanchard			 */
/*									- nb_aleatoire        			Par: Chuan Dong					 */
/*									- nb_aleatoire_0_1				Par: Chuan Dong	 				 */
/*									- est_dans_intervalle			Par: Chuan Dong					 */				
/*									- valeur_absolue    			Par: Chuan Dong					 */
/*									- maximum            			Par: Chuan Dong					 */
/*									- entier_valide       			Par: Chuan Dong					 */																				 
/*									- reel_valide         			Par: Chuan Dong					 */
/*									- tester_plafond     			Par: Dominic Blanchard			 */
/*																	Par: Chuan Dong					 */																								 
/*									- tester_est_dans_intervalle	Par: Dominic Blanchard			 */
/*									- tester_valeur_absolue			Par: Dominic Blanchard			 */
/*									- tester_maximum      			Par: Dominic Blanchard			 */
/*																									 */
/*****************************************************************************************************/


/*****************************************************************************************************/
/*							INCLUSION DE LIBRAIRIES							                         */
/*****************************************************************************************************/
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "module_util.h"

/*****************************************************************************************************/
/*							DÉCLARATIONS DE FONCTIONS                                                */
/*****************************************************************************************************/
/*
	PLAFOND
 
	Cette fonction retourne le plafond d'un nombre réel.
	Le plafond correspond à la plus petite valeur entière supérieure ou égale au nombre
	reçu.
*/
long int plafond(double x)
{
    return (long int)ceil(x);
}


/*
	NB_ALEATOIRE
 
	Cette fonction retourne un nombre aléatoire entier dans l'intervalle [min, max].
	Chaque valeur de l'intervalle possède la même probabilité d'être choisie.
*/
int nb_aleatoire(int min, int max)
{
    return min + (int)(rand() / (RAND_MAX + 0.0000001) * (max - min + 1));
}


/*
	NB_ALEATOIRE_0_1

	Cette fonction retourne un nombre aléatoire réel dans l'intervalle [0, 1].
	Chaque valeur de l'intervalle possède la même probabilité d'être choisie.
*/
double nb_aleatoire_0_1(void)
{
    return rand() / (double)(RAND_MAX);
}


/*
	EST_DANS_INTERVALLE
 
	Cette fonction retourne 1 si la valeur "x" se trouve dans l'intervalle [x1, x2],
	sinon, elle retourne 0.
*/
int est_dans_intervalle(int x, int x1, int x2)
{
    if(x1 <= x && x <= x2) return 1;
    else return 0;
}


/*
	VALEUR_ABSOLUE
 
	Cette fonction retourne la valeur absolue d'un nombre réel.
*/
double valeur_absolue(double x)
{
    return fabs(x);
}


/*
	MAXIMUM
 
	Cette fonction retourne la plus grande des deux valeurs reçues.
*/
double maximum(double nb1, double nb2)
{
    return nb1>nb2 ? nb1 : nb2;
}


/*
	ENTIER_VALIDE
 
	Cette fonction saisit un entier au clavier et recommence jusqu'à ce que
	le nombre lu se trouve dans l'intervalle [min, max] reçu.
*/
int entier_valide(int min, int max, const char * message_invitation,
                  const char * message_erreur)
{
    int nb_lu;
    
    printf(message_invitation);
    scanf_s("%i", &nb_lu);
 
    /* 
		Vérifie si nb_lu est dans [min,max], sinon on va afficher
		une message d'erreur et ensuite on demande à l'utilisateur 
		d'entre encore une fois une valeur.
	*/
    while(min > nb_lu || nb_lu > max)
    {
		/* Si on entre une chaîne contenant un caractère non-numérique								 */
		while(getchar() != '\n'); 

        printf(message_erreur);
        scanf_s("%i", &nb_lu);
    }
    
    return nb_lu;
}


/*
	REEL_VALIDE
 
	Cette fonction saisit un nombre réel au clavier et recommence jusqu'à ce que
	le nombre lu se trouve dans l'intervalle [min, max] reçu.
*/
double reel_valide(double min, double max, const char * message_invitation,
                   const char * message_erreur)
{
    double nb_lu;
    
    printf(message_invitation);
    scanf_s("%lf", &nb_lu);
    
	/* 
		On vérifie si nb_lu est dans [min,max], sinon on va afficher
		une message d'erreur et ensuite on demande à l'utilisateur 
		d'entrer encore une fois une valeur.
	*/
    while(min > nb_lu || nb_lu > max)
    {
		/* On test si la valeur entrée par l'utilisateur est une chaîne contenant un caractère 
		   non-numérique si oui, on redemande à l'utilisateur d'entrer une autre valeur				 */
		while(getchar() != '\n'); 

        printf(message_erreur);
        scanf_s("%lf", &nb_lu);
    }
    
    return nb_lu;
}


/*
	TESTER_PLAFOND

	Cette fonction affiche le test de la fonction plafond qui est de retourner la plus petite valeur 
	entière supérieure ou égale au nombre reçu.
	
	PARAMÈTRES : Aucun.
	
	VALEUR DE RETOUR : Aucun.
*/
void tester_plafond(void)
{
	printf(" TEST : PLAFOND\n\n\n");
	
	/* Affiche le résultat du test 1.    [plafond(-1,3)]											*/
	printf("      Test #1\n");
	printf("  x :  -1.3         Valeur attendue :  -1\n");	
	printf("                    Valeur obtenue  :  %i\n",plafond(-1.3));

	/* Affiche le résultat du test 2.    [plafond(2)]										  	    */
	printf("\n\n      Test #2\n");
	printf("  x :   2           Valeur attendue :   2\n");	
	printf("                    Valeur obtenue  :   %i\n",plafond(2));
	
	/* Affiche le résultat du test 3.    [plafond(2,4)]										  	    */
	printf("\n\n      Test #3\n");
	printf("  x :   2.4         Valeur attendue :   3\n");	
	printf("                    Valeur obtenue  :   %i\n",plafond(2.4));
	
	/* Affiche le résultat du test 4.    [plafond(2,97)]										    */
	printf("\n\n      Test #4\n");
	printf("  x :   2.97        Valeur attendue :   3\n");	
	printf("                    Valeur obtenue  :   %i\n",plafond(2.97));

	printf("\n\n");
}


/*
	TESTER_EST_DANS_INTERVALLE

	Cette fonction affiche le test de la fonction est_dans_intervalle qui est de retourner un 1 si la
	valeur "x" se trouve dans l'intervalle donnée.
	
	PARAMÈTRES : Aucun.
	
	VALEUR DE RETOUR : Aucun.
*/
void tester_est_dans_intervalle(void)
{
	printf(" TEST : EST_DANS_INTERVALLE\n\n\n");
	
	/* Affiche le résultat du test 1.    [est_dans_intervalle(0,-5,5)]                              */
	printf("      Test #1\n\n");
	printf("  x                 :  0         Valeur attendue :    1\n");	
	printf("  borne_inferieure  : -5         Valeur obtenue  :    %i\n",est_dans_intervalle(0,-5,5));
	printf("  borne_superieure  :  5\n\n");
	
	/* Affiche le résultat du test 2.    [est_dans_intervalle(0,0,5)]                               */
	printf("      Test #2\n");
	printf("  x                 :  0         Valeur attendue :    1\n");	
	printf("  borne_inferieure  :  0         Valeur obtenue  :    %i\n",est_dans_intervalle(0,0,5));
	printf("  borne_superieure  :  5\n\n");

	/* Affiche le résultat du test 3.    [est_dans_intervalle(0,-5,0)]                              */
	printf("      Test #3\n");
	printf("  x                 :  0         Valeur attendue :    1\n");	
	printf("  borne_inferieure  : -5         Valeur obtenue  :    %i\n",est_dans_intervalle(0,-5,0));
	printf("  borne_superieure  :  0\n\n");

	/* Affiche le résultat du test 4.    [est_dans_intervalle(0,2,5)]                               */
	printf("      Test #4\n");
	printf("  x                 :  0         Valeur attendue :    0\n");	
	printf("  borne_inferieure  :  2         Valeur obtenue  :    %i\n",est_dans_intervalle(0,2,5));
	printf("  borne_superieure  :  5\n\n");

	/* Affiche le résultat du test 5.    [est_dans_intervalle(0,5,-5)]                              */
	printf("      Test #5\n");
	printf("  x                 :  0         Valeur attendue :    0\n");	
	printf("  borne_inferieure  :  5         Valeur obtenue  :    %i\n",est_dans_intervalle(0,5,-5));
	printf("  borne_superieure  : -5\n\n");

	printf("\n\n");
}


/*
	TESTER_VALEUR_ABSOLUE

	Cette fonction affiche le test de la fonction valeur_abosule qui retourne la valeur
	absulue d'un nombre réel.

	PARAMÈTRES : Aucun.
	
	VALEUR DE RETOUR : Aucun.
*/
void tester_valeur_absolue(void)
{
	printf(" TEST : VALEUR_ABSOLUE\n\n\n");

	/* Affiche le résultat du test 1.    [valeur_absolue(-1,3)]									    */
	printf("      Test #1\n");
	printf("  x :  -1.3         Valeur attendue :    1.3\n");	
	printf("                    Valeur obtenue  :    %.1f\n",valeur_absolue(-1.3));

	/* Affiche le résultat du test 2.    [valeur_absolue(0)]									    */
	printf("      Test #2\n");
	printf("  x :   0           Valeur attendue :    0\n");	
	printf("                    Valeur obtenue  :    %.0f\n",valeur_absolue(0));

	/* Affiche le résultat du test 3.    [valeur_absolue(2)]									    */
	printf("      Test #3\n");
	printf("  x :   2           Valeur attendue :    2\n");	
	printf("                    Valeur obtenue  :    %.0f\n",valeur_absolue(2));

	printf("\n\n");
}


/*
	TESTER_MAXIMUM

	Cette fonction affiche le test de la fonction maximum qui est de retourne la plus grande des 
	deux valeurs reçues. 
	
	PARAMÈTRES : Aucun.
	
	VALEUR DE RETOUR : Aucun.
*/
void tester_maximum(void)
{
	printf(" TEST : MAXIMUM\n\n\n");
	
	/* Affiche le résultat du test 1.    [maximum(-5,5)]										    */
	printf("      Test #1\n");
	printf("  nb1 : -5           Valeur attendue :   5\n");	
	printf("  nb2 :  5           Valeur obtenue  :   %.0f\n\n",maximum(-5,5));
	
	/* Affiche le résultat du test 2.    [maximum(5,-5)]										    */
	printf("      Test #2\n");
	printf("  nb1 :  5           Valeur attendue :   5\n");	
	printf("  nb2 : -5           Valeur obtenue  :   %.0f\n\n",maximum(5,-5));
	
	/* Affiche le résultat du test 3.    [maximum(5,5)]										        */
	printf("      Test #3\n");
	printf("  nb1 :  5           Valeur attendue :   5\n");	
	printf("  nb2 :  5           Valeur obtenue  :   %.0f\n\n",maximum(5,5));
	
	printf("\n\n");
}


