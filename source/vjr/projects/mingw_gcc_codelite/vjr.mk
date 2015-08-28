##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=vjr
ConfigurationName      :=Debug
WorkspacePath          := "C:\libsf\source\vjr\projects\mingw_gcc_codelite"
ProjectPath            := "C:\libsf\source\vjr\projects\mingw_gcc_codelite"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=rhodgin
Date                   :=28/08/2015
CodeLitePath           :="C:\Program Files (x86)\CodeLite"
LinkerName             :=C:/MinGW_old/MinGW/bin/g++.exe
SharedObjectLinkerName :=C:/MinGW_old/MinGW/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=c:/libsf_offline/source/vjr/bin/32-bit/vjr_gcc_32.exe
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="vjr.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/MinGW_old/MinGW/bin/windres.exe
LinkOptions            :=  -g
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)C:/libsf/source/vjr/projects/vs2010/ 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)kernel32 $(LibrarySwitch)user32 $(LibrarySwitch)gdi32 $(LibrarySwitch)winspool $(LibrarySwitch)comdlg32 $(LibrarySwitch)advapi32 $(LibrarySwitch)shell32 $(LibrarySwitch)ole32 $(LibrarySwitch)oleaut32 $(LibrarySwitch)uuid $(LibrarySwitch)odbc32 $(LibrarySwitch)odbccp32 $(LibrarySwitch)SDL $(LibrarySwitch)glew32 $(LibrarySwitch)glew32s $(LibrarySwitch)freeglut $(LibrarySwitch)freeglut_static $(LibrarySwitch)glu32 $(LibrarySwitch)opengl32 
ArLibs                 :=  "kernel32" "user32" "gdi32" "winspool" "comdlg32" "advapi32" "shell32" "ole32" "oleaut32" "uuid" "odbc32" "odbccp32" "SDL" "glew32" "glew32s" "freeglut" "freeglut_static" "glu32" "opengl32" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)C:/libsf/source/vjr/projects/mingw_gcc_codelite/lib32/ 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/MinGW_old/MinGW/bin/ar.exe rcu
CXX      := C:/MinGW_old/MinGW/bin/g++.exe
CC       := C:/MinGW_old/MinGW/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall -Wno-comment -Wno-multichar -Wno-narrowing -Wno-write-strings -Wno-format-contains-nul -Wno-reorder -Wno-strict-aliasing -Wno-char-subscripts -Wno-unused-variable $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall -Wno-comment -Wno-multichar -Wno-narrowing -Wno-write-strings -Wno-format-contains-nul -Wno-strict-aliasing -Wno-char-subscripts $(Preprocessors)
ASFLAGS  := 
AS       := C:/MinGW_old/MinGW/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files (x86)\CodeLite
UNIT_TEST_PP_SRC_DIR:=C:\UnitTest++-1.3
Objects0=$(IntermediateDirectory)/source_vjr.cpp$(ObjectSuffix) $(IntermediateDirectory)/bmps_bmps.cpp$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_add.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_cpi.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_div.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_exp.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_fam.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_fft.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_flr.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_fpf.c$(ObjectSuffix) \
	$(IntermediateDirectory)/mapm_mapm_gcd.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_lg2.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_lg3.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_lg4.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_log.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_mul.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_pow.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_rcp.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_rnd.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm_set.c$(ObjectSuffix) \
	$(IntermediateDirectory)/mapm_mapm_sin.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapm5sin.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmasin.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmasn0.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmcbrt.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmcnst.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmfact.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmfmul.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmgues.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmhasn.c$(ObjectSuffix) \
	$(IntermediateDirectory)/mapm_mapmhsin.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmipwr.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmistr.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmpwr2.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmrsin.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmsqrt.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmstck.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmutil.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmutl1.c$(ObjectSuffix) $(IntermediateDirectory)/mapm_mapmutl2.c$(ObjectSuffix) \
	



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/source_vjr.cpp$(ObjectSuffix): ../../source/vjr.cpp $(IntermediateDirectory)/source_vjr.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/libsf/source/vjr/source/vjr.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/source_vjr.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_vjr.cpp$(DependSuffix): ../../source/vjr.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/source_vjr.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/source_vjr.cpp$(DependSuffix) -MM "../../source/vjr.cpp"

