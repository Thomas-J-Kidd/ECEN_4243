# Each instruction is described below 

Instructions here are described first in pseudocode on what control signals need to be enabled and what the order of operations will be



## Instructions


ImmSrc Encoding

|ImmSrc|ImmExt|Type| Description |
|-----------|-----------|-----------|-----------|
| 00 | {{20{Instr[31]}}, Instr[31:20]} | I | 12-bit signed immediate |
| 01 | {{20{Instr[31]}}, Instr[31:25], Instr[11:7]} | S | 12-bit signed immediate |
| 10 | {{20{Instr[31]}}, Instr[7], Instr[30:25], Instr[11:8], 1’b0} | B | 13-bit signed immediate |

### B type instructions 

### BEQ

Branch if $rs1 == rs2$ PC = label

The branch offset is 13 bits stored in a 12 bit imm field 

ImmSrc = 2

#### BGE  

Branch if greater than or equal to [if ($rs1 \geq rs2$) PC = label]


#### BLT

#### BLTU

#### BNE

### I type instructions

#### JALR

#### LB

#### LBU 

#### LH

#### LHU

#### SLLI 

#### SLTIU

#### SRAI 

#### SRLI

#### XORI

### U type instructions

#### LUI

### S type instructions

#### SB

#### SH

### R type instructions

#### SLL

#### SLTU

#### SRA

#### SRL

#### XOR


