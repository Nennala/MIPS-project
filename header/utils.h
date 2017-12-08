#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <string.h>
#include <ctype.h>

void to_binary(const int src, char out_binary[], int len);

int to_int(const char in_binary[], int len);

int is_hexa(char operande[]);

int hexa_to_int(const char in_hex[], int len);

#endif
