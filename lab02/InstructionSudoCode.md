# Each instruction is described below 

Instructions here are described first in pseudocode on what control signals need to be enabled and what the order of operations will be



# Instructions


ImmSrc Encoding

|ImmSrc|ImmExt|Type| Description |
|-----------|-----------|-----------|-----------|
| 00 | {{20{Instr[31]}}, Instr[31:20]} | I | 12-bit signed immediate |
| 01 | {{20{Instr[31]}}, Instr[31:25], Instr[11:7]} | S | 12-bit signed immediate |
| 10 | {{20{Instr[31]}}, Instr[7], Instr[30:25], Instr[11:8], 1’b0} | B | 13-bit signed immediate |

## B type instructions 

|Name| OPCode | Func3 | ImmSrc | ALUSrc | ALUControl | PCSrc | RegWrite | MemWrite |
|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
| BEQ  | 1100011 | 000 | 10 | 0 use SrcB | 001 (sub) |  0/1 depends | 0 | 0 |
| BNE  | 1100011 | 001 | 10 | 0 use SrcB | 001 (sub) | 0/1 depends | 0 | 0 |
| BLT  | 1100011 | 100 | 10 | 0 use SrcB | 101 (SLT) | 0/1 depends | 0 | 0 |
| BGE  | 1100011 | 101 | 10 | 0 use SrcB | TB (TB) | 0/1 depends | 0 | 0 |
| BLTU  | 1100011 | 110 | 10 | 0 use SrcB | TB (TB) | 0/1 depends | 0 | 0 |
| BGEU  | 1100011 | 111 | 10 | 0 use SrcB | TB (TB) | 0/1 depends | 0 | 0 |

### BEQ OPcode = 1100011, Func3 = 000
Branch if $rs1 == rs2$ PC = label

#### Order of Operations

1) Read the PC
2) Get the instruction from the Instruction Memory
3) Decode the instruction using the control unit
4) The Main Control unit gets the following signals: ImmSrc = 2, RegWrite = 0, MemWrite = 0, PCSrc = 0,1
5) The ALU Control unit gets the following signals: ALUSrc = 0, ALUControl = 001
6) The ImmExtender carries through using the ImmSrc control signal
7) The PCTarget module creates the new PC value from this Extended Immediate value
8) The two source registers are compared (Rs1 -> SrcA - Rs2 -> SrcB)
9) The ALUSrc Signal = 0 to to signal to the ALU to use SrcB not ImmExtended
10) If the value is 0 a ALUzero Flag = 1 to signal to the PSSrc = 1
11) If the PSSrc = 1 use PCTarget address
12) If not use the next PC+4 address
#### Modules in use

- RF to get the two values to compare
- Extend the immediate 
- PC target to find the new PC value if the comparison is true
- PCplus 4 if the comparison is falce
- PCNext module to decide which PC to use
- ALU to perform the arithmetic
- ALUSrc to decide the input SecB into the ALU


##### ImmSrc = 2
The branch offset is 13 bits stored in a 12 bit imm field this is handled by the Extender module and the ImmSrc controls how the mudule interprets the incominhg data.

##### ALUControl = 001
The ALU will perform a subtraction
Somehow we must determine that the value of this subtraction is 0

##### if SrcA - SrcB = 0 PCSrc = 1
set the PC control signal to 1 to branch to the new address provided by the instruction immediate. Use the **PCTarget module**

##### if SrcA - SrcB = !0 PCSrc = 0
Use the **PC+4 module** to move forward in the instructions

##### ALUSrc = 0
chooses SrcB from the mem file instead of the extended immediate in other cases

##### RegWrite = 0 
No writing to registers

##### MemWrite = 0
No writing to memory




### BNE OPcode = 1100011, Func3 = 001
Branch if $rs1 != rs2$ PC = label

#### Order of Operations

