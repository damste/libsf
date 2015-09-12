//////////
//
// /libsf/exodus/tools/debi/disasm.cpp
//
//////
// Version 0.80
// Copyright (c) 2014-2015 by Rick C. Hodgin
//////
// Last update:
//     Sep.12.2015
//////
// Change log:
//     Sep.12.2015 - Refactoring for Exodus OS tool support
//     Feb.13.2014 - Initial creation
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
//     http://www.visual-freepro.org/wiki/index.php/Repeat_License
//
// Thank you.  And may The Lord bless you richly as you lift up your life, your
// talents, your gifts, your praise, unto Him.  In Jesus' name I pray.  Amen.
//
//




//////////
//
// The Debi (Debug Intel (x86) architecture) disassembler module
//
//////
	void debi_disassemble(u8* data, u32 length, u32 address)
	{
		u32				lnCount, lnIterator, lnOffset, lnOpcode;	// Offset into the data block of assembly opcodes
		u8*				dd_data_root;
		u8*				op;
		u8*				lcb;
		SDisasmData		dd;											// Disassemble info data structure
		u8				tbuffer1[512];


		// Process through every block until we reach the end
		lnCount			= 0;
		lnOffset		= 0;
		memset(&dd, 0, sizeof(dd));
		dd.data			= data;
		dd.data_root	= data;
		while (lnOffset < length)
		{
			// Update the structure with decoded instruction information
			lnOpcode = data[lnOffset + dd.opcode_bytes];
			first_byte_functions[lnOpcode](data + lnOffset + dd.opcode_bytes, &dd);

			if (dd.opcode_bytes == 0)
				_asm int 3;

			// If there is information, display it
			if (dd.mnemonic)
			{
				// Move to the next position
				lnOffset += dd.opcode_bytes;
				
				// Show address and opcode bytes
				printf("%08X : %02X : ", (int)(address + lnOffset), (int)dd.opcode_bytes);
				for (lnIterator = 0; lnIterator < dd.opcode_bytes; lnIterator++)
					printf("%02x ", (int)dd.data[lnIterator]);
				
				// Update the operand pointer
				if (dd.destination_source_type == Memory)
				{
					switch (dd.operand_size)
					{
						case Byte:
							op = cgc_byte_ptr;
							break;
						case Word:
							op = cgc_word_ptr;
							break;
						case Dword:
							op = cgc_dword_ptr;
							break;
						case Qword:
							op = cgc_qword_ptr;
							break;
						case DQword:
							op = cgc_dqword_ptr;
							break;
						case Tbyte:
							op = cgc_tbyte_ptr;
							break;
						default:
							op = _null_string;
							break;
					}

				} else {
					op = _null_string;
				}
				
				// Upgrade the line_comment buffer
				sprintf((s8*)&tbuffer1[0], "\t\t\t%s", dd.line_comment);
				lcb = dd.line_comment ? &tbuffer1[0] : _null_string;
				
				// Show the instruction
				if (dd.operand1 && dd.operand2 && dd.operand3 && !dd.immediate)
					printf("\n\t%s\t%s,%s,%s%s\n", dd.mnemonic, dd.operand1, dd.operand2, dd.operand3, lcb);
					
				else if (dd.operand1 && dd.operand2 && !dd.immediate)
					printf("\n\t%s\t%s,%s%s\n", dd.mnemonic, dd.operand1, dd.operand2, lcb);
					
				else if (dd.operand1 && !dd.immediate)
					printf("\n\t%s\t%s%s\n", dd.mnemonic, dd.operand1, lcb);
					
				else if (dd.operand1 && dd.operand2 && dd.operand3 && dd.immediate)
					printf("\n\t%s\t%s%s,%s,%s,%s%s\n", dd.mnemonic, op, dd.operand1, dd.operand2, dd.operand3, dd.immediate, lcb);
					
				else if (dd.operand1 && dd.operand2 && dd.immediate)
					printf("\n\t%s\t%s%s,%s,%s%s\n", dd.mnemonic, op, dd.operand1, dd.operand2, dd.immediate, lcb);
					
				else if (dd.operand1 && dd.immediate)
					printf("\n\t%s\t%s%s,%s%s\n", dd.mnemonic, op, dd.operand1, dd.immediate, lcb);
					
				else if (dd.immediate)
					printf("\n\t%s\t%s%s%s\n", dd.mnemonic, op, dd.immediate, lcb);
					
				else
					printf("\n\t%s%s\n", dd.mnemonic, lcb);
					

				// Reset the structure
				dd_data_root	= dd.data_root + dd.opcode_bytes;
 				memset(&dd, 0, sizeof(dd));
				dd.data			= data + lnOffset;
				dd.data_root	= dd_data_root;

				if (dd.data_root != dd.data)
					_asm int 3;	// Oops, these should ALWAYS be in sync

				++lnCount;

			} else {
				_asm nop;
			}
		}
		printf("\nDecoded %u instructions\n", (int)lnCount);
	}




