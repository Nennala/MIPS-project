#include "../header/utils.h"
#include "../header/convert_hexa.h"

#define MAX_SIZE 32
#define MAX_SIZE_FILE 100

const char name[] = "test.txt";    

int main(int argc, char *argv[]) {
    int i;
    char *token = NULL;
    char operande[MAX_SIZE] = ""; 
    char instruction[MAX_SIZE] = "";
    
    char type = 0;
    /* Type I, J ou R */
    
    FILE* program = NULL;
    
    program = fopen(name, "r");
    
    if (program != NULL) {
        while (fgets(operande, MAX_SIZE_FILE, program) != NULL) {
            i = 0;
            while (operande[i] == ' ' && i < 32) {
                strcpy(operande,operande+1);
                i++;
            }
            if (i != 32 && operande[0] != '\n') {
                token = strchr(operande, ' ');
                if (token != NULL)
                    *token = '\0';
                else {
                    token = strchr(operande, '\n');
                    *token = '\0';
                }
            
                if (operande[0] != '#') {
                    type = type_instruction(operande);
            
                    strcpy(instruction, "");
                    if (type == 'I')
                        typeI_to_hexa(operande, token, instruction);
                    if (type == 'J')
                        typeJ_to_hexa(operande, token, instruction);
                    if (type == 'R')
                        typeR_to_hexa(operande, token, instruction);
        
                    printf("%08x\n", to_int(instruction, 32));
                }
            }
        }
        fclose(program);
    }
    else {
        perror("fopen");
    }
    return 0;
}
