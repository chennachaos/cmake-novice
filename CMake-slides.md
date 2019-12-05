---
marp: true
title: Introduction to CMake
paginate: true
---

## <!--fit--> Introduction to CMake

---

## Outline
* Introduction
* Hands-on exercises
    * Single source file
    * Multiple source files
* Compilers and compiler flags
* Linking libraries
* System Introspection
* CTest

---

## Introduction

* CMake is not a build system
* CMake is system that manages the build process
* Portability and flexibility for cross-perform compiling
* In conjunction with native build environment
    * Makefiles on Unix
    * MSVC on Windows
* Supported by many IDEs - MS Visual Studio, NetBeans, Eclipse, KDevelop
* Builds the dependency graph internally
    * Especially useful for large-scale Fortran projects
* Integrated testing

---

## Getting stated with CMake

1. Configuring
2. Building
3. Installing

* To start with, we need to create a CMakeLists.txt file

```cmake
cmake_minimum_required(VERSION 2.8.1)

project(HelloCMake)

add_executable(hello_cmake hello_cmake.cpp)
```

* CMake picks up the default compiler

---

## Getting stated with CMake

1. Configuring
    `cmake CMakeLists.txt` or `cmake .`
2. Building
    `make`
3. Installing (depends on the project organisation)
    `make install`

---

## Exercise 1

* Enter the `ex1` directory
* Compile, build and run the executable

---

## Project with multiple source files

![CMake directory structure](./fig/cmake-dir-structure.png)

---

## Project with multiple source files


```cmake
cmake_minimum_required(VERSION 2.8.1)

project(Math)

include_directories(./src/add  ./src/mul)

file(GLOB sources src/*/*.cpp)

add_executable(ex2test1 ./src/ex2test1.cpp ${sources})
add_executable(ex2test2 ./src/ex2test2.cpp ${sources})

install(TARGETS ex2test1 ex2test2 RUNTIME DESTINATION /home/s.engkadac/cmakecourse/ex2/bin)
```

* Make sure to modify the DESTINATION path
---

### Project with multiple source files

1. Configure
    `cd build`
    `cmake ..`
2. Build
    `make`
3. Install
    `make install`
---

### `make` vs `make install`

* `make` command only builds the library and creates the executable(s) in the 'build' directory

* `make install` command builds the library, creates the executable(s) in the 'build' directory and copies the executable(s) to DESTINATION directory

* Always use `make install` directly

---

## Exercise 2

* Enter the `ex2` directory
* Compile, build, install and run the executable(s)

---

## Resolving dependencies

* Needs no user intervention except the list of source files
* Especially useful for Fortran
* For example,

```cmake
file(GLOB sources source/*.f)

add_executable(myexe  main.f  ${sources})
```

---

# Dealing with compilers and compiler flags

---

## Compilers
* Option 1: Use `modules` if on an HPC machine
* Option 2: Set ENV variables `CC` `CXX` and `FC`
* Option 3: Set CMake variables
```cmake
set(CMAKE_C_COMPILER "/path/to/your/c/compiler/executable")

set(CMAKE_CXX_COMPILER "/path/to/your/cpp/compiler/executable")
```
---

## Compiler flags
```cmake
set(COPT "-std=c++11 -O3 -D DOMAIN2D -fopenmp  -fpermissive -frounding-math")

# this command appends to the CXX compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COPT}")
```
---

## Project language(s)

```cmake
project(myproject C)
```
#
```cmake
project(myproject CXX Fortran)
```
#
```cmake
enable_language(CXX)
```
When a language is enabled, CMake finds a compiler for that language, and determines some information, such as the target architecture, the vendor, the compiler, version of the compiler and the location of the corresponding utilities.

---

## Project language(s)

* If the language <LANG> is enabled, then the corresponding variables are set
    * CMAKE_<LANG>_COMPILER
        * CMAKE_C_COMPILER
        * CMAKE_CXX_COMPILER
    * CMAKE_<LANG>_COMPILER_ID
    * CMAKE_<LANG>_COMPILER_VENDOR
