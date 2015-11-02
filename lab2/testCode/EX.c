void EX(){

	if(IDEX.validBit == 1){
		struct Instr test = *IDEX.data;
	
		if(strcmp(test.opcode, "add")==0){
			test.product = mips_reg[test.rs] + mips_reg[test.rt];
		}
	
	    else if(strcmp(test.opcode, "addi")==0){
			test.product = mips_reg[test.rs] + test.imm;
	   	}
	
    else if(strcmp(test.opcode, "sub")==0){	  
		test.product = mips_reg[test.rs] - mips_reg[test.rt];
	}
		
	else if(strcmp(test.opcode, "mul")==0){
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
	EXMEM.data = &test;
	}
}