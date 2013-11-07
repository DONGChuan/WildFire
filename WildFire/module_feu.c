/*****************************************************************************************************/
/* Par       : Dominic Blanchard										                        	 */
/*																									 */
/* Revise le : 01/11/2013													                         */
/* Fichier   : feu.c												                            	 */
/*																		                             */
/* Description:  Ce module se compose de deux fonctions. Une fonction qui retourne la propabilité    */
/*               qu'un feu se propage entre deux points (arbres) et une autre fonction qui sert      */
/*               à tester cette fonction.															 */
/*											   - probabilite_propagation_feu						 */
/*											   - tester_probabilite_propagation_feu					 */
/*                                                                                                   */
/*****************************************************************************************************/


/*****************************************************************************************************/
/*							INCLUSION DE LIBRAIRIES							                         */
/*****************************************************************************************************/
#include<stdio.h>
#include"module_feu.h"


/*****************************************************************************************************/
/*								DEFINITIONS DE CONSTANTES                                            */
/*****************************************************************************************************/

/* Constantes de probabilitées que le feu se propage entre deux arbres 
   selon la distance qui les sépares.                                                                */
#define PROBALITE_DISTANCE_1       0.900
#define PROBALITE_DISTANCE_2       0.150
#define PROBALITE_DISTANCE_3       0.030
#define PROBALITE_DISTANCE_4       0.010
#define PROBALITE_DISTANCE_5       0.005
#define PROBALITE_AUTRES_DISTANCE  0.000


/*****************************************************************************************************/
/*						   DECLARATION DE FONCTIONS				                               	     */
/*****************************************************************************************************/
/*
	PROBABILITE_PROPAGATION_FEU

	Cette fonction retourne la probabilité qu'un feu se propage d'un point A à 
	un point B si ces deux points se trouvent à une certaine distance.
*/
double probabilite_propagation_feu(int distance)
{
	/*
		Retourne une constante de probabilité selon la distance reçue entre [1 et 5] inclusivement sinon,
		il retoune 0.000 comme propabilité. 
	*/
	if (distance == 1)
		return PROBALITE_DISTANCE_1;
	else if (distance == 2)
		return PROBALITE_DISTANCE_2;
	else if (distance == 3)
		return PROBALITE_DISTANCE_3;
	else if (distance == 4)
		return PROBALITE_DISTANCE_4;
	else if (distance == 5)
		return PROBALITE_DISTANCE_5;
	else return PROBALITE_AUTRES_DISTANCE;
	}


/*
	TESTER_PROBABILITE_PROPAGATION_FEU

	Cette fonction affiche le test de la fonction probabilite_propagation_feu qui est de determiner 
	la propabilité qu'un feu se propage entre deux arbres selon la distance qui les sépares.

	PARAMÈTRES : Aucun.
	
	VALEUR DE RETOUR :   Aucun.
*/
void tester_probabilite_propagation_feu(void)
{
	printf(" TEST : PROBABILITE_PROPAGATION_FEU\n\n\n");
	
	/* Affiche le résultat du test 1.    [probabilite_propagation_feu(-3)]							*/
	printf("      Test #1\n\n");
	printf("  Distance :  -3       Valeur attendue :   0.000\n");	
	printf("                       Valeur obtenue  :   %.3lf\n",probabilite_propagation_feu(-3));

	/* Affiche le résultat du test 2.    [probabilite_propagation_feu(1)]							*/
	printf("      Test #2\n\n");
	printf("  Distance :   1       Valeur attendue :   0.900\n");	
	printf("                       Valeur obtenue  :   %.3lf\n",probabilite_propagation_feu(1));

	/* Affiche le résultat du test 3.    [probabilite_propagation_feu(2)]							*/
	printf("      Test #3\n\n");
	printf("  Distance :   2       Valeur attendue :   0.150\n");	
	printf("                       Valeur obtenue  :   %.3lf\n",probabilite_propagation_feu(2));

	/* Affiche le résultat du test 4.    [probabilite_propagation_feu(3)]							*/
	printf("      Test #4\n\n");
	printf("  Distance :   3       Valeur attendue :   0.030\n");	
	printf("                       Valeur obtenue  :   %.3lf\n",probabilite_propagation_feu(3));

	/* Affiche le résultat du test 5.    [probabilite_propagation_feu(4)]							*/
	printf("      Test #5\n\n");
	printf("  Distance :   4       Valeur attendue :   0.010\n");	
	printf("                       Valeur obtenue  :   %.3lf\n",probabilite_propagation_feu(4));

	/* Affiche le résultat du test 6.    [probabilite_propagation_feu(5)]							*/
	printf("      Test #6\n\n");
	printf("  Distance :   5       Valeur attendue :   0.005\n");	
	printf("                       Valeur obtenue  :   %.3lf\n",probabilite_propagation_feu(5));

	/* Affiche le résultat du test 7.    [probabilite_propagation_feu(7)]							*/
	printf("      Test #7\n\n");
	printf("  Distance :   7       Valeur attendue :   0.000\n");	
	printf("                       Valeur obtenue  :   %.3lf\n",probabilite_propagation_feu(7));

	printf("\n\n");
}