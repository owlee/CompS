#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define REG_NUM 32
long mem_reg[256];
long mips_reg[REG_NUM];
  //For REG_NUM == 32
long *$zero = &mips_reg[0], *$0 = &mips_reg[0], *$al = &mips_reg[1] , *$1  = &mips_reg[1] , *$v0 = &mips_reg[2] , *$2  = &mips_reg[2] , *$v1 = &mips_reg[3] , *$3  = &mips_reg[3] , *$a0 = &mips_reg[4] , *$4  = &mips_reg[4] , *$a1 = &mips_reg[5] , *$5  = &mips_reg[5] , *$a2 = &mips_reg[6] , *$6  = &mips_reg[6] , *$a3 = &mips_reg[7] , *$7  = &mips_reg[7] , *$t0 = &mips_reg[8] , *$8  = &mips_reg[8] , *$t1 = &mips_reg[9] , *$9  = &mips_reg[9] , *$t2 = &mips_reg[10] , *$10 = &mips_reg[10] , *$t3 = &mips_reg[11] , *$11 = &mips_reg[11] , *$t4 = &mips_reg[12] , *$12 = &mips_reg[12] , *$t5 = &mips_reg[13] , *$13 = &mips_reg[13] , *$t6 = &mips_reg[14] , *$14 = &mips_reg[14] , *$t7 = &mips_reg[15] , *$15 = &mips_reg[15] , *$s0 = &mips_reg[16] , *$16 = &mips_reg[16] , *$s1 = &mips_reg[17] , *$17 = &mips_reg[17] , *$s2 = &mips_reg[18] , *$18 = &mips_reg[18] , *$s3 = &mips_reg[19] , *$19 = &mips_reg[19] , *$s4 = &mips_reg[20] , *$20 = &mips_reg[20] , *$s5 = &mips_reg[21] , *$21 = &mips_reg[21] , *$s6 = &mips_reg[22] , *$22 = &mips_reg[22] , *$s7 = &mips_reg[23] , *$23 = &mips_reg[23] , *$t8 = &mips_reg[24] , *$24 = &mips_reg[24] , *$t9 = &mips_reg[25] , *$25 = &mips_reg[25] , *$k0 = &mips_reg[26] , *$26 = &mips_reg[26] , *$k1 = &mips_reg[27] , *$27 = &mips_reg[27] , *$gp = &mips_reg[28] , *$28 = &mips_reg[28] , *$sp = &mips_reg[29] , *$29 = &mips_reg[29] , *$fp = &mips_reg[30] , *$30 = &mips_reg[30] , *$ra = &mips_reg[31] , *$31 = &mips_reg[31];

//mips_reg[4] = 89;
struct Instr{ //Makeshift Instruction struct
  int memWrite;
  int memRead;
  int regWrite;

  long rs;
  long rt; 
  long rd; //Pointers to destination of regWrite
  long imm;
  long product; //Contains the output of ex/mem stages and inputs of the mem/wb stages
};

struct Latch {
	struct Instr inst; //Points to an Instruction struct; currently loaded in 
	int validBit; //if the Instruction is new and ready to be loaded in.
};
struct Latch MemWB;

void main() { //Test	
	//printf("hi");
	init_testMem(mem_reg);
	mips_reg[4] = 5;
	
	struct Instr testInsA;
	testInsA.regWrite = 1;
	testInsA.rd = 4;
	testInsA.product = 99;
	
	struct Instr testInsB;
	testInsB.regWrite = 0;
	testInsB.rd = 4;
	testInsB.product = 20;
	
	struct Instr testInsC;
	testInsC.regWrite = 1;
	testInsC.rd = 4;
	testInsC.product = 69;
	
	
	printf("Register File at 4 initially contains: %d\n", mips_reg[4]); // expect 5
	
	MemWB.inst = testInsA;
	MemWB.validBit = 1;
	printf("The input latch has recieved an input of: %d\n", MemWB.inst.product); //99
	WBStage(MemWB);
	printf("Register File at 4 now contains: %d\n", mips_reg[4]); // 99
	
	MemWB.inst = testInsB;
	MemWB.validBit = 1;
	printf("The input latch has recieved an input of: %d\n", MemWB.inst.product); //20
	WBStage(MemWB);
	printf("Register File at 4 now contains: %d\n", mips_reg[4]); // still 99
	
	MemWB.inst = testInsC;
	MemWB.validBit = 1;
	printf("The input latch has recieved an input of: %d\n", MemWB.inst.product); //69
	WBStage(MemWB);
	printf("Register File at 4 now contains: %d\n", mips_reg[4]); // 69
}

int WBStage(){ //struct Latch MemWB
	struct Instr temp = MemWB.inst;
	if(MemWB.validBit == 1) { //Checks if latch has valid data for processing.
		MemWB.validBit = 0;
		if(temp.regWrite == 1) //Checks if the Instruction writes back into the RegFile.
			mips_reg[temp.rd] = temp.product; //The input from the mem stage is written into the Register pointed to by writeIntoRegister pointer.	}
	}
}

//int validCheck(struct Latch validLatch){ // Checks for the status of the valid bit so the stage can take in new input.
	//assert(validLatch.validBit == 1 || validLatch.validBit == 0);
	//return validLatch.validBit; // 1 for valid; 0 for invalid.
//}

int init_testMem(long mem[]){
	int i;
	for(i = 0; i < 256; i++)
		mem[i] = i;
	return 0;
}
