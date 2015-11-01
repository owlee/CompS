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

int PC = 0;

enum opcode_type{add,sub,mul,addi,beq,lw,sw};
const char* opcode_str[] = {"add","sub","mul","addi","beq","lw","sw"};
//opcode_type op[7]; //used for printing
//op[0] = add;
//op[1] = sub;
//op[2] = mul;
//op[3] = addi;
//op[4] = beq;
//op[5] = lw;
//op[6] = sw;

struct Instr{ //Makeshift Instruction struct
	int memWrite;
	int memRead;
	int regWrite;
  
	enum opcode_type opcode;
	long rs;
	long rt; 
	long rd; 
	long imm;
	long product; //Contains the output of ex/mem stages and inputs of the mem/wb stages
};

struct Latch {
	struct Instr inst; //Points to an Instruction struct; currently loaded in 
	int validBit; //Tells if the Instruction is new and ready to be loaded in.
};
struct Latch IDEX;
struct Latch EXMEM;

int main(void) { //Test	
	init_testMem(mem_reg);
	
	struct Instr testInsA;
	testInsA.opcode = add;
	testInsA.rs = 3;
	testInsA.rt = 6;
	testInsA.imm = 1000;
	//printf("testInsA.opcode");
	struct Instr testInsB;
	testInsB.opcode = add;
	testInsB.rs = 20;
	testInsB.rt = 200;
	testInsB.imm = 2000;
	
	struct Instr testInsC;
	testInsC.opcode = add;
	testInsC.rs = 3;
	testInsC.rt = 300;
	testInsC.imm = 3000;
	
	struct Instr testInsD;
	testInsD.opcode = add;
	testInsD.rs = 40;
	testInsD.rt = 400;
	testInsD.imm = 4000;
	
	EXMEM.inst = testInsD;
	EXMEM.validBit = 0;
	IDEX.inst = testInsA;
	IDEX.validBit = 1;
	
	printf("The output latch currently has the opcode of: %s\n", opcode_str[EXMEM.inst.opcode]); // add
	printf("The output latch valid bit is set to: %d\n\n", EXMEM.validBit); // 0
	
	printf("The inputt latch currently has the opcode of: %s\n", opcode_str[IDEX.inst.opcode]); // add
	printf("The input latch has recieved an input of: %d, %d\n", IDEX.inst.rs, IDEX.inst.rt); // 10, 100
	printf("The input latch valid bit is set to: %d\n\n", IDEX.validBit); // 1
	ExStage();
	printf("The output latch currently has the output: %d\n", EXMEM.inst.product); //110
	printf("The output latch valid bit is set to: %d\n\n", EXMEM.validBit); //1
	
	
	IDEX.inst = testInsB;
	IDEX.validBit = 1;
	printf("The input latch currently has the opcode of: %s\n", opcode_str[IDEX.inst.opcode]); // add
	printf("The input latch has recieved an input of: %d, %d\n", IDEX.inst.rs, IDEX.inst.rt); // 20, 200
	printf("The input latch valid bit is set to: %d\n\n", IDEX.validBit); // 1
	ExStage();
	printf("The output latch currently has the output: %d\n", EXMEM.inst.product); //220
	printf("The output latch valid bit is set to: %d\n\n", EXMEM.validBit); //1
}

int ExStage(){
	struct Instr temp = IDEX.inst;
	if(IDEX.validBit == 1){
		IDEX.validBit = 0;
		if(temp.opcode == add)
			temp.product = mips_reg[temp.rs] + mips_reg[temp.rt];
		else if(temp.opcode == addi)
			temp.product = mips_reg[temp.rs] + temp.imm;
		else if(temp.opcode == sub)
			temp.product = mips_reg[temp.rs] - mips_reg[temp.rt];
		else if(temp.opcode == mul)
			temp.product = mips_reg[temp.rs] * mips_reg[temp.rt];
		else if(temp.opcode == beq){
			if(mips_reg[temp.rs] == mips_reg[temp.rt]){
				int j = (temp.imm)/4;
				PC = PC + j;
			}
		}
		else if(temp.opcode = lw)
			temp.product = mips_reg[temp.rs] + temp.imm;
		else if(temp.opcode = sw)
			temp.product = mips_reg[temp.rs] + temp.imm;
		else
			printf("no valid instructions were executed");
		EXMEM.inst.product = temp.product; //instruction into output latch
		EXMEM.validBit = 1; //Validates the Instruction so that the next stage is able to read in.
	}
}
	
int init_testMem(long mem[]){
	int i;
	for(i = 0; i < 256; i++)
		mem[i] = i;
	return 0;
}
