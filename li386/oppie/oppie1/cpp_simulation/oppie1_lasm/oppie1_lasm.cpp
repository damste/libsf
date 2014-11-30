//////////
//
// /libsf/li386/oppie/oppie1/cpp_simulation/oppie1_lasm/oppie1_lasm.cpp
//
//////
// Version 0.01
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Nov.29.2014
//////
// Change log:
//     Nov.29.2014 - Initial creation
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
// Oppie-1 LASM is the LibSF Assembler for Oppie-1 source code.  It has no linker
// and reads a simple source file with the following syntax, creates the output
// to a file with the same name with the .img extension.
//
// $ lasm myfile.asm
// LibSF Oppie-1 Assembler v0.02
// Assembling myfile.asm
// Write 2048 bytes to myfile.img
//
// ----------
//		 ; START myfile.asm				; Comment regarding start-of-file
//		 top:							; Give this address in memory a symbolic name
//				mov   r1,value1			; Load memory contents to a register by symbolic name
//				mov   r1,[512]			; Load memory contents to a register by symbolic name
//				mov   r3,r2				; Move contents from one register to another
//				add   r4,r1				; Add the contents from one register to another
//				adc   r1,r3				; Add with carry? the contents from one register to another
//				sub   r2,r1				; Subtract the contents from one register to another
//				sbb   r4,r3				; Subtract with borrow (carry?) the contents from one register to another
//				mov   value2,r4			; Move the value from one register to memory by symbolic name
//				mov   [513],r4			; Move the value from one register to memory by symbolic name
//				cmp   r4,r1				; Compare the value of one register to value
//				jnc   done				; Jump to the indicated address by symbolic name
//				jc    done				; Jump to the indicated address by symbolic name
//				jnz   done				; Jump to the indicated address by symbolic name
//				jz    done				; Jump to the indicated address by symbolic name
//				jmp   top				; Jump unconditionally to the indicatedaddress
//		 done:
//				jmp   done				; Stop processing
//		
//			.org 200					; Indicate the following begins explicitly at offset 200 decimal
//		 value1:						; Give a symbolic name to this address
//				db 4 dup 0				; Store 32-bits of 0
//		 value2:						; Give a symbolic name to this address
//				db 4 dup 0				; Store 32-bits of 0
//		 ; END myfile.asm				; Comment regarding the end-of-file
// ----------
//
//////


//////////
// Uses Visual FreePro, Jr's existing parsing facilities to simplify our processing
//////
	#define _OPPIE1_COMPILE		// Turns off some features in VJr that fail on compilation from here
	#include "\libsf\source\vjr\vjr.h"
	#undef main


//////////
// Instruction encoding
//////
	#include "..\common\instructions.h"
	#include "oppie1_lasm.h"




//////////
//
// Top level lasm1 assembler
//
//////
	int main(int argc, char* argv[])
	{
		s32					lnErrors, lnWarnings, lnOrg;
		SEM*				asmFile;
		SLine*				line;
		SOppie1Instruction*	instr;


		//////////
		// Identify ourself
		//////
			printf("LibSF Oppie-1 Assembler v0.02\n");


		//////////
		// lasm1 only takes one parameter, the input filename
		//////
			if (argc != 1)
			{
				// Display syntax
				printf("Usage:  lasm1 myfile.asm\n");

			} else {
				// Allocate our load manager
				asmFile = iSEM_allocate(true);
				if (!asmFile)
				{
					// Internal error
					printf("Internal error allocating load buffer\n");

				} else {
					// Try to physically load it
					if (!iSEM_loadFromDisk(asmFile, argv[1], true))
					{
						// Error opening
						printf("Unable to open %s\n", argv[1]);

					} else {
						//////////
						// Parse every line into known components
						//////
							for (line = asmFile->firstLine; line; line = (SLine*)line->ll.next)
								iParseSourceCodeLine(line);


						//////////
						// Compile every line that can be compiled, report any errors
						//////
							for (	line = asmFile->firstLine, lnErrors = 0, lnWarnings = 0;
									line;
									line = (SLine*)line->ll.next	)
							{
								// Compile pass-1
								iCompileSourceCodeLine(asmFile, line, &lnErrors, &lnWarnings, 1);
							}

							// If there were any errors, exit
							if (lnErrors != 0)
								return -1;


						//////////
						// Assign addresses to everything
						//////
							for (	lnOrg = 0, line = asmFile->firstLine;
									line;
									line = (SLine*)line->ll.next	)
							{
								//////////
								// Based on the type update it
								//////
									instr = (SOppie1Instruction*)line->compilerInfo->extra_info;
									if (instr->isOrg)
									{
										// Update the origin
										lnOrg		= instr->org;

									} else {
										// Store the origin, and increase beyond this instruction's length
										instr->org	= lnOrg;
										lnOrg		+= instr->size;
									}
							}


						//////////
						// Compile every line which has an address that may not have been resolvable before
						//////
							for (	line = asmFile->firstLine, lnErrors = 0, lnWarnings = 0;
									line;
									line = (SLine*)line->ll.next	)
							{
								// Compile pass-2
								iCompileSourceCodeLine(asmFile, line, &lnErrors, &lnWarnings, 2);
							}

							// If there were any errors, exit
							if (lnErrors != 0)
								return -2;


						//////////
						// When we get here, every line has compiled out.
						// Look for memory locations which will overlay
						//////


						//////////
						// Write the output
						//////
					}
				}
			}


		//////////
		// Task completed (one way or another :-))
		//////
			return 0;
	}




