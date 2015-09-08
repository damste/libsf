#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=cc
CCC=CC
CXX=CC
FC=f95

# Macros
PLATFORM=SunStudio_12.1-Solaris-x86

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Release/${PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/libsf/source/vjr/projects/sunStudio2009/vjr/../../../source/vjr.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/${PLATFORM}/vjr

dist/Release/${PLATFORM}/vjr: ${OBJECTFILES}
	${MKDIR} -p dist/Release/${PLATFORM}
	${LINK.cc} -o dist/Release/${PLATFORM}/vjr ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/_ext/libsf/source/vjr/projects/sunStudio2009/vjr/../../../source/vjr.o: ../../../source/vjr.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/libsf/source/vjr/projects/sunStudio2009/vjr/../../../source
	$(COMPILE.cc) -fast -o ${OBJECTDIR}/_ext/libsf/source/vjr/projects/sunStudio2009/vjr/../../../source/vjr.o ../../../source/vjr.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/${PLATFORM}/vjr
	${CCADMIN} -clean

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
