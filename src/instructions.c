/* -----------------------------------------
 * Nom : Porteries Daphné, Champey Vincent
 * ----------------------------------------- */

#include "../header/instructions.h"

int nomInstruction(char mot[]) {
    char *copieMot = NULL;

    copieMot= malloc(32*sizeof(char));
    if (copieMot == NULL)
        exit(0);

    int numeroInstruction=0;
    char *finMot;

    strcpy(copieMot, mot);
    mot[6]='\0';
    
    finMot = copieMot+26;

    if (strcmp(mot, "000010")==0)
        numeroInstruction=J_I;
    if (strcmp(mot, "000011")==0)
        numeroInstruction=JAL_I;
    if (strcmp(mot, "001000")==0)
        numeroInstruction=ADDI_I;
    if (strcmp(mot, "000100")==0) 
        numeroInstruction=BEQ_I;
    if (strcmp(mot, "000111")==0) 
        numeroInstruction=BGTZ_I;
    if (strcmp(mot, "000110")==0) 
        numeroInstruction=BLEZ_I;
    if (strcmp(mot, "000101")==0) 
        numeroInstruction=BNE_I;
    if (strcmp(mot, "001111")==0) 
        numeroInstruction=LUI_I;
    if (strcmp(mot, "100011")==0) 
        numeroInstruction=LW_I;
    if (strcmp(mot, "101010")==0)
        numeroInstruction=SW_I;
    if (strcmp(mot, "000000")==0) {
        if (strcmp(finMot, "100000")==0)
            numeroInstruction=ADD_I;
        if (strcmp(finMot, "100100")==0)
            numeroInstruction=AND_I;
        if (strcmp(finMot, "011010")==0)
            numeroInstruction=DIV_I;
        if (strcmp(finMot, "001000")==0)
            numeroInstruction=JR_I;
        if (strcmp(finMot, "010000")==0)
            numeroInstruction=MFHI_I;
        if (strcmp(finMot, "010010")==0)
            numeroInstruction=MFLO_I;
        if (strcmp(finMot, "011000")==0)
            numeroInstruction=MULT_I;
        if (strcmp(finMot, "100101")==0)
            numeroInstruction=OR_I;
        if (strcmp(finMot, "000000")==0) {
            if (strcmp(copieMot,"00000000000000000000000000000000") == 0)
                numeroInstruction=NOP_I;
            else 
                numeroInstruction=SLL_I;
        }
        if (strcmp(finMot, "101010")==0)
            numeroInstruction=SLT_I;
        if (strcmp(finMot, "100010")==0)
            numeroInstruction=SUB_I;
        if (strcmp(finMot, "001100")==0)
            numeroInstruction=SYSCALL_I;
        if (strcmp(finMot, "100110")==0)
            numeroInstruction=XOR_I;
        if (strcmp(finMot, "000010")==0) {
            if (copieMot[10]=='1')
                numeroInstruction=SRL_I;
            if (copieMot[10]=='0')
                numeroInstruction=ROTR_I;
        }
    }
    if (numeroInstruction == 0)
        printf("Erreur dans le code binaire.\n");

    free(copieMot);

    return(numeroInstruction);
}

