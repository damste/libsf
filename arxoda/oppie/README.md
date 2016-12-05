Nov.22.2014
-----------

Oppie (or "Little Opcode") plans to be (James 4:15, Lord willing), a
series of mini-CPUs that perform various functions approaching a real
CPU.

Oppie-1 -- (in progress) A simple 8-bit CPU with eight opcodes, 2 KB of
		RAM, four 8-bit registers, built atop a 3-, 4-, or 5-stage
		pipeline (read instruction, decode, [read data], execute,
		[write retire] -- pipe stages in [brackets] are optional
		per instruction).

Oppie-2 -- (planned) An extension of Oppie-1 supporting more instructions,
		eight 32-bit registers and full 32-bit unsigned integer
		processing and instructions, a stack, tasks, and selectors.

Oppie-3 -- (planned) A near i386 compatible machine, but with many
		planned LibSF 386-x40 features.

Oppie-4 -- (planned) A dual-core Oppie-3.

Oppie-5 -- (planned) A full LibSF 386-x40 core.
		
Oppie-6 -- (planned) A Love Threading Oppie-5.

Oppie-7 -- (planned) A dual-core Oppie-6.

Oppie-8 -- (planned) A dual-core Oppie-7 with 21TB of memory.

-----
The final goal is the basic framework necessary to bring the
"LibSF 386-x40" to life (hereafter called li386 for short).

The li386 architecture defines:

	(1)  Only protected-mode operations.
	(2)  32-bit or 40-bit processing.
	(3)  FPU and SIMD as first-class citizens, no FPU stack in li386 mode.
	(4)  Two cores, each with Love Threading (two tightly coupled threads).
	(5)  1TB of addressable memory per core (Oppie-6 and Oppie-7, Oppie-8 4TB of addressable memory per core).
	(6)  1TB of addressable memory shared in common (Oppie-7, Oppie-8 1TB each per Oppie-7 core, plus 3TB shared between all cores).
	(7)  Support for multiple ISAs, including:
		(a) li386 (LibSF's revamp of the i386 opcodes)
		(b) liARM (a large subset of ARMv7's 32-bit ISA)
		(c) i386 ISAs (80386 opcodes with some newer features
			added bringing it closer to i686)

All of this is James 4:15, which is to say, "Lord willing," for it is
not by me, but by Him, if it is to be. :-)

Best regards,
Rick C. Hodgin
