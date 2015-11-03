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
  int memWrite;
  int memRead;
  int regWrite;
  
  // Holder Values to organize
  int arg0, arg1, arg2;
  
  // Acutal Destinations of Instruction
  char opcode[4];
  int rs, rt, rd, imm;
  long product;
  int index;
  int halt;
};

struct Latch {
  int validBit;
  struct Instr data; //instruction currently held
};

// GLOBAL VARIABLES
char* instr_mem[512];  // 512 word size
struct Latch IFID, IDEX, EXMEM, MEMWB, haltLatch;
long mips_reg[REG_NUM];
long mem_reg[512];
double ifUtil=0, idUtil=0, exUtil=0, memUtil=0, wbUtil=0;
int PC=0, c, m, n;
int stallRAW;
static int evaluation[32];

// GLOBAL FUNCTIONS
void IF();
void ID();
void EX();
void MEM();
void WB();
struct Instr progScanner(char *);
int regConverter(char*);
void resolveBranch();
void resolveHazard();
void hazardDetection();

int main (int argc, char *argv[]) {
  int sim_mode=0;   // mode flag, 1 for single-cycle, 0 for batch
  long pgm_c=0;     // program counter
  long sim_cycle=0; // simulation cycle counter
  
  //define your own counter for the usage of each pipeline stage here
  
  int test_counter=0;
  
  // FILE setup
  FILE *input;     // Input a set of instructions
  FILE *output;    // Output the data
  
  int i;
  printf("The arguments are:");
  for(i=1;i<argc;i++){
    printf("%s ",argv[i]);
  }
  
  //choosing the simulation mode
  printf("\n");
  if (argc==7) {
    if (strcmp("-s",argv[1])==0){
      sim_mode=SINGLE;
    } else if(strcmp("-b",argv[1])==0){
      sim_mode=BATCH;
    } else{
      printf("Wrong sim mode chosen\n");
      exit(0);
    }
    
    m=atoi(argv[2]); // number of cycles needed by miltiplication
    n=atoi(argv[3]); // other operation
    c=atoi(argv[4]); // memory access
    
    input=fopen(argv[5],"r");
    output=fopen(argv[6],"w");
    
  } else {
    printf("Usage: ./sim-mips -s m n c input_name output_name (single-sysle mode)\n or \n ./sim-mips -b m n c input_name  output_name(batch mode)\n");
    printf("m,n,c stand for number of cycles needed by multiplication, other operation, and memory access, respectively\n");
    exit(0);
  }
  
  if (input == NULL) {
    printf("Unable to open input or output file\n");
    exit(0);
  }
  
  if (output == NULL) {
    printf("Cannot create output file\n");
    exit(0);
  }
  
  // parsing the file
  int x = 0;
  char buffer[40];
  char *temp;
  
  while ((temp = fgets(buffer, sizeof(buffer), input)) != NULL) {
    instr_mem[x] = strdup(temp);
    x++;
  }
  
  //initialize registers so displays as empty for single mode
  if (sim_mode == 1) {
    for (i=0;i<REG_NUM;i++){
      mips_reg[i]=0;
    }
  }
  
  if (sim_mode == 0) {  // batch cycle
    
    while (1) {
      if (haltLatch.data.halt == 1) { break; }
      
      WB();
      MEM();
      EX();
      ID();
      if ( stallRAW == 0){
        IF();
      }
      
    }
    
    // ----- Code 3 -----
    // Add the following code to the end of the simulation,
    // to output statistics in batch mode
    
    fprintf(output,"program name: %s\n",argv[5]);
    fprintf(output,"stage utilization: %f  %f  %f  %f  %f \n", ifUtil, idUtil, exUtil, memUtil, wbUtil);
    // add the (double) stage_counter/sim_cycle for each
    // stage following sequence IF ID EX MEM WB
    
    fprintf(output,"register values ");
    for (i=1;i<REG_NUM;i++){
      fprintf(output,"%ld  ", mips_reg[i]);
    }
    fprintf(output,"%ld\n", pgm_c);
    
  } else {  // single cycle
    
      while (1) {
      if (haltLatch.data.halt == 1) { break; }
      
      WB();
      MEM();
      EX();
      ID();
      if ( stallRAW == 0){ IF(); }
        
      printf("cycle: %ld ",sim_cycle);
      if(sim_mode==1){
        for (i=1;i<REG_NUM;i++){
          printf("%ld  ",mips_reg[i]);
        }
      }
      
      printf("%ld\n",pgm_c);
      pgm_c+=4;
      sim_cycle+=1;
      test_counter++;
      printf("press ENTER to continue\n");
      while (getchar() != '\n');
        
    }
    
  }
  
  // Clean up
  fclose(input);
  fclose(output);
  return 0;
}

