/* -----------------------------------------
 * Nom : Porteries Daphné, Champey Vincent 
 * ----------------------------------------- */

#ifndef _UTILITAIRE_H
#define _UTILITAIRE_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void to_binary(const int src, char out_binary[], int len);

int to_int(const char in_binary[], int len);

int is_hexa(char operande[]);

int hexa_to_int(const char in_hex[], int len);

void hexa_to_bin(const char in_hex[], int len, char out_bin[]);

int hexa_to_bin_to_int(const char in_hex[], int len);

void add_one(char binary[], int len);

void complement2(char binary[], int len);

#endif
