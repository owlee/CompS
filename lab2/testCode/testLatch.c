#include <stdio.h>
#include <assert.h>
#include <assert.h>
#include <stdlib.h>

struct Instr {
  int regDst;
  int aluSrc;
  int aluOp;
  int memWrite;
  int memRead;
  int memToReg;
  int regWrite;
  
  // Holder Values to organize
  int arg0, arg1, arg2;
  
  // Acutal Destinations of Instruction
  char *opcode;
  int rs, rt, rd, imm;
  long *temp;
};

struct Latch {
  int validBit;
  struct Instr *data; //instruction currently held
};

int main (int argc, char *argv[]) {


}