1) Read the PC
2) Get the instruction from the Instruction Memory
3) Decode the instruction using the control unit
4) The Main Control unit gets the following signals: ImmSrc = 2, RegWrite = 0, MemWrite = 0, PCSrc = 0,1
5) The ALU Control unit gets the following signals: ALUSrc = 0, ALUControl = 001
6) The ImmExtender carries through using the ImmSrc control signal
7) The PCTarget module creates the new PC value from this Extended Immediate value
8) The two source registers are compared (Rs1 -> SrcA - Rs2 -> SrcB)
9) The ALUSrc Signal = !0 to to signal to the ALU to use SrcB not ImmExtended
10) If the value is !0 a ALUzero Flag = 1 to signal to the PSSrc = 1
11) If the PSSrc = 1 use PCTarget address
12) If not use the next PC+4 address
#### Modules in use

- RF to get the two values to compare
- Extend the immediate 
- PC target to find the new PC value if the comparison is true
- PCplus 4 if the comparison is falce
- PCNext module to decide which PC to use
- ALU to perform the arithmetic
- ALUSrc to decide the input SecB into the ALU


##### ImmSrc = 2
The branch offset is 13 bits stored in a 12 bit imm field this is handled by the Extender module and the ImmSrc controls how the mudule interprets the incominhg data.

##### ALUControl = 001
The ALU will perform a subtraction
Somehow we must determine that the value of this subtraction is 0

##### if SrcA - SrcB = 0 PCSrc = 1
set the PC control signal to 1 to branch to the new address provided by the instruction immediate. Use the **PCTarget module**

##### if SrcA - SrcB = !0 PCSrc = 0
Use the **PC+4 module** to move forward in the instructions

##### ALUSrc = 0
chooses SrcB from the mem file instead of the extended immediate in other cases

##### RegWrite = 0 
No writing to registers

##### MemWrite = 0
No writing to memory


### BLT OPcode = 1100011, Func3 = 100

Branch if greater than or equal to [if ($rs1 \lt rs2$) PC = label]

#### Order of Operations

1) Read the PC
2) Get the instruction from the Instruction Memory
3) Decode the instruction using the control unit
4) The Main Control unit gets the following signals: ImmSrc = 2, RegWrite = 0, MemWrite = 0, PCSrc = 0,1
5) The ALU Control unit gets the following signals: ALUSrc = 0, ALUControl = 001
6) The ImmExtender carries through using the ImmSrc control signal
7) The PCTarget module creates the new PC value from this Extended Immediate value
8) The two source registers are compared (Rs1 -> SrcA $\lt$ Rs2 -> SrcB)
8.1) The ALU should have a set less than implemented. If the statement is true, the output should be 1 of the ALU. This can then be used to determine the next state.
9) The ALUSrc Signal = TRUE to to signal to the ALU to use SrcB not ImmExtended
10) If the statment is FALSE a ALUzero Flag = 1 to signal to the PSSrc = 1
11) If the PSSrc = 1 use PCTarget address
12) If not use the next PC+4 address
#### Modules in use

- RF to get the two values to compare
- Extend the immediate 
- PC target to find the new PC value if the comparison is true
- PCplus 4 if the comparison is falce
- PCNext module to decide which PC to use
- ALU to perform the arithmetic
- ALUSrc to decide the input SecB into the ALU


##### ImmSrc = 2
The branch offset is 13 bits stored in a 12 bit imm field this is handled by the Extender module and the ImmSrc controls how the mudule interprets the incominhg data.

##### ALUControl = 001
The ALU will perform a subtraction
Somehow we must determine that the value of this subtraction is 0

##### if SrcA >= SrcB  PCSrc = 1
set the PC control signal to 1 to branch to the new address provided by the instruction immediate. Use the **PCTarget module**

##### if SrcA < SrcB PCSrc = 0
Use the **PC+4 module** to move forward in the instructions

##### ALUSrc = 0
chooses SrcB from the mem file instead of the extended immediate in other cases

##### RegWrite = 0 
No writing to registers

