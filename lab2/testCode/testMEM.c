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

  long rs;
  long rt; //Pointers to register values 
  long rd; //Pointers to destination of regWrite
  long imm;
  long product; //Contains the output of ex/mem stages and inputs of the mem/wb stages
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
	
	struct Instr testInsA;
	strcpy(testInsA.func, "lw");
	testInsA.memRead = 1;
	testInsA.memWrite = 0;
	testInsA.product = 99;
	
	struct Instr testInsB;
	strcpy(testInsB.func, "sw");
	testInsB.memRead = 0;
	testInsB.memWrite = 1;
	testInsB.product = 20;
	testInsB.rt = 55;
	
	struct Instr testInsC;
	strcpy(testInsA.func, "lw2");
	testInsC.memRead = 1;
	testInsC.memWrite = 0;
	testInsC.product = 101;
	
	struct Instr testInsD;
	strcpy(testInsA.func, "lw3");
	testInsD.memRead = 1;
	testInsD.memWrite = 0;
	testInsD.product = 150;
	
//	struct Latch ExMem; //input latch is valid and set to lw
	ExMem.inst = testInsA;
	ExMem.validBit = 1;	
//	struct Latch MemWB; //output latch set to invalid and sw
	MemWB.inst = testInsB;
	MemWB.validBit = 0;
	
	printf("The output latch currently has the output product of: %d\n", MemWB.inst.product); // 20
	printf("The output latch valid bit is set to: %d\n\n", MemWB.validBit); // 0
	
	printf("The input latch has recieved an input of: %d\n", ExMem.inst.product); // 99
	printf("The input latch valid bit is set to: %d\n", ExMem.validBit); // 1
	MemStage();
	printf("The output latch currently has the output: %d\n", MemWB.inst.product); //99
	printf("The output latch valid bit is set to: %d\n\n", MemWB.validBit); //1
	
	ExMem.inst = testInsC;
	ExMem.validBit = 1;
	printf("The Execution Stage has recieved an input address of: %d\n", ExMem.inst.product); // 101
	printf("The input latch valid bit is set to: %d\n", ExMem.validBit); // 1
	MemStage();
	printf("The output latch product : %d\n", MemWB.inst.product); //101
	printf("The output latch valid bit is set to: %d\n\n", MemWB.validBit); //1
	
	ExMem.inst = testInsD;
	ExMem.validBit = 1;
	printf("The Execution Stage has recieved an input address of: %d\n", ExMem.inst.product); // 150
	printf("The input latch valid bit is set to: %d\n", ExMem.validBit); // 1
	MemStage();
	printf("The output latch product: %d\n", MemWB.inst.product); //150
	printf("The output latch valid bit is set to: %d\n\n", MemWB.validBit); //1
	
	ExMem.inst = testInsB;
	ExMem.validBit = 1;
	printf("The Execution Stage has recieved an input address of: %d\n", ExMem.inst.product); // 20
	printf("The input latch valid bit is set to: %d\n", ExMem.validBit); // 1
	printf("The mem reg to be accessed contains: %d\n", mem_reg[ExMem.inst.product]); //20
	MemStage();
	printf("The output product is: %d\n", MemWB.inst.product); //150
	printf("The output latch valid bit is set to: %d\n", MemWB.validBit); //1
	printf("The accessed memory now contains: %d\n", mem_reg[ExMem.inst.product]); //50
	
	return 0;
};

int MemStage(){ //INPUT LATCH: ExMem ; OUTPUT LATCH = MemWB
	struct Instr temp = ExMem.inst;
	if(ExMem.validBit == 1) //Checks if latch has valid data for processing. Ends function/stage when it fails.
		ExMem.validBit = 0; //Reads in valid Instruction and then invalidates it.
		assert(!(temp.memWrite && temp.memRead));
		if(temp.memWrite == 1)  //sw
			mem_reg[temp.product] = (uintptr_t)temp.rt;
		if(temp.memRead == 1)
			temp.product = mem_reg[temp.product]; //Stores value of memory of input addr into
		MemWB.inst.product = temp.product; //instruction into output latch
		MemWB.validBit = 1; //Validates the Instruction so that the next stage is able to read in.
	}


int init_testMem(long mem[]){
	int i;
	for(i = 0; i < 256; i++)
		mem[i] = i;
	return 0;
}