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
  
	char *opcode;
	long rs;
	long rt; 
	long rd; //Pointers to destination of regWrite
	long imm;
	long product; //Contains the output of ex/mem stages and inputs of the mem/wb stages
};

struct Latch {
	struct Instr data; //Points to an Instruction struct; currently loaded in 
	int validBit; //if the Instruction is new and ready to be loaded in.
};
struct Latch EXMEM;
struct Latch MEMWB;

int main() { //Test	
	
	init_testMem(mem_reg);
	mips_reg[4] = 5;
	
	struct Instr testInsA; //lw
	testInsA.memWrite = 0;
	testInsA.memRead = 1;
	testInsA.product = 33;
	
	struct Instr testInsB; //sw
	testInsB.memWrite = 1;
	testInsB.memRead = 0;
	testInsB.product = 4;
	testInsB.rt = 4;
	
	struct Instr testInsC;
	testInsC.memWrite = 0;
	testInsC.memRead = 1;
	testInsC.product = 99;
//	struct Latch EXMEM; //input latch is valid and set to lw
	EXMEM.data = testInsA;
	EXMEM.validBit = 1;	
//	struct Latch MEMWB; //output latch set to invalid and sw
	MEMWB.data = testInsB;
	MEMWB.validBit = 0;
	
	printf("The output latch currently has the output data of: %d\n", MEMWB.data.product); // 66
	printf("The output latch valid bit is set to: %d\n\n", MEMWB.validBit); // 0
	
	printf("The input latch has recieved an input of: %d\n", EXMEM.data.product); // 33
	printf("The input latch valid bit is set to: %d\n", EXMEM.validBit); // 1
	MemStage();
	printf("The output latch currently has the output: %d\n", MEMWB.data.product); //33
	printf("The output latch valid bit is set to: %d\n\n", MEMWB.validBit); //1
	
	EXMEM.data = testInsC;
	EXMEM.validBit = 1;
	printf("The Execution Stage has recieved an input address of: %d\n", EXMEM.data.product); // 99
	printf("The input latch valid bit is set to: %d\n", EXMEM.validBit); // 1
	MemStage();
	printf("The output latch product : %d\n", MEMWB.data.product); //99
	printf("The output latch valid bit is set to: %d\n\n", MEMWB.validBit); //1
	
	EXMEM.data = testInsB;
	EXMEM.validBit = 1;
	printf("%d\n", mem_reg[EXMEM.data.product%512]);
	printf("The Execution Stage has recieved an input address of: %d\n", EXMEM.data.product); // 4
	printf("The input latch valid bit is set to: %d\n", EXMEM.validBit); // 1
	printf("Memory to be accessed contains: %d", mem_reg[EXMEM.data.product%512]); //4
	MemStage();
	printf("The output latch product : %d\n", MEMWB.data.product); //4
	printf("The output latch valid bit is set to: %d\n\n", MEMWB.validBit); //1
	printf("Memory now contains: %d", mem_reg[EXMEM.data.product%512]); //16
//	EXMEM.data = testInsD;
//	EXMEM.validBit = 1;
//	printf("The Execution Stage has recieved an input address of: %d\n", EXMEM.data.product); // 150
//	printf("The input latch valid bit is set to: %d\n", EXMEM.validBit); // 1
//	MemStage();
//	printf("The output latch product: %d\n", MEMWB.data.product); //150
//	printf("The output latch valid bit is set to: %d\n\n", MEMWB.validBit); //1
	
//	EXMEM.data = testInsB;
//	EXMEM.validBit = 1;
//	printf("The Execution Stage has recieved an input address of: %d\n", EXMEM.data.product); // 20
//	printf("The input latch valid bit is set to: %d\n", EXMEM.validBit); // 1
//	printf("The mem reg to be accessed contains: %d\n", mem_reg[EXMEM.data.product]); //20
//	MemStage();
//	printf("The output product is: %d\n", MEMWB.data.product); //150
//	printf("The output latch valid bit is set to: %d\n", MEMWB.validBit); //1
//	printf("The accessed memory now contains: %d\n", mem_reg[EXMEM.data.product]); //50
	
	return 0;
};

int MemStage(){ //INPUT LATCH: EXMEM ; OUTPUT LATCH = MEMWB
	long holder;
	struct Instr temp = EXMEM.data;
	if(EXMEM.validBit == 1) //valid inst test
		EXMEM.validBit = 0; //has been read and invalidated.
		if(temp.memWrite == 1){  //sw
			assert(temp.memRead == 0);
			mem_reg[(temp.product%512)] = mips_reg[temp.rt];
		}	
		else if(temp.memRead == 1){   //lw
			assert(temp.memWrite == 0);
			holder = mem_reg[(temp.product%512)];
			temp.product = holder; //memory value to be used in WB.
		}
		MEMWB.data.product = temp.product; //push instr into output latch
		MEMWB.validBit = 1; //validates output latch
}

int init_testMem(long mem[]){
	int i;
	for(i = 0; i < 256; i++)
		mem[i] = i;
	//printf("%d", mem_reg[4]);
	return 0;
}