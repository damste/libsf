//////////
//
// /libsf/li386/oppie/oppie1/cpp_simulation/oppie1.cpp
//
//////
// Version 0.01
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Nov.26.2014
//////
// Change log:
//     Nov.24.2014 - Initial creation
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
// Oppie-1 is a CPU design.  See oppie1.sv for the equivalent verilog source code.
// It is known to compile and synthesize in Altera Quartus-II.
//
//		Instruction pipeline:
//			+-----------+
//			|  i-read   |	// instruction fetch/read
//			+-----------+
//			      |
//			      |
//			+-----------+
//			|  i-decode |	// instruction decode
//			+-----------+
//			      |
//			      |
//			+-----------+
//			|   d-read  |	// data fetch/read
//			+-----------+
//			      |
//			      |
//			+-----------+
//			| i-process |	// instruction processing (conduct physical work)
//			+-----------+
//			      |
//			      |
//			+-----------+
//			|  d-write  |	// data write
//			+-----------+
//
//////
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

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "\libsf\source\vjr\vjr_const.h"


//////////
// The clock follows a 4-stage pattern, as it repeats forever:
//		 _____1_____
//		|			|
//		|0			|2
//		|			|_____3______
//
//////
	const s32	_POSEDGE			= 0;		// positive edge
	const s32	_POSLEVEL			= 1;		// positive level
	const s32	_NEGEDGE			= 2;		// negative edge
	const s32	_NEGLEVEL			= 3;		// negative level

	#define		B000				0x0;		// Binary 000
	#define		B001				0x1;		// Binary 001
	#define		B010				0x2;		// Binary 010
	#define		B011				0x3;		// Binary 011
	#define		B100				0x4;		// Binary 100
	#define		B101				0x5;		// Binary 101
	#define		B110				0x6;		// Binary 110
	#define		B111				0x7;		// Binary 111

	const s32	_RAM_SIZE			= 2048;		// 2KB of RAM

	const s32	_R1					= 0;		// 00b
	const s32	_R2					= 1;		// 01b
	const s32	_R3					= 2;		// 10b
	const s32	_R4					= 3;		// 11b

	const s32	_STAGE0				= 0;		// Pipe stage 0... which only happens during a branch (so the instruction pipe is refilled)
	const s32	_STAGE1				= 1;		// Pipe stage 1 is valid
	const s32	_STAGE2				= 2;		// Pipe stage 2 is valid
	const s32	_STAGE3				= 3;		// Pipe stage 3 is valid
	const s32	_STAGE4				= 4;		// Pipe stage 4 is valid
	const s32	_STAGE5				= 5;		// Pipe stage 5 is valid

	const s32	_MOV_R8_ADDR		= B000;		//		mov   reg8,[address]	2			000.00.000:00000000
	const s32	_MOV_R8_R8			= B001;		//		mov   reg8,reg8			1			001.x.00.00	(dest,src)
	const s32	_ADD_R8_R8			= B100;		//		add   reg8,reg8			1			0100.00.00
	const s32	_ADC_R8_R8			= B110;		//		adc   reg8,reg8			1			0110.00.00
	const s32	_SUB_R8_R8			= B101;		//		sub   reg8,reg8			1			0101.00.00
	const s32	_SBB_R8_R8			= B111;		//		sbb   reg8,reg8			1			0111.00.00
	const s32	_MOV_ADDR_R8		= B100;		//		mov   [address],reg8	2			100.00.000:00000000
	const s32	_CMP_R8_R8			= B101;		//		cmp   reg8,reg8			1			101.x.00.00	(left,right)
	const s32	_JZ_REL_ADDR		= B110;		//		jz    +/- 1KB			2			110.xx.s.00:00000000
	const s32	_JMP_REL_ADDR		= B111;		//		jmp   +/- 1KB			2			111.xx.s.00:00000000 

	// Numbered operations mimic the bit encoding-derived instructions above
	const s32	_OP_MOV_R8_ADDR		= 1;
	const s32	_OP_MOV_R8_R8		= 2;
	const s32	_OP_ADD_R8_R8		= 3;
	const s32	_OP_ADC_R8_R8		= 4;
	const s32	_OP_SUB_R8_R8		= 5;
	const s32	_OP_SBB_R8_R8		= 6;
	const s32	_OP_MOV_ADDR_R8		= 7;
	const s32	_OP_CMP_R8_R8		= 8;
	const s32	_OP_JZ_REL_ADDR		= 9;
	const s32	_OP_JMP_REL_ADDR	= 10;




