#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

long mips_reg[32];
long Mem_Reg[256];

struct Instr{ //Makeshift Instruction struct
	char[] function;
	long rsValue; //value of register when Instruction passes through IF stage
	long rtValue;
	long imm;
	long *regT; //register to be written back to  for I-type Instructions
	long *regD; //register to be written back to for R-type
	long product; //Holds the inputs to be used in next stage, takes in the output of that stage when it has completed.

	int ALUSrc; //controls
	int MemWrite;
	int MemRead;
	int RegWrite;
}
struct Instr addi = {"addi", 5, 6, 45, $t3, $t5, 100, 0, 0, 0, 1};
struct Instr sub = {"sub", 5, 5, 88, $t3, $t3, 200, 1, 0, 0, 1};
struct Instr sw = {"sw", 10, 10, 55, $t4, $t5, 300, 0, 1, 0, 0};

struct Latch {
	struct Instr Instruction; //Points to an Instruction struct; currently loaded in 
	int validBit; //Tells if the Instruction is new and ready to be loaded in.
}
struct Latch ExecutionMemory = {1, addi};
struct Latch MemoryWriteBack = {0, sub};


int main(void) { //Test	
	init_reg();
	init_testMem();

	printf("The output latch currently has the Instruction of: %s", MemoryWriteBack.Instruction.function);
	printf("The output latch currently has the output product of: %f", MemoryWriteBack.Instruction.product);
	
	printf("The Execution Stage has an input Instruction of: %s", ExecutionMemory.Instruction.function);
	printf("The Execution Stage has recieved an input of: %f", ExecutionMemory.Instruction.product);
	MemStage(ExecutionMemory);
	printf("The Execution Stage has pushed into the next latch the output Instruction of: %s", MemoryWriteBack.Instruction.function);
	printf("The Execution Stage has pushed into the next latch the output product of: %f", MemoryWriteBack.Instruction.product);
	
	ExecutionMemory = {1, sw};
	printf("The Execution Stage has an input Instruction of: %s", ExecutionMemory.Instruction.function);
	printf("The Execution Stage has recieved an input of: %f", ExecutionMemory.Instruction.product);
	printf("The memory to be accessed currently contains: %f", MemReg[ExecutionMemory.Instruction.product]);
	MemStage(ExecutionMemory);
	printf("The Execution Stage has pushed into the next latch the output Instruction of: %s", MemoryWriteBack.Instruction.function);
	printf("The Execution Stage has pushed into the next latch the output product of: %f", MemoryWriteBack.Instruction.product);
	printf("The accessed memory now contains: %f", MemReg[ExecutionMemory.Instruction.product]);
	
	return 0;
};

void MemStage(struct Latch ExMem){
	Instr currInstr = ExMem.Instruction; //holds the current Instruction stored in input latch
	if(validCheck(ExMem) == 0){ //Checks if latch has valid data for processing. Ends function/stage when it fails.
		break;
	}
	else{
		invalidateBit(ExMem); //Reads in valid Instruction and then invalidates it.
		switch(currInstr.function){
			case "sw": //sw case
				if(currInstr.memWrite == 1) 
					Mem_Reg[product] = currInstr.rt;
			break;
			case "lw": //lw case
				if(currInstr.memRead == 1)
					currInstr.product = Mem_Reg[product]; //Stores value of memory of input addr into
				break;
			default:
				break;
		}
		MemWB.*Instruction = currInstr; //Pushes input Instruction into the output latch.
		validateBit(MemWB); //Validates the Instruction so that the next stage is able to read in.
	}
}

