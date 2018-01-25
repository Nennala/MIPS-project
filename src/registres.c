/* -----------------------------------------
 * Nom : Porteries Daphné, Champey Vincent 
 * ----------------------------------------- */

#include "../header/registres.h"

int registre[TAILLE_TABLEAU_REG];

char *nomReg[TAILLE_TABLEAU_REG] = {"ZERO","AT","V0","V1","A0","A1","A2","A3","T0","T1","T2","T3","T4","T5","T6","T7","S0","S1","S2","S3","S4","S5","S6","S7","T8","T9","K0","K1","GP","SP","FP","RA","PC","HI","LO"};

void afficherRegistre() {
    int i;
    printf("****** REGISTRES ******\n");
    for (i = 0;i<TAILLE_TABLEAU_REG;i++) {
        printf("$%s = %d\n",nomReg[i],registre[i]);
    }
}

int lireRegistre(int nom) {
    return registre[nom];
}

void ecrireRegistre(int valeur, int nom) {
    if (nom == ZERO) {
        printf("Vous tentez d'écrire sur un registre qui ne varie pas.\n");
    }
    else if (nom == K0 || nom == K1) {
        printf("Vous tentez d'écrire sur des registres réservés au kernel ! C'est interdit !\n");
    }
    else {
        registre[nom] = valeur;
    }
}

void initialisationReg() {
    int i;
    for (i = 0;i < TAILLE_TABLEAU_REG;i++)
        registre[i] = 0;
}
