#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 32

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

const char name[] = "test.txt";

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

char type_instruction(char instruction[]) {
    char type = 0;
    
    if (strcmp(instruction,"J") == 0 || strcmp(instruction,"JAL") == 0)
        type = 'J';
    if (instruction[0] == 'B' || instruction[0] == 'L' || strcmp(instruction,"ADDI") == 0 || strcmp(instruction,"SW") == 0)
        type = 'I';
    else
        type = 'R';
    return type;
}
    

int main(int argc, char *argv[]) {
    char *token;
    char operande[MAX_SIZE] = ""; 
    char instruction[MAX_SIZE] = "";
    char fonctions[MAX_SIZE] = "";
    char tmp_reg[MAX_SIZE] = "";
    int rt = 0;
    int rs = 0;
    int rd = 0;
    int sa = 0;
    int offset = 0;
    FILE* program = NULL;
    
    int typeI = 0;
    /* typeI 1 : BEQ, BNE, ADDI
     * typeI 2 : BLEZ, BGTZ
     * typeI 3 : LUI
     * typeI 4 : LW, SW
     * permet de différencier les syntaxes du type I */
    
    int typeR = 0;
    /* typeR = 1 : ADD, OR, XOR, SUB, SLT, AND
     * typeR = 2 : ROTR, SLL, SRL
     * typeR = 3 : MULT, DIV
     * typeR = 4 : MFHI, MFLO
     * typeR = 5 : JR
     * permet de différencier les syntaxes du type R */
    
    char type = 0;
    /* type I, R ou J */
    
    program = fopen(name, "r");
    
    if (program != NULL) {
        fgets(operande, MAX_SIZE, program);
        token = strchr(operande, ' ');
        *token = '\0';
        
        type = type_instruction(operande);
        if (type == 'I') {
        
            if (strcmp(operande, "ADDI") == 0) {
                strcat(instruction, ADDI);
                typeI = 1;
            }
            if (strcmp(operande, "BNE") == 0) {
                strcat(instruction, BNE);
                typeI = 1;
            }
            if (strcmp(instruction, "BEQ") == 0) {
                strcat(instruction, BEQ);
                typeI = 1;
            }
            if (strcmp(instruction, "BLEZ") == 0) {
                strcat(instruction, BLEZ);
                typeI = 2;
            }
            if (strcmp(instruction, "BGTZ") == 0) {
                strcat(instruction, BGTZ);
                typeI = 2;
            }
            if (strcmp(operande, "LUI") == 0) {
                strcat(instruction, LUI);
                typeI = 3;
            }
            if (strcmp(operande, "LW") == 0) {
                strcat(instruction, LW);
                typeI = 4;
            }
            if (strcmp(operande, "SW") == 0) {
                strcat(instruction, SW);
                typeI = 4;
            }
        
            printf("%s\n", instruction);
        
            if (typeI == 1) {
                strcpy(operande,token+1);
                token = strchr(operande, ',');
                *token = '\0';
        
                rt = atoi(operande+1);
        
                if (*(token+1) == ' ')
                    strcpy(operande, token+2);
                else
                    strcpy(operande, token+1);
        
                token = strchr(operande, ',');
                *token = '\0';
        
                rs = atoi(operande+1);
        
                if (*(token+1) == ' ')
                    strcpy(operande, token+2);
                else
                    strcpy(operande, token+1);
        
                offset = atoi(operande);
        
                printf("rt = %d, rs = %d, offset = %d\n", rt, rs, offset);
            }
        
            if (typeI == 2) {
                strcpy(operande,token+1);
                token = strchr(operande, ',');
                *token = '\0';
            
                rs = atoi(operande+1);
            
                if (*(token+1) == ' ')
                    strcpy(operande,token+2);
                else
                    strcpy(operande,token+1);
            
                offset = atoi(operande);
            
                rt = 0;
            
                printf("rs = %d, offset = %d\n", rs, offset);
            }
        
            if (typeI == 3) {
                strcpy(operande,token+1);
                token = strchr(operande, ',');
                *token = '\0';
            
                rt = atoi(operande+1);
            
                if (*(token+1) == ' ')
                    strcpy(operande,token+2);
                else
                    strcpy(operande,token+1);
            
                offset = atoi(operande);
            
                rs = 0;
            
                printf("rt = %d, offset = %d\n", rt, offset);
            }
        
            if (typeI == 4) {
                printf("Type %c\n", type);
                
                strcpy(operande,token+1);
                token = strchr(operande, ',');
                *token = '\0';
            
                rt = atoi(operande+1);
            
                if (*(token+1) == ' ')
                    strcpy(operande,token+2);
                else
                    strcpy(operande,token+1);
            
                token = strchr(operande, '(');
                *token = '\0';
            
                offset = atoi(operande);
            
                strcpy(operande,token+1);
                token = strchr(operande, ')');
                *token = '\0';
            
                rs = atoi(operande+1);
            
                printf("rt = %d, rs = %d, offset = %d\n", rt, rs, offset);
            }
        
            /* traduction en binaire */
            to_binary(rs, tmp_reg, 5);
            strcat(instruction, tmp_reg);
            to_binary(rt, tmp_reg, 5);
            strcat(instruction, tmp_reg);
            to_binary(offset, tmp_reg, 16);
            strcat(instruction, tmp_reg);
        
            printf("%x\n", to_int(instruction, 32));
        }
        if (type == 'J') {
            printf("Type %c\n", type);
            
            if (strcmp(operande,"J") == 0)
                strcat(instruction,J);
            if (strcmp(operande,"JAL") == 0)
                strcat(instruction,JAL);
            
            offset = atoi(token+1);
            
            /* traduction en binaire */
            to_binary(offset,tmp_reg,26);
            strcat(instruction,tmp_reg);
            
            printf("%x\n", to_int(instruction,32));
        }
        if (type == 'R') {
            printf("Type %c\n", type);
            
            if (strcmp(operande,"AND") == 0) {
                strcat(fonctions,AND);
                typeR = 1;
            }
            if (strcmp(operande,"OR") == 0) {
                strcat(fonctions,OR);
                typeR = 1;
            }
            if (strcmp(operande,"XOR") == 0) {
                strcat(fonctions,XOR);
                typeR = 1;
            }
            if (strcmp(operande,"ADD") == 0) {
                strcat(fonctions,ADD);
                typeR = 1;
            }
            if (strcmp(operande,"SUB") == 0) {
                strcat(fonctions,SUB);
                typeR = 1;
            }
            if (strcmp(operande,"SLT") == 0) {
                strcat(fonctions,SLT);
                typeR = 1;
            }
            if (strcmp(operande,"ROTR") == 0) {
                strcat(fonctions,ROTR);
                typeR = 2;
                rs = 1;
            }
            if (strcmp(operande,"SLL") == 0) {
                strcat(fonctions,SLL);
                typeR = 2;
                rs = 0;
            }
            if (strcmp(operande,"SRL") == 0) {
                strcat(fonctions,SRL);
                typeR = 2;
                rs = 0;
            }
            if (strcmp(operande,"MULT") == 0) {
                strcat(fonctions,MULT);
                typeR = 3;
            }
            if (strcmp(operande,"DIV") == 0) {
                strcat(fonctions,DIV);
                typeR = 3;
            }
            if (strcmp(operande,"MFHI") == 0) {
                strcat(fonctions,MFHI);
                typeR = 4;
            }
            if (strcmp(operande,"MFLO") == 0) {
                strcat(fonctions,MFLO);
                typeR = 4;
            }
            if (strcmp(operande,"JR") == 0) {
                strcat(fonctions,JR);
                typeR = 5;
            }
            
            strcat(instruction,"000000");
            if (typeR == 1) {
                sa = 0;
                
                strcpy(operande,token+1);
                token = strchr(operande, ',');
                *token = '\0';
            
                rd = atoi(operande+1);
            
                if (*(token+1) == ' ')
                    strcpy(operande,token+2);
                else
                    strcpy(operande,token+1);
                
                token = strchr(operande, ',');
                *token = '\0';
                
                rs = atoi(operande+1);
                
                if (*(token+1) == ' ')
                    strcpy(operande,token+2);
                else
                    strcpy(operande,token+1);
                
                rt = atoi(operande+1);
            }
            if (typeR == 2) {
                strcpy(operande,token+1);
                token = strchr(operande, ',');
                *token = '\0';
                
                rd = atoi(operande+1);
                
                if (*(token+1) == ' ')
                    strcpy(operande,token+2);
                else
                    strcpy(operande,token+1);
                
                token = strchr(operande,',');
                *token = '\0';
                    
                rt = atoi(operande+1);
                
                if (*(token+1) == ' ')
                    strcpy(operande,token+2);
                else
                    strcpy(operande,token+1);
                
                sa = atoi(operande);
            }
            if (typeR == 3) {
                rd = 0;
                sa = 0;
                
                strcpy(operande,token+1);
                token = strchr(operande, ',');
                *token = '\0';
                
                rs = atoi(operande+1);
                
                if (*(token+1) == ' ')
                    strcpy(operande,token+2);
                else
                    strcpy(operande,token+1);
                
                rt = atoi(operande+1);
            }
            if (typeR == 4) {
                rs = 0;
                rt = 0;
                sa = 0;
                
                strcpy(operande,token+1);
                rd = atoi(operande+1);
            }
            if (typeR == 5) {
                rt = 0;
                rd = 0;
                sa = 0;
                
                strcpy(operande,token+1);
                rs = atoi(operande+1);
            }
            
            printf("rs = %d, rt = %d, rd = %d, sa = %d, fonction = %s\n", rs, rt, rd, sa, fonctions);
            
            /* traduction en binaire puis hexa */
            to_binary(rs,tmp_reg,5);
            strcat(instruction,tmp_reg);
            to_binary(rt,tmp_reg,5);
            strcat(instruction,tmp_reg);
            to_binary(rd,tmp_reg,5);
            strcat(instruction,tmp_reg);
            to_binary(sa,tmp_reg,5);
            strcat(instruction,tmp_reg);
            strcat(instruction,fonctions);
            
            printf("%x\n", to_int(instruction,32));
        }
        fclose(program);
    }
}