//////////
//
// Parses the text of the line into any known tokens
//
//////
	SComp* iParseSourceCodeLine(SLine* line)
	{
		SComp* compNext;


		//////////
		// Make sure we have a compilerInfo block
		//////
			if (!line->compilerInfo)
			{
				// Allocate the compiler info
				line->compilerInfo = iCompiler_allocate(line);
				if (!line->compilerInfo)
				{
					// Should never happen
					printf("Out of memory\n");
					exit(-999);
				}
			}

		//////////
		// Make sure we have our SOppie1Instruction allocated
		//////
			if (!line->compilerInfo->extra_info)
			{
				// Allocate a structure
				line->compilerInfo->extra_info = (SOppie1Instruction*)malloc(sizeof(SOppie1Instruction));
				if (!line->compilerInfo->extra_info)
				{
					// Should never happen
					printf("Out of memory\n");
					exit(-998);
				}

				// Initialize to NULLs
				memset(line->compilerInfo->extra_info, 0, sizeof(SOppie1Instruction));
			}


		//////////
		// Parse out the line
		//////
			iComps_translateSourceLineTo(&cgcFundamentalSymbols[0], line);
			if (!line->compilerInfo->firstComp)
				return(NULL);	// Nothing to compile on this blank line

			// Remove whitespaces [x][whitespace][y] becomes [x][y]
			iComps_removeLeadingWhitespaces(line);
			if (!line->compilerInfo->firstComp)
				return(NULL);	// Nothing to compile on this line with only whitespaces


		//////////
		// We don't need to process comment-only lines
		//////
			if (line->compilerInfo->firstComp && (line->compilerInfo->firstComp->iCode == _ICODE_COMMENT || line->compilerInfo->firstComp->iCode == _ICODE_LINE_COMMENT))
			{
				//////////
				// Combine every item after this to a single comment component or easy parsing and handling
				//////
					iComps_combineNextN(line->compilerInfo->firstComp, 99999, line->compilerInfo->firstComp->iCode, line->compilerInfo->firstComp->iCat, line->compilerInfo->firstComp->color);

			} else {
				//////////
				// Perform natural source code fixups
				//////
					iComps_removeStartEndComments(line);		// Remove /* comments */
					iComps_fixupNaturalGroupings(line);			// Fixup natural groupings [_][aaa][999] becomes [_aaa999], [999][.][99] becomes [999.99], etc.
					iComps_removeWhitespaces(line);				// Remove all whitespaces after everything else was parsed [use][whitespace][foo] becomes [use][foo]


				//////////
				// Translate sequences to known keywords
				//////
					iComps_translateToOthers((SAsciiCompSearcher*)&cgcKeywordsOppie1[0], line);


				//////////
				// Perform fixups that are unique to Oppie-1
				//////
					// .org
					// [.][org] becomes [.org]
					if ((compNext = (SComp*)line->compilerInfo->firstComp->ll.next) && line->compilerInfo->firstComp->iCode == _ICODE_DOT && compNext->iCode == _ICODE_ORG)
						iComps_combineNextN(line->compilerInfo->firstComp, 1, compNext->iCode, compNext->iCat, compNext->color);

					// label:
					// [alpha][:] becomes [label]
					if ((compNext = (SComp*)line->compilerInfo->firstComp->ll.next) && (line->compilerInfo->firstComp->iCode == _ICODE_ALPHA || line->compilerInfo->firstComp->iCode == _ICODE_ALPHANUMERIC) && compNext->iCode == _ICODE_COLON)
						iComps_combineNextN(line->compilerInfo->firstComp, 1, _ICODE_LABEL, compNext->iCat, compNext->color);
			}


		//////////
		// Return the first component
		//////
			return(line->compilerInfo->firstComp);
	}




