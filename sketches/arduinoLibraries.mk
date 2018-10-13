##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=arduinoLibraries
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
ObjectsFileList        :="arduinoLibraries.txt"
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
Objects0=$(IntermediateDirectory)/IRLibProtocols_IRLibSendBase.cpp$(ObjectSuffix) $(IntermediateDirectory)/IRLibProtocols_IRLibProtocols.cpp$(ObjectSuffix) $(IntermediateDirectory)/IRLibProtocols_IRLibSAMD21.cpp$(ObjectSuffix) $(IntermediateDirectory)/IRLibProtocols_IRLibHardware.cpp$(ObjectSuffix) $(IntermediateDirectory)/Firmata_FirmataMarshaller.cpp$(ObjectSuffix) $(IntermediateDirectory)/Firmata_FirmataParser.cpp$(ObjectSuffix) $(IntermediateDirectory)/Firmata_Firmata.cpp$(ObjectSuffix) $(IntermediateDirectory)/CppList_CppList.cpp$(ObjectSuffix) $(IntermediateDirectory)/HC-SR04_SR04.cpp$(ObjectSuffix) $(IntermediateDirectory)/IrSensorCluster_IrSensorCluster.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/Arduino_FreeRTOS_timers.c$(ObjectSuffix) $(IntermediateDirectory)/Arduino_FreeRTOS_heap_3.c$(ObjectSuffix) $(IntermediateDirectory)/Arduino_FreeRTOS_queue.c$(ObjectSuffix) $(IntermediateDirectory)/Arduino_FreeRTOS_tasks.c$(ObjectSuffix) $(IntermediateDirectory)/Arduino_FreeRTOS_event_groups.c$(ObjectSuffix) $(IntermediateDirectory)/Arduino_FreeRTOS_port.c$(ObjectSuffix) $(IntermediateDirectory)/Arduino_FreeRTOS_croutine.c$(ObjectSuffix) $(IntermediateDirectory)/Arduino_FreeRTOS_variantHooks.cpp$(ObjectSuffix) $(IntermediateDirectory)/Arduino_FreeRTOS_list.c$(ObjectSuffix) $(IntermediateDirectory)/Arduino_FreeRTOS_stream_buffer.c$(ObjectSuffix) \
	$(IntermediateDirectory)/DS3231_DS3231.cpp$(ObjectSuffix) $(IntermediateDirectory)/Indicator_Indicator.cpp$(ObjectSuffix) $(IntermediateDirectory)/PotMotor_PotMotor.cpp$(ObjectSuffix) $(IntermediateDirectory)/IRremote_IRremote.cpp$(ObjectSuffix) $(IntermediateDirectory)/IRremote_IrReceiver.cpp$(ObjectSuffix) $(IntermediateDirectory)/TurretControllers_TraverseController.cpp$(ObjectSuffix) $(IntermediateDirectory)/TurretControllers_TurretController.cpp$(ObjectSuffix) $(IntermediateDirectory)/utility_BLEStream.cpp$(ObjectSuffix) 

Objects1=$(IntermediateDirectory)/utility_EthernetClientStream.cpp$(ObjectSuffix) $(IntermediateDirectory)/utility_SerialFirmata.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/utility_EthernetServerStream.cpp$(ObjectSuffix) $(IntermediateDirectory)/utility_BluefruitLE_SPI_Stream.cpp$(ObjectSuffix) $(IntermediateDirectory)/utility_WiFiStream.cpp$(ObjectSuffix) 



Objects=$(Objects0) $(Objects1) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	@echo $(Objects1) >> $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "/home/robot1/Source/robot1/sketches/.build-debug"
	@echo rebuilt > "/home/robot1/Source/robot1/sketches/.build-debug/arduinoLibraries"

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


