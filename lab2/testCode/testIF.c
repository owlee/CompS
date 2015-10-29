#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Instr {
  int regDst;
  int aluSrc;
  int aluOp;
  int memWrite;
  int memRead;
  int memToReg;
  int regWrite;
  
  char func[10], arg0[10], arg1[10], arg2[10];
  long rs, rt, rd;
};

struct Instr instr_fields[10];

int parseFile(char* in) {
  
  FILE* fp = fopen(in, "r");
  assert(fp!=NULL);
  char delimiters[]=", ;$\n"; // TODO: Maybe add the $ in here to be delimited
  char buffer[40];
  int lineNum=0;
  
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    int i=0;
    
    while (buffer[i]) {
      
      buffer[i] =   tolower(buffer[i]);
      i++;
    }
    
    strcpy(instr_fields[lineNum].func, strtok(buffer,delimiters));
    strcpy(instr_fields[lineNum].arg0, strtok(NULL,delimiters));
    strcpy(instr_fields[lineNum].arg1, strtok(NULL,delimiters));
    strcpy(instr_fields[lineNum].arg2, strtok(NULL,delimiters));
    
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
  
  printf("String : %s\n", instr_fields[0].func);
  printf("String : %s\n", instr_fields[0].arg0);
  printf("String : %s\n", instr_fields[0].arg1);
  printf("String : %s\n", instr_fields[0].arg2);
  
  printf("String : %s\n", instr_fields[1].func);
  printf("String : %s\n", instr_fields[1].arg0);
  printf("String : %s\n", instr_fields[1].arg1);
  printf("String : %s\n", instr_fields[1].arg2);
  
  printf("String : %s\n", instr_fields[2].func);
  printf("String : %s\n", instr_fields[2].arg0);
  printf("String : %s\n", instr_fields[2].arg1);
  printf("String : %s\n", instr_fields[2].arg2);
}