##### MemWrite = 0
No writing to memory

### BGE OPcode = 1100011, Func3 = 101

Branch if greater than or equal to [if ($rs1 \geq rs2$) PC = label]

#### Order of Operations

1) Read the PC
2) Get the instruction from the Instruction Memory
3) Decode the instruction using the control unit
4) The Main Control unit gets the following signals: ImmSrc = 2, RegWrite = 0, MemWrite = 0, PCSrc = 0,1
5) The ALU Control unit gets the following signals: ALUSrc = 0, ALUControl = 001
6) The ImmExtender carries through using the ImmSrc control signal
7) The PCTarget module creates the new PC value from this Extended Immediate value
8) The two source registers are compared (Rs1 -> SrcA $\geq$ Rs2 -> SrcB)
8.1) This can be checked by doing a subtraction (Rs1-Rs2) and then checking if the most significat bit is 0 -> if so then we branch where we need to.  
9) The ALUSrc Signal = 0 to to signal to the ALU to use SrcB not ImmExtended
10) If the statment is True a ALUzero Flag = 1 to signal to the PSSrc = 1
11) If the PSSrc = 1 use PCTarget address
12) If not use the next PC+4 address
#### Modules in use

- RF to get the two values to compare
- Extend the immediate 
- PC target to find the new PC value if the comparison is true
- PCplus 4 if the comparison is falce
- PCNext module to decide which PC to use
- ALU to perform the arithmetic
- ALUSrc to decide the input SecB into the ALU


##### ImmSrc = 2
The branch offset is 13 bits stored in a 12 bit imm field this is handled by the Extender module and the ImmSrc controls how the mudule interprets the incominhg data.

##### ALUControl = 001
The ALU will perform a subtraction
Somehow we must determine that the value of this subtraction is 0

##### if SrcA >= SrcB  PCSrc = 1
set the PC control signal to 1 to branch to the new address provided by the instruction immediate. Use the **PCTarget module**

##### if SrcA < SrcB PCSrc = 0
Use the **PC+4 module** to move forward in the instructions

##### ALUSrc = 0
chooses SrcB from the mem file instead of the extended immediate in other cases

##### RegWrite = 0 
No writing to registers

##### MemWrite = 0
No writing to memory




### BLTU OPcode = 1100011, Func3 = 110
USES UNSIGNED NUMBERS 
Branch if greater than or equal to [if ($rs1 \lt rs2$) PC = label] 

#### Order of Operations

1) Read the PC
2) Get the instruction from the Instruction Memory
3) Decode the instruction using the control unit
4) The Main Control unit gets the following signals: ImmSrc = 2, RegWrite = 0, MemWrite = 0, PCSrc = 0,1
5) The ALU Control unit gets the following signals: ALUSrc = 0, ALUControl = 001
6) The ImmExtender carries through using the ImmSrc control signal
7) The PCTarget module creates the new PC value from this Extended Immediate value
8) The two source registers are compared (Rs1 -> SrcA $\lt$ Rs2 -> SrcB)
8).1 This again can be implemented by either the SLT operation of the ALU.
9) The ALUSrc Signal = TRUE to to signal to the ALU to use SrcB not ImmExtended
10) If the statment is FALSE a ALUzero Flag = 1 to signal to the PSSrc = 1
11) If the PSSrc = 1 use PCTarget address
12) If not use the next PC+4 address
#### Modules in use

- RF to get the two values to compare
- Extend the immediate 
- PC target to find the new PC value if the comparison is true
- PCplus 4 if the comparison is falce
- PCNext module to decide which PC to use
- ALU to perform the arithmetic
- ALUSrc to decide the input SecB into the ALU


##### ImmSrc = 2
The branch offset is 13 bits stored in a 12 bit imm field this is handled by the Extender module and the ImmSrc controls how the mudule interprets the incominhg data.

##### ALUControl = 001
The ALU will perform a subtraction
Somehow we must determine that the value of this subtraction is 0