void IF() {
  
  struct Instr instrObj = {0};

  if (instr_mem[PC] != NULL) {
    
    if (strcmp(instr_mem[PC], "haltSimulation") == 0) {
      instrObj.halt = 1;
      
    } else {
      instrObj = progScanner(instr_mem[PC]);
      ifUtil+=n;
    }
    
    PC++;
    IFID.validBit = 1;
    IFID.data = instrObj;
  }
}

struct Instr progScanner(char* in) {
  //do initial checks for extra characters (( )) or s and t followed by number
  
  // progScanner initially
  char delimiters[]=", \n$()"; // TODO: Maybe add the $ in here to be delimited
  char sanitize[40] = "";
  char* token = strtok(in, delimiters);
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
  
  //instrObj.opcode = token;
  //instrObj.opcode = "";
  strcpy(instrObj.opcode, token);
  
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
  if (strcmp(instrObj.opcode, "addi") == 0) {
    token = strtok(NULL, delimiters2);
    instrObj.arg2 = atoi(token);
  } else {
    token = strtok(NULL, delimiters2);
    instrObj.arg2 = regConverter(token);
  }
  
  
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


void ID() {
  if (IFID.validBit == 1){
    struct Instr test = IFID.data;
    test.imm = 0;
    IFID.validBit = 0;
    
    if (test.halt == 1) { // halt cleanup
      IDEX.data = test;
      IDEX.validBit = 1;
      
    } else {
      
      if(test.imm > 65535){
        printf("%s\n, %i\n", test.opcode, test.imm);
        printf("%s", "Immediate field is out of range\n");
        exit(0);
      }
      if(strcmp(test.opcode, "add") == 0){
        test.rd = test.arg0;
        test.rs = test.arg1;
        test.rt = test.arg2;
        test.memRead = 0;
        test.memWrite = 0;
        test.regWrite = 1;
        hazardDetection(test);
        resolveHazard(test);
      }
      
      else if(strcmp(test.opcode, "addi") == 0){
        test.rd = test.arg0;
        test.rs = test.arg1;
        test.imm = test.arg2;
        test.memRead = 0;
        test.memWrite = 0;
        test.regWrite = 1;
        test.rt = test.rd;
        hazardDetection(test);
        resolveHazard(test);
      }
      else if(strcmp(test.opcode, "sub") == 0){
        test.rd = test.arg0;
        test.rs = test.arg1;
        test.rt = test.arg2;
        test.memRead = 0;
        test.memWrite = 0;
        test.regWrite = 1;
        hazardDetection(test);
        resolveHazard(test);
      }
      else if(strcmp(test.opcode, "mul") == 0){
        test.rd = test.arg0;
        test.rs = test.arg1;
        test.rt = test.arg2;
        test.memRead = 0;
        test.memWrite = 0;
        test.regWrite = 1;
        hazardDetection(test);
        resolveHazard(test);
      }
      
      else if(strcmp(test.opcode, "beq") == 0){
        test.rs = test.arg0;
        test.rt = test.arg1;
        test.imm = test.arg2;
        test.memRead = 0;
        test.memWrite = 0;
        test.regWrite = 0;
        test.rt = test.rs;
        hazardDetection(test);
        resolveHazard(test);
        resolveBranch(test);
      }
      
      else if(strcmp(test.opcode, "lw") == 0){
        test.rd = test.arg0;
        test.imm = test.arg1;
        test.rs = test.arg2;
        test.memWrite = 0;
        test.memRead = 1;
        test.regWrite = 1;
        test.rt = test.rd;
        hazardDetection(test);
        resolveHazard(test);
      }
      else if(strcmp(test.opcode, "sw") == 0){
        test.rt = test.arg0;
        test.imm = test.arg1;
        test.rs = test.arg2;
        test.memRead = 0;
        test.regWrite = 0;
        test.memWrite = 1;
        hazardDetection(test);
        resolveHazard(test);
      }
      
      
      else{
        printf("%s", "Invalid function\n");
        exit(0);
      }
      
      //IDEX.data = test;
      idUtil+=1;
    }
  }
}

void EX(){
  
  if(IDEX.validBit == 1){
    struct Instr test = IDEX.data;
    IDEX.validBit = 0;
    
    if (test.halt == 1) { // halt cleanup
      EXMEM.data = test;
      EXMEM.validBit = 1;
      
    } else {
    
      if(strcmp(test.opcode, "add")==0){
        test.product = mips_reg[test.rs] + mips_reg[test.rt];
        exUtil+=n;
      }
      
      else if(strcmp(test.opcode, "addi")==0){
        test.product = mips_reg[test.rs] + test.imm;
        exUtil+=n;
      }
      else if(strcmp(test.opcode, "addi\n")==0){
        test.product = mips_reg[test.rs] + test.imm;
        exUtil+=n;
      }
      else if(strcmp(test.opcode, "sub")==0){
        test.product = mips_reg[test.rs] - mips_reg[test.rt];
        exUtil+=n;
      }
      
      else if(strcmp(test.opcode, "mul")==0){
        test.product = mips_reg[test.rs] * mips_reg[test.rt];
        exUtil+=m;
      }
      
      else if(strcmp(test.opcode, "beq")==0){
        stallRAW = 0;
        if(test.imm%(long)4 != 0){
          printf("%s", "Immediate field not byte offset\n");
          exit(0);
        }
        else if(mips_reg[test.rs] == mips_reg[test.rt]){
          int j = (test.imm)/(long)4;
          PC = PC + j + 1;
          exUtil+=n;
        }
      }
      
      else if(strcmp(test.opcode, "lw")==0){
        if(test.imm%(long)4 != 0){
          printf("%s", "Immediate field not byte offset\n");
          exit(0);
        }
        else {
          test.product = mips_reg[mips_reg[test.rs]] + (test.imm/(long)4);
          exUtil+=n;
        }
      }
      else if(strcmp(test.opcode, "sw")==0){
        if(test.imm%(long)4 != 0){
          printf("%s", "Immediate field not byte offset\n");
          exit(0);
        }
        else{
          test.product = mips_reg[test.rs] + (test.imm/(long)4);
          exUtil+=n;
        }
      }
      else{
        printf("%s", "Invalid function\n");
        exit(0);
      }
      EXMEM.validBit = 1;
      EXMEM.data = test;
    }
  }
}

void MEM(){ //INPUT LATCH: EXMEM ; OUTPUT LATCH = MEMWB
  
  if(EXMEM.validBit == 1) { //valid inst test
    struct Instr temp = EXMEM.data;
    EXMEM.validBit = 0;
    
    if (temp.halt == 1) { // halt cleanup
      MEMWB.data = temp;
      MEMWB.validBit = 1;
      
    } else {
      
      assert(!(temp.memWrite && temp.memRead));
    
      if(temp.memWrite == 1) {  //sw
        assert(temp.memRead == 0);
        mem_reg[temp.product%512] = mips_reg[temp.rt];
        memUtil+=c;
      
      } else if(temp.memRead == 1) { //lw
        assert(temp.memWrite == 0);
        long holder = mem_reg[temp.product%512];
        temp.product = holder; //memory value to be used in WB.
        memUtil+=c;
      }
    
      MEMWB.data = temp; //push instr into output latch
      MEMWB.validBit = 1; //validates output latch
    }
  }
}

void WB(){ //struct Latch MEMWB
  if (MEMWB.validBit == 1) { //valid instruction
    struct Instr temp = MEMWB.data;
    MEMWB.validBit = 0; //reads in and invalidates latch
    stallRAW=0;
    evaluation[temp.rs]=0;
    evaluation[temp.rt]=0;
    if (temp.halt == 1) { // halt cleanup
      haltLatch.data = temp;
      
    } else {
      if (temp.regWrite == 1) //valid to change mips_reg
        mips_reg[temp.rd] = temp.product; //input from Mem written into destinate mips_reg
        wbUtil++;
    }
  }
}


void hazardDetection(struct Instr test){
  if(MEMWB.validBit == 1){
    struct Instr w = MEMWB.data;
    if(test.rs == w.rd) {
      evaluation[test.rs] = 1;
    }
    if (test.rt == w.rd) {
      evaluation[test.rt] = 1;
    }
    
  } else if(EXMEM.validBit == 1) {
    struct Instr q = EXMEM.data;
    if(test.rs == q.rd) {
      evaluation[test.rs] = 1;
    }
    if (test.rt == q.rd) {
      evaluation[test.rt] = 1;
    }
    
    
  }
}

void resolveHazard(struct Instr test){
   if((evaluation[test.rs] || evaluation[test.rt]) == 1){
     stallRAW = 1;
     IDEX.validBit = 0;
      }
   else{
     IDEX.validBit = 1;
     stallRAW = 0;
     IDEX.data = test;
     IFID.validBit = 0;
   }
}
void resolveBranch(struct Instr test){
  stallRAW = 1;
}