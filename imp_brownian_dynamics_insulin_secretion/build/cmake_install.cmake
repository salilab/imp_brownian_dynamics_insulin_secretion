# Install script for directory: /Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion

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
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3.11/site-packages/IMP/insulinsecretion" TYPE FILE FILES "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/lib/IMP/insulinsecretion/_version_check.py")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/IMP" TYPE FILE RENAME "insulinsecretion.h" FILES "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/include/IMP/insulinsecretion.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/IMP/insulinsecretion" TYPE FILE RENAME "CaChannelOpeningOptimizerState.h" FILES "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/include/CaChannelOpeningOptimizerState.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/IMP/insulinsecretion" TYPE FILE RENAME "CaChannelStateDecorator.h" FILES "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/include/CaChannelStateDecorator.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/IMP/insulinsecretion" TYPE FILE RENAME "DockingStateDecorator.h" FILES "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/include/DockingStateDecorator.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/IMP/insulinsecretion" TYPE FILE RENAME "InsulinSecretionOptimizerState.h" FILES "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/include/InsulinSecretionOptimizerState.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/IMP/insulinsecretion" TYPE FILE RENAME "MaturationStateDecorator.h" FILES "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/include/MaturationStateDecorator.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/IMP/insulinsecretion" TYPE FILE RENAME "RadialDistributionFunctionSingletonScore.h" FILES "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/include/RadialDistributionFunctionSingletonScore.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/IMP/insulinsecretion" TYPE FILE RENAME "SecretionCounterDecorator.h" FILES "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/include/SecretionCounterDecorator.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/IMP/insulinsecretion" TYPE FILE RENAME "VesicleDockingOptimizerState.h" FILES "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/include/VesicleDockingOptimizerState.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/IMP/insulinsecretion" TYPE FILE RENAME "VesicleTraffickingSingletonScore.h" FILES "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/include/VesicleTraffickingSingletonScore.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/IMP/insulinsecretion" TYPE FILE RENAME "insulinsecretion_config.h" FILES "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/include/IMP/insulinsecretion/insulinsecretion_config.h")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/IMP/build_info" TYPE FILE RENAME "IMP_insulinsecretion.pck" FILES "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/build_info/IMP_insulinsecretion.pck")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/IMP/swig" TYPE FILE RENAME "IMP_insulinsecretion.Parameter.i" FILES "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/pyext/IMP_insulinsecretion.Parameter.i")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/IMP/swig" TYPE FILE RENAME "IMP_insulinsecretion.i" FILES "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/swig/IMP_insulinsecretion.i")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/IMP/swig" TYPE FILE RENAME "IMP_insulinsecretion.impl.i" FILES "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/pyext/swig.i-in")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/src/cmake_install.cmake")
  include("/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/test/cmake_install.cmake")
  include("/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/examples/cmake_install.cmake")
  include("/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/benchmark/cmake_install.cmake")
  include("/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/bin/cmake_install.cmake")
  include("/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/utility/cmake_install.cmake")
  include("/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/pyext/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/lipingsun/SynologyDrive/research/Acompleted/2025PBC/github/imp_brownian_dynamics_insulin_secretion/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
