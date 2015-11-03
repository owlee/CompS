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
long PC;
static int evaluation[32];
void resolveBranch();
void resolveHazard();
void hazardDetection();
// Structures
struct Instr {
  int memWrite;
  int memRead;
  int regWrite;
  
  // Holder Values to organize
  int arg0, arg1, arg2;
  
  // Acutal Destinations of Instruction
  char *opcode;
  int rs, rt, rd, imm;
  long product;
  int index;
};

struct Latch {
  int validBit;
  struct Instr *data; //instruction currently held
};

// GLOBAL VARIABLES
struct Instr instr_mem[512];  // 512 word size
struct Latch IFID, IDEX, EXMEM, MEMWB;
char buffer[40];
long mips_reg[REG_NUM];
double ifUtil=0, idUtil=0, exUtil=0, memUtil=0, wbUtil=0;
int stallRAW;

// GLOBAL FUNCTIONS
void IF();
void ID();
void EX();
int countLine(char *);
struct Instr progScanner(char *);
int regConverter(char*);

void ID(){
 
 if(IFID.validBit == 1){
	struct Instr test = *(IFID.data);
		
	if(test.imm > 65535){
			printf("%s", "Immediate field is out of range");
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
		printf("%s", "Invalid function");
		exit(0);
	}

	
	
}
}


void EX(){	
	IFID.data = &instr_mem[PC];
	struct Instr test;
	if(IDEX.validBit == 1){
		test = *(IDEX.data);
	
		if(strcmp(test.opcode, "add")==0){
		test.product = mips_reg[test.rs] + mips_reg[test.rt];
		}
	
	   else if(strcmp(test.opcode, "addi")==0){
		test.product = mips_reg[test.rs] + test.imm;
	   }
	
    else if(strcmp(test.opcode, "sub")==0){	  
	  test.product = mips_reg[test.rs] - mips_reg[test.rt];
	}
		
	else if(strcmp(test.opcode, "mul")==0){
		test.product = mips_reg[test.rs] * mips_reg[test.rt];
	}
		
    else if(strcmp(test.opcode, "beq")==0){	
		stallRAW = 0;
		if(test.imm%(long)4 != 0){
			printf("%s", "Immediate field not byte offset");
			exit(0);
	   }
	   	else if(mips_reg[test.rs] == mips_reg[test.rt]){
		int j = (test.imm)/(long)4;
		PC = PC + 1 + j;
		}	
		
		
	}
		
	
	else if(strcmp(test.opcode, "lw")==0){
		if(test.imm%(long)4 != 0){
			printf("%s", "Immediate field not byte offset");
			exit(0);
	   }
		else {
			test.product = mips_reg[mips_reg[test.rs]] + (test.imm/(long)4);		
	}
	}	
   else if(strcmp(test.opcode, "sw")==0){
	   if(test.imm%(long)4 != 0){
			printf("%s", "Immediate field not byte offset");
			exit(0);
	   }
		else{
			test.product = mips_reg[test.rs] + (test.imm/(long)4);
   }
   }
	else{
	printf("%s", "Invalid function");
	exit(0);
	}
	
	
	IDEX.validBit = 0;
	EXMEM.validBit = 1;
	EXMEM.data = &instr_mem[PC];
	}
}	






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
  int c,m,n;
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
  
  //initialize registers and program counter
  if (sim_mode == 1) {
    for (i=0;i<REG_NUM;i++){
      mips_reg[i]=0;
    }
  }
  
  char *textInst = (char*) malloc(30);
  strcpy(textInst, "./textInstructions.txt");
  FILE *fp = fopen(textInst, "r");
  
  assert(fp!=NULL);
  
  // OUR CODE
  if (sim_mode == 0) {  // batch cycle
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
    
    // ----- Code 2 -----
    // The following code will output the register
    // value to screen at every cycle and wait for the ENTER key
    // to be pressed; this will make it proceed to the next cycle
    
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
  
  // Clean up
  fclose(input);
  fclose(output);
  return 0;
}
void hazardDetection(struct Instr test){	
	if(MEMWB.validBit == 1 || EXMEM.validBit == 1){
	struct Instr q = *(EXMEM.data);	
	struct Instr w = *(MEMWB.data);
	if(test.rs == (q.rd || w.rd)){	evaluation[test.rs] = 1; }
	if (test.rt == (q.rd || w.rd)) {evaluation[test.rt] = 1; }
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
		IDEX.data = &instr_mem[PC];
		IFID.validBit = 0;
		}
		}
void resolveBranch(struct Instr test){
	stallRAW = 1;
	}