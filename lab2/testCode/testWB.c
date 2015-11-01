void WBStage(){ //struct Latch MemWB
	struct Instr test;
	if(MEMWB.valid == 1){ //Checks if latch has valid data for processing.
	test = MEMWB.data;
	 if(test.regWrite == 1){//Checks if the Instruction writes back into the RegFile.
	  
         mips_reg[test.rd] = test.temp; //The input from the mem stage is written into the Register pointed to by writeIntoRegister pointer.	
         }

        MEMWB.valid = 0;
         }
}