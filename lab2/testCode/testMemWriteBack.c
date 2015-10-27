#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
//Let add = 'a' ; addi = 'i' ; sub = 's' ; mul = 'm' ; lw = 'l' ; sw = 's' ;
// beq = 'b' ; haltSimulation = h ; for the action attribute of the instruction

Struct Instr{ //Makeshift instruction struct
	char action; //instruction type, see comment list on line 6+7
	long rs; //value of register when instruction passes through IF stage
	long rt;
	long *writeIntoRegister; 
	long imm;
	long inputOutput; //Holds the inputs to be used in next stage, holds the output of that stage when it has completed.

	int ALUSrc; //controls
	int MemWrite;
	int MemRead;
	int RegWrite;
}

Struct Latch{
	Instr *instruction; //Points to an instruction struct; currently loaded in 
	int validBit; //Tells if the instruction is new and ready to be loaded in.
}

int main(){ //Test
//
}

void MemStage(Latch ExMem){
	Instr currInstr = ExMem.*instruction; //holds the current instruction stored in input latch
	if(validCheck(ExMem) == 0){ //Checks if latch has valid data for processing. Ends function/stage when it fails.
		break;
	}
	else{
		invalidateBit(ExMem); //Reads in valid instruction and then invalidates it.
		switch(currInstr.action){
			case 's': //sw case
				if(currInstr.memWrite == 1) 
					Mem_Reg[inputOutput] = currInstr.rt;
			case 'l': //lw case
				if(currInstr.memRead == 1)
					currInstr.inputOutput = Mem_Reg[inputOutput]; //Stores value of memory of input addr into
			default:
				break;
		}
		MemWB.*instruction = currInstr; //Pushes input instruction into the output latch.
		validateBit(MemWB); //Validates the instruction so that the next stage is able to read in.
	}
}

void WBStage(Latch MemWB){
	Instr currInstr = MemWB.*instruction; //Stores the current instruction stored in input latch
	if(validCheck(MemWB) == 0) //Checks if latch has valid data for processing.
		break;
	else
		invalidateBit(MemWB);
		if(currInstr.RegWrite == 1) //Checks if the instruction writes back into the RegFile.
			currInstr.writeIntoRegister = currInstr.inputOutput; //The input from the mem stage is written into the Register pointed to by writeIntoRegister pointer.
}

int validCheck(Latch validLatch){ // Checks for the status of the valid bit so the stage can take in new input.
	return validLatch.validBit; // 1 for valid; 0 for invalid.
}

int invalidateBit(Latch zeroThis){
	zeroThis.validBit = 0;
	return 0;
}

int validateBit(Latch oneThis){
	oneThis.validBit = 1;
	return 1;
}