//////////
// Structures
//////
	// Registers
	struct SRegs
	{
		u8		r1		:	8;
		u8		r2		:	8;
		u8		r3		:	8;
		u8		r4		:	8;
		s16		ip		:	11;
		u8		carry	:	1;
		u8		zero	:	1;
	};

	// Template instructions:
	struct SOra	// Ora = Operation, register, address
	{
		// ooo.rr.aaa:aaaaaaaa
		union {
			struct {
				u8		i_data1;			// Opcode byte 1
				u8		i_data2;			// Opcode byte 2
			};
			struct {
				u8		ooo			: 3;
				u8		rd			: 2;
				u8		aaa			: 3;
				u8		aaaaaaaa	: 8;
			};
		};
	};

	struct SOrr // Orr = Operation, register, register
	{
		// ooo.x.rd.rs		-- 3-bit form
		// oooo.rd.rs		-- 4-bit form
		union {
			struct {
				u8		i_data1;			// Opcode byte 1
			};
			struct {
				u8		ignore		: 4;
				u8		rd			: 2;
				u8		rs			: 2;
			};
			struct {
				u8		ooo			: 3;
				u8		x			: 1;
				u8		rd1			: 2;
				u8		rs1			: 2;
			};
			struct {
				u8		oooo		: 4;
				u8		rd2			: 2;
				u8		rs2			: 2;
			};
		};
	};

	// Template instructions:
	struct SBsa	// Ba = Branch, sign, address
	{
		// ooo.xx.s.aaa:aaaaaaaa
		union {
			struct {
				u8		i_data1;			// Opcode byte 1
				u8		i_data2;			// Opcode byte 2
			};
			struct {
				u8		ooo			: 3;
				u8		xx			: 2;
				u8		s			: 1;
				u8		aa			: 2;
				u8		aaaaaaaa	: 8;
			};
		};
	};

	// Overall machine state status
	struct SState
	{
		u32		clk;						// Clock signal
		bool	is_CPU_halted;				// True if the machine is halted
		int		pipeStage;					// The current pipeline stage that's valid (set to 0 during branch, incremented up to 5 )

		// Register state
		SRegs	regs;
	};

	// Pipe stage 1:  i-fetch
	struct SPipe1
	{
		u16		ip;							// ip address of opcode1
		char	i_data1;					// [ip+0]
		char	i_data2;					// [ip+1]
		char	i_data3;					// [ip+2]
	};

	// Pipe stage 2:  i-decode
	struct SPipe2
	{
		u16		ip;							// ip address of i_data1
		char	i_data1;					// opcode byte 1
		char	i_data2;					// optional opcode byte 2

		bool	p2_increment2;				// Should the instruction pointer be increased by 2?

		bool	p3_d_read;					// Should data be read for this step in stage 3?
		u16		p3_d_read_address;			// Address to read

		u8		p4_op;						// Operation to conduct in stage 4
		u8		p4_reg_src;					// Register for source operation
		u8		p4_reg_dst;					// Register for destination operation
		// For relative branches
		bool	p4_ip_sign;					// Sign of relative jump (0=positive, 1=negative)
		u16		p4_ip_delta;				// Number of bytes to adjust ip

		bool	p5_d_write;					// Should data be written in stage 5?
		u16		p5_d_write_address;			// Address to write
	};

	// Pipe stage 3:  d-fetch
	struct SPipe3
	{
		u16		ip;							// ip address of the opcode associated with this instruction

		bool	p3_d_read;					// Should data be read for this step in stage 3?
		u16		p3_d_read_address;			// Address to read

		u8		p4_op;						// Operation to conduct in stage 4
		u8		p4_data;					// Data read in stage 3
		u8		p4_reg_src;					// Register for source operation
		u8		p4_reg_dst;					// Register for destination operation
		// For relative branches
		bool	p4_ip_sign;					// Sign of relative jump (0=positive, 1=negative)
		u16		p4_ip_delta;				// Number of bytes to adjust ip

		bool	p5_d_write;					// Should data be written in stage 5?
		u16		p5_d_write_address;			// Address to write
	};

	// Pipe stage 4:  i-process
	struct SPipe4
	{
		u16		ip;							// ip address of the opcode associated with this instruction

		u8		p4_op;						// Operation to conduct in stage 4
		u8		p4_data;					// Data read in stage 3
		u8		p4_reg_src;					// Register for source operation
		u8		p4_reg_dst;					// Register for destination operation
		// For relative branches
		bool	p4_ip_sign;					// Sign of relative jump (0=positive, 1=negative)
		u16		p4_ip_delta;				// Number of bytes to adjust ip
		bool	p4_computed_ip_is_valid;	// Is the computed ip address valid (should we branch)?
		u16		p4_computed_ip_on_branch;	// The new ip if there was a branch

		bool	p5_d_write;					// Should data be written in stage 5?
		u8		p5_data;					// Result of the operation computed in stage 4, to write out in stage 5
		u16		p5_d_write_address;			// Address to write
	};

	// Pipe stage 5:  d-write
	struct SPipe5
	{
		u16		ip;							// ip address of the opcode associated with this instruction

		bool	p5_d_write;					// Should data be written in stage 5?
		u8		p5_data;					// Result of the operation computed in stage 4, to write out in stage 5
		u16		p5_d_write_address;			// Address to write
	};


