void MemStage(){ //INPUT LATCH: ExMem ; OUTPUT LATCH = MemWB
	struct Instr test;
	if(EXMEM.validBit == 1){ //Checks if latch has valid data for processing. Ends function/stage when it fails.
	   test = EXMEM.data; //Reads in valid Instruction and then invalidates it.
	   if(temp.memWrite == 1){  //sw
	   mem_reg[test.temp] = test.rt;
		}

           else if(test.memRead == 1){
		test.rt = mem_reg[test.temp]; //Stores value of memory of input addr into
		}
           else{}
           }
          EXMEM.valid = 0; //Validates the Instruction so that the next stage is able to read in.
          MEMWB.valid = 1;
          MEMWB.data = test;  //instruction into output latch
	}
}