//void WBStage(struct Latch MemWB){
//	Instr currInstr = MemWB.Instruction; //Stores the current Instruction stored in input latch
	//if(validCheck(MemWB) == 1) { //Checks if latch has valid data for processing.
		//invalidateBit(MemWB);
		//if((currInstr.function == "add") || (currInstr.function == "sub") || (currInstr.function == "mul")){
			//if(currInstr.RegWrite == 1) //Checks if the Instruction writes back into the RegFile.
				//currInstr.RegD = currInstr.product; //The input from the mem stage is written into the Register pointed to by writeIntoRegister pointer.
		//}
		//if((currInstr.function == "lw") || (currInstr.function == "addi")){
			//if(currInstr.RegWrite == 1) //Checks if the Instruction writes back into the RegFile.
				//currInstr.RegT = currInstr.product; //The input from the mem stage is written into the Register pointed to by writeIntoRegister pointer.
		//}
	//}
//}


int validCheck( struct Latch validLatch){ // Checks for the status of the valid bit so the stage can take in new input.
	assert(validLatch.validBit == 1 || validLatch.validBit == 0);
	return validLatch.validBit; // 1 for valid; 0 for invalid.
}

int invalidateBit(struct Latch zeroThis){
	zeroThis.validBit = 0;
	assert(zeroThis.validBit == 0);
	return 0;
}

int validateBit(struct Latch oneThis){
	oneThis.validBit = 1;
	assert(oneThis.validBit == 1);
	return 1;
}

int init_reg(void) {
  long *$zero = &mips_reg[0], *$0 = &mips_reg[0], 
  long *$al = &mips_reg[1] , *$1  = &mips_reg[1] ,
  *$v0 = &mips_reg[2] , *$2  = &mips_reg[2] , 
  *$v1 = &mips_reg[3] , *$3  = &mips_reg[3] , 
  *$a0 = &mips_reg[4] , *$4  = &mips_reg[4] , 
  *$a1 = &mips_reg[5] , *$5  = &mips_reg[5] , 
  *$a2 = &mips_reg[6] , *$6  = &mips_reg[6] , 
  *$a3 = &mips_reg[7] , *$7  = &mips_reg[7] , 
  *$t0 = &mips_reg[8] , *$8  = &mips_reg[8] , 
  *$t1 = &mips_reg[9] , *$9  = &mips_reg[9] , 
  *$t2 = &mips_reg[10] , *$10 = &mips_reg[10] , 
  *$t3 = &mips_reg[11] , *$11 = &mips_reg[11] , 
  *$t4 = &mips_reg[12] , *$12 = &mips_reg[12] , 
  *$t5 = &mips_reg[13] , *$13 = &mips_reg[13] , 
  *$t6 = &mips_reg[14] , *$14 = &mips_reg[14] , 
  *$t7 = &mips_reg[15] , *$15 = &mips_reg[15] , 
  *$s0 = &mips_reg[16] , *$16 = &mips_reg[16] , 
  *$s1 = &mips_reg[17] , *$17 = &mips_reg[17] , 
  *$s2 = &mips_reg[18] , *$18 = &mips_reg[18] , 
  *$s3 = &mips_reg[19] , *$19 = &mips_reg[19] , 
  *$s4 = &mips_reg[20] , *$20 = &mips_reg[20] , 
  *$s5 = &mips_reg[21] , *$21 = &mips_reg[21] , 
  *$s6 = &mips_reg[22] , *$22 = &mips_reg[22] , 
  *$s7 = &mips_reg[23] , *$23 = &mips_reg[23] , 
  *$t8 = &mips_reg[24] , *$24 = &mips_reg[24] , 
  *$t9 = &mips_reg[25] , *$25 = &mips_reg[25] , 
  *$k0 = &mips_reg[26] , *$26 = &mips_reg[26] , 
  *$k1 = &mips_reg[27] , *$27 = &mips_reg[27] , 
  *$gp = &mips_reg[28] , *$28 = &mips_reg[28] , 
  *$sp = &mips_reg[29] , *$29 = &mips_reg[29] , 
  *$fp = &mips_reg[30] , *$30 = &mips_reg[30] , 
  *$ra = &mips_reg[31] , *$31 = &mips_reg[31];
  return 0;
}

int init_testMem(void){
	int i;
	for(i = 0; i < 256; i++)
		Mem_Reg[i] = i;
}