$(IntermediateDirectory)/source_vjr.cpp$(PreprocessSuffix): ../../source/vjr.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_vjr.cpp$(PreprocessSuffix) "../../source/vjr.cpp"

$(IntermediateDirectory)/bmps_bmps.cpp$(ObjectSuffix): ../../source/bmps/bmps.cpp $(IntermediateDirectory)/bmps_bmps.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/libsf/source/vjr/source/bmps/bmps.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/bmps_bmps.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/bmps_bmps.cpp$(DependSuffix): ../../source/bmps/bmps.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/bmps_bmps.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/bmps_bmps.cpp$(DependSuffix) -MM "../../source/bmps/bmps.cpp"

$(IntermediateDirectory)/bmps_bmps.cpp$(PreprocessSuffix): ../../source/bmps/bmps.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/bmps_bmps.cpp$(PreprocessSuffix) "../../source/bmps/bmps.cpp"

$(IntermediateDirectory)/mapm_mapm_add.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_add.c $(IntermediateDirectory)/mapm_mapm_add.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_add.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_add.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_add.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_add.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_add.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_add.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_add.c"

$(IntermediateDirectory)/mapm_mapm_add.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_add.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_add.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_add.c"

$(IntermediateDirectory)/mapm_mapm_cpi.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_cpi.c $(IntermediateDirectory)/mapm_mapm_cpi.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_cpi.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_cpi.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_cpi.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_cpi.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_cpi.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_cpi.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_cpi.c"

$(IntermediateDirectory)/mapm_mapm_cpi.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_cpi.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_cpi.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_cpi.c"

$(IntermediateDirectory)/mapm_mapm_div.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_div.c $(IntermediateDirectory)/mapm_mapm_div.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_div.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_div.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_div.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_div.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_div.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_div.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_div.c"

$(IntermediateDirectory)/mapm_mapm_div.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_div.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_div.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_div.c"

$(IntermediateDirectory)/mapm_mapm_exp.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_exp.c $(IntermediateDirectory)/mapm_mapm_exp.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_exp.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_exp.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_exp.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_exp.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_exp.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_exp.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_exp.c"

$(IntermediateDirectory)/mapm_mapm_exp.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_exp.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_exp.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_exp.c"

$(IntermediateDirectory)/mapm_mapm_fam.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_fam.c $(IntermediateDirectory)/mapm_mapm_fam.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_fam.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_fam.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_fam.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_fam.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_fam.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_fam.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_fam.c"

$(IntermediateDirectory)/mapm_mapm_fam.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_fam.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_fam.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_fam.c"

$(IntermediateDirectory)/mapm_mapm_fft.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_fft.c $(IntermediateDirectory)/mapm_mapm_fft.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_fft.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_fft.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_fft.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_fft.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_fft.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_fft.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_fft.c"

$(IntermediateDirectory)/mapm_mapm_fft.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_fft.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_fft.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_fft.c"

$(IntermediateDirectory)/mapm_mapm_flr.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_flr.c $(IntermediateDirectory)/mapm_mapm_flr.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_flr.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_flr.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_flr.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_flr.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_flr.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_flr.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_flr.c"

$(IntermediateDirectory)/mapm_mapm_flr.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_flr.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_flr.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_flr.c"

$(IntermediateDirectory)/mapm_mapm_fpf.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_fpf.c $(IntermediateDirectory)/mapm_mapm_fpf.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_fpf.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_fpf.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_fpf.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_fpf.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_fpf.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_fpf.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_fpf.c"

$(IntermediateDirectory)/mapm_mapm_fpf.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_fpf.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_fpf.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_fpf.c"

$(IntermediateDirectory)/mapm_mapm_gcd.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_gcd.c $(IntermediateDirectory)/mapm_mapm_gcd.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_gcd.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_gcd.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_gcd.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_gcd.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_gcd.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_gcd.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_gcd.c"

