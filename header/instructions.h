/* -----------------------------------------
 * Nom : Porteries Daphné, Champey Vincent
 * ----------------------------------------- */

#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#include "memoire.h"
#include "registres.h"
#include "utilitaire.h"

/* Équivalence numéro/instructions */
#define ADD_I 1
#define AND_I 2
#define DIV_I 3
#define JR_I 4
#define MFHI_I 5
#define MFLO_I 6
#define MULT_I 7
#define NOP_I 8
#define OR_I 9
#define SRL_I 10
#define SLL_I 11
#define SLT_I 12
#define ROTR_I 13
#define SUB_I 14
#define SYSCALL_I 15
#define XOR_I 16
#define ADDI_I 17
#define BEQ_I 18
#define BGTZ_I 19
#define BLEZ_I 20
#define BNE_I 21
#define LUI_I 22
#define LW_I 23
#define SW_I 24
#define J_I 25
#define JAL_I 26

int nomInstruction(char mot[]);
	/*retourne un int qui correspond a une certaine instruction*/

void execution(char mot[]);
  /*détermine les valeurs des opérandes suivant le type d'instruction et exécute cette instruction*/


#endif