./Debug:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/IRLibProtocols_IRLibSendBase.cpp$(ObjectSuffix): libraries/IRLibProtocols/IRLibSendBase.cpp $(IntermediateDirectory)/IRLibProtocols_IRLibSendBase.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/IRLibProtocols/IRLibSendBase.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/IRLibProtocols_IRLibSendBase.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/IRLibProtocols_IRLibSendBase.cpp$(DependSuffix): libraries/IRLibProtocols/IRLibSendBase.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/IRLibProtocols_IRLibSendBase.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/IRLibProtocols_IRLibSendBase.cpp$(DependSuffix) -MM "libraries/IRLibProtocols/IRLibSendBase.cpp"

$(IntermediateDirectory)/IRLibProtocols_IRLibSendBase.cpp$(PreprocessSuffix): libraries/IRLibProtocols/IRLibSendBase.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/IRLibProtocols_IRLibSendBase.cpp$(PreprocessSuffix) "libraries/IRLibProtocols/IRLibSendBase.cpp"

$(IntermediateDirectory)/IRLibProtocols_IRLibProtocols.cpp$(ObjectSuffix): libraries/IRLibProtocols/IRLibProtocols.cpp $(IntermediateDirectory)/IRLibProtocols_IRLibProtocols.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/IRLibProtocols/IRLibProtocols.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/IRLibProtocols_IRLibProtocols.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/IRLibProtocols_IRLibProtocols.cpp$(DependSuffix): libraries/IRLibProtocols/IRLibProtocols.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/IRLibProtocols_IRLibProtocols.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/IRLibProtocols_IRLibProtocols.cpp$(DependSuffix) -MM "libraries/IRLibProtocols/IRLibProtocols.cpp"

$(IntermediateDirectory)/IRLibProtocols_IRLibProtocols.cpp$(PreprocessSuffix): libraries/IRLibProtocols/IRLibProtocols.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/IRLibProtocols_IRLibProtocols.cpp$(PreprocessSuffix) "libraries/IRLibProtocols/IRLibProtocols.cpp"

$(IntermediateDirectory)/IRLibProtocols_IRLibSAMD21.cpp$(ObjectSuffix): libraries/IRLibProtocols/IRLibSAMD21.cpp $(IntermediateDirectory)/IRLibProtocols_IRLibSAMD21.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/IRLibProtocols/IRLibSAMD21.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/IRLibProtocols_IRLibSAMD21.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/IRLibProtocols_IRLibSAMD21.cpp$(DependSuffix): libraries/IRLibProtocols/IRLibSAMD21.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/IRLibProtocols_IRLibSAMD21.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/IRLibProtocols_IRLibSAMD21.cpp$(DependSuffix) -MM "libraries/IRLibProtocols/IRLibSAMD21.cpp"

$(IntermediateDirectory)/IRLibProtocols_IRLibSAMD21.cpp$(PreprocessSuffix): libraries/IRLibProtocols/IRLibSAMD21.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/IRLibProtocols_IRLibSAMD21.cpp$(PreprocessSuffix) "libraries/IRLibProtocols/IRLibSAMD21.cpp"

$(IntermediateDirectory)/IRLibProtocols_IRLibHardware.cpp$(ObjectSuffix): libraries/IRLibProtocols/IRLibHardware.cpp $(IntermediateDirectory)/IRLibProtocols_IRLibHardware.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/IRLibProtocols/IRLibHardware.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/IRLibProtocols_IRLibHardware.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/IRLibProtocols_IRLibHardware.cpp$(DependSuffix): libraries/IRLibProtocols/IRLibHardware.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/IRLibProtocols_IRLibHardware.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/IRLibProtocols_IRLibHardware.cpp$(DependSuffix) -MM "libraries/IRLibProtocols/IRLibHardware.cpp"

$(IntermediateDirectory)/IRLibProtocols_IRLibHardware.cpp$(PreprocessSuffix): libraries/IRLibProtocols/IRLibHardware.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/IRLibProtocols_IRLibHardware.cpp$(PreprocessSuffix) "libraries/IRLibProtocols/IRLibHardware.cpp"

