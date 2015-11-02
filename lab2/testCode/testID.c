#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define REG_NUM 32
long mem_reg[256];
long mips_reg[REG_NUM];
  //For REG_NUM == 32
long *$zero = &mips_reg[0], *$0 = &mips_reg[0], *$al = &mips_reg[1] , *$1  = &mips_reg[1] , *$v0 = &mips_reg[2] , *$2  = &mips_reg[2] , *$v1 = &mips_reg[3] , *$3  = &mips_reg[3] , *$a0 = &mips_reg[4] , *$4  = &mips_reg[4] , *$a1 = &mips_reg[5] , *$5  = &mips_reg[5] , *$a2 = &mips_reg[6] , *$6  = &mips_reg[6] , *$a3 = &mips_reg[7] , *$7  = &mips_reg[7] , *$t0 = &mips_reg[8] , *$8  = &mips_reg[8] , *$t1 = &mips_reg[9] , *$9  = &mips_reg[9] , *$t2 = &mips_reg[10] , *$10 = &mips_reg[10] , *$t3 = &mips_reg[11] , *$11 = &mips_reg[11] , *$t4 = &mips_reg[12] , *$12 = &mips_reg[12] , *$t5 = &mips_reg[13] , *$13 = &mips_reg[13] , *$t6 = &mips_reg[14] , *$14 = &mips_reg[14] , *$t7 = &mips_reg[15] , *$15 = &mips_reg[15] , *$s0 = &mips_reg[16] , *$16 = &mips_reg[16] , *$s1 = &mips_reg[17] , *$17 = &mips_reg[17] , *$s2 = &mips_reg[18] , *$18 = &mips_reg[18] , *$s3 = &mips_reg[19] , *$19 = &mips_reg[19] , *$s4 = &mips_reg[20] , *$20 = &mips_reg[20] , *$s5 = &mips_reg[21] , *$21 = &mips_reg[21] , *$s6 = &mips_reg[22] , *$22 = &mips_reg[22] , *$s7 = &mips_reg[23] , *$23 = &mips_reg[23] , *$t8 = &mips_reg[24] , *$24 = &mips_reg[24] , *$t9 = &mips_reg[25] , *$25 = &mips_reg[25] , *$k0 = &mips_reg[26] , *$26 = &mips_reg[26] , *$k1 = &mips_reg[27] , *$27 = &mips_reg[27] , *$gp = &mips_reg[28] , *$28 = &mips_reg[28] , *$sp = &mips_reg[29] , *$29 = &mips_reg[29] , *$fp = &mips_reg[30] , *$30 = &mips_reg[30] , *$ra = &mips_reg[31] , *$31 = &mips_reg[31];

int PC = 0;

struct Instr {
  int memWrite;
  int memRead;
  int regWrite;
  
  // Holder Values to organize
  int arg0, arg1, arg2;
  
  // Acutal Destinations of Instruction
  char *opcode;
  int rs, rt, rd, imm;
  long data;
};

struct Latch {
	struct Instr data; //Points to an Instruction struct; currently loaded in 
	int validBit; //Tells if the Instruction is new and ready to be loaded in.
};
struct Latch IFID;
struct Latch IDEX;

