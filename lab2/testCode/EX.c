//static int PC;

void EX(){
	struct Instr test;
	if(IDEX.valid == 1){
		test = IDEX.data;
	
	enum opcode val = check string and set value;
	
	switch(val){
		
    case 0:
		test.temp = test.rs + test.rt;
		break;
	
	case 1:
		test.temp = test.rs + temp.imm;
		break;
	
	case 2:
		test.temp = test.rs - test.rt;
		break;
		
	case 3:	
		test.temp = test.rs * test.rt;
		break;
		
    case 4:		
		if(test.imm > 65535){
			printf("%s", "Immediate field is out of range");
			exit(0);
		}
		else if(test.imm%4 != 0){
			printf("%s", "Immediate field not byte offset");
			exit(0);
		}
		else{
		if(test.rs == test.rt){
		int j = (test.imm)/4;
		PC = PC + j;
		}
		
	   }
		break;
	
	case 5:
		test.temp = mem_reg[test.rs + (test.imm/4)];		
		break;
		
	case 6:
		mem_reg[test.rs + (test.imm/4)] = *(test.rt);
	
	default:
	printf("%s", "Invalid function");
	exit(0);
	}
	
	IDEX.valid = 0;
	EXMEM.valid = 1;
	EXMEM.data = test;
}