/* -----------------------------------------
 * Nom : Porteries Daphné, Champey Vincent 
 * ----------------------------------------- */

#include "../header/utilitaire.h"
#include "../header/hexa.h"
#include "../header/memoire.h"
#include "../header/registres.h"
#include "../header/instructions.h"

#define MAX_SIZE_FILE 100
#define MEMORY_SIZE 1000000000

const char name[] = "test.txt";
int mode = 0; /* 1 = pas à pas, 0 = fichier */

int main(int argc, char *argv[]) {
    int i;
    int adresse = 0;
    char *token = NULL;
    char operande[MAX_SIZE] = ""; 
    char instruction[MAX_SIZE] = "";
    char adresse_bin[MAX_SIZE+1] = "";
    
    char type = 0;
    /* Type I, J ou R */
    
    FILE* program = NULL;
    
    initialisationReg();
    
    if (mode == 0) { /* mode fichier */
        program = fopen(name, "r");
    
        if (program != NULL) {
            to_binary(adresse,adresse_bin,32);
            adresse_bin[32] = '\0';
            while (fgets(operande, MAX_SIZE_FILE, program) != NULL) {
                i = 0;
                while (operande[i] == ' ' && i < 32) {
                    strcpy(operande,operande+1);
                    i++;
                }
                if (i != 32 && operande[0] != '\n') {
                    token = strchr(operande, ' ');
                    if (token != NULL)
                        *token = '\0';
                    else {
                        token = strchr(operande, '\n');
                        *token = '\0';
                    }
            
                    if (operande[0] != '#') {
                        type = type_instruction(operande);
            
                        strcpy(instruction, "");
                        if (type == 'I')
                            typeI_to_hexa(operande, token, instruction);
                        if (type == 'J')
                            typeJ_to_hexa(operande, token, instruction);
                        if (type == 'R')
                            typeR_to_hexa(operande, token, instruction);
                        
                        ecrireMemoire(adresse_bin,instruction,&memoireInst);
                        printf("%08x\n", to_int(instruction, 32));
                        adresse += 4;
                        to_binary(adresse,adresse_bin,32);
                        adresse_bin[32] = '\0';
                    }
                }
            }
            fclose(program);
            
            /* début de l'exécution du programme */
            adresse = 0;
            to_binary(adresse,adresse_bin,32);
            while (lireMemoire(adresse_bin,instruction,memoireInst) != 0) {
                execution(instruction);
                adresse += 4;
                to_binary(adresse,adresse_bin,32);
                
                /* affichage des registres pour suivre l'état */
                afficherRegistre();
            }
        }
        else {
            perror("fopen");
        }
    }
    else {
        /* Mode pas à pas */
    }
    return 0;
}
