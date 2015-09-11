# Microsoft Developer Studio Project File - Name="fpu" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=fpu - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "fpu.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "fpu.mak" CFG="fpu - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "fpu - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "fpu - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "fpu - Win32 Release"

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
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".." /I "../instrument/stubs" /I "stubs" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "PARANOID" /D "DEBUGGING" /D "NO_ASSEMBLER" /D "USE_WITH_CPU_SIM" /YX /FD /TP /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "fpu - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /GX /Z7 /Od /I ".." /I "../instrument/stubs" /I "./stubs" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NDEBUG" /D "_WINDOWS" /D "PARANOID" /D "DEBUGGING" /D "NO_ASSEMBLER" /D "USE_WITH_CPU_SIM" /YX /FD /TP /c
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

# Name "fpu - Win32 Release"
# Name "fpu - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\f2xm1.cpp
# End Source File
# Begin Source File

SOURCE=.\ferr.cpp
# End Source File
# Begin Source File

SOURCE=.\fpatan.cpp
# End Source File
# Begin Source File

SOURCE=.\fprem.cpp
# End Source File
# Begin Source File

SOURCE=.\fpu.cpp
# End Source File
# Begin Source File

SOURCE=.\fpu_arith.cpp
# End Source File
# Begin Source File

SOURCE=.\fpu_compare.cpp
# End Source File
# Begin Source File

SOURCE=.\fpu_const.cpp
# End Source File
# Begin Source File

SOURCE=.\fpu_load_store.cpp
# End Source File
# Begin Source File

SOURCE=.\fpu_misc.cpp
# End Source File
# Begin Source File

SOURCE=.\fpu_tags.cpp
# End Source File
# Begin Source File

SOURCE=.\fpu_trans.cpp
# End Source File
# Begin Source File

SOURCE=.\fsincos.cpp
# End Source File
# Begin Source File

SOURCE=.\fyl2x.cpp
# End Source File
# Begin Source File

SOURCE=.\poly.cpp
# End Source File
# Begin Source File

SOURCE=".\softfloat-round-pack.cpp"
# End Source File
# Begin Source File

SOURCE=".\softfloat-specialize.cpp"
# End Source File
# Begin Source File

SOURCE=.\softfloat.cpp
# End Source File
# Begin Source File

SOURCE=.\softfloatx80.cpp
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

SOURCE=.\control_w.h
# End Source File
# Begin Source File

SOURCE=.\exception.h
# End Source File
# Begin Source File

SOURCE=.\fpu_asm.h
# End Source File
# Begin Source File

SOURCE=.\fpu_emu.h
# End Source File
# Begin Source File

SOURCE=.\fpu_proto.h
# End Source File
# Begin Source File

SOURCE=.\fpu_system.h
# End Source File
# Begin Source File

SOURCE=.\poly.h
# End Source File
# Begin Source File

SOURCE=.\reg_constant.h
# End Source File
# End Group
# End Target
# End Project
