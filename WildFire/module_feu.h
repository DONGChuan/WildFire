/****************************************************************************************
 Par  : Frédérick Henri
 Date : 10/09/2013

 Ce module offre une unique fonction qui détermine la probabilité qu'un feu se propage
 d'un point A à un point B en fonction de la distance entre les deux points.

 Il contient les fonctions suivantes :
	- probabilite_propagation_feu : Retourne la probabilité de propagation.
****************************************************************************************/




#if !defined(MODULE_FEU)
#define MODULE_FEU




/****************************************************************************************
							DÉFINITIONS DE CONSTANTES
****************************************************************************************/
/*	La distance maximale de propagation d'un feu. Passé cette distance, on considère
	qu'il est impossible que le feu puisse se propager.
*/
#define DISTANCE_MAX_PROPAGATION	5




/****************************************************************************************
							DÉCLARATIONS DE FONCTIONS
****************************************************************************************/
/*
	PROBABILITE_PROPAGATION_FEU

	Cette fonction retourne la probabilité qu'un feu se propage d'un point A à 
	un point B si ces deux points se trouvent à une distance "distance".

	PARAMÈTRES :
		- distance : La distance entre les deux points (type : int).

	VALEUR DE RETOUR : La probabilité que le feu se propage (type : double).
					   Cette valeur se trouvera toujours dans l'intervalle
					   [0, 1].
*/
double probabilite_propagation_feu(int distance);




#endif