//////////
//
// Called to parse the indicated line of source code
//
//////
	void iCompileSourceCodeLine(SEM* asmFile, SLine* line, s32* tnErrors, s32* tnWarnings, s32 tnPass)
	{
		s32						lnI;
		u32						lnAddress;
		bool					llFailure;
		SCommand*				cmd;
		SComp*					comp[6];
		SOppie1Instruction*		instr;


		//////////
		// Grab as many components as there are
		//////
			// Reset to NULLs
			for (lnI = 0; lnI < 6; lnI++)
				comp[lnI] = NULL;

			// Load whatever's possible
			if ((comp[0] = line->compilerInfo->firstComp) && (comp[1] = (SComp*)comp[0]->ll.next) && (comp[2] = (SComp*)comp[1]->ll.next) && (comp[3] = (SComp*)comp[2]->ll.next) && (comp[4] = (SComp*)comp[3]->ll.next) && (comp[5] = (SComp*)comp[4]->ll.next))
			{
				// Placeholder, just used to load as many as are available up to five
			}


		//////////
		// Make sure we have something to do
		//////
			if (comp[1] && comp[1]->iCode != _ICODE_COMMENT)
			{
				// Populate as many components as follow
				for (cmd = (SCommand*)&gsCommands[0]; cmd && cmd->cmdType != -1; cmd++)
				{
					// Iterate for any matching components
					for (lnI = 0, llFailure = false; lnI < 6; lnI++)
					{
						// Is this line valid?
						if (cmd->comp[lnI].iCode == -1 && cmd->comp[lnI].iCode2 == -1 && cmd->comp[lnI].iCat == -1)
						{
							// Nothing on this line

						} else {
							// This line has something, does it match up?
							if (		(cmd->comp[lnI].iCode	== -1 || cmd->comp[lnI].iCode	== comp[lnI]->iCode)
									&&	(cmd->comp[lnI].iCode2	== -1 || cmd->comp[lnI].iCode2	== comp[lnI]->iCode)
									&&	(cmd->comp[lnI].iCat	== -1 || cmd->comp[lnI].iCat	== comp[lnI]->iCode)	)
							{
								// If we enter this block, a full match was made here
								// No code goes here, it's just coded this way to capture the logic condition without using the awkward reverse logic in the above statement

							} else {
								// If we get to any component which fails, then this is not a match
								llFailure = true;
								break;
							}
						}
					}

					// When we get here, we either have a full match on this command, or a failure to match at some point
					if (!llFailure)
					{
						// A full match
						instr = (SOppie1Instruction*)line->compilerInfo->extra_info;
						switch (cmd->opcodeType)
						{
							//////////
							// ORR -- Opcode,Register,Register
							//////
							case _ORR:
								if (cmd->_uniqueHandler)
								{
									// There is a unique handler to setup the values
									cmd->uniqueHandler(cmd, line, comp[0], tnPass);

								} else {
									// Standard handler
									if (tnPass == 1)
									{
										if ((cmd->opcode & ~_OPCODE_MASK) == _OPCODE_THREE_BITS)
										{
											// 3-bit encoding
											instr->orr.ooo = cmd->opcode & _OPCODE_MASK;

										} else {
											// 4-bit encoding
											instr->orr.oooo = cmd->opcode & _OPCODE_MASK;
										}

										// Store the registers
										instr->orr.rd = iGetRegisterEncoding(comp[1]);
										instr->orr.rs = iGetRegisterEncoding(comp[1]);
									}
									// Encoding is complete
								}
								break;


							//////////
							// ORA -- Opcode,register,address
							//////
							case _ORA:
								if (cmd->_uniqueHandler)
								{
									// There is a unique handler to setup the values
									cmd->uniqueHandler(cmd, line, comp[0], tnPass);

								} else {
									// Standard handler
									if (tnPass == 2)
									{
										// Grab the address
										switch (comp[cmd->componentLabelOrNumber]->iCode)
										{
											case _ICODE_ALPHA:
											case _ICODE_ALPHANUMERIC:
												// Label
												lnAddress = iGetLabelAddress(asmFile, comp[cmd->componentLabelOrNumber]);
												break;

											case _ICODE_NUMERIC:
												// Hard address
												// Note:  This address is in the raw positive numeric value, the sign is stored as a separate bit
												lnAddress = iComps_getAs_s32(comp[cmd->componentLabelOrNumber]);
												break;
										}

										// Store the upper 3-bits of the address
										instr->ora.aaa		= (lnAddress & 0x700) >> 8;

										// Store the lower 8-bits of the address
										instr->ora.aaaaaaaa	= (lnAddress & 0xff);
										// Encoding is complete

									} else {
										// Always 3-bit encoding
										instr->ora.ooo = cmd->opcode & _OPCODE_MASK;

										// Store the register
										instr->ora.rd = iGetRegisterEncoding(comp[cmd->componentRegister]);
										// First-pass encoding is complete
									}
								}
								break;


							//////////
							// Branch,Sign,Address
							//////
							case _BSA:
								if (cmd->_uniqueHandler)
								{
									// There is a unique handler to setup the values
									cmd->uniqueHandler(cmd, line, comp[0], tnPass);

								} else {
									// Standard handler
									if (tnPass == 2)
									{
										// Grab the address
										switch (comp[cmd->componentLabelOrNumber]->iCode)
										{
											case _ICODE_ALPHA:
											case _ICODE_ALPHANUMERIC:
												// Label
												lnAddress = iGetLabelAddress(asmFile, comp[cmd->componentLabelOrNumber]);
												break;

											case _ICODE_NUMERIC:
												// Hard address
												// Note:  This address is in the raw positive numeric value, the sign is stored as a separate bit
												lnAddress = iComps_getAs_s32(comp[cmd->componentLabelOrNumber]);
												break;
										}

										// Store the upper 2-bits of the address
										instr->bsa.aa		= (lnAddress & 0x300) >> 8;

										// Store the lower 8-bits of the address
										instr->bsa.aaaaaaaa	= (lnAddress & 0xff);
										// Encoding is complete

									} else {
										// Always 5-bit encoding
										instr->bsa.ooooo = cmd->opcode & _OPCODE_MASK;

										// Store the sign
										instr->bsa.s = cmd->opcodeSign;
										// First-pass encoding is complete
									}
								}
								break;

							default:
								// It's not a standard instruction, but is likely some compiler directive or data assignment
								if (cmd->_uniqueHandler)
								{
									// Use the custom handler
									cmd->uniqueHandler(cmd, line, comp[0], tnPass);

								} else {
									// Should never happen
									// Internal consistency error
_asm int 3;
								}
						}
					}

				}
				// If we get here, we've exhausted our command patterns, and this line is unknown.
				printf("Unrecognized command on line %u\n", line->lineNumber);
			}
	}




