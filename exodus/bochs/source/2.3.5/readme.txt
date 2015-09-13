Sep.11.2015
-----------

MoMo emulates the IBM Monochrome Graphics Adapter display.  It
specicifically (as of Sep.11.2015) allows display of the Hercules
graphics modes, which are a monochrome grid 720 x 348 pixels.
Exodus drives this mode by writing raw pixel data in the memory
range 0xb0000 to 0xb7fff, which is sent to MoMo via a named pipe.
When received, MoMo displays the new contents.

VeMo emulates SVGA screens of arbitrary resolution.  It has not
been completed yet (as of Sep.11.2015) but will be completed
early on (Lord willing) as part of the continued development of
Exodus.

Best regards,
Rick C. Hodgin
