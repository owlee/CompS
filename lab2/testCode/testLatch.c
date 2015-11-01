#include <stdio.h>
#include <assert.h>
#include <assert.h>
#include <stdlib.h>

struct Instr {
  int aluSrc; //Controls
  int memWrite;
  int memRead;
  int regWrite;
  
  char func[];
  long *rs, *rt; //mips_reg data
  long *rd; //mips_reg writeback destination
  long imm;
  long product; //value passed along between ex and wb.
}

struct Latch {
  // reads when read == 1, set == 0
  //  sets when read == 0, set == 1
  // holds when read == 0, set == 0
  //int read = 0;
  //int set = 0;
  
  int validBit;
  struct Instr *data; //instruction currently held
}

struct Instr clkLatch(struct Latch latch, struct Instr instr) {
  // set. Next stage is given the instruction
  if ((read == 0) && (set == 1)) {
    latch.read=1;
    latch.set=0;
    return instr;

  // read. Instruction is read and stored from the previous stage
  } else if ((read == 1) && (set == 0)) {
    latch.read=0;
    latch.set=1;
    latch.data = instr;

  // Hold. Might make this a check for abnormalities
  } else {
    printf("Instt clkLatch have read and set out of bounds.")
    exit(0);
  }
}

int main (int argc, char *argv[]) {


}