void MEM(){ //INPUT LATCH: EXMEM ; OUTPUT LATCH = MEMWB

	if(EXMEM.validBit == 1) { //valid inst test
		struct Instr temp = *EXMEM.data;

		EXMEM.validBit = 0; //has been read and invalidated.
		assert(!(temp.memWrite && temp.memRead));

		if(temp.memWrite == 1) {  //sw
			mem_reg[temp.product] = mips_reg[temp.rt];

		} else if(temp.memRead == 1) { //lw
			temp.product = mem_reg[temp.product]; //memory value to be used in WB.
		}

		MEMWB.data = &temp; //push instr into output latch
		MEMWB.validBit = 1; //validates output latch
	}
}