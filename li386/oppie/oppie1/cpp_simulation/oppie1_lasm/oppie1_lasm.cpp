//////////
//
// /libsf/li386/oppie/oppie1/cpp_simulation/oppie1_lasm/oppie1_lasm.cpp
//
//////
//    _     _ _     _____ _____ 
//   | |   (_) |__ / ____|  ___|
//   | |   | | '_ \\___ \|  __|
//   | |___| | |_) |___) | |
//   |_____|_|_.__/_____/|_|
//
//   Liberty Software Foundation
// and the Village Freedom Project
//   __     _______     ____  
//   \ \   / /  ___| __|  _ \ 
//    \ \ / /| |_ | '__| |_) |
//     \ V / |  _|| |  |  __/ 
//      \_/  |_|  |_|  |_|
//
//////
// Version 0.01
// Copyright (c) 2014 by Rick C. Hodgin
//////
// Last update:
//     Nov.30.2014
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
// Known issues:
//		(1) If multiple labels of the same name are used, only the first one is referenced.
//
// Please report any bugs at the location shown at the visual-freepro.org site above.
//
//////


//////////
// Uses Visual FreePro, Jr's existing parsing facilities to simplify our processing
//////
	#define _NONVJR_COMPILE		// Turns off some features in VJr that fail on compilation from here
	#define _BMP_LOCALITY 1		// Force definitions to be local
	#include "\libsf\source\vjr\source\vjr.h"
	#undef main


//////////
// Instruction encoding
//////
	#include "..\common\instructions.h"
	#include "oppie1_lasm.h"
	#include "..\oppie1\debo1_disasm.cpp"