$(IntermediateDirectory)/mapm_mapm_gcd.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_gcd.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_gcd.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_gcd.c"

$(IntermediateDirectory)/mapm_mapm_lg2.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_lg2.c $(IntermediateDirectory)/mapm_mapm_lg2.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_lg2.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_lg2.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_lg2.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_lg2.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_lg2.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_lg2.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_lg2.c"

$(IntermediateDirectory)/mapm_mapm_lg2.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_lg2.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_lg2.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_lg2.c"

$(IntermediateDirectory)/mapm_mapm_lg3.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_lg3.c $(IntermediateDirectory)/mapm_mapm_lg3.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_lg3.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_lg3.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_lg3.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_lg3.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_lg3.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_lg3.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_lg3.c"

$(IntermediateDirectory)/mapm_mapm_lg3.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_lg3.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_lg3.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_lg3.c"

$(IntermediateDirectory)/mapm_mapm_lg4.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_lg4.c $(IntermediateDirectory)/mapm_mapm_lg4.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_lg4.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_lg4.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_lg4.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_lg4.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_lg4.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_lg4.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_lg4.c"

$(IntermediateDirectory)/mapm_mapm_lg4.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_lg4.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_lg4.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_lg4.c"

$(IntermediateDirectory)/mapm_mapm_log.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_log.c $(IntermediateDirectory)/mapm_mapm_log.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_log.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_log.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_log.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_log.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_log.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_log.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_log.c"

$(IntermediateDirectory)/mapm_mapm_log.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_log.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_log.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_log.c"

$(IntermediateDirectory)/mapm_mapm_mul.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_mul.c $(IntermediateDirectory)/mapm_mapm_mul.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_mul.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_mul.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_mul.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_mul.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_mul.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_mul.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_mul.c"

$(IntermediateDirectory)/mapm_mapm_mul.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_mul.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_mul.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_mul.c"

$(IntermediateDirectory)/mapm_mapm_pow.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_pow.c $(IntermediateDirectory)/mapm_mapm_pow.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_pow.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_pow.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_pow.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_pow.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_pow.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_pow.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_pow.c"

$(IntermediateDirectory)/mapm_mapm_pow.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_pow.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_pow.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_pow.c"

$(IntermediateDirectory)/mapm_mapm_rcp.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_rcp.c $(IntermediateDirectory)/mapm_mapm_rcp.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_rcp.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_rcp.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_rcp.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_rcp.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_rcp.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_rcp.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_rcp.c"

$(IntermediateDirectory)/mapm_mapm_rcp.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_rcp.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_rcp.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_rcp.c"

$(IntermediateDirectory)/mapm_mapm_rnd.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_rnd.c $(IntermediateDirectory)/mapm_mapm_rnd.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_rnd.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_rnd.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_rnd.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_rnd.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_rnd.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_rnd.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_rnd.c"

$(IntermediateDirectory)/mapm_mapm_rnd.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_rnd.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_rnd.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_rnd.c"

$(IntermediateDirectory)/mapm_mapm_set.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_set.c $(IntermediateDirectory)/mapm_mapm_set.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_set.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_set.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_set.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_set.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_set.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_set.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_set.c"

$(IntermediateDirectory)/mapm_mapm_set.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_set.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_set.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_set.c"

$(IntermediateDirectory)/mapm_mapm_sin.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm_sin.c $(IntermediateDirectory)/mapm_mapm_sin.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm_sin.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm_sin.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm_sin.c$(DependSuffix): ../../source/3rd_party/mapm/mapm_sin.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm_sin.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm_sin.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm_sin.c"

$(IntermediateDirectory)/mapm_mapm_sin.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm_sin.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm_sin.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm_sin.c"

$(IntermediateDirectory)/mapm_mapm5sin.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapm5sin.c $(IntermediateDirectory)/mapm_mapm5sin.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapm5sin.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapm5sin.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapm5sin.c$(DependSuffix): ../../source/3rd_party/mapm/mapm5sin.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapm5sin.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapm5sin.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapm5sin.c"

$(IntermediateDirectory)/mapm_mapm5sin.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapm5sin.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapm5sin.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapm5sin.c"

$(IntermediateDirectory)/mapm_mapmasin.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmasin.c $(IntermediateDirectory)/mapm_mapmasin.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmasin.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmasin.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmasin.c$(DependSuffix): ../../source/3rd_party/mapm/mapmasin.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmasin.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmasin.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmasin.c"

$(IntermediateDirectory)/mapm_mapmasin.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmasin.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmasin.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmasin.c"

$(IntermediateDirectory)/mapm_mapmasn0.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmasn0.c $(IntermediateDirectory)/mapm_mapmasn0.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmasn0.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmasn0.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmasn0.c$(DependSuffix): ../../source/3rd_party/mapm/mapmasn0.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmasn0.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmasn0.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmasn0.c"

$(IntermediateDirectory)/mapm_mapmasn0.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmasn0.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmasn0.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmasn0.c"

$(IntermediateDirectory)/mapm_mapmcbrt.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmcbrt.c $(IntermediateDirectory)/mapm_mapmcbrt.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmcbrt.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmcbrt.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmcbrt.c$(DependSuffix): ../../source/3rd_party/mapm/mapmcbrt.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmcbrt.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmcbrt.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmcbrt.c"

$(IntermediateDirectory)/mapm_mapmcbrt.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmcbrt.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmcbrt.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmcbrt.c"

$(IntermediateDirectory)/mapm_mapmcnst.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmcnst.c $(IntermediateDirectory)/mapm_mapmcnst.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmcnst.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmcnst.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmcnst.c$(DependSuffix): ../../source/3rd_party/mapm/mapmcnst.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmcnst.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmcnst.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmcnst.c"

$(IntermediateDirectory)/mapm_mapmcnst.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmcnst.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmcnst.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmcnst.c"

$(IntermediateDirectory)/mapm_mapmfact.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmfact.c $(IntermediateDirectory)/mapm_mapmfact.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmfact.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmfact.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmfact.c$(DependSuffix): ../../source/3rd_party/mapm/mapmfact.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmfact.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmfact.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmfact.c"

$(IntermediateDirectory)/mapm_mapmfact.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmfact.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmfact.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmfact.c"

$(IntermediateDirectory)/mapm_mapmfmul.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmfmul.c $(IntermediateDirectory)/mapm_mapmfmul.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmfmul.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmfmul.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmfmul.c$(DependSuffix): ../../source/3rd_party/mapm/mapmfmul.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmfmul.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmfmul.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmfmul.c"

$(IntermediateDirectory)/mapm_mapmfmul.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmfmul.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmfmul.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmfmul.c"

$(IntermediateDirectory)/mapm_mapmgues.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmgues.c $(IntermediateDirectory)/mapm_mapmgues.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmgues.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmgues.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmgues.c$(DependSuffix): ../../source/3rd_party/mapm/mapmgues.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmgues.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmgues.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmgues.c"

$(IntermediateDirectory)/mapm_mapmgues.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmgues.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmgues.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmgues.c"

$(IntermediateDirectory)/mapm_mapmhasn.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmhasn.c $(IntermediateDirectory)/mapm_mapmhasn.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmhasn.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmhasn.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmhasn.c$(DependSuffix): ../../source/3rd_party/mapm/mapmhasn.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmhasn.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmhasn.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmhasn.c"

$(IntermediateDirectory)/mapm_mapmhasn.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmhasn.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmhasn.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmhasn.c"

$(IntermediateDirectory)/mapm_mapmhsin.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmhsin.c $(IntermediateDirectory)/mapm_mapmhsin.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmhsin.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmhsin.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmhsin.c$(DependSuffix): ../../source/3rd_party/mapm/mapmhsin.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmhsin.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmhsin.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmhsin.c"

$(IntermediateDirectory)/mapm_mapmhsin.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmhsin.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmhsin.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmhsin.c"

$(IntermediateDirectory)/mapm_mapmipwr.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmipwr.c $(IntermediateDirectory)/mapm_mapmipwr.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmipwr.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmipwr.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmipwr.c$(DependSuffix): ../../source/3rd_party/mapm/mapmipwr.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmipwr.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmipwr.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmipwr.c"

$(IntermediateDirectory)/mapm_mapmipwr.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmipwr.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmipwr.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmipwr.c"

$(IntermediateDirectory)/mapm_mapmistr.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmistr.c $(IntermediateDirectory)/mapm_mapmistr.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmistr.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmistr.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmistr.c$(DependSuffix): ../../source/3rd_party/mapm/mapmistr.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmistr.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmistr.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmistr.c"

$(IntermediateDirectory)/mapm_mapmistr.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmistr.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmistr.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmistr.c"

$(IntermediateDirectory)/mapm_mapmpwr2.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmpwr2.c $(IntermediateDirectory)/mapm_mapmpwr2.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmpwr2.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmpwr2.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmpwr2.c$(DependSuffix): ../../source/3rd_party/mapm/mapmpwr2.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmpwr2.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmpwr2.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmpwr2.c"

$(IntermediateDirectory)/mapm_mapmpwr2.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmpwr2.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmpwr2.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmpwr2.c"

$(IntermediateDirectory)/mapm_mapmrsin.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmrsin.c $(IntermediateDirectory)/mapm_mapmrsin.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmrsin.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmrsin.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmrsin.c$(DependSuffix): ../../source/3rd_party/mapm/mapmrsin.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmrsin.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmrsin.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmrsin.c"

$(IntermediateDirectory)/mapm_mapmrsin.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmrsin.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmrsin.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmrsin.c"

$(IntermediateDirectory)/mapm_mapmsqrt.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmsqrt.c $(IntermediateDirectory)/mapm_mapmsqrt.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmsqrt.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmsqrt.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmsqrt.c$(DependSuffix): ../../source/3rd_party/mapm/mapmsqrt.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmsqrt.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmsqrt.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmsqrt.c"

$(IntermediateDirectory)/mapm_mapmsqrt.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmsqrt.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmsqrt.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmsqrt.c"

$(IntermediateDirectory)/mapm_mapmstck.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmstck.c $(IntermediateDirectory)/mapm_mapmstck.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmstck.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmstck.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmstck.c$(DependSuffix): ../../source/3rd_party/mapm/mapmstck.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmstck.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmstck.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmstck.c"

$(IntermediateDirectory)/mapm_mapmstck.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmstck.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmstck.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmstck.c"

$(IntermediateDirectory)/mapm_mapmutil.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmutil.c $(IntermediateDirectory)/mapm_mapmutil.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmutil.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmutil.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmutil.c$(DependSuffix): ../../source/3rd_party/mapm/mapmutil.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmutil.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmutil.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmutil.c"

$(IntermediateDirectory)/mapm_mapmutil.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmutil.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmutil.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmutil.c"

$(IntermediateDirectory)/mapm_mapmutl1.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmutl1.c $(IntermediateDirectory)/mapm_mapmutl1.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmutl1.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmutl1.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmutl1.c$(DependSuffix): ../../source/3rd_party/mapm/mapmutl1.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmutl1.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmutl1.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmutl1.c"

$(IntermediateDirectory)/mapm_mapmutl1.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmutl1.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmutl1.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmutl1.c"

$(IntermediateDirectory)/mapm_mapmutl2.c$(ObjectSuffix): ../../source/3rd_party/mapm/mapmutl2.c $(IntermediateDirectory)/mapm_mapmutl2.c$(DependSuffix)
	$(CC) $(SourceSwitch) "C:/libsf/source/vjr/source/3rd_party/mapm/mapmutl2.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/mapm_mapmutl2.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/mapm_mapmutl2.c$(DependSuffix): ../../source/3rd_party/mapm/mapmutl2.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/mapm_mapmutl2.c$(ObjectSuffix) -MF$(IntermediateDirectory)/mapm_mapmutl2.c$(DependSuffix) -MM "../../source/3rd_party/mapm/mapmutl2.c"

$(IntermediateDirectory)/mapm_mapmutl2.c$(PreprocessSuffix): ../../source/3rd_party/mapm/mapmutl2.c
	@$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/mapm_mapmutl2.c$(PreprocessSuffix) "../../source/3rd_party/mapm/mapmutl2.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