$(IntermediateDirectory)/Firmata_FirmataMarshaller.cpp$(ObjectSuffix): libraries/Firmata/FirmataMarshaller.cpp $(IntermediateDirectory)/Firmata_FirmataMarshaller.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Firmata/FirmataMarshaller.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Firmata_FirmataMarshaller.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Firmata_FirmataMarshaller.cpp$(DependSuffix): libraries/Firmata/FirmataMarshaller.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Firmata_FirmataMarshaller.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Firmata_FirmataMarshaller.cpp$(DependSuffix) -MM "libraries/Firmata/FirmataMarshaller.cpp"

$(IntermediateDirectory)/Firmata_FirmataMarshaller.cpp$(PreprocessSuffix): libraries/Firmata/FirmataMarshaller.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Firmata_FirmataMarshaller.cpp$(PreprocessSuffix) "libraries/Firmata/FirmataMarshaller.cpp"

$(IntermediateDirectory)/Firmata_FirmataParser.cpp$(ObjectSuffix): libraries/Firmata/FirmataParser.cpp $(IntermediateDirectory)/Firmata_FirmataParser.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Firmata/FirmataParser.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Firmata_FirmataParser.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Firmata_FirmataParser.cpp$(DependSuffix): libraries/Firmata/FirmataParser.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Firmata_FirmataParser.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Firmata_FirmataParser.cpp$(DependSuffix) -MM "libraries/Firmata/FirmataParser.cpp"

$(IntermediateDirectory)/Firmata_FirmataParser.cpp$(PreprocessSuffix): libraries/Firmata/FirmataParser.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Firmata_FirmataParser.cpp$(PreprocessSuffix) "libraries/Firmata/FirmataParser.cpp"

$(IntermediateDirectory)/Firmata_Firmata.cpp$(ObjectSuffix): libraries/Firmata/Firmata.cpp $(IntermediateDirectory)/Firmata_Firmata.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Firmata/Firmata.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Firmata_Firmata.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Firmata_Firmata.cpp$(DependSuffix): libraries/Firmata/Firmata.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Firmata_Firmata.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Firmata_Firmata.cpp$(DependSuffix) -MM "libraries/Firmata/Firmata.cpp"

$(IntermediateDirectory)/Firmata_Firmata.cpp$(PreprocessSuffix): libraries/Firmata/Firmata.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Firmata_Firmata.cpp$(PreprocessSuffix) "libraries/Firmata/Firmata.cpp"

$(IntermediateDirectory)/CppList_CppList.cpp$(ObjectSuffix): libraries/CppList/CppList.cpp $(IntermediateDirectory)/CppList_CppList.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/CppList/CppList.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CppList_CppList.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/CppList_CppList.cpp$(DependSuffix): libraries/CppList/CppList.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/CppList_CppList.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/CppList_CppList.cpp$(DependSuffix) -MM "libraries/CppList/CppList.cpp"

$(IntermediateDirectory)/CppList_CppList.cpp$(PreprocessSuffix): libraries/CppList/CppList.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/CppList_CppList.cpp$(PreprocessSuffix) "libraries/CppList/CppList.cpp"

$(IntermediateDirectory)/HC-SR04_SR04.cpp$(ObjectSuffix): libraries/HC-SR04/SR04.cpp $(IntermediateDirectory)/HC-SR04_SR04.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/HC-SR04/SR04.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/HC-SR04_SR04.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HC-SR04_SR04.cpp$(DependSuffix): libraries/HC-SR04/SR04.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/HC-SR04_SR04.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/HC-SR04_SR04.cpp$(DependSuffix) -MM "libraries/HC-SR04/SR04.cpp"

$(IntermediateDirectory)/HC-SR04_SR04.cpp$(PreprocessSuffix): libraries/HC-SR04/SR04.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/HC-SR04_SR04.cpp$(PreprocessSuffix) "libraries/HC-SR04/SR04.cpp"