//////////
//
// Top level lasm1 assembler
//
//////
	int main(int argc, char* argv[])
	{
		s32					lnI, lnErrors, lnWarnings, lnOrg, numread;
		bool				llMap;
		SEM*				asmFile;
		SBuilder*			map;
		SLine*				line;
		FILE*				lfh;
		SOppie1Instruction*	instr;
		s8					buffer[2048];
		s8					output[2048];


//////////
//
// 		SBsa				bsa;
// 		SOra				ora;
// 		SOrr				orr;
//
// 		memset(&bsa, 0, sizeof(bsa));
// 		memset(&ora, 0, sizeof(ora));
// 		memset(&orr, 0, sizeof(orr));
// 		bsa.ooooo	= 0x1f;
// 		ora.ooo		= 0x7;
// 		orr.oooo	= 0xf;
// 		_asm nop;
//
//////


		//////////
		// Identify ourself
		//////
			printf("LibSF Oppie-1 Assembler v0.02\n");


		//////////
		// Initialize Visual FreePro, Jr. stuff
		///////
			InitializeCriticalSection(&cs_uniqueIdAccess);
			InitializeCriticalSection(&cs_logData);


		//////////
		// lasm1 only takes one parameter, the input filename
		//////
			if (argc < 2 || argc > 3)
			{
				// Display syntax
				printf("Usage:  lasm1 myfile.asm /map\n");

			} else {
				// Allocate our load manager
				asmFile = iSEM_allocate(true);
				if (!asmFile)
				{
					// Internal error
					printf("Internal error allocating load buffer\n");

				} else {
					// Try to physically load it
					if (!iSEM_load_fromDisk(NULL, asmFile, argv[1], false, false))
					{
						// Error opening
						printf("Unable to open %s\n", argv[1]);

					} else {
						// Indicate we're in progress
						printf("Assembling %s\n", argv[1]);

						// See if they specified /map
						llMap = (argc == 3 && strlen(argv[2]) == 4 && _memicmp(argv[2], "/map", 4) == 0);

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
								if (line->compilerInfo->firstComp && line->compilerInfo->firstComp->iCode != _ICODE_COMMENT)
									iCompileSourceCodeLine(asmFile, line, &lnErrors, &lnWarnings, 1);
							}

							// If there were any errors, exit
							if (lnErrors != 0)
								exit_program(-1);


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
									instr = (SOppie1Instruction*)line->compilerInfo->first_extraInfo;
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
								exit_program(-2);


						//////////
						// When we get here, every line has compiled out.
						// Look for memory locations which will overlay
						//////
							memset(output, 0, sizeof(output));
							memset(buffer, 0, sizeof(buffer));
							for (	line = asmFile->firstLine;
									line;
									line = (SLine*)line->ll.next	)
							{
								//////////
								// Grab the instruction for this line
								//////
									instr = (SOppie1Instruction*)line->compilerInfo->first_extraInfo;
									if (instr->size != 0)
									{
										// There's some content there
										if (instr->isData)
										{
											//////////
											// Store the data
											//////
												for (lnI = 0; lnI < instr->size; lnI++)
												{
													// Increase our test buffer count
													++buffer[instr->org + lnI];
													if (buffer[instr->org + 1] > 1)
													{
														// We've overwritten a prior memory value
														printf("Addresses overlap on line %u\n", line->lineNumber);
														exit_program(-3);
													}

													// Copy the raw data
													output[instr->org + lnI] = instr->data[lnI];
												}

										} else if (instr->isInstruction) {
											//////////
											// Store the instruction
											//////
												if (instr->org + instr->size - 1 >= 2048)
												{
													// It will wrap around the end
													printf("Invalid address for line %u\n", line->lineNumber);
													exit_program(-4);
												}


											//////////
											// Increase for first byte
											//////
												++buffer[instr->org];
												output[instr->org] = instr->ora.i_data1;
												if (buffer[instr->org] > 1)
												{
													// We've overwritten a prior memory value
													printf("Addresses overlap on line %u\n", line->lineNumber);
													exit_program(-5);
												}


											//////////
											// If there's a second byte, do that one as well
											//////
												if (instr->size == 2)
												{
													++buffer[instr->org + 1];
													output[instr->org + 1] = instr->ora.i_data2;
													if (buffer[instr->org + 1] > 1)
													{
														// We've overwritten a prior memory value
														printf("Addresses overlap on line %u\n", line->lineNumber);
														exit_program(-6);
													}
												}
										}
									}
							}


						//////////
						// Create the otuput file
						//////
							memcpy(argv[1] + strlen(argv[1]) - 4, ".img", 4);
							lfh = fopen(argv[1], "wb+");
							if (!lfh)
							{
								// Could not create the output file
								printf("Error creating %s\n", argv[1]);
								exit_program(-7);
							}


						//////////
						// Write the buffer
						//////
							numread = fwrite(output, 1, 2048, lfh);
							fclose(lfh);
							if (numread != 2048)
							{
								printf("Error writing 2048 bytes\n");
								exit_program(-8);

							} else {
								// Success
								printf("Wrote 2048 bytes\n");
							}


						//////////
						// They specified a map file
						//////
							if (llMap)
							{
								//////////
								// Allocate our output buffer
								//////
									iBuilder_createAndInitialize(&map, -1);


								//////////
								// Iterate through each line and convey data, or disassembly for the output
								//////
									for (	line = asmFile->firstLine, lnErrors = 0, lnWarnings = 0;
											line;
											line = (SLine*)line->ll.next	)
									{
										//////////
										// Grab the instruction for this line
										//////
											instr = (SOppie1Instruction*)line->compilerInfo->first_extraInfo;
											if (instr->size != 0)
											{
												//////////
												// Show the address:
												//////
													sprintf(buffer, "%03x: \0", instr->org);
													iBuilder_appendData(map, buffer, -1);


												//////////
												// There's some content there
												//////
													memset(buffer, 0, sizeof(buffer));
													if (instr->isData)
													{
														//////////
														// Show the data
														//////
															for (lnI = 0; lnI < instr->size; lnI++)
																sprintf(buffer + (lnI * 3), "%02x%s", instr->data[lnI], ((lnI + 1 < instr->size) ? ",\0" : " \0"));


													} else if (instr->isInstruction) {
														// Disassemble the instruction
														iiDebo1_decodeAssembly(buffer, instr->org, false, true, (u8*)output);
														memset(buffer + strlen(buffer), 32, 64);
														buffer[45] = '/';
														buffer[46] = '/';
														memcpy(buffer + 48, line->sourceCode->data_s8, line->sourceCode_populatedLength);
														buffer[48 + line->sourceCode_populatedLength] = 0;
													}


												//////////
												// Append the data
												//////
													iBuilder_appendData(map, buffer, strlen(buffer));
													iBuilder_appendCrLf(map);
											}

									}


								//////////
								// Save the map file
								//////
									memcpy(argv[1] + strlen(argv[1]) - 4, ".map", 4);
									iBuilder_asciiWriteOutFile(map, (u8*)argv[1]);

							}

					}
				}
			}


		//////////
		// Task completed (one way or another :-))
		//////
			exit_program(0);
	}