void execution(char mot[]) {
    int rs, rt, rd, sa, imm, tg, i, rt_val, rs_val;
    char *bin1, *bin2, *bin3, *imm_bin;

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

        rt_val=lireRegistre(rt);
        rs_val=lireRegistre(rs);
        
        bin1 = "";
        bin2 = "";

        switch(nomInstruction(copie)) {
            case ADD_I:
                printf("C'est un ADD $%d, $%d, $%d !\n", rd, rs, rt);
                ecrireRegistre(rs_val+rt_val, rd);
                break;
            case AND_I:
                printf("C'est un AND $%d, $%d, $%d !\n", rd, rs, rt);
                to_binary(rs_val, bin1, TAILLE_ELEM);
                to_binary(rt_val, bin2, TAILLE_ELEM);
                for(i=0;i<TAILLE_ELEM;i++) {
                    if (*(bin1+i)==1 || *(bin2+i)==1)
                        *(bin2+i)=0;
                }
                ecrireRegistre(to_int(bin2, 32), rd);
                break;
            case DIV_I:
                printf("C'est un DIV $%d, $%d !\n", rs, rt);
                ecrireRegistre(rs_val/rt_val, LO);
                ecrireRegistre(rs_val%rt_val, HI);
                break;
            case JR_I:
                printf("C'est un JR $%d !\n", rs);
                ecrireRegistre(rs_val, PC);
                break;
            case MFHI_I:
                printf("C'est un MFHI $%d !\n", rd);
                ecrireRegistre(lireRegistre(HI), rd);
                break;
            case MFLO_I:
                printf("C'est un MFLO $%d !\n", rd);
                ecrireRegistre(lireRegistre(LO), rd);
                break;
            case MULT_I:
                printf("C'est un MULT $%d, $%d !\n", rs, rt);
                to_binary(rs_val*rt_val, bin1, 64);
                ecrireRegistre(to_int(bin1+32, 32),LO);
                bin1[32]='\0';
                ecrireRegistre(to_int(bin1, 32),HI);
                break;
            case NOP_I:
                printf("C'est un NOP !\n");
                break;
            case OR_I:
                printf("C'est un OR $%d, $%d, $%d !\n", rd, rs, rt);
                to_binary(rs_val, bin1, TAILLE_ELEM);
                to_binary(rt_val, bin2, TAILLE_ELEM);
                for(i=0;i<TAILLE_ELEM;i++) {
                    if (*(bin1+i)==1)
                        *(bin2+i)=1;
                }
                ecrireRegistre(to_int(bin2, 32), rd);
                break;
            case SRL_I:
                printf("C'est un SRL $%d, $%d, $%d !\n", rd, rt, sa);
                to_binary(rt_val, bin1, TAILLE_ELEM);
                for(i=0;i<sa;i++)
                    *(bin2+i)='0';
                for(i=sa;i<32;i++)
                    *(bin2+i)=*(bin1+i-sa);
                *(bin2+32)='\0';
                ecrireRegistre(to_int(bin2, 32), rd);
                break;
            case SLL_I:
                printf("C'est un SLL $%d, $%d, $%d !\n", rd, rt, sa);
                to_binary(rt_val, bin1, TAILLE_ELEM);
                for(i=0;i<32-sa;i++)
                    *(bin2+i)=*(bin1+i+sa);
                for(i=32-sa;i<32;i++)
                    *(bin2+i)='0';
                *(bin2+32)='\0';
                ecrireRegistre(to_int(bin2, 32), rd);
                break;
            case SLT_I:
                printf("C'est un SLT $%d, $%d, $%d !\n", rd, rs, rt);
                if(rs_val<rt_val)
                    ecrireRegistre(1,rd);
                else 
                    ecrireRegistre(0,rd);
                break;
            case ROTR_I:
                printf("C'est un ROTR $%d, $%d, $%d !\n", rd, rt, sa);
                to_binary(rt_val, bin1, TAILLE_ELEM);
                for(i=0;i<sa;i++)
                    *(bin2+i)=*(bin1+i+32-sa);
                for(i=sa;i<32;i++)
                    *(bin2+i)=*(bin1+i-sa);
                *(bin2+32)='\0';
                ecrireRegistre(to_int(bin2, 32), rd);
                break;
            case SUB_I:
                printf("C'est un SUB $%d, $%d, $%d !\n", rd, rs, rt);
                ecrireRegistre(rs_val-rt_val, rd);
                break;
            case SYSCALL_I:
                printf("C'est un SYSCALL !\n");
                /* pas géré pour l'instant */
                break;
            case XOR_I:
                printf("C'est un XOR $%d, $%d, $%d !\n", rd, rs, rt);
                to_binary(rs_val, bin1, TAILLE_ELEM);
                to_binary(rt_val, bin2, TAILLE_ELEM);
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
        imm_bin = mot+16;
        if (*imm_bin == '1') {
            complement2(imm_bin,16);
            imm = -1*to_int(imm_bin,16);
        }
        else
            imm=to_int(imm_bin, 16);

        mot[16]='\0';
        rt= to_int(mot+11, 5);

        mot[11]='\0';
        rs= to_int(mot+6, 5);

        rs_val = lireRegistre(rs);
        switch(nomInstruction(copie)) {
            case ADDI_I:
                printf("C'est un ADDI $%d, $%d, %d !\n", rt, rs, imm);
                ecrireRegistre(rs_val+imm, rt);
                break;
            case BEQ_I:
                printf("C'est un BEQ $%d, $%d, %d !\n", rs, rt, imm);
                rt_val = lireRegistre(rt);
                to_binary(imm, bin1, 16);
                strcat(bin1, "00");
                if(rs_val == rt_val)
                    ecrireRegistre(PC+4+to_int(bin1, 18),PC);
                break;
            case BGTZ_I:
                printf("C'est un BGTZ $%d, %d !\n", rs, imm);
                to_binary(imm, bin1, 16);
                strcat(bin1, "00");
                if(rs_val > 0)
                    ecrireRegistre(PC+4+to_int(bin1, 18),PC);
                break;
            case BLEZ_I:
                printf("C'est un BLEZ $%d, %d !\n", rs, imm);
                to_binary(imm, bin1, 16);
                strcat(bin1, "00");
                if(rs_val <= 0)
                    ecrireRegistre(PC+4+to_int(bin1, 18),PC);
                break;
            case BNE_I:
                printf("C'est un BNE $%d, $%d, %d !\n", rs, rt, imm);
                rt_val = lireRegistre(rt);
                to_binary(imm, bin1, 16);
                strcat(bin1, "00");
                if(rs_val != rt_val)
                    ecrireRegistre(PC+4+to_int(bin1, 18),PC);
                break;
            case LUI_I:
                printf("C'est un LUI $%d, %d !\n", rt, imm);
                to_binary(imm, bin1, 16);
                strcat(bin1, "0000000000000000");
                ecrireRegistre(to_int(bin1, 32), rt);
                break;
            case LW_I:
                printf("C'est un LW $%d, %d(%d) !\n", rt, imm, rs);
                to_binary(rs_val+imm, bin1, 32);
                lireMemoire(bin1, bin2, memoireInst);
                ecrireRegistre(to_int(bin2, 32), rt);
                break;
            case SW_I:
                printf("C'est un SW $%d, %d(%d) !\n", rt, imm, rs);
                rt_val = lireRegistre(rt);
                to_binary(rt_val, bin1, 32);
                to_binary(rs_val+imm, bin2, 32);
                ecrireMemoire(bin2, bin1, &memoireInst);
                break;
        }
    }
    if (nomInstruction(copie) > 24 && nomInstruction(copie) < 27) {
        tg=to_int(mot+6, 26);
        
        bin3 = "";

        switch(nomInstruction(copie)) {
            case J_I:
                printf("C'est un J %d !\n", tg);
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
            case JAL_I:
                printf("C'est un JAL %d !\n", tg);
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