##### if SrcA >= SrcB  PCSrc = 1
set the PC control signal to 1 to branch to the new address provided by the instruction immediate. Use the **PCTarget module**

##### if SrcA < SrcB PCSrc = 0
Use the **PC+4 module** to move forward in the instructions

##### ALUSrc = 0
chooses SrcB from the mem file instead of the extended immediate in other cases

##### RegWrite = 0 
No writing to registers

##### MemWrite = 0
No writing to memory

### BGEU OPcode = 1100011, Func3 = 111
USES UNSIGNED NUMBERS 
Branch if greater than or equal to [if ($rs1 \geq rs2$) PC = label] 

#### Order of Operations

1) Read the PC
2) Get the instruction from the Instruction Memory
3) Decode the instruction using the control unit
4) The Main Control unit gets the following signals: ImmSrc = 2, RegWrite = 0, MemWrite = 0, PCSrc = 0,1
5) The ALU Control unit gets the following signals: ALUSrc = 0, ALUControl = 001
6) The ImmExtender carries through using the ImmSrc control signal
7) The PCTarget module creates the new PC value from this Extended Immediate value
8) The two source registers are compared (Rs1 -> SrcA $\geq$ Rs2 -> SrcB)
9) The ALUSrc Signal = TRUE to to signal to the ALU to use SrcB not ImmExtended
10) If the statment is FALSE a ALUzero Flag = 1 to signal to the PSSrc = 1
11) If the PSSrc = 1 use PCTarget address
12) If not use the next PC+4 address
#### Modules in use

- RF to get the two values to compare
- Extend the immediate 
- PC target to find the new PC value if the comparison is true
- PCplus 4 if the comparison is falce
- PCNext module to decide which PC to use
- ALU to perform the arithmetic
- ALUSrc to decide the input SecB into the ALU


##### ImmSrc = 2
The branch offset is 13 bits stored in a 12 bit imm field this is handled by the Extender module and the ImmSrc controls how the mudule interprets the incominhg data.

##### ALUControl = 001
The ALU will perform a subtraction
Somehow we must determine that the value of this subtraction is 0

##### if SrcA >= SrcB  PCSrc = 1
set the PC control signal to 1 to branch to the new address provided by the instruction immediate. Use the **PCTarget module**

##### if SrcA < SrcB PCSrc = 0
Use the **PC+4 module** to move forward in the instructions

##### ALUSrc = 0
chooses SrcB from the mem file instead of the extended immediate in other cases

##### RegWrite = 0 
No writing to registers

##### MemWrite = 0
No writing to memory





## I type instructions

|Name| OPCode | Func3 |Func7|  ImmSrc | ALUSrc | ALUControl | PCSrc | RegWrite | MemWrite | ResultSrc |
|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
|lb | 0000011 | 000 |NA| 00 | 1 | 0000 (ADD) | 0 | 1 | 0 | 1 use Data Memory result |
|lh | 0000011 | 001 |NA| 00 | 1 | 0000 (ADD) | 0 | 1 | 0 | 1 use Data Memory result |
|lw | 0000011 | 010 |NA| 00 | 1 | 0000 (ADD) | 0 | 1 | 0 | 1 use Data Memory result |
|lbu | 0000011 | 100 |NA| 00 | 1 | 0000 (ADD) | 0 | 1 | 0 | 1 use Data Memory result |
|lhu | 0000011 | 101 |NA| 00 | 1 | 0000 (ADD) | 0 | 1 | 0 | 1 use Data Memory result |
|addi | 0010011 | 000 |NA| 00 | 1 | 0000 (ADD) | 0 | 1 | 0 write to reg| 0 |
|slli | 0010011 | 001 |0000000| 00 | 1 | 1001 (SLL) | 0 | 1 | 0 write to reg | 0 |
|slti | 0010011 | 010 |NA| 00 | 1 | 0101 (SLT) | 0 | 1 | 0 write to reg | 0 |
|sltiu | 0010011 | 010 |NA| No Sign Extention | 1 | 0101 (SLT) | 0 | 1 | 0 write to reg | 0 |
|xori | 0010011| 100 |NA| 00 | 1 | 0110 (XOR) | 0 | 1 | 0 write to reg | 0 |
|srli | 0010011 | 101 |0000000| 1 | 1 |  | 0 | 1 | 0 write to reg | 0 |
|srai | 0010011| 101 |0100000| 00 | 1 | 0110 (XOR) | 0 | 1 | 0 write to reg | 0 |
|ori | 0010011| 110 |NA| 00 | 1 | 0110 (XOR) | 0 | 1 | 0 write to reg | 0 |
|andi | 0010011| 111 |NA| 00 | 1 | 0110 (XOR) | 0 | 1 | 0 write to reg | 0 |