$(IntermediateDirectory)/IrSensorCluster_IrSensorCluster.cpp$(ObjectSuffix): libraries/IrSensorCluster/IrSensorCluster.cpp $(IntermediateDirectory)/IrSensorCluster_IrSensorCluster.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/IrSensorCluster/IrSensorCluster.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/IrSensorCluster_IrSensorCluster.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/IrSensorCluster_IrSensorCluster.cpp$(DependSuffix): libraries/IrSensorCluster/IrSensorCluster.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/IrSensorCluster_IrSensorCluster.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/IrSensorCluster_IrSensorCluster.cpp$(DependSuffix) -MM "libraries/IrSensorCluster/IrSensorCluster.cpp"

$(IntermediateDirectory)/IrSensorCluster_IrSensorCluster.cpp$(PreprocessSuffix): libraries/IrSensorCluster/IrSensorCluster.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/IrSensorCluster_IrSensorCluster.cpp$(PreprocessSuffix) "libraries/IrSensorCluster/IrSensorCluster.cpp"

$(IntermediateDirectory)/Arduino_FreeRTOS_timers.c$(ObjectSuffix): libraries/Arduino_FreeRTOS/timers.c $(IntermediateDirectory)/Arduino_FreeRTOS_timers.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Arduino_FreeRTOS/timers.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Arduino_FreeRTOS_timers.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Arduino_FreeRTOS_timers.c$(DependSuffix): libraries/Arduino_FreeRTOS/timers.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Arduino_FreeRTOS_timers.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Arduino_FreeRTOS_timers.c$(DependSuffix) -MM "libraries/Arduino_FreeRTOS/timers.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_timers.c$(PreprocessSuffix): libraries/Arduino_FreeRTOS/timers.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Arduino_FreeRTOS_timers.c$(PreprocessSuffix) "libraries/Arduino_FreeRTOS/timers.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_heap_3.c$(ObjectSuffix): libraries/Arduino_FreeRTOS/heap_3.c $(IntermediateDirectory)/Arduino_FreeRTOS_heap_3.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Arduino_FreeRTOS/heap_3.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Arduino_FreeRTOS_heap_3.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Arduino_FreeRTOS_heap_3.c$(DependSuffix): libraries/Arduino_FreeRTOS/heap_3.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Arduino_FreeRTOS_heap_3.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Arduino_FreeRTOS_heap_3.c$(DependSuffix) -MM "libraries/Arduino_FreeRTOS/heap_3.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_heap_3.c$(PreprocessSuffix): libraries/Arduino_FreeRTOS/heap_3.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Arduino_FreeRTOS_heap_3.c$(PreprocessSuffix) "libraries/Arduino_FreeRTOS/heap_3.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_queue.c$(ObjectSuffix): libraries/Arduino_FreeRTOS/queue.c $(IntermediateDirectory)/Arduino_FreeRTOS_queue.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Arduino_FreeRTOS/queue.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Arduino_FreeRTOS_queue.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Arduino_FreeRTOS_queue.c$(DependSuffix): libraries/Arduino_FreeRTOS/queue.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Arduino_FreeRTOS_queue.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Arduino_FreeRTOS_queue.c$(DependSuffix) -MM "libraries/Arduino_FreeRTOS/queue.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_queue.c$(PreprocessSuffix): libraries/Arduino_FreeRTOS/queue.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Arduino_FreeRTOS_queue.c$(PreprocessSuffix) "libraries/Arduino_FreeRTOS/queue.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_tasks.c$(ObjectSuffix): libraries/Arduino_FreeRTOS/tasks.c $(IntermediateDirectory)/Arduino_FreeRTOS_tasks.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Arduino_FreeRTOS/tasks.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Arduino_FreeRTOS_tasks.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Arduino_FreeRTOS_tasks.c$(DependSuffix): libraries/Arduino_FreeRTOS/tasks.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Arduino_FreeRTOS_tasks.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Arduino_FreeRTOS_tasks.c$(DependSuffix) -MM "libraries/Arduino_FreeRTOS/tasks.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_tasks.c$(PreprocessSuffix): libraries/Arduino_FreeRTOS/tasks.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Arduino_FreeRTOS_tasks.c$(PreprocessSuffix) "libraries/Arduino_FreeRTOS/tasks.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_event_groups.c$(ObjectSuffix): libraries/Arduino_FreeRTOS/event_groups.c $(IntermediateDirectory)/Arduino_FreeRTOS_event_groups.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Arduino_FreeRTOS/event_groups.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Arduino_FreeRTOS_event_groups.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Arduino_FreeRTOS_event_groups.c$(DependSuffix): libraries/Arduino_FreeRTOS/event_groups.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Arduino_FreeRTOS_event_groups.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Arduino_FreeRTOS_event_groups.c$(DependSuffix) -MM "libraries/Arduino_FreeRTOS/event_groups.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_event_groups.c$(PreprocessSuffix): libraries/Arduino_FreeRTOS/event_groups.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Arduino_FreeRTOS_event_groups.c$(PreprocessSuffix) "libraries/Arduino_FreeRTOS/event_groups.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_port.c$(ObjectSuffix): libraries/Arduino_FreeRTOS/port.c $(IntermediateDirectory)/Arduino_FreeRTOS_port.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Arduino_FreeRTOS/port.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Arduino_FreeRTOS_port.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Arduino_FreeRTOS_port.c$(DependSuffix): libraries/Arduino_FreeRTOS/port.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Arduino_FreeRTOS_port.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Arduino_FreeRTOS_port.c$(DependSuffix) -MM "libraries/Arduino_FreeRTOS/port.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_port.c$(PreprocessSuffix): libraries/Arduino_FreeRTOS/port.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Arduino_FreeRTOS_port.c$(PreprocessSuffix) "libraries/Arduino_FreeRTOS/port.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_croutine.c$(ObjectSuffix): libraries/Arduino_FreeRTOS/croutine.c $(IntermediateDirectory)/Arduino_FreeRTOS_croutine.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Arduino_FreeRTOS/croutine.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Arduino_FreeRTOS_croutine.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Arduino_FreeRTOS_croutine.c$(DependSuffix): libraries/Arduino_FreeRTOS/croutine.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Arduino_FreeRTOS_croutine.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Arduino_FreeRTOS_croutine.c$(DependSuffix) -MM "libraries/Arduino_FreeRTOS/croutine.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_croutine.c$(PreprocessSuffix): libraries/Arduino_FreeRTOS/croutine.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Arduino_FreeRTOS_croutine.c$(PreprocessSuffix) "libraries/Arduino_FreeRTOS/croutine.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_variantHooks.cpp$(ObjectSuffix): libraries/Arduino_FreeRTOS/variantHooks.cpp $(IntermediateDirectory)/Arduino_FreeRTOS_variantHooks.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Arduino_FreeRTOS/variantHooks.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Arduino_FreeRTOS_variantHooks.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Arduino_FreeRTOS_variantHooks.cpp$(DependSuffix): libraries/Arduino_FreeRTOS/variantHooks.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Arduino_FreeRTOS_variantHooks.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Arduino_FreeRTOS_variantHooks.cpp$(DependSuffix) -MM "libraries/Arduino_FreeRTOS/variantHooks.cpp"

