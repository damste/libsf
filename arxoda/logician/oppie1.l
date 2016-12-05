<logician>

<!-- c:/libsf/li386/logician/oppie1.l -->

	<version ma="0" mi="01" rev="0"/>
	<copyright y="2014" n="Rick C. Hodgin"/>
	<update last="Nov.23.2014">
		<change date="Nov.17.2014" desc="Initial creation"/>
	</update>
	
	<license>
This software is released as Liberty Software under a Repeat License, as governed
by the Public Benefit License v1.0 or later (PBL).

You are free to use, copy, modify and share this software.  However, it can only
be released under the PBL version indicated, and every project must include a copy
of the pbl.txt document for its version as is at http://www.libsf.org/licenses/.

For additional information about this project, or to view the license, see:

    http://www.libsf.org/
    http://www.libsf.org/licenses/
    http://www.visual-freepro.org/vjr/indexmain.html
    http://www.visual-freepro.org/wiki/index.php/PBL

Thank you.  And may The Lord bless you richly as you lift up your life, your
talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
	</license>
	
	<overview>
Oppie-1 -- Simple CPU able to execute these instructions:

	ASM Instruction			Bytes		Opcode Bit Encoding (x=unused)
	-------------------		------		------------------------------
										* Register encodings are 2 bits
	mov   reg8,[address]	2			000.00.000:00000000
	mov   reg8,reg8			1			001.x.00.00	(dest,src)
	add   reg8,reg8			1			0100.00.00
	adc   reg8,reg8			1			0110.00.00
	sub   reg8,reg8			1			0101.00.00
	sbb   reg8,reg8			1			0111.00.00
	mov   [address],reg8	2			100.00.000:00000000
	cmp   reg8,reg8			1			101.x.00.00	(left,right)
	jz    +/- 1KB			2			110.xx.s.00:00000000
	jmp   +/- 1KB			2			111.xx.s.00:00000000 

Using this environment:

	8-bit Regs			Flags			Memory
	---------------		---------		-----------
	r1 -- 00000000		zero?			2 Kilobytes
	r2 -- 00000000		carry?
	r3 -- 00000000
	r4 -- 00000000

	ip -- 00000000		-- Instruction pointer

-----
Compiled in Icarus Verilog 0.9.7.
Using GTKWave for validation.

-----
Note:  Incomplete and untested as of Nov.23.2014.
	</overview>
	
	<clock freq="max">
		<gripper name="Outputs" orientation="south">
			<signal ds="UP" init="0"/>
			<signal ds="HI" init="0"/>
			<signal ds="DN" init="0"/>
			<signal ds="LO" init="0"/>
		</gripper>
		<gripper name="Data">
			<regs name="Internal">
				<reg name="cycle" endian="little" size="3" init="0"/>
			</regs>
		</gripper>
		<code>
//////////
// A single clock cycle is broken out into dispatchable phases:
//
//        2___3____4                UP = 0 start, stop 1
//        |        |                HI = 2 start, stop 4
//       1|        |5               DN = 4 start, stop 5
//        |        |_________       LO = 6 start, stop 8/0
//       0         6    7   8/0
//
//////
	// Signal this phase
	switch (cycle)
	{
		case 0:		LO = 0;		UP = 1;		break;
		case 1:		UP = 0;					break;
		case 2:		HI = 1;					break;
		case 3:		/* Nothing changes */	break;
		case 4:		HI = 0;		DN = 1;		break;
		case 5:		DN = 0;					break;
		case 6:		LO = 1;					break;
	}
	
	// Prepare for next phase
	++cycle;	// Note:  Cycle is only 3 bits, it wraps back to 0 on overflow
		</code>
	</clock>

	<code name="init">
//////////
// Added to allow compilation in both iverilog, and Quartus-II:
//////
//#define _ICARUS_VERILOG_COMPILATION
	</code>

	<code name="main">
	</code>
</logician>
