---
title: "System introspection"
teaching: 10
exercises: 10
questions:
- "How to find out details of the platform and the compiler?"
- "How to write CMakeLists.txt file for optional compilation and linking?"
objectives:
- "To find out the platform and compiler details"
- "To add optional compilation arguments to CMakeLists.txt"
keypoints:
- "FIX ME"
---

## Local Vs Cached variables
Many a times, we have to develop our projects considering portability
to other platforms/architectures/operating system. Some of the libraries
that we want to use in our application might not be available in a certain
platform. It might also happen that we want to change our compiler, for example, 
from Intel to GNU or GNU to PGI or PGI to Intel. Since the options that we want
to pass to the compiler vary from one compiler to the other compiler, we 
need an introspecting mechanism with which we can have a flexibility and portability.

To understand system introspection in CMake, we first need to understand 
the concept of variables in CMake. In CMake, the variables can be grouped into
two types: 1.) Local variables and 2.) Cached (or global) variables.

> ## Exercise on variables
> Create a CMakeLists.txt file with the following lines,  
> configure the project using `cmake .` and observe the output.
> ```cmake
> cmake_minimum_required(VERSION 2.8)
> project(test)
> enable_language(CXX)
>
> message("---------------")
> message(STATUS ${MY_VAR})
> 
> set(MY_VAR "I am a local variable")
> message("---------------")
> message(STATUS ${MY_VAR})
> message("---------------")
> ```
> Execute the following commands on the terminal one by one and
> observe the ouput.
>
>   1. `cmake .`
>   2. `cmake . -DMY_VAR="global variable"`
>   3. `cmake .`
>
> > ## Solution
> > The variables defined in the CMakeLists.txt are local variables.
> > They are not cached. The variables defined with `-D` option to the
> > `cmake` are cached.
> > That is why when we executed the last command, we still see the contents
> > of the variable `MY_VAR` being displayed. This is because `MY_VAR` is cached
> > when the second command was executed.
> >
> > The list of all the cached variables are stored in the `CMakeCache.txt` file.
> {: .solution}
{: .challenge}


## Environmental variables
We can also access environmental variables that are set outside CMake.

For example, we can set the variable COMPILER_TYPE as
~~~
export COMPILER_TYPE=INTEL
~~~
{: .language-bash}

and access it from within the CMakeLists.txt using $ENV{<varname>}. For example,
```cmake
$ENV{COMPILER_TYPE}
```

## Decision making with control statements
CMake supports control statement, if-else, that offers
a great flexibility in writing CMakeLists.txt files with a high degree
of portability.

A sample usage of if-else statement in CMake is as follows.

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

Another example using cached variables.

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

In this way, we can choose from a pre-defined list of compilers
and/or compiler options by using the environment/cached variables.


{% include links.md %}