//////////
//
// Called to convert the component to its actual register encoding for the instruction
//
//////
	u32 iGetRegisterEncoding(SComp* comp)
	{
		switch (comp->iCode)
		{
			case _ICODE_R1:
				return(_R1);
				break;

			case _ICODE_R2:
				return(_R2);
				break;

			case _ICODE_R3:
				return(_R3);
				break;

			case _ICODE_R4:
				return(_R4);
				break;

			default:
				// Should never happen.
				// Indicates an internal programming error
				// Check the call stack.  It should have something passing a component which is only an _ICODE_RN register.
				break;
		}
_asm int 3;
		return(-1);
	}




//////////
//
// Called to search for the indicated label and return its address (org or origin)
//
//////
	u32 iGetLabelAddress(SEM* asmFile, SComp* compLabelSrch)
	{
		SLine*					line;
		SComp*					compLabelThis;
		SOppie1Instruction*		instr;


		// Iterate through every line to find the label
		for (	line = asmFile->firstLine;
				line;
				line = (SLine*)line->ll.next)
		{
			// Is this one a label
			instr = (SOppie1Instruction*)line->compilerInfo->extra_info;
			if (instr->isLabel)
			{
				//////////
				// Grab the component
				//////
					compLabelThis = iComps_getNth(line->compilerInfo->firstComp, instr->labelComponentNumber);


				//////////
				// Is it a match?
				//////
					if (compLabelThis->length - 1 == compLabelSrch->length)
					{
						// They're the same length, are they the same?
						if (_memicmp(	compLabelThis->line->sourceCode->data_s8	+ compLabelThis->start,
										compLabelSrch->line->sourceCode->data_s8	+ compLabelSrch->start,
										compLabelSrch->length) == 0)
						{
							// It is a match
							return(instr->org);
						}
					}

			}
		}
		// If we get here, not found
		printf("Label not found on line %u\n", line->lineNumber);
		exit(-4);
	}




//////////
//
// Called to handle the .ORG command
//
//////
	void iCompile_orgHandler(SCommand* cmd, SLine* line, SComp* compFirst, s32 tnPass)
	{
	}




//////////
//
// Called to handle the label assignment
//
//////
	void iCompile_labelHandler(SCommand* cmd, SLine* line, SComp* compFirst, s32 tnPass)
	{
	}




//////////
//
// Called to handle the db N dup 0 memory assignment
//
//////
	void iCompile_dbDupHandler(SCommand* cmd, SLine* line, SComp* compFirst, s32 tnPass)
	{
	}
