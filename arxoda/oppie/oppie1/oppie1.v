//////////
//
// /libsf/li386/oppie/oppie-1/oppie1.v
//
//////
// Version 0.01
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Nov.23.2014
//////
// Change log:
//     Nov.17.2014 - Initial creation
//////
//
// This software is released as Liberty Software under a Repeat License, as governed
// by the Public Benefit License v1.0 or later (PBL).
//
// You are free to use, copy, modify and share this software.  However, it can only
// be released under the PBL version indicated, and every project must include a copy
// of the pbl.txt document for its version as is at http://www.libsf.org/licenses/.
//
// For additional information about this project, or to view the license, see:
//
//     http://www.libsf.org/
//     http://www.libsf.org/licenses/
//     http://www.visual-freepro.org/vjr/indexmain.html
//     http://www.visual-freepro.org/wiki/index.php/PBL
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//////
//
// Oppie-1 -- Simple CPU able to execute these instructions:
//
//		ASM Instruction			Bytes		Opcode Bit Encoding (x=unused)
//		-------------------		------		------------------------------
//											* Register encodings are 2 bits
//		mov   reg8,[address]	2			000.00.000:00000000
//		mov   reg8,reg8			1			001.x.00.00	(dest,src)
//		add   reg8,reg8			1			0100.00.00
//		adc   reg8,reg8			1			0110.00.00
//		sub   reg8,reg8			1			0101.00.00
//		sbb   reg8,reg8			1			0111.00.00
//		mov   [address],reg8	2			100.00.000:00000000
//		cmp   reg8,reg8			1			101.x.00.00	(left,right)
//		jz    +/- 1KB			2			110.xx.s.00:00000000
//		jmp   +/- 1KB			2			111.xx.s.00:00000000 
//
// Using this environment:
//
//		8-bit Regs			Flags			Memory
//		---------------		---------		-----------
//		r1 -- 00000000		zero?			2 Kilobytes
//		r2 -- 00000000		carry?
//		r3 -- 00000000
//		r4 -- 00000000
//
//		ip -- 00000000		// Instruction pointer
//
//////
//
// Compiled in Icarus Verilog 0.9.7.
// Using GTKWave for validation.
//
//////
//
// Note:  Incomplete and untested as of Nov.23.2014.
//
//////


//////////
// Added to allow compilation in both iverilog, and Quartus-II:
//////
//	`define _ICARUS_VERILOG_COMPILATION




//////////
//
// Top-level module:  oppie1()
//
//////
`ifdef _ICARUS_VERILOG_COMPILATION
	module oppie1();
`else
	module oppie1(output [0:0] added_to_make_the_synthesizer_software_recognize_this_as_top_level_logic);
