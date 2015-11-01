// Authors: Shikang Xu; ECE 353 TA
//          Calvin Tran
//          Delphine Mweze
//          Oscar Lee

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SINGLE 1
#define BATCH 0
#define REG_NUM 32

// Structures
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

struct Latch {
  int validBit;
  struct Instr *data; //instruction currently held
};

// GLOBAL VARIABLES
struct Instr instr_mem[10];
struct Latch IFID, IDEX, EXMEM, MEMWB;
char buffer[40];
long mips_reg[REG_NUM];

// GLOBAL FUNCTIONS
void IF();
int countLine(char *);
struct Instr progScanner(char *);
int regConverter(char*);

main (int argc, char *argv[]){
  int sim_mode=0;   // mode flag, 1 for single-cycle, 0 for batch
  long pgm_c=0;     // program counter
  long sim_cycle=0; // simulation cycle counter
  
  //define your own counter for the usage of each pipeline stage here
  
  int test_counter=0;
  
  int lineNum = 0;
  char *textInst = (char*) malloc(30);
  strcpy(textInst, "./textInstructions.txt");
  FILE* fp = fopen(textInst, "r");
  
  assert(fp!=NULL);
  
  FILE *input=;     // Input a set of instructions
  FILE *output=NULL;    // Output the data
  
  int i;
  printf("The arguments are:");
  for(i=1;i<argc;i++){
    printf("%s ",argv[i]);
  }
  
  //choosing the simulation mode
  int c,m,n;
  printf("\n");
  if(argc==7){
    if(strcmp("-s",argv[1])==0){
      sim_mode=SINGLE;
    }
    else if(strcmp("-b",argv[1])==0){
      sim_mode=BATCH;
    }
    else{
      printf("Wrong sim mode chosen\n");
      exit(0);
    }
    
    m=atoi(argv[2]); // number of cycles needed by miltiplication
    n=atoi(argv[3]); // other operation
    c=atoi(argv[4]); // memory access
    input=fopen(argv[5],"r");
    output=fopen(argv[6],"w");
  }
  
  else{
    printf("Usage: ./sim-mips -s m n c input_name output_name (single-sysle mode)\n or \n ./sim-mips -b m n c input_name  output_name(batch mode)\n");
    printf("m,n,c stand for number of cycles needed by multiplication, other operation, and memory access, respectively\n");
    exit(0);
  }
  
  if(input==NULL){
    printf("Unable to open input or output file\n");
    exit(0);
  }
  
  if(output==NULL){
    printf("Cannot create output file\n");
    exit(0);
  }
  
  //initialize registers and program counter
  if(sim_mode==1){
    for (i=0;i<REG_NUM;i++){
      mips_reg[i]=0;
    }
  }
  
  //start your code from here
}