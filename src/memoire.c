/* -----------------------------------------
 * Nom : Porteries Daphné, Champey Vincent 
 * ----------------------------------------- */

#include "../header/memoire.h"

case_memoire *memoireInst = NULL;
case_memoire *memoireData = NULL;

int lireMemoire(char etiquette[], char valeur[], case_memoire *memoire) {
    case_memoire *element = memoire;
    int fait;
    
    if (element->suivant == NULL)
        fait = 0;
    else {
        while (element->suivant != NULL && strcmp(element->etiquette,etiquette) != 0)
            element = element->suivant;
    
        strcpy(valeur, element->valeur);
        
        fait = 1;
    }
    return fait;
}

int ecrireMemoire (char etiquette[], char valeur[], case_memoire *memoire) {
    case_memoire *select, *suiv, *libre;
    int fait = 0;
    
    if (elementExiste(etiquette, memoire) == 0 && tailleMemoire() <= 1000000000) {
        select = NULL;
        suiv = memoire;
    
        while (suiv != NULL) {
            select = suiv;
            suiv = suiv->suivant;
        }
    
        libre = (case_memoire *)malloc(sizeof(case_memoire));
        if (select != NULL) {
            strcpy(valeur,libre->valeur);
            strcpy(etiquette,libre->etiquette);
            libre->suivant = suiv;
            select->suivant = libre;
        }
        else {
            memoire = libre;
            libre->suivant = suiv;
            strcpy(valeur,libre->valeur);
            strcpy(etiquette,libre->etiquette);
        }
        fait = 1;
    }
    
    if (elementExiste(etiquette, memoire) == 1) {
        strcpy(valeur,select->valeur);
        fait = 1;
    }
    return fait;
}

int elementExiste(char etiquette[], case_memoire *memoire) {
    int result;
    case_memoire *select = memoire;
    
    while (select != NULL && strcmp(etiquette,select->etiquette) != 0) {
        select = select->suivant;
    }
    if (select == NULL)
        result = 0;
    else
        result = 1;
    
    return result;
}

int tailleMemoire() {
    int taille = 0;
    case_memoire *select = memoireInst;
    
    while (select->suivant != NULL) {
        select = select->suivant;
        taille++;
    }
    
    select = memoireData;
    while (select->suivant != NULL) {
        select = select->suivant;
        taille++;
    }
    return taille;
}