//////////
//
// Supporting functions
//
/////
	void extract_gp_reg_operand(SDisasmData* dd, u8 reg, u8** op, u32/*REGTYPE*/ rt)
	{
		if (rt == _8bit)
		{
			// 8-bit register
			extract_8bit_reg_operand(reg, op, _null_string);
		}
		else
		{
			// 16-bit or 32-bit immediate
			if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
				(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
			{
				// 32-bit addressing mode
				extract_32bit_reg_operand(reg, op, _null_string);
			}
			else
			{
				// 16-bit addressing mode
				extract_16bit_reg_operand(reg, op, _null_string);
			}
		}
	}
	
	void add_prefix_op(u8** op, u8* prefix_op)
	{
		// See if there's anything to prefix
		if (prefix_op == _null_string)
			return;	// nope
		
		// Replace the current value with the destination value
		sprintf((s8*)&prefix_op_buffer[0], "%s%s", prefix_op, *op);
		*op = &prefix_op_buffer[0];
	}

	void extract_8bit_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)			*op = cgc_al_reg;
		else if (reg == 1)		*op = cgc_cl_reg;
		else if (reg == 2)		*op = cgc_dl_reg;
		else if (reg == 3)		*op = cgc_bl_reg;
		else if (reg == 4)		*op = cgc_ah_reg;
		else if (reg == 5)		*op = cgc_ch_reg;
		else if (reg == 6)		*op = cgc_dh_reg;
		else if (reg == 7)		*op = cgc_bh_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_16bit_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)			*op = cgc_ax_reg;
		else if (reg == 1)		*op = cgc_cx_reg;
		else if (reg == 2)		*op = cgc_dx_reg;
		else if (reg == 3)		*op = cgc_bx_reg;
		else if (reg == 4)		*op = cgc_sp_reg;
		else if (reg == 5)		*op = cgc_bp_reg;
		else if (reg == 6)		*op = cgc_si_reg;
		else if (reg == 7)		*op = cgc_di_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_32bit_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)			*op = cgc_eax_reg;
		else if (reg == 1)		*op = cgc_ecx_reg;
		else if (reg == 2)		*op = cgc_edx_reg;
		else if (reg == 3)		*op = cgc_ebx_reg;
		else if (reg == 4)		*op = cgc_esp_reg;
		else if (reg == 5)		*op = cgc_ebp_reg;
		else if (reg == 6)		*op = cgc_esi_reg;
		else if (reg == 7)		*op = cgc_edi_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_64bit_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)			*op = cgc_rax_reg;
		else if (reg == 1)		*op = cgc_rcx_reg;
		else if (reg == 2)		*op = cgc_rdx_reg;
		else if (reg == 3)		*op = cgc_rbx_reg;
		else if (reg == 4)		*op = cgc_rsp_reg;
		else if (reg == 5)		*op = cgc_rbp_reg;
		else if (reg == 6)		*op = cgc_rsi_reg;
		else if (reg == 7)		*op = cgc_rdi_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_test_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)			*op = cgc_tr0_reg;
		else if (reg == 1)		*op = cgc_tr1_reg;
		else if (reg == 2)		*op = cgc_tr2_reg;
		else if (reg == 3)		*op = cgc_tr3_reg;
		else if (reg == 4)		*op = cgc_tr4_reg;
		else if (reg == 5)		*op = cgc_tr5_reg;
		else if (reg == 6)		*op = cgc_tr6_reg;
		else if (reg == 7)		*op = cgc_tr7_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_debug_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)			*op = cgc_dr0_reg;
		else if (reg == 1)		*op = cgc_dr1_reg;
		else if (reg == 2)		*op = cgc_dr2_reg;
		else if (reg == 3)		*op = cgc_dr3_reg;
		else if (reg == 4)		*op = cgc_dr4_reg;
		else if (reg == 5)		*op = cgc_dr5_reg;
		else if (reg == 6)		*op = cgc_dr6_reg;
		else if (reg == 7)		*op = cgc_dr7_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_control_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)			*op = cgc_cr0_reg;
		else if (reg == 1)		*op = cgc_cr1_reg;
		else if (reg == 2)		*op = cgc_cr2_reg;
		else if (reg == 3)		*op = cgc_cr3_reg;
		else if (reg == 4)		*op = cgc_cr4_reg;
		else if (reg == 5)		*op = cgc_cr5_reg;
		else if (reg == 6)		*op = cgc_cr6_reg;
		else if (reg == 7)		*op = cgc_cr7_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_mmx_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)			*op = cgc_mm0_reg;
		else if (reg == 1)		*op = cgc_mm1_reg;
		else if (reg == 2)		*op = cgc_mm2_reg;
		else if (reg == 3)		*op = cgc_mm3_reg;
		else if (reg == 4)		*op = cgc_mm4_reg;
		else if (reg == 5)		*op = cgc_mm5_reg;
		else if (reg == 6)		*op = cgc_mm6_reg;
		else if (reg == 7)		*op = cgc_mm7_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_xmmx_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)			*op = cgc_xmm0_reg;
		else if (reg == 1)		*op = cgc_xmm1_reg;
		else if (reg == 2)		*op = cgc_xmm2_reg;
		else if (reg == 3)		*op = cgc_xmm3_reg;
		else if (reg == 4)		*op = cgc_xmm4_reg;
		else if (reg == 5)		*op = cgc_xmm5_reg;
		else if (reg == 6)		*op = cgc_xmm6_reg;
		else if (reg == 7)		*op = cgc_xmm7_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_stx_reg_operand(u8 reg, u8** op, u8* prefix_op)
	{	
		if (reg == 0)			*op = cgc_st0_reg;
		else if (reg == 1)		*op = cgc_st1_reg;
		else if (reg == 2)		*op = cgc_st2_reg;
		else if (reg == 3)		*op = cgc_st3_reg;
		else if (reg == 4)		*op = cgc_st4_reg;
		else if (reg == 5)		*op = cgc_st5_reg;
		else if (reg == 6)		*op = cgc_st6_reg;
		else if (reg == 7)		*op = cgc_st7_reg;
		
		add_prefix_op(op, prefix_op);
	}

	void extract_8bit_reg_operands_1_2(u8* data, SDisasmData* dd)
	{
		extract_8bit_reg_operand((*data & 0xf0) >> 4, &dd->operand1, _null_string);
		extract_8bit_reg_operand( *data & 0x0f,		  &dd->operand2, _null_string);
		dd->operand_size = Byte;
	}
	
	void store_prefix_mnemonics(u8* buffer, SDisasmData* dd)
	{
		// Refer to PREFIX enums in structs.h
		// Note:  Proper syntax does not allow for multiple of these override prefixes,
		//        though they can be physically encoded and will be processed by the CPU
		sprintf((s8*)buffer, "%s%s%s%s%s%s%s", 
			dd->prefixes & LOCK  ? (s8*)"[lock] " : (s8*)_null_string,
			dd->prefixes & CSREG ? (s8*)cgc_cs_colon : (s8*)_null_string,
			dd->prefixes & DSREG ? (s8*)cgc_ds_colon : (s8*)_null_string,
			dd->prefixes & ESREG ? (s8*)cgc_es_colon : (s8*)_null_string,
			dd->prefixes & FSREG ? (s8*)cgc_fs_colon : (s8*)_null_string,
			dd->prefixes & GSREG ? (s8*)cgc_gs_colon : (s8*)_null_string,
			dd->prefixes & SSREG ? (s8*)cgc_ss_colon : (s8*)_null_string);
	}

	void extract_modrm_16bit_address_mode(u8* data, SDisasmData* dd, u8* op_buffer, u8** op1, u8** op2, ERegType rt, bool do_reg, u8* prefix_op1)
	{
		u8 t;
		u8 prefix_buffer[32];
		u8 mod = (*data & 0xc0) >> 6;	// Upper 2 bits
		u8 r   = (*data & 0x38) >> 3;	// Next 3 lower
		u8 rm  = (*data & 0x07);		// Bottom 3


		// Load any "cs:", "ss:" stuff
		store_prefix_mnemonics(&prefix_buffer[0], dd);


		// See if we're supposed to order reg/rm operands in the reverse order
		if (dd->regrm_reversed)
		{
			// swap
			t = rm;
			rm = r;
			r = t;
		}


		// Figure out what to do here
		switch (mod)
		{
			case 0:
				dd->opcode_bytes			+= 1;
				dd->destination_source_type	= Memory;
				if (dd->is_reversed)
					dd->operand2_source_type = Memory;
				else
					dd->operand1_source_type = Memory;


				switch (rm)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[bx+si]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[bx+di]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[bp+si]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[bp+di]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 4:
						sprintf((s8*)op_buffer, "%s%s[si]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[di]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 6:
						// 16-bit displacement value
						sprintf((s8*)op_buffer, "%s%s[%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						dd->opcode_bytes += 2;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[bx]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
				}
				break;

			case 1:
				dd->opcode_bytes			+= 2;
				dd->destination_source_type	= Memory;
				if (dd->is_reversed)
					dd->operand2_source_type = Memory;
				else
					dd->operand1_source_type = Memory;


				switch (rm)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[bx+si+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[bx+di+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[bp+si+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[bp+di+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 4:
						sprintf((s8*)op_buffer, "%s%s[si+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[di+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[bp+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[bx+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
				}
				break;

			case 2:
				dd->opcode_bytes += 3;
				dd->destination_source_type	= Memory;
				if (dd->is_reversed)
					dd->operand2_source_type = Memory;
				else
					dd->operand1_source_type = Memory;


				switch (rm)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[bx+si+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[bx+di+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[bp+si+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[bp+di+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						break;
					case 4:
						sprintf((s8*)op_buffer, "%s%s[si+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[di+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[bp+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[bx+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u16*)(data + 1));
						*op1 = op_buffer;
						break;
				}
				break;

			case 3:
				dd->opcode_bytes += 1;
				dd->destination_source_type	= Register;
				if (dd->is_reversed)
					dd->operand2_source_type = Memory;
				else
					dd->operand1_source_type = Memory;


				switch (dd->force_reg ? dd->force_reg : 
						rt != _varies ? rt :
						dd->is_reversed ? dd->operand2_regtype : dd->operand1_regtype)
				{
					case _8bit:
						extract_8bit_reg_operand(rm, op1, prefix_op1);
						break;
					case _16bit:
						extract_16bit_reg_operand(rm, op1, prefix_op1);
						break;
					case _32bit:
						extract_32bit_reg_operand(rm, op1, prefix_op1);
						break;
					case _64bit:
						extract_64bit_reg_operand(rm, op1, prefix_op1);
						break;
					case _mmx:
						extract_mmx_reg_operand(rm, op1, prefix_op1);
						break;
					case _xmmx:
						extract_xmmx_reg_operand(rm, op1, prefix_op1);
						break;
				}
				break;

		}
		
		if (do_reg)
		{
			// Store operand2
			if (dd->is_reversed)
				dd->operand1_source_type = Register;
			else
				dd->operand2_source_type = Register;


			switch (dd->force_reg ? dd->force_reg : 
					rt != _varies ? rt :
					dd->is_reversed ? dd->operand1_regtype : dd->operand2_regtype)
			{
				case _8bit:
					extract_8bit_reg_operand(r, op2, _null_string);
					dd->operand_size = Byte;
					break;
				case _16bit:
					extract_16bit_reg_operand(r, op2, _null_string);
					dd->operand_size = Word;
					break;
				case _32bit:
					extract_32bit_reg_operand(r, op2, _null_string);
					dd->operand_size = Dword;
					break;
				case _64bit:
					extract_64bit_reg_operand(r, op2, _null_string);
					dd->operand_size = Qword;
					break;
				case _mmx:
					extract_mmx_reg_operand(r, op2, _null_string);
					dd->operand_size = Qword;
					break;
				case _xmmx:
					extract_xmmx_reg_operand(r, op2, _null_string);
					dd->operand_size = DQword;
					break;
			}
		}
	}

	void extract_modrm_32bit_address_mode(u8* data, SDisasmData* dd, u8* op_buffer, u8** op1, u8** op2, ERegType rt, bool do_reg, u8* prefix_op1)
	{
		u8 t;
		u8 prefix_buffer[32];
		u8 mod = (*data & 0xc0) >> 6;	// Upper 2 bits
		u8 r   = (*data & 0x38) >> 3;	// Next 3 lower
		u8 rm  = (*data & 0x07);		// Bottom 3


		// Load any "cs:", "ss:" stuff
		store_prefix_mnemonics(&prefix_buffer[0], dd);


		// See if we're supposed to order reg/rm operands in the reverse order
		if (dd->regrm_reversed)
		{
			// swap
			t = rm;
			rm = r;
			r = t;
		}


		// Figure out what to do here
		switch (mod)
		{
			case 0:
				dd->opcode_bytes			+= 1;
				dd->destination_source_type	= Memory;
				if (dd->is_reversed)
					dd->operand2_source_type = Memory;
				else
					dd->operand1_source_type = Memory;


				switch (rm)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[eax]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[ecx]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[edx]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[ebx]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 4:
						// SIB byte follows
						extract_sib_32bit_address_mode(data + 1, dd, _null_string, &prefix_buffer[0], op_buffer, op1, op2, mod, prefix_op1);
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u32*)(data + 1));
						*op1 = op_buffer;
						dd->opcode_bytes += 4;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[esi]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[edi]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
				}
				break;

			case 1:
				dd->opcode_bytes			+= 2;
				dd->destination_source_type	= Memory;
				if (dd->is_reversed)
					dd->operand2_source_type = Memory;
				else
					dd->operand1_source_type = Memory;


				switch (rm)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[eax+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[ecx+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[edx+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[ebx+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 4:
						sprintf((s8*)&sib2_buffer[0], "+%u", (int)*(u8*)(data + 2));
						extract_sib_32bit_address_mode(data + 1, dd, &sib2_buffer[0], &prefix_buffer[0], op_buffer, op1, op2, mod, prefix_op1);
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[ebp+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[esi+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[edi+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(data + 1));
						*op1 = op_buffer;
						break;
				}
				break;

			case 2:
				dd->opcode_bytes			+= 5;
				dd->destination_source_type	= Memory;
				if (dd->is_reversed)
					dd->operand2_source_type = Memory;
				else
					dd->operand1_source_type = Memory;


				switch (rm)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[eax+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u32*)(data + 1));
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[ecx+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u32*)(data + 1));
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[edx+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u32*)(data + 1));
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[ecx+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u32*)(data + 1));
						*op1 = op_buffer;
						break;
					case 4:
						sprintf((s8*)&sib2_buffer[0], "+%u", (int)*(u32*)(data + 2));
						extract_sib_32bit_address_mode(data + 1, dd, &sib2_buffer[0], &prefix_buffer[0], op_buffer, op1, op2, mod, prefix_op1);
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[ebp+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u32*)(data + 1));
						*op1 = op_buffer;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[esi+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u32*)(data + 1));
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[edi+%u]", (s8*)prefix_op1, (s8*)&prefix_buffer[0], (int)*(u32*)(data + 1));
						*op1 = op_buffer;
						break;
				}
				break;

			case 3:
				dd->opcode_bytes += 1;
				dd->destination_source_type	= Register;
				if (dd->is_reversed)
					dd->operand2_source_type = Register;
				else
					dd->operand1_source_type = Register;


				switch (dd->force_reg ? dd->force_reg : 
						rt != _varies ? rt :
						dd->is_reversed ? dd->operand2_regtype : dd->operand1_regtype)
				{
					case _8bit:
						extract_8bit_reg_operand(rm, op1, prefix_op1);
						break;
					case _16bit:
						extract_16bit_reg_operand(rm, op1, prefix_op1);
						break;
					case _32bit:
						extract_32bit_reg_operand(rm, op1, prefix_op1);
						break;
					case _64bit:
						extract_64bit_reg_operand(rm, op1, prefix_op1);
						break;
					case _mmx:
						extract_mmx_reg_operand(rm, op1, prefix_op1);
						break;
					case _xmmx:
						extract_xmmx_reg_operand(rm, op1, prefix_op1);
						break;
				}
				break;

		}
		
		if (do_reg)
		{
			// Store operand2
			if (dd->is_reversed)
				dd->operand1_source_type = Register;
			else
				dd->operand2_source_type = Register;


			switch (dd->force_reg ? dd->force_reg : 
					rt != _varies ? rt :
					dd->is_reversed ? dd->operand1_regtype : dd->operand2_regtype)
			{
				case _8bit:
					extract_8bit_reg_operand(r, op2, _null_string);
					dd->operand_size = Byte;
					break;
				case _16bit:
					extract_16bit_reg_operand(r, op2, _null_string);
					dd->operand_size = Word;
					break;
				case _32bit:
					extract_32bit_reg_operand(r, op2, _null_string);
					dd->operand_size = Dword;
					break;
				case _64bit:
					extract_64bit_reg_operand(r, op2, _null_string);
					dd->operand_size = Qword;
					break;
				case _mmx:
					extract_mmx_reg_operand(r, op2, _null_string);
					dd->operand_size = Qword;
					break;
				case _xmmx:
					extract_xmmx_reg_operand(r, op2, _null_string);
					dd->operand_size = DQword;
					break;
			}
		}
	}
	
	u8* do_common_return_operand_size_text(SDisasmData* dd)
	{
		switch (dd->operand_size)
		{
			case _8bit:				return(cgc_byte_ptr);
			case _16bit:			return(cgc_word_ptr);
			case _32bit:			return(cgc_dword_ptr);
			case _64bit:			return(cgc_qword_ptr);
			case _80bit:			return(cgc_tbyte_ptr);
			case _128bit:			return(cgc_dqword_ptr);
			case _6byte:			return(cgc_6byte_ptr);
			case _10byte:			return(cgc_10byte_ptr);
			case _illegal:			return(cgc_illegal_ptr);
			case _0bit:				return(_null_string);
			case _f32:				return(cgc_f32_ptr);
			case _f64:				return(cgc_f64_ptr);
			case _f80:				return(cgc_f80_ptr);
			case _s32:				return(cgc_s32_ptr);
			case _s64:				return(cgc_s64_ptr);
			case _mmx:				return(cgc_mmx_ptr);
			case _xmmx:				return(cgc_xmmx_ptr);
			case _fpu:				return(cgc_fpu_ptr);
			case _m94byte:			return(cgc_94byte_ptr);
			case _m108byte:			return(cgc_108byte_ptr);
			case _m14byte:			return(cgc_14byte_ptr);
			case _m28byte:			return(cgc_28byte_ptr);
			default:
				return(cgc_unk_ptr);		// Should never be used
		}
	}
	
	void do_common_set_operand_size(SDisasmData* dd)
	{
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
		{
			// 32-bit operand mode
			dd->operand_size = _32bit;
		}
		else
		{
			// 16-bit operand mode
			dd->operand_size = _16bit;
		}
	}

	void extract_sib_32bit_address_mode(u8* data, SDisasmData* dd, u8* disp, u8* prefix_buffer, u8* op_buffer, u8** op1, u8** op2, u8 mod, u8* prefix_op1)
	{
		u32 needs_plus;					// Does the base reg need a plus sign before the scale? True if not (mod=0, b=5)
		u8 s = (*data & 0xc0) >> 6;		// Upper 2 bits
		u8 i  = (*data & 0x38) >> 3;	// Next 3 lower
		u8 b   = (*data & 0x07);		// Bottom 3



		// Set the base register
		needs_plus = 1;
		switch (b)
		{
			case 0:
				sprintf((s8*)&sib_buffer[0], "%s", cgc_eax_reg);
				break;
			case 1:
				sprintf((s8*)&sib_buffer[0], "%s", cgc_ecx_reg);
				break;
			case 2:
				sprintf((s8*)&sib_buffer[0], "%s", cgc_edx_reg);
				break;
			case 3:
				sprintf((s8*)&sib_buffer[0], "%s", cgc_ebx_reg);
				break;
			case 4:
				sprintf((s8*)&sib_buffer[0], "%s", cgc_esp_reg);
				break;
			case 5:
				if (mod == 0)
				{
					// None is used
					sprintf((s8*)&sib_buffer[0], "%s", (s8*)_null_string);
					needs_plus = 0;
				}
				else
				{
					// ebp
					sprintf((s8*)&sib_buffer[0], "%s", cgc_ebp_reg);
				}
				break;
			case 6:
				sprintf((s8*)&sib_buffer[0], "%s", cgc_esi_reg);
				break;
			case 7:
				sprintf((s8*)&sib_buffer[0], "%s", cgc_edi_reg);
				break;
		}
		
		switch (s)
		{
			case 0:
				dd->opcode_bytes += 1;
				switch (i)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[%s%seax%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[%s%secx%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[%s%sedx%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[%s%sebx%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 4:
						sprintf((s8*)op_buffer, "%s%s[%s%s%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[%s%sebp%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[%s%sesi%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[%s%sedi%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
				}
				break;

			case 1:
				dd->opcode_bytes += 1;
				switch (i)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[%s%seax*2%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[%s%secx*2%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[%s%sedx*2%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[%s%sebx*2%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 4:
						// None
						sprintf((s8*)op_buffer, "%s%s[%s%s%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[%s%sebp*2%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[%s%sesi*2%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[%s%sedi*2%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
				}
				break;

			case 2:
				dd->opcode_bytes += 1;
				switch (i)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[%s%seax*4%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[%s%secx*4%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[%s%sedx*4%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[%s%sebx*4%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 4:
						// None
						sprintf((s8*)op_buffer, "%s%s[%s%s%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[%s%sebp*4%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[%s%sesi*4%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[%s%sedi*4%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
				}
				break;

			case 3:
				dd->opcode_bytes += 1;
				switch (i)
				{
					case 0:
						sprintf((s8*)op_buffer, "%s%s[%s%seax*8%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 1:
						sprintf((s8*)op_buffer, "%s%s[%s%secx*8%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 2:
						sprintf((s8*)op_buffer, "%s%s[%s%sedx*8%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 3:
						sprintf((s8*)op_buffer, "%s%s[%s%sebx*8%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 4:
						// None
						sprintf((s8*)op_buffer, "%s%s[%s%s%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 5:
						sprintf((s8*)op_buffer, "%s%s[%s%sebp*8%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 6:
						sprintf((s8*)op_buffer, "%s%s[%s%sesi*8%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
					case 7:
						sprintf((s8*)op_buffer, "%s%s[%s%sedi*8%s]", (s8*)prefix_op1, (s8*)prefix_buffer, &sib_buffer[0], needs_plus ? cgc_plus_string : _null_string, (s8*)disp);
						*op1 = op_buffer;
						break;
				}
				break;

		}
	}
	
	void do_common_adjust_register_size(u8* op, u32/*REGTYPE*/ rt)
	{
		switch (rt)
		{
			case _8bit:
				if (op == cgc_ax_reg || op == cgc_eax_reg)					op = cgc_al_reg;
				else if (op == cgc_bx_reg || op == cgc_ebx_reg)				op = cgc_bl_reg;
				else if (op == cgc_cx_reg || op == cgc_ecx_reg)				op = cgc_cl_reg;
				else if (op == cgc_dx_reg || op == cgc_edx_reg)				op = cgc_dl_reg;
				break;

			case _16bit:
				if (op == cgc_al_reg || op == cgc_eax_reg)					op = cgc_ax_reg;
				else if (op == cgc_bl_reg || op == cgc_ebx_reg)				op = cgc_bx_reg;
				else if (op == cgc_cl_reg || op == cgc_ecx_reg)				op = cgc_cx_reg;
				else if (op == cgc_dl_reg || op == cgc_edx_reg)				op = cgc_dx_reg;
				else if (op == cgc_esi_reg)								op = cgc_si_reg;
				else if (op == cgc_edi_reg)								op = cgc_di_reg;
				else if (op == cgc_ebp_reg)								op = cgc_bp_reg;
				else if (op == cgc_esp_reg)								op = cgc_sp_reg;
				break;

			case _32bit:
				if (op == cgc_al_reg || op == cgc_ax_reg)						op = cgc_eax_reg;
				else if (op == cgc_bl_reg || op == cgc_bx_reg)				op = cgc_ebx_reg;
				else if (op == cgc_cl_reg || op == cgc_cx_reg)				op = cgc_ecx_reg;
				else if (op == cgc_dl_reg || op == cgc_dx_reg)				op = cgc_edx_reg;
				else if (op == cgc_esi_reg)								op = cgc_esi_reg;
				else if (op == cgc_edi_reg)								op = cgc_edi_reg;
				else if (op == cgc_ebp_reg)								op = cgc_ebp_reg;
				else if (op == cgc_esp_reg)								op = cgc_esp_reg;
				break;
		}
	}

	void do_common_regrm(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, bool do_reg, u8* prefix_op1)
	{
		u32 lTest;
		
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Address) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Address) != 0))
		{
			// 32-bit addressing mode
			if (rt == _8bit)
				extract_modrm_32bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, _8bit, do_reg, prefix_op1);
			else
			{
				if ((dd->overrides & (u32)Operand) == 0 && rt != (u32)_16bit)
				{
					// No operand override
					// The next two lines (and repeats of the same) are coded this way due to an apparent bug in g++
					// The syntax:  if (rt == (_16bit | _32bit)) does not work.
					// The syntax:  if (rt & (_16bit | _32bit) == rt) does not work
					// etc.
					lTest = ((rt == (_16bit | _32bit)) ? 1 : 0);
					if (lTest)
						extract_modrm_32bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, _cpu_mode == _16bit_mode ? _16bit : _32bit, do_reg, prefix_op1);
					else
						extract_modrm_32bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, (ERegType)rt, do_reg, prefix_op1);
				}
				else
				{
					// Operand override
					lTest = ((rt == (_16bit | _32bit)) ? 1 : 0);
					if (lTest)
						extract_modrm_32bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, _cpu_mode == _16bit_mode ? _32bit : _16bit, do_reg, prefix_op1);
					else
						extract_modrm_32bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, (ERegType)rt, do_reg, prefix_op1);
				}
			}
		}
		else
		{
			// 16-bit addressing mode
			if (rt == _8bit)
				extract_modrm_16bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, _8bit, do_reg, prefix_op1);
			else
			{
				if ((dd->overrides & (u32)Operand) == 0 && rt != (u32)_32bit)
				{
					// No operand override
					lTest = ((rt == (_16bit | _32bit)) ? 1 : 0);
					if (lTest)
						extract_modrm_16bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, _cpu_mode == _16bit_mode ? _16bit : _32bit, do_reg, prefix_op1);
					else
						extract_modrm_16bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, (ERegType)rt, do_reg, prefix_op1);
				}
				else
				{
					// Operand override
					lTest = ((rt == (_16bit | _32bit)) ? 1 : 0);
					if (lTest)
						extract_modrm_16bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, _cpu_mode == _16bit_mode ? _32bit : _16bit, do_reg, prefix_op1);
					else
						extract_modrm_16bit_address_mode(data, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2, (ERegType)rt, do_reg, prefix_op1);
				}
			}
		}
	}

	void do_common_regrm_reversed(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, bool do_reg, u8* prefix_op1)
	{
		u32 lTest;
		
		dd->is_reversed = 1;
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Address) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Address) != 0))
		{
			// 32-bit addressing mode
			if (rt == _8bit)
				extract_modrm_32bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, _8bit, do_reg, prefix_op1);
			else
			{
				if ((dd->overrides & (u32)Operand) == 0 && rt != (u32)_16bit)
				{
					// No operand override
					lTest = ((rt == (_16bit | _32bit)) ? 1 : 0);
					if (lTest)
						extract_modrm_32bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, _cpu_mode == _16bit_mode ? _16bit : _32bit, do_reg, prefix_op1);
					else
						extract_modrm_32bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, (ERegType)rt, do_reg, prefix_op1);
				}
				else
				{
					// Operand override
					lTest = ((rt == (_16bit | _32bit)) ? 1 : 0);
					if (lTest)
						extract_modrm_32bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, _cpu_mode == _16bit_mode ? _32bit : _16bit, do_reg, prefix_op1);
					else
						extract_modrm_32bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, (ERegType)rt, do_reg, prefix_op1);
				}
			}
		}
		else
		{
			// 16-bit addressing mode
			if (rt == _8bit)
				extract_modrm_16bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, _8bit, do_reg, prefix_op1);
			else
			{
				if ((dd->overrides & (u32)Operand) == 0 && rt != (u32)_32bit)
				{
					// No operand override
					lTest = ((rt == (_16bit | _32bit)) ? 1 : 0);
					if (lTest)
						extract_modrm_16bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, _cpu_mode == _16bit_mode ? _16bit : _32bit, do_reg, prefix_op1);
					else
						extract_modrm_16bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, (ERegType)rt, do_reg, prefix_op1);
				}
				else
				{
					// Operand override
					lTest = ((rt == (_16bit | _32bit)) ? 1 : 0);
					if (lTest)
						extract_modrm_16bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, _cpu_mode == _16bit_mode ? _32bit : _16bit, do_reg, prefix_op1);
					else
						extract_modrm_16bit_address_mode(data, dd, &operand2_buffer[0], &dd->operand2, &dd->operand1, (ERegType)rt, do_reg, prefix_op1);
				}
			}
		}
	}

	void do_common_rm(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, u8* prefix_op1)
	{
		do_common_regrm(data, dd, rt, false, prefix_op1);
	}

	void do_common_r(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, u8* prefix_op1)
	{
		dd->regrm_reversed = 1;
		do_common_regrm(data, dd, rt, false, prefix_op1);
	}
	
	void do_common_opcode_mov(u8* data, SDisasmData* dd, u32 op1_reg, u32 op2_reg, u32 opcode_length)
	{
		dd->mnemonic			= cgc_mov_instruction;
		dd->operand1_regtype	= op1_reg;
		dd->operand2_regtype	= op1_reg;
		dd->opcode_bytes		+= opcode_length;
		do_common_regrm(dd->data_root + dd->opcode_bytes, dd, _varies, false, _null_string);
	}
	
	void do_common_opcode_rm8_one_operand(u8* data, SDisasmData* dd, u8* mnemonic, u32 hard_operand_size, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m8", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;

		do_common_rm(dd->data_root + opcode_length, dd, _8bit, _null_string);
		if (dd->operand1_source_type == Memory)
		{
			if (hard_operand_size != 0)
				dd->operand_size = hard_operand_size;
			else
				do_common_set_operand_size(dd);
			
			do_common_prefix_operand1(dd, do_common_return_operand_size_text(dd));
		}
	}
	
	void do_common_opcode_rm16_one_operand(u8* data, SDisasmData* dd, u8* mnemonic, u32 hard_operand_size, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;

		do_common_rm(dd->data_root + opcode_length, dd, _16bit, _null_string);
		if (dd->operand1_source_type == Memory)
		{
			if (hard_operand_size != 0)
				dd->operand_size = hard_operand_size;
			else
				do_common_set_operand_size(dd);
			
			do_common_prefix_operand1(dd, do_common_return_operand_size_text(dd));
		}
	}
	
	void do_common_opcode_rm32_one_operand(u8* data, SDisasmData* dd, u8* mnemonic, u32 hard_operand_size, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m32", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;

		do_common_rm(dd->data_root + opcode_length, dd, _32bit, _null_string);
		if (dd->operand1_source_type == Memory)
		{
			if (hard_operand_size != 0)
				dd->operand_size = hard_operand_size;
			else
				do_common_set_operand_size(dd);
			
			do_common_prefix_operand1(dd, do_common_return_operand_size_text(dd));
		}
	}
	
	void do_common_opcode_fpu_rm_one_operand(u8* data, SDisasmData* dd, u8* mnemonic, u32 operand_size, u32 opcode_length)
	{
		u8* p;
		
		dd->operand_size	= operand_size;
		p					= do_common_return_operand_size_text(dd);
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s %s", mnemonic, (s8*)p);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		
		do_common_rm(dd->data_root + opcode_length, dd, _fpu, p);
	}
	
	void do_common_opcode_fpu_hard_stx(u8* data, SDisasmData* dd, u8* mnemonic, u32 reg, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		extract_stx_reg_operand((u8)reg, &dd->operand1, _null_string);
		extract_stx_reg_operand(*(data + 1) & 0x07, &dd->operand2, _null_string);
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_fpu_stx_hard(u8* data, SDisasmData* dd, u8* mnemonic, u32 reg, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		extract_stx_reg_operand(*(data + 1) & 0x07, &dd->operand1, _null_string);
		extract_stx_reg_operand((u8)reg, &dd->operand2, _null_string);
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_fpu_stx(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		extract_stx_reg_operand(*(data + 1) & 0x07, &dd->operand1, _null_string);
		dd->opcode_bytes	+= opcode_length;
	}

	void do_common_opcode_r16_m16_16_one_operand(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r16,m16_16", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;

		do_common_rm(dd->data_root + opcode_length, dd, _16bit | _32bit, _null_string);
		do_common_prefix_operand1(dd, cgc_m16_16_ptr);
	}
	
	void do_common_opcode_r32_m16_32_one_operand(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r32,m16_32", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;

		do_common_rm(dd->data_root + opcode_length, dd, _16bit | _32bit, _null_string);
		do_common_prefix_operand1(dd, cgc_m16_32_ptr);
	}
	
	void do_common_opcode_rm16_rm32_one_operand(u8* data, SDisasmData* dd, u8* mnemonic, u32 hard_operand_size, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16; %s r32/m32", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		
		do_common_rm(dd->data_root + opcode_length, dd, _16bit | _32bit, _null_string);
		if (dd->operand1_source_type == Memory)
		{
			if (hard_operand_size != 0)
				dd->operand_size = hard_operand_size;
			else
				do_common_set_operand_size(dd);
			
			do_common_prefix_operand1(dd, do_common_return_operand_size_text(dd));
		}
	}

	void do_common_opcode_m_one_operand(u8* data, SDisasmData* dd, u8* mnemonic, u32 hard_operand_size, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s m", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		
		do_common_rm(dd->data_root + opcode_length, dd, _16bit | _32bit, _null_string);
		
		if (hard_operand_size != 0)
			dd->operand_size = hard_operand_size;
		else
			do_common_set_operand_size(dd);
		
		if (dd->operand1_source_type != Memory)
		{
			sprintf((s8*)&misc_buffer[0], "%s%s", (s8*)cgc_illegal_ptr, (s8*)do_common_return_operand_size_text(dd));
			do_common_prefix_operand1(dd, &misc_buffer[0]);
		}
		else
			do_common_prefix_operand1(dd, do_common_return_operand_size_text(dd));
	}

	void do_immediate(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, u8* prefix_op)
	{
		if (rt == _8bit)
		{
			// 8-bit immediate
			sprintf((s8*)&immediate_buffer[0], "%s%u", prefix_op, (int)*data);
			dd->immediate_value	= (u32)*data;
			dd->opcode_bytes	+= 1;
			dd->operand_size	= Byte;
		}
		else
		{
			// 16-bit or 32-bit immediate
			if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
				(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
			{
				// 32-bit addressing mode
				sprintf((s8*)&immediate_buffer[0], "%s%u", prefix_op, (int)*(u32*)data);
				dd->immediate_value	= (u32)*(u32*)data;
				dd->opcode_bytes	+= 4;
				dd->operand_size	= Dword;
			}
			else
			{
				// 16-bit addressing mode
				sprintf((s8*)&immediate_buffer[0], "%s%u", prefix_op, (int)*(u16*)data);
				dd->immediate_value	= (u32)*(u16*)data;
				dd->opcode_bytes	+= 2;
				dd->operand_size	= Word;
			}
		}
		// Store the buffer operand
		dd->immediate = &immediate_buffer[0];
	}

	void do_signed_immediate(u8* data, SDisasmData* dd, u32/*REGTYPE*/ rt, u8* prefix_op)
	{
		int i;
		
		
		if (rt == _8bit)
		{
			// 8-bit immediate
			i = (int)*data;
			sprintf((s8*)&immediate_buffer[0], "%s%s%i", prefix_op, i < 0 ? _null_string : cgc_plus_string, i);
			dd->immediate_value	= (u32)*data;
			dd->opcode_bytes	+= 1;
			dd->operand_size	= Byte;
		}
		else
		{
			// 16-bit or 32-bit immediate
			if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
				(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
			{
				// 32-bit addressing mode
				i = (int)*(u32*)data;
				sprintf((s8*)&immediate_buffer[0], "%s%s%i", prefix_op, i < 0 ? _null_string : cgc_plus_string, i);
				dd->immediate_value	= (u32)*(u32*)data;
				dd->opcode_bytes	+= 4;
				dd->operand_size	= Dword;
			}
			else
			{
				// 16-bit addressing mode
				i = (int)*(u16*)data;
				sprintf((s8*)&immediate_buffer[0], "%s%s%i", prefix_op, i < 0 ? _null_string : cgc_plus_string, i);
				dd->immediate_value	= (u32)*(u16*)data;
				dd->opcode_bytes	+= 2;
				dd->operand_size	= Word;
			}
		}
		// Store the buffer operand
		dd->immediate = &immediate_buffer[0];
	}
	
	int sign_extend_8bit_to_32bits(u8 value)
	{
		// Extract 7th bit, extend it through to the top 24 bits
		return((int)value + ((((int)value & 0x80) >> 7) * 0xffffff00));
	}
	
	int sign_extend_16bits_to_32bits(u16 value)
	{
		// Extract 15th bit, extend it through to the top 16 bits
		return((int)value + ((((int)value & 0x8000) >> 15) * 0xffff0000));
	}
	
	void do_common_swap_operand1_operand2(SDisasmData* dd)
	{
		u32 tst;
		u8* t;

		t				= dd->operand1;
		dd->operand1	= dd->operand2;
		dd->operand2	= t;
		
		tst							= dd->operand1_source_type;
		dd->operand1_source_type	= dd->operand2_source_type;
		dd->operand2_source_type	= tst;
	}
	
	void do_common_prefix_operand1(SDisasmData* dd, u8* prefix)
	{
		sprintf((s8*)&prefix_op1_buffer[0], "%s%s", prefix, dd->operand1);
		dd->operand1 = &prefix_op1_buffer[0];
	}
	
	void do_common_prefix_operand2(SDisasmData* dd, u8* prefix)
	{
		sprintf((s8*)&prefix_op2_buffer[0], "%s%s", prefix, dd->operand2);
		dd->operand2 = &prefix_op2_buffer[0];
	}

	void do_immediate_sign_extend_8bits_to_16_32bit(u8* data, SDisasmData* dd)
	{
		// 16-bit or 32-bit immediate
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
		{
			// 32-bit addressing mode
			sprintf((s8*)&immediate_buffer[0], "%u", (int)sign_extend_8bit_to_32bits(*data));
			dd->immediate_value	= (u32)*(u32*)data;
			dd->opcode_bytes	+= 4;
			dd->operand_size	= Dword;
		}
		else
		{
			// 16-bit addressing mode
			sprintf((s8*)&immediate_buffer[0], "%u", (int)(sign_extend_8bit_to_32bits(*data) & 0xffff));
			dd->immediate_value	= (u32)*(u16*)data;
			dd->opcode_bytes	+= 2;
			dd->operand_size	= Word;
		}
		// Store the buffer operand
		dd->immediate = &immediate_buffer[0];
	}

	void do_common_opcode_rm8(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m8,r8", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}

	void do_common_opcode_r1632_rm8(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r16/32,r8", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_rm8_reversed(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->is_reversed		= 1;
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r8,r/m8", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_rm16_rm32(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16,r16; %s r32/m32,r32", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_rm16_r16(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16,r16", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_rm32_r32(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m32,r32", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_r16_rm16(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r16,r/m16", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_r32_rm32(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r32,r/m32", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_r1632_rm1632(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
			do_common_opcode_r32_rm32(dd, mnemonic, opcode_length);
		else
			do_common_opcode_r16_rm16(dd, mnemonic, opcode_length);
	}

	void do_common_opcode_rm1632_m16_1632(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
		{
			do_common_opcode_r32_m16_32_one_operand(data, dd, mnemonic, opcode_length);
		}
		else
		{
			do_common_opcode_r16_m16_16_one_operand(data, dd, mnemonic, opcode_length);
		}
	}

	void do_common_opcode_rm16_r16_cl(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16,r16,cl", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_rm32_r32_cl(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m32,r32,cl", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_rm1632_r1632_cl(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
			do_common_opcode_rm32_r32_cl(dd, mnemonic, opcode_length);
		else
			do_common_opcode_rm16_r16_cl(dd, mnemonic, opcode_length);
	}
	
	void do_common_opcode_rm16_rm32_reversed(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->is_reversed		= 1;
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r16,r/m16; %s r32,r32/m32", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_r_rm_mmx(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->is_reversed		= 1;
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s mm,mm/m64", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_r_rm_xmmx(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->is_reversed		= 1;
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s xmm,xmm/m128", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_rm_r_mmx(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->is_reversed		= 1;
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s mm/m64,mm", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_rm_r_xmmx(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->is_reversed		= 1;
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s xmm/m128,xmm", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_mmx_immed8(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->is_reversed		= 1;
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s mm/m64,immed8", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_xmmx_immed8(SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->is_reversed		= 1;
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s xmm/m128,immed8", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_rm8_immed8(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m8,immed8", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		do_common_rm(dd->data_root + dd->opcode_bytes, dd, _8bit, _null_string);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit, _null_string);
	}
	
	void do_common_rm8_1(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m8,1", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		do_common_rm(dd->data_root + dd->opcode_bytes, dd, _8bit, _null_string);
		dd->immediate		= cgc_1_string;
	}
	
	void do_common_rm8_cl(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m8,cl", mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		do_common_rm(dd->data_root + dd->opcode_bytes, dd, _8bit, _null_string);
		dd->immediate		= cgc_cl_reg;
	}
	
	void do_common_rm16_32_immed8(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16,immed8; %s r32/m32,immed8", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		do_common_rm(dd->data_root + dd->opcode_bytes, dd, _16bit | _32bit, _null_string);
		do_immediate_sign_extend_8bits_to_16_32bit(dd->data_root + dd->opcode_bytes, dd);
	}
	
	void do_common_rm16_32_1(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16,1; %s r32/m32,1", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		do_common_rm(dd->data_root + dd->opcode_bytes, dd, _16bit | _32bit, _null_string);
		dd->immediate		= cgc_1_string;
	}
	
	void do_common_rm16_32_cl(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16,cl; %s r32/m32,cl", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		do_common_rm(dd->data_root + dd->opcode_bytes, dd, _16bit | _32bit, _null_string);
		dd->immediate		= cgc_cl_reg;
	}
	
	void do_common_rm16_32_immed16_32(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s r/m16,immed16; %s r32/m32,immed32", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		do_common_rm(dd->data_root + dd->opcode_bytes, dd, _16bit | _32bit, _null_string);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _16bit | _32bit, _null_string);
	}
	
	void do_common_accum8_immed8(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s al,immed8", mnemonic);
		dd->comment			= &comment_buffer[0];
		extract_8bit_reg_operand((u8)_accum_low_reg, &dd->operand1, _null_string);
		dd->opcode_bytes	+= opcode_length;
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit, _null_string);
	}

	void do_common_accum16_32_immed8(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s ax,immed16; %s eax,immed32", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
		{
			// 32-bit addressing mode
			extract_32bit_reg_operand((u8)_accum_reg, &dd->operand1, _null_string);
		}
		else
			extract_16bit_reg_operand((u8)_accum_reg, &dd->operand1, _null_string);
			
		dd->opcode_bytes += opcode_length;
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _16bit | _32bit, _null_string);
	}
	
	void do_common_accum16_32_immed16_32(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length)
	{
		dd->mnemonic		= mnemonic;
		sprintf((s8*)&comment_buffer[0], "%s ax,immed8; %s eax,immed8", mnemonic, mnemonic);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= opcode_length;
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
		{
			// 32-bit addressing mode
			extract_32bit_reg_operand((u8)_accum_reg, &dd->operand1, _null_string);
			do_immediate(dd->data_root + dd->opcode_bytes, dd, _32bit, _null_string);
		}
		else
		{
			extract_16bit_reg_operand((u8)_accum_reg, &dd->operand1, _null_string);
			do_immediate(dd->data_root + dd->opcode_bytes, dd, _16bit, _null_string);
		}
	}

	void do_common_mnemonic(SDisasmData* dd, u8* mnemonic, u32 opcode_length, u8* comment, u8* line_comment)
	{
		dd->mnemonic		= mnemonic;
		dd->opcode_bytes	+= opcode_length;
		if (comment)
			dd->comment		= comment;
		if (line_comment)
			dd->line_comment= comment;
	}
	
	void do_common_unknown(u8* data, SDisasmData* dd, u8* mnemonic, u32 opcode_length, u8* comment, u8* line_comment)
	{
		u32 i;
		u8 opcode_sequence[256];
		u8 buff[256];
		u8 line_buff[256];
		
		// Store the opcode bytes
		for (i=0; i < opcode_length; i++)
			sprintf((s8*)&opcode_sequence[i*3],"%02x ", (int)(dd->data_root + dd->opcode_bytes + i));

		// Create the comments
		sprintf((s8*)&line_buff[256], "; (%s)", (s8*)&opcode_sequence[0]);
		sprintf((s8*)&buff[256], "; UNK - Unknown instruction (%s)", (s8*)&opcode_sequence[0]);
		// Store the instruction
		do_common_mnemonic(dd, mnemonic, opcode_length,
							dd->comment  ? comment      : buff,
							line_comment ? line_comment : line_buff);
	}


	void do_common_operand_size_check_mnemonic(SDisasmData* dd, u32 opcode_length, u8* _16bit_mnemonic, u8* _32bit_mnemonic)
	{
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
			do_common_mnemonic(dd, _32bit_mnemonic, 1, NULL, NULL);
		else
			do_common_mnemonic(dd, _16bit_mnemonic, 1, NULL, NULL);
	}
	
	void do_common_two_prefixes_mnemonic_operand_size_check(SDisasmData* dd, u32 opcode_length, 
															u32 prefix1, u8* mnemonic1,
															u32 prefix2, u8* mnemonic2,
															u8* _16bit_operand,
															u8* _32bit_operand)
	{
		if (dd->prefixes & prefix1)
		{
			dd->mnemonic	= mnemonic1;
			if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
				(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
				dd->operand1		= _32bit_operand;
			else
				dd->operand1		= _16bit_operand;
		}
		else if (dd->prefixes & prefix2)
		{
			dd->mnemonic	= mnemonic2;
			if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
				(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
				dd->operand1		= _32bit_operand;
			else
				dd->operand1		= _16bit_operand;
		}
		else
		{
			if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
				(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
				dd->mnemonic		= _32bit_operand;
			else
				dd->mnemonic		= _16bit_operand;
		}
		dd->opcode_bytes	+= opcode_length;
	}
	
	void do_common_opcode_mmx_xmmx_immed8(u8* data, SDisasmData* dd, u8* instruction, u8* comment)
	{
		do_common_opcode_xmmx_immed8(dd, instruction, 0);
		do_common_rm(data, dd, dd->overrides & (u32)Operand ? _xmmx : _mmx, _null_string);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit, _null_string);
		sprintf((s8*)&comment_buffer[0], "%s", (s8*)comment);
	}
	
	void do_common_opcode_mmx_xmmx(u8* data, SDisasmData* dd, u8* instruction, u8* comment)
	{
		do_common_opcode_r_rm_xmmx(dd, instruction, 0);
		do_common_regrm_reversed(data, dd, dd->overrides & (u32)Operand ? _xmmx : _mmx, false, _null_string);
		sprintf((s8*)&comment_buffer[0], "%s", (s8*)comment);
		dd->comment = &comment_buffer[0];
	}









//////////
//
// Decode instructions
//
//////////
	void opcode_aaa(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_aaa_instruction, 1, NULL, NULL);
	}

	void opcode_aad(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_aad_instruction, 2, NULL, NULL);
	}

	void opcode_aam(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_aam_instruction, 2, NULL, NULL);
	}

	void opcode_aas(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_aas_instruction, 1, NULL, NULL);
	}

	void opcode_adc10(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8(dd, cgc_adc_instruction, 1);
		do_common_regrm(data + 1, dd, _8bit, false, _null_string);
	}

	void opcode_adc11(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, cgc_adc_instruction, 1);
		do_common_regrm(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_adc12(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8_reversed(dd, cgc_adc_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _8bit, false, _null_string);
	}

	void opcode_adc13(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, cgc_add_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_adc_rm8_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm8_immed8(data, dd, cgc_adc_instruction, 1);
	}

	void opcode_adc_rm16_32_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed16_32(data, dd, cgc_adc_instruction, 1);
	}

	void opcode_add00(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8(dd, cgc_add_instruction, 1);
		do_common_regrm(data + 1, dd, _8bit, false, _null_string);
	}

	void opcode_add01(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, cgc_add_instruction, 1);
		do_common_regrm(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_add02(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8_reversed(dd, cgc_add_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _8bit, false, _null_string);
	}

	void opcode_add03(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32_reversed(dd, cgc_add_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_add_rm8_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm8_immed8(data, dd, cgc_add_instruction, 1);
	}

	void opcode_add_rm16_32_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed16_32(data, dd, cgc_add_instruction, 1);
	}

	void opcode_adr_size_override(u8* data, SDisasmData* dd)
	{
		dd->opcode_bytes += 1;
		dd->overrides |= Address;
	}

	void opcode_and20(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8(dd, cgc_and_instruction, 1);
		do_common_regrm(data + 1, dd, _8bit, false, _null_string);
	}

	void opcode_and21(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, cgc_and_instruction, 1);
		do_common_regrm(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_and22(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8_reversed(dd, cgc_and_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _8bit, false, _null_string);
	}

	void opcode_and23(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, cgc_and_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_and_rm8_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm8_immed8(data, dd, cgc_and_instruction, 1);
	}

	void opcode_and_rm16_32_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed16_32(data, dd, cgc_and_instruction, 1);
	}

	void opcode_arpl(u8* data, SDisasmData* dd)
	{
		dd->force_reg = _16bit;
		do_common_opcode_rm16_r16(dd, cgc_arpl_instruction, 1);
		do_common_regrm(data + 1, dd, _16bit, false, _null_string);
	}

	void opcode_bound(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm1632(dd, cgc_bound_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_bsf(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm1632(dd, cgc_bsf_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_bsr(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm1632(dd, cgc_bsr_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit, false, _null_string);
	}
	
	void opcode_bswap_xxx(u8* data, SDisasmData* dd)
	{
		dd->mnemonic		= cgc_bswap_instruction;
		extract_32bit_reg_operand(*data & 0x07, &dd->operand1, _null_string);
		sprintf((s8*)&comment_buffer[0], "bswap %s; byte swap, swaps endian", dd->operand1);
		dd->comment			= &comment_buffer[0];
		dd->opcode_bytes	+= 1;
	}
	
	void opcode_bt(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm1632(dd, cgc_bt_instruction, 1);
		do_common_regrm(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_btc(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm1632(dd, cgc_btc_instruction, 1);
		do_common_regrm(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_btr(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm1632(dd, cgc_btr_instruction, 1);
		do_common_regrm(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_bts(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm1632(dd, cgc_bts_instruction, 1);
		do_common_regrm(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_jmp_call_far_operand(u8* data, SDisasmData* dd, u8* instruction)
	{
		int v1, v2;		// Values pulled from opcode encoding
		
		
		do_common_mnemonic(dd, instruction, 1, NULL, NULL);
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
		{
			// 32-bit addressing mode
			v1 = (int)(*(u16*)(data + 5));
			v2 = (int)(*(u32*)(data + 1));
			sprintf((s8*)&operand1_buffer[0], "%04xh:%08xh", v1, v2);
			dd->opcode_bytes += 6;
		}
		else
		{
			// 16-bit addressing mode
			v1 = (int)(*(u16*)(data + 3));
			v2 = (int)(*(u16*)(data + 1));
			sprintf((s8*)&operand1_buffer[0], "%04xh:%04xh", v1, v2);
			dd->opcode_bytes += 4;
		}
		dd->operand1 = &operand1_buffer[0];
		
		// Store additional information in the line comment
		sprintf((s8*)&line_comment_buffer[0], "; %u:%u (base-10)", v1, v2);
		dd->line_comment = &line_comment_buffer[0];
	}

	void opcode_jmp_call_near_relative(u8* data, SDisasmData* dd, u8* instruction)
	{
		do_common_mnemonic(dd, instruction, 1, NULL, NULL);
		do_signed_immediate(data + 1, dd, _16bit | _32bit, _null_string);
	}

	void opcode_cbw(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cbw_instruction, 1, NULL, NULL);
	}

	void opcode_check_reg_0f00(u8* data, SDisasmData* dd)
	{
		u8 r = (*data & 0x38) >> 3;
		
		if (r == 0)
		{
			// SLDT
			do_common_opcode_rm16_rm32(dd, cgc_sldt_instruction, 0);
			do_common_regrm(data, dd, _16bit, false, _null_string);
			sprintf((s8*)&comment_buffer[0], "SLDT - Store Local Descriptor Table");
		}
		else if (r == 1)
		{
			// STR r/m16
			do_common_opcode_rm16_rm32(dd, cgc_str_instruction, 0);
			do_common_regrm(data, dd, _16bit, false, _null_string);
			sprintf((s8*)&comment_buffer[0], "STR - Store Task Register");
		}
		else if (r == 2)
		{
			// LLDT
			do_common_opcode_rm16_rm32(dd, cgc_lldt_instruction, 0);
			do_common_regrm(data, dd, _16bit, false, _null_string);
			sprintf((s8*)&comment_buffer[0], "LLDT - Load Local Descriptor Table");
		}
		else if (r == 3)
		{
			// LTR
			do_common_opcode_rm16_rm32(dd, cgc_ltr_instruction, 0);
			do_common_regrm(data, dd, _16bit, false, _null_string);
			sprintf((s8*)&comment_buffer[0], "LTR - Load Task Register");
		}
		else if (r == 4)
		{
			// VERR r/m16
			do_common_opcode_rm16_rm32(dd, cgc_verr_instruction, 0);
			do_common_regrm(data, dd, _16bit, false, _null_string);
			sprintf((s8*)&comment_buffer[0], "VERW - Verify segment for reading");
		}
		else if (r == 5)
		{
			// VERW r/m16
			do_common_opcode_rm16_rm32(dd, cgc_verw_instruction, 0);
			do_common_regrm(data, dd, _16bit, false, _null_string);
			sprintf((s8*)&comment_buffer[0], "VERW - Verify segment for writing");
		}
		else
		{
			// Unused
			do_common_opcode_rm16_rm32(dd, cgc_unk_instruction, 0);
			do_common_regrm(data, dd, _16bit, false, _null_string);
			sprintf((s8*)&comment_buffer[0], "UNK - Unknown instruction (0F 00 /%u) in the class of LLDT, SLDT, LTR, STR, VERR, VERW", r);
		}
		dd->comment = &comment_buffer[0];
	}

	void opcode_check_reg_0f01(u8* data, SDisasmData* dd)
	{
		u8 r = (*data & 0x38) >> 3;
		
		if (r == 0)
		{
			// SGDT
			do_common_opcode_m_one_operand(data, dd, cgc_sgdt_instruction, _10byte, 0);
			// The fllowing is handled in the do_common_opcode_m_one_operand() function
			//do_common_rm(data, dd, _16bit, false);
			sprintf((s8*)&comment_buffer[0], "SGDT - Store Global Descriptor Table");
		}
		else if (r == 1)
		{
			// SIDT
			do_common_opcode_m_one_operand(data, dd, cgc_sidt_instruction, _10byte, 0);
			sprintf((s8*)&comment_buffer[0], "SIDT - Store Interrupt Descriptor Table");
		}
		else if (r == 2)
		{
			// LGDT
			do_common_opcode_m_one_operand(data, dd, cgc_lgdt_instruction, _10byte, 0);
			sprintf((s8*)&comment_buffer[0], "LGDT - Load Global Descriptor Table");
		}
		else if (r == 3)
		{
			// LIDT
			do_common_opcode_m_one_operand(data, dd, cgc_lidt_instruction, _10byte, 0);
			sprintf((s8*)&comment_buffer[0], "LIDT - Load Interrupt Descriptor Table");
		}
		else if (r == 4)
		{
			// SMSW r/m16/32
			do_common_opcode_rm16_rm32_one_operand(data, dd, cgc_smsw_instruction, _16bit, 0);
			sprintf((s8*)&comment_buffer[0], "LMSW - Store Machine Status Word");
		}
		else if (r == 6)
		{
			// LMSW r/m16
			do_common_opcode_rm16_one_operand(data, dd, cgc_lmsw_instruction, _16bit, 0);
			sprintf((s8*)&comment_buffer[0], "LMSW - Load Machine Status Word");
		}
		else if (r == 7)
		{
			// INVLPG mem
			do_common_opcode_rm16_one_operand(data, dd, cgc_invlpg_instruction, _0bit, 0);
			sprintf((s8*)&comment_buffer[0], "INVLPG - Invalidate TLB Entry");
		}
		else
		{
			// Unused
			do_common_opcode_rm16_rm32(dd, cgc_unk_instruction, 0);
			do_common_regrm(data, dd, _16bit, false, _null_string);
			sprintf((s8*)&comment_buffer[0], "UNK - Unknown instruction (0F 01 /%u) in the class of LGDT, SGDT, LIDT, SIDT, LMSR, SMSW, INVLPG", r);
		}
		dd->comment = &comment_buffer[0];
	}

	void opcode_check_reg_0f71(u8* data, SDisasmData* dd)
	{
		u8 r = (*data & 0x38) >> 3;
		
		if (r == 2)
			opcode_psrlw_immed8(data, dd);					// PSRLW mm,immed8
		else if (r == 4)
			opcode_psraw_immed8(data, dd);					// PSRAW mm,immed8
		else
		{
			// Unused
			if (dd->overrides & (u32)Operand)
			{
				do_common_opcode_xmmx_immed8(dd, cgc_unk_instruction, 0);
				do_common_rm(data, dd, _xmmx, _null_string);
			}
			else
			{
				do_common_opcode_mmx_immed8(dd, cgc_unk_instruction, 0);
				do_common_rm(data, dd, _mmx, _null_string);
			}
			do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit, _null_string);
			sprintf((s8*)&comment_buffer[0], "UNK - Unknown instruction (0F 71 /%u) in the class of PSRAW/PSLAW mm,immed8", r);
		}
		dd->comment = &comment_buffer[0];
	}

	void opcode_check_reg_0f72(u8* data, SDisasmData* dd)
	{
		u8 r = (*data & 0x38) >> 3;
		
		if (r == 2)
			opcode_psrld_immed8(data, dd);					// PSRLD mm,immed8
		else if (r == 4)
			opcode_psrad_immed8(data, dd);					// PSRAD mm,immed8
		else
		{
			// Unused
			if (dd->overrides & (u32)Operand)
			{
				do_common_opcode_xmmx_immed8(dd, cgc_unk_instruction, 0);
				do_common_rm(data, dd, _xmmx, _null_string);
			}
			else
			{
				do_common_opcode_mmx_immed8(dd, cgc_unk_instruction, 0);
				do_common_rm(data, dd, _mmx, _null_string);
			}
			do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit, _null_string);
			sprintf((s8*)&comment_buffer[0], "UNK - Unknown instruction (0F 72 /%u) in the class of PSRAD/PSRLD mm,immed8", r);
		}
		dd->comment = &comment_buffer[0];
	}

	void opcode_check_reg_0f73(u8* data, SDisasmData* dd)
	{
		u8 r = (*data & 0x38) >> 3;
		
		if (r == 2)
			opcode_psrlq_immed8(data, dd);					// PSRLQ mm,immed8
		else
		{
			// Unused
			if (dd->overrides & (u32)Operand)
			{
				do_common_opcode_xmmx_immed8(dd, cgc_unk_instruction, 0);
				do_common_rm(data, dd, _xmmx, _null_string);
			}
			else
			{
				do_common_opcode_mmx_immed8(dd, cgc_unk_instruction, 0);
				do_common_rm(data, dd, _mmx, _null_string);
			}
			do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit, _null_string);
			sprintf((s8*)&comment_buffer[0], "UNK - Unknown instruction (0F 73 /%u) in the class of PSRLQ mm,immed8", r);
			dd->comment = &comment_buffer[0];
		}
	}

	void opcode_check_reg_0fba(u8* data, SDisasmData* dd)
	{
		u8 r = (*data & 0x38) >> 3;
		
		if (r == 4)				do_common_rm16_32_immed8(data, dd, cgc_bt_instruction, 1);		// BT r/m16/32,imm8
		else if (r == 5)		do_common_rm16_32_immed8(data, dd, cgc_bts_instruction, 1);		// BTS r/m16/32,imm8
		else if (r == 6)		do_common_rm16_32_immed8(data, dd, cgc_btr_instruction, 1);		// BTR r/m16/32,imm8
		else if (r == 7)		do_common_rm16_32_immed8(data, dd, cgc_btc_instruction, 1);		// BTC r/m16/32,imm8
		else
		{
			// Unused
			do_common_rm16_32_immed8(data, dd, cgc_unk_instruction, 0);
			sprintf((s8*)&comment_buffer[0], "UNK - Unknown instruction (0F ba /%u) in the class of BT, BTS, BTR, BTC r/m16/32,immed8", (int)r);
			dd->comment = &comment_buffer[0];
		}
	}

	void opcode_check_reg_0fc7(u8* data, SDisasmData* dd)
	{
		u8 r = (*data & 0x38) >> 3;
		
		if (r == 1)
			opcode_cmpxchg8b(data, dd);					// CMPXCHG8B m64
		else
		{
			if (dd->prefixes & (u32)LOCK && *data == 0xc8)
			{
				//  Undocumented instruction "hcf, halt and catch fire"
				// f0 0f c7 c8
				do_common_mnemonic(dd, cgc_hcf_instruction, 1, (u8*)"HCF - Halt and Catch Fire", (u8*)"; Warning! Locks up the cpu");
			}
			else
			{
				// Unused
				do_common_rm16_32_immed8(data, dd, cgc_unk_instruction, 0);
				sprintf((s8*)&comment_buffer[0], "UNK - Unknown instruction (0F ba /%u) in the class of BT, BTS, BTR, BTC r/m16/32,immed8", r);
				dd->comment = &comment_buffer[0];
			}
		}
	}

	void opcode_check_reg_80(u8* data, SDisasmData* dd)
	{
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)				do_common_rm8_immed8(data, dd, cgc_add_instruction, 1);		// ADD r/m8,imm8
		else if (r == 1)		do_common_rm8_immed8(data, dd, cgc_or_instruction, 1);		// OR r/m8,imm8
		else if (r == 2)		do_common_rm8_immed8(data, dd, cgc_adc_instruction, 1);		// ADC r/m8,imm8
		else if (r == 3)		do_common_rm8_immed8(data, dd, cgc_sbb_instruction, 1);		// SBB r/m8,imm8
		else if (r == 4)		do_common_rm8_immed8(data, dd, cgc_and_instruction, 1);		// AND r/m8,imm8
		else if (r == 5)		do_common_rm8_immed8(data, dd, cgc_sub_instruction, 1);		// SUB r/m8,imm8
		else if (r == 6)		do_common_rm8_immed8(data, dd, cgc_xor_instruction, 1);		// XOR r/m8,imm8
		else if (r == 7)		do_common_rm8_immed8(data, dd, cgc_cmp_instruction, 1);		// CMP r/m8,imm8
	}

	void opcode_check_reg_81(u8* data, SDisasmData* dd)
	{
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)				do_common_rm16_32_immed16_32(data, dd, cgc_add_instruction, 1);		// ADD r/m16/32,imm16/32
		else if (r == 1)		do_common_rm16_32_immed16_32(data, dd, cgc_or_instruction, 1);		// OR r/m16/32,immed16/32
		else if (r == 2)		do_common_rm16_32_immed16_32(data, dd, cgc_adc_instruction, 1);		// ADC r/m16/32,imm16/32
		else if (r == 3)		do_common_rm16_32_immed16_32(data, dd, cgc_sbb_instruction, 1);		// SBB r/m16/32,imm16/32
		else if (r == 4)		do_common_rm16_32_immed16_32(data, dd, cgc_and_instruction, 1);		// AND r/m16/32,imm16/32
		else if (r == 5)		do_common_rm16_32_immed16_32(data, dd, cgc_sub_instruction, 1);		// SUB r/m16/32,imm16/32
		else if (r == 6)		do_common_rm16_32_immed16_32(data, dd, cgc_xor_instruction, 1);		// XOR r/m16/32,imm16/32
		else if (r == 7)		do_common_rm16_32_immed16_32(data, dd, cgc_cmp_instruction, 1);		// CMP r/m16/32,imm16/32
	}

	void opcode_check_reg_82(u8* data, SDisasmData* dd)
	{ // 82
		// Unused
		do_common_unknown(data, dd, cgc_unk_instruction, 1, NULL, NULL);
	}

	void opcode_check_reg_83(u8* data, SDisasmData* dd)
	{
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)				do_common_rm16_32_immed8(data, dd, cgc_add_instruction, 1);		// ADD r/m16/32,imm8
		else if (r == 1)		do_common_rm16_32_immed8(data, dd, cgc_or_instruction, 1);		// OR r/m16/32,immed8
		else if (r == 2)		do_common_rm16_32_immed8(data, dd, cgc_adc_instruction, 1);		// ADC r/m16/32,imm8
		else if (r == 3)		do_common_rm16_32_immed8(data, dd, cgc_sbb_instruction, 1);		// SBB r/m16/32,imm8
		else if (r == 4)		do_common_rm16_32_immed8(data, dd, cgc_and_instruction, 1);		// AND r/m16/32,imm8
		else if (r == 5)		do_common_rm16_32_immed8(data, dd, cgc_sub_instruction, 1);		// SUB r/m16/32,imm8
		else if (r == 6)		do_common_rm16_32_immed8(data, dd, cgc_xor_instruction, 1);		// XOR r/m16/32,imm8
		else if (r == 7)		do_common_rm16_32_immed8(data, dd, cgc_cmp_instruction, 1);		// CMP r/m16/32,imm8
	}

	void opcode_check_reg_8f(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_opcode_rm16_rm32_one_operand(data, dd, cgc_pop_instruction, 0, 1);	// POP rm16/32
		else
		{
			// Unused
			sprintf((s8*)&buff[256], "UNK - Unknown instruction (8f /%u) in the class of POP m16/32", (int)r);
			do_common_mnemonic(dd, cgc_unk_instruction, 2, &buff[256], NULL);
		}
	}

	void opcode_check_reg_c0(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)				do_common_rm8_immed8(data, dd, cgc_rol_instruction, 1);		// ROL rm8,imm8
		else if (r == 1)		do_common_rm8_immed8(data, dd, cgc_ror_instruction, 1);		// ROR rm8,imm8
		else if (r == 2)		do_common_rm8_immed8(data, dd, cgc_rcl_instruction, 1);		// RCL rm8,imm8
		else if (r == 3)		do_common_rm8_immed8(data, dd, cgc_rcr_instruction, 1);		// RCR rm8,imm8
		else if (r == 4)		do_common_rm8_immed8(data, dd, cgc_shl_instruction, 1);		// SHL rm8,imm8
		else if (r == 5)		do_common_rm8_immed8(data, dd, cgc_shr_instruction, 1);		// SHR rm8,imm8
		else if (r == 7)		do_common_rm8_immed8(data, dd, cgc_sar_instruction, 1);		// SAR rm8,imm8
		else
		{
			// Unused
			sprintf((s8*)&buff[256], "UNK - Unknown instruction (c0 /%u) in the class of ROL, ROR, RCL, RCR, SHL, SHR, SAR rm8,immed8", (int)r);
			do_common_mnemonic(dd, cgc_unk_instruction, 2, &buff[256], NULL);
		}
	}

	void opcode_check_reg_c1(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)				do_common_rm16_32_immed8(data, dd, cgc_rol_instruction, 1);		// ROL rm16/32,imm8
		else if (r == 1)		do_common_rm16_32_immed8(data, dd, cgc_ror_instruction, 1);		// ROR rm16/32,imm8
		else if (r == 2)		do_common_rm16_32_immed8(data, dd, cgc_rcl_instruction, 1);		// RCL rm16/32,imm8
		else if (r == 3)		do_common_rm16_32_immed8(data, dd, cgc_rcr_instruction, 1);		// RCR rm16/32,imm8
		else if (r == 4)		do_common_rm16_32_immed8(data, dd, cgc_shl_instruction, 1);		// SHL rm16/32,imm8
		else if (r == 5)		do_common_rm16_32_immed8(data, dd, cgc_shr_instruction, 1);		// SHR rm16/32,imm8
		else if (r == 6)
		{
			// Unused opcode
			sprintf((s8*)&buff[256], "UNK - Unknown instruction (c1 /%u) in the class of ROL, ROR, RCL, RCR, SHL, SHR, SAR m16/32", (int)r);
			do_common_mnemonic(dd, cgc_unk_instruction, 2, &buff[256], NULL);
		}
		else if (r == 7)		do_common_rm16_32_immed8(data, dd, cgc_sar_instruction, 1);		// SAR rm16/32,imm8
	}

	void opcode_check_reg_c6(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_rm8_immed8(data, dd, cgc_mov_instruction, 1);		// MOV rm8,imm8
		else
		{
			// Unused
			sprintf((s8*)&buff[256], "UNK - Unknown instruction (c6 /%u) in the class of MOV rm8,imm8", (int)r);
			do_common_mnemonic(dd, cgc_unk_instruction, 2, &buff[256], NULL);
		}
	}

	void opcode_check_reg_c7(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)
			do_common_rm16_32_immed16_32(data, dd, cgc_mov_instruction, 1);	// mov rm/16/32,imm16/32
		else if (r == 1)
		{
			// Unused
			sprintf((s8*)&buff[256], "UNK - Unknown instruction (c7 /%u) in the class of MOV rm16/32,immed16/32", (int)r);
			do_common_mnemonic(dd, cgc_unk_instruction, 2, &buff[256], NULL);
		}
	}

	void opcode_check_reg_d0(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)				do_common_rm8_1(data, dd, cgc_rol_instruction, 1);		// ROL rm8,1
		else if (r == 1)		do_common_rm8_1(data, dd, cgc_ror_instruction, 1);		// ROR rm8,1
		else if (r == 2)		do_common_rm8_1(data, dd, cgc_rcl_instruction, 1);		// RCL rm8,1
		else if (r == 3)		do_common_rm8_1(data, dd, cgc_rcl_instruction, 1);		// RCR rm8,1
		else if (r == 4)		do_common_rm8_1(data, dd, cgc_shl_instruction, 1);		// SHL rm8,1
		else if (r == 5)		do_common_rm8_1(data, dd, cgc_shr_instruction, 1);		// SHR rm8,1
		else if (r == 6)
		{
			// Unused
			sprintf((s8*)&buff[256], "UNK - Unknown instruction (d0 /%u) in the class of ROL, ROR, RCL, RCR, SHL, SHR, SAR rm8,1", (int)r);
			do_common_mnemonic(dd, cgc_unk_instruction, 2, &buff[256], NULL);
		}
		else if (r == 7)		do_common_rm8_1(data, dd, cgc_sar_instruction, 1);		// SAR rm8,1
	}

	void opcode_check_reg_d1(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)				do_common_rm16_32_1(data, dd, cgc_rol_instruction, 1);		// ROL rm16/32,1
		else if (r == 1)		do_common_rm16_32_1(data, dd, cgc_ror_instruction, 1);		// ROR rm16/32,1
		else if (r == 2)		do_common_rm16_32_1(data, dd, cgc_rcl_instruction, 1);		// RCL rm16/32,1
		else if (r == 3)		do_common_rm16_32_1(data, dd, cgc_rcr_instruction, 1);		// RCR rm16/32,1
		else if (r == 4)		do_common_rm16_32_1(data, dd, cgc_shl_instruction, 1);		// SHL rm16/32,1
		else if (r == 5)		do_common_rm16_32_1(data, dd, cgc_shr_instruction, 1);		// SHR rm16/32,1
		else if (r == 6)
		{
			// Unused
			sprintf((s8*)&buff[256], "UNK - Unknown instruction (d1 /%u) in the class of ROL, ROR, RCL, RCR, SHL, SHR, SAR rm16/32,1", (int)r);
			do_common_mnemonic(dd, cgc_unk_instruction, 2, &buff[256], NULL);
		}
		else if (r == 7)		do_common_rm16_32_1(data, dd, cgc_sar_instruction, 1);		// SAR rm16/32,1
	}

	void opcode_check_reg_d2(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)				do_common_rm8_cl(data, dd, cgc_rol_instruction, 1);		// ROL rm8,cl
		else if (r == 1)		do_common_rm8_cl(data, dd, cgc_rol_instruction, 1);		// ROR rm8,cl
		else if (r == 2)		do_common_rm8_cl(data, dd, cgc_rcl_instruction, 1);		// RCL rm8,cl
		else if (r == 3)		do_common_rm8_cl(data, dd, cgc_rcr_instruction, 1);		// RCR rm8,cl
		else if (r == 4)		do_common_rm8_cl(data, dd, cgc_shl_instruction, 1);		// SHL rm8,cl
		else if (r == 5)		do_common_rm8_cl(data, dd, cgc_shr_instruction, 1);		// SHR rm8,cl
		else if (r == 6)
		{
			// Unused
			sprintf((s8*)&buff[256], "UNK - Unknown instruction (d2 /%u) in the class of ROL, ROR, RCL, RCR, SHL, SHR, SAR rm8,cl", (int)r);
			do_common_mnemonic(dd, cgc_unk_instruction, 2, &buff[256], NULL);
		}
		else if (r == 7)		do_common_rm8_cl(data, dd, cgc_sar_instruction, 1);		// SAR rm8,cl
	}

	void opcode_check_reg_d3(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)				do_common_rm16_32_cl(data, dd, cgc_rol_instruction, 1);		// ROL rm16/32,cl
		else if (r == 1)		do_common_rm16_32_cl(data, dd, cgc_ror_instruction, 1);		// ROR rm16/32,cl
		else if (r == 2)		do_common_rm16_32_cl(data, dd, cgc_rcl_instruction, 1);		// RCL rm16/32,cl
		else if (r == 3)		do_common_rm16_32_cl(data, dd, cgc_rcr_instruction, 1);		// RCR rm16/32,cl
		else if (r == 4)		do_common_rm16_32_cl(data, dd, cgc_shl_instruction, 1);		// SHL rm16/32,cl
		else if (r == 5)		do_common_rm16_32_cl(data, dd, cgc_shr_instruction, 1);		// SHR rm16/32,cl
		else if (r == 6)
		{
			// Unused
			sprintf((s8*)&buff[256], "UNK - Unknown instruction (d2 /%u) in the class of ROL, ROR, RCL, RCR, SHL, SHR, SAR rm16/32,cl", (int)r);
			do_common_mnemonic(dd, cgc_unk_instruction, 2, &buff[256], NULL);
		}
		else if (r == 7)		do_common_rm16_32_cl(data, dd, cgc_sar_instruction, 1);		// SAR rm16/32,cl
	}

	void opcode_check_reg_f6(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)				do_common_rm8_immed8(data, dd, cgc_test_instruction, 1);			// TEST rm8,imm8
		else if (r == 1)
		{
			// Unused
			sprintf((s8*)&buff[256], "UNK - Unknown instruction (f6 /%u) in the class of TEST, NOT, NEG, MUL, IMUL, DIV, IDIV rm8", (int)r);
			do_common_mnemonic(dd, cgc_unk_instruction, 2, &buff[256], NULL);
		}
		else if (r == 2)		do_common_opcode_rm8_one_operand(data, dd, cgc_not_instruction, 0, 1);	// NOT rm8
		else if (r == 3)		do_common_opcode_rm8_one_operand(data, dd, cgc_neg_instruction, 0, 1);	// NEG rm8
		else if (r == 4)		do_common_opcode_rm8_one_operand(data, dd, cgc_mul_instruction, 0, 1);	// MUL rm8
		else if (r == 5)		do_common_opcode_rm8_one_operand(data, dd, cgc_imul_instruction, 0, 1);	// IMUL rm8
		else if (r == 6)		do_common_opcode_rm8_one_operand(data, dd, cgc_div_instruction, 0, 1);	// DIV rm8
		else if (r == 7)		do_common_opcode_rm8_one_operand(data, dd, cgc_idiv_instruction, 0, 1);	// IDIV rm8
	}

	void opcode_check_reg_f7(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)				do_common_rm16_32_immed16_32(data, dd, cgc_test_instruction, 1);			// TEST rm16/32,imm16/32
		else if (r == 1)
		{
			// Unused
			sprintf((s8*)&buff[256], "UNK - Unknown instruction (f7 /%u) in the class of TEST, NOT, NEG, MUL, IMUL, DIV, IDIV rm16/32,immed16/32", (int)r);
			do_common_mnemonic(dd, cgc_unk_instruction, 2, &buff[256], NULL);
		}
		else if (r == 2)		do_common_opcode_rm16_rm32_one_operand(data, dd, cgc_neg_instruction, 0, 1);		// NEG rm16/32
		else if (r == 3)		do_common_opcode_rm16_rm32_one_operand(data, dd, cgc_neg_instruction, 0, 1);		// NOT rm16/32
		else if (r == 4)		do_common_opcode_rm16_rm32_one_operand(data, dd, cgc_neg_instruction, 0, 1);		// MUL rm16/32
		else if (r == 5)		do_common_opcode_rm16_rm32_one_operand(data, dd, cgc_imul_instruction, 0, 1);		// IMUL rm16/32
		else if (r == 6)		do_common_opcode_rm16_rm32_one_operand(data, dd, cgc_div_instruction, 0, 1);		// DIV rm16/32
		else if (r == 7)		do_common_opcode_rm16_rm32_one_operand(data, dd, cgc_idiv_instruction, 0, 1);		// IDIV rm16/32
	}

	void opcode_check_reg_fe(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)				do_common_opcode_rm8_one_operand(data, dd, cgc_inc_instruction, 0, 1);	// INC rm8
		else if (r == 1)		do_common_opcode_rm8_one_operand(data, dd, cgc_dec_instruction, 0, 1);	// DEC rm8
		else
		{
			// Unused
			sprintf((s8*)&buff[256], "UNK - Unknown instruction (fe /%u) in the class of INC, DEC rm8", (int)r);
			do_common_mnemonic(dd, cgc_unk_instruction, 2, &buff[256], NULL);
		}
	}
	
	void opcode_jmp_call_rm1632_absolute_indirect(u8* data, SDisasmData* dd, u8* instruction)
	{
		do_common_mnemonic(dd, instruction, 1, NULL, NULL);
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Address) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Address) != 0))
		{
			// 32-bit addressing mode
			extract_modrm_32bit_address_mode(data + 1, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2,
											 dd->overrides & (u32)Operand ? _16bit    : _32bit, false, 
											 dd->overrides & (u32)Operand ? cgc_word_ptr : cgc_dword_ptr);
		}
		else
		{
			// 16-bit addressing mode
			extract_modrm_16bit_address_mode(data + 1, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2,
											 dd->overrides & (u32)Operand ? _32bit     : _16bit, false,
											 dd->overrides & (u32)Operand ? cgc_dword_ptr : cgc_word_ptr);
		}
	}
	
	void opcode_jmp_call_m16_m1632_absolute_indirect(u8* data, SDisasmData* dd, u8* instruction)
	{
		do_common_mnemonic(dd, instruction, 1, NULL, NULL);
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Address) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Address) != 0))
		{
			// 32-bit addressing mode
			extract_modrm_32bit_address_mode(data + 1, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2,
											 dd->overrides & (u32)Operand ? _16bit    : _32bit, false, 
											 dd->overrides & (u32)Operand ? cgc_word_ptr : cgc_dword_ptr);
		}
		else
		{
			// 16-bit addressing mode
			extract_modrm_16bit_address_mode(data + 1, dd, &operand1_buffer[0], &dd->operand1, &dd->operand2,
											 dd->overrides & (u32)Operand ? _32bit     : _16bit, false,
											 dd->overrides & (u32)Operand ? cgc_dword_ptr : cgc_word_ptr);
		}
	}

	void opcode_check_reg_ff(u8* data, SDisasmData* dd)
	{
		u8 buff[256];
		u8 r = (*(data + 1) & 0x38) >> 3;
		
		if (r == 0)				do_common_opcode_rm16_rm32_one_operand(data, dd, cgc_inc_instruction, 0, 1);		// INC rm16/32
		else if (r == 1)		do_common_opcode_rm16_rm32_one_operand(data, dd, cgc_dec_instruction, 0, 1);		// DEC rm16/32
		else if (r == 2)		opcode_jmp_call_rm1632_absolute_indirect(data, dd, cgc_call_instruction);			// CALL rm16/32 absolute
		else if (r == 3)		opcode_jmp_call_m16_m1632_absolute_indirect(data, dd, cgc_call_instruction);		// CALL m16_m16/32 absolute
		else if (r == 4)		opcode_jmp_call_rm1632_absolute_indirect(data, dd, cgc_jmp_instruction);			// JMP m16_m16/32 absolute
		else if (r == 5)		opcode_jmp_call_m16_m1632_absolute_indirect(data, dd, cgc_jmp_instruction);			// JMP FAR m16_m16/32 absolute
		else if (r == 6)		do_common_opcode_rm16_rm32_one_operand(data, dd, cgc_push_instruction, 0, 1);		// PUSH rm16/32
		else if (r == 7)
		{
			// Unused
			sprintf((s8*)&buff[256], "UNK - Unknown instruction (ff /%u) in the class of INC, DEC rm16/32, CALL/JMP rm16/32, CALL/JMP m16_m16/32", (int)r);
			do_common_mnemonic(dd, cgc_unk_instruction, 2, &buff[256], NULL);
		}
	}

	void opcode_clc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_clc_instruction, 1, NULL, NULL);
	}

	void opcode_cld(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cld_instruction, 1, NULL, NULL);
	}

	void opcode_cli(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cli_instruction, 1, NULL, NULL);
	}

	void opcode_clts(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_clts_instruction, 1, NULL, NULL);
	}

	void opcode_cmc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmc_instruction, 1, NULL, NULL);
	}

	void opcode_cmova(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmova_instruction, 0, NULL, NULL);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmovc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmovc_instruction, 0, NULL, NULL);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmovg(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmovg_instruction, 0, NULL, NULL);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmovl(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmovl_instruction, 0, NULL, NULL);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmovna(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmovna_instruction, 0, NULL, NULL);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmovnc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmovnc_instruction, 0, NULL, NULL);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmovng(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmovng_instruction, 0, NULL, NULL);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmovnl(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmovnl_instruction, 0, NULL, NULL);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmovno(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmovno_instruction, 0, NULL, NULL);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmovns(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmovns_instruction, 0, NULL, NULL);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmovnz(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmovnz_instruction, 0, NULL, NULL);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmovo(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmovo_instruction, 0, NULL, NULL);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmovpe(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmovpe_instruction, 0, NULL, NULL);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmovpo(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmovpo_instruction, 0, NULL, NULL);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmovs(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmovs_instruction, 0, NULL, NULL);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmovz(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmovz_instruction, 0, NULL, NULL);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}
	
	void opcode_cmp38(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8_reversed(dd, cgc_cmp_instruction, 1);
		do_common_regrm(data + 1, dd, _8bit, false, _null_string);
	}

	void opcode_cmp39(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32_reversed(dd, cgc_cmp_instruction, 1);
		do_common_regrm(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmp3a(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8(dd, cgc_cmp_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _8bit, false, _null_string);
	}

	void opcode_cmp3b(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, cgc_cmp_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmp3c(u8* data, SDisasmData* dd)
	{
		do_common_accum8_immed8(data, dd, cgc_cmp_instruction, 1);
	}

	void opcode_cmp3d(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed16_32(data, dd, cgc_cmp_instruction, 1);
	}

	void opcode_cmpsb(u8* data, SDisasmData* dd)
	{
		if (dd->prefixes & REPE)
		{
			dd->mnemonic	= (u8*)"repe";
			dd->operand1	= (u8*)"cmpsb";
		}
		else if (dd->prefixes & REPNE)
		{
			dd->mnemonic	= (u8*)"repne";
			dd->operand1	= (u8*)"cmpsb";
		}
		else
		{
			dd->mnemonic	= (u8*)"cmpsb";
		}
		dd->opcode_bytes	+= 1;
	}

	void opcode_cmpsw(u8* data, SDisasmData* dd)
	{
		do_common_two_prefixes_mnemonic_operand_size_check(dd, 1, 
															REPE,	cgc_repe_instruction,
															REPNE,	cgc_repne_instruction,
															cgc_cmpsw_instruction,
															cgc_cmpsd_instruction);
	}

	void opcode_cmpxchg(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmpxchg_instruction, 0, NULL, NULL);
		do_common_regrm(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_cmpxchg_byte(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmpxchg_instruction, 0, NULL, NULL);
		do_common_regrm(data, dd, _8bit, false, _null_string);
	}

	void opcode_cmpxchg8b(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cmpxchg8b_instruction, 0, NULL, NULL);
		do_common_rm(data, dd, _16bit | _32bit, _null_string);
	}

	void opcode_cpuid(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cpuid_instruction, 1, NULL, NULL);
	}

	void opcode_cs_override(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= CSREG;
		dd->opcode_bytes	+= 1;
	}

	void opcode_cwd(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_cwd_instruction, 1, NULL, NULL);
	}

	void opcode_daa(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_daa_instruction, 1, NULL, NULL);
	}

	void opcode_das(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_das_instruction, 1, NULL, NULL);
	}

	void opcode_dec_xxx(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_dec_instruction, 1, NULL, NULL);
		extract_gp_reg_operand(dd, *data & 0x07, &dd->operand1, _16bit | _32bit);
	}
	
	void opcode_ds_override(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= DSREG;
		dd->opcode_bytes	+= 1;
	}

	void opcode_emms(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_emms_instruction, 1, NULL, NULL);
	}

	void opcode_enter(u8* data, SDisasmData* dd)
	{
		sprintf((s8*)&operand1_buffer[0], "%u", (int)(*(u16*)(data + 1)));
		sprintf((s8*)&operand2_buffer[0], "%u", (int)(*(u8*)(data + 3)));
		dd->mnemonic		= (u8*)"enter";
		dd->operand1		= &operand1_buffer[0];
		dd->operand2		= &operand2_buffer[0];
		dd->opcode_bytes	+= 4;
	}

	void opcode_es_override(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= ESREG;
		dd->opcode_bytes	+= 1;
	}

	void opcode_fpu_d8(u8* data, SDisasmData* dd)
	{
		u8 rm = *(data + 1);
_asm int 3;
		
		
		if (rm >= 0xc0 && rm <= 0xc7)				do_common_opcode_fpu_hard_stx(data, dd, cgc_fadd_instruction, 0, 2);		// FADD st(0),st(i)
		else if (rm >= 0xc8 && rm <= 0xcf)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fmul_instruction, 0, 2);		// FMUL st(0),st(i)
		else if (rm >= 0xd0 && rm <= 0xd7)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fcom_instruction, 0, 2);		// FCOM st(0),st(i)
		else if (rm >= 0xd8 && rm <= 0xdf)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fcomp_instruction, 0, 2);		// FCOMP st(0),st(i)
		else if (rm >= 0xe0 && rm <= 0xe7)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fsub_instruction, 0, 2);		// FSUB st(0),st(i)
		else if (rm >= 0xe8 && rm <= 0xef)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fsubr_instruction, 0, 2);		// FSUBR st(0),st(i)
		else if (rm >= 0xf0 && rm <= 0xf7)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fdiv_instruction, 0, 2);		// FDIV st(0),st(i)
		else if (rm >= 0xf8 && rm <= 0xff)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fdivr_instruction, 0, 2);		// FDIVR st(0),st(i)


		// It wasn't one of the st0/sti instructions, so we check the reg bits
		rm = (rm >> 3) & 0x07;
		if (rm == 0)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fadd_instruction, _f32, 2);		// FADD real4
		else if (rm == 1)			do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fmul_instruction, _f32, 2);		// FMUL real4
		else if (rm == 2)			do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fcom_instruction, _f32, 2);		// FCOM real4
		else if (rm == 3)			do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fcomp_instruction, _f32, 2);		// FCOMP real4
		else if (rm == 4)			do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fsub_instruction, _f32, 2);		// FSUB real4
		else if (rm == 5)			do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fsubr_instruction, _f32, 2);		// FSUBR real4
		else if (rm == 6)			do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fdiv_instruction, _f32, 2);		// FDIV real4
		else if (rm == 7)			do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fdivr_instruction, _f32, 2);		// FDIVR real4
	}

	void opcode_fpu_d9(u8* data, SDisasmData* dd)
	{
		u8 rm = *(data + 1);
_asm int 3;
		
		if (rm >= 0xc0 && rm <= 0xc7)			do_common_opcode_fpu_stx(data, dd, cgc_fld_instruction);			// fld st(i)
		else if (rm >= 0xc8 && rm <= 0xcf)		do_common_opcode_fpu_stx(data, dd, cgc_fxch_instruction);			// fxch st(i)
		else if (rm == 0xd0)					do_common_mnemonic(dd, cgc_fnop_instruction, 1, NULL, NULL);		// fnop
		else if (rm == 0xe0)					do_common_mnemonic(dd, cgc_fchs_instruction, 1, NULL, NULL);		// fchs
		else if (rm == 0xe1)					do_common_mnemonic(dd, cgc_fabs_instruction, 1, NULL, NULL);		// fabs
		else if (rm == 0xe4)					do_common_mnemonic(dd, cgc_ftst_instruction, 1, NULL, NULL);		// ftst
		else if (rm == 0xe5)					do_common_mnemonic(dd, cgc_fxam_instruction, 1, NULL, NULL);		// fxam
		else if (rm == 0xe8)					do_common_mnemonic(dd, cgc_fld1_instruction, 1, NULL, NULL);		// fld1
		else if (rm == 0xe9)					do_common_mnemonic(dd, cgc_fld2t_instruction, 1, NULL, NULL);		// fldl2t
		else if (rm == 0xea)					do_common_mnemonic(dd, cgc_fld2e_instruction, 1, NULL, NULL);		// fldl2e
		else if (rm == 0xeb)					do_common_mnemonic(dd, cgc_fldpi_instruction, 1, NULL, NULL);		// fldpi
		else if (rm == 0xec)					do_common_mnemonic(dd, cgc_fldlg2_instruction, 1, NULL, NULL);		// fldlg2
		else if (rm == 0xed)					do_common_mnemonic(dd, cgc_fldln2_instruction, 1, NULL, NULL);		// fldln2
		else if (rm == 0xee)					do_common_mnemonic(dd, cgc_fldz_instruction, 1, NULL, NULL);		// fldz
		else if (rm == 0xf0)					do_common_mnemonic(dd, cgc_f2xm1_instruction, 1, NULL, NULL);		// f2xm1
		else if (rm == 0xf1)					do_common_mnemonic(dd, cgc_fyl2x_instruction, 1, NULL, NULL);		// fyl2x
		else if (rm == 0xf2)					do_common_mnemonic(dd, cgc_fptan_instruction, 1, NULL, NULL);		// fptan
		else if (rm == 0xf3)					do_common_mnemonic(dd, cgc_fpatan_instruction, 1, NULL, NULL);		// fpatan
		else if (rm == 0xf4)					do_common_mnemonic(dd, cgc_fxtract_instruction, 1, NULL, NULL);		// fxtract
		else if (rm == 0xf5)					do_common_mnemonic(dd, cgc_fprem1_instruction, 1, NULL, NULL);		// fprem1
		else if (rm == 0xf6)					do_common_mnemonic(dd, cgc_fdecstp_instruction, 1, NULL, NULL);		// fdecstp
		else if (rm == 0xf7)					do_common_mnemonic(dd, cgc_fincstp_instruction, 1, NULL, NULL);		// fincstp
		else if (rm == 0xf8)					do_common_mnemonic(dd, cgc_fprem_instruction, 1, NULL, NULL);		// fprem
		else if (rm == 0xf9)					do_common_mnemonic(dd, cgc_fyl2xp1_instruction, 1, NULL, NULL);		// fyl2xp1
		else if (rm == 0xfa)					do_common_mnemonic(dd, cgc_fsqrt_instruction, 1, NULL, NULL);		// fsqrt
		else if (rm == 0xfb)					do_common_mnemonic(dd, cgc_fsincos_instruction, 1, NULL, NULL);		// fsincos
		else if (rm == 0xfc)					do_common_mnemonic(dd, cgc_frndint_instruction, 1, NULL, NULL);		// frndint
		else if (rm == 0xfd)					do_common_mnemonic(dd, cgc_fscale_instruction, 1, NULL, NULL);		// fscale
		else if (rm == 0xfe)					do_common_mnemonic(dd, cgc_fsin_instruction, 1, NULL, NULL);		// fsin
		else if (rm == 0xff)					do_common_mnemonic(dd, cgc_fcos_instruction, 1, NULL, NULL);		// fcos
		else
		{
			rm = (rm >> 3) & 0x07;
			if (rm == 0)						do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fadd_instruction, _f32);		// FLD real4
			else if (rm == 2)					do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fst_instruction, _f32);		// FST real4
			else if (rm == 3)					do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fstp_instruction, _f32);		// FSTP real4
			else if (rm == 4)
			{
				// fldenv
				if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
					(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
				{
					// 32-bit addressing mode
					do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fldenv_instruction, _m28byte);
				}
				else
				{
					// 16-bit addressing mode
					do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fldenv_instruction, _m14byte);
				}
			}
			else if (rm == 5)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fldcw_instruction, _16bit);		// fldcw m16
			else if (rm == 6)
			{
				// fnstenv
				if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
					(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
				{
					// 32-bit addressing mode
					do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fnstenv_instruction, _m28byte);
				}
				else
				{
					// 16-bit addressing mode
					do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fnstenv_instruction, _m14byte);
				}
			}
			else if (rm == 7)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fnstcw_instruction, _16bit);		// fnstcw m16
			else							do_common_unknown(data, dd, (u8*)"FUNK", 2, (u8*)"FUNK - Floating point unknown instruction");
		}
	}

	void opcode_fpu_da(u8* data, SDisasmData* dd)
	{
		u8 rm = *(data + 1);
_asm int 3;

		if (rm >= 0xc0 && rm <= 0xc7)				do_common_opcode_fpu_hard_stx(data, dd, cgc_fdivr_instruction, 0);		// FCMOVB st0,sti
		else if (rm >= 0xc8 && rm <= 0xcf)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fdivr_instruction, 0);		// FCMOVZ st0,sti
		else if (rm >= 0xd0 && rm <= 0xd7)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fdivr_instruction, 0);		// FCMOVNG st0,sti
		else if (rm >= 0xd8 && rm <= 0xdf)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fdivr_instruction, 0);		// FCMOVPO st0,sti
		else if (rm == 0xe9)						do_common_mnemonic(dd, cgc_fucompp_instruction, 1, NULL, NULL);			// FUCOMPP
		else
		{
			rm = (rm >> 3) & 0x07;
			if (rm == 0)					do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fiadd_instruction, _s32);		// FIADD m32_int
			else if (rm == 1)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fimul_instruction, _s32);		// FIMUL m32_int
			else if (rm == 2)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_ficom_instruction, _s32);		// FICOM m32_int
			else if (rm == 3)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_ficomp_instruction, _s32);	// FICOMP m32_int
			else if (rm == 4)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fisub_instruction, _s32);		// FISUB m32_int
			else if (rm == 5)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fisubr_instruction, _s32);	// FISUBR m32_int
			else if (rm == 6)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fidiv_instruction, _s32);		// FIDIV m32_int
			else if (rm == 7)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fidivr_instruction, _s32);	// FIDIVR m32_int
		}
	}

	void opcode_fpu_db(u8* data, SDisasmData* dd)
	{
		u8 rm = *(data + 1);
_asm int 3;


		if (rm >= 0xc0 && rm <= 0xc7)				do_common_opcode_fpu_hard_stx(data, dd, cgc_fdivr_instruction, 0);		// FCMOVNB st0,sti
		else if (rm >= 0xc8 && rm <= 0xcf)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fdivr_instruction, 0);		// FCMOVNZ st0,sti
		else if (rm >= 0xd0 && rm <= 0xd7)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fdivr_instruction, 0);		// FCMOVG st0,sti
		else if (rm >= 0xd8 && rm <= 0xdf)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fdivr_instruction, 0);		// FCMOVPE st0,sti
		else if (rm == 0xe2)						do_common_mnemonic(dd, cgc_fnclex_instruction, 1, NULL, NULL);			// fnclex
		else if (rm == 0xe3)						do_common_mnemonic(dd, cgc_fninit_instruction, 1, NULL, NULL);			// fninit
		else if (rm >= 0xe8 && rm <= 0xef)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fdivr_instruction, 0);		// FUCOMI st(0),st(i)
		else if (rm >= 0xf0 && rm <= 0xf7)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fdivr_instruction, 0);		// FCOMI st(0),st(i)
		else
		{
			rm = (rm >> 3) & 0x07;
			if (rm == 0)					do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fild_instruction, _s32);		// FILD m32_int
			else if (rm == 2)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fist_instruction, _s32);		// FIST m32_int
			else if (rm == 3)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fistp_instruction, _s32);		// FISTP m32_int
			else if (rm == 5)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fld_instruction, _f80);		// FLD real10
			else if (rm == 7)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fstp_instruction, _f80);		// FSTP real10
			else							do_common_unknown(data, dd, (u8*)"FUNK", 2, (u8*)"FUNK - Floating point unknown instruction");
		}
	}

	void opcode_fpu_dc(u8* data, SDisasmData* dd)
	{
		u8 rm = *(data + 1);
_asm int 3;
		
		if (rm >= 0xc0 && rm <= 0xc7)				do_common_opcode_fpu_stx_hard(data, dd, cgc_fdivr_instruction, 0);		// FADD st(i),st(0)
		else if (rm >= 0xc8 && rm <= 0xcf)			do_common_opcode_fpu_stx_hard(data, dd, cgc_fdivr_instruction, 0);		// FMUL st(i),st(0)
		else if (rm >= 0xe0 && rm <= 0xe7)			do_common_opcode_fpu_stx_hard(data, dd, cgc_fdivr_instruction, 0);		// FSUBR st(i),st(0)
		else if (rm >= 0xe8 && rm <= 0xef)			do_common_opcode_fpu_stx_hard(data, dd, cgc_fdivr_instruction, 0);		// FSUB st(i),st(0)
		else if (rm >= 0xf0 && rm <= 0xf7)			do_common_opcode_fpu_stx_hard(data, dd, cgc_fdivr_instruction, 0);		// FDIVR st(i),st(0)
		else if (rm >= 0xf8 && rm <= 0xff)			do_common_opcode_fpu_stx_hard(data, dd, cgc_fdivr_instruction, 0);		// FDIV st(i),st(0)
		else
		{
			rm = (rm >> 3) & 0x07;
			if (rm == 0)					do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fadd_instruction, _f64);		// FADD real8
			else if (rm == 1)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fmul_instruction, _f64);		// FMUL real8
			else if (rm == 2)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fcom_instruction, _f64);		// FCOM real8
			else if (rm == 3)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fcomp_instruction, _f64);		// FCOMP real8
			else if (rm == 4)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fsub_instruction, _f64);		// FSUB real8
			else if (rm == 5)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fsubr_instruction, _f64);		// FSUBR real8
			else if (rm == 6)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fdiv_instruction, _f64);		// FDIV real8
			else if (rm == 7)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fdivr_instruction, _f64);		// FDIVR real8
		}
	}

	void opcode_fpu_dd(u8* data, SDisasmData* dd)
	{
		u8 rm = *(data + 1);
_asm int 3;
		
		if (rm >= 0xc0 && rm <= 0xc7)				do_common_opcode_fpu_stx(data, dd, cgc_fld_instruction);		// FFREE st(i)
		else if (rm >= 0xd0 && rm <= 0xd7)			do_common_opcode_fpu_stx(data, dd, cgc_fld_instruction);		// FST st(i)
		else if (rm >= 0xd8 && rm <= 0xdf)			do_common_opcode_fpu_stx(data, dd, cgc_fld_instruction);		// FSTP st(i)
		else if (rm >= 0xe0 && rm <= 0xe7)			do_common_opcode_fpu_stx(data, dd, cgc_fld_instruction);		// FUCOM st(i)
		else if (rm >= 0xe8 && rm <= 0xef)			do_common_opcode_fpu_stx(data, dd, cgc_fld_instruction);		// FUCOMP st(i)
		else if (rm == 0xe9)						do_common_mnemonic(dd, cgc_fucomp_instruction, 1, NULL, NULL);	// FUCOMP
		else
		{
			rm = (rm >> 3) & 0x07;
			if (rm == 0)					do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fld_instruction, _f64);		// FLD real8
			else if (rm == 2)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fst_instruction, _f64);		// FST real8
			else if (rm == 3)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fstp_instruction, _f64);		// FSTP real8
			else if (rm == 4)
			{
				// frstor
				if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
					(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
				{
					// 32-bit addressing mode
					do_common_opcode_fpu_rm_one_operand(data, dd, cgc_frstor_instruction, _m108byte);
				}
				else
				{
					// 16-bit addressing mode
					do_common_opcode_fpu_rm_one_operand(data, dd, cgc_frstor_instruction, _m94byte);
				}
			}
			else if (rm == 6)
			{
				// fnsave
				if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
					(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
				{
					// 32-bit addressing mode
					do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fnsave_instruction, _m108byte);
				}
				else
				{
					// 16-bit addressing mode
					do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fnsave_instruction, _m94byte);
				}
			}
			else if (rm == 7)			do_common_mnemonic(dd, cgc_fnstsw_instruction, 1, NULL, NULL);		// FNSTSW
			else						do_common_unknown(data, dd, (u8*)"UNKF", 2, (u8*)"UNKF - Unknown floating point instruction");
		}
	}

	void opcode_fpu_de(u8* data, SDisasmData* dd)
	{
		u8 rm = *(data + 1);
_asm int 3;


		if (rm >= 0xc0 && rm <= 0xc7)				do_common_opcode_fpu_stx_hard(data, dd, cgc_fdivr_instruction, 0);				// FADDP st(i),st(0)
		else if (rm >= 0xc8 && rm <= 0xcf)			do_common_opcode_fpu_stx_hard(data, dd, cgc_fdivr_instruction, 0);				// FMULP st(i),st(0)
		else if (rm == 0xd9)						do_common_opcode_fpu_stx_hard(data, dd, cgc_fdivr_instruction, 0);				// FCOMPP
		else if (rm >= 0xe0 && rm <= 0xe7)			do_common_opcode_fpu_stx_hard(data, dd, cgc_fdivr_instruction, 0);				// FSUBRP st(i),st(0)
		else if (rm >= 0xe8 && rm <= 0xef)			do_common_opcode_fpu_stx_hard(data, dd, cgc_fdivr_instruction, 0);				// FSUBP st(i),st(0)
		else if (rm >= 0xf0 && rm <= 0xf7)			do_common_opcode_fpu_stx_hard(data, dd, cgc_fdivr_instruction, 0);				// FDIVRP st(i),st(0)
		else if (rm >= 0xf8 && rm <= 0xff)			do_common_opcode_fpu_stx_hard(data, dd, cgc_fdivr_instruction, 0);				// FDIVP st(i),st(0)
		else
		{
			rm = (rm >> 3) & 0x07;
			if (rm == 0)							do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fiadd_instruction, _s64);		// FIADD m64_int
			else if (rm == 1)						do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fimul_instruction, _s64);		// FIMUL m16_int
			else if (rm == 2)						do_common_opcode_fpu_rm_one_operand(data, dd, cgc_ficom_instruction, _s16);		// FICOM m16_int
			else if (rm == 3)						do_common_opcode_fpu_rm_one_operand(data, dd, cgc_ficomp_instruction, _s16);	// FICOMP m16_int
			else if (rm == 4)						do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fisub_instruction, _s16);		// FISUB m16_int
			else if (rm == 5)						do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fisubr_instruction, _s16);	// FISUBR m16_int
			else if (rm == 6)						do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fidiv_instruction, _s16);		// FIDIV m16_int
			else if (rm == 7)						do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fidivr_instruction, _s16);	// FIDIVR m16_int
		}
	}

