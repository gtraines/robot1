# Install script for directory: /home/graham/Source/robot1/sketches

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/graham/Source/robot1/sketches/cmake-build-debug/libraries/Arduino_FreeRTOS/cmake_install.cmake")
  include("/home/graham/Source/robot1/sketches/cmake-build-debug/libraries/CppList/cmake_install.cmake")
  include("/home/graham/Source/robot1/sketches/cmake-build-debug/libraries/TurretConfig/cmake_install.cmake")
  include("/home/graham/Source/robot1/sketches/cmake-build-debug/libraries/Indicator/cmake_install.cmake")
  include("/home/graham/Source/robot1/sketches/cmake-build-debug/libraries/PotMotor/cmake_install.cmake")
  include("/home/graham/Source/robot1/sketches/cmake-build-debug/libraries/IrTxRx/cmake_install.cmake")
  include("/home/graham/Source/robot1/sketches/cmake-build-debug/libraries/IrSensorCluster/cmake_install.cmake")
  include("/home/graham/Source/robot1/sketches/cmake-build-debug/libraries/TurretControllers/cmake_install.cmake")
  include("/home/graham/Source/robot1/sketches/cmake-build-debug/turretFreeRtos/cmake_install.cmake")
  include("/home/graham/Source/robot1/sketches/cmake-build-debug/rtosTest/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/graham/Source/robot1/sketches/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
