#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

#define REG_NUM 32
long mem_reg[256];

long mips_reg[REG_NUM];
  //For REG_NUM == 32
  long *$zero = &mips_reg[0], *$0 = &mips_reg[0], *$al = &mips_reg[1] , *$1  = &mips_reg[1] , *$v0 = &mips_reg[2] , *$2  = &mips_reg[2] , *$v1 = &mips_reg[3] , *$3  = &mips_reg[3] , *$a0 = &mips_reg[4] , *$4  = &mips_reg[4] , *$a1 = &mips_reg[5] , *$5  = &mips_reg[5] , *$a2 = &mips_reg[6] , *$6  = &mips_reg[6] , *$a3 = &mips_reg[7] , *$7  = &mips_reg[7] , *$t0 = &mips_reg[8] , *$8  = &mips_reg[8] , *$t1 = &mips_reg[9] , *$9  = &mips_reg[9] , *$t2 = &mips_reg[10] , *$10 = &mips_reg[10] , *$t3 = &mips_reg[11] , *$11 = &mips_reg[11] , *$t4 = &mips_reg[12] , *$12 = &mips_reg[12] , *$t5 = &mips_reg[13] , *$13 = &mips_reg[13] , *$t6 = &mips_reg[14] , *$14 = &mips_reg[14] , *$t7 = &mips_reg[15] , *$15 = &mips_reg[15] , *$s0 = &mips_reg[16] , *$16 = &mips_reg[16] , *$s1 = &mips_reg[17] , *$17 = &mips_reg[17] , *$s2 = &mips_reg[18] , *$18 = &mips_reg[18] , *$s3 = &mips_reg[19] , *$19 = &mips_reg[19] , *$s4 = &mips_reg[20] , *$20 = &mips_reg[20] , *$s5 = &mips_reg[21] , *$21 = &mips_reg[21] , *$s6 = &mips_reg[22] , *$22 = &mips_reg[22] , *$s7 = &mips_reg[23] , *$23 = &mips_reg[23] , *$t8 = &mips_reg[24] , *$24 = &mips_reg[24] , *$t9 = &mips_reg[25] , *$25 = &mips_reg[25] , *$k0 = &mips_reg[26] , *$26 = &mips_reg[26] , *$k1 = &mips_reg[27] , *$27 = &mips_reg[27] , *$gp = &mips_reg[28] , *$28 = &mips_reg[28] , *$sp = &mips_reg[29] , *$29 = &mips_reg[29] , *$fp = &mips_reg[30] , *$30 = &mips_reg[30] , *$ra = &mips_reg[31] , *$31 = &mips_reg[31];

struct Instr{ //Makeshift Instruction struct
  int memWrite;
  int memRead;
  int regWrite;

  long *rs, *rt; //Pointers to register values 
  long *rd; //Pointers to destination of regWrite
  long imm;
  long product; //Contains the output of ex/mem stages and inputs of the mem/wb stages
  char func[];
};

struct Latch {
	struct Instr inst; //Points to an Instruction struct; currently loaded in 
	int validBit; //Tells if the Instruction is new and ready to be loaded in.
};

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
	
	struct Latch exMem; //input latch is valid and set to lw
	validBit(exMem);
	exMem.inst = testIns;
	
	struct Latch memWB; //output latch set to invalid and sw
	memWB.inst = testIns22;
	
	printf("The output latch currently has the Instruction of: %s", memWB.inst.func); // sw
	printf("The output latch currently has the output product of: %f", memWB.inst.product); // 20
	
	printf("The input latch has an Instruction of: %s", exMem.inst.func); // lw
	printf("The input latch has recieved an input of: %f", exMem.inst.product); // 99
	MemStage(exMem, memWB);
	printf("The output latch currently has the instruction: %s", memWB.inst.func); // lw 
	printf("The output latch currently has the output: %f", memWB.inst.product); //99
	
	exMem.inst = testIns22;
	printf("The Execution Stage has an input Instruction of: %s", exMem.inst.func); // sw
	printf("The Execution Stage has recieved an input address of: %f", exMem.inst.product); // 20
	printf("The memory to be accessed currently contains: %f", mem_reg[exMem.inst.product]); // 20
	MemStage(exMem, memWB);
	printf("The output instruction is: %s", memWB.inst.func); //sw
	printf("The E: %f", memWB.inst.product); //20
	printf("The accessed memory now contains: %f", mem_reg[exMem.inst.product]); //20s
	
	return 0;
};

void MemStage(struct Latch ExMem, struct Latch MemWB){ //input latch and output latch
	struct Instr temp = ExMem.inst;
	if(validCheck(ExMem) == 1) //Checks if latch has valid data for processing. Ends function/stage when it fails.
		invalidateBit(ExMem); //Reads in valid Instruction and then invalidates it.
		if(temp.memWrite == 1) 
			mem_reg[temp.product] = temp.rt;
		else if(temp.memRead == 1)
			temp.product = mem_reg[temp.product]; //Stores value of memory of input addr into
		MemWB.inst = temp; //Pushes input Instruction into the output latch.
		validateBit(MemWB); //Validates the Instruction so that the next stage is able to read in.
		}


void WBStage(struct Latch MemWB){
	struct Instr temp = MemWB.inst; //Stores the current Instruction stored in input latch
	if(validCheck(MemWB) == 1) { //Checks if latch has valid data for processing.
		invalidateBit(MemWB);
		if(temp.regWrite == 1) //Checks if the Instruction writes back into the RegFile.
			temp.rd = temp.product; //The input from the mem stage is written into the Register pointed to by writeIntoRegister pointer.
	}
}

int validCheck( struct Latch validLatch){ // Checks for the status of the valid bit so the stage can take in new input.
	assert(validLatch.validBit == 1 || validLatch.validBit == 0);
	return validLatch.validBit; // 1 for valid; 0 for invalid.
}

int invalidateBit(struct Latch zeroThis){
	assert(zeroThis.validBit == 1 || zeroThis.validBit == 0);
	zeroThis.validBit = 0;
	return 0;
}

int validateBit(struct Latch oneThis){
	assert(oneThis.validBit == 1 || oneThis.validBit == 0);
	oneThis.validBit = 1;
	return 1;
}

int init_testMem(long mem[]){
	int i;
	for(i = 0; i < 256; i++)
		mem[i] = i;
	return 0;
}