$(IntermediateDirectory)/Arduino_FreeRTOS_variantHooks.cpp$(PreprocessSuffix): libraries/Arduino_FreeRTOS/variantHooks.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Arduino_FreeRTOS_variantHooks.cpp$(PreprocessSuffix) "libraries/Arduino_FreeRTOS/variantHooks.cpp"

$(IntermediateDirectory)/Arduino_FreeRTOS_list.c$(ObjectSuffix): libraries/Arduino_FreeRTOS/list.c $(IntermediateDirectory)/Arduino_FreeRTOS_list.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Arduino_FreeRTOS/list.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Arduino_FreeRTOS_list.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Arduino_FreeRTOS_list.c$(DependSuffix): libraries/Arduino_FreeRTOS/list.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Arduino_FreeRTOS_list.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Arduino_FreeRTOS_list.c$(DependSuffix) -MM "libraries/Arduino_FreeRTOS/list.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_list.c$(PreprocessSuffix): libraries/Arduino_FreeRTOS/list.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Arduino_FreeRTOS_list.c$(PreprocessSuffix) "libraries/Arduino_FreeRTOS/list.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_stream_buffer.c$(ObjectSuffix): libraries/Arduino_FreeRTOS/stream_buffer.c $(IntermediateDirectory)/Arduino_FreeRTOS_stream_buffer.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Arduino_FreeRTOS/stream_buffer.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Arduino_FreeRTOS_stream_buffer.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Arduino_FreeRTOS_stream_buffer.c$(DependSuffix): libraries/Arduino_FreeRTOS/stream_buffer.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Arduino_FreeRTOS_stream_buffer.c$(ObjectSuffix) -MF$(IntermediateDirectory)/Arduino_FreeRTOS_stream_buffer.c$(DependSuffix) -MM "libraries/Arduino_FreeRTOS/stream_buffer.c"

