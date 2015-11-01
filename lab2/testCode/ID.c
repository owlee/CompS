void ID(){
	struct Instr test;
	if(IFID.valid == 1){
	test = latchIF.data;	
	
	switch(test.opcode){
		case 0:
		test.rd = test.arg0;
		test.rs = test.arg1;
		test.rt = test.arg2;
		test.regWrite = 1;
		break;
			
	    case 1:	
    	test.rt = test.arg0;
		test.rs = test.arg1;
		test.imm = test.arg2;
		test.aluSrc = 1;
		test.regWrite = 1;
		break;
		
		case 2:
		test.rd = test.arg0;
		test.rs = test.arg1;
		test.rt = test.arg2;
		test.regWrite = 1;
		
		case 3:
		test.rd = test.arg0;
		test.rs = test.arg1;
		test.rt = test.arg2;
		test.regWrite = 1;
		break;
		
		case 4:
		test.rs = test.arg0;
		test.rt = test.arg1;
		test.imm = test.arg2;
		break;
	
		case 5:        
		test.rt = test.arg0;
		test.imm = test.arg1;
		test.rs = test.arg2;
		test.aluSrc = 1;
		test.memRead = 1;
		test.regWrite = 1;
		break;
		
		case 6:
		test.rt = test.arg0;
		test.imm = test.arg1;
		test.rs = test.arg2;
		test.aluSrc = 1;
		test.memWrite = 1;
		break;
	}
	IFID.valid = 0;
	IDEX.valid = 1;
	IDEX.data = test;
}
}
