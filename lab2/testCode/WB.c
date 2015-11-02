void WBStage(){ //struct Latch MEMWB
	if(MEMWB.validBit == 1) { //valid instruction
		struct Instr temp = *MEMWB.data;
		MEMWB.validBit = 0; //reads in and invalidates latch

		if(temp.regWrite == 1) //valid to change mips_reg
			mips_reg[temp.rd] = temp.product; //input from Mem written into destinate mips_reg
	}
}