#include "../header/convert_hexa.h"

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

void typeI_to_hexa(char operande[], char *token, char instruction[]) {
    int typeI = 0;
    /* typeI 1 : BEQ, BNE, ADDI
     * typeI 2 : BLEZ, BGTZ
     * typeI 3 : LUI
     * typeI 4 : LW, SW
     * permet de différencier les syntaxes du type I */
    
    char tmp_reg[MAX_SIZE] = "";
    
    int rt = 0;
    int rs = 0;
    int offset = 0;
    
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
        
        if (is_hexa(operande))
            offset = atoi(operande+2);
        else
            offset = atoi(operande);
            
        rt = 0;
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
        
        if (is_hexa(operande))
            offset = atoi(operande+2);
        else
            offset = atoi(operande+1);
            
        rs = 0;
    }
        
    if (typeI == 4) {                
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
        
        if (is_hexa(operande))
            offset = atoi(operande+2);
        else
            offset = atoi(operande);
    
        strcpy(operande,token+1);
        token = strchr(operande, ')');
        *token = '\0';
            
        rs = atoi(operande+1);
    }
        
    /* traduction en binaire */
    to_binary(rs, tmp_reg, 5);
    strcat(instruction, tmp_reg);
    to_binary(rt, tmp_reg, 5);
    strcat(instruction, tmp_reg);
    to_binary(offset, tmp_reg, 16);
    strcat(instruction, tmp_reg);
}

void typeJ_to_hexa(char operande[], char *token, char instruction[]) {
    int offset = 0;
    char tmp_reg[MAX_SIZE] = "";
    
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

void typeR_to_hexa(char operande[], char *token, char instruction[]) {
    int rs = 0;
    int rt = 0;
    int rd = 0;
    int sa = 0;
    
    int typeR = 0;
    /* typeR = 1 : ADD, OR, XOR, SUB, SLT, AND
     * typeR = 2 : ROTR, SLL, SRL
     * typeR = 3 : MULT, DIV
     * typeR = 4 : MFHI, MFLO
     * typeR = 5 : JR
     * permet de différencier les syntaxes du type R */
    
    char tmp_reg[MAX_SIZE] = "";
    char fonctions[MAX_SIZE] = "";
    
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
    if (strcmp(operande,"NOP") == 0) {
        strcat(fonctions,NOP);
        rs = 0;
        rt = 0;
        rd = 0;
        sa = 0;
    }
    if (strcmp(operande,"SYSCALL") == 0) {
        strcat(fonctions,SYSCALL);
        /* pour l'instant mis à zéro car pas de connaissance
         * des codes du syscall */
        rs = 0;
        rt = 0;
        rd = 0;
        sa = 0;
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
}
