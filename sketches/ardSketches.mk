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
Date                   :=11/10/18
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
Objects0=$(IntermediateDirectory)/tests_main.cpp$(ObjectSuffix) $(IntermediateDirectory)/bug-cam_InputValues.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/tests_main.cpp$(ObjectSuffix): tests/main.cpp $(IntermediateDirectory)/tests_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/tests/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/tests_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/tests_main.cpp$(DependSuffix): tests/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/tests_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/tests_main.cpp$(DependSuffix) -MM "tests/main.cpp"

$(IntermediateDirectory)/tests_main.cpp$(PreprocessSuffix): tests/main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/tests_main.cpp$(PreprocessSuffix) "tests/main.cpp"

$(IntermediateDirectory)/bug-cam_InputValues.cpp$(ObjectSuffix): bug-cam/InputValues.cpp $(IntermediateDirectory)/bug-cam_InputValues.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/bug-cam/InputValues.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/bug-cam_InputValues.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/bug-cam_InputValues.cpp$(DependSuffix): bug-cam/InputValues.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/bug-cam_InputValues.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/bug-cam_InputValues.cpp$(DependSuffix) -MM "bug-cam/InputValues.cpp"

$(IntermediateDirectory)/bug-cam_InputValues.cpp$(PreprocessSuffix): bug-cam/InputValues.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/bug-cam_InputValues.cpp$(PreprocessSuffix) "bug-cam/InputValues.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


