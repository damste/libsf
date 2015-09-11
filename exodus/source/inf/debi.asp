€€€€                                                    low-level DEBI Debugger
€€€€›
ﬁ€€€€‹
 ﬂﬂ€€€€€‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹‹
   ›
   ›    Structures, Memory locations, etc
   ›
 ‹‹€€€€€ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ
ﬁ€€€€ﬂ
€€€€›
€€€€
€€€€    _sDEBI_screen
€€€€        This is a raw buffer used to handle the MONO screen buffer during screen saves.  The data begins at offset 0 and
€€€€        continues on through 7fffh (32k)
€€€€
€€€€    _sDEBI_objects
€€€€        This is a referenced buffer.  The first 8 bytes represent these items:
€€€€
€€€€          Offset  Length    Description
€€€€          ------  ------    --------------------
€€€€            0       4       Offset to where the next item would be added to this memory region
€€€€            4+              Available for storage, referenced by the structure information in DEBI_screen_table
€€€€
€€€€
€€€€
€€€€
€€€€
€€€€
€€€€    RCH - 01/21/01 11:32 am
€€€€     end 
€€€€