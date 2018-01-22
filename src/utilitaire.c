/* -----------------------------------------
 * Nom : Porteries Daphné, Champey Vincent 
 * ----------------------------------------- */

#include "../header/utilitaire.h"

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

int hexa_to_int(const char in_hex[], int len) {
    int i;
    int tmp_int = 0;
    int result = 0;
    
    for (i = 0; i < len; i++) {
        if (isalpha(in_hex[i])) {
            switch (toupper(in_hex[i])) {
                case 'A' :
                    tmp_int = 10;
                    break;
                case 'B' :
                    tmp_int = 11;
                    break;
                case 'C' :
                    tmp_int = 12;
                    break;
                case 'D' :
                    tmp_int = 13;
                    break;
                case 'E' :
                    tmp_int = 14;
                    break;
                case 'F' :
                    tmp_int = 15;
                    break;
            }
        }
        else {
            tmp_int = in_hex[i] - '0';
        }
        result += tmp_int*pow(16,len-i-1);
    }
    return result;
}

void hexa_to_bin(const char in_hex[], int len, char out_bin[]) {
    int i;
    char *tmp_bin = "";
    
    strcat(out_bin,"");
    
    for (i = 0;i < len;i++) {
        switch (toupper(in_hex[i])) {
            case 'A':
                strcpy(tmp_bin,"1010");
                break;
            case 'B':
                strcpy(tmp_bin,"1011");
                break;
            case 'C':
                strcpy(tmp_bin,"1100");
                break;
            case 'D':
                strcpy(tmp_bin,"1101");
                break;
            case 'E':
                strcpy(tmp_bin,"1110");
                break;
            case 'F':
                strcpy(tmp_bin,"1111");
                break;
        }
        strcat(out_bin,tmp_bin);
    }
}

int hexa_to_bin_to_int(const char in_hex[], int len) {
    char *out_bin = "";
    int neg = 1;
    int out_int = 0;
    
    hexa_to_bin(in_hex, len, out_bin);
    if (out_bin[0] == '1') {
        complement2(out_bin,len*4);
        neg = -1;
    }
    out_int = to_int(out_bin,len*4);
    
    return neg*out_int;
}

void add_one(char binary[], int len) {
    int num, carry, i;
    char *tmp_binary = malloc(len*sizeof(char));
    
    carry = 1;
    
    for (i = len-1; i >= 0; i--) {
        num = binary[i] - 48;
        num = (num+carry)%2;
        if (num == 1 && carry == 1)
            carry = 0;
        if (num == 0 && carry == 1)
            carry = 1;
        tmp_binary[i] = num + 48;
    }
    strcpy(binary,tmp_binary);
    free(tmp_binary);
}
    
void complement2(char binary[], int len) {
    char *tmp_binary = malloc(len*sizeof(char));
    for (int i = 0; i < len; i++) {
        if (binary[i] == '0')
            tmp_binary[i] = '1';
        else
            tmp_binary[i] = '0';
    }
    add_one(tmp_binary,len);
    
    strcpy(binary, tmp_binary);
    free(tmp_binary);
}

