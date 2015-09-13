Sep.11.2015
-----------

lasm -- LibSF Assembler for Exodus (i386 and later)
lcc  -- LibSF C Compiler for Exodus (i386 and later)

Both of these tools are primitive, but they are designed to
produce code suitable for execution in the Exodus kernel.
Use -16 or -32 to generate real-mode 16-bit code, or pmode
32-bit code.

-----
lasm is roughly compatible with a sub-feature-set of MASM 6.11d,
with new assembly opcode extensions added in.  It allows the same
type of macro processing and simple procedure declarations,
anonymous labels, etc.

-----
lcc is a simple C compiler which takes C source code and generates
completely un-optimized assembly code for compilation with lasm.

Best regards,
Rick C. Hodgin
