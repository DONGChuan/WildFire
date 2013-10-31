/****************************************************************************************
 Par  : Chuan Dong
 Date : 21/10/2013

 Ce module offre diverses fonctions utilitaires :
	- plafond             : Retourne le plafond d'un nombre.
	- nb_aleatoire        : Retourne un nombre al�atoire entier dans un intervalle donn�.
	- nb_aleatoire_0_1    : Retourne un nombre al�atoire r�el dans l'intervalle [0, 1].
	- est_dans_intervalle : Pour savoir si une valeur se trouve dans un intervalle.
	- valeur_absolue      : Retourne la valeur absolue d'un nombre.
	- maximum		      : Retourne le maximum de deux nombres.
	- entier_valide       : Saisit un entier jusqu'� ce que celui-ci se trouve dans un
							intervalle donn�.
	- reel_valide         : Saisit un r�el jusqu'� ce que celui-ci se trouve dans un
							intervalle donn�.
****************************************************************************************/

#include "module_util.h"

#include <stdio.h>
#include <math.h>
#include <time.h> 
#include <stdlib.h> 

/****************************************************************************************
							D�CLARATIONS DE FONCTIONS
****************************************************************************************/
/*
	PLAFOND

	Cette fonction retourne le plafond d'un nombre r�el.
	Le plafond correspond � la plus petite valeur enti�re sup�rieure ou �gale au nombre
	re�u.

	PARAM�TRES :
		- x : Le nombre dont on cherche le plafond (type : Double).
			  On suppose que ce nombre se trouve dans l'intervalle
			  [0, LONG_MAX].

	VALEUR DE RETOUR : Le plafond de la valeur re�ue (type : long int).
*/
long int plafond(double x)
{	
	/* 
		Round() n'exist pas dans math.h pour Windows donc on utilise ici
		floor() qui retourne le plus grand valeur enti�re sup�rieure ou �gale au nombre
		inf�rieur ou �gale au nombre
	*/
	return (long int)floor(x + 0.5);
}

/*
	NB_ALEATOIRE

	Cette fonction retourne un nombre al�atoire entier dans l'intervalle [min, max].
	Chaque valeur de l'intervalle poss�de la m�me probabilit� d'�tre choisie.

	PARAM�TRES :
		- min : La plus petite valeur pouvant �tre g�n�r�e (type : int).
		- max : La plus grande valeur pouvant �tre g�n�r�e (type : int).
				On suppose que min est plus petit ou �gal � max.
	
	VALEUR DE RETOUR : Un nombre dans l'intervalle [min, max] (type : int).
*/
int nb_aleatoire(int min, int max)
{
	return min + (int)(rand() / (RAND_MAX + 0.0000001) * (max - min + 1));
}

/*
	NB_ALEATOIRE_0_1

	Cette fonction retourne un nombre al�atoire r�el dans l'intervalle [0, 1].
	Chaque valeur de l'intervalle poss�de la m�me probabilit� d'�tre choisie.

	PARAM�TRES : Aucun.
	
	VALEUR DE RETOUR : Un nombre dans l'intervalle [0, 1] (type : double).
*/
double nb_aleatoire_0_1(void)
{
	return rand() / (double)(RAND_MAX);
}

/*
	EST_DANS_INTERVALLE

	Cette fonction retourne 1 si la valeur "x" se trouve dans l'intervalle [x1, x2].

	PARAM�TRES :
		- x  : La valeur � tester (type : int).
		- x1 : La borne inf�rieure de l'intervalle (type : int).
		- x2 : La borne sup�rieure de l'intervalle (type : int).
			   On suppose que x2 >= x2.

	VALEUR DE RETOUR : 1 si x se trouve dans l'intervalle [x1, x2] et 0 lorsque ce 
					   n'est pas le cas (type : int).
*/
int est_dans_intervalle(int x, int x1, int x2)
{
	if(x1 <= x && x <= x2) return 1;
	else return 0;
}

/*
	VALEUR_ABSOLUE

	Cette fonction retourne la valeur absolue d'un nombre r�el.

	PARAM�TRES :
		- x : Le nombre dont on cherche la valeur absolue (type : double).

	VALEUR DE RETOUR : La valeur absolue de x (type : double).
*/
double valeur_absolue(double x)
{
	/* In C, abs() serve seulement pour int */
	return fabs(x);
}

/*
	MAXIMUM

	Cette fonction retourne la plus grande des deux valeurs re�ues.

	PARAM�TRES :
		- nb1 : Le premier des deux nombres � comparer (type : double).
		- nb2 : Le second des deux nombres � comparer (type : double).

	VALEUR DE RETOUR : Le maximum entre nb1 et nb2 (type : double).
*/
double maximum(double nb1, double nb2)
{
	return nb1>nb2 ? nb1 : nb2;
}