//////////
//
// Added for debugging, allows trapping to see where the program exits.
//
//////
	void exit_program(int tnExitCode)
	{
		exit(tnExitCode);
	}




//////////
//
// Parses the text of the line into any known tokens
//
//////
	SComp* iParseSourceCodeLine(SLine* line)
	{
		SComp*				comp;
		SComp*				compNext;
		SOppie1Instruction*	instr;


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
					exit_program(-999);
				}
			}

		//////////
		// Make sure we have our SOppie1Instruction allocated
		//////
			if (!line->compilerInfo->first_extraInfo)
			{
				// Allocate a structure
				instr = (SOppie1Instruction*)malloc(sizeof(SOppie1Instruction));
				if (!instr)
				{
					// Should never happen
					printf("Out of memory\n");
					exit_program(-998);
				}

				// Add to the chain
				iLl_appendExistingNodeAtEnd((SLL**)&line->compilerInfo->first_extraInfo, (SLL*)instr);

				// Initialize to NULLs
				memset(line->compilerInfo->first_extraInfo, 0, sizeof(SOppie1Instruction));
			}


		//////////
		// Parse out the line
		//////
			iComps_translate_sourceLineTo(&cgcFundamentalSymbols[0], line);
			if (!line->compilerInfo->firstComp)
				return(NULL);	// Nothing to compile on this blank line

			// Remove whitespaces [x][whitespace][y] becomes [x][y]
			iComps_remove_leadingWhitespaces(line);
			if (!line->compilerInfo->firstComp)
				return(NULL);	// Nothing to compile on this line with only whitespaces


		//////////
		// We don't need to process comment-only lines
		//////
			if ((comp = line->compilerInfo->firstComp) && (comp->iCode == _ICODE_COMMENT || comp->iCode == _ICODE_LINE_COMMENT))
			{
				//////////
				// Combine every item after this to a single comment component or easy parsing and handling
				//////
					iComps_combineN(comp, 99999, comp->iCode, comp->iCat, comp->color);

			} else {
				//////////
				// Perform natural source code fixups
				//////
					iComps_remove_startEndComments(line);		// Remove /* comments */
					iComps_fixup_naturalGroupings(line);			// Fixup natural groupings [_][aaa][999] becomes [_aaa999], [999][.][99] becomes [999.99], etc.
					iComps_remove_whitespaces(line);				// Remove all whitespaces after everything else was parsed [use][whitespace][foo] becomes [use][foo]


				//////////
				// Translate sequences to known keywords
				//////
					iComps_translate_toOthers((SAsciiCompSearcher*)&cgcKeywordsOppie1[0], line->compilerInfo->firstComp, false);


				//////////
				// Perform fixups that are unique to Oppie-1
				//////
					// .org
					// [.org] as a _ICODE_DOT_VARIABLE, becomes [.org] as _ICODE_DOT_ORG
					if (comp->iCode == _ICODE_DOT_VARIABLE && comp->length == 4 && _memicmp(comp->line->sourceCode->data_s8 + comp->start + 1, "org", 3) == 0)
						comp->iCode = _ICODE_ORG;

					// label:
					// [alpha][:] becomes [label]
					if ((compNext = (SComp*)comp->ll.next) && (comp->iCode == _ICODE_ALPHA || comp->iCode == _ICODE_ALPHANUMERIC) && compNext->iCode == _ICODE_COLON)
						iComps_combineN(comp, 2, _ICODE_LABEL, compNext->iCat, compNext->color);
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
		bool					llMatchFailure, llisPassDone;
		SCommand*				cmd;
		SComp*					comp[6];
		SOppie1Instruction*		instr;


//////////
// For debugging:
// 
	s8 bufferComps[2048];
	iComps_visualize(line->compilerInfo->firstComp, 999, bufferComps, sizeof(bufferComps), true, &cgcKeywordsOppie1[0], NULL);

	if (line->lineNumber == 100)
		_asm nop;
// 
//////


		//////////
		// Grab as many components as there are
		//////
			// Reset to NULLs
			memset(&comp[0], 0, sizeof(comp));
	
			// Load whatever's possible
			if ((comp[0] = line->compilerInfo->firstComp) && (comp[1] = (SComp*)comp[0]->ll.next) && (comp[2] = (SComp*)comp[1]->ll.next) && (comp[3] = (SComp*)comp[2]->ll.next) && (comp[4] = (SComp*)comp[3]->ll.next) && (comp[5] = (SComp*)comp[4]->ll.next))
			{
				// Placeholder, just used to load as many as are available up to five
			}


		//////////
		// Make sure we have something to do
		//////
			if (comp[0] && comp[0]->iCode != _ICODE_COMMENT)
			{
				// Populate as many components as follow
				for (cmd = (SCommand*)&gsCommands[0], llisPassDone = false; cmd && cmd->cmdType != -1 && !llisPassDone; cmd++)
				{
					// Iterate for any matching components
					for (lnI = 0, llMatchFailure = false; lnI < 6; lnI++)
					{
						// Is this line valid?
						if (cmd->comp[lnI].iCode == -1 && cmd->comp[lnI].iCode2 == -1 && cmd->comp[lnI].iCat == -1)
						{
							// There's Nothing on this line, which means it's an implicit hit/match

						} else {
							// This line has something, does it match up?
							if (!comp[lnI] ||	(	(	(cmd->comp[lnI].iCode	!= -1 && cmd->comp[lnI].iCode	== comp[lnI]->iCode)
													||	(cmd->comp[lnI].iCode2	!= -1 && cmd->comp[lnI].iCode2	== comp[lnI]->iCode)
													||	(cmd->comp[lnI].iCode	== -1 && cmd->comp[lnI].iCode2	== -1))
													&&	(cmd->comp[lnI].iCat	== -1 || cmd->comp[lnI].iCat	== comp[lnI]->iCat)
												)
											)
							{
								// If we enter this block, a full match was made here
								// No code goes here, it's just coded this way to capture the logic condition without using the awkward reverse logic in the above statement

							} else {
								// If we get to any component which fails, then this is not a match
								llMatchFailure = true;
								break;
							}
						}
					}

					// When we get here, we either have a full match on this command, or a failure to match at some point
					if (!llMatchFailure)
					{
						// A full match
						instr = (SOppie1Instruction*)line->compilerInfo->first_extraInfo;
						switch (cmd->opcodeType)
						{
							//////////
							// ORR -- Opcode,Register,Register
							//////
							case _ORR:
								instr->isInstruction = true;
								if (cmd->_uniqueHandler)
								{
									// There is a unique handler to setup the values
									cmd->uniqueHandler(cmd, line, comp[0], tnPass);
									return;

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
										instr->orr.rd	= iGetRegisterEncoding(comp[1]);
										instr->orr.rs	= iGetRegisterEncoding(comp[3]);
										instr->size		= 1;
									}
									// Encoding is complete
									return;
								}
								break;


							//////////
							// ORA -- Opcode,register,address
							//////
							case _ORA:
								instr->isInstruction = true;
								if (cmd->_uniqueHandler)
								{
									// There is a unique handler to setup the values
									cmd->uniqueHandler(cmd, line, comp[0], tnPass);
									return;

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
										return;

									} else {
										// Always 3-bit encoding
										instr->ora.ooo = cmd->opcode & _OPCODE_MASK;

										// Store the register
										instr->ora.rd	= iGetRegisterEncoding(comp[cmd->componentRegister]);

										// First-pass encoding is complete
										instr->size		= 2;
										llisPassDone	= true;
									}
								}
								break;


							//////////
							// Branch,Sign,Address
							//////
							case _BSA:
								instr->isInstruction = true;
								if (cmd->_uniqueHandler)
								{
									// There is a unique handler to setup the values
									cmd->uniqueHandler(cmd, line, comp[0], tnPass);
									return;

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

										// Adjust the target into a relative address
										if (lnAddress >= (u32)(instr->org + instr->size))
										{
											// We're jumping positive
											lnAddress		= lnAddress - (instr->org + instr->size);
											instr->bsa.s	= 0;

										} else {
											// We're jumping negative
											lnAddress		= (instr->org + instr->size) - lnAddress;
											instr->bsa.s	= 1;
										}

										// Store the upper 2-bits of the address
										instr->bsa.aa		= (lnAddress & 0x300) >> 8;

										// Store the lower 8-bits of the address
										instr->bsa.aaaaaaaa	= (lnAddress & 0xff);
										// Encoding is complete
										return;

									} else {
										// Always 5-bit encoding
										instr->bsa.ooooo = cmd->opcode & _OPCODE_MASK;

										// Store the sign
										instr->bsa.s	= cmd->opcodeSign;

										// First-pass encoding is complete
										instr->size		= 2;
										llisPassDone	= true;
									}
								}
								break;

							default:
								// It's not a standard instruction, but is likely some compiler directive or data assignment
								if (cmd->_uniqueHandler)
								{
									// Use the custom handler
									cmd->uniqueHandler(cmd, line, comp[0], tnPass);
									return;

								} else {
									// Should never happen
									// Internal consistency error
_asm int 3;
								}
						}
					}

				}
				// If we get here, we've exhausted our command patterns, and this line is unknown.
				if (llMatchFailure)
				{
_asm int 3;
					printf("Unrecognized command on line %u\n", line->lineNumber);
				}
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
			instr = (SOppie1Instruction*)line->compilerInfo->first_extraInfo;
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
		printf("Label not found on line %u\n", compLabelSrch->line->lineNumber);
		exit_program(-4);

		// Required so the compiler doesn't complain
		return(0);
	}




