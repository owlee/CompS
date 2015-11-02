void ID(){

	if(IFID.validBit == 1){
		struct Instr test = *(IFID.data);	
		if(test.imm > 65535){
				printf("%s", "Immediate field is out of range");
				exit(0);
			}
			
			if(strcmp(test.opcode, "add") == 0){	
			test.rd = test.arg0;
			test.rs = test.arg1;
			test.rt = test.arg2;
			test.memRead = 0;
			test.memWrite = 0;
			test.regWrite = 1;
			}
		else if(strcmp(test.opcode, "addi") == 0){			
		    test.rd = test.arg0;
			test.rs = test.arg1;
			test.imm = test.arg2;
			test.memRead = 0;
			test.memWrite = 0;
			test.regWrite = 1;
		}
		else if(strcmp(test.opcode, "sub") == 0){
			test.rd = test.arg0;
			test.rs = test.arg1;
			test.rt = test.arg2;
			test.memRead = 0;
			test.memWrite = 0;
			test.regWrite = 1;
		}
			
		else if(strcmp(test.opcode, "mul") == 0){
			test.rd = test.arg0;
			test.rs = test.arg1;
			test.rt = test.arg2;
			test.memRead = 0;
			test.memWrite = 0;
			test.regWrite = 1;
		}
			
		else if(strcmp(test.opcode, "beq") == 0){
			test.rs = test.arg0;
			test.rt = test.arg1;
			test.imm = test.arg2;
			test.memRead = 0;
			test.memWrite = 0;
			test.regWrite = 0;
		}
		
		else if(strcmp(test.opcode, "lw") == 0){     
			test.rd = test.arg0;
			test.imm = test.arg1;
			test.rs = test.arg2;
			test.memWrite = 0;
			test.memRead = 1;
			test.regWrite = 1;
		}
			
		else if(strcmp(test.opcode, "sw") == 0){
			test.rt = test.arg0;
			test.imm = test.arg1;
			test.rs = test.arg2;
			test.memRead = 0;
			test.regWrite = 0;
			test.memWrite = 1;
		}
		else{
			printf("%s", "Invalid function");
			exit(0);
		}

	IFID.validBit = 0;
	IDEX.validBit = 1;
	IDEX.data = &test;
	}
}