### LB OPcode = 0000011, Func3 = 000
Load byte

### LH OPcode = 0000011, Func3 = 001
Load half word

### LW OPcode = 0000011, Func3 = 010
Load word

### LBU OPcode = 0000011, Func3 = 100
Load byte unsigned

### LHU OPcode = 0000011, Func3 = 101
Load half word unsigned

### ADDI OPcode = 0010011, Func3 = 000
Add Immediate

### SLLI OPcode = 0010011, Func3 = 001
Shift left logical 

### SLTI OPcode = 0010011, Func3 = 010
Shift less than immediate

### SLTIU OPcode = 0010011, Func3 = 011
Shift less than Immediate unsign

### XORI OPcode = 0010011, Func3 = 100
Xor Immediate

### SRLI OPcode = 0010011, Func3 =101
Shift Right Logical Immediate

### SRAI OPcode = 0010011, Func3 = 101, Func7 =0100000
Shift Right Arithmetic Immediate

### ORI OPcode = 0010011, Func3 = 110
Or Immediate

### ANDI OPcode = 0010011, Func3 = 111
And Immediate

### JALR OPcode = 1100111, Func3 = 000
Jump and Link register

## U type instructions

### LUI

## S type instructions

### SB

### SH

## R type instructions

Here are the specific ALU control signals for the different arithmetic operations


|Name| OPCode | Func3 | Func7| ImmSrc | ALUSrc | ALUControl | PCSrc | RegWrite | MemWrite | ResultSrc |
|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
| ADD  | 0110011 | 000 |0000000| NA | 0 use SrcB | 0000 (ADD) |  0  | 1|0| 0 use ALUResult|
| SUB  | 0110011 | 000 |0100000| NA | 0 use SrcB | 0001 (sub) | 0 | 1 | 0|0 use ALUResult|
| SLL  | 0110011  | 001 |0000000| NA | 0 use SrcB | 1001 | 0  | 1| 0|0 use ALUResult|
| SLT  | 0110011  | 010 |0000000| NA | 0 use SrcB | 101 | 0  | 1 | 0|0 use ALUResult|
| SLTU  | 0110011  | 011 |0000000| NA | 0 use SrcB | 101 | 0  | 1 | 0|0 use ALUResult|
| XOR  | 0110011  | 100 |0000000| NA | 0 use SrcB | 110 | 0  | 1 | 0 |0 use ALUResult|
| SRL  | 0110011  | 101 |0000000| NA | 0 use SrcB | 111 | 0  | 1 | 0 |0 use ALUResult|
| SRA  | 0110011  | 101 |0100000| NA | 0 use SrcB | 1000 | 0  | 1 | 0 |0 use ALUResult|
| OR  | 0110011  | 110 |0000000| NA | 0 use SrcB | 011 | 0  | 1 | 0 |0 use ALUResult|
| AND  | 0110011  | 111 |0000000| NA | 0 use SrcB | 010 | 0  | 1 | 0 |0 use ALUResult|