//////////
//
// Called to handle the .ORG command
//
//////
	void iCompile_orgHandler(SCommand* cmd, SLine* line, SComp* compFirst, s32 tnPass)
	{
		s32						lnOrg;
		SOppie1Instruction*		instr;


		//////////
		// Grab the value, which is known to be a numeric value
		//////
			lnOrg = iComps_getAs_s32(iComps_getNth(compFirst, 1));
			if (lnOrg < 0 || lnOrg >= 2048)
			{
				// Invalid
				printf("Invalid .ORG location on line %u\n", line->lineNumber);
				exit_program(-999);
			}


		//////////
		// Setup the instruction
		//////
			instr = (SOppie1Instruction*)line->compilerInfo->first_extraInfo;
			instr->isOrg	= true;
			instr->org		= lnOrg;
	}




//////////
//
// Called to handle the label assignment
//
//////
	void iCompile_labelHandler(SCommand* cmd, SLine* line, SComp* compFirst, s32 tnPass)
	{
		SOppie1Instruction* instr;


		//////////
		// Setup the instruction
		//////
			instr = (SOppie1Instruction*)line->compilerInfo->first_extraInfo;
			instr->isLabel				= true;
			instr->labelComponentNumber	= cmd->componentLabelOrNumber;
	}




//////////
//
// Called to handle the db N dup 0 memory assignment
//
//////
	void iCompile_dbDupHandler(SCommand* cmd, SLine* line, SComp* compFirst, s32 tnPass)
	{
		s32						lnCount, lnValue;
		SOppie1Instruction*		instr;


		//////////
		// Grab the count and value
		//////
			lnCount = iComps_getAs_s32(iComps_getNth(compFirst, 1));
			if (lnCount < 0 || lnCount >= 2048)
			{
				// Invalid
				printf("Invalid DB count on line %u\n", line->lineNumber);
				exit_program(-999);
			}
			lnValue = iComps_getAs_s32(iComps_getNth(compFirst, 1));
			if (lnValue < 0 || lnValue > 255)
			{
				// Invalid
				printf("Invalid initialization value %u on line %u\n", lnValue, line->lineNumber);
				exit_program(-999);
			}


		//////////
		// Setup the instruction
		//////
			instr = (SOppie1Instruction*)line->compilerInfo->first_extraInfo;
			instr->isData	= true;
			instr->size		= lnCount;
			instr->data		= (u8*)malloc(lnCount);
			if (!instr->data)
			{
				// Should never happen
				printf("Out of memory on line %u\n", line->lineNumber);
				exit_program(-999);
			}

			// Initialize the data block
			memset(instr->data, lnValue, lnCount);
	}




//////////
//
// Called to handle the db N memory assignment
//
//////
	void iCompile_dbHandler(SCommand* cmd, SLine* line, SComp* compFirst, s32 tnPass)
	{
		s32						lnValue;
		SOppie1Instruction*		instr;


		//////////
		// Grab the value
		//////
			lnValue = iComps_getAs_s32(iComps_getNth(compFirst, 1));
			if (lnValue < 0 || lnValue > 255)
			{
				// Invalid
				printf("Invalid initialization value %u on line %u\n", lnValue, line->lineNumber);
				exit_program(-999);
			}


		//////////
		// Setup the instruction
		//////
			instr = (SOppie1Instruction*)line->compilerInfo->first_extraInfo;
			instr->isData	= true;
			instr->size		= 1;
			instr->data		= (u8*)malloc(1);
			if (!instr->data)
			{
				// Should never happen
				printf("Out of memory on line %u\n", line->lineNumber);
				exit_program(-999);
			}

			// Initialize the data block
			instr->data[0]	= (u8)lnValue;
	}