$(IntermediateDirectory)/Arduino_FreeRTOS_stream_buffer.c$(PreprocessSuffix): libraries/Arduino_FreeRTOS/stream_buffer.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Arduino_FreeRTOS_stream_buffer.c$(PreprocessSuffix) "libraries/Arduino_FreeRTOS/stream_buffer.c"

$(IntermediateDirectory)/DS3231_DS3231.cpp$(ObjectSuffix): libraries/DS3231/DS3231.cpp $(IntermediateDirectory)/DS3231_DS3231.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/DS3231/DS3231.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DS3231_DS3231.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DS3231_DS3231.cpp$(DependSuffix): libraries/DS3231/DS3231.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DS3231_DS3231.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/DS3231_DS3231.cpp$(DependSuffix) -MM "libraries/DS3231/DS3231.cpp"

$(IntermediateDirectory)/DS3231_DS3231.cpp$(PreprocessSuffix): libraries/DS3231/DS3231.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DS3231_DS3231.cpp$(PreprocessSuffix) "libraries/DS3231/DS3231.cpp"

$(IntermediateDirectory)/Indicator_Indicator.cpp$(ObjectSuffix): libraries/Indicator/Indicator.cpp $(IntermediateDirectory)/Indicator_Indicator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Indicator/Indicator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Indicator_Indicator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Indicator_Indicator.cpp$(DependSuffix): libraries/Indicator/Indicator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Indicator_Indicator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Indicator_Indicator.cpp$(DependSuffix) -MM "libraries/Indicator/Indicator.cpp"

$(IntermediateDirectory)/Indicator_Indicator.cpp$(PreprocessSuffix): libraries/Indicator/Indicator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Indicator_Indicator.cpp$(PreprocessSuffix) "libraries/Indicator/Indicator.cpp"

$(IntermediateDirectory)/PotMotor_PotMotor.cpp$(ObjectSuffix): libraries/PotMotor/PotMotor.cpp $(IntermediateDirectory)/PotMotor_PotMotor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/PotMotor/PotMotor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PotMotor_PotMotor.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PotMotor_PotMotor.cpp$(DependSuffix): libraries/PotMotor/PotMotor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/PotMotor_PotMotor.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/PotMotor_PotMotor.cpp$(DependSuffix) -MM "libraries/PotMotor/PotMotor.cpp"

$(IntermediateDirectory)/PotMotor_PotMotor.cpp$(PreprocessSuffix): libraries/PotMotor/PotMotor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PotMotor_PotMotor.cpp$(PreprocessSuffix) "libraries/PotMotor/PotMotor.cpp"

$(IntermediateDirectory)/IRremote_IRremote.cpp$(ObjectSuffix): libraries/IRremote/IRremote.cpp $(IntermediateDirectory)/IRremote_IRremote.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/IRremote/IRremote.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/IRremote_IRremote.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/IRremote_IRremote.cpp$(DependSuffix): libraries/IRremote/IRremote.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/IRremote_IRremote.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/IRremote_IRremote.cpp$(DependSuffix) -MM "libraries/IRremote/IRremote.cpp"

