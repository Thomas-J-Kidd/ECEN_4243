module stimulus ();
    logic clk;
    logic we3;
    logic [4:0] ra1, ra2, wa3; 
    logic [31:0] wd3;
    logic [31:0] rd1, rd2;

    integer handle3;
    integer desc3;

// Instantiate DUT
regfile dut (clk, we3, ra1, ra2, wa3, wd3, rd1, rd2);

   // Setup the clock to toggle every 1 time units 
   initial 
        begin	
	    clk = 1'b1;
	    forever #5 clk = ~clk;
        end

    initial
        begin
	    // Gives output file name
	    handle3 = $fopen("test_regfile.out");
	    // Tells when to finish simulation
	    #500 $finish;		
        end

    always 
        begin
	    desc3 = handle3;
	    #5 $fdisplay(desc3, "%b", rd1);
        end   


    initial 
        begin      
        
        
        


        // showing writing data works correctly
        #5 we3 = 1'b1;
        #0 wa3 = 5'b00010;
        #0 wd3 = 32'h00000015;

        // writing again
        #10 we3 = 1'b1;
        #0 wa3 = 5'b00011;
        #0 wd3 = 32'h00000016;


        // showing that reading data works combinationally
        #2 ra1 = 5'b00010;
        #2 ra2 = 5'b00011;
    
       

        end

endmodule