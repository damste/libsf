# Microsoft Developer Studio Project File - Name="iodev" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=iodev - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "iodev.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "iodev.mak" CFG="iodev - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "iodev - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "iodev - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "iodev - Win32 Release"

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

!ELSEIF  "$(CFG)" == "iodev - Win32 Debug"

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
# ADD CPP /nologo /MTd /W3 /GX /Z7 /Od /I ".." /I "../instrument/stubs" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NDEBUG" /D "_WINDOWS" /YX /FD /TP /c
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

# Name "iodev - Win32 Release"
# Name "iodev - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\acpi.cpp
# End Source File
# Begin Source File

SOURCE=.\biosdev.cpp
# End Source File
# Begin Source File

SOURCE=.\busmouse.cpp
# End Source File
# Begin Source File

SOURCE=.\cdrom.cpp
# End Source File
# Begin Source File

SOURCE=.\cmos.cpp
# End Source File
# Begin Source File

SOURCE=.\crc32.cpp
# End Source File
# Begin Source File

SOURCE=.\devices.cpp
# End Source File
# Begin Source File

SOURCE=.\dma.cpp
# End Source File
# Begin Source File

SOURCE=.\eth.cpp
# End Source File
# Begin Source File

SOURCE=.\eth_arpback.cpp
# End Source File
# Begin Source File

SOURCE=.\eth_fbsd.cpp
# End Source File
# Begin Source File

SOURCE=.\eth_linux.cpp
# End Source File
# Begin Source File

SOURCE=.\eth_null.cpp
# End Source File
# Begin Source File

SOURCE=.\eth_packetmaker.cpp
# End Source File
# Begin Source File

SOURCE=.\eth_vnet.cpp
# End Source File
# Begin Source File

SOURCE=.\eth_win32.cpp
# End Source File
# Begin Source File

SOURCE=.\extfpuirq.cpp
# End Source File
# Begin Source File

SOURCE=.\floppy.cpp
# End Source File
# Begin Source File

SOURCE=.\gameport.cpp
# End Source File
# Begin Source File

SOURCE=.\harddrv.cpp
# End Source File
# Begin Source File

SOURCE=.\hdimage.cpp
# End Source File
# Begin Source File

SOURCE=.\ioapic.cpp
# End Source File
# Begin Source File

SOURCE=.\iodebug.cpp
# End Source File
# Begin Source File

SOURCE=.\keyboard.cpp
# End Source File
# Begin Source File

SOURCE=.\ne2k.cpp
# End Source File
# Begin Source File

SOURCE=.\parallel.cpp
# End Source File
# Begin Source File

SOURCE=.\pci.cpp
# End Source File
# Begin Source File

SOURCE=.\pci2isa.cpp
# End Source File
# Begin Source File

SOURCE=.\pci_ide.cpp
# End Source File
# Begin Source File

SOURCE=.\pcidev.cpp
# End Source File
# Begin Source File

SOURCE=.\pcipnic.cpp
# End Source File
# Begin Source File

SOURCE=.\pciusb.cpp
# End Source File
# Begin Source File

SOURCE=.\pcivga.cpp
# End Source File
# Begin Source File

SOURCE=.\pic.cpp
# End Source File
# Begin Source File

SOURCE=.\pit82c54.cpp
# End Source File
# Begin Source File

SOURCE=.\pit_wrap.cpp
# End Source File
# Begin Source File

SOURCE=.\sb16.cpp
# End Source File
# Begin Source File

SOURCE=.\scancodes.cpp
# End Source File
# Begin Source File

SOURCE=.\scsi_device.cpp
# End Source File
# Begin Source File

SOURCE=.\serial.cpp
# End Source File
# Begin Source File

SOURCE=.\serial_raw.cpp
# End Source File
# Begin Source File

SOURCE=.\slowdown_timer.cpp
# End Source File
# Begin Source File

SOURCE=.\soundlnx.cpp
# End Source File
# Begin Source File

SOURCE=.\soundosx.cpp
# End Source File
# Begin Source File

SOURCE=.\soundwin.cpp
# End Source File
# Begin Source File

SOURCE=.\speaker.cpp
# End Source File
# Begin Source File

SOURCE=.\svga_cirrus.cpp
# End Source File
# Begin Source File

SOURCE=.\unmapped.cpp
# End Source File
# Begin Source File

SOURCE=.\usb_hid.cpp
# End Source File
# Begin Source File

SOURCE=.\usb_msd.cpp
# End Source File
# Begin Source File

SOURCE=.\vga.cpp
# End Source File
# Begin Source File

SOURCE=.\virt_timer.cpp
# End Source File
# Begin Source File

SOURCE=.\vmware3.cpp
# End Source File
# Begin Source File

SOURCE=.\vmware4.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\acpi.h
# End Source File
# Begin Source File

SOURCE=.\cdrom.h
# End Source File
# Begin Source File

SOURCE=.\cmos.h
# End Source File
# Begin Source File

SOURCE=.\dma.h
# End Source File
# Begin Source File

SOURCE=.\eth.h
# End Source File
# Begin Source File

SOURCE=.\floppy.h
# End Source File
# Begin Source File

SOURCE=.\gameport.h
# End Source File
# Begin Source File

SOURCE=.\harddrv.h
# End Source File
# Begin Source File

SOURCE=.\hdimage.h
# End Source File
# Begin Source File

SOURCE=.\iodev.h
# End Source File
# Begin Source File

SOURCE=.\keyboard.h
# End Source File
# Begin Source File

SOURCE=.\ne2k.h
# End Source File
# Begin Source File

SOURCE=.\parallel.h
# End Source File
# Begin Source File

SOURCE=.\pci.h
# End Source File
# Begin Source File

SOURCE=.\pci2isa.h
# End Source File
# Begin Source File

SOURCE=.\pci_ide.h
# End Source File
# Begin Source File

SOURCE=.\pcipnic.h
# End Source File
# Begin Source File

SOURCE=.\pciusb.h
# End Source File
# Begin Source File

SOURCE=.\pcivga.h
# End Source File
# Begin Source File

SOURCE=.\pic.h
# End Source File
# Begin Source File

SOURCE=.\pit82c54.h
# End Source File
# Begin Source File

SOURCE=.\pit_wrap.h
# End Source File
# Begin Source File

SOURCE=.\sb16.h
# End Source File
# Begin Source File

SOURCE=.\scsi_device.h
# End Source File
# Begin Source File

SOURCE=.\serial.h
# End Source File
# Begin Source File

SOURCE=.\soundwin.h
# End Source File
# Begin Source File

SOURCE=.\unmapped.h
# End Source File
# Begin Source File

SOURCE=.\usb_hid.h
# End Source File
# Begin Source File

SOURCE=.\usb_msd.h
# End Source File
# Begin Source File

SOURCE=.\vga.h
# End Source File
# Begin Source File

SOURCE=.\vmware3.h
# End Source File
# Begin Source File

SOURCE=.\vmware4.h
# End Source File
# End Group
# End Target
# End Project
