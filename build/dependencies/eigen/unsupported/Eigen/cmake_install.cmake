# Install script for directory: D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/parallel_final")
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
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "D:/dev_environment/MinGW/x86_64-15.2.0-release-win32-seh-ucrt-rt_v13-rev0/mingw64/bin/objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE FILE FILES
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/AdolcForward"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/AlignedVector3"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/ArpackSupport"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/AutoDiff"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/BVH"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/EulerAngles"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/FFT"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/IterativeSolvers"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/KroneckerProduct"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/LevenbergMarquardt"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/MatrixFunctions"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/MPRealSupport"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/NNLS"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/NonLinearOptimization"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/NumericalDiff"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/OpenGLSupport"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/Polynomials"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/SparseExtra"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/SpecialFunctions"
    "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/Splines"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/unsupported/Eigen" TYPE DIRECTORY FILES "D:/dev_project/Parallel-Final/dependencies/eigen/unsupported/Eigen/src" FILES_MATCHING REGEX "/[^/]*\\.h$")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/dev_project/Parallel-Final/build/dependencies/eigen/unsupported/Eigen/CXX11/cmake_install.cmake")

endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "D:/dev_project/Parallel-Final/build/dependencies/eigen/unsupported/Eigen/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