$(IntermediateDirectory)/IRremote_IRremote.cpp$(PreprocessSuffix): libraries/IRremote/IRremote.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/IRremote_IRremote.cpp$(PreprocessSuffix) "libraries/IRremote/IRremote.cpp"

$(IntermediateDirectory)/IRremote_IrReceiver.cpp$(ObjectSuffix): libraries/IRremote/IrReceiver.cpp $(IntermediateDirectory)/IRremote_IrReceiver.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/IRremote/IrReceiver.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/IRremote_IrReceiver.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/IRremote_IrReceiver.cpp$(DependSuffix): libraries/IRremote/IrReceiver.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/IRremote_IrReceiver.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/IRremote_IrReceiver.cpp$(DependSuffix) -MM "libraries/IRremote/IrReceiver.cpp"

$(IntermediateDirectory)/IRremote_IrReceiver.cpp$(PreprocessSuffix): libraries/IRremote/IrReceiver.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/IRremote_IrReceiver.cpp$(PreprocessSuffix) "libraries/IRremote/IrReceiver.cpp"

$(IntermediateDirectory)/TurretControllers_TraverseController.cpp$(ObjectSuffix): libraries/TurretControllers/TraverseController.cpp $(IntermediateDirectory)/TurretControllers_TraverseController.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/TurretControllers/TraverseController.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TurretControllers_TraverseController.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TurretControllers_TraverseController.cpp$(DependSuffix): libraries/TurretControllers/TraverseController.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TurretControllers_TraverseController.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TurretControllers_TraverseController.cpp$(DependSuffix) -MM "libraries/TurretControllers/TraverseController.cpp"

$(IntermediateDirectory)/TurretControllers_TraverseController.cpp$(PreprocessSuffix): libraries/TurretControllers/TraverseController.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TurretControllers_TraverseController.cpp$(PreprocessSuffix) "libraries/TurretControllers/TraverseController.cpp"

$(IntermediateDirectory)/TurretControllers_TurretController.cpp$(ObjectSuffix): libraries/TurretControllers/TurretController.cpp $(IntermediateDirectory)/TurretControllers_TurretController.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/TurretControllers/TurretController.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TurretControllers_TurretController.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TurretControllers_TurretController.cpp$(DependSuffix): libraries/TurretControllers/TurretController.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TurretControllers_TurretController.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TurretControllers_TurretController.cpp$(DependSuffix) -MM "libraries/TurretControllers/TurretController.cpp"

$(IntermediateDirectory)/TurretControllers_TurretController.cpp$(PreprocessSuffix): libraries/TurretControllers/TurretController.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TurretControllers_TurretController.cpp$(PreprocessSuffix) "libraries/TurretControllers/TurretController.cpp"

$(IntermediateDirectory)/utility_BLEStream.cpp$(ObjectSuffix): libraries/Firmata/utility/BLEStream.cpp $(IntermediateDirectory)/utility_BLEStream.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Firmata/utility/BLEStream.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/utility_BLEStream.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utility_BLEStream.cpp$(DependSuffix): libraries/Firmata/utility/BLEStream.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/utility_BLEStream.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/utility_BLEStream.cpp$(DependSuffix) -MM "libraries/Firmata/utility/BLEStream.cpp"

$(IntermediateDirectory)/utility_BLEStream.cpp$(PreprocessSuffix): libraries/Firmata/utility/BLEStream.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/utility_BLEStream.cpp$(PreprocessSuffix) "libraries/Firmata/utility/BLEStream.cpp"

$(IntermediateDirectory)/utility_EthernetClientStream.cpp$(ObjectSuffix): libraries/Firmata/utility/EthernetClientStream.cpp $(IntermediateDirectory)/utility_EthernetClientStream.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Firmata/utility/EthernetClientStream.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/utility_EthernetClientStream.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utility_EthernetClientStream.cpp$(DependSuffix): libraries/Firmata/utility/EthernetClientStream.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/utility_EthernetClientStream.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/utility_EthernetClientStream.cpp$(DependSuffix) -MM "libraries/Firmata/utility/EthernetClientStream.cpp"

