Nov.22.2014
-----------

The li386 folder was created to support the LibSF i386-x40 CPU design, a 40-bit extension of the traditional i386 architecture with several internal changes to make it a much simpler core.  Our talents and skills given back to God, from whom they came, being used to serve His Kingdom here upon this Earth.  In much prayer and supplication, knowing that He is able to do exceedingly abundantly beyond any of our needs.  Jesus Christ, our Savior, to Him be all the glory.

&nbsp;&nbsp;&nbsp;&nbsp;(1)  Only protected mode is supported.<br>
&nbsp;&nbsp;&nbsp;&nbsp;(2)  Hardware-only FPU and SIMD support, see [design](https://github.com/RickCHodgin/libsf/blob/master/li386/oppie/oppie-5.png).<br>
&nbsp;&nbsp;&nbsp;&nbsp;(3)  32-bit (eax) and 40-bit processing (wax) registers, see [design](https://github.com/RickCHodgin/libsf/blob/master/li386/li386-documentation/images/wex_register_mapping.png).<br>
&nbsp;&nbsp;&nbsp;&nbsp;(4)  32-bit and 40-bit memory address modes, see [design](https://github.com/RickCHodgin/libsf/blob/master/li386/li386-documentation/images/eflags.png).<br>
&nbsp;&nbsp;&nbsp;&nbsp;(5)  Four-core base design (using two [Oppie-6](https://github.com/RickCHodgin/libsf/blob/master/li386/oppie/oppie-6.png) cores per die), see [design](https://github.com/RickCHodgin/libsf/blob/master/li386/oppie/oppie-7.png).<br>
&nbsp;&nbsp;&nbsp;&nbsp;(6)  1 Terabyte of addressable memory per core (2TB total).<br>
&nbsp;&nbsp;&nbsp;&nbsp;(7)  1 Terabyte of common / shared memory between cores, see [design](https://github.com/RickCHodgin/libsf/blob/master/li386/oppie/oppie-7.png) and the [selector design](https://github.com/RickCHodgin/libsf/blob/master/li386/li386-documentation/images/selector.png).<br>
&nbsp;&nbsp;&nbsp;&nbsp;(8)  Removal of traditional paging support, replaced with a new concept called Memory Monitor Range, which simulates features of paging in a heavily memory'd environment (such as with 1 TB of addressable RAM), see [design](https://github.com/RickCHodgin/libsf/blob/master/li386/li386-documentation/images/paging_cr0_cr4.png).<br>
&nbsp;&nbsp;&nbsp;&nbsp;(9)  Hardware support for multiple ISAs:<br>
	
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(a) li386 -- A revamping of i386 opcodes, see [design](https://github.com/RickCHodgin/libsf/tree/master/li386/oppie/LibSF-386-x40).
		
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(b) liARM -- Support for a large subset of ARMv7.
		
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;(c) i386  -- The original 80386 ISA with some tweaks.

Prayer and Hope
---------------

&nbsp;&nbsp;&nbsp;&nbsp;We'll see what the Lord brings.  Currently there are test projects under development to make li386 a reality, codenamed "Oppie" for "little opcodes."  Also see the [design images](https://github.com/RickCHodgin/libsf/tree/master/li386/li386-documentation/images).

&nbsp;&nbsp;&nbsp;&nbsp;See the [oppie folder](https://github.com/RickCHodgin/libsf/tree/master/li386/oppie) for current progress.

Nov.27.2014
-----------

&nbsp;&nbsp;&nbsp;&nbsp;As of Nov.16.2015 no ongoing development is active, but remains planned (James 4:15) following the completion of other projects, or when more developers arrive to help with LibSF projects.

&nbsp;&nbsp;&nbsp;&nbsp;(1)  Oppie-1 -- (coding in progress) an 8-bit core, 5-stage pipeline, see [Oppie-1](https://github.com/RickCHodgin/libsf/tree/master/li386/oppie/oppie1) and the [design](https://github.com/RickCHodgin/libsf/blob/master/li386/oppie/oppie-1.png).<br>
&nbsp;&nbsp;&nbsp;&nbsp;(2)  Oppie-2 -- Extended Oppie-1 to 32-bits, stack, interrupts, see the [design](https://github.com/RickCHodgin/libsf/blob/master/li386/oppie/oppie-2.png).<br>
&nbsp;&nbsp;&nbsp;&nbsp;(3)  Oppie-3 -- A largely i386 compatible core, no FPU or SIMD, see the [design](https://github.com/RickCHodgin/libsf/blob/master/li386/oppie/oppie-3.png).<br>
&nbsp;&nbsp;&nbsp;&nbsp;(4)  Oppie-4 -- A dual-core Oppie-3, see the [design](https://github.com/RickCHodgin/libsf/blob/master/li386/oppie/oppie-4.png).<br>
&nbsp;&nbsp;&nbsp;&nbsp;(5)  Oppie-5 -- A single-thread LibSF 386-x40, see the [design](https://github.com/RickCHodgin/libsf/blob/master/li386/oppie/oppie-5.png).<br>
&nbsp;&nbsp;&nbsp;&nbsp;(6)  Oppie-6 -- Add Love Threading, Love Processing, see the [design](https://github.com/RickCHodgin/libsf/blob/master/li386/oppie/oppie-6.png).<br>
&nbsp;&nbsp;&nbsp;&nbsp;(7)  Oppie-7 -- Dual-core Oppie-6, see the [design](https://github.com/RickCHodgin/libsf/blob/master/li386/oppie/oppie-7.png).<br>
&nbsp;&nbsp;&nbsp;&nbsp;(8)  Oppie-8 -- Dual-core Oppie-7, see the [design](https://github.com/RickCHodgin/libsf/blob/master/li386/oppie/oppie-8.png).<br>

&nbsp;&nbsp;&nbsp;&nbsp;Best regards,
&nbsp;&nbsp;&nbsp;&nbsp;Rick C. Hodgin
