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
  
  char func[10];
  long *arg0, *arg1, *arg2;
  long rs, rt, rd;
};

struct Instr instr_mem[10];

struct Instr progScanner(char *);

int main (int argc, char *argv[]) {
  char *textInst = (char*) malloc(30);
  strcpy(textInst, "./textInstructions.txt");
  
  FILE* fp = fopen(textInst, "r");
  assert(fp!=NULL);
  
  char buffer[40];
  int lineNum = 0;
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    instr_mem[lineNum] = progScanner(buffer);
    lineNum++;
  }
  
  fclose(fp);
  return 0; //for success
}

struct Instr progScanner(char* buffer) {
  //do initial checks for extra characters (( )) or s and t followed by number
  
  // progScanner initially
  char delimiters[]=", \n$()"; // TODO: Maybe add the $ in here to be delimited
  char sanitize[40] = "";
  char* token = strtok(buffer, delimiters);
  int tokenSize = 0;
  
  while (token != '\0') {
    strcat(sanitize, token);
    token = strtok(NULL, delimiters);
    if (token != '\0') {
      strcat(sanitize, " ");
    }
    tokenSize++;
  }
  
  if (tokenSize != 4) {
    printf("Instruction argument error: expect (4), got %d", tokenSize);
    exit(0);
  }
  
  // regNumberConverter
  char delimiters2[]=" ";
  token = strtok(sanitize, delimiters2);
  enum instructions {add, addi, sub, mult, beq, lw, sw};
  enum instructions func =
  
  switch(token){
      
  }
  
  if (strcmp(token, ''))
  
  
  
  
  
  // parser()
  
  
  struct Instr nop;
  return nop;
}