//////////
// The RAM, and processing internals of the each stage
//////
	u8				ram[_RAM_SIZE];
	SState			state;
	SPipe1			pipe1;
	SPipe2			pipe2;
	SPipe3			pipe3;
	SPipe4			pipe4;
	SPipe5			pipe5;
	bool			glOppie1_isRunning;




//////////
// Forward declarations
//////
	void			iExecute_clockPhase					(u32 clk);
	void			iExecute_stage1						(u32 clk, s32 direction);
	void			iExecute_stage2						(u32 clk, s32 direction);
	void			iExecute_stage3						(u32 clk, s32 direction);
	void			iExecute_stage4						(u32 clk, s32 direction);
	u8				iiExecute_stage4_getRegSrc			(void);
	void			iExecute_stage5						(u32 clk, s32 direction);


//////////
// debo1.cpp
//////
	#include "debo1.cpp"
	void			iDebo1_launch						(void);




//////////
//
// The main CPU execution loop
//
//////
	int main(int argc, char* argv[])
	{
		//////////
		// Launch debugger
		//////
			glOppie1_isRunning = true;
			iDebo1_launch();

		
		//////////
		// Simulate forever
		//////
			for (state.clk = _POSEDGE, state.pipeStage = _STAGE1; glOppie1_isRunning; )
			{
				// The debugger can override our execution
				if (glDebo1_executionIsPaused)
				{
					// Take a breather
					Sleep(10);
				
				} else {
					// Go ahead and execute
					iExecute_clockPhase(state.clk);
					
					// Phase
					state.clk = (++state.clk % (_NEGLEVEL + 1));

					// Are we back to the start of a cycle again?
					if (state.clk == _POSEDGE)
					{
						// Are we single-stepping or throttled?
						if (glDebo1_executionIsSingleStepping || glDebo1_executionIsThrottled)
						{
							// Signal the debugger to update itself if need be
							glDebo1_updateDisplay		= true;
							glDebo1_executionIsPaused	= true;
						}

					} else if (state.clk == _NEGLEVEL) {
						// Indicate the pipe stage has increased
						state.pipeStage = min(++state.pipeStage, _STAGE5);
					}
				}
			}
			return 0;
	}




