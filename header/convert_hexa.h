#ifndef CONVERT_HEXA_H
#define CONVERT_HEXA_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/* Type I */
#define ADDI "001000"
#define LW "100011"
#define SW "101011"
#define LUI "001111"
#define BEQ "000100"
#define BNE "000101"
#define BGTZ "000111"
#define BLEZ "000110"

/* Type J */
#define J "000010"
#define JAL "000011"

/* Type R */
#define AND "100100"
#define OR "100101"
#define XOR "100110"
#define ADD "100000"
#define SUB "100010"
#define SLT "101010"
#define ROTR "000010"
#define SRL "000010"
#define SLL "000000"
#define MULT "011000"
#define DIV "011010"
#define MFHI "010000"
#define MFLO "010010"
#define JR "001000"
#define NOP "000000"
#define SYSCALL "001100"

/* Taille de tableaux */
#define MAX_SIZE 32

char type_instruction(char instruction[]);

void typeI_to_hexa(char operande[], char *token, char instruction[]);

void typeJ_to_hexa(char operande[], char *token, char instruction[]);

void typeR_to_hexa(char operande[], char *token, char instruction[]);

#endif
