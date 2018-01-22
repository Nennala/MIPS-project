/* -----------------------------------------
 * Nom : Porteries Daphné, Champey Vincent 
 * ----------------------------------------- */

#ifndef _REGISTRES_H
#define _REGISTRES_H

#include "utilitaire.h"

#define TAILLE_TABLEAU_REG 35
#define ZERO 0
#define AT 1
#define V0 2
#define V1 3
#define A0 4
#define A1 5
#define A2 6
#define A3 7
#define T0 8
#define T1 9
#define T2 10
#define T3 11
#define T4 12
#define T5 13
#define T6 14
#define T7 15
#define S0 16
#define S1 17
#define S2 18
#define S3 19
#define S4 20
#define S5 21
#define S6 22
#define S7 23
#define T8 24
#define T9 25
#define K0 26
#define K1 27
#define GP 28
#define SP 29
#define FP 30
#define RA 31
#define PC 32
#define HI 33
#define LO 34

extern int registre[TAILLE_TABLEAU_REG];

extern char *nomReg[TAILLE_TABLEAU_REG];

int numRegistre(char nom[]);

void afficherRegistre();

int lireRegistre(char nom[]);
	/*ouvre le registre demandé et retourne sa valeur*/

void ecrireRegistre(int valeur, char nom[]);
	/*remplace la valeur du registre demandé par la valeur*/
    
void initialisationReg();
    /*par convention on mettra tous les registres à 0 de base pour éviter
     * les effets de bord */

#endif
