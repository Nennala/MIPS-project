/* -----------------------------------------
 * Nom : Porteries Daphné, Champey Vincent 
 * ----------------------------------------- */

#ifndef _MEMOIRE_H
#define _MEMOIRE_H

#include "utilitaire.h"

char** memoire;

char* lireMemoire(int PC, int NbBits);

void ecrireMemoire (int PC, char chaine[]);

/* Nous ne savons pas encore si nous allons différencier en plusieurs fonctions pour la lecture de mémoire d'instructions et celle de données,
 * on est donc potentiellement amené à en rajouter pendant l'écriture du programme. */

#endif
