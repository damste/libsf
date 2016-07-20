Jul.19.2016
-----------

lsa -- LibSF Simple Assembler for ES/2 (i386 and later)
lsc -- LibSF Simple C Compiler for ES/2 (i386 and later)

Both of these tools are primitive, but they are designed to
produce code suitable for execution in the Exodus kernel.  They
will produce 16-bit code blocks and 32-bit code blocks, which
are encapsulated in flat binary output files relative to their
ORG, or in DOS 16-bit or Windows 32-bit executables.

-----
lsa is roughly compatible with a sub-feature-set of MASM 6.11d,
with new assembly opcode extensions added in.  It allows the
same type of macro processing and simple procedure declarations,
anonymous labels, etc.  A conversion utility was created to
migrate MASM 6.11d source code into lsa's syntax:

    \libsf\exodus\tools\xbase\convert_asm_to_lasm.prg

-----
lsc is a simple C compiler which takes C source code and
generates completely un-optimized assembly code for assembly
in lsa.

Best regards,
Rick C. Hodgin
