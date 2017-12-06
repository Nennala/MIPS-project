#include "../header/utils.h"

void to_binary(const int src, char out_binary[], int len) {
    int nb = src;
    strcpy(out_binary, "");
    
    while (len > 0) {
        if (nb - pow(2,len-1) >= 0) {
            strcat(out_binary,"1");
            nb = nb - pow(2,len-1);
        }
        else
            strcat(out_binary, "0");
        len--;
    }
}

int to_int(const char in_binary[], int len) {
    int out = 0;
    int i;
    
    for (i = len-1; i >= 0; i--) {
        out += (in_binary[len-i-1]-48)*pow(2,i);
    }
    return out;
}

int is_hexa(char operande[]) {
    int hexa = 0;
    
    if (operande[0] == '0' && operande[1] == 'x')
        hexa = 1;
    
    return hexa;
}