/*
	ENTIER_VALIDE

	Cette fonction saisit un entier au clavier et recommence jusqu'� ce que
	le nombre lu se trouve dans l'intervalle [min, max] re�u.

	PARAM�TRES :
		- min                : La plus petite valeur permise (type : int).
		- max                : La plus petite grande permise (type : int).
		- message_invitation : Le message invitant l'utilisateur � entrer un
							   nombre (type : const char *).
		- message_erreur     : Le message � afficher lorsque la saisie n'est pas
							   valide (type : const char *).

	VALEUR DE RETOUR : Un nombre entier se trouvant dans l'intervalle [min, max]
					   (type : int).

	EXEMPLE D'APPEL :
		int nb_lu;
		nb_lu = entier_valide(1, 10, "Veuillez entrer un nombre entre 1 et 10 :",
					          "Vous devez entrer un nombre entier dans l'intervalle ");
*/
int entier_valide(int min, int max, const char * message_invitation, 
				  const char * message_erreur)
{
	int nb_lu;

	printf(message_invitation);
	scanf_s("%i", &nb_lu);

	while(min >= nb_lu || nb_lu >= max)
	{
		printf(message_erreur);

		printf(message_invitation);
		scanf_s("%i", &nb_lu);
	}

	return nb_lu;
}



/*
	REEL_VALIDE

	Cette fonction saisit un nombre r�el au clavier et recommence jusqu'� ce que
	le nombre lu se trouve dans l'intervalle [min, max] re�u.

	PARAM�TRES :
		- min                : La plus petite valeur permise (type : double).
		- max                : La plus petite grande permise (type : double).
		- message_invitation : Le message invitant l'utilisateur � entrer un
							   nombre (type : const char *).
		- message_erreur     : Le message � afficher lorsque la saisie n'est pas
							   valide (type : const char *).

	VALEUR DE RETOUR : Un nombre r�el se trouvant dans l'intervalle [min, max]
					   (type : double).

	EXEMPLE D'APPEL :
		double nb_lu;
		nb_lu = reel_valide(0.0, 1.0, "Veuillez entrer un nombre entre 0 et 1 :",
					        "Vous devez entrer un nombre r�el dans l'intervalle ");
*/
double reel_valide(double min, double max, const char * message_invitation, 
				   const char * message_erreur)
{
	double nb_lu;

	printf(message_invitation);
	scanf_s("%lf", &nb_lu);

	while(min >= nb_lu || nb_lu >= max)
	{
		printf(message_erreur);

		printf(message_invitation);
		scanf_s("%lf", &nb_lu);
	}

	return nb_lu;
}

//plafond, est_dans_intervalle, valeur_absolue maximum

void test_plafond()
{
	printf("TEST : PLAFOND\n\n");

	printf("      Test #1 : -1.3 \n");
	printf("      Valeur attendue : -1\n");
	printf("      Valeur obtenue  : %i\n\n", plafond(-1.3));

	printf("      Test #2 : 2 \n");
	printf("      Valeur attendue : 2\n");
	printf("      Valeur obtenue  : %i\n\n", plafond(2));

	printf("      Test #3 : 2.4 \n");
	printf("      Valeur attendue : 3\n");
	printf("      Valeur obtenue  : %i\n\n", plafond(2.4));

	printf("      Test #4 : 2.97 \n");
	printf("      Valeur attendue : 3\n");
	printf("      Valeur obtenue  : %i\n\n", plafond(2.97));
}

void test_est_dans_intervalle()
{
	printf("TEST : EST_DANS_INTERVALLE\n\n");

	printf("      Test #1 : 0 [-5, 5] \n");
	printf("      Valeur attendue : 1\n");
	printf("      Valeur obtenue  : %i\n\n", est_dans_intervalle(0, -5, 5));

	printf("      Test #2 : 0 [0, 5] \n");
	printf("      Valeur attendue : 1\n");
	printf("      Valeur obtenue  : %i\n\n", est_dans_intervalle(0, 0, 5));

	printf("      Test #3 : 0 [-5, 0] \n");
	printf("      Valeur attendue : 1\n");
	printf("      Valeur obtenue  : %i\n\n", est_dans_intervalle(0, -5, 0));

	printf("      Test #4 : 0 [2, 5] \n");
	printf("      Valeur attendue : 0\n");
	printf("      Valeur obtenue  : %i\n\n", est_dans_intervalle(0, 2, 5));

	printf("      Test #5 : 0 [5, -5] \n");
	printf("      Valeur attendue : 0\n");
	printf("      Valeur obtenue  : %i\n\n", est_dans_intervalle(0, 5, -5));
}

void test_valeur_absolue(void)
{
	printf("TEST : VALEUR_ABSOLUE\n\n");

	printf("      Test #1 : -1.3 \n");
	printf("      Valeur attendue : 1.3\n");
	printf("      Valeur obtenue  : %f\n\n", valeur_absolue(-1.3));

	printf("      Test #2 : 0 \n");
	printf("      Valeur attendue : 1\n");
	printf("      Valeur obtenue  : %f\n\n", valeur_absolue(0));

	printf("      Test #3 : 2 \n");
	printf("      Valeur attendue : 2\n");
	printf("      Valeur obtenue  : %f\n\n", valeur_absolue(2));
}

void test_maximum(void)
{
	printf("TEST : MAXIMUM\n\n");

	printf("      Test #1 : (-5, 5)  \n");
	printf("      Valeur attendue : 5\n");
	printf("      Valeur obtenue  : %f\n\n", maximum(-5,5));

	printf("      Test #2 : (5, -5) \n");
	printf("      Valeur attendue : 5\n");
	printf("      Valeur obtenue  : %f\n\n", maximum(5,-5));

	printf("      Test #3 : (5,  5) \n");
	printf("      Valeur attendue : 5\n");
	printf("      Valeur obtenue  : %f\n\n", maximum(5,5));
}
