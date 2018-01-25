/* -----------------------------------------
 * Nom : Porteries Daphné, Champey Vincent
 * ----------------------------------------- */

#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#include "memoire.h"
#include "registres.h"
#include "utilitaire.h"

/* Équivalence numéro/instructions */
#define ADD 1
#define AND 2
#define DIV 3
#define JR 4
#define MFHI 5
#define MFLO 6
#define MULT 7
#define NOP 8
#define OR 9
#define SRL 10
#define SLL 11
#define SLT 12
#define ROTR 13
#define SUB 14
#define SYSCALL 15
#define XOR 16
#define ADDI 17
#define BEQ 18
#define BGTZ 19
#define BLEZ 20
#define BNE 21
#define LUI 22
#define LW 23
#define SW 24
#define J 25
#define JAL 26

int nomInstruction(char mot[]);
	/*retourne un int qui correspond a une certaine instruction*/

void operande(char mot[]);
  /*détermine les valeurs des opérandes suivant le type d'instruction et exécute cette instruction*/


#endif