//////////
//
// Execute the clock cycle phase "simultaneously" on all stages
//
///////
	void iExecute_clockPhase(u32 clk)
	{
		//////////
		// Execute in the order 1..5
		//////
			iExecute_stage1(clk, 1);
			iExecute_stage2(clk, 1);
			iExecute_stage3(clk, 1);
			iExecute_stage4(clk, 1);
			iExecute_stage5(clk, 1);


		//////////
		// Execute in the order 5..1
		//////
			iExecute_stage5(clk, -1);
			iExecute_stage4(clk, -1);
			iExecute_stage3(clk, -1);
			iExecute_stage2(clk, -1);
			iExecute_stage1(clk, -1);
	}




//////////
//
// Execute stage 1
//
//////
	void iExecute_stage1(u32 clk, s32 direction)
	{
		if (direction > 0)
		{
			// Order of 1..5
			if (clk == _POSEDGE)
			{
				// i-fetch
				if (!state.is_CPU_halted /*&& state.pipeStage >= _STAGE1 not included because pipe stage 1 is always valid when the CPU is not halted*/)
				{
					// Grab the next three bytes
					pipe1.i_data1	= ram[state.regs.ip + 0];
					pipe1.i_data2	= ram[state.regs.ip + 1];
					pipe1.i_data3	= ram[state.regs.ip + 2];
				}
			}

		} else {
			// Order of 5..1
			if (clk == _NEGEDGE)
			{
				// Perform the push
				pipe1.ip += ((pipe2.p2_increment2) ? 2 : 1);
			}
		}
	}




