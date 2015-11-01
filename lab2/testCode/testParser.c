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
  int rs, rt, rd;
};

// GLOBAL VARIABLES
struct Instr instr_mem[10];

// GLOBAL FUNCTIONS
struct Instr progScanner(char *);
int regConverter(char*);

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
    printf("Instruction argument error: expect (4), got %d\n", tokenSize);
    exit(0);
  }
  
  // regNumberConverter
  char delimiters2[]=" ";
  
  token = strtok(sanitize, delimiters2);

  if (strcmp(token, "add") == 0) {  // filters for a bad opcode
  } else if (strcmp(token, "addi") == 0) {
  } else if (strcmp(token, "sub") == 0) {
  } else if (strcmp(token, "mul") == 0) {
  } else if (strcmp(token, "beq") == 0) {
  } else if (strcmp(token, "lw") == 0) {
  } else if (strcmp(token, "sw") == 0) {
  } else {
    printf("The opcode of the instruction is invalid or not supported.\n");
    exit(0);
  }
  
    // parser
  // opcode
  struct Instr instrObj;
  //zeroOutInstr(instrObj);
  instrObj.opcode = token;
  
  // arg0
  token = strtok(NULL, delimiters2);
  instrObj.arg0 = regConverter(token);
  
  if (strcmp(instrObj.opcode, "sw") == 0) {
    // arg1
    token = strtok(NULL, delimiters2);
    instrObj.arg1 = atoi(token);
    
  } else if (strcmp(instrObj.opcode, "lw") == 0) {
    // arg1
    token = strtok(NULL, delimiters2);
    instrObj.arg1 = atoi(token);
    
  } else {
    // arg1
    token = strtok(NULL, delimiters2);
    instrObj.arg1 = regConverter(token);
  }
  
  // arg2
  token = strtok(NULL, delimiters2);
  instrObj.arg2 = regConverter(token);
  
  return instrObj;
}

int regConverter(char* str) {
  int ret = 0;
  if (strcmp(str, "zero") == 0) { ret = 0; }
  else if (strcmp(str, "at") == 0) { ret = 1; }
  else if (strcmp(str, "v0") == 0) { ret = 2; }
  else if (strcmp(str, "v1") == 0) { ret = 3; }
  else if (strcmp(str, "a0") == 0) { ret = 4; }
  else if (strcmp(str, "a1") == 0) { ret = 5; }
  else if (strcmp(str, "a2") == 0) { ret = 6; }
  else if (strcmp(str, "a3") == 0) { ret = 7; }
  else if (strcmp(str, "t0") == 0) { ret = 8; }
  else if (strcmp(str, "t1") == 0) { ret = 9; }
  else if (strcmp(str, "t2") == 0) { ret = 10; }
  else if (strcmp(str, "t3") == 0) { ret = 11; }
  else if (strcmp(str, "t4") == 0) { ret = 12; }
  else if (strcmp(str, "t5") == 0) { ret = 13; }
  else if (strcmp(str, "t6") == 0) { ret = 14; }
  else if (strcmp(str, "t7") == 0) { ret = 15; }
  else if (strcmp(str, "s0") == 0) { ret = 16; }
  else if (strcmp(str, "s1") == 0) { ret = 17; }
  else if (strcmp(str, "s2") == 0) { ret = 18; }
  else if (strcmp(str, "s3") == 0) { ret = 19; }
  else if (strcmp(str, "s4") == 0) { ret = 20; }
  else if (strcmp(str, "s5") == 0) { ret = 21; }
  else if (strcmp(str, "s6") == 0) { ret = 22; }
  else if (strcmp(str, "s7") == 0) { ret = 23; }
  else if (strcmp(str, "t8") == 0) { ret = 24; }
  else if (strcmp(str, "t9") == 0) { ret = 25; }
  else if (strcmp(str, "k0") == 0) { ret = 26; }
  else if (strcmp(str, "k1") == 0) { ret = 27; }
  else if (strcmp(str, "gp") == 0) { ret = 28; }
  else if (strcmp(str, "sp") == 0) { ret = 29; }
  else if (strcmp(str, "fp") == 0) { ret = 30; }
  else if (strcmp(str, "ra") == 0) { ret = 31; }
  else {
    printf("Register name error: %s\n", str);
    exit(0);
  }
  return ret;
}