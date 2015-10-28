#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Instr {
  int regDst;
  int aluSrc;
  int aluOp;
  int memWrite;
  int memRead;
  int memToReg;
  int regWrite;
  
  char *opcode, *arg0, *arg1, *arg2;
  long rs, rt, rd;
};

struct Instr instr_fields[2];

int parseFile(char* in) {
  
  FILE* fp = fopen(in, "r");
  assert(fp!=NULL);
  char delimiters[]=", ;"; // TODO: Maybe add the $ in here to be delimited
  char buffer[1024];
  int lineNum=0;
  
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    printf("line: %s\n", buffer);
    
    instr_fields[lineNum].opcode = strtok(buffer,delimiters);
    //printf("String : %s\n", instr_fields[lineNum].opcode);
    instr_fields[lineNum].arg0 = strtok(NULL,delimiters);
    //printf("String : %s\n", instr_fields[lineNum].arg0);
    instr_fields[lineNum].arg1 = strtok(NULL,delimiters);
    //printf("String : %s\n", instr_fields[lineNum].arg1);
    instr_fields[lineNum].arg2 = strtok(NULL,delimiters);
    //printf("String : %s\n", instr_fields[lineNum].arg2);
    
    printf("line number: %d\n", lineNum);
    
    lineNum++;
  }
  fclose(fp);
  return 0;
}
struct Instr IF(char* in) {
  // int i;
  // for(i=0;i<EOF;i++) {
  //   if(strcmp("HALTINSTRUCTION", fgets(inputF)) == 0) {
  //     exit(0);
  //   }
  // }
  struct Instr nop;
  return nop;
  //return newInstr;
};

int main (int argc, char *argv[]) {
  assert(parseFile("./textInstructions.txt")==0);
  
  printf("String : %s\n", instr_fields[0].opcode);
  printf("String : %s\n", instr_fields[0].arg0);
  printf("String : %s\n", instr_fields[0].arg1);
  printf("String : %s\n", instr_fields[0].arg2);
  
  printf("String : %s\n", instr_fields[1].opcode);
  printf("String : %s\n", instr_fields[1].arg0);
  printf("String : %s\n", instr_fields[1].arg1);
  printf("String : %s\n", instr_fields[1].arg2);

  
}