|ALU control signal 3 bits | Function |
|-----------|-----------|
|0000|Add|
|0001|Sub|
|0010|AND|
|0011|OR|
|0101|SLT|
|0110|XOR|
|0111|SRL|
|1000|SRA|
|1001|SLL|





NO immediates are being used in this instruction. ALUSrc will be set to 0 -> ALUSrc = 0

### ADD OPcode: 0110011, Func3: 000, Func7: 0000000

rd = rs1 + rs2


#### Order of Operations

1) Read the PC
2) Get the instruction from the Instruction Memory
3) Decode the instruction using the control unit
4) The Main Control unit gets the following signals: ImmSrc = 0, RegWrite = 1, MemWrite = 0, ALUSrc = 0 PCSrc = 0
5) SrcA will get RD1 from the RF
5) The ALUSrc = 0 Multiplexer will decide to take make SrcB = RD2. 
6) The ALUControl signal will be given  to execute the addition ALUControl = 000 Rs1 + Rs2
7) Result is gotten from the ALUResult 32bit result bus, and a ResultSrc mux is checked to 0 to allow it to go to the WD3
8) We write the answer back to the register specified in rd.
9) Finally we increment the PC by passing it through the PCPlus4 module 

#### Modules in use
- Main Decoder
- ALU Decoder
- Instruction Memory
- Register File
- ALUSrc Control Mux
- ALU
- ResultSRC Mux
- PCPlus 4 Mux
- PCSrc Control mux

### SUB OPcode: 0110011, Func3: 000, Func7: 0100000

rd = rs1 - rs2


#### Order of Operations

1) Read the PC
2) Get the instruction from the Instruction Memory
3) Decode the instruction using the control unit
4) The Main Control unit gets the following signals: ImmSrc = 0, RegWrite = 1, MemWrite = 0, ALUSrc = 0 PCSrc = 0
5) SrcA will get RD1 from the RF
5) The ALUSrc = 0 Multiplexer will decide to take make SrcB = RD2. 
6) The ALUControl signal will be given  to execute the addition ALUControl = 001 Rs1 - Rs2
7) Result is gotten from the ALUResult 32bit result bus, and a ResultSrc mux is checked to 0 to allow it to go to the WD3
8) We write the answer back to the register specified in rd.
9) Finally we increment the PC by passing it through the PCPlus4 module 

#### Modules in use
- Main Decoder
- ALU Decoder
- Instruction Memory
- Register File
- ALUSrc Control Mux
- ALU
- ResultSRC Mux
- PCPlus 4 Mux
- PCSrc Control mux


### SLL OPcode: 0110011, Func3: 001, Func7: 0000000

shift logical left
rd = rs1 << rs2
implement via binary multiplication?


#### Order of Operations

1) Read the PC
2) Get the instruction from the Instruction Memory
3) Decode the instruction using the control unit
4) The Main Control unit gets the following signals: ImmSrc = 0, RegWrite = 1, MemWrite = 0, ALUSrc = 0 PCSrc = 0
5) SrcA will get RD1 from the RF
5) The ALUSrc = 0 Multiplexer will decide to take make SrcB = RD2. 
6) The ALUControl signal will be given  to execute the addition ALUControl = ??? Rs1 * 2^Rs2
7) Result is gotten from the ALUResult 32bit result bus, and a ResultSrc mux is checked to 0 to allow it to go to the WD3
8) We write the answer back to the register specified in rd.
9) Finally we increment the PC by passing it through the PCPlus4 module 

#### Modules in use
- Main Decoder
- ALU Decoder
- Instruction Memory
- Register File
- ALUSrc Control Mux
- ALU
- ResultSRC Mux
- PCPlus 4 Mux
- PCSrc Control mux

### SLT OPcode: 0110011, Func3: 010, Func7: 0000000

Set less than
if rs1 < rs2 rd = 1
if rs1 >= rs2 rd = 0
implemented via subtraction and check the result


#### Order of Operations

