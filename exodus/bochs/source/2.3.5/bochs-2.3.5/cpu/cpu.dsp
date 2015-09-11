# Microsoft Developer Studio Project File - Name="cpu" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=cpu - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "cpu.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "cpu.mak" CFG="cpu - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "cpu - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "cpu - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "cpu - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../obj-release"
# PROP Intermediate_Dir "../obj-release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".." /I "../instrument/stubs" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /TP /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "cpu - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../obj-debug"
# PROP Intermediate_Dir "../obj-debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /GX /Z7 /Od /I "../" /I "../instrument/stubs/" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NDEBUG" /D "_WINDOWS" /YX /FD /TP /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "cpu - Win32 Release"
# Name "cpu - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\3dnow.cpp
# End Source File
# Begin Source File

SOURCE=.\access.cpp
# End Source File
# Begin Source File

SOURCE=.\apic.cpp
# End Source File
# Begin Source File

SOURCE=.\arith16.cpp
# End Source File
# Begin Source File

SOURCE=.\arith32.cpp
# End Source File
# Begin Source File

SOURCE=.\arith64.cpp
# End Source File
# Begin Source File

SOURCE=.\arith8.cpp
# End Source File
# Begin Source File

SOURCE=.\bcd.cpp
# End Source File
# Begin Source File

SOURCE=.\bit.cpp
# End Source File
# Begin Source File

SOURCE=.\cpu.cpp
# End Source File
# Begin Source File

SOURCE=.\cpuid.cpp
# End Source File
# Begin Source File

SOURCE=.\ctrl_xfer16.cpp
# End Source File
# Begin Source File

SOURCE=.\ctrl_xfer32.cpp
# End Source File
# Begin Source File

SOURCE=.\ctrl_xfer64.cpp
# End Source File
# Begin Source File

SOURCE=.\ctrl_xfer8.cpp
# End Source File
# Begin Source File

SOURCE=.\jmp_far.cpp
# End Source File
# Begin Source File

SOURCE=.\call_far.cpp
# End Source File
# Begin Source File

SOURCE=.\ret_far.cpp
# End Source File
# Begin Source File

SOURCE=.\iret.cpp
# End Source File
# Begin Source File

SOURCE=.\ctrl_xfer_pro.cpp
# End Source File
# Begin Source File

SOURCE=.\data_xfer16.cpp
# End Source File
# Begin Source File

SOURCE=.\data_xfer32.cpp
# End Source File
# Begin Source File

SOURCE=.\data_xfer64.cpp
# End Source File
# Begin Source File

SOURCE=.\data_xfer8.cpp
# End Source File
# Begin Source File

SOURCE=.\debugstuff.cpp
# End Source File
# Begin Source File

SOURCE=.\exception.cpp
# End Source File
# Begin Source File

SOURCE=.\extdb.cpp
# End Source File
# Begin Source File

SOURCE=.\fetchdecode.cpp
# End Source File
# Begin Source File

SOURCE=.\fetchdecode64.cpp
# End Source File
# Begin Source File

SOURCE=.\flag_ctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\flag_ctrl_pro.cpp
# End Source File
# Begin Source File

SOURCE=.\fpu_emu.cpp
# End Source File
# Begin Source File

SOURCE=.\init.cpp
# End Source File
# Begin Source File

SOURCE=.\io.cpp
# End Source File
# Begin Source File

SOURCE=.\io_pro.cpp
# End Source File
# Begin Source File

SOURCE=.\lazy_flags.cpp
# End Source File
# Begin Source File

SOURCE=.\logical16.cpp
# End Source File
# Begin Source File

SOURCE=.\logical32.cpp
# End Source File
# Begin Source File

SOURCE=.\logical64.cpp
# End Source File
# Begin Source File

SOURCE=.\logical8.cpp
# End Source File
# Begin Source File

SOURCE=.\mmx.cpp
# End Source File
# Begin Source File

SOURCE=.\mult16.cpp
# End Source File
# Begin Source File

SOURCE=.\mult32.cpp
# End Source File
# Begin Source File

SOURCE=.\mult64.cpp
# End Source File
# Begin Source File

SOURCE=.\mult8.cpp
# End Source File
# Begin Source File

SOURCE=.\paging.cpp
# End Source File
# Begin Source File

SOURCE=.\proc_ctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\protect_ctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\smm.cpp
# End Source File
# Begin Source File

SOURCE=.\resolve16.cpp
# End Source File
# Begin Source File

SOURCE=.\resolve32.cpp
# End Source File
# Begin Source File

SOURCE=.\resolve64.cpp
# End Source File
# Begin Source File

SOURCE=.\segment_ctrl.cpp
# End Source File
# Begin Source File

SOURCE=.\segment_ctrl_pro.cpp
# End Source File
# Begin Source File

SOURCE=.\shift16.cpp
# End Source File
# Begin Source File

SOURCE=.\shift32.cpp
# End Source File
# Begin Source File

SOURCE=.\shift64.cpp
# End Source File
# Begin Source File

SOURCE=.\shift8.cpp
# End Source File
# Begin Source File

SOURCE=.\soft_int.cpp
# End Source File
# Begin Source File

SOURCE=.\sse.cpp
# End Source File
# Begin Source File

SOURCE=.\sse_move.cpp
# End Source File
# Begin Source File

SOURCE=.\sse_pfp.cpp
# End Source File
# Begin Source File

SOURCE=.\sse_rcp.cpp
# End Source File
# Begin Source File

SOURCE=.\stack16.cpp
# End Source File
# Begin Source File

SOURCE=.\stack32.cpp
# End Source File
# Begin Source File

SOURCE=.\stack64.cpp
# End Source File
# Begin Source File

SOURCE=.\stack_pro.cpp
# End Source File
# Begin Source File

SOURCE=.\string.cpp
# End Source File
# Begin Source File

SOURCE=.\tasking.cpp
# End Source File
# Begin Source File

SOURCE=.\vm8086.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\bochs.h
# End Source File
# Begin Source File

SOURCE=..\config.h
# End Source File
# Begin Source File

SOURCE=.\cpu.h
# End Source File
# Begin Source File

SOURCE=.\lazy_flags.h
# End Source File
# End Group
# End Target
# End Project