`endif

	//////////
	// Oppie operational mechanics
	//////
		reg					clk;				// Clock signal
		reg					i_halt;				// Instruction halt
		
		// Flags between pipe stages
		reg					ok_i_fetch;			// Okay to fetch the next instruction?
		reg					ok_i_decode;		// Okay to decode the next instruction?
		reg					ok_d_read;			// Okay to read data?
		reg					ok_i_process;		// Okay to process the instruction?
		reg					ok_d_write;			// Okay to write out data?
		
		// Valid pipe stage (used for refilling after branch)
		reg		[2:0]		pipe_valid;
		reg					ok_pipe_stage2;		// Indicates if stage-2 is okay
		reg					ok_pipe_stage3;		// Indicates if stage-3 is okay
		reg					ok_pipe_stage4;		// Indicates if stage-4 is okay
		
		`define STAGE0		3'b000
		`define STAGE1		3'b001
		`define STAGE2		3'b010
		`define STAGE3		3'b011
		`define STAGE4		3'b100
	
	
	//////////
	// Oppie register state
	//////
		reg		[1:0]		flags;				// bit-0=zero? bit-1=carry?
		reg		[7:0]		r1;					// 8-bit R1 general purpose register
		reg		[7:0]		r2;					// 8-bit R1 general purpose register
		reg		[7:0]		r3;					// 8-bit R1 general purpose register
		reg		[7:0]		r4;					// 8-bit R1 general purpose register
		reg		[10:0]		ip;					// 11-bit IP instruction pointer (2 KB)
		
		`define R1			2'b00
		`define R2			2'b01
		`define R3			2'b10
		`define R4			2'b11
		
		`define CARRY		1'b1
		`define ZERO		1'b0


	//////////
	// Memory write
	//////
		reg		[10:0]		p5_write_address;
		reg		[7:0]		p5_write_data;

	
	//////////
	// Memory reads
	//////
		reg					read1_enable;		// Instruction 1 (read in stage 1)
		reg		[10:0]		read1_address;
		wire	[7:0]		read1_data;
	  
		reg					read2_enable;		// Instruction 2 (read in stage 1)
		reg		[10:0]		read2_address;
		wire	[7:0]		read2_data;
	  
		reg					read3_enable;		// Insruction 3 (read in stage 1)
		reg		[10:0]		read3_address;
		wire	[7:0]		read3_data;
	  
		reg					read4_enable;		// Data 1 (read in stage 3)
		reg		[10:0]		read4_address;
		wire	[7:0]		read4_data;
	
	
	//////////
	// Queues for pipe stages
	//////
		reg		[10:0]		p1_ip_address;		// ip address as of the instruction fetch
		
		reg		[7:0]		p2_i_data1;			// i-data 1 read from stage 1
		reg		[7:0]		p2_i_data2;			// i-data 2 read from stage 1
		reg		[1:0]		p2_reg_src;			// Register source for stage 4
		reg		[1:0]		p2_reg_dst;			// Register destination for stage 4
		reg					p2_read_ok;			// Is it okay to read data in stage 3
		reg		[10:0]		p2_read_address;	// Read address for stage 3
		reg					p2_write_ok;		// Is it okay to write data in stage 5
		reg		[10:0]		p2_write_address;	// Write address for stage 5, i_write
		reg		[9:0]		p2_ip_sign;			// Direction for jump targets stage 4
		reg		[9:0]		p2_ip_delta;		// Delta for jump targets stage 4
		reg		[10:0]		p2_ip_address;		// ip of this instruction
		reg		[3:0]		p2_process_op;		// Operation to conduct for stage 4
		reg					p2_increment2;		// Should the instruction pointer be increased by 2?

		reg		[1:0]		p3_reg_src;			// Register source for stage 4
		reg		[1:0]		p3_reg_dst;			// Register destination for stage 4
		reg		[7:0]		p3_data;			// Data read in stage 3
		reg					p3_write_ok;		// Is it okay to write data in stage 5
		reg		[10:0]		p3_write_address;	// Write address for stage 5, i_write
		reg		[9:0]		p3_ip_sign;			// Direction for jump targets stage 4
		reg		[9:0]		p3_ip_delta;		// Delta for jump targets stage 4
		reg		[10:0]		p3_ip_address;		// ip of this instruction
		reg		[3:0]		p3_process_op;		// Operation to conduct for stage 4

		reg					p4_new_ip_valid;	// If valid, the new IP is set
		reg		[10:0]		p4_new_ip;			// A new IP address for a branch in stage 4
		reg		[1:0]		p4_reg_src;			// Register source for stage 4
		reg		[1:0]		p4_reg_dst;			// Register destination for stage 4
		reg		[7:0]		p4_data;			// Data read in stage 3
		reg		[7:0]		p4_result;			// Computed result stage 4
		reg					p4_write_ok;		// Is it okay to write data in stage 5
		reg		[10:0]		p4_write_address;	// Write address for stage 5, i_write
		reg		[9:0]		p4_ip_sign;			// Direction for jump targets stage 4
		reg		[9:0]		p4_ip_delta;		// Delta for jump targets stage 4
		reg		[3:0]		p4_process_op;		// Operation to conduct for stage 4
		reg					p4_carry;			// Used for common operations

		reg					p5_write_ok;		// Is it okay to write data in stage 5
	
	
	//////////
	// Process ops in stage-4
	//////
		reg		[3:0]		i_process_op [2:0];
		
		`define MOV_FROM_MEM8	4'b0000		// 0
		`define MOV				4'b0001		// 1
		`define ADD				4'b0010		// 2
		`define ADC				4'b0011		// 3
		`define SUB				4'b0100		// 4
		`define SBB				4'b0101		// 5
		`define MOV_TO_MEM8		4'b0110		// 6
		`define CMP				4'b0111		// 7
		`define JZ				4'b1000		// 8
		`define JMP				4'b1001		// 9
	

	//////////
	//
	// Instantiate i-data and d-data:
	//		BITS_DATA		= 8
	//		BITS_ADDRESS	= 11
	//		SIZE_RAM		= 2048		// BITS_DATA count
	//
	//////
	  ram_1_4 #(8, 11, 2048)	i_d_data(	.write_enable	(p5_write_ok		&&	ok_d_write	&&	~i_halt),
											.write_address	(p5_write_address),
											.write_data		(p5_write_data),
											
											.read1_enable	(read1_enable		&&	ok_i_fetch	&&	~i_halt),
											.read1_address	(read1_address),
											.read1_data		(read1_data),
											
											.read2_enable	(read2_enable		&&	ok_i_fetch	&&	~i_halt),
											.read2_address	(read2_address),
											.read2_data		(read2_data),
											
											.read3_enable	(read3_enable		&&	ok_i_fetch	&&	~i_halt),
											.read3_address	(read3_address),
											.read3_data		(read3_data),

											.read4_enable	(read4_enable		&&	ok_d_read	&&	ok_pipe_stage3	&& ~i_halt),
											.read4_address	(read4_address),
											.read4_data		(read4_data)		);


	//////////
	//
	// Instantiate adder
	//
	//////
		reg		[7:0]	add_v1;			// Value 1
		reg		[7:0]	add_v2;			// Value 2
		reg		[1:0]	add_dst;		// Destination register

		// Will be computed on the negative edge of the clock
		add_adc_reg8 aar8(.v1(add_v1), .v2(add_v2), .carry_in(p4_carry), .dst_reg(add_dst));


	//////////
	//
	// Instantiate subtractor
	//
	//////
		reg		[7:0]	sub_v1;			// Value 1
		reg		[7:0]	sub_v2;			// Value 2
		reg		[1:0]	sub_dst;		// Destination register

		// Will be computed on the negative edge of the clock
		sub_sbb_reg8 ssr8(.v1(sub_v1), .v2(sub_v2), .borrow_in(p4_carry), .dst_reg(sub_dst));


	//////////
	//
	// Initial setup
	// Set clock and halt instruction processing
	//
	//////
		initial begin
			bootup;
