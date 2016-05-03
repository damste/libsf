Sanitizing Debugger
May.02.2016
-------------------

I had a bug in a program that I couldn't find.  Still can't as of
the time of this writing.  I was able to find a work-around by
modifying the alloc() and free() algorithms to pad the head and
tail of the request memory block with 16 bytes each.  It may
work with less, but I'm keeping it at 16 since it's a paragraph-
aligned value on x86.

To help track down the cause of the buffer overrun, I want to
write this sanitizing debugger which is planned to connect to a
32-bit Windows application, and perform the following:

	(1)  Single-step execute a program, allowing for setup
		 to control which IP address ranges are stepped through
		 (such as only single-step through a particular DLL).

	(2)  Disassemble every instruction as it's single stepping,
		 and extract those which reference memory.

	(3)  Intercept the root malloc(), calloc(), realloc(), and
		 free() algorithms, to capture which lines are calling
		 them, and also which variables are initially associated
		 with them, so they can be tracked to determine some
		 warnings on range accesses, and not mere out-of-buffer
		 writes.

	(4)  For those instructions which reference memory, determine
		 if they're in range of an allocated block, and if not,
		 report on it immediately, breaking to a debugger which
		 will show the source code line from the compiled PDB.
	
	(5)  Maintain a shadow buffer for every access and record
		 read/write metrics in the nibbles, for 0..15 or more
		 references per byte, per read or write.
	
	(6)  Allow a real-time exporting of this information so it
		 can be graphed, queried, breakpoints set on various
		 source code lines, etc.

We'll see how it goes.  A lot of stuff on my plate right now.

Best regards,
Rick C. Hodgin
