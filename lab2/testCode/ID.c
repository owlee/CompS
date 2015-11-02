void ID(){
	instr_mem[PC] = in;
	IFID.data = &instr_mem[PC]; 
	
if(IFID.validBit == 1){
	test = *(IFID.data);	
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
	    test.rt = test.arg0;
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
		
	else if(strcmp(test.opcode, "mult") == 0){
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
		test.rt = test.arg0;
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
	IDEX.data = &instr_mem[PC];
	}
}


	
	IFID.data = &instr_mem[PC];
	struct Instr test;
	if(IDEX.validBit == 1){
		test = *(IDEX.data);
	
		if(strcmp(test.opcode, "add")==0){
		test.product = mips_reg[test.rs] + mips_reg[test.rt];
		}
	
	   else if(strcmp(test.opcode, "addi")==0){
		test.product = mips_reg[test.rs] + test.imm;
	   }
	
    else if(strcmp(test.opcode, "sub")==0){	  
	  test.product = mips_reg[test.rs] - mips_reg[test.rt];
	}
		
	else if(strcmp(test.opcode, "mult")==0){
		test.product = mips_reg[test.rs] * mips_reg[test.rt];
	}
		
    else if(strcmp(test.opcode, "beq")==0){	
		if(test.imm%(long)4 != 0){
			printf("%s", "Immediate field not byte offset");
			exit(0);
	   }
	   	else if(mips_reg[test.rs] == mips_reg[test.rt]){
		int j = (test.imm)/(long)4;
		PC = PC + j;
		}	
		
		
	}
		
	
	else if(strcmp(test.opcode, "lw")==0){
		if(test.imm%(long)4 != 0){
			printf("%s", "Immediate field not byte offset");
			exit(0);
	   }
		else {
			test.product = mips_reg[mips_reg[test.rs]] + (test.imm/(long)4);		
	}
	}	
   else if(strcmp(test.opcode, "sw")==0){
	   if(test.imm%(long)4 != 0){
			printf("%s", "Immediate field not byte offset");
			exit(0);
	   }
		else{
			test.product = mips_reg[test.rs] + (test.imm/(long)4);
   }
   }
	else{
	printf("%s", "Invalid function");
	exit(0);
	}
	
	
	IDEX.validBit = 0;
	EXMEM.validBit = 1;
	EXMEM.data = &instr_mem[PC];
}
}

	
	in.arg0 = 2;
	in.arg1 = 2;
	in.arg2 = 8;
	in.opcode = "beq";
	
	IFID.validBit = 1;
	
	ID();
    EX();	
	
	printf("%i\n", test.rs);
	printf("%i\n", test.rt);
	printf("%i\n", test.imm);
	printf("%i\n", test.memWrite);
	printf("%i\n", test.regWrite);
	printf("%i\n", PC);
	
	
	return 0;
}
	

