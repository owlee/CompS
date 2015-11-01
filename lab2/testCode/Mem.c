void MemStage(){ //INPUT LATCH: EXMEM ; OUTPUT LATCH = MEMWB
	struct Instr temp = EXMEM.inst;
	if(EXMEM.validBit == 1) //valid inst test
		EXMEM.validBit = 0; //has been read and invalidated.
		assert(!(temp.memWrite && temp.memRead));
		if(temp.memWrite == 1)  //sw
			mem_reg[temp.product] = temp.rt;
		if(temp.memRead == 1)   //lw
			temp.product = mem_reg[temp.product]; //memory value to be used in WB.
		MEMWB.inst.product = temp.product; //push instr into output latch
		MEMWB.validBit = 1; //validates output latch
	}