* The list of enabled languages for the current project can be accessed with the variable `ENABLED_LANGUAGES`
---

## Exercise 3

* Enter the `ex3` directory
* Update the CMakeLists.txt with
    * the project for CXX
    * set the CXX compiler
    * set CXX compiler flags
* Compile, build, install and run the executable(s)

---

# Linking libraries

---

# Finding libraries automatically

```cmake
find_package(MPI REQUIRED)

file(GLOB_RECURSE sources src/*.f90)
add_executable(main programs/main.f90 ${sources})
target_include_directories(main PRIVATE ${MPI_Fortran_INCLUDE_PATH})
target_link_libraries(main ${MPI_Fortran_LIBRARIES})
```

* Danger of not finding the library (vendor and version) you particularly want
* I learnt to be skeptical of `modules` (on Sunbird)
---

# Finding libraries manually
* Header files
    ```cmake
    include_directories(
    /usr/include/openmpi 
    /usr/include/petsc 
    /usr/include/boost
    )
    ```
* Libraries (.so, .a files)
    ```cmake
    link_directories(
    /usr/lib/libblas
    /usr/lib/openmpi
    /usr/lib/petsc
    )
    ```
We know exactly the libraries that we are using.

---

## Exercise 4

* Enter the `ex4` directory
* Update the CMakeLists.txt with
    * the project for CXX
    * set the CXX compiler
    * set CXX compiler flags
    * set the missing entries in
        * include_directories
        * link_directories
* Compile, build, install and run the executable(s)
---

# System introspection

---

## Local Vs Cached variables

```cmake
cmake_minimum_required(VERSION 2.8)
project(test)
enable_language(CXX)

message("---------------")
message(STATUS ${MY_VAR})
set(MY_VAR "I am a local variable")
message("---------------")
message(STATUS ${MY_VAR})
message("---------------")
```
**Exercise:** Create a CMakeLists.txt file with the above code, run the following commands and observe the output
1. cmake .
2. cmake . -DMY_VAR="global variable"
3. cmake .

---

## Environmental variables

* Access environmental variables from within CMakeLists.txt
    * $ENV{VAR_NAME}

* **Exercise**
    * Define an env variable COMPILER_TYPE as "INTEL"
    * Print its contents from within CMakeLists.txt 

---

## Decision making

```cmake
if( $ENV{COMPILER_TYPE} MATCHES "INTEL")

    message ("Using INTEL compilers")

    set(CMAKE_C_COMPILER "/opt/intel/compilers_and_libraries_2016.3.210/linux/bin/intel64/icc")
    set(CMAKE_CXX_COMPILER "/opt/intel/compilers_and_libraries_2016.3.210/linux/bin/intel64/icc")
    set(CMAKE_Fortran_COMPILER "/opt/intel/compilers_and_libraries_2016.3.210/linux/bin/intel64/ifort")

    set(COPT "-Wall -std=c++11  -O3")
    
else()
    message ("Using GNU compilers")
    set(CMAKE_C_COMPILER "/opt/ohpc/pub/compiler/gcc/5.3.0/bin/gcc")
    set(CMAKE_CXX_COMPILER "/opt/ohpc/pub/compiler/gcc/5.3.0/bin/g++")
    set(CMAKE_Fortran_COMPILER "/opt/ohpc/pub/compiler/gcc/5.3.0/bin/gfortran")

    set(COPT "-w -std=c++11 -O3 -fopenmp")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COPT}")
```
---

## Decision making
```cmake
if( CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    message ("Using INTEL compilers")
elseif( CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message ("Using Clang compilers")
elseif( CMAKE_CXX_COMPILER_ID MATCHES "Cray")
    message ("Using Cray compilers")
elseif( CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    message ("Using GNU compilers")
else()
    message ("Compiler type not available")
endif()
```
---

# CTest

---