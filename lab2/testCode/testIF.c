#include <stdio.h>
#include <assert.h>
#include <assert.h>
#include <stdlib.h>

struct Instr {
  int regDst;
  int aluSrc;
  int aluOp;
  int memWrite;
  int memRead;
  int memToReg;
  int regWrite;

  char opcode[];
  char args[3];
  long rs, rt, rd;
};

struct Instr instr_fields[1];

int parseFile(char* in) {
  
  FILE* inputF = fopen(in, "r");
  char delimiters[]=", " // TODO: Maybe add the $ in here to be delimited
  char buffer[100];
  int lineNum=0;
  char *token;
  
  while (fgets(buffer, 100, inputF)) {
    instr_fields[lineNum].opcode = strtok(buffer,delimiters);
    instr_fields[lineNum].args[0] = strtok(NULL,delimiters);
    instr_fields[lineNum].args[1] = strtok(NULL,delimiters);
    instr_fields[lineNum].args[2] = strtok(NULL,delimiters);
    
    assert(strtok(NULL,delimiters) == NULL); // Checks for additional parameters

    lineNum++;
  }
  fclose(inputF);
  return 0;
}
struct Instr IF(char* in) {
 // int i;
 // for(i=0;i<EOF;i++) {
 //   if(strcmp("HALTINSTRUCTION", fgets(inputF)) == 0) {
 //     exit(0);
 //   }
 // }

    return newInstr;
}

int main (int argc, char *argv[]) {
    assert(parseFile("./textInstructions.txt")==0);
}