`ifndef _ICARUS_VERILOG_COMPILATION
			added_to_make_the_synthesizer_software_recognize_this_as_top_level_logic <= 1'b1;
`endif
		end


	//////////
	//
	// Clock signal
	//
	//////
		always begin
			#10 clk = ~clk;
		end
	
	
	//////////
	//
	// 1: i-fetch
	//
	//////
		always @(posedge clk) begin
			i_fetch;	// Retrieve the instruction bytes
		end
	
	
	//////////
	//
	// 2: i-decode
	//
	//////
		always @(posedge clk) begin
			i_decode;	// Decode the loaded instruction
		end
	
	
	//////////
	//
	// 3: d-read
	//
	//////
		always @(posedge clk) begin
			d_read;
		end
	
	
	//////////
	//
	// 4: Process
	//
	//////
		always @(posedge clk) begin
			i_process;
		end
	
	
	//////////
	//
	// 5: d-write
	//
	//////
		always @(posedge clk) begin
			d_write;
		end
	
	
	//////////
	//
	// Push between pipe stages
	//
	//////
		always @(negedge clk) begin
			if (i_halt == 0) begin
				push_pipe_data;
			end
		end
	
	
	//////////
	//
	// Read the next instruction
	//
	//////
		task i_fetch;
			begin
				// Read the next instruction unless we're halted
				if (i_halt == 0 && ok_i_fetch) begin
					// Raise the read signal and wait a tick
					read1_enable	= 1'b1;
					read2_enable	= 1'b1;
					p1_ip_address	= ip;			// Indicate the ip address
					read1_address	= ip;			// Read from the IP address
					read2_address	= ip + 11'd1;	// Read from the IP address + 1
					read3_address	= ip + 11'd2;	// Read from the IP address + 2
				end
			end
		endtask
	
	
	//////////
	//
	// Decode fetched instruction
	//
	//////
		task i_decode;
			begin
				if (i_halt == 0 && ok_i_decode && ok_pipe_stage2) begin
					if (read1_data[7:5] == 3'b000) begin
						// mov  reg8,[address]
						// 2 opcode bytes
						// 000.00.000:00000000 = 000.reg8_dst.address_src
						p2_reg_dst				<= p2_i_data1[4:3];
						p2_read_address[10:8]	<= p2_i_data1[2:0];
						p2_read_address[7:0]	<= p2_i_data2[7:0];
						p2_read_ok				<= 1;
						p2_write_ok				<= 1;
						p2_process_op[3:0]		<= `MOV_FROM_MEM8;
						p2_increment2			<= 1;
			
					end else if (read1_data[7:5] == 3'b001) begin
						// mov  reg8,reg8
						// 1 opcode byte
						// 001.x.00.00 = 001.x.reg8_dst.reg8_src
						p2_reg_dst				<= p2_i_data1[3:2];
						p2_reg_src				<= p2_i_data1[1:0];
						p2_read_ok				<= 0;
						p2_write_ok				<= 0;
						p2_process_op[3:0]		<= `MOV;
						p2_increment2			<= 0;
			  
					end else if (read1_data[7:4] == 4'b0100) begin
						// add  reg8,reg8
						// 1 opcode byte
						// 0100.00.00 = 010.x.reg8_dst.reg8_src
						p2_reg_dst				<= p2_i_data1[3:2];
						p2_reg_src				<= p2_i_data1[1:0];
						p2_read_ok				<= 0;
						p2_write_ok				<= 0;
						p2_process_op[3:0]		<= `ADD;
						p2_increment2			<= 0;
			  
					end else if (read1_data[7:4] == 4'b0110) begin
						// adc  reg8,reg8
						// 1 opcode byte
						// 0110.00.00 = 011.x.reg8_dst.reg8_src
						p2_reg_dst				<= p2_i_data1[3:2];
						p2_reg_src				<= p2_i_data1[1:0];
						p2_read_ok				<= 0;
						p2_write_ok				<= 0;
						p2_process_op[3:0]		<= `ADC;
						p2_increment2			<= 0;
			  
					end else if (read1_data[7:4] == 4'b0101) begin
						// sub  reg8,reg8
						// 1 opcode byte
						// 0101.00.00 = 010.x.reg8_dst.reg8_src
						p2_reg_dst				<= p2_i_data1[3:2];
						p2_reg_src				<= p2_i_data1[1:0];
						p2_read_ok				<= 0;
						p2_write_ok				<= 0;
						p2_process_op[3:0]		<= `SUB;
						p2_increment2			<= 0;
			  
					end else if (read1_data[7:4] == 4'b0111) begin
						// sbb  reg8,reg8
						// 1 opcode byte
						// 0111.00.00 = 011.x.reg8_dst.reg8_src
						p2_reg_dst				<= p2_i_data1[3:2];
						p2_reg_src				<= p2_i_data1[1:0];
						p2_read_ok				<= 0;
						p2_write_ok				<= 0;
						p2_process_op[3:0]		<= `SBB;
						p2_increment2			<= 0;
			  
					end else if (read1_data[7:5] == 3'b100) begin
						// mov  [address],reg8
						// 2 opcode bytes
						// 100.00.000:00000000 = 100.reg8_src.address_dst
						p2_reg_src				<= p2_i_data1[4:3];
						p2_write_address[10:8]	<= p2_i_data1[2:0];
						p2_write_address[7:0]	<= p2_i_data2[7:0];
						p2_read_ok				<= 0;
						p2_write_ok				<= 1;
						p2_process_op[3:0]		<= `MOV_TO_MEM8;
						p2_increment2			<= 1;
			  
					end else if (read1_data[7:5] == 3'b101) begin
						// cmp  reg8,reg8
						// 1 opcode byte
						// 101.x.00.00 = 101.x.reg8_dst.reg8_src
						p2_reg_dst				<= p2_i_data1[3:2];
						p2_reg_src				<= p2_i_data1[1:0];
						p2_read_ok				<= 0;
						p2_write_ok				<= 0;
						p2_process_op[3:0]		<= `CMP;
						p2_increment2			<= 0;
			  
					end else if (read1_data[7:5] == 3'b110) begin
						// jz   +/- 1KB
						// 2 opcode bytes
						// 110.xx.s.00:00000000 = 110.xx.sign.delta
						p2_read_ok				<= 0;
						p2_write_ok				<= 0;
						p2_ip_sign[0]			<= p2_i_data1[2:2];
						p2_ip_delta[9:8]		<= p2_i_data1[1:0];
						p2_ip_delta[7:0]		<= p2_i_data2[7:0];
						p2_process_op[3:0]		<= `JZ;
						p2_increment2			<= 1;
			  
					end else /*if (read1_data[7:5] == 3'b111)*/ begin
						// jmp  +/- 1KB
						// 2 opcode bytes
						// 111.xx.s.00:00000000 = 111.xx.sign.delta
						p2_read_ok				<= 0;
						p2_write_ok				<= 0;
						p2_ip_sign[0]			<= p2_i_data1[2:2];
						p2_ip_delta[9:8]		<= p2_i_data1[1:0];
						p2_ip_delta[7:0]		<= p2_i_data2[7:0];
						p2_process_op[3:0]		<= `JMP;
						p2_increment2			<= 1;
					end
				end
			end
		endtask
	
	
	//////////
	//
	// Read data for the instruction
	//
	//////
		task d_read;
			begin
//				if (i_halt == 0 && ok_d_read && ok_pipe_stage3) begin
//					// This stage happens in the i_d_data() ram object
//				end
			end
		endtask
	
	
	//////////
	//
	// Process the instruction
	//
	//////
		task i_process;
			begin
				if (i_halt == 0 && ok_i_process && ok_pipe_stage4) begin
					// ok_d_read is set in i_decode based on the instruction encoding
					if (p4_process_op == `MOV_FROM_MEM8) begin
						mov_from_mem8;
					
					end else if (p4_process_op == `MOV) begin
						// The p4_reg_src contents need moved into the p4_reg_dst
						mov_reg8_to_reg8;
					
					end else if (p4_process_op == `ADD) begin
						// The p4_reg_src contents need added into the p4_reg_dst
						p4_carry = 1'b0;
						add_adc_reg8_to_reg8;
					
					end else if (p4_process_op == `ADC) begin
						// The p4_reg_src contents need added-with-carry into the p4_reg_dst
						p4_carry = flags[`CARRY:`CARRY];
						add_adc_reg8_to_reg8;
					
					end else if (p4_process_op == `SUB) begin
						// The p4_reg_src contents need subtracted from the p4_reg_dst
						p4_carry = 1'b0;
						sub_sbb_reg8_to_reg8;
					
					end else if (p4_process_op == `SBB) begin
						// The p4_reg_src contents need subtracted from the p4_reg_dst
						p4_carry = flags[`CARRY:`CARRY];
						sub_sbb_reg8_to_reg8;
					
					end else if (p4_process_op == `MOV_TO_MEM8) begin
						// The p4_reg_src contents need moved into the write address
						// And if an upcoming read from that address is in the pipe, it needs updated as well
						mov_to_mem8;
					
					end else if (p4_process_op == `CMP) begin
						// The p4_reg_dst(left) contents need compared to the p4_reg_src(right)
						cmp_reg8_to_reg8;
					
					end else if (p4_process_op == `JZ) begin
						// We need to alter the instruction pointer if zero
						if (flags[`CARRY:`CARRY]) begin
							p4_new_ip_valid	= 1;
							if (p4_ip_sign) begin
								// Jumping negative
								p4_new_ip	= p3_ip_address - p4_ip_delta;
							
							end else begin
								// Jumping positive
								p4_new_ip	= p3_ip_address + p4_ip_delta;
							end
						end
					
					end else if (p4_process_op == `JMP) begin
						// We need to alter the instruction pointer unconditionally
						p4_new_ip_valid	= 1;
						if (p4_ip_sign) begin
							// Jumping negative
							p4_new_ip = p3_ip_address - p4_ip_delta;
						
						end else begin
							// Jumping positive
							p4_new_ip = p3_ip_address + p4_ip_delta;
						end
					end
				end
			end
		endtask
	
	
	//////////
	//
	// Write the data back out to main memory
	//
	//////
		task d_write;
			begin
//				if (i_halt == 0 && ok_d_write) begin
//					// This stage happens in the i_d_data() ram object
//				end
			end
		endtask
	
	
	//////////
	//
	// Move data from mem8 into the destination reg8
	//
	//////
		task mov_from_mem8;
			begin
				// The loaded data from stage 3 needs to be moved into the destination
				if (p4_reg_dst == `R1) begin
					r1 = p4_data;
				
				end else if (p4_reg_dst == `R2) begin
					r2 = p4_data;
				
				end else if (p4_reg_dst == `R3) begin
					r3 = p4_data;
				
				end else /*if (p4_reg_dst == `R4)*/ begin
					r4 = p4_data;
				end
			end
		endtask
	
	
	//////////
	//
	// Move data from reg8 to reg8
	//
	//////
		task mov_reg8_to_reg8;
			begin
				if (p4_reg_dst == `R1) begin
					/*if (p4_reg_src == `R1) begin
						// nop
						r1 = r1;
					end else*/ if (p4_reg_src == `R2) begin
						r1 = r2;
					end else if (p4_reg_src == `R3) begin
						r1 = r3;
					end /*else if (p4_reg_src == `R4)*/ begin
						r1 = r4;
					end
				
				end else if (p4_reg_dst == `R2) begin
					if (p4_reg_src == `R1) begin
						r2 = r1;
					end /*else if (p4_reg_src == `R2) begin
						// nop
						r2 = r2;
					end*/ else if (p4_reg_src == `R3) begin
						r2 = r3;
					end /*else if (p4_reg_src == `R4)*/ begin
						r2 = r4;
					end
				
				end else if (p4_reg_dst == `R3) begin
					if (p4_reg_src == `R1) begin
						r3 = r1;
					end else if (p4_reg_src == `R2) begin
						r3 = r2;
					end /*else if (p4_reg_src == `R3) begin
						// nop
						r3 = r3;
					end*/ /*else if (p4_reg_src == `R4)*/ begin
						r3 = r4;
					end
				
				end else /*if (p4_reg_dst == `R4)*/ begin
					if (p4_reg_src == `R1) begin
						r4 = r1;
					end else if (p4_reg_src == `R2) begin
						r4 = r2;
					end else if (p4_reg_src == `R3) begin
						r4 = r3;
					end /*else if (p4_reg_src == `R4) begin
						// nop
						r4 = r4;
					end*/
				end
			end
		endtask
	
	
	//////////
	//
	// ADD or ADC reg8 to reg8
	//
	//////
		task add_adc_reg8_to_reg8;
			begin
				add_dst = p4_reg_dst;
				if (p4_reg_dst == `R1) begin
					add_v1 = r1;
				end else if (p4_reg_dst == `R2) begin
					add_v1 = r2;
				end else if (p4_reg_dst == `R3) begin
					add_v1 = r3;
				end else /*if (p4_reg_dst == `R4)*/ begin
					add_v1 = r4;
				end
				
				if (p4_reg_src == `R1) begin
					add_v2 = r1;
				end else if (p4_reg_src == `R2) begin
					add_v2 = r2;
				end else if (p4_reg_src == `R3) begin
					add_v2 = r3;
				end /*else if (p4_reg_src == `R4)*/ begin
					add_v2 = r4;
				end
			end
		endtask
	
	
	//////////
	//
	// SUB or SBB reg8 to reg8
	//
	//////
		task sub_sbb_reg8_to_reg8;
			begin
				sub_dst = p4_reg_dst;
				if (p4_reg_dst == `R1) begin
					sub_v1 = r1;
				end else if (p4_reg_dst == `R2) begin
					sub_v1 = r2;
				end else if (p4_reg_dst == `R3) begin
					sub_v1 = r3;
				end else /*if (p4_reg_dst == `R4)*/ begin
					sub_v1 = r4;
				end
				
				if (p4_reg_src == `R1) begin
					sub_v2 = r1;
				end else if (p4_reg_src == `R2) begin
					sub_v2 = r2;
				end else if (p4_reg_src == `R3) begin
					sub_v2 = r3;
				end /*else if (p4_reg_src == `R4)*/ begin
					sub_v2 = r4;
				end
			end
		endtask
	
	
	//////////
	//
	// Move data to mem8 from the source reg8
	//
	//////
		task mov_to_mem8;
			begin
				// The register needs to be moved back out to main memory
				if (p4_reg_dst == `R1) begin
					p4_result = r1;
				
				end else if (p4_reg_dst == `R2) begin
					p4_result = r2;
				
				end else if (p4_reg_dst == `R3) begin
					p4_result = r3;
				
				end else /*if (p4_reg_dst == `R4)*/ begin
					p4_result = r4;
				end
			end
		endtask
	

	//////////
	//
	// Compare reg8 to reg8
	//
	//////
		task cmp_reg8_to_reg8;
			begin
				if (p4_reg_dst == `R1) begin
					if (p4_reg_src == `R1) begin
						flags[`ZERO:`ZERO] = 1'b1;
					end else if (p4_reg_src == `R2) begin
						flags[`ZERO:`ZERO] = (r1 == r2);
					end else if (p4_reg_src == `R3) begin
						flags[`ZERO:`ZERO] = (r1 == r3);
					end /*else if (p4_reg_src == `R4)*/ begin
						flags[`ZERO:`ZERO] = (r1 == r4);
					end
				
				end else if (p4_reg_dst == `R2) begin
					if (p4_reg_src == `R1) begin
						flags[`ZERO:`ZERO] = (r2 == r1);
					end else if (p4_reg_src == `R2) begin
						flags[`ZERO:`ZERO] = 1'b1;
					end else if (p4_reg_src == `R3) begin
						flags[`ZERO:`ZERO] = (r2 == r3);
					end /*else if (p4_reg_src == `R4)*/ begin
						flags[`ZERO:`ZERO] = (r2 == r4);
					end
				
				end else if (p4_reg_dst == `R3) begin
					if (p4_reg_src == `R1) begin
						flags[`ZERO:`ZERO] = (r3 == r1);
					end else if (p4_reg_src == `R2) begin
						flags[`ZERO:`ZERO] = (r3 == r2);
					end else if (p4_reg_src == `R3) begin
						flags[`ZERO:`ZERO] = 1'b1;
					end /*else if (p4_reg_src == `R4)*/ begin
						flags[`ZERO:`ZERO] = (r3 == r4);
					end
				
				end else /*if (p4_reg_dst == `R4)*/ begin
					if (p4_reg_src == `R1) begin
						flags[`ZERO:`ZERO] = (r4 == r1);
					end else if (p4_reg_src == `R2) begin
						flags[`ZERO:`ZERO] = (r4 == r2);
					end else if (p4_reg_src == `R3) begin
						flags[`ZERO:`ZERO] = (r4 == r3);
					end else if (p4_reg_src == `R4) begin
						flags[`ZERO:`ZERO] = 1'b1;
					end
				end
			end
		endtask
	
	
	//////////
	//
	// Transfer data between clocks for pipe stages
	//
	//////
		task push_pipe_data;
			begin
				
				//////////
				// If we have d-read memory in flight that's from our
				// write address, we need to update the value
				//////
					if (read4_address == p4_write_address) begin
						p3_data = p4_result;
					end
				
				
				//////////
				// Stage 4 to stage 5
				//////
					p5_write_ok			= p4_write_ok;
					p5_write_address	= p4_write_address;
					p5_write_data		= p4_result;
				
				
				//////////
				// Stage 3 to stage 4
				//////
					p4_reg_src			= p3_reg_src;
					p4_reg_dst			= p3_reg_dst;
					p4_data				= p3_data;
					p4_write_ok			= p3_write_ok;
					p4_write_address	= p3_write_address;
					p4_ip_sign			= p3_ip_sign;
					p4_ip_delta			= p3_ip_delta;
					p4_process_op		= p3_process_op;
				
				
				//////////
				// Stage 2 to stage 3
				//////
					p3_reg_src			= p2_reg_src;
					p3_reg_dst			= p2_reg_dst;
					p3_write_ok			= p2_write_ok;
					p3_write_address	= p2_write_address;
					p3_ip_sign			= p2_ip_sign;
					p3_ip_delta			= p2_ip_delta;
					p3_ip_address		= p2_ip_address;
					p3_process_op		= p2_process_op;
					read4_enable		= p2_read_ok;
					read4_address		= p2_read_address;
				
				
				//////////
				// Increase the instruction pointer if we're not the target of a recent branch
				//////
					if (p4_new_ip_valid == 1) begin
						// We branched, set the new target
						ip				= p4_new_ip;
//						p4_new_ip_valid	= 0;			// Lower the flag for the next pass
					
					end else begin
						// Continuing in normal processing
						if (pipe_valid != `STAGE0) begin
							if (p2_increment2) begin
								// This opcode consumed 2 bytes, so we need to adjust the opcodes in the pipe, and the ip address for next read
								ip				= ip + 11'd2;
								p2_ip_address	= p1_ip_address + 11'd1;
								
								// Adjust opcodes pre-fetched
								p2_i_data1		= read2_data;
								p2_i_data2		= read3_data;
								//p2_i_data3	= ignored
								
							
							end else begin
								// Incremented by 1 byte
								ip				= ip + 11'd1;
								p2_ip_address	= p1_ip_address;
								
								// Copy opcodes forward as they are:
								p2_i_data1		= read1_data;
								p2_i_data2		= read2_data;
							end
						end
					end
				
				
				//////////
				// Indicate which pipe entries are valid
				//////
					if (pipe_valid == `STAGE0) begin
						pipe_valid		= `STAGE1;
						ok_pipe_stage2	= 0;
						ok_pipe_stage3	= 0;
						ok_pipe_stage4	= 0;
						
					end else if (pipe_valid == `STAGE1) begin
						pipe_valid		= `STAGE2;
						ok_pipe_stage2	= 1;
						ok_pipe_stage3	= 0;
						ok_pipe_stage4	= 0;
					
					end else if (pipe_valid == `STAGE2) begin
						pipe_valid		= `STAGE3;
						ok_pipe_stage3	= 1;
						ok_pipe_stage4	= 0;
						
					end else if (pipe_valid == `STAGE3) begin
						pipe_valid		= `STAGE4;
						ok_pipe_stage4	= 1;
					end
			end
		endtask

	
	//////////
	//
	// Bootup
	//
	//////
		task bootup;
			begin
				// Initialize clk
				clk					= 0;			// Clock is initially low
	    
				// Halt all instruction processing until we're done loading
				i_halt				= 1;			// Halt is true
				pipe_valid			= `STAGE1;		// No valid stages except i-fetch
	      
				// Initialize ok values
				ok_i_fetch			= 0;			// Okay to i-fetch:		is false
				ok_i_decode			= 0;			// Okay to i-decode:	is false
				ok_d_read			= 0;			// Okay to d-read:		is false
				ok_i_process		= 0;			// Okay to i-process:	is false
				ok_d_write			= 0;			// Okay to d-write:		is false
	    
				// Initialize flags and registers
				flags				= 0;			// 0=zero? 1=carry?
				r1					= 0;			// 8-bit R1 general purpose register, set to 0
				r2					= 0;			// 8-bit R1 general purpose register, set to 0
				r3					= 0;			// 8-bit R1 general purpose register, set to 0
				r4					= 0;			// 8-bit R1 general purpose register, set to 0
				ip					= 0;			// 11-bit RI instruction pointer begins at 0
				
				// Initial write/read values
				p5_write_address	= 0;
				p5_write_data		= 0;
				
				read1_enable		= 0;
				read1_address		= 0;
`ifndef _ICARUS_VERILOG_COMPILATION
				read1_data			= 0;
`endif
				
				read2_enable		= 0;
				read2_address		= 0;
`ifndef _ICARUS_VERILOG_COMPILATION
				read2_data			= 0;
`endif
				
				read3_enable		= 0;
				read3_address		= 0;
`ifndef _ICARUS_VERILOG_COMPILATION
				read3_data			= 0;
`endif
				
				read4_enable		= 0;
				read4_address		= 0;
`ifndef _ICARUS_VERILOG_COMPILATION
				read4_data			= 0;
`endif
								
				// Setup initial values
				p1_ip_address		= 0;
			
				p2_i_data1			= 0;
				p2_i_data2			= 0;
				p2_reg_src			= 0;
				p2_reg_dst			= 0;
				p2_read_ok			= 0;
				p2_read_address		= 0;
				p2_write_ok			= 0;
				p2_write_address	= 0;
				p2_ip_sign			= 0;
				p2_ip_delta			= 0;
				p2_ip_address		= 0;
				p2_process_op		= 0;
				p2_increment2		= 0;
	
				p3_reg_src			= 0;
				p3_reg_dst			= 0;
				p3_data				= 0;
				p3_write_ok			= 0;
				p3_write_address	= 0;
				p3_ip_sign			= 0;
				p3_ip_delta			= 0;
				p3_ip_address		= 0;
				p3_process_op		= 0;
	
				p4_new_ip_valid		= 0;
				p4_new_ip			= 0;
				p4_reg_src			= 0;
				p4_reg_dst			= 0;
				p4_data				= 0;
				p4_result			= 0;
				p4_write_ok			= 0;
				p4_write_address	= 0;
				p4_ip_sign			= 0;
				p4_ip_delta			= 0;
				p4_process_op		= 0;
				p4_carry			= 0;
	
				p5_write_ok			= 0;
	    
				// Populate RAM
			end
		endtask

endmodule




//////////
//
// RAM with 1 write port and 4 read ports
//
//////
`ifndef _ICARUS_VERILOG_COMPILATION
  module ram_1_4(	input									write_enable,
					input		[WIDTH_ADDRESS	- 1:0]		write_address,
					input		[WIDTH_DATA		- 1:0]		write_data,

					input									read1_enable,
					input		[WIDTH_ADDRESS	- 1:0]		read1_address,
					output		[WIDTH_DATA		- 1:0]		read1_data,

					input									read2_enable,
					input		[WIDTH_ADDRESS	- 1:0]		read2_address,
					output 		[WIDTH_DATA		- 1:0]		read2_data,

					input									read3_enable,
					input		[WIDTH_ADDRESS	- 1:0]		read3_address,
					output 		[WIDTH_DATA		- 1:0]		read3_data,

					input									read4_enable,
					input		[WIDTH_ADDRESS	- 1:0]		read4_address,
					output 		[WIDTH_DATA		- 1:0]		read4_data
					);
	
	//////////
	// Memory sizing parameters
	//////													// By default:
	  parameter		WIDTH_DATA				= 8;			// 8-bit data
	  parameter		WIDTH_ADDRESS			= 11;			// 11-bit address
	  parameter		SIZE_RAM				= 2048;			// 2 KB buffer
	
	
	//////////
	// Physical storage
	//////
		reg		[WIDTH_DATA		- 1:0]		memory[SIZE_RAM - 1:0];
`else
  module ram_1_4(	write_enable,
					write_address,
					write_data,
					
					read1_enable,
					read1_address,
					read1_data,
					
					read2_enable,
					read2_address,
					read2_data,
					
					read3_enable,
					read3_address,
					read3_data,
					
					read4_enable,
					read4_address,
					read4_data		);
	
	
	//////////
	// Memory sizing parameters
	//////													// By default:
	  parameter		WIDTH_DATA				= 8;			// 8-bit data
	  parameter		WIDTH_ADDRESS			= 11;			// 11-bit address
	  parameter		SIZE_RAM				= 2048;			// 2 KB buffer
	
	
	//////////
	// Physical storage
	//////
		reg		[WIDTH_DATA		- 1:0]		memory[SIZE_RAM - 1:0];


	//////////
	// One write port
	//////
		input								write_enable;
		input	[WIDTH_ADDRESS	- 1:0]		write_address;
		input	[WIDTH_DATA		- 1:0]		write_data;


	//////////
	// Four read ports
	//////
		input								read1_enable;
		input	[WIDTH_ADDRESS	- 1:0]		read1_address;
		output	[WIDTH_DATA		- 1:0]		read1_data;
		reg		[WIDTH_DATA		- 1:0]		read1_data;

		input								read2_enable;
		input	[WIDTH_ADDRESS	- 1:0]		read2_address;
		output	[WIDTH_DATA		- 1:0]		read2_data;
		reg		[WIDTH_DATA		- 1:0]		read2_data;

		input								read3_enable;
		input	[WIDTH_ADDRESS	- 1:0]		read3_address;
		output	[WIDTH_DATA		- 1:0]		read3_data;
		reg		[WIDTH_DATA		- 1:0]		read3_data;

		input								read4_enable;
		input	[WIDTH_ADDRESS	- 1:0]		read4_address;
		output	[WIDTH_DATA		- 1:0]		read4_data;
		reg		[WIDTH_DATA		- 1:0]		read4_data;
`endif

    //////////
    // Write data to memory
    //////
		always @(negedge oppie1.clk) begin
			if (write_enable) begin
				memory[write_address] <= write_data;	// Receive the data
			end
		end


    //////////
    // Read data from memorys
    //////
		always @(negedge oppie1.clk) begin
			if (read1_enable) begin
				read1_data	<= memory[read1_address];	// Pipe the #1 data
			end
			if (read2_enable) begin
				read2_data	<= memory[read2_address];	// Pipe the #2 data
			end
			if (read3_enable) begin
				read3_data	<= memory[read3_address];	// Pipe the #3 data
			end
			if (read4_enable) begin
				read4_data	<= memory[read4_address];	// Pipe the #4 data
			end
		end
  endmodule




//////////
//
// 8-bit adder with carry
//
//////
	module add_adc_reg8(	input	[7:0]	v1,			// Value 1
							input	[7:0]	v2,			// Value 2
							input	[0:0]	carry_in,	// carry? in
							input	[1:0]	dst_reg);	// Destination register

		
		
		//////////
		// Local computed result
		//////
			wire	[7:0]		lresult;	// Local computed result
			wire				carry_out;	// Computed carry? ultimately goes into flags[`CARRY:`CARRY]
		
		
		//////////
		// Hookup our subtractor
		//////
			full_add_sub_bit_count #(8) fasbc0(.sum(lresult), .co(carry_out), .v1(v1), .v2(v2), .ci(carry_in), .is_subtractor(1'b0));
		

		//////////
		// Compute the 8-bit sum with carry
		//////
			always @(negedge oppie1.clk) begin
				// Computed in fasbc0
				
				// Store the result
				if (dst_reg == `R1) begin
					oppie1.r1 = lresult;
				end else if (dst_reg == `R2) begin
					oppie1.r2 = lresult;
				end else if (dst_reg == `R3) begin
					oppie1.r3 = lresult;
				end else /*if (dst_reg == `R4)*/ begin
					oppie1.r4 = lresult;
				end
				
				// Store the carry? flag
				oppie1.flags[`CARRY:`CARRY] = carry_out;
			end
	endmodule




//////////
//
// Primitive 2-input bitwise full adder/subtractor
//
//////
	// Performs:  result = l1 + l2		// when is_subtractor = 0
	// Performs:  result = l1 - l2		// when is_subtractor = 1
	module full_adder_subtractor(	output	[0:0]	result,			// Result of l1 + l2 + carry? in
									output	[0:0]	carry_out,		// carry? data out
									input	[0:0]	l1,				// Line 1 data in
									input	[0:0]	l2,				// Line 2 data in
									input	[0:0]	carry_in,		// carry? data in
									input	[0:0]	is_subtractor);	// 1=subtractor, 0=adder
		
		// Circuit fabric
		wire	net1, net2, net3, net_add_sub;
		
		// See circuit:  logic/full_adder_subtractor.png
		// For symbols:  logic/logic_symbols.png
		xor	(net_add_sub,	is_subtractor,	l2);
		xor (net1,			l1,				net_add_sub);
		xor (result,		net1,			carry_in);
		and	(net3,			l1,				net_add_sub);
		and	(net2,			net1,			carry_in);
		or	(carry_out,		net2,			net3);
	endmodule




//////////
//
// N-bit adder with carry, subtractor with borrow
//
//////
	module full_add_sub_bit_count(	output	[BIT_COUNT-1:0]		sum,			// Result of v1 + v2 or v1 - v2
									output	[0:0]				co,				// carry?/borrow out
									input	[BIT_COUNT-1:0]		v1,				// value1 in
									input	[BIT_COUNT-1:0]		v2,				// value2 in
									input	[0:0]				ci,				// carry?/borrow in
									input	[0:0]				is_subtractor);	// 1=subtractor, 0=adder
		
		parameter BIT_COUNT = 8;
		
		// Net of carry? outs for each sub-adder
		wire	[BIT_COUNT-2:0]	nco;

		// Generate adder/subtractor for BIT_COUNT bits
		genvar i;
		generate
			for (i = 0; i < BIT_COUNT; i = i + 1) begin: nbits
				case (i)
					// Hook up to carry in
					0: full_adder_subtractor	instancex(	.result(sum[i]),
															.carry_out(nco[i]),
															.l1(v1[i]),
															.l2(v2[i]),
															.carry_in(ci),
															.is_subtractor(is_subtractor));

					// Hook up to carry out
					BIT_COUNT-1: full_adder_subtractor	instancex(	.result(sum[i]),
																	.carry_out(co),
																	.l1(v1[i]),
																	.l2(v2[i]),
																	.carry_in(nco[i-1]),
																	.is_subtractor(is_subtractor));
					
					default:
						full_adder_subtractor	instancex(	.result(sum[i]),
															.carry_out(nco[i]),
															.l1(v1[i]),
															.l2(v2[i]),
															.carry_in(nco[i-1]),
															.is_subtractor(is_subtractor));
				endcase
			end
		endgenerate
	endmodule




//////////
//
// 8-bit subtract with borrow
//
//////
	module sub_sbb_reg8(	input	[7:0]	v1,			// Value 1
							input	[7:0]	v2,			// Value 2
							input	[0:0]	borrow_in,	// borrow in
							input	[1:0]	dst_reg);	// Destination register
		
		//////////
		// Local computed result
		//////
			wire	[7:0]		lresult;	// Local computed result
			wire				borrow_out;	// Computed borrow ultimately goes into flags[`CARRY:`CARRY]
		
		
		//////////
		// Hookup our subtractor
		//////
			full_add_sub_bit_count #(8) fasbc0(.sum(lresult), .co(borrow_out), .v1(v1), .v2(v2), .ci(borrow_in), .is_subtractor(1'b1));
		

		//////////
		// Compute the 8-bit subtraction with borrow
		//////
			always @(negedge oppie1.clk) begin
				// Computed in fasbc0
				
				// Store the result
				if (dst_reg == `R1) begin
					oppie1.r1 = lresult;
				end else if (dst_reg == `R2) begin
					oppie1.r2 = lresult;
				end else if (dst_reg == `R3) begin
					oppie1.r3 = lresult;
				end else /*if (dst_reg == `R4)*/ begin
					oppie1.r4 = lresult;
				end
			end
	endmodule