1) Read the PC
2) Get the instruction from the Instruction Memory
3) Decode the instruction using the control unit
4) The Main Control unit gets the following signals: ImmSrc = 0, RegWrite = 1, MemWrite = 0, ALUSrc = 0 PCSrc = 0
5) SrcA will get RD1 from the RF
5) The ALUSrc = 0 Multiplexer will decide to take make SrcB = RD2. 
6) The ALUControl signal will be given  to execute the addition ALUControl = 101 Rs1 < Rs2
7) Result is gotten from the ALUResult 32bit result bus, and a ResultSrc mux is checked to 0 to allow it to go to the WD3
8) We write the answer back to the register specified in rd.
9) Finally we increment the PC by passing it through the PCPlus4 module 

#### Modules in use
- Main Decoder
- ALU Decoder
- Instruction Memory
- Register File
- ALUSrc Control Mux
- ALU
- ResultSRC Mux
- PCPlus 4 Mux
- PCSrc Control mux

### SLTU: 0110011, Func3: 011, Func7: 0000000

Set less than unsigned
if rs1 < rs2 rd = 1
if rs1 >= rs2 rd = 0
implemented via subtraction and check the result


#### Order of Operations

1) Read the PC
2) Get the instruction from the Instruction Memory
3) Decode the instruction using the control unit
4) The Main Control unit gets the following signals: ImmSrc = 0, RegWrite = 1, MemWrite = 0, ALUSrc = 0 PCSrc = 0
5) SrcA will get RD1 from the RF
5) The ALUSrc = 0 Multiplexer will decide to take make SrcB = RD2. 
6) The ALUControl signal will be given  to execute the addition ALUControl = 101 Rs1 < Rs2
7) Result is gotten from the ALUResult 32bit result bus, and a ResultSrc mux is checked to 0 to allow it to go to the WD3
8) We write the answer back to the register specified in rd.
9) Finally we increment the PC by passing it through the PCPlus4 module 

#### Modules in use
- Main Decoder
- ALU Decoder
- Instruction Memory
- Register File
- ALUSrc Control Mux
- ALU
- ResultSRC Mux
- PCPlus 4 Mux
- PCSrc Control mux

### XOR OPcode: 0110011, Func3: 100, Func7: 0000000
XOR operator ^ rd = rs1 ^ rs2


#### Order of Operations

1) Read the PC
2) Get the instruction from the Instruction Memory
3) Decode the instruction using the control unit
4) The Main Control unit gets the following signals: ImmSrc = 0, RegWrite = 1, MemWrite = 0, ALUSrc = 0 PCSrc = 0
5) SrcA will get RD1 from the RF
5) The ALUSrc = 0 Multiplexer will decide to take make SrcB = RD2. 
6) The ALUControl signal will be given  to execute the addition ALUControl = 110 Rs1 ^ Rs2
7) Result is gotten from the ALUResult 32bit result bus, and a ResultSrc mux is checked to 0 to allow it to go to the WD3
8) We write the answer back to the register specified in rd.
9) Finally we increment the PC by passing it through the PCPlus4 module 

#### Modules in use
- Main Decoder
- ALU Decoder
- Instruction Memory
- Register File
- ALUSrc Control Mux
- ALU
- ResultSRC Mux
- PCPlus 4 Mux
- PCSrc Control mux

### SRL OPcode: 0110011, Func3: 101, Func7: 0000000

shift logical right
rd = rs1 >> $rs2_{4:0}$
implement via binary multiplication?


#### Order of Operations

1) Read the PC
2) Get the instruction from the Instruction Memory
3) Decode the instruction using the control unit
4) The Main Control unit gets the following signals: ImmSrc = 0, RegWrite = 1, MemWrite = 0, ALUSrc = 0 PCSrc = 0
5) SrcA will get RD1 from the RF
5) The ALUSrc = 0 Multiplexer will decide to take make SrcB = RD2. 
6) The ALUControl signal will be given  to execute the addition ALUControl = 111 rs1 >> $rs2_{4:0}$
7) Result is gotten from the ALUResult 32bit result bus, and a ResultSrc mux is checked to 0 to allow it to go to the WD3
8) We write the answer back to the register specified in rd.
9) Finally we increment the PC by passing it through the PCPlus4 module 

#### Modules in use
- Main Decoder
- ALU Decoder
- Instruction Memory
- Register File
- ALUSrc Control Mux
- ALU
- ResultSRC Mux
- PCPlus 4 Mux
- PCSrc Control mux



### SRA OPcode: 0110011, Func3: 101, Func7: 0100000
shift right arithmetic
rd = rs1 >>> $rs2_{4:0}$
implement via binary multiplication?


#### Order of Operations

1) Read the PC
2) Get the instruction from the Instruction Memory
3) Decode the instruction using the control unit
4) The Main Control unit gets the following signals: ImmSrc = 0, RegWrite = 1, MemWrite = 0, ALUSrc = 0 PCSrc = 0
5) SrcA will get RD1 from the RF
5) The ALUSrc = 0 Multiplexer will decide to take make SrcB = RD2. 
6) The ALUControl signal will be given  to execute the addition ALUControl = 1000 rs1 >>> $rs2_{4:0}$
7) Result is gotten from the ALUResult 32bit result bus, and a ResultSrc mux is checked to 0 to allow it to go to the WD3
8) We write the answer back to the register specified in rd.
9) Finally we increment the PC by passing it through the PCPlus4 module 

#### Modules in use
- Main Decoder
- ALU Decoder
- Instruction Memory
- Register File
- ALUSrc Control Mux
- ALU
- ResultSRC Mux
- PCPlus 4 Mux
- PCSrc Control mux

### OR OPcode: 0110011, Func3: 110, Func7: 0000000
OR

rd = rs1 | rs2

#### Order of Operations

1) Read the PC
2) Get the instruction from the Instruction Memory
3) Decode the instruction using the control unit
4) The Main Control unit gets the following signals: ImmSrc = 0, RegWrite = 1, MemWrite = 0, ALUSrc = 0 PCSrc = 0
5) SrcA will get RD1 from the RF
5) The ALUSrc = 0 Multiplexer will decide to take make SrcB = RD2. 
6) The ALUControl signal will be given  to execute the addition ALUControl = 011 Rs1 | Rs2
7) Result is gotten from the ALUResult 32bit result bus, and a ResultSrc mux is checked to 0 to allow it to go to the WD3
8) We write the answer back to the register specified in rd.
9) Finally we increment the PC by passing it through the PCPlus4 module 

#### Modules in use
- Main Decoder
- ALU Decoder
- Instruction Memory
- Register File
- ALUSrc Control Mux
- ALU 
- ResultSRC Mux
- PCPlus 4 Mux
- PCSrc Control mux

### AND OPcode: 0110011, Func3: 111, Func7: 0000000
AND

rd = rs1 & rs2

#### Order of Operations

1) Read the PC
2) Get the instruction from the Instruction Memory
3) Decode the instruction using the control unit
4) The Main Control unit gets the following signals: ImmSrc = 0, RegWrite = 1, MemWrite = 0, ALUSrc = 0 PCSrc = 0
5) SrcA will get RD1 from the RF
5) The ALUSrc = 0 Multiplexer will decide to take make SrcB = RD2. 
6) The ALUControl signal will be given  to execute the and comparison ALUControl = 010 Rs1 & Rs2
7) Result is gotten from the ALUResult 32bit result bus, and a ResultSrc mux is checked to 0 to allow it to go to the WD3
8) We write the answer back to the register specified in rd.
9) Finally we increment the PC by passing it through the PCPlus4 module 

#### Modules in use
- Main Decoder
- ALU Decoder
- Instruction Memory
- Register File
- ALUSrc Control Mux
- ALU
- ResultSRC Mux
- PCPlus 4 Mux
- PCSrc Control mux