int main(void) { //Test	
	
	struct Instr testInsA;
	testInsA.opcode = "add";
	//strcpy(testInsA.opcode, "add");
	testInsA.arg0 = 1;
	testInsA.arg1 = 2;
	testInsA.arg2 = 3;

	struct Instr testInsB;
	testInsB.opcode = "addi";
	//strcpy(testInsB.opcode, "addi");
	testInsB.arg0 = 4;
	testInsB.arg1 = 5;
	testInsB.arg2 = 6;
	
	struct Instr testInsC;
	testInsC.opcode = "sub";
	//strcpy(testInsC.opcode, "sub");
	testInsC.arg0 = 7;
	testInsC.arg1 = 8;
	testInsC.arg2 = 9;
	
	struct Instr testInsD;
	testInsD.opcode = "mul";
	//strcpy(testInsD.opcode, "mul");
	testInsD.arg0 = 10;
	testInsD.arg1 = 11;
	testInsD.arg2 = 12;
	
	IFID.data = testInsA;
	IFID.validBit = 1;
	printf("%d\n", IFID.data.arg2);
	ID();
	printf("rs:%d , rt:%d , rd:%d, memRead:%d , memWrite:%d, regWrite:%d\n", IDEX.data.rs, IDEX.data.rt, IDEX.data.rd, IDEX.data.memRead, IDEX.data.memWrite, IDEX.data.regWrite);

	IFID.data = testInsB;
	IFID.validBit = 1;
	ID();
	printf("rs:%d , rt:%d , rd:%d, memRead:%d , memWrite:%d, regWrite:%d\n", IDEX.data.rs, IDEX.data.rt, IDEX.data.rd, IDEX.data.memRead, IDEX.data.memWrite, IDEX.data.regWrite);

	IFID.data = testInsC;
	IFID.validBit = 1;
	ID();
	printf("rs:%d , rt:%d , rd:%d, memRead:%d , memWrite:%d, regWrite:%d\n", IDEX.data.rs, IDEX.data.rt, IDEX.data.rd, IDEX.data.memRead, IDEX.data.memWrite, IDEX.data.regWrite);

	IFID.data = testInsD;
	IFID.validBit = 1;
	ID();
	printf("rs:%d , rt:%d , rd:%d, memRead:%d , memWrite:%d, regWrite:%d\n", IDEX.data.rs, IDEX.data.rt, IDEX.data.rd, IDEX.data.memRead, IDEX.data.memWrite, IDEX.data.regWrite);
}

int ID(){
	struct Instr temp = IFID.data;
	if(IFID.validBit == 1){
		IFID.validBit = 0;	
		if(temp.imm > 65535){
			//printf("%s", "Immediate field is out of range");
			exit(0);
		}
		else{
			if(strcmp(temp.opcode, "add") == 0){	
				temp.rd = temp.arg0;
				temp.rs = temp.arg1;
				temp.rt = temp.arg2;
				temp.memRead = 0;
				temp.memWrite = 0;
				temp.regWrite = 1;
			}
			else if(strcmp(temp.opcode, "addi") == 0){			
				temp.rt = temp.arg0;
				temp.rs = temp.arg1;
				temp.imm = temp.arg2;
				temp.memRead = 0;
				temp.memWrite = 0;
				temp.regWrite = 1;
			}
			else if(strcmp(temp.opcode, "sub") == 0){
				temp.rd = temp.arg0;
				temp.rs = temp.arg1;
				temp.rt = temp.arg2;
				temp.memRead = 0;
				temp.memWrite = 0;
				temp.regWrite = 1;
			}
			else if(strcmp(temp.opcode, "mul") == 0){
				temp.rd = temp.arg0;
				temp.rs = temp.arg1;
				temp.rt = temp.arg2;
				temp.memRead = 0;
				temp.memWrite = 0;
				temp.regWrite = 1;
			}
			else if(strcmp(temp.opcode, "beq") == 0){
				temp.rs = temp.arg0;
				temp.rt = temp.arg1;
				temp.imm = temp.arg2;
				temp.memRead = 0;
				temp.memWrite = 0;
				temp.regWrite = 0;
			}
			else if(strcmp(temp.opcode, "lw") == 0){     
				temp.rt = temp.arg0;
				temp.imm = temp.arg1;
				temp.rs = temp.arg2;
				temp.memWrite = 0;
				temp.memRead = 1;
				temp.regWrite = 1;
			}
			else if(strcmp(temp.opcode, "sw") == 0){
				temp.rt = temp.arg0;
				temp.imm = temp.arg1;
				temp.rs = temp.arg2;
				temp.memRead = 0;
				temp.regWrite = 0;
				temp.memWrite = 1;
			}
			//else{
				//printf("%s", "Invalid function");
				//exit(0);
		}
	
		IFID.validBit = 0;
		IDEX.validBit = 1;
		IDEX.data = temp;
	}
}