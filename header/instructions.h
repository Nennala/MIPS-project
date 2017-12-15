/* -----------------------------------------
 * Nom : Porteries Daphné, Champey Vincent 
 * ----------------------------------------- */

#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#include "memoire.h"
#include "registres.h"
#include "utilitaire.h"

#define TAILLE_TABLEAU_OPERANDE 5

int nomInstruction(char mot[]);
	/*retourne un int qui correspond à une certaine instruction*/

int* operande(char mot[]);
	/*retourne un tableau de 5 cases : ['R', rs, rd, rt, sa] OU ['I', rs, rt, immediate, 0] OU ['J', target, 0, 0, 0]*/

void execute(char tableau[], int taille);
	/*utilise les fonctions des fichiers memoireInstr.h, memoireData.h, et registres.h pour executer l'instruction*/

#endif
