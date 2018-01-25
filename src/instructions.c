/* -----------------------------------------
 * Nom : Porteries Daphné, Champey Vincent
 * ----------------------------------------- */

#include "../header/instructions.h"

int nomInstruction(char mot[]) {
    char *copieMot = NULL;
    char *arguments = NULL;

    copieMot= malloc(32*sizeof(char));
    if (copieMot == NULL)
        exit(0);

    int numeroInstruction=0;
    char *finMot;

    strcpy(copieMot, mot);
    mot[6]='\0';
    
    strcpy(arguments,copieMot);
    arguments = arguments+11;
    *(arguments+15) = '\0';   

    finMot = copieMot+26;

    if (strcmp(mot, "000010")==0)
        numeroInstruction=J;
    if (strcmp(mot, "000011")==0)
        numeroInstruction=JAL;
    if (strcmp(mot, "001000")==0)
        numeroInstruction=ADDI;
    if (strcmp(mot, "000100")==0) 
        numeroInstruction=BEQ;
    if (strcmp(mot, "000111")==0) 
        numeroInstruction=BGTZ;
    if (strcmp(mot, "000110")==0) 
        numeroInstruction=BLEZ;
    if (strcmp(mot, "000101")==0) 
        numeroInstruction=BNE;
    if (strcmp(mot, "001111")==0) 
        numeroInstruction=LUI;
    if (strcmp(mot, "100011")==0) 
        numeroInstruction=LW;
    if (strcmp(mot, "101010")==0)
        numeroInstruction=SW;
    if (strcmp(mot, "000000")==0) {
        if (strcmp(finMot, "100000")==0)
            numeroInstruction=ADD;
        if (strcmp(finMot, "100100")==0)
            numeroInstruction=AND;
        if (strcmp(finMot, "011010")==0)
            numeroInstruction=DIV;
        if (strcmp(finMot, "001000")==0)
            numeroInstruction=JR;
        if (strcmp(finMot, "010000")==0)
            numeroInstruction=MFHI;
        if (strcmp(finMot, "010010")==0)
            numeroInstruction=MFLO;
        if (strcmp(finMot, "011000")==0)
            numeroInstruction=MULT;
        if (strcmp(finMot, "100101")==0)
            numeroInstruction=OR;
        if (strcmp(finMot, "000000")==0) {
            if (strcmp(arguments,"000000000000000") == 0)
                numeroInstruction=NOP;
            else 
                numeroInstruction=SLL;
        }
        if (strcmp(finMot, "101010")==0)
            numeroInstruction=SLT;
        if (strcmp(finMot, "100010")==0)
            numeroInstruction=SUB;
        if (strcmp(finMot, "001100")==0)
            numeroInstruction=SYSCALL;
        if (strcmp(finMot, "100110")==0)
            numeroInstruction=XOR;
        if (strcmp(finMot, "000010")==0) {
            if (copieMot[10]=='1')
                numeroInstruction=SRL;
            if (copieMot[10]=='0')
                numeroInstruction=ROTR;
            else 
                printf("erreur dans le code binaire\n");
        }
        else
            printf("erreur dans le code binaire\n");
    }
    else
        printf("erreur dans le code binaire\n");

    free(copieMot);
    free(arguments);

    return(numeroInstruction);
}

