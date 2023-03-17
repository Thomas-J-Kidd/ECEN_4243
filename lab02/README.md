# Update as of March 16th 2023


Thomas
-------
## Updates: 

### Created official backups. 

riscv_single_working_backup.do
riscv_single_working_backup.sv

##### These are the working backup files as of right now. 


### Testing files

riscv_single_testing_copy.sv
riscv_single.do 

##### Theses are the testing files as of right now. 


### Working on the load word, load half word, and load byte 

In the riscv_single_testing_copy.sv I created a module called loading module. The goal of this module is to help convert the loading input into either word, half word, or byte form.It takes 3 inputs and gives one output. 

Input Logic:
- ReadData: This is what we will send out eventually. Just depends if we want to send a byte, half word, or the entire word. 
- func3: this helps us decide if we are doing lb, lh, lw
- ResultSrc: this helps us decide if we are doing a load instruction

Output logic: 
- out: this will be the final output. 


#### How it works

Essentially we have 3 inputs connect into a big mux called choose_b_h_w_mux. This mux takes 3 input in. lbyte, halfword, and ReadData. lbyte and halfword come from 2 other muxes above that are used to segment the inputs of the ReadData value into bytes and halfwords. 

the choose_b_h_w_mux decided if the instruction is lb, lh, or lw. It does this through using func3. 
The trouble we are running into is how to select the choose_b_h_w_mux variable. Using simply just func3 does not work because other instructions func3 will also come through. Thats why I started using ResultSrc. ResultSrc will always be 01 for any load instruction. Becaus of this I am trying to do a choosing statement starting line 253.  THIS DOES NOT WORK CURRENTLY. 

### ISSUE

We are having problems choosing the correct output value. We need to only choose the variable "out" in the loading module when we are using a load instruction. Every other time we want to let the ***"ReadData"*** variable through. This is where the issue is. Line 253 error: 

```
# ** Error: (vlog-13069) riscv_single_testing_copy.sv(258): near "case": syntax error, unexpected case.
# ** Error: riscv_single_testing_copy.sv(277): (vlog-2730) Undefined variable: 'a'.
# ** Error: riscv_single_testing_copy.sv(277): (vlog-2730) Undefined variable: 'b'.
```

This is the current error. Tried some things but didnt work yet. 






## TODO:

- finish loading instructions
- implement sw, sh, sb
- implement jal, jalr, lui, the weird instructions. 
- test all arrithemtic instructions. 




- 
