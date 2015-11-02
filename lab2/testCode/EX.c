//static int PC;

void EX(){
	struct Instr test;
	if(IDEX.validBit == 1){
		test = IDEX.data;
	else{
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
		if(test.imm%4 != 0){
			printf("%s", "Immediate field not byte offset");
			exit(0);
		}
		else{
		if(mips_reg[test.rs] == mips_reg[test.rt]){
		int j = (test.imm)/4;
		PC = PC + j;
		}
		
	   }
	}
		
	
	else if(strcmp(test.opcode, "lw")==0){
		test.product = mips_reg[mips_reg[test.rs]] + (test.imm/4);		
	}
		
   else if(strcmp(test.opcode, "sw")==0){
		test.product = mips_reg[test.rs] + (test.imm/4)
   }
	else{
	printf("%s", "InvalidBit function");
	exit(0);
	}
	}
	
	IDEX.validBit = 0;
	EXMEM.validBit = 1;
	EXMEM.data = test;
}
}