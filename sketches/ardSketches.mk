##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=ardSketches
ConfigurationName      :=Debug
WorkspacePath          := "/home/robot1/Source/robot1/sketches"
ProjectPath            := "/home/robot1/Source/robot1/sketches"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=robot1
Date                   :=13/10/18
CodeLitePath           :="/home/robot1/.codelite"
LinkerName             :=/usr/bin/avr-g++
SharedObjectLinkerName :=/usr/bin/avr-g++ -shared -fPIC
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
OutputFile             :=$(IntermediateDirectory)/lib$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="ardSketches.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/avr-ar rcu
CXX      := /usr/bin/avr-g++
CC       := /usr/bin/avr-gcc
CXXFLAGS :=  -g $(Preprocessors)
CFLAGS   :=  -g $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/avr-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/bug-cam_InputValues.cpp$(ObjectSuffix) $(IntermediateDirectory)/cmake-build-debug_turretFreeRtos_turretFreeRtos.ino.cpp$(ObjectSuffix) $(IntermediateDirectory)/CMakeFiles_feature_tests.cxx$(ObjectSuffix) $(IntermediateDirectory)/CMakeFiles_feature_tests.c$(ObjectSuffix) $(IntermediateDirectory)/CompilerIdC_CMakeCCompilerId.c$(ObjectSuffix) $(IntermediateDirectory)/CompilerIdCXX_CMakeCXXCompilerId.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "/home/robot1/Source/robot1/sketches/.build-debug"
	@echo rebuilt > "/home/robot1/Source/robot1/sketches/.build-debug/ardSketches"

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


./Debug:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/bug-cam_InputValues.cpp$(ObjectSuffix): bug-cam/InputValues.cpp $(IntermediateDirectory)/bug-cam_InputValues.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/bug-cam/InputValues.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/bug-cam_InputValues.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/bug-cam_InputValues.cpp$(DependSuffix): bug-cam/InputValues.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/bug-cam_InputValues.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/bug-cam_InputValues.cpp$(DependSuffix) -MM "bug-cam/InputValues.cpp"

$(IntermediateDirectory)/bug-cam_InputValues.cpp$(PreprocessSuffix): bug-cam/InputValues.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/bug-cam_InputValues.cpp$(PreprocessSuffix) "bug-cam/InputValues.cpp"

$(IntermediateDirectory)/cmake-build-debug_turretFreeRtos_turretFreeRtos.ino.cpp$(ObjectSuffix): turretFreeRtos/cmake-build-debug/turretFreeRtos_turretFreeRtos.ino.cpp $(IntermediateDirectory)/cmake-build-debug_turretFreeRtos_turretFreeRtos.ino.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/turretFreeRtos/cmake-build-debug/turretFreeRtos_turretFreeRtos.ino.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/cmake-build-debug_turretFreeRtos_turretFreeRtos.ino.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/cmake-build-debug_turretFreeRtos_turretFreeRtos.ino.cpp$(DependSuffix): turretFreeRtos/cmake-build-debug/turretFreeRtos_turretFreeRtos.ino.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/cmake-build-debug_turretFreeRtos_turretFreeRtos.ino.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/cmake-build-debug_turretFreeRtos_turretFreeRtos.ino.cpp$(DependSuffix) -MM "turretFreeRtos/cmake-build-debug/turretFreeRtos_turretFreeRtos.ino.cpp"

$(IntermediateDirectory)/cmake-build-debug_turretFreeRtos_turretFreeRtos.ino.cpp$(PreprocessSuffix): turretFreeRtos/cmake-build-debug/turretFreeRtos_turretFreeRtos.ino.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/cmake-build-debug_turretFreeRtos_turretFreeRtos.ino.cpp$(PreprocessSuffix) "turretFreeRtos/cmake-build-debug/turretFreeRtos_turretFreeRtos.ino.cpp"

$(IntermediateDirectory)/CMakeFiles_feature_tests.cxx$(ObjectSuffix): turretFreeRtos/cmake-build-debug/CMakeFiles/feature_tests.cxx $(IntermediateDirectory)/CMakeFiles_feature_tests.cxx$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/turretFreeRtos/cmake-build-debug/CMakeFiles/feature_tests.cxx" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CMakeFiles_feature_tests.cxx$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CMakeFiles_feature_tests.cxx$(DependSuffix): turretFreeRtos/cmake-build-debug/CMakeFiles/feature_tests.cxx
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CMakeFiles_feature_tests.cxx$(ObjectSuffix) -MF$(IntermediateDirectory)/CMakeFiles_feature_tests.cxx$(DependSuffix) -MM "turretFreeRtos/cmake-build-debug/CMakeFiles/feature_tests.cxx"

