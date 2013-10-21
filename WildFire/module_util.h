/****************************************************************************************
 Par  : Fr�d�rick Henri
 Date : 10/09/2013

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




#if !defined(MODULE_UTIL)
#define MODULE_UTIL




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
long int plafond(double x);



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
int nb_aleatoire(int min, int max);



/*
	NB_ALEATOIRE_0_1

	Cette fonction retourne un nombre al�atoire r�el dans l'intervalle [0, 1].
	Chaque valeur de l'intervalle poss�de la m�me probabilit� d'�tre choisie.

	PARAM�TRES : Aucun.
	
	VALEUR DE RETOUR : Un nombre dans l'intervalle [0, 1] (type : double).
*/
double nb_aleatoire_0_1(void);



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
int est_dans_intervalle(int x, int x1, int x2);



/*
	VALEUR_ABSOLUE

	Cette fonction retourne la valeur absolue d'un nombre r�el.

	PARAM�TRES :
		- x : Le nombre dont on cherche la valeur absolue (type : double).

	VALEUR DE RETOUR : La valeur absolue de x (type : double).
*/
double valeur_absolue(double x);



/*
	MAXIMUM

	Cette fonction retourne la plus grande des deux valeurs re�ues.

	PARAM�TRES :
		- nb1 : Le premier des deux nombres � comparer (type : double).
		- nb2 : Le second des deux nombres � comparer (type : double).

	VALEUR DE RETOUR : Le maximum entre nb1 et nb2 (type : double).
*/
double maximum(double nb1, double nb2);



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
				  const char * message_erreur);



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
				   const char * message_erreur);




#endif