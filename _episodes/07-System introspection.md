---
title: "System introspection"
teaching: 10
exercises: 10
questions:
- "How to find out details of the platform and the compiler?"
- "How to write CMakeLists.txt file for optional compilation and linking?"
- "How can CMake help me configure my project automatically?"
objectives:
- "To find out the platform and compiler details"
- "To add optional compilation arguments to CMakeLists.txt"
- "To use the search capabilities of CMake to create a more robust build 
   system."
keypoints:
- "Careful with the Cache"
- "Use Find Modules when possible"
---

Very often building software requires pointing the compiler towards 
the proper header files, and the linker towards the proper static 
libraries.  
Unfortunately, every system is different. Moreover, HPC systems tend to
offer multiple versions of the same libraries, and some times the user 
needs particular libraries that would not be worth installing in system
directories. 

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

> ## Switching Modules and CMake configuration
> Be aware that if you switch modules (e.g., choose another compiler
> or MPI version via `module load ...`) the CMake cache will be completely
> unaware of it. This may cause unexpected behaviour that can be resolved
> only by clearing the cache.
{: .callout}

## Finding things automatically with CMake

When the path of a necessary file (library or header)
is not precisely known, we can
resort to looking at the environment variables to make a general guess 
and then pinpoint the file path via `find`.  
CMake provides a more flexible way to manage this aspect of building 
software via functions that can be used to find files and packages
automatically. Since such search operations can be expensive, the
results are usually cached. 

### Finding include directories and files

The function [`find_path()`](https://cmake.org/cmake/help/latest/command/find_path.html) may be used to locate the path of a library
or a header. The result of the search is stored in a variable that can be
then used in a call to [`target_link_directories()`](https://cmake.org/cmake/help/latest/command/target_link_directories.html#command:target_link_directories) or 
[`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html?highlight=target_include_directories).

> ## Finding paths
> 1. Create a file to search for:
> ```bash
> DIR=${HOME}/dir_to_search/another_one
> mkdir -p $DIR
> touch $DIR/findme
> ```
> 2. Create a `CMakeLists.txt` file with the following lines, 
>   modify the relevant lines to find the file that you just created:
> ```cmake 
> cmake_minimum_required(VERSION 2.8)
> project(test)
> find_path(Path_To_Find NAMES findme PATHS ...)
> message("The file is in " ${Path_To_Find})
> ```
> 3.  configure the project using `cmake . ` and observe the output. 
>     Was the file found?
> 
> > ## Solution 
> > Finding files is not as straightforward as using find, unfortunately.
> > A possible solution is the following:
> > ```cmake 
> > cmake_minimum_required(VERSION 2.8)
> > project(test)
> > find_path(Path_To_Find NAMES findme PATHS $ENV{HOME}/*/* )
> > message("The file is in " ${Path_To_Find})
> > ```
> > An asterisk `*` needs to be used for each level. 
> > Sub-directories will not be searched, but
> > multiple paths can be specified.
> {: .solution}
{: .challenge}

A similar function specifically for finding  libraries, is 
`find_library()`. Its use is encouraged over using `find_file()` for 
finding libraries, as it can be cleverer with names and search paths.

> ## Finding Libraries
> Use the  `find_library()` function to find the `libmpifort.so` library
> on Sunbird.
> > ## Solution
> > If a MPI module is loaded, then the `MPI_ROOT` environment variable
> > should be defined. We can then use it in a `CMakeLists.txt`
> > ```cmake
> > cmake_minimum_required(VERSION 2.8)
> > project(test)
> > find_library(MPI NAMES mpifort PATHS $ENV{MPI_ROOT}/* )
> > message("The file is in " ${MPI})
> > ```
> {: .solution}
> Notice that MPI libraries are used daily by thousands of people. 
> Maybe someone has has already solved this problem in a robust way?
{: .challenge}

> ## Caching search results 
> The `find_file()`, `find_library()` and `find_path()` functions can be 
> called for the same variable more times with different options and 
> paths, to expand the search space. The first successful search will 
> write the found path in the cache, and the following calls will not be 
> performed.  
> In general, if the value of a variable defined by any of these function
> is already in the cache, the function will not be called.
{: .callout}



### Find modules

If the headers and the libraries are part of an established package, it is
likely that there is a *find module* already created that may help you with
locating said package on the system where you are building the software.  
A list of find modules that are provided by the CMake distribution is 
available here: [A list of find modules available in CMake](https://cmake.org/cmake/help/latest/manual/cmake-modules.7.html)

In the following example we want to compile our program including MPI 
headers and linking against the MPI library:

```cmake
find_package(MPI REQUIRED)
file(GLOB_RECURSE sources src/*.f90)
add_executable(main programs/main.f90 ${sources})
target_include_directories(main PRIVATE ${MPI_Fortran_INCLUDE_PATH})
target_link_libraries(main ${MPI_Fortran_LIBRARIES})
```

The cmake module `FindMPI.cmake`, which is invoked through the 
`find_package()` function, is going to look for the MPI package by nicely
cooperating with the module system, and will set up some variables in CMake
that we can use in `target_include_directories()` and 
`target_link_libraries` (see [documentation on Find Modules](https://cmake.org/cmake/help/latest/manual/cmake-developer.7.html#find-modules)).

> ## Checking that CMake did the right thing
> When we delegate the search of libraries and packages to CMake, we may
> think we have no control over it any more, and 
> wonder if it is not doing something dodgy in the background.  
> To have all the commands printed out during compilation, it is possible
> to define `VERBOSE=1` when invoking `make`:
> ```bash
> make VERBOSE=1
> ```
> so that all the commands will be visible. You may want to redirect the
> output to a file.  
> Notice that the `-n` option for `make` does not produce 
> anything interesting.
{: .callout}

{% include links.md %}
