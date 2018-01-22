/* -----------------------------------------
 * Nom : Porteries Daphné, Champey Vincent 
 * ----------------------------------------- */

#ifndef _MEMOIRE_H
#define _MEMOIRE_H

#define MAX_SIZE 32

#include "utilitaire.h"

typedef struct case_memoire case_memoire;
struct case_memoire {
    char valeur[MAX_SIZE];
    char etiquette[MAX_SIZE];
    case_memoire *suivant;
};

extern case_memoire* memoireInst;
extern case_memoire* memoireData;

int lireMemoire(char etiquette[], char valeur[], case_memoire *memoire);

int ecrireMemoire (char etiquette[], char valeur[], case_memoire *memoire);

int elementExiste(char etiquette[], case_memoire *memoire);

int tailleMemoire();

#endif