$(IntermediateDirectory)/utility_EthernetClientStream.cpp$(PreprocessSuffix): libraries/Firmata/utility/EthernetClientStream.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/utility_EthernetClientStream.cpp$(PreprocessSuffix) "libraries/Firmata/utility/EthernetClientStream.cpp"

$(IntermediateDirectory)/utility_SerialFirmata.cpp$(ObjectSuffix): libraries/Firmata/utility/SerialFirmata.cpp $(IntermediateDirectory)/utility_SerialFirmata.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Firmata/utility/SerialFirmata.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/utility_SerialFirmata.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utility_SerialFirmata.cpp$(DependSuffix): libraries/Firmata/utility/SerialFirmata.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/utility_SerialFirmata.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/utility_SerialFirmata.cpp$(DependSuffix) -MM "libraries/Firmata/utility/SerialFirmata.cpp"

$(IntermediateDirectory)/utility_SerialFirmata.cpp$(PreprocessSuffix): libraries/Firmata/utility/SerialFirmata.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/utility_SerialFirmata.cpp$(PreprocessSuffix) "libraries/Firmata/utility/SerialFirmata.cpp"

$(IntermediateDirectory)/utility_EthernetServerStream.cpp$(ObjectSuffix): libraries/Firmata/utility/EthernetServerStream.cpp $(IntermediateDirectory)/utility_EthernetServerStream.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Firmata/utility/EthernetServerStream.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/utility_EthernetServerStream.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utility_EthernetServerStream.cpp$(DependSuffix): libraries/Firmata/utility/EthernetServerStream.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/utility_EthernetServerStream.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/utility_EthernetServerStream.cpp$(DependSuffix) -MM "libraries/Firmata/utility/EthernetServerStream.cpp"

$(IntermediateDirectory)/utility_EthernetServerStream.cpp$(PreprocessSuffix): libraries/Firmata/utility/EthernetServerStream.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/utility_EthernetServerStream.cpp$(PreprocessSuffix) "libraries/Firmata/utility/EthernetServerStream.cpp"

$(IntermediateDirectory)/utility_BluefruitLE_SPI_Stream.cpp$(ObjectSuffix): libraries/Firmata/utility/BluefruitLE_SPI_Stream.cpp $(IntermediateDirectory)/utility_BluefruitLE_SPI_Stream.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Firmata/utility/BluefruitLE_SPI_Stream.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/utility_BluefruitLE_SPI_Stream.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utility_BluefruitLE_SPI_Stream.cpp$(DependSuffix): libraries/Firmata/utility/BluefruitLE_SPI_Stream.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/utility_BluefruitLE_SPI_Stream.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/utility_BluefruitLE_SPI_Stream.cpp$(DependSuffix) -MM "libraries/Firmata/utility/BluefruitLE_SPI_Stream.cpp"

$(IntermediateDirectory)/utility_BluefruitLE_SPI_Stream.cpp$(PreprocessSuffix): libraries/Firmata/utility/BluefruitLE_SPI_Stream.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/utility_BluefruitLE_SPI_Stream.cpp$(PreprocessSuffix) "libraries/Firmata/utility/BluefruitLE_SPI_Stream.cpp"

$(IntermediateDirectory)/utility_WiFiStream.cpp$(ObjectSuffix): libraries/Firmata/utility/WiFiStream.cpp $(IntermediateDirectory)/utility_WiFiStream.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/robot1/Source/robot1/sketches/libraries/Firmata/utility/WiFiStream.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/utility_WiFiStream.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/utility_WiFiStream.cpp$(DependSuffix): libraries/Firmata/utility/WiFiStream.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/utility_WiFiStream.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/utility_WiFiStream.cpp$(DependSuffix) -MM "libraries/Firmata/utility/WiFiStream.cpp"

$(IntermediateDirectory)/utility_WiFiStream.cpp$(PreprocessSuffix): libraries/Firmata/utility/WiFiStream.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/utility_WiFiStream.cpp$(PreprocessSuffix) "libraries/Firmata/utility/WiFiStream.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


