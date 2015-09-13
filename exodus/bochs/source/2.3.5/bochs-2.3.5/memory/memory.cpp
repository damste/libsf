/////////////////////////////////////////////////////////////////////////
// $Id: memory.cc,v 1.59 2006/12/29 08:02:35 sshwarts Exp $
/////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2001  MandrakeSoft S.A.
//
//    MandrakeSoft S.A.
//    43, rue d'Aboukir
//    75002 Paris - France
//    http://www.linux-mandrake.com/
//    http://www.mandrakesoft.com/
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA


#include "bochs.h"
#include "cpu/cpu.h"
#include "iodev/iodev.h"
#define LOG_THIS BX_MEM_THIS

#if BX_PROVIDE_CPU_MEMORY

//
// Memory map inside the 1st megabyte:
//
// 0x00000 - 0x7ffff    DOS area (512K)
// 0x80000 - 0x9ffff    Optional fixed memory hole (128K)
// If BX_REMOTE_MDA == 1, MDA intercepts everything written to or read from 0b0000 to 0b7fff
// 0xa0000 - 0xbffff    Standard PCI/ISA Video Mem / SMMRAM (128K)
// 0xc0000 - 0xdffff    Expansion Card BIOS and Buffer Area (128K)
// 0xe0000 - 0xeffff    Lower BIOS Area (64K)
// 0xf0000 - 0xfffff    Upper BIOS Area (64K)
//
#if BX_REMOTE_MDA == 1
    unsigned char bx_mda_32kb_buffer[32768];
    long bx_mda_mouse_x			= 0;
    long bx_mda_mouse_y			= 0;
    long bx_mda_mouse_buttons	= 0;
	long bx_mda_key				= 0;
	long bx_mda_key_up_down		= 0;
