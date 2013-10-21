/****************************************************************************************
 Par  : Fr�d�rick Henri
 Date : 10/09/2013

 Ce module offre une unique fonction qui d�termine la probabilit� qu'un feu se propage
 d'un point A � un point B en fonction de la distance entre les deux points.

 Il contient les fonctions suivantes :
	- probabilite_propagation_feu : Retourne la probabilit� de propagation.
****************************************************************************************/




#if !defined(MODULE_FEU)
#define MODULE_FEU




/****************************************************************************************
							D�FINITIONS DE CONSTANTES
****************************************************************************************/
/*	La distance maximale de propagation d'un feu. Pass� cette distance, on consid�re
	qu'il est impossible que le feu puisse se propager.
*/
#define DISTANCE_MAX_PROPAGATION	5




/****************************************************************************************
							D�CLARATIONS DE FONCTIONS
****************************************************************************************/
/*
	PROBABILITE_PROPAGATION_FEU

	Cette fonction retourne la probabilit� qu'un feu se propage d'un point A � 
	un point B si ces deux points se trouvent � une distance "distance".

	PARAM�TRES :
		- distance : La distance entre les deux points (type : int).

	VALEUR DE RETOUR : La probabilit� que le feu se propage (type : double).
					   Cette valeur se trouvera toujours dans l'intervalle
					   [0, 1].
*/
double probabilite_propagation_feu(int distance);




#endif