$(IntermediateDirectory)/CMakeFiles_feature_tests.cxx$(PreprocessSuffix): turretFreeRtos/cmake-build-debug/CMakeFiles/feature_tests.cxx
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CMakeFiles_feature_tests.cxx$(PreprocessSuffix) "turretFreeRtos/cmake-build-debug/CMakeFiles/feature_tests.cxx"

$(IntermediateDirectory)/CMakeFiles_feature_tests.c$(ObjectSuffix): turretFreeRtos/cmake-build-debug/CMakeFiles/feature_tests.c $(IntermediateDirectory)/CMakeFiles_feature_tests.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/turretFreeRtos/cmake-build-debug/CMakeFiles/feature_tests.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CMakeFiles_feature_tests.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CMakeFiles_feature_tests.c$(DependSuffix): turretFreeRtos/cmake-build-debug/CMakeFiles/feature_tests.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CMakeFiles_feature_tests.c$(ObjectSuffix) -MF$(IntermediateDirectory)/CMakeFiles_feature_tests.c$(DependSuffix) -MM "turretFreeRtos/cmake-build-debug/CMakeFiles/feature_tests.c"

$(IntermediateDirectory)/CMakeFiles_feature_tests.c$(PreprocessSuffix): turretFreeRtos/cmake-build-debug/CMakeFiles/feature_tests.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CMakeFiles_feature_tests.c$(PreprocessSuffix) "turretFreeRtos/cmake-build-debug/CMakeFiles/feature_tests.c"

$(IntermediateDirectory)/CompilerIdC_CMakeCCompilerId.c$(ObjectSuffix): turretFreeRtos/cmake-build-debug/CMakeFiles/3.10.3/CompilerIdC/CMakeCCompilerId.c $(IntermediateDirectory)/CompilerIdC_CMakeCCompilerId.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/turretFreeRtos/cmake-build-debug/CMakeFiles/3.10.3/CompilerIdC/CMakeCCompilerId.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CompilerIdC_CMakeCCompilerId.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CompilerIdC_CMakeCCompilerId.c$(DependSuffix): turretFreeRtos/cmake-build-debug/CMakeFiles/3.10.3/CompilerIdC/CMakeCCompilerId.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CompilerIdC_CMakeCCompilerId.c$(ObjectSuffix) -MF$(IntermediateDirectory)/CompilerIdC_CMakeCCompilerId.c$(DependSuffix) -MM "turretFreeRtos/cmake-build-debug/CMakeFiles/3.10.3/CompilerIdC/CMakeCCompilerId.c"

$(IntermediateDirectory)/CompilerIdC_CMakeCCompilerId.c$(PreprocessSuffix): turretFreeRtos/cmake-build-debug/CMakeFiles/3.10.3/CompilerIdC/CMakeCCompilerId.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CompilerIdC_CMakeCCompilerId.c$(PreprocessSuffix) "turretFreeRtos/cmake-build-debug/CMakeFiles/3.10.3/CompilerIdC/CMakeCCompilerId.c"

$(IntermediateDirectory)/CompilerIdCXX_CMakeCXXCompilerId.cpp$(ObjectSuffix): turretFreeRtos/cmake-build-debug/CMakeFiles/3.10.3/CompilerIdCXX/CMakeCXXCompilerId.cpp $(IntermediateDirectory)/CompilerIdCXX_CMakeCXXCompilerId.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/turretFreeRtos/cmake-build-debug/CMakeFiles/3.10.3/CompilerIdCXX/CMakeCXXCompilerId.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CompilerIdCXX_CMakeCXXCompilerId.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CompilerIdCXX_CMakeCXXCompilerId.cpp$(DependSuffix): turretFreeRtos/cmake-build-debug/CMakeFiles/3.10.3/CompilerIdCXX/CMakeCXXCompilerId.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CompilerIdCXX_CMakeCXXCompilerId.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CompilerIdCXX_CMakeCXXCompilerId.cpp$(DependSuffix) -MM "turretFreeRtos/cmake-build-debug/CMakeFiles/3.10.3/CompilerIdCXX/CMakeCXXCompilerId.cpp"

$(IntermediateDirectory)/CompilerIdCXX_CMakeCXXCompilerId.cpp$(PreprocessSuffix): turretFreeRtos/cmake-build-debug/CMakeFiles/3.10.3/CompilerIdCXX/CMakeCXXCompilerId.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CompilerIdCXX_CMakeCXXCompilerId.cpp$(PreprocessSuffix) "turretFreeRtos/cmake-build-debug/CMakeFiles/3.10.3/CompilerIdCXX/CMakeCXXCompilerId.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


