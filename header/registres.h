/* -----------------------------------------
 * Nom : Porteries Daphn�, Champey Vincent 
 * ----------------------------------------- */

#ifndef _REGISTRES_H
#define _REGISTRES_H

#include "utilitaire.h"

#define TAILLE_TABLEAU_REGISTRES 33

int registres[TAILLE_TABLEAU_REGISTRES];

int lireRegistre(int registre, int tableRegistre[], int taille);
	/*ouvre le registre demand� et retourne sa valeur*/

void ecrireRegistre(int valeur, int registre, int tableRegistre[], int taille);
	/*remplace la valeur du registre demand� par la valeur*/

#endif