// Undocumented instructions
// FFREEP performs FFREE ST(i) and pop stack
// DF 1101 1111 1100 0REG (6)
// http://www.pagetable.com/?p=16
	void opcode_fpu_df(u8* data, SDisasmData* dd)
	{
		u8 v;
		u8 rm = *(data + 1);
_asm int 3;


		if (rm >= 0xc0 && rm <= 0xc7)
			do_common_opcode_fpu_stx(data, dd, cgc_fld_instruction);		// FFREEP st(i)
		else if (rm == 0xe0)
		{ // FNSTSW ax
			_asm int 3;
			v = _accum_reg;
			do_common_opcode_fpu_rm_one_operand((u8*)&v, dd, cgc_fnstsw_instruction, _16bit);
		}
		else if (rm >= 0xe8 && rm <= 0xef)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fdivr_instruction, 0);		// FUCOMIP st(0),st(i)
		else if (rm >= 0xf0 && rm <= 0xf7)			do_common_opcode_fpu_hard_stx(data, dd, cgc_fdivr_instruction, 0);		// FCOMIP st(0),st(i)
		else
		{
			rm = (rm >> 3) & 0x07;
			if (rm == 0)					do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fild_instruction, _s16);		// FILD m16_int
			else if (rm == 2)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fist_instruction, _s16);		// FIST m16_int
			else if (rm == 3)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fistp_instruction, _s16);		// FISTP m16_int
			else if (rm == 4)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fbld_instruction, _m80);		// fbld m80_bcd
			else if (rm == 5)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fild_instruction, _s64);		// FILD m64_int
			else if (rm == 6)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fbstp_instruction, _m80);		// fbstp m80_bcd
			else if (rm == 7)				do_common_opcode_fpu_rm_one_operand(data, dd, cgc_fistp_instruction, _s64);		// FISTP m64_int
			else							do_common_unknown(data, dd, (u8*)"FUNK", 2, (u8*)"FUNK - Floating point unknown instruction");
		}
	}

	void opcode_fs_override(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= FSREG;
		dd->opcode_bytes	+= 1;
	}

	void opcode_gs_override(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= GSREG;
		dd->opcode_bytes	+= 1;
	}

	void opcode_hlt(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_hlt_instruction, 1, NULL, NULL);
	}

	void opcode_imul_rm8(u8* data, SDisasmData* dd)
	{ // f6
		do_common_opcode_rm8_one_operand(data, dd, cgc_imul_instruction);
	}

	void opcode_imul_rm1632(u8* data, SDisasmData* dd)
	{ // f7
		do_common_opcode_rm16_rm32_one_operand(data, dd, cgc_imul_instruction);
	}

	void opcode_imulaf(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_imul_instruction, 0);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_imul_3_parms_immed16_32(u8* data, SDisasmData* dd)
	{ // 69
		do_common_opcode_rm1632_r1632_cl(dd, cgc_imul_instruction, 0);
		do_common_regrm(data, dd, _16bit | _32bit, false, _null_string);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _16bit | _32bit);
	}

	void opcode_imul_3_parms_immed8(u8* data, SDisasmData* dd)
	{ // 68
		do_common_opcode_rm1632_r1632_cl(dd, cgc_imul_instruction, 0);
		do_common_regrm(data, dd, _16bit | _32bit, false, _null_string);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
	}

	void opcode_in(u8* data, SDisasmData* dd)
	{ // ed
		do_common_mnemonic(dd, cgc_in_instruction, 1, NULL, NULL);
		dd->operand1	= cgc_al_reg;
		extract_gp_reg_operand(dd, _data_reg, &dd->operand2, _16bit | _32bit);
	}

	void opcode_in16_32_immed8(u8* data, SDisasmData* dd)
	{ // e5
		do_common_mnemonic(dd, cgc_in_instruction);
		extract_gp_reg_operand(dd, _accum_reg, &dd->operand2, _16bit | _32bit);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
	}

	void opcode_in8_immed8(u8* data, SDisasmData* dd)
	{ // e4
		do_common_mnemonic(dd, cgc_in_instruction, 1, NULL, NULL);
		dd->operand1	= cgc_al_reg;
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
	}

	void opcode_in_byte(u8* data, SDisasmData* dd)
	{ // ec
		do_common_mnemonic(dd, cgc_in_instruction, 1, NULL, NULL);
		dd->operand1	= cgc_al_reg;
		dd->operand2	= cgc_dx_reg;
	}

	void opcode_inc_xxx(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_inc_instruction, 1, NULL, NULL);
		extract_gp_reg_operand(dd, *data & 0x07, &dd->operand1, _16bit | _32bit);
	}
	void opcode_insb(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_insb_instruction, 1, NULL, NULL);
	}

	void opcode_insw(u8* data, SDisasmData* dd)
	{
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
			do_common_mnemonic(dd, cgc_insd_instruction, 1, NULL, NULL);
		else
			do_common_mnemonic(dd, cgc_insw_instruction, 1, NULL, NULL);
	}

	void opcode_int3(u8* data, SDisasmData* dd)
	{ // cc
		do_common_mnemonic(dd, cgc_int3_instruction, 1, NULL, NULL);
	}

	void opcode_into(u8* data, SDisasmData* dd)
	{ // ce
		do_common_mnemonic(dd,cgc_into_instruction, 1, NULL, NULL);
	}

	void opcode_intx(u8* data, SDisasmData* dd)
	{ // cd 
		sprintf((s8*)&operand1_buffer[0], "0x%x", (int)*(data + 1));
		dd->operand1		= &operand1_buffer[0];
		do_common_mnemonic(dd, cgc_int_instruction, 2, NULL, NULL);
	}

	void opcode_invd(u8* data, SDisasmData* dd)
	{ // 0f 08
		do_common_mnemonic(dd, cgc_invd_instruction, 1, NULL, NULL);
	}

	void opcode_iret(u8* data, SDisasmData* dd)
	{ // cf
		do_common_mnemonic(dd, cgc_iret_instruction, 1, NULL, NULL);
	}
	

	void opcode_ja(u8* data, SDisasmData* dd)
	{ // 70
		opcode_xxx_rel8(data, dd, cgc_ja_instruction);
	}

	void opcode_ja_l(u8* data, SDisasmData* dd)
	{ // 0f 80
		opcode_xxx_rel16(data, dd, cgc_ja_instruction);
	}

	void opcode_jc(u8* data, SDisasmData* dd)
	{ // 72
		opcode_xxx_rel8(data, dd, cgc_jc_instruction);
	}

	void opcode_jc_l(u8* data, SDisasmData* dd)
	{ // 0f 82
		opcode_xxx_rel16(data, dd, cgc_jc_instruction);
	}

	void opcode_jcxz(u8* data, SDisasmData* dd)
	{ // e3
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
			
			opcode_xxx_rel8(data, dd, cgc_jecxz_instruction);		// 32-bit addressing mode
		else
			opcode_xxx_rel8(data, dd, cgc_jcxz_instruction);		// 16-bit addressing mode
	}

	void opcode_jg(u8* data, SDisasmData* dd)
	{ // 7f
		opcode_xxx_rel8(data, dd, cgc_jg_instruction);
	}

	void opcode_jg_l(u8* data, SDisasmData* dd)
	{ // 0f 8f
		opcode_xxx_rel16(data, dd, cgc_jg_instruction);
	}

	void opcode_jl(u8* data, SDisasmData* dd)
	{ // 0f 7c
		opcode_xxx_rel8(data, dd, cgc_jl_instruction);
	}

	void opcode_jl_l(u8* data, SDisasmData* dd)
	{ // 0f 8c
		opcode_xxx_rel16(data, dd, cgc_jl_instruction);
	}

	void opcode_jmp16_32(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32_one_operand(data, dd, cgc_jmp_instruction);
	}

	void opcode_jmp8(u8* data, SDisasmData* dd)
	{
		opcode_xxx_rel8(data, dd, cgc_jmp_instruction);
	}

	void opcode_call_near_relative(u8* data, SDisasmData* dd)
	{
		opcode_jmp_call_near_relative(data, dd, cgc_call_instruction);
	}

	void opcode_call_far_operand(u8* data, SDisasmData* dd)
	{
		opcode_jmp_call_far_operand(data, dd, cgc_call_instruction);
	}

	void opcode_jmp_far(u8* data, SDisasmData* dd)
	{
		opcode_jmp_call_far_operand(data, dd, cgc_jmp_instruction);
	}
	
	void opcode_xxx_rel8(u8* data, SDisasmData* dd, u8* instruction)
	{
		do_common_mnemonic(dd, instruction, 1, NULL, NULL);
		do_immediate(data + 1, dd, _8bit);
	}
	
	void opcode_xxx_rel16(u8* data, SDisasmData* dd, u8* instruction)
	{
		do_common_mnemonic(dd, instruction, 2, NULL, NULL);
		do_immediate(data + 2, dd, _16bit);
	}

	void opcode_jna(u8* data, SDisasmData* dd)
	{ // 76
		opcode_xxx_rel8(data, dd, cgc_jna_instruction);
	}

	void opcode_jna_l(u8* data, SDisasmData* dd)
	{ // 0f 86
		opcode_xxx_rel16(data, dd, cgc_jna_instruction);
	}

	void opcode_jnc(u8* data, SDisasmData* dd)
	{ // 73
		opcode_xxx_rel8(data, dd, cgc_jnc_instruction);
	}

	void opcode_jnc_l(u8* data, SDisasmData* dd)
	{ // 0f 83
		opcode_xxx_rel16(data, dd, cgc_jnc_instruction);
	}

	void opcode_jng(u8* data, SDisasmData* dd)
	{ // 7e
		opcode_xxx_rel8(data, dd, cgc_jng_instruction);
	}

	void opcode_jng_l(u8* data, SDisasmData* dd)
	{ // 0f 8e
		opcode_xxx_rel16(data, dd, cgc_jng_instruction);
	}

	void opcode_jnl(u8* data, SDisasmData* dd)
	{ // 7d
		opcode_xxx_rel8(data, dd, cgc_jnl_instruction);
	}

	void opcode_jnl_l(u8* data, SDisasmData* dd)
	{ // 0f 8d
		opcode_xxx_rel16(data, dd, cgc_jnl_instruction);
	}

	void opcode_jno(u8* data, SDisasmData* dd)
	{ // 7a
		opcode_xxx_rel8(data, dd, cgc_jno_instruction);
	}

	void opcode_jno_l(u8* data, SDisasmData* dd)
	{ // 81
		opcode_xxx_rel16(data, dd, cgc_jno_instruction);
	}

	void opcode_jns(u8* data, SDisasmData* dd)
	{ // 79
		opcode_xxx_rel8(data, dd, cgc_jns_instruction);
	}

	void opcode_jns_l(u8* data, SDisasmData* dd)
	{ // 0f 89
		opcode_xxx_rel16(data, dd, cgc_jns_instruction);
	}

	void opcode_jnz(u8* data, SDisasmData* dd)
	{ // 75
		opcode_xxx_rel8(data, dd, cgc_jnz_instruction);
	}

	void opcode_jnz_l(u8* data, SDisasmData* dd)
	{ // 0f 85
		opcode_xxx_rel16(data, dd, cgc_jnz_instruction);
	}

	void opcode_jo(u8* data, SDisasmData* dd)
	{ // 70
		opcode_xxx_rel8(data, dd, cgc_jo_instruction);
	}

	void opcode_jo_l(u8* data, SDisasmData* dd)
	{ // 0f 80
		opcode_xxx_rel16(data, dd, cgc_jo_instruction);
	}

	void opcode_jpe(u8* data, SDisasmData* dd)
	{ // 7a
		opcode_xxx_rel8(data, dd, cgc_jpe_instruction);
	}

	void opcode_jpe_l(u8* data, SDisasmData* dd)
	{ // 0f 8a
		opcode_xxx_rel16(data, dd, cgc_jpe_instruction);
	}

	void opcode_jpo(u8* data, SDisasmData* dd)
	{ // 7b
		opcode_xxx_rel8(data, dd, cgc_jpo_instruction);
	}

	void opcode_jpo_l(u8* data, SDisasmData* dd)
	{ // 0f 8b
		opcode_xxx_rel16(data, dd, cgc_jpo_instruction);
	}

	void opcode_js(u8* data, SDisasmData* dd)
	{ // 78
		opcode_xxx_rel8(data, dd, cgc_js_instruction);
	}

	void opcode_js_l(u8* data, SDisasmData* dd)
	{ // 0f 78
		opcode_xxx_rel16(data, dd, cgc_js_instruction);
	}

	void opcode_jz(u8* data, SDisasmData* dd)
	{ // 74
		opcode_xxx_rel8(data, dd, cgc_jz_instruction);
	}

	void opcode_jz_l(u8* data, SDisasmData* dd)
	{ // 0f 84
		opcode_xxx_rel16(data, dd, cgc_jz_instruction);
	}

	void opcode_lahf(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_lahf_instruction, 1, NULL, NULL);
	}

	void opcode_lar(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm1632(dd, cgc_lar_instruction, 1);
	}

	void opcode_lds(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm1632_m16_1632(data, dd, cgc_lds_instruction, 1);
	}

	void opcode_lea(u8* data, SDisasmData* dd)
	{ // 8d
		do_common_opcode_rm16_rm32_reversed(dd, cgc_lea_instruction, 1);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_leave(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_leave_instruction, 1, NULL, NULL);
	}

	void opcode_les(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm1632_m16_1632(data, dd, cgc_les_instruction, 1);
	}

	void opcode_lfs(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm1632_m16_1632(data, dd, cgc_lfs_instruction, 1);
	}

	void opcode_lgs(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm1632_m16_1632(data, dd, cgc_lgs_instruction, 1);
	}
	
	void opcode_icebp(u8* data, SDisasmData* dd)
	{ // f1
		do_common_mnemonic(dd, cgc_icebp_instruction, 1, NULL, NULL);
		dd->line_comment = (u8*)"; Undocumented instruction";
	}

	void opcode_lock_prefix(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= LOCK;
		dd->opcode_bytes	+= 1;
	}

	void opcode_lodsb(u8* data, SDisasmData* dd)
	{
		if (dd->prefixes & REPE)
		{
			dd->mnemonic	= (u8*)"repe";
			dd->operand1	= (u8*)"lodsb";
		}
		else if (dd->prefixes & REPNE)
		{
			dd->mnemonic	= (u8*)"repne";
			dd->operand1	= (u8*)"lodsb";
		}
		else
		{
			dd->mnemonic	= (u8*)"lodsb";
		}
		dd->opcode_bytes	+= 1;
	}

	void opcode_lodsw(u8* data, SDisasmData* dd)
	{
		do_common_two_prefixes_mnemonic_operand_size_check(dd, 1, 
															REPE,	cgc_repe_instruction,
															REPNE,	cgc_repne_instruction,
															cgc_lodsw_instruction,
															cgc_lodsd_instruction);
	}

	void opcode_loop(u8* data, SDisasmData* dd)
	{ // e2
		opcode_xxx_rel8(data, dd, cgc_loop_instruction);
	}

	void opcode_loope(u8* data, SDisasmData* dd)
	{ // e1
		opcode_xxx_rel8(data, dd, cgc_loope_instruction);
	}

	void opcode_loopne(u8* data, SDisasmData* dd)
	{ // e0
		opcode_xxx_rel8(data, dd, cgc_loopne_instruction);
	}

	void opcode_lsl(u8* data, SDisasmData* dd)
	{ // 0f 03
		do_common_opcode_rm16_rm32_reversed(dd, cgc_lsl_instruction, 1);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_lss(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm1632_m16_1632(data, dd, cgc_lss_instruction, 1);
	}

	void opcode_mov_accum_mem_16_32(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed16_32(data, dd, cgc_mov_instruction, 1);
	}

	void opcode_mov_accum_mem_8(u8* data, SDisasmData* dd)
	{
		do_common_opcode_r1632_rm8(dd, cgc_mov_instruction, 1);
	}

	void opcode_mov_gp_control(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _gp_reg, _control_reg);
	}

	void opcode_mov_gp_debug(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _gp_reg, _debug_reg);
	}

	void opcode_mov_gp_test(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _gp_reg, _test_reg);
	}

	void opcode_mov_control_gp(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _control_reg, _gp_reg);
	}

	void opcode_mov_debug_gp(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _debug_reg, _gp_reg);
	}

	void opcode_mov_test_gp(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _test_reg, _gp_reg);
	}

	void opcode_mov_mem_accum_16_32(u8* data, SDisasmData* dd)
	{
		_asm int 3;
	}

	void opcode_mov_mem_accum_8(u8* data, SDisasmData* dd)
	{
		_asm int 3;
	}

	void opcode_mov_reg16_32_sreg(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _gp_reg, _segment_reg);
	}

	void opcode_mov_reg_immed16_32(u8* data, SDisasmData* dd)
	{
		_asm int 3;
	}

	void opcode_mov_reg_immed8(u8* data, SDisasmData* dd)
	{
		_asm int 3;
	}

	void opcode_mov_reg_rm_16_32(u8* data, SDisasmData* dd)
	{
		_asm int 3;
	}

	void opcode_mov_reg_rm_8(u8* data, SDisasmData* dd)
	{
		_asm int 3;
	}

	void opcode_mov_rm_reg_16_32(u8* data, SDisasmData* dd)
	{
		_asm int 3;
	}

	void opcode_mov_rm_reg_8(u8* data, SDisasmData* dd)
	{
		_asm int 3;
	}

	void opcode_mov_sreg_reg16_32(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _segment_reg, _gp_reg);
	}

	void opcode_movd_gp_mmx(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _gp_reg, _mmx_reg);
	}

	void opcode_movd_mmx_gp(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mov(data, dd, _mmx_reg, _gp_reg);
	}

	void opcode_movq_mm_mmx_mmx(u8* data, SDisasmData* dd)
	{
		_asm int 3;
	}

	void opcode_movq_mmx_mm_mmx(u8* data, SDisasmData* dd)
	{
		_asm int 3;
	}

	void opcode_movsb(u8* data, SDisasmData* dd)
	{
		if (dd->prefixes & REPE)
		{
			dd->mnemonic	= (u8*)"repe";
			dd->operand1	= (u8*)"movsb";
		}
		else if (dd->prefixes & REPNE)
		{
			dd->mnemonic	= (u8*)"repne";
			dd->operand1	= (u8*)"movsb";
		}
		else
		{
			dd->mnemonic	= (u8*)"movsb";
		}
		dd->opcode_bytes	+= 1;
	}

	void opcode_movsw(u8* data, SDisasmData* dd)
	{
		do_common_two_prefixes_mnemonic_operand_size_check(dd, 1, 
															REPE,	cgc_repe_instruction,
															REPNE,	cgc_repne_instruction,
															cgc_movsw_instruction,
															cgc_movsd_instruction);
	}

	void opcode_movsx_byte(u8* data, SDisasmData* dd)
	{ // 0f be
		do_common_opcode_r1632_rm8(dd, cgc_movsx_instruction, 1);
		do_common_regrm(data, dd, _16bit | _32bit, false, _null_string);
		do_common_adjust_register_size(dd->operand2, _8bit);
	}

	void opcode_movsx_word(u8* data, SDisasmData* dd)
	{ // 0f bf
		do_common_opcode_r1632_rm8(dd, cgc_movsx_instruction, 1);
		do_common_regrm(data, dd, _32bit, false, _null_string);
		do_common_adjust_register_size(dd->operand2, _16bit);
	}

	void opcode_movzx_byte(u8* data, SDisasmData* dd)
	{ // 0f b6
		do_common_opcode_r1632_rm8(dd, cgc_movzx_instruction, 1);
		do_common_regrm(data, dd, _16bit | _32bit, false, _null_string);
		do_common_adjust_register_size(dd->operand2, _8bit);
	}

	void opcode_movzx_word(u8* data, SDisasmData* dd)
	{ // 0f b7
		do_common_opcode_r1632_rm8(dd, cgc_movzx_instruction, 1);
		do_common_regrm(data, dd, _32bit, false, _null_string);
		do_common_adjust_register_size(dd->operand2, _16bit);
	}

	void opcode_nop(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_nop_instruction, 1, NULL, NULL);
	}

	void opcode_op_size_override(u8* data, SDisasmData* dd)
	{
		dd->overrides		|= Operand;
		dd->opcode_bytes	+= 1;
	}

	void opcode_or_accum0c(u8* data, SDisasmData* dd)
	{ // 0c
		do_common_accum8_immed8(data, dd, cgc_or_instruction, 1);
	}

	void opcode_or_accum0d(u8* data, SDisasmData* dd)
	{ // 0d
		do_common_accum16_32_immed16_32(data, dd, cgc_or_instruction, 1);
	}

	void opcode_or_rm08(u8* data, SDisasmData* dd)
	{ // 08
		do_common_opcode_rm8(dd, cgc_or_instruction, 1);
		do_common_regrm(data, dd, _8bit, false, _null_string);
	}

	void opcode_or_rm09(u8* data, SDisasmData* dd)
	{ // 09
		do_common_opcode_rm16_rm32(dd, cgc_or_instruction, 1);
		do_common_regrm(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_or_rm0a(u8* data, SDisasmData* dd)
	{ // 0a
		do_common_opcode_rm8_reversed(dd, cgc_or_instruction, 1);
		do_common_regrm(data, dd, _8bit, false, _null_string);
	}

	void opcode_or_rm0b(u8* data, SDisasmData* dd)
	{ // 0b
		do_common_opcode_rm16_rm32_reversed(dd, cgc_or_instruction, 1);
		do_common_regrm_reversed(data, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_or_rm8_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm8_immed8(data, dd, cgc_or_instruction, 1);
	}

	void opcode_or_rm16_32_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed16_32(data, dd, cgc_or_instruction, 1);
	}

	void opcode_or_rm16_32_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed8(data, dd, cgc_or_instruction, 1);
	}

	void opcode_oute7(u8* data, SDisasmData* dd)
	{ // e7
		do_common_mnemonic(dd, cgc_in_instruction, 1, NULL, NULL);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _16bit | _32bit);
		dd->operand1	= dd->immediate;
		dd->immediate	= NULL;
		extract_gp_reg_operand(dd, _accum_reg, &dd->operand2, _16bit | _32bit);
	}

	void opcode_oute6(u8* data, SDisasmData* dd)
	{ // e6
		do_common_mnemonic(dd, cgc_in_instruction, 1, NULL, NULL);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
		dd->operand1	= dd->immediate;
		dd->immediate	= NULL;
		extract_gp_reg_operand(dd, _accum_reg, &dd->operand2, _8bit);
	}

	void opcode_outee(u8* data, SDisasmData* dd)
	{ // ee
		do_common_mnemonic(dd, cgc_in_instruction, 1, NULL, NULL);
		dd->operand1	= cgc_dx_reg;
		extract_gp_reg_operand(dd, _accum_reg, &dd->operand2, _8bit);
	}

	void opcode_outef(u8* data, SDisasmData* dd)
	{ // ef
		do_common_mnemonic(dd, cgc_in_instruction, 1, NULL, NULL);
		dd->operand1	= cgc_dx_reg;
		extract_gp_reg_operand(dd, _accum_reg, &dd->operand2, _16bit | _32bit);
	}

	void opcode_outsb(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_outsb_instruction, 1, NULL, NULL);
	}

	void opcode_outsw(u8* data, SDisasmData* dd)
	{
		do_common_operand_size_check_mnemonic(dd, 1, cgc_outsw_instruction, cgc_outsd_instruction);
	}

	void opcode_packssdw(u8* data, SDisasmData* dd)
	{ // 0f 63
		do_common_opcode_mmx_xmmx(data, dd, cgc_packssdw_instruction, (u8*)"PACKSSDW - Pack dwords into with words with signed saturation");
	}

	void opcode_packsswb(u8* data, SDisasmData* dd)
	{ // 0f 6b
		do_common_opcode_mmx_xmmx(data, dd, cgc_packsswb_instruction, (u8*)"PACKSSWB - Pack words into with bytes with signed saturation");
	}

	void opcode_packuswb(u8* data, SDisasmData* dd)
	{ // 0f 67
		do_common_opcode_mmx_xmmx(data, dd, cgc_packuswb_instruction, (u8*)"PACKUSWB - Pack words into with bytes with unsigned saturation");
	}

	void opcode_paddb(u8* data, SDisasmData* dd)
	{ // 0f fc
		do_common_opcode_mmx_xmmx(data, dd, cgc_paddb_instruction, (u8*)"PADDB - Packed add bytes");
	}

	void opcode_paddd(u8* data, SDisasmData* dd)
	{ // 0f fe
		do_common_opcode_mmx_xmmx(data, dd, cgc_paddd_instruction, (u8*)"PADDD - Packed add dwords");
	}

	void opcode_paddsb(u8* data, SDisasmData* dd)
	{ // 0f ec
		do_common_opcode_mmx_xmmx(data, dd, cgc_paddsb_instruction, (u8*)"PADDSB - Packed add signed integer bytes");
	}

	void opcode_paddsw(u8* data, SDisasmData* dd)
	{ // 0f ed
		do_common_opcode_mmx_xmmx(data, dd, cgc_paddsb_instruction, (u8*)"PADDSW - Packed add signed integer words");
	}

	void opcode_paddusb(u8* data, SDisasmData* dd)
	{ // 0f dc
		do_common_opcode_mmx_xmmx(data, dd, cgc_paddusb_instruction, (u8*)"PADDUSB - Packed add unsigned integer bytes");
	}

	void opcode_paddusw(u8* data, SDisasmData* dd)
	{ // 0f dd
		do_common_opcode_mmx_xmmx(data, dd, cgc_paddusw_instruction, (u8*)"PADDUSW - Packed add unsigned integer words");
	}

	void opcode_paddw(u8* data, SDisasmData* dd)
	{ // 0f fd
		do_common_opcode_mmx_xmmx(data, dd, cgc_paddw_instruction, (u8*)"PADDW - Packed add words");
	}

	void opcode_pand(u8* data, SDisasmData* dd)
	{ // 0f db
		do_common_opcode_mmx_xmmx(data, dd, cgc_pand_instruction, (u8*)"PAND - Packed logical AND");
	}

	void opcode_pandn(u8* data, SDisasmData* dd)
	{ // 0f df
		do_common_opcode_mmx_xmmx(data, dd, cgc_pandn_instruction, (u8*)"PANDN - Packed logical NOT on first operand, then AND");
	}

	void opcode_pcmpeqb(u8* data, SDisasmData* dd)
	{ // 0f 74
		do_common_opcode_mmx_xmmx(data, dd, cgc_pcmpeqb_instruction, (u8*)"PCMPEQB - Packed compare equality bytes");
	}

	void opcode_pcmpeqd(u8* data, SDisasmData* dd)
	{ // 0f 76
		do_common_opcode_mmx_xmmx(data, dd, cgc_pcmpeqd_instruction, (u8*)"PCMPEQD - Packed compare equality dwords");
	}

	void opcode_pcmpeqw(u8* data, SDisasmData* dd)
	{ // 0f 75
		do_common_opcode_mmx_xmmx(data, dd, cgc_pcmpeqw_instruction, (u8*)"PCMPEQW - Packed compare equality words");
	}

	void opcode_pcmpgtb(u8* data, SDisasmData* dd)
	{ // 0f 64
		do_common_opcode_mmx_xmmx(data, dd, cgc_pcmpgtb_instruction, (u8*)"PCMPGTB - Packed compare greater than signed bytes");
	}

	void opcode_pcmpgtd(u8* data, SDisasmData* dd)
	{ // 0f 66
		do_common_opcode_mmx_xmmx(data, dd, cgc_pcmpgtd_instruction, (u8*)"PCMPGTD - Packed compare greater than signed dwords");
	}

	void opcode_pcmpgtw(u8* data, SDisasmData* dd)
	{ // 0f 65
		do_common_opcode_mmx_xmmx(data, dd, cgc_pcmpgtw_instruction, (u8*)"PCMPGTW - Packed compare greater than signed words");
	}

	void opcode_pmaddwd(u8* data, SDisasmData* dd)
	{ // 0f f5
		do_common_opcode_mmx_xmmx(data, dd, cgc_pmaddwd_instruction, (u8*)"PMADDWD - Packed multiply-add signed words");
	}

	void opcode_pmulhw(u8* data, SDisasmData* dd)
	{ // 0f e5
		do_common_opcode_mmx_xmmx(data, dd, cgc_pmulhw_instruction, (u8*)"PMULHW - Packed multiply signed word integers, store high result");
	}

	void opcode_pmullw(u8* data, SDisasmData* dd)
	{ // 0f d5
		do_common_opcode_mmx_xmmx(data, dd, cgc_pmullw_instruction, (u8*)"PMULLW - Packed multiply signed word integers, store low result");
	}

	void opcode_pop_ds(u8* data, SDisasmData* dd)
	{
		dd->operand1		= cgc_ds_reg;
		do_common_mnemonic(dd, cgc_pop_instruction, 1, NULL, NULL);
	}

	void opcode_pop_es(u8* data, SDisasmData* dd)
	{
		dd->operand1		= cgc_es_reg;
		do_common_mnemonic(dd, cgc_pop_instruction, 1, NULL, NULL);
	}

	void opcode_pop_fs(u8* data, SDisasmData* dd)
	{
		dd->operand1		= cgc_fs_reg;
		do_common_mnemonic(dd, cgc_pop_instruction, 1, NULL, NULL);
	}

	void opcode_pop_gs(u8* data, SDisasmData* dd)
	{
		dd->operand1		= cgc_gs_reg;
		do_common_mnemonic(dd, cgc_pop_instruction, 1, NULL, NULL);
	}

	void opcode_pop_ss(u8* data, SDisasmData* dd)
	{
		dd->operand1		= cgc_ss_reg;
		do_common_mnemonic(dd, cgc_pop_instruction, 1, NULL, NULL);
	}

	void opcode_pop_xreg(u8* data, SDisasmData* dd)
	{
		extract_gp_reg_operand(dd, *data & 0x07, &dd->operand1, _16bit | _32bit);
		do_common_mnemonic(dd, cgc_pop_instruction, 1, NULL, NULL);
	}

	void opcode_popa(u8* data, SDisasmData* dd)
	{
		do_common_operand_size_check_mnemonic(dd, 1, cgc_popa_instruction, cgc_popad_instruction);
	}

	void opcode_popf(u8* data, SDisasmData* dd)
	{
		do_common_operand_size_check_mnemonic(dd, 1, cgc_popf_instruction, cgc_popfd_instruction);
	}

	void opcode_por(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_por_instruction, (u8*)"POR - Packed logical OR");
	}

	void opcode_pslld(u8* data, SDisasmData* dd)
	{ // 0f f2
		do_common_opcode_mmx_xmmx(data, dd, cgc_pslld_instruction, (u8*)"PSLLD - Packed shift left logical dwords");
	}

	void opcode_psllq(u8* data, SDisasmData* dd)
	{ // 0f f3
		do_common_opcode_mmx_xmmx(data, dd, cgc_psllq_instruction, (u8*)"PSLLQ - Packed shift left logical qwords");
	}

	void opcode_psllw(u8* data, SDisasmData* dd)
	{ // 0f f1
		do_common_opcode_mmx_xmmx(data, dd, cgc_psllw_instruction, (u8*)"PSLLW - Packed shift left logical words");
	}

	u8 _psrad_comment[] = "PSRAD - Shift Packed Data Right Arithmetic Dword";
	void opcode_psrad_immed8(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx_immed8(data, dd, cgc_psrad_instruction, _psrad_comment);
	}

	void opcode_psrad(u8* data, SDisasmData* dd)
	{ // 0f e2
		do_common_opcode_mmx_xmmx(data, dd, cgc_psrad_instruction, _psrad_comment);
	}

	u8 _psraw_comment[] = "PSRAW - Shift Packed Data Right Arithmetic Word";
	void opcode_psraw_immed8(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx_immed8(data, dd, cgc_psraw_instruction, _psraw_comment);
	}

	void opcode_psraw(u8* data, SDisasmData* dd)
	{ // 0f e1
		do_common_opcode_mmx_xmmx(data, dd, cgc_psraw_instruction, _psraw_comment);
	}

	u8 _psrld_comment[] = "PSLRD - Shift Packed Data Right Logical Dword";
	void opcode_psrld_immed8(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx_immed8(data, dd, cgc_psrld_instruction, _psrld_comment);
	}

	void opcode_psrld(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_psrld_instruction, _psrld_comment);
	}

	u8 _psrlq_comment[] = "PSLRQ - Shift Packed Data Right Logical Qword";
	void opcode_psrlq_immed8(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx_immed8(data, dd, cgc_psrlq_instruction, _psrlq_comment);
	}

	void opcode_psrlq(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_psrlq_instruction, _psrlq_comment);
	}

	u8 _psrlw_comment[] = "PSLRQ - Shift Packed Data Right Logical Word";
	void opcode_psrlw_immed8(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx_immed8(data, dd, cgc_psrlw_instruction, _psrlw_comment);
	}

	void opcode_psrlw(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_psrlw_instruction, _psrlw_comment);
	}

	void opcode_psubb(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_psubb_instruction, (u8*)"PSUBB - Subtract packed bytes");
	}

	void opcode_psubd(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_psubd_instruction, (u8*)"PSUBD - Subtract packed dwords");
	}

	void opcode_psubsb(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_psubsb_instruction, (u8*)"PSUBSB - Subtract packed signed bytes with signed saturation");
	}

	void opcode_psubsw(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_psubsw_instruction, (u8*)"PSUBSW - Subtract packed signed words with signed saturation");
	}

	void opcode_psubusb(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_psubusb_instruction, (u8*)"PSUBUSB - Subtract packed unsigned bytes with unsigned saturation");
	}

	void opcode_psubusw(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_psubusw_instruction, (u8*)"PSUBUSW - Subtract packed unsigned words with unsigned saturation");
	}

	void opcode_psubw(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_psubw_instruction, (u8*)"PSUBW - Subtract packed words");
	}

	void opcode_punpckhbw(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_punpckhbw_instruction, (u8*)"PUNPCKHBW- Unpack high data, bytes to words");
	}

	void opcode_punpckhdq(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_punpckhdq_instruction, (u8*)"PUNPCKHDQ - Unpack high data, dwords to qwords");
	}

	void opcode_punpckhwd(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_punpckhwd_instruction, (u8*)"PUNPCKHWD - Unpack high data, words to dwords");
	}

	void opcode_punpcklbw(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_punpcklbw_instruction, (u8*)"PUNPCKLBW- Unpack low data, bytes to words");
	}

	void opcode_punpckldq(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_punpckldq_instruction, (u8*)"PUNPCKLDQ- Unpack low data, dwords to qwords");
	}

	void opcode_punpcklwd(u8* data, SDisasmData* dd)
	{
		do_common_opcode_mmx_xmmx(data, dd, cgc_punpcklwd_instruction, (u8*)"PUNPCKLWD- Unpack low data, words to dwords");
	}

	void opcode_push_cs(u8* data, SDisasmData* dd)
	{
		dd->operand1		= cgc_cs_reg;
		do_common_mnemonic(dd, cgc_push_instruction, 1, NULL, NULL);
	}

	void opcode_push_ds(u8* data, SDisasmData* dd)
	{
		dd->operand1		= cgc_ds_reg;
		do_common_mnemonic(dd, cgc_push_instruction, 1, NULL, NULL);
	}

	void opcode_push_es(u8* data, SDisasmData* dd)
	{
		dd->operand1		= cgc_es_reg;
		do_common_mnemonic(dd, cgc_push_instruction, 1, NULL, NULL);
	}

	void opcode_push_fs(u8* data, SDisasmData* dd)
	{
		dd->operand1		= cgc_fs_reg;
		do_common_mnemonic(dd, cgc_push_instruction, 1, NULL, NULL);
	}

	void opcode_push_gs(u8* data, SDisasmData* dd)
	{
		dd->operand1		= cgc_gs_reg;
		do_common_mnemonic(dd, cgc_push_instruction, 1, NULL, NULL);
	}

	void opcode_push_immed16_32(u8* data, SDisasmData* dd)
	{ // 68
		u16 v1;
		u32 v2;
		
		do_common_mnemonic(dd, cgc_push_instruction, 1, NULL, NULL);
		
		if ((_cpu_mode == _32bit_mode && (dd->overrides & (u32)Operand) == 0) ||
			(_cpu_mode == _16bit_mode && (dd->overrides & (u32)Operand) != 0))
		{
			// 32-bit addressing mode
			v2 = *(u32*)(data + 1);
			sprintf((s8*)&line_comment_buffer[0], "; dword 0x%04x (%u)", (int)v2, (int)v2);
			do_immediate(data + 1, dd, _32bit);
		}
		else
		{
			// 16-bit addressing mode
			v1 = *(u16*)(data + 1);
			v2 = sign_extend_16bits_to_32bits(v1);
			sprintf((s8*)&line_comment_buffer[0], "; word 0x%04x (%u) pushed as dword 0x%08x (%u)", (int)v1, (int)v1, (int)v2, (int)v2);
			do_immediate(data + 1, dd, _16bit);
		}
		dd->line_comment = &line_comment_buffer[0];
	}

	void opcode_push_immed8(u8* data, SDisasmData* dd)
	{ // 6a
		u8 v1;
		u32 v2;
		
		do_common_mnemonic(dd, cgc_push_instruction, 1, NULL, NULL);
		
		v1 = *(data + 1);
		v2 = sign_extend_8bit_to_32bits(v1);
		sprintf((s8*)&line_comment_buffer[0], "; byte 0x%02x (%u) pushed as dword %08x (%u)", (int)v1, (int)v1, (int)v2, (int)v2);
		dd->line_comment = &line_comment_buffer[0];
		
		do_immediate(data + 1, dd, _8bit);
	}

	void opcode_push_ss(u8* data, SDisasmData* dd)
	{
		dd->operand1		= cgc_ss_reg;
		do_common_mnemonic(dd, cgc_push_instruction, 1, NULL, NULL);
	}

	void opcode_push_xreg(u8* data, SDisasmData* dd)
	{
		extract_gp_reg_operand(dd, *data & 0x07, &dd->operand1, _16bit | _32bit);
		do_common_mnemonic(dd, cgc_push_instruction, 1, NULL, NULL);
	}

	void opcode_pusha(u8* data, SDisasmData* dd)
	{
		do_common_operand_size_check_mnemonic(dd, 1, cgc_pusha_instruction, cgc_pushad_instruction);
	}

	void opcode_pushf(u8* data, SDisasmData* dd)
	{
		do_common_operand_size_check_mnemonic(dd, 1, cgc_pushf_instruction, cgc_pushfd_instruction);
	}

	void opcode_pxor(u8* data, SDisasmData* dd)
	{ // 0f ef
		do_common_opcode_mmx_xmmx(data, dd, cgc_pxor_instruction, (u8*)"PXOR - Packed logical exclusive OR");
	}

	void opcode_rdmsr(u8* data, SDisasmData* dd)
	{ // 
		do_common_mnemonic(dd, cgc_rdmsr_instruction, 1, NULL, NULL);
	}

	void opcode_rdpmc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_rdpmc_instruction, 1, NULL, NULL);
	}

	void opcode_rdtsc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_rdtsc_instruction, 1, NULL, NULL);
	}

	void opcode_repe_prefix(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= REPE;
		dd->opcode_bytes	+= 1;
	}

	void opcode_repne_prefix(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= REPNE;
		dd->opcode_bytes	+= 1;
	}

	void opcode_retf(u8* data, SDisasmData* dd)
	{ // cb
		do_common_mnemonic(dd, cgc_retf_instruction, 1, NULL, NULL);
	}

	void opcode_retf_immed(u8* data, SDisasmData* dd)
	{ // ca iw
		do_common_mnemonic(dd, cgc_retf_instruction, 1, NULL, NULL);
		do_immediate(data + 1, dd, _16bit);
	}

	void opcode_retn(u8* data, SDisasmData* dd)
	{ // c3
		do_common_mnemonic(dd, cgc_retn_instruction, 1, NULL, NULL);
	}

	void opcode_retn_immed(u8* data, SDisasmData* dd)
	{ // c2 iw
		do_common_mnemonic(dd, cgc_retn_instruction, 1, NULL, NULL);
		do_immediate(data + 1, dd, _16bit);
	}

	void opcode_rsm(u8* data, SDisasmData* dd)
	{ // 0f aa
		do_common_mnemonic(dd, cgc_rsm_instruction, 2, NULL, NULL);
	}

	void opcode_sahf(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_sahf_instruction, 1, NULL, NULL);
	}

	void opcode_sbb_accum_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed16_32(data, dd, cgc_sbb_instruction, 1);
	}

	void opcode_sbb_accum_immed8(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed8(data, dd, cgc_sbb_instruction, 1);
	}

	void opcode_sbb18(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8(dd, cgc_sbb_instruction, 1);
		do_common_regrm(data + 1, dd, _8bit, false, _null_string);
	}

	void opcode_sbb19(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, cgc_sbb_instruction, 1);
		do_common_regrm(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_sbb1a(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8_reversed(dd, cgc_sbb_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _8bit, false, _null_string);
	}

	void opcode_sbb1b(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, cgc_sbb_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_sbb_rm8_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm8_immed8(data, dd, cgc_sbb_instruction, 1);
	}

	void opcode_sbb_rm16_32_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed16_32(data, dd, cgc_sbb_instruction, 1);
	}

	void opcode_sbb_rm16_32_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed8(data, dd, cgc_sbb_instruction, 1);
	}

	void opcode_scasb(u8* data, SDisasmData* dd)
	{
		if (dd->prefixes & REPE)
		{
			dd->mnemonic	= (u8*)"repe";
			dd->operand1	= (u8*)"scasb";
		}
		else if (dd->prefixes & REPNE)
		{
			dd->mnemonic	= (u8*)"repne";
			dd->operand1	= (u8*)"scasb";
		}
		else
		{
			dd->mnemonic	= (u8*)"scasb";
		}
		dd->opcode_bytes	+= 1;
	}

	void opcode_scasw(u8* data, SDisasmData* dd)
	{
		do_common_two_prefixes_mnemonic_operand_size_check(dd, 1, 
															REPE,	cgc_repe_instruction,
															REPNE,	cgc_repne_instruction,
															cgc_scasw_instruction,
															cgc_scasd_instruction);
	}

	void opcode_seta(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_seta_instruction, 1, NULL, NULL);
	}

	void opcode_setc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_setc_instruction, 1, NULL, NULL);
	}

	void opcode_setg(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_setg_instruction, 1, NULL, NULL);
	}

	void opcode_setl(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_setl_instruction, 1, NULL, NULL);
	}

	void opcode_setna(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_setna_instruction, 1, NULL, NULL);
	}

	void opcode_setnc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_setnc_instruction, 1, NULL, NULL);
	}

	void opcode_setng(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_setng_instruction, 1, NULL, NULL);
	}

	void opcode_setnl(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_setnl_instruction, 1, NULL, NULL);
	}

	void opcode_setno(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_setno_instruction, 1, NULL, NULL);
	}

	void opcode_setns(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_setns_instruction, 1, NULL, NULL);
	}

	void opcode_setnz(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_setnz_instruction, 1, NULL, NULL);
	}

	void opcode_seto(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_seto_instruction, 1, NULL, NULL);
	}

	void opcode_setpe(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_setpe_instruction, 1, NULL, NULL);
	}

	void opcode_setpo(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_setpo_instruction, 1, NULL, NULL);
	}

	void opcode_sets(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_sets_instruction, 1, NULL, NULL);
	}

	void opcode_setz(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_setz_instruction, 1, NULL, NULL);
	}

	void opcode_shld_cl(u8* data, SDisasmData* dd)
	{ // 0f a5
		do_common_opcode_rm1632_r1632_cl(dd, cgc_shld_instruction, 0);
		do_common_regrm(data, dd, _16bit | _32bit, false, _null_string);
		extract_gp_reg_operand(dd, (int)_count_low_reg, &dd->operand3, _8bit);
	}

	void opcode_shld_immed(u8* data, SDisasmData* dd)
	{ // 0f a4
		do_common_opcode_rm1632_r1632_cl(dd, cgc_shld_instruction, 0);
		do_common_regrm(data, dd, _16bit | _32bit, false, _null_string);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
	}

	void opcode_shrd_cl(u8* data, SDisasmData* dd)
	{ // 0f ad
		do_common_opcode_rm1632_r1632_cl(dd, cgc_shrd_instruction, 0);
		do_common_regrm(data, dd, _16bit | _32bit, false, _null_string);
		extract_gp_reg_operand(dd, (int)_count_low_reg, &dd->operand3, _8bit);
	}

	void opcode_shrd_immed(u8* data, SDisasmData* dd)
	{ // 0f ac
		do_common_opcode_rm1632_r1632_cl(dd, cgc_shrd_instruction, 0);
		do_common_regrm(data, dd, _16bit | _32bit, false, _null_string);
		do_immediate(dd->data_root + dd->opcode_bytes, dd, _8bit);
	}

	void opcode_ss_override(u8* data, SDisasmData* dd)
	{
		dd->prefixes		|= SSREG;
		dd->opcode_bytes	+= 1;
	}

	void opcode_stc(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_stc_instruction, 1, NULL, NULL);
	}

	void opcode_std(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_std_instruction, 1, NULL, NULL);
	}

	void opcode_sti(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_sti_instruction, 1, NULL, NULL);
	}

	void opcode_stosb(u8* data, SDisasmData* dd)
	{
		if (dd->prefixes & REPE)
		{
			dd->mnemonic	= (u8*)"repe";
			dd->operand1	= (u8*)"stosb";
		}
		else if (dd->prefixes & REPNE)
		{
			dd->mnemonic	= (u8*)"repne";
			dd->operand1	= (u8*)"stosb";
		}
		else
		{
			dd->mnemonic	= (u8*)"stosb";
		}
		dd->opcode_bytes	+= 1;
	}

	void opcode_stosw(u8* data, SDisasmData* dd)
	{
		do_common_two_prefixes_mnemonic_operand_size_check(dd, 1, 
															REPE,	cgc_repe_instruction,
															REPNE,	cgc_repne_instruction,
															cgc_stosw_instruction,
															cgc_stosd_instruction);
	}

	void opcode_sub_accum_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed16_32(data, dd, cgc_sub_instruction, 1);
	}

	void opcode_sub_accum_immed8(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed8(data, dd, cgc_sub_instruction, 1);
	}

	void opcode_sub28(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8(dd, cgc_sub_instruction, 1);
		do_common_regrm(data + 1, dd, _8bit, false, _null_string);
	}

	void opcode_sub29(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, cgc_sub_instruction, 1);
		do_common_regrm(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_sub2a(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8_reversed(dd, cgc_sub_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _8bit, false, _null_string);
	}

	void opcode_sub2b(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, cgc_sub_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_sub_rm8_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm8_immed8(data, dd, cgc_sub_instruction, 1);
	}

	void opcode_sub_rm16_32_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed16_32(data, dd, cgc_sub_instruction, 1);
	}

	void opcode_sub_rm16_32_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed8(data, dd, cgc_sub_instruction, 1);
	}

	void opcode_test_accum_imm16_32(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed16_32(data, dd, cgc_test_instruction, 1);
	}

	void opcode_test_accum_imm8(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed8(data, dd, cgc_test_instruction, 1);
	}

	void opcode_test_rm_reg16_32(u8* data, SDisasmData* dd)
	{
		_asm int 3;
	}

	void opcode_test_rm_reg_8(u8* data, SDisasmData* dd)
	{
		_asm int 3;
	}

	void opcode_two_byte_instruction(u8* data, SDisasmData* dd)
	{
		dd->opcode_bytes += 2;
		second_byte_functions[dd->data_root[dd->opcode_bytes - 1]]
			(dd->data_root + dd->opcode_bytes, dd);
	}

	void opcode_two_byte_unused(u8* data, SDisasmData* dd)
	{
		_asm int 3;
	}

	void opcode_ud2_0f0b(u8* data, SDisasmData* dd)
	{ // 0f 0b
		do_common_mnemonic(dd, cgc_ud2_instruction, 1, NULL, NULL);
		dd->line_comment = (u8*)"; 0f 0b, always generates #UD";
	}

	void opcode_ud2_0fb9(u8* data, SDisasmData* dd)
	{ // 0f b9
		do_common_mnemonic(dd, cgc_ud2_instruction, 1, NULL, NULL);
		dd->line_comment = (u8*)"; 0f b9, always generates #UD";
	}

	void opcode_unused(u8* data, SDisasmData* dd)
	{
		_asm int 3;
	}

	void opcode_wait(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_wait_instruction, 1, NULL, NULL);
	}

	void opcode_wbinvd(u8* data, SDisasmData* dd)
	{ // 0f 09
		do_common_mnemonic(dd, cgc_wbinvd_instruction, 1, NULL, NULL);
	}

	void opcode_wrmsr(u8* data, SDisasmData* dd)
	{ // 0f 30
		do_common_mnemonic(dd, cgc_wrmsr_instruction, 1, NULL, NULL);
	}

	void opcode_xadd(u8* data, SDisasmData* dd)
	{ // 0f c1
		do_common_opcode_rm16_rm32(dd, cgc_xadd_instruction, 1);
		do_common_regrm(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_xadd_byte(u8* data, SDisasmData* dd)
	{ // 0f c0
		do_common_opcode_rm8(dd, cgc_xadd_instruction, 1);
		do_common_regrm(data + 1, dd, _8bit, false, _null_string);
	}

	void opcode_xchg(u8* data, SDisasmData* dd)
	{  // 87
		do_common_opcode_rm16_rm32(dd, cgc_xchg_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_xchg_byte(u8* data, SDisasmData* dd)
	{ // 86
		do_common_opcode_rm16_rm32(dd, cgc_xchg_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _8bit, false, _null_string);
	}

	void opcode_xchg_xxx(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_xchg_instruction, 1, NULL, NULL);
		extract_gp_reg_operand(dd, *data & 0x07, &dd->operand1, _16bit | _32bit);
	}

	void opcode_xlat(u8* data, SDisasmData* dd)
	{
		do_common_mnemonic(dd, cgc_xlat_instruction, 1, NULL, NULL);
	}

	void opcode_xor_accum_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed16_32(data, dd, cgc_xor_instruction, 1);
	}

	void opcode_xor_accum_immed8(u8* data, SDisasmData* dd)
	{
		do_common_accum16_32_immed8(data, dd, cgc_xor_instruction, 1);
	}

	void opcode_xor30(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8(dd, cgc_xor_instruction, 1);
		do_common_regrm(data + 1, dd, _8bit, false, _null_string);
	}

	void opcode_xor31(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, cgc_xor_instruction, 1);
		do_common_regrm(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_xor32(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm8_reversed(dd, cgc_xor_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _8bit, false, _null_string);
	}

	void opcode_xor33(u8* data, SDisasmData* dd)
	{
		do_common_opcode_rm16_rm32(dd, cgc_xor_instruction, 1);
		do_common_regrm_reversed(data + 1, dd, _16bit | _32bit, false, _null_string);
	}

	void opcode_xor_rm8_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm8_immed8(data, dd, cgc_xor_instruction, 1);
	}

	void opcode_xor_rm16_32_immed16_32(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed16_32(data, dd, cgc_xor_instruction, 1);
	}

	void opcode_xor_rm16_32_immed8(u8* data, SDisasmData* dd)
	{
		do_common_rm16_32_immed8(data, dd, cgc_xor_instruction, 1);
	}
