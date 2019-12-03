---
title: "Dealing with compilers"
teaching: 10
exercises: 10
questions:
- "How to change the compiler?"
- "How to add compiler flags?"
objectives:
- "To learn how to change the compiler"
- "To learn how to set the compiler flags"
keypoints:
- "First key point. Brief Answer to questions. (FIXME)"
---

The true power of CMake is in its flexibility to specify various configuration
and build options.

CMake uses a toolchain of utilities to to drive the build process.
The toolchain utilities available are determined by the languages enabled.
In normal builds, CMake automatically determines the toolchain for host builds
based on system introspection and defaults. In cross-compiling scenarios,
a toolchain file may be specified with information about compiler and utility paths.


## Language
The `project()` command enables the suitable languages for the 
application. Language-specific built-in variables, such as CMAKE_CXX_COMPILER,
CMAKE_CXX_COMPILER_ID etc are set by invoking the `project()` command.
By default the enabled languages are C and CXX.

To create a project that use only C++ language
```cmake
project(C_Only_Project C)
```

We can also enable the language features using the `enable_language()`
after the project() command.

```cmake
enable_language(CXX)
```
When a language is enabled, CMake finds a compiler for that language,
and determines some information, such as the target architecture, the vendor,
the compiler, version of the compiler and the location of the corresponding utilities.


We can access the list of enabled languages for the current project
by using the variable `ENABLED_LANGUAGES`.


## Compiler variables and properties
Once a particular language is enabled, several variables related to that 
language components of a toolchain are created.

If the enabled language is \<LANG\>, then the corresponding variables are:
* CMAKE_\<LANG\>_COMPILER is the full path to the compiler used for \<LANG\>.
* CMAKE_\<LANG\>_COMPILER_ID is the identifier used by CMake for the compiler
* CMAKE_\<LANG\>_COMPILER_VERSION is the version of the compiler.
* CMAKE_\<LANG\>_FLAGS is the list of flags that will be added to the
compile command when compiling a file of a particular language.

* For C compiler:
    * CMAKE_C_COMPILER, CMAKE_C_COMPILER_ID, CMAKE_C_COMPILER_Version and CMAKE_C_FLAGS.
* For C++ compiler:
    * CMAKE_CXX_COMPILER, CMAKE_CXX_COMPILER_ID, CMAKE_CXX_COMPILER_Version and CMAKE_CXX_FLAGS.
* For C compiler:
    * CMAKE_Fortran_COMPILER, CMAKE_Fortran_COMPILER_ID, CMAKE_Fortran_COMPILER_Version and CMAKE_Fortran_FLAGS.



## Setting the compiler
By default, CMake picks up the compiler from the environment using the 
environment variables, `CC`, `CXX` and `FC` etc. We have seen this with
`tutorial 1`. Since we loaded the GNU compiler, CMake picked `gcc` and `g++`
as the compilers.

We can check the compiler that is being used and, if necessary, modify the 
compiler and its flags, by setting various environment variables from
within CMakeLists.txt.


```cmake

set(CMAKE_C_COMPILER "/path/to/your/c/compiler/executable")

set(CMAKE_CXX_COMPILER "/path/to/your/cpp/compiler/executable")

```

Similarly, we can set the compiler flags as follows.

```cmake

set(COPT "-std=c++11 -O3 -D DOMAIN2D -fopenmp  -fpermissive -frounding-math")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COPT}")

```



{% include links.md %}