//    unsigned char bx_base_640kb_buffer[655360];
//    unsigned char bx_upper_256kb_buffer[262144];
	HWND bx_mda_hwnd			= NULL;
	void CALLBACK bx_mda_named_pipe(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
    #define BX_MDA_WM_UPDATE_MOUSE_X        WM_USER + 0
    #define BX_MDA_WM_UPDATE_MOUSE_Y        WM_USER + 1
    #define BX_MDA_WM_UPDATE_MOUSE_BUTTONS  WM_USER + 2
	#define BX_MDA_WM_UPDATE_KEY			WM_USER + 3
	#define BX_MDA_WM_UPDATE_KEY_UP_DOWN	WM_USER + 4
#endif

  void BX_CPP_AttrRegparmN(3)
BX_MEM_C::writePhysicalPage(BX_CPU_C *cpu, bx_phy_address addr, unsigned len, void *data)
{
    unsigned len2;
    bool lbSendall = false;
    Bit8u *data_ptr;
    bx_phy_address a20addr = A20ADDR(addr);
    struct memory_handler_struct *memory_handler = NULL;

#if BX_REMOTE_MDA == 1
    if (addr >= 0x0b0000 && addr <= 0x0b7fff)
    {
        // It's for the MDA
        for (len2 = len ; len2 > 0; len2--)
        {
            bx_mda_32kb_buffer[addr - 0x0b0000 + len2 - 1] = ((unsigned char*)data)[len2 - 1];
        }
        return;
    }
//     else if (addr < 0x0a0000)
//     {
//         // Store in base 640KB
//         for (len2 = len ; len2 > 0; len2--)
//         {
//             bx_base_640kb_buffer[addr + len2 - 1] = ((unsigned char*)data)[len2 - 1];
//         }
//     }
//     else if (addr >= 0x0c0000)
//     {
//         // Store in upper 256 KB
//         for (len2 = len ; len2 > 0; len2--)
//         {
//             bx_upper_256kb_buffer[addr - 0x0c0000 + len2 - 1] = ((unsigned char*)data)[len2 - 1];
//         }
//     }
#endif

  // Note: accesses should always be contained within a single page now

  if (cpu != NULL) {
#if BX_SUPPORT_IODEBUG
    bx_iodebug_c::mem_write(cpu, a20addr, len, data);
#endif

    BX_INSTR_PHY_WRITE(cpu->which_cpu(), a20addr, len);

#if BX_DEBUGGER
    // (mch) Check for physical write break points, TODO
    // (bbd) Each breakpoint should have an associated CPU#, TODO
    for (int i = 0; i < num_write_watchpoints; i++) {
      if (write_watchpoint[i] == a20addr) {
        BX_CPU(0)->watchpoint = a20addr;
        BX_CPU(0)->break_point = BREAK_POINT_WRITE;
        break;
      }
    }
#endif

#if BX_SUPPORT_APIC
    bx_generic_apic_c *local_apic = &cpu->local_apic;
    if (local_apic->is_selected(a20addr, len)) {
      local_apic->write(a20addr, (Bit32u *)data, len);
      return;
    }
#endif

    if ((a20addr & 0xfffe0000) == 0x000a0000 && (BX_MEM_THIS smram_available))
    {
      // SMRAM memory space
      if (BX_MEM_THIS smram_enable || (cpu->smm_mode() && !BX_MEM_THIS smram_restricted))
        goto mem_write;
    }
  }

  memory_handler = BX_MEM_THIS memory_handlers[a20addr >> 20];
  while (memory_handler) {
    if (memory_handler->begin <= a20addr &&
          memory_handler->end >= a20addr &&
          memory_handler->write_handler(a20addr, len, data, memory_handler->param))
    {
      return;
    }
    memory_handler = memory_handler->next;
  }

mem_write:

  // all memory access feets in single 4K page 
  if (a20addr < BX_MEM_THIS len) {
#if BX_SUPPORT_ICACHE
    pageWriteStampTable.decWriteStamp(a20addr);
#endif
    // all of data is within limits of physical memory
    if ((a20addr & 0xfff80000) != 0x00080000 || (a20addr <= 0x0009ffff))
    {
      if (len == 8) {
        WriteHostQWordToLittleEndian(&BX_MEM_THIS vector[a20addr], *(Bit64u*)data);
        BX_DBG_DIRTY_PAGE(a20addr >> 12);
        return;
      }
      if (len == 4) {
        WriteHostDWordToLittleEndian(&BX_MEM_THIS vector[a20addr], *(Bit32u*)data);
        BX_DBG_DIRTY_PAGE(a20addr >> 12);
        return;
      }
      if (len == 2) {
        WriteHostWordToLittleEndian(&BX_MEM_THIS vector[a20addr], *(Bit16u*)data);
        BX_DBG_DIRTY_PAGE(a20addr >> 12);
        return;
      }
      if (len == 1) {
        * ((Bit8u *) (&BX_MEM_THIS vector[a20addr])) = * (Bit8u *) data;
        BX_DBG_DIRTY_PAGE(a20addr >> 12);
        return;
      }
      // len == other, just fall thru to special cases handling
    }

#ifdef BX_LITTLE_ENDIAN
    data_ptr = (Bit8u *) data;
#else // BX_BIG_ENDIAN
    data_ptr = (Bit8u *) data + (len - 1);
#endif

write_one:
    if ((a20addr & 0xfff80000) != 0x00080000 || (a20addr <= 0x0009ffff))
    {
      // addr *not* in range 000A0000 .. 000FFFFF
      BX_MEM_THIS vector[a20addr] = *data_ptr;
      BX_DBG_DIRTY_PAGE(a20addr >> 12);
inc_one:
      if (len == 1) return;
      len--;
      a20addr++;
#ifdef BX_LITTLE_ENDIAN
      data_ptr++;
#else // BX_BIG_ENDIAN
      data_ptr--;
#endif
      goto write_one;
    }

    // addr must be in range 000A0000 .. 000FFFFF

    // SMMRAM
    if (a20addr <= 0x000bffff) {
      // devices are not allowed to access SMMRAM under VGA memory
      if (cpu) {
        BX_MEM_THIS vector[a20addr] = *data_ptr;
        BX_DBG_DIRTY_PAGE(a20addr >> 12);
      }
      goto inc_one;
    }

    // adapter ROM     C0000 .. DFFFF
    // ROM BIOS memory E0000 .. FFFFF
#if BX_SUPPORT_PCI == 0
    // ignore write to ROM
#else
    // Write Based on 440fx Programming
    if (BX_MEM_THIS pci_enabled && ((a20addr & 0xfffc0000) == 0x000c0000))
    {
      switch (DEV_pci_wr_memtype(a20addr)) {
        case 0x1:   // Writes to ShadowRAM
          BX_DEBUG(("Writing to ShadowRAM: address %08x, data %02x", (unsigned) a20addr, *data_ptr));
          BX_MEM_THIS vector[a20addr] = *data_ptr;
          BX_DBG_DIRTY_PAGE(a20addr >> 12);
          goto inc_one;

        case 0x0:   // Writes to ROM, Inhibit
          BX_DEBUG(("Write to ROM ignored: address %08x, data %02x", (unsigned) a20addr, *data_ptr));
          goto inc_one;

        default:
          BX_PANIC(("writePhysicalPage: default case"));
          goto inc_one;
      }
    }
#endif
    goto inc_one;
  }
  else {
    // access outside limits of physical memory, ignore
    BX_DEBUG(("Write outside the limits of physical memory (0x%08x) (ignore)", a20addr));
  }
}

  void BX_CPP_AttrRegparmN(3)
BX_MEM_C::readPhysicalPage(BX_CPU_C *cpu, bx_phy_address addr, unsigned len, void *data)
{
  Bit8u *data_ptr;
  bx_phy_address a20addr = A20ADDR(addr);
  struct memory_handler_struct *memory_handler = NULL;

#if BX_REMOTE_MDA == 1
  if (addr >= 0x0b0000 && addr <= 0x0b7fff)
  {
      // It's for the MDA
      *(unsigned char*)data = bx_mda_32kb_buffer[addr - 0x0b0000];
      return;
  }
#endif

  // Note: accesses should always be contained within a single page now

  if (cpu != NULL) {
#if BX_SUPPORT_IODEBUG
    bx_iodebug_c::mem_read(cpu, a20addr, len, data);
#endif
 
    BX_INSTR_PHY_READ(cpu->which_cpu(), a20addr, len);

#if BX_DEBUGGER
    // (mch) Check for physical read break points, TODO
    // (bbd) Each breakpoint should have an associated CPU#, TODO
    for (int i = 0; i < num_read_watchpoints; i++) {
      if (read_watchpoint[i] == a20addr) {
         BX_CPU(0)->watchpoint = a20addr;
         BX_CPU(0)->break_point = BREAK_POINT_READ;
         break;
      }
    }
#endif

#if BX_SUPPORT_APIC
    bx_generic_apic_c *local_apic = &cpu->local_apic;
    if (local_apic->is_selected (a20addr, len)) {
      local_apic->read(a20addr, data, len);
      return;
    }
#endif

    if ((a20addr & 0xfffe0000) == 0x000a0000 && (BX_MEM_THIS smram_available))
    {
      // SMRAM memory space
      if (BX_MEM_THIS smram_enable || (cpu->smm_mode() && !BX_MEM_THIS smram_restricted))
        goto mem_read;
    }
  }

  memory_handler = BX_MEM_THIS memory_handlers[a20addr >> 20];
  while (memory_handler) {
    if (memory_handler->begin <= a20addr &&
          memory_handler->end >= a20addr &&
          memory_handler->read_handler(a20addr, len, data, memory_handler->param))
    {
      return;
    }
    memory_handler = memory_handler->next;
  }

mem_read:

  if (a20addr <= BX_MEM_THIS len) {
    // all of data is within limits of physical memory
    if ((a20addr & 0xfff80000) != 0x00080000 || (a20addr <= 0x0009ffff))
    {
      if (len == 8) {
        ReadHostQWordFromLittleEndian(&BX_MEM_THIS vector[a20addr], * (Bit64u*) data);
        return;
      }
      if (len == 4) {
        ReadHostDWordFromLittleEndian(&BX_MEM_THIS vector[a20addr], * (Bit32u*) data);
        return;
      }
      if (len == 2) {
        ReadHostWordFromLittleEndian(&BX_MEM_THIS vector[a20addr], * (Bit16u*) data);
        return;
      }
      if (len == 1) {
        * (Bit8u *) data = * ((Bit8u *) (&BX_MEM_THIS vector[a20addr]));
        return;
      }
      // len == other case can just fall thru to special cases handling
    }

#ifdef BX_LITTLE_ENDIAN
    data_ptr = (Bit8u *) data;
#else // BX_BIG_ENDIAN
    data_ptr = (Bit8u *) data + (len - 1);
#endif

read_one:
    if ((a20addr & 0xfff80000) != 0x00080000 || (a20addr <= 0x0009ffff))
    {
      // addr *not* in range 00080000 .. 000FFFFF
      *data_ptr = BX_MEM_THIS vector[a20addr];
inc_one:
      if (len == 1) return;
      len--;
      a20addr++;
#ifdef BX_LITTLE_ENDIAN
      data_ptr++;
#else // BX_BIG_ENDIAN
      data_ptr--;
#endif
      goto read_one;
    }

    // addr must be in range 000A0000 .. 000FFFFF

    // SMMRAM
    if (a20addr <= 0x000bffff) {
      // devices are not allowed to access SMMRAM under VGA memory
      if (cpu) *data_ptr = BX_MEM_THIS vector[a20addr];
      goto inc_one;
    }

#if BX_SUPPORT_PCI
    if (BX_MEM_THIS pci_enabled && ((a20addr & 0xfffc0000) == 0x000c0000))
    {
      switch (DEV_pci_rd_memtype(a20addr)) {
        case 0x0:  // Read from ROM
          if ((a20addr & 0xfffe0000) == 0x000e0000)
          {
            *data_ptr = BX_MEM_THIS rom[a20addr & BIOS_MASK];
          }
          else
          {
            *data_ptr = BX_MEM_THIS rom[(a20addr & EXROM_MASK) + BIOSROMSZ];
          }
          goto inc_one;
        case 0x1:  // Read from ShadowRAM
          *data_ptr = BX_MEM_THIS vector[a20addr];
          goto inc_one;
        default:
          BX_PANIC(("readPhysicalPage: default case"));
      }
      goto inc_one;
    }
    else
#endif  // #if BX_SUPPORT_PCI
    {
      if ((a20addr & 0xfffc0000) != 0x000c0000) {
        *data_ptr = BX_MEM_THIS vector[a20addr];
      }
      else if ((a20addr & 0xfffe0000) == 0x000e0000)
      {
        *data_ptr = BX_MEM_THIS rom[a20addr & BIOS_MASK];
      }
      else
      {
        *data_ptr = BX_MEM_THIS rom[(a20addr & EXROM_MASK) + BIOSROMSZ];
      }
      goto inc_one;
    }
  }
  else
  {  // access outside limits of physical memory

#ifdef BX_LITTLE_ENDIAN
    data_ptr = (Bit8u *) data;
#else // BX_BIG_ENDIAN
    data_ptr = (Bit8u *) data + (len - 1);
#endif

    for (unsigned i = 0; i < len; i++) {
      if (a20addr >= (bx_phy_address)~BIOS_MASK)
        *data_ptr = BX_MEM_THIS rom[a20addr & BIOS_MASK];
      else
        *data_ptr = 0xff;
      addr++;
      a20addr = (addr);
#ifdef BX_LITTLE_ENDIAN
      data_ptr++;
#else // BX_BIG_ENDIAN
      data_ptr--;
#endif
    }
  }
}

#if BX_REMOTE_MDA == 1
	void CALLBACK bx_mda_named_pipe(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
    {
        HANDLE hPipe; 
        CHAR chBuf[512]; 
        BOOL fSuccess; 
        DWORD cbRead, cbWritten, dwMode; 
        LPTSTR lpszPipename = "\\\\.\\pipe\\MoMoPipe";


        // Try to open a named pipe; wait for it, if necessary. 
        while (1) 
        { 
            hPipe = CreateFile( lpszPipename,   // pipe name 
                                GENERIC_READ |  // read and write access 
                                GENERIC_WRITE, 
                                0,              // no sharing 
                                NULL,           // no security attributes
                                OPEN_EXISTING,  // opens existing pipe 
                                0,              // default attributes 
                                NULL);          // no template file 

            // Break if the pipe handle is valid. 
            if (hPipe != INVALID_HANDLE_VALUE) 
            {
                // We're good, we have the pipe
                break;
            }
            return;
        } 

        // The pipe connected; change to message-read mode. 
        dwMode = PIPE_READMODE_MESSAGE; 
        fSuccess = SetNamedPipeHandleState( hPipe,    // pipe handle 
                                            &dwMode,  // new pipe mode 
                                            NULL,     // don't set maximum bytes 
                                            NULL);    // don't set maximum time 
        if (!fSuccess)
            return;

        // Send a message to the pipe server. 
        fSuccess = WriteFile(hPipe,                  // pipe handle 
                            bx_mda_32kb_buffer,     // message 
                            sizeof(bx_mda_32kb_buffer), // message length 
                            &cbWritten,             // bytes written 
                            NULL);                  // not overlapped 
        if (! fSuccess) 
            return;

        do 
        { 
            // Read from the pipe. 
            fSuccess = ReadFile(hPipe,    // pipe handle 
                                chBuf,    // buffer to receive reply 
                                512,      // size of buffer 
                                &cbRead,  // number of bytes read 
                                NULL);    // not overlapped 

            if (! fSuccess && GetLastError() != ERROR_MORE_DATA) 
                break; 

            // Right now, data is in chBuf
            // MoMo returns MONO mouse position as first two DWORDs
            bx_mda_mouse_x          = *((long*)&chBuf[0]);
            bx_mda_mouse_y          = *((long*)&chBuf[4]);
            bx_mda_mouse_buttons    = *((long*)&chBuf[8]);
			bx_mda_key				= *((long*)&chBuf[12]);
			bx_mda_key_up_down		= *((long*)&chBuf[16]);

        } while (!fSuccess);    // repeat loop if ERROR_MORE_DATA 

        // All done
        CloseHandle(hPipe); 

        // We're good!
        return;
    }

	void CALLBACK bx_mda_timer_function(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
    {
        if (bx_mda_hwnd == NULL)
        {
            // We have to find the window
            bx_mda_hwnd = FindWindow("MoMo", "MoMo");
            if (bx_mda_hwnd == NULL)
                return;
        }
        bx_mda_mouse_x			= SendMessage(bx_mda_hwnd, BX_MDA_WM_UPDATE_MOUSE_X,		0, 0);
        bx_mda_mouse_y			= SendMessage(bx_mda_hwnd, BX_MDA_WM_UPDATE_MOUSE_Y,		0, 0);
        bx_mda_mouse_buttons	= SendMessage(bx_mda_hwnd, BX_MDA_WM_UPDATE_MOUSE_BUTTONS,	0, 0);
		bx_mda_key				= SendMessage(bx_mda_hwnd, BX_MDA_WM_UPDATE_KEY,			0, 0);
		bx_mda_key_up_down		= SendMessage(bx_mda_hwnd, BX_MDA_WM_UPDATE_KEY_UP_DOWN,	0, 0);
    }
#endif // #if BX_REMOTE_MDA == 1

#endif // #if BX_PROVIDE_CPU_MEMORY
