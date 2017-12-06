#include "../header/utils.h"
#include "../header/convert_hexa.h"

#define MAX_SIZE 32
#define MAX_SIZE_FILE 100

const char name[] = "test.txt";    

int main(int argc, char *argv[]) {
    char *token;
    char operande[MAX_SIZE] = ""; 
    char instruction[MAX_SIZE] = "";
    
    char type = 0;
    /* Type I, J ou R */
    
    FILE* program = NULL;
    
    program = fopen(name, "r");
    
    if (program != NULL) {
        fgets(operande, MAX_SIZE_FILE, program);
        token = strchr(operande, ' ');
        *token = '\0';
        
        type = type_instruction(operande);
        
        if (type == 'I')
            typeI_to_hexa(operande, token, instruction);
        if (type == 'J')
            typeJ_to_hexa(operande, token, instruction);
        if (type == 'R')
            typeR_to_hexa(operande, token, instruction);
        
        printf("%x\n", to_int(instruction, 32));
        
        fclose(program);
    }
}
