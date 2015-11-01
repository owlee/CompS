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
int statusIF;

struct Instr IF(char* buffer, int lineNum) {
  assert(buffer != NULL);

  //TODO: Dynamically allocate more space for instr_mem like realloc.
  //if lineNum < memNum

  char delimiters[]=", ;\n"; // TODO: Maybe add the $ in here to be delimited
  char* token;

  token = strtok(buffer, delimiters);
  int i;
  for(i=0; i<8; i++) {
    if (token != instruction[i])
  }

//  token = strtok(buffer, delimiters);
//  strcpy(instr_mem[lineNum].func, token);

//  token = strtok(NULL, delimiters);
//  strcpy(instr_mem[lineNum].arg0, token);

//  token = strtok(NULL, delimiters);
//  strcpy(instr_mem[lineNum].arg1, token);

  token = strtok(NULL, delimiters);  //dealing with sw and lw
  if (token != 0) {
    strcpy(instr_mem[lineNum].arg2, token);
  }

  //counter++;
  return instr_mem[lineNum];

  // int i;
  // for(i=0;i<EOF;i++) {
  //   if(strcmp("HALTINSTRUCTION", fgets(inputF)) == 0) {
  //     exit(0);
  //   }
  // }


  //push a nop object through if there is nothing in the args
}

int main (int argc, char *argv[]) {
  char *textInst = (char*) malloc(30);
  strcpy(textInst, "./textInstructions.txt");

  FILE* fp = fopen(textInst, "r");
  assert(fp!=NULL);

  char buffer[40];
  int lineNum = 0;
  while (fgets(buffer, sizeof(buffer), fp) != NULL) {
    IF(buffer, lineNum);
    lineNum++;
  }

  fclose(fp);
  return 0; //for success

  //assert(parseFile(textInst) == 0);
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

struct Instr IF(char* in, struct Instr instr_fields[]) {
  // int i;
  // for(i=0;i<EOF;i++) {
  //   if(strcmp("HALTINSTRUCTION", fgets(inputF)) == 0) {
  //     exit(0);
  //   }
  // }
  assert(parseFile(in, instr_fields)==0);

  struct Instr nop;
  return nop;

  //return newInstr;
};

int main (int argc, char *argv[]) {
   struct Instr *instr_fields = malloc(sizeof(struct Instr));
   char *textInst = (char*) malloc(30);
  strcpy(textInst, "./textInstructions.txt");
 assert(parseFile("./textInstructions.txt", instr_fields)==0);
  struct Instr instr_mem[countLine(textInst)];

   printf("Number of lines in file: %i\n", countLine(textInst));

   printf("String : %s\n", instr_fields[0].func);
   printf("String : %s\n", instr_fields[0].arg0);
   printf("String : %s\n", instr_fields[0].arg1);
   printf("String : %s\n", instr_fields[0].arg2);

   //printf("String : %s\n", instr_fields[1].func);
   //printf("String : %s\n", instr_fields[1].arg0);
   //printf("String : %s\n", instr_fields[1].arg1);
   //printf("String : %s\n", instr_fields[1].arg2);
   free(instr_fields);
  //
  //  printf("String : %s\n", instr_fields[2].func);
  //  printf("String : %s\n", instr_fields[2].arg0);
  //  printf("String : %s\n", instr_fields[2].arg1);
  //  printf("String : %s\n", instr_fields[2].arg2);
}

