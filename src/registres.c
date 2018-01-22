/* -----------------------------------------
 * Nom : Porteries Daphné, Champey Vincent 
 * ----------------------------------------- */

#include "../header/registres.h"

int registre[TAILLE_TABLEAU_REG];

char *nomReg[TAILLE_TABLEAU_REG] = {"ZERO","AT","V0","V1","A0","A1","A2","A3","T0","T1","T2","T3","T4","T5","T6","T7","S0","S1","S2","S3","S4","S5","S6","S7","T8","T9","K0","K1","GP","SP","FP","RA","PC","HI","LO"};

int numRegistre(char nom[]) {
    int result = -1;
    int i = 0;
    if (nom[0] == '$' && nom[1] != ' ') {
        nom = nom+1;
        if (atoi(nom) != 0 && nom[0] != '0') {
            while (nom[i] != '\0') {
                nom[i] = toupper(nom[i]);
                i++;
            }
            if (strcmp("ZERO",nom) == 0)
                result = ZERO;
            if (strcmp("AT",nom) == 0)
                result = AT;
            if (strcmp("V0",nom) == 0)
                result = V0;
            if (strcmp("V1",nom) == 0)
                result = V1;
            if (strcmp("A0",nom) == 0)
                result = A0;
            if (strcmp("A1",nom) == 0)
                result = A1;
            if (strcmp("A2",nom) == 0)
                result = A2;
            if (strcmp("A3",nom) == 0)
                result = A3;
            if (strcmp("T0",nom) == 0)
                result = T0;
            if (strcmp("T1",nom) == 0)
                result = T1;
            if (strcmp("T2",nom) == 0)
                result = T2;
            if (strcmp("T3",nom) == 0)
                result = T3;
            if (strcmp("T4",nom) == 0)
                result = T4;
            if (strcmp("T5",nom) == 0)
                result = T5;
            if (strcmp("T6",nom) == 0)
                result = T6;
            if (strcmp("T7",nom) == 0)
                result = T7;
            if (strcmp("S0",nom) == 0)
                result = S0;
            if (strcmp("S1",nom) == 0)
                result = S1;
            if (strcmp("S2",nom) == 0)
                result = S2;
            if (strcmp("S3",nom) == 0)
                result = S3;
            if (strcmp("S4",nom) == 0)
                result = S4;
            if (strcmp("S5",nom) == 0)
                result = S5;
            if (strcmp("S6",nom) == 0)
                result = S6;
            if (strcmp("S7",nom) == 0)
                result = S7;
            if (strcmp("T8",nom) == 0)
                result = T8;
            if (strcmp("T9",nom) == 0)
                result = T9;
            if (strcmp("K0",nom) == 0)
                result = K0;
            if (strcmp("K1",nom) == 0)
                result = K1;
            if (strcmp("GP",nom) == 0)
                result = GP;
            if (strcmp("SP",nom) == 0)
                result = SP;
            if (strcmp("FP",nom) == 0)
                result = FP;
            if (strcmp("RA",nom) == 0)
                result = RA;
            if (strcmp("PC",nom) == 0)
                result = PC;
            if (strcmp("HI",nom) == 0)
                result = HI;
            if (strcmp("LO",nom) == 0)
                result = LO;
        }
        else
            result = atoi(nom);
    }
    return result;
}

void afficherRegistre() {
    int i;
    printf("****** REGISTRES ******\n");
    for (i = 0;i<TAILLE_TABLEAU_REG;i++) {
        printf("$%s = %d\n",nomReg[i],registre[i]);
    }
}

int lireRegistre(char nom[]) {
    int num = 0;
    num = numRegistre(nom);
    return registre[num];
}

void ecrireRegistre(int valeur, char nom[]) {
    int num = 0;
    if (strcmp(nom,"ZERO")) {
        printf("Vous tentez d'écrire sur un registre qui ne varie pas.\n");
    }
    else if (strcmp(nom,"K0") || strcmp(nom,"K1")) {
        printf("Vous tentez d'écrire sur des registres réservés au kernel ! C'est interdit !\n");
    }
    else {
        num = numRegistre(nom);
        registre[num] = valeur;
    }
}

void initialisationReg() {
    int i;
    for (i = 0;i < TAILLE_TABLEAU_REG;i++)
        registre[i] = 0;
}