//////////
//
// Execute stage 2
//
//////
	void iExecute_stage2(u32 clk, s32 direction)
	{
		SOra	iora;		// ooo.xx.aaa.aaaaaaaa
		SOrr	iorr;		// ooo.x.rd.rs, oooo.rd.rs
		SBsa	ibsa;		// ooo.x.s.aaa.aaaaaaaa

		if (direction > 0)
		{
			// Order of 1..5
			if (clk == _POSEDGE)
			{
				// i-decode
				if (!state.is_CPU_halted && state.pipeStage >= _STAGE2)
				{
					// Fill the instruction patterns for testing
					iora.i_data1 = pipe2.i_data1;
					iorr.i_data1 = pipe2.i_data1;
					ibsa.i_data1 = pipe2.i_data1;

					// Decode the bits
					if (iora.ooo == _MOV_R8_ADDR)
					{
						// mov   reg8,[address]		2			000.00.000:00000000
						iora.i_data2				= pipe2.i_data2;
						pipe2.p4_op					= _OP_MOV_R8_ADDR;
						pipe2.p4_reg_dst			= iora.rd;
						pipe2.p3_d_read				= true;
						pipe2.p3_d_read_address		= ((u16)iora.aaa << 8) | (u16)iora.aaaaaaaa;

					} else if (iorr.ooo == _MOV_R8_R8) {
						// mov   reg8,reg8			1			001.x.00.00	(dest,src)
						pipe2.p4_op					= _OP_MOV_R8_R8;
						pipe2.p4_reg_dst			= iorr.rd;
						pipe2.p4_reg_src			= iorr.rs;
						pipe2.p3_d_read				= false;

					} else if (iorr.oooo == _ADD_R8_R8) {
						// add   reg8,reg8			1			0100.00.00
						pipe2.p4_op					= _OP_ADD_R8_R8;
						pipe2.p4_reg_dst			= iorr.rd;
						pipe2.p4_reg_src			= iorr.rs;
						pipe2.p3_d_read				= false;

					} else if (iorr.oooo == _ADC_R8_R8) {
						// adc   reg8,reg8			1			0110.00.00
						pipe2.p4_op					= _OP_ADC_R8_R8;
						pipe2.p4_reg_dst			= iorr.rd;
						pipe2.p4_reg_src			= iorr.rs;
						pipe2.p3_d_read				= false;

					} else if (iorr.oooo == _SUB_R8_R8) {
						// sub   reg8,reg8			1			0101.00.00
						pipe2.p4_op					= _OP_SUB_R8_R8;
						pipe2.p4_reg_dst			= iorr.rd;
						pipe2.p4_reg_src			= iorr.rs;
						pipe2.p3_d_read				= false;

					} else if (iorr.oooo == _SBB_R8_R8) {
						// sbb   reg8,reg8			1			0111.00.00
						pipe2.p4_op					= _OP_SBB_R8_R8;
						pipe2.p4_reg_dst			= iorr.rd;
						pipe2.p4_reg_src			= iorr.rs;
						pipe2.p3_d_read				= false;

					} else if (iora.ooo == _MOV_ADDR_R8) {
						// mov   [address],reg8		2			100.00.000:00000000
						iora.i_data2				= pipe2.i_data2;
						pipe2.p4_op					= _OP_MOV_ADDR_R8;
						pipe2.p4_reg_dst			= iora.rd;
						pipe2.p5_d_write_address	= ((u16)iora.aaa << 8) | (u16)iora.aaaaaaaa;
						pipe2.p3_d_read				= false;

					} else if (iorr.ooo == _CMP_R8_R8) {
						// cmp   reg8,reg8			1			101.x.00.00	(left,right)
						pipe2.p4_op					= _OP_CMP_R8_R8;
						pipe2.p4_reg_dst			= iorr.rd;
						pipe2.p4_reg_src			= iorr.rs;
						pipe2.p3_d_read				= false;

					} else if (ibsa.ooo == _JZ_REL_ADDR) {
						// jz    +/- 1KB			2			110.xx.s.00:00000000
						ibsa.i_data2				= pipe2.i_data2;
						pipe2.p4_op					= _OP_JZ_REL_ADDR;
						pipe2.p4_ip_sign			= ibsa.s;
						pipe2.p4_ip_delta			= ((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa;
						pipe2.p3_d_read				= false;

					} else if (ibsa.ooo == _JMP_REL_ADDR) {
						// jmp   +/- 1KB			2			111.xx.s.00:00000000 
						ibsa.i_data2				= pipe2.i_data2;
						pipe2.p4_op					= _OP_JMP_REL_ADDR;
						pipe2.p4_ip_sign			= ibsa.s;
						pipe2.p4_ip_delta			= ((u16)ibsa.aa << 8) | (u16)ibsa.aaaaaaaa;
						pipe2.p3_d_read				= false;

					} else {
						// Invalid opcode
						printf("Invalid opcode encountered at %u. Exiting.\n", pipe2.ip);
						exit(-1);
					}
				}
			}

		} else {
			// Order of 5..1
			if (clk == _NEGEDGE)
			{
				// Perform the push
				pipe2.ip			= pipe1.ip;
				pipe2.i_data1		= pipe1.i_data1;
				pipe2.i_data2		= pipe1.i_data2;
			}
		}
	}




//////////
//
// Execute stage 3
//
//////
	void iExecute_stage3(u32 clk, s32 direction)
	{
		if (direction > 0)
		{
			// Order of 1..5
			if (clk == _POSEDGE)
			{
				// d-read
				if (!state.is_CPU_halted && state.pipeStage >= _STAGE3 && pipe3.p3_d_read)
				{
					// Retrieve the memory
					pipe3.p4_data = ram[pipe3.p3_d_read_address];
				}
			}

		} else {
			// Order of 5..1
			if (clk == _NEGEDGE)
			{
				// Perform the push
				pipe3.ip					= pipe2.ip;
				pipe3.p3_d_read				= pipe2.p3_d_read;
				pipe3.p3_d_read_address		= pipe2.p3_d_read_address;

				pipe3.p4_op					= pipe2.p4_op;
				pipe3.p4_reg_dst			= pipe2.p4_reg_dst;
				pipe3.p4_reg_src			= pipe2.p4_reg_src;
				pipe3.p4_ip_sign			= pipe2.p4_ip_sign;
				pipe3.p4_ip_delta			= pipe2.p4_ip_delta;

				pipe3.p5_d_write			= pipe2.p5_d_write;
				pipe3.p5_d_write_address	= pipe2.p5_d_write_address;
			}
		}
	}




//////////
//
// Execute stage 4
//
//////
	void iExecute_stage4(u32 clk, s32 direction)
	{
		u8 rx;

		if (direction > 0)
		{
			// Order of 1..5
			if (clk == _POSEDGE)
			{
				// i-process
				if (!state.is_CPU_halted && state.pipeStage >= _STAGE4)
				{
					// Execute the op
					switch (pipe4.p4_op)
					{
						case _OP_MOV_R8_ADDR:
							switch (pipe4.p4_reg_dst)
							{
								case _R1:	rx = state.regs.r1 = pipe4.p4_data;		break;
								case _R2:	rx = state.regs.r2 = pipe4.p4_data;		break;
								case _R3:	rx = state.regs.r3 = pipe4.p4_data;		break;
								case _R4:	rx = state.regs.r4 = pipe4.p4_data;		break;
							}
							state.regs.zero = (rx == 0);
							break;

						case _OP_MOV_R8_R8:
							rx = iiExecute_stage4_getRegSrc();
							switch (pipe4.p4_reg_dst)
							{
								case _R1:	rx = (state.regs.r1 = rx);		break;
								case _R2:	rx = (state.regs.r2 = rx);		break;
								case _R3:	rx = (state.regs.r3 = rx);		break;
								case _R4:	rx = (state.regs.r4 = rx);		break;
							}
							state.regs.zero = (rx == 0);
							break;

						case _OP_ADD_R8_R8:
							rx = iiExecute_stage4_getRegSrc();
							switch (pipe4.p4_reg_dst)
							{
								case _R1:	rx = (state.regs.r1 += rx);		break;
								case _R2:	rx = (state.regs.r2 += rx);		break;
								case _R3:	rx = (state.regs.r3 += rx);		break;
								case _R4:	rx = (state.regs.r4 += rx);		break;
							}
							state.regs.zero = (rx == 0);
							break;

						case _OP_ADC_R8_R8:
							rx = iiExecute_stage4_getRegSrc();
							switch (pipe4.p4_reg_dst)
							{
								case _R1:	rx = (state.regs.r1 += rx + state.regs.carry);	break;
								case _R2:	rx = (state.regs.r2 += rx + state.regs.carry);	break;
								case _R3:	rx = (state.regs.r3 += rx + state.regs.carry);	break;
								case _R4:	rx = (state.regs.r4 += rx + state.regs.carry);	break;
							}
							state.regs.zero = (rx == 0);
							break;

						case _OP_SUB_R8_R8:
							rx = iiExecute_stage4_getRegSrc();
							switch (pipe4.p4_reg_dst)
							{
								case _R1:	rx = (state.regs.r1 -= rx);		break;
								case _R2:	rx = (state.regs.r2 -= rx);		break;
								case _R3:	rx = (state.regs.r3 -= rx);		break;
								case _R4:	rx = (state.regs.r4 -= rx);		break;
							}
							state.regs.zero = (rx == 0);
							break;

						case _OP_SBB_R8_R8:
							rx = iiExecute_stage4_getRegSrc();
							switch (pipe4.p4_reg_dst)
							{
								case _R1:	rx = (state.regs.r1 -= rx + state.regs.carry);		break;
								case _R2:	rx = (state.regs.r2 -= rx + state.regs.carry);		break;
								case _R3:	rx = (state.regs.r3 -= rx + state.regs.carry);		break;
								case _R4:	rx = (state.regs.r4 -= rx + state.regs.carry);		break;
							}
							state.regs.zero = (rx == 0);
							break;

						case _OP_MOV_ADDR_R8:
							switch (pipe4.p4_reg_dst)
							{
								case _R1:	pipe4.p5_data = state.regs.r1;		break;
								case _R2:	pipe4.p5_data = state.regs.r2;		break;
								case _R3:	pipe4.p5_data = state.regs.r3;		break;
								case _R4:	pipe4.p5_data = state.regs.r4;		break;
							}
							break;

						case _OP_CMP_R8_R8:
							rx = iiExecute_stage4_getRegSrc();
							switch (pipe4.p4_reg_dst)
							{
								case _R1:	state.regs.carry = (state.regs.r1 == rx);	break;
								case _R2:	state.regs.carry = (state.regs.r2 == rx);	break;
								case _R3:	state.regs.carry = (state.regs.r3 == rx);	break;
								case _R4:	state.regs.carry = (state.regs.r4 == rx);	break;
							}
							if (state.regs.carry && rx == 0)
							{
								// They match, and rx is 0, which means they're zero. :-)
								state.regs.zero = 1;

							} else {
								// Not zero
								state.regs.zero = 0;
							}
							break;

						case _OP_JZ_REL_ADDR:
							if (state.regs.carry)
							{
								// We jump
								state.pipeStage = _STAGE0;
								if (pipe4.p4_ip_sign)
								{
									// Branching negative
									state.regs.ip	= pipe3.ip - pipe4.p4_ip_delta;

								} else {
									// Branching positive
									state.regs.ip	= pipe3.ip + pipe4.p4_ip_delta;
								}
							}
							break;

						case _OP_JMP_REL_ADDR:
							// We jump
							state.pipeStage = _STAGE0;
							if (pipe4.p4_ip_sign)
							{
								// Branching negative
								state.regs.ip	= pipe3.ip - pipe4.p4_ip_delta;

							} else {
								// Branching positive
								state.regs.ip	= pipe3.ip + pipe4.p4_ip_delta;
							}
							break;

						default:
							printf("Internal consistency error. Exiting.\n");
							exit(-2);
					}
				}
			}

		} else {
			// Order of 5..1
			if (clk == _NEGEDGE)
			{
				// Perform the push
				pipe4.ip					= pipe3.ip;
				pipe4.p4_op					= pipe3.p4_op;
				pipe4.p4_data				= pipe3.p4_data;
				pipe4.p4_reg_dst			= pipe3.p4_reg_dst;
				pipe4.p4_reg_src			= pipe3.p4_reg_src;

				pipe4.p5_d_write			= pipe3.p5_d_write;
				pipe4.p5_d_write_address	= pipe3.p5_d_write_address;
			}
		}
	}

	u8 iiExecute_stage4_getRegSrc(void)
	{
		switch (pipe4.p4_reg_src)
		{
			case _R1:	return(state.regs.r1);
			case _R2:	return(state.regs.r1);
			case _R3:	return(state.regs.r1);
			case _R4:	return(state.regs.r1);
			default:
				printf("Internal consistency error. Exiting.\n");
				exit(-3);
		}
	}




//////////
//
// Execute stage 5
//
//////
	void iExecute_stage5(u32 clk, s32 direction)
	{
		if (direction > 0)
		{
			// Order of 1..5
			if (clk == _POSEDGE)
			{
				// i-write
				if (!state.is_CPU_halted && pipe5.p5_d_write)
				{
					// Write the data
					ram[pipe5.p5_d_write_address] = pipe5.p5_data;
				}
			}

		} else {
			// Order of 5..1
			if (clk == _NEGEDGE)
			{
				// Update data in flight between stage 3 and stage 4
				if (pipe3.p3_d_read_address == pipe5.p5_d_write_address)
					pipe3.p4_data = pipe5.p5_data;

				// Perform the push
				pipe5.ip					= pipe4.ip;
				pipe5.p5_d_write			= pipe4.p5_d_write;
				pipe5.p5_d_write_address	= pipe4.p5_d_write_address;
				pipe5.p5_data				= pipe4.p5_data;
			}
		}
	}
