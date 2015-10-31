#include <stdio.h>
#include <assert.h>
#include <assert.h>
#include <stdlib.h>

struct Instr {
  int aluSrc = 0; //Controls
  int memWrite = 0;
  int memRead = 0;
  int regWrite = 0;

  long *rs = 0, *rt = 0; //Pointers to register values 
  long *rd = 0; //Pointers to destination of regWrite
  long imm;
  long product; //Contains the output of ex/mem stages and inputs of the mem/wb stages
}

struct Latch {
  // reads when read == 1, set == 0
  //  sets when read == 0, set == 1
  // holds when read == 0, set == 0
  //int read = 0;
  //int set = 0;
  
  int validBit;
  struct Instr *data; //Points to instruction currently held.
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