void operande(char mot[]) {
    int rs, rt, rd, sa, imm, tg, i;
    char *bin1, *bin2, *bin3;

    char copie[32];
    strcpy(copie, mot);

    if (nomInstruction(copie) > 0 && nomInstruction(copie) < 17) {
        mot[26]='\0';
        sa= to_int(mot+21, 5);

        mot[21]='\0';
        rd= to_int(mot+16, 5);

        mot[16]='\0';
        rt= to_int(mot+11, 5);

        mot[11]='\0';
        rs= to_int(mot+6, 5);

        rt=lireRegistre(rt);
        rs=lireRegistre(rs);
        
        bin1 = "";
        bin2 = "";

        switch(nomInstruction(copie)) {
            case ADD:
                ecrireRegistre(rs+rt, rd);
                break;
            case AND:
                to_binary(rs, bin1, TAILLE_ELEM);
                to_binary(rt, bin2, TAILLE_ELEM);
                for(i=0;i<TAILLE_ELEM;i++) {
                    if (*(bin1+i)==1 || *(bin2+i)==1)
                        *(bin2+i)=0;
                }
                ecrireRegistre(to_int(bin2, 32), rd);
                break;
            case DIV:
                ecrireRegistre(rs/rt, LO);
                ecrireRegistre(rs%rt, HI);
                break;
            case JR:
                ecrireRegistre(rs, PC);
                break;
            case MFHI:
                ecrireRegistre(lireRegistre(HI), rd);
                break;
            case MFLO:
                ecrireRegistre(lireRegistre(LO), rd);
                break;
            case MULT:
                to_binary(rs*rt, bin1, 64);
                ecrireRegistre(to_int(bin1+32, 32),LO);
                bin1[32]='\0';
                ecrireRegistre(to_int(bin1, 32),HI);
                break;
            case NOP:
                break;
            case OR:
                to_binary(rs, bin1, TAILLE_ELEM);
                to_binary(rt, bin2, TAILLE_ELEM);
                for(i=0;i<TAILLE_ELEM;i++) {
                    if (*(bin1+i)==1)
                        *(bin2+i)=1;
                }
                ecrireRegistre(to_int(bin2, 32), rd);
                break;
            case SRL:
                to_binary(rt, bin1, TAILLE_ELEM);
                for(i=0;i<sa;i++)
                    *(bin2+i)='0';
                for(i=sa;i<32;i++)
                    *(bin2+i)=*(bin1+i-sa);
                *(bin2+32)='\0';
                ecrireRegistre(to_int(bin2, 32), rd);
                break;
            case SLL:
                to_binary(rt, bin1, TAILLE_ELEM);
                for(i=0;i<32-sa;i++)
                    *(bin2+i)=*(bin1+i+sa);
                for(i=32-sa;i<32;i++)
                    *(bin2+i)='0';
                *(bin2+32)='\0';
                ecrireRegistre(to_int(bin2, 32), rd);
                break;
            case SLT:
                if(rs<rt)
                    ecrireRegistre(1,rd);
                else 
                    ecrireRegistre(0,rd);
                break;
            case ROTR:
                to_binary(rt, bin1, TAILLE_ELEM);
                for(i=0;i<sa;i++)
                    *(bin2+i)=*(bin1+i+32-sa);
                for(i=sa;i<32;i++)
                    *(bin2+i)=*(bin1+i-sa);
                *(bin2+32)='\0';
                ecrireRegistre(to_int(bin2, 32), rd);
                break;
            case SUB:
                ecrireRegistre(rs-rt, rd);
                break;
            case SYSCALL:
                /* pas géré pour l'instant */
                break;
            case XOR:
                to_binary(rs, bin1, TAILLE_ELEM);
                to_binary(rt, bin2, TAILLE_ELEM);
                for(i=0;i<TAILLE_ELEM;i++) {
                    if (*(bin1+i)==1 && *(bin2+i)==1)
                        *(bin2+i)=0;
                    if (*(bin1+i)==1)
                        *(bin2+i)=0;
                }
                ecrireRegistre(to_int(bin2, 32), rd);
                break;
        }
    }
    if (nomInstruction(copie) > 16 && nomInstruction(copie) < 25) {
        imm=to_int(mot+16, 16);

        mot[16]='\0';
        rt= to_int(mot+11, 5);

        mot[11]='\0';
        rs= to_int(mot+6, 5);

        rs = lireRegistre(rs);
        switch(nomInstruction(copie)) {
            case ADDI:
                ecrireRegistre(rs+imm, rt);
                break;
            case BEQ:
                rt = lireRegistre(rt);
                to_binary(imm, bin1, 16);
                strcat(bin1, "00");
                if(rs == rt)
                    ecrireRegistre(PC+4+to_int(bin1, 18),PC);
                break;
            case BGTZ:
                to_binary(imm, bin1, 16);
                strcat(bin1, "00");
                if(rs > 0)
                    ecrireRegistre(PC+4+to_int(bin1, 18),PC);
                break;
            case BLEZ:
                to_binary(imm, bin1, 16);
                strcat(bin1, "00");
                if(rs <= 0)
                    ecrireRegistre(PC+4+to_int(bin1, 18),PC);
                break;
            case BNE:
                rt = lireRegistre(rt);
                to_binary(imm, bin1, 16);
                strcat(bin1, "00");
                if(rs != rt)
                    ecrireRegistre(PC+4+to_int(bin1, 18),PC);
                break;
            case LUI:
                to_binary(imm, bin1, 16);
                strcat(bin1, "0000000000000000");
                ecrireRegistre(to_int(bin1, 32), rt);
                break;
            case LW:
                to_binary(rs+imm, bin1, 32);
                lireMemoire(bin1, bin2, memoireInst);
                ecrireRegistre(to_int(bin2, 32), rt);
                break;
            case SW:
                rt = lireRegistre(rt);
                to_binary(rt, bin1, 32);
                to_binary(rs+imm, bin2, 32);
                ecrireMemoire(bin2, bin1, memoireInst);
                break;
        }
    }
    if (nomInstruction(copie) > 24 && nomInstruction(copie) < 27) {
        tg=to_int(mot+6, 26);
        
        bin3 = "";

        switch(nomInstruction(copie)) {
            case J:
                to_binary(lireRegistre(PC), bin1, 32);
                bin2[0] = bin1[0];
                bin2[1] = bin1[1];
                bin2[2] = bin1[2];
                bin2[3] = bin1[3];

                to_binary(tg, bin3, 26);
                strcat(bin3, "00");
                strcat(bin2, bin3);

                ecrireRegistre(to_int(bin2, 32), PC);
                break;
            case JAL:
                ecrireRegistre(lireRegistre(PC)+4, RA);

                to_binary(lireRegistre(PC)+4, bin1, 32);
                bin2[0] = bin1[0];
                bin2[1] = bin1[1];
                bin2[2] = bin1[2];
                bin2[3] = bin1[3];

                to_binary(tg, bin3, 26);
                strcat(bin3, "00");
                strcat(bin2, bin3);

                ecrireRegistre(to_int(bin2, 32), PC);
                break;
        }
    }
}
