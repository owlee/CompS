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
  
  // Holder Values to organize
  int arg0, arg1, arg2;
  
  // Acutal Destinations of Instruction
  char *opcode;
  int rs, rt, rd, imm;
  long *temp;
};

// GLOBAL VARIABLES
struct Instr instr_mem[10];

// GLOBAL FUNCTIONS
void IF();
int countLine(char *);

int main (int argc, char *argv[]) {
  char *textInst = (char*) malloc(30);
  strcpy(textInst, "./textInstructions.txt");
  
  FILE* fp = fopen(textInst, "r");
  assert(fp!=NULL);
  
  char buffer[40];
  int lineNum = 0;
  
  fclose(fp);
  return 0; //for success
}

void Instr IF() {

  //TODO: Dynamically allocate more space for instr_mem like realloc.
  //if lineNum < memNum

}


int countLine(char *in) {
  FILE *fp = fopen(in, "r");
  int lines = 0;
  char ch;

  ch = getc(fp);
  while (ch != EOF) {
    if (ch == '\n') {
      lines = lines+1;
    }
    ch = getc(fp);
  }
  return lines+1;
}

