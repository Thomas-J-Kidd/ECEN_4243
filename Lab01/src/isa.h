/***************************************************************/
/*                                                             */
/*   RISC-V RV32 Instruction Level Simulator                   */
/*                                                             */
/*   ECEN 4243                                                 */
/*   Oklahoma State University                                 */
/*                                                             */
/***************************************************************/

#ifndef _SIM_ISA_H_
#define _SIM_ISA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

//
// MACRO: Check sign bit (sb) of (v) to see if negative
//   if no, just give number
//   if yes, sign extend (e.g., 0x80_0000 -> 0xFF80_0000)
//
#define SIGNEXT(v, sb) ((v) | ( (0 < ( (v) & (1 << (sb-1) ) )) ? ~( (1 << (sb-1) )-1 ) : 0))


//Zero extend function
int ZEROEXT(int v, int val)
{
  if(val == 8)
   {
    int f = 0XFF & v;
    return f;
   }

   else if(val == 5)
   {
    int f = 0X1F & v;
    return f;
   }

   else if(val == 16)
   {
    int f = 0XFFFF & v;
    return f;
   }

   else {
    printf("Invalid ZEROEXT parameters! \n");
   }
}






// I Instructions
int ADDI (int Rd, int Rs1, int Imm, int Funct3) {

  int cur = 0;
  //signed test = -1;
  //test = SIGNEXT(Imm,12);
  cur = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12);
  //printf("Printing out current state in ADDI: cur: %d, test: %d\n\n", cur, test);
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int LB (int Rd, int Rs1, int Imm, int Funct3)
{
  uint32_t address = CURRENT_STATE.REGS[Rs1] + SIGNEXT(Imm, 12);
  int read = mem_read_32(address);
  int data = read;
  NEXT_STATE.REGS[Rd] = SIGNEXT((data),16); 
};

int LH (char* i_);
int LW (char* i_);
int LBU (char* i_);
int LHU (char* i_);
int SLLI (char* i_);
int SLTI (char* i_);
int SLTIU (char* i_);
int XORI (char* i_);
int SRLI (char* i_);
int SRAI (char* i_);
int ORI (char* i_);
int ANDI (char* i_);

// U Instruction
int AUIPC (char* i_);
int LUI (char* i_);

// S Instruction
int SB (char* i_);
int SH (char* i_);
int SW (char* i_);

// R instruction


int ADD (int Rd, int Rs1, int Rs2, int Funct3) {

  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] + CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;

}

int SUB (int Rd, int Rs1, int Rs2, int Funct3, int Funct7)
{
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] - CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;  
  return 0;
}



int SLL (int Rd, int Rs1, int Rs2, int Funct3)
{
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs2] << CURRENT_STATE.REGS[Rs1];
  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int SLT (int Rd, int Rs1, int Rs2, int Funct3)
{
  int cur = 0;

  if(CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2])
  {
    cur = 1;
  }
    
  else
  {
    cur = 0;
  }
    

  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

unsigned SLTU (unsigned Rd, unsigned Rs1, unsigned Rs2, unsigned Funct3)
{
   unsigned cur = 0;

  if(CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2], 5)
  {
    cur = 1;
  }
    
  else
  {
    cur = 0;
  }
    

  NEXT_STATE.REGS[Rd] = cur;
  return 0;
}

int XOR (int Rd, int Rs1, int Rs2, int Funct3)
{
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] ^ CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;  
  return 0;
}

int SRL (int Rd, int Rs1, int Rs2, int Funct3)
{
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] >> CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;  
  return 0;
}

unsigned SRA (unsigned Rd, unsigned Rs1, unsigned Rs2, unsigned Funct3, unsigned Funct7)
{
  unsigned cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] >> CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;  
  return 0;
}

int OR (int Rd, int Rs1, int Rs2, int Funct3)
{
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] | CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;  
  return 0;
}

int AND (int Rd, int Rs1, int Rs2, int Funct3)
{
  int cur = 0;
  cur = CURRENT_STATE.REGS[Rs1] & CURRENT_STATE.REGS[Rs2];
  NEXT_STATE.REGS[Rd] = cur;  
  return 0;
}

// B instructions
int BEQ (int Rs1, int Rs2, int Imm, int Funct3)
{
  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] = CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC + 4) + (SIGNEXT(Imm,13));
  return 0;
}

int BNE (int Rs1, int Rs2, int Imm, int Funct3) 
{
  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] != CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC + 4) + (SIGNEXT(Imm,13));
  return 0;
}


int BLT (int Rs1, int Rs2, int Imm, int Funct3)
{
  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC + 4) + (SIGNEXT(Imm,13));
  return 0;
}

int BGE (int Rs1, int Rs2, int Imm, int Funct3_)
{
  int cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] >= CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC + 4) + (SIGNEXT(Imm,13));
  return 0;
}

unsigned BLTU (unsigned Rs1, unsigned Rs2, unsigned Imm, unsigned Funct3)
{
  unsigned cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] < CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC + 4) + (SIGNEXT(Imm,13));
  return 0;
}

unsigned BGEU (unsigned Rs1, unsigned Rs2, unsigned Imm, unsigned Funct3)
{
  unsigned cur = 0;
  Imm = Imm << 1;
  if (CURRENT_STATE.REGS[Rs1] >= CURRENT_STATE.REGS[Rs2])
    NEXT_STATE.PC = (CURRENT_STATE.PC + 4) + (SIGNEXT(Imm,13));
  return 0;
}

// I instruction


int JALR (int Rd, int Rs1, int Imm, int Funct3)
{
  Imm = Imm << 1;
  NEXT_STATE.PC = (CURRENT_STATE.REGS[Rs1]) + (SIGNEXT(Imm,12));
  NEXT_STATE.REGS[Rd] = (CURRENT_STATE.PC + 4);
}



// J instruction
int JAL (char* i_);

int ECALL (char* i_){return 0;}

#endif
