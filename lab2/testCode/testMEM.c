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

struct Instr{ //Makeshift Instruction struct
  int memWrite;
  int memRead;
  int regWrite;

  int *rs, *rt; //Pointers to register values 
  int *rd; //Pointers to destination of regWrite
  int imm;
  int product; //Contains the output of ex/mem stages and inputs of the mem/wb stages
  char func[];
};

struct Latch {
	struct Instr inst; //Points to an Instruction struct; currently loaded in 
	int validBit; //Tells if the Instruction is new and ready to be loaded in.
};
struct Latch ExMem;
struct Latch MemWB;

int main(void) { //Test	
	init_testMem(mem_reg);
	
	struct Instr testIns;
	strcpy(testIns.func, "lw");
	testIns.memRead = 1;
	testIns.memWrite = 0;
	testIns.product = 99;
	
	struct Instr testIns22;
	strcpy(testIns22.func, "sw");
	testIns.memRead = 0;
	testIns.memWrite = 1;
	testIns.product = 20;
	
//	struct Latch ExMem; //input latch is valid and set to lw
	validBit(ExMem);
	ExMem.inst = testIns;
	
//	struct Latch MemWB; //output latch set to invalid and sw
	MemWB.inst = testIns22;
	
	printf("The output latch currently has the Instruction of: %s", MemWB.inst.func); // sw
	printf("The output latch currently has the output product of: %f", MemWB.inst.product); // 20
	
	printf("The input latch has an Instruction of: %s", ExMem.inst.func); // lw
	printf("The input latch has recieved an input of: %f", ExMem.inst.product); // 99
	MemStage();
	printf("The output latch currently has the instruction: %s", MemWB.inst.func); // lw 
	printf("The output latch currently has the output: %f", MemWB.inst.product); //99
	
	ExMem.inst = testIns22;
	printf("The Execution Stage has an input Instruction of: %s", ExMem.inst.func); // sw
	printf("The Execution Stage has recieved an input address of: %f", ExMem.inst.product); // 20
	printf("The memory to be accessed currently contains: %f", mem_reg[ExMem.inst.product]); // 20
	MemStage();
	printf("The output instruction is: %s", MemWB.inst.func); //sw
	printf("The E: %f", MemWB.inst.product); //20
	printf("The accessed memory now contains: %f", mem_reg[ExMem.inst.product]); //20s
	
	return 0;
};

int MemStage(){ //INPUT LATCH: ExMem ; OUTPUT LATCH = MemWB
	if(validCheck(ExMem) == 1) //Checks if latch has valid data for processing. Ends function/stage when it fails.
		invalidateBit(ExMem); //Reads in valid Instruction and then invalidates it.
		if(ExMem.inst.memWrite == 1)  //sw
			mem_reg[ExMem.inst.product] = (uintptr_t)ExMem.inst.rt;
		if(ExMem.inst.memRead == 1)
			ExMem.inst.product = mem_reg[ExMem.inst.product]; //Stores value of memory of input addr into
		MemWB.inst.product = ExMem.inst.product; //instruction into output latch
		validateBit(MemWB); //Validates the Instruction so that the next stage is able to read in.
	return 0;
	}

int validCheck( struct Latch validLatch){ // Checks for the status of the valid bit so the stage can take in new input.
	//assert(validLatch.validBit == 1 || validLatch.validBit == 0);
	return validLatch.validBit; // 1 for valid; 0 for invalid.
}

int invalidateBit(struct Latch zeroThis){
	//assert(zeroThis.validBit == 1 || zeroThis.validBit == 0);
	zeroThis.validBit = 0;
	return 0;
}

int validateBit(struct Latch oneThis){
	//assert(oneThis.validBit == 1 || oneThis.validBit == 0);
	oneThis.validBit = 1;
	return 1;
}

int init_testMem(long mem[]){
	int i;
	for(i = 0; i < 256; i++)
		mem[i] = i;
	return 0;
}