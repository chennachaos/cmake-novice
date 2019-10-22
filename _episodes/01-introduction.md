---
title: "Introduction"
teaching: 15
exercises: 0
questions:
- "What is CMake?"
objectives:
- "To learn basics of CMake"
keypoints:
- "CMake is a meta build system to generate build scripts 
   for a range of platforms"
---
## What is CMake?
Computer program written in languages such as C, C++ and Fortran
need to be compiled using an appropriate compiler in order to
generate an executable. This process requires tools that identify
the depedencies in the source code and link them accordingly. 
`Microsoft Visual Studio` on Windows and `GNU Make` build system
on Unix are two such tools.

an IDE (integrated 
development environment) such as Microsoft Visual Studio, Eclipse,
NetBeams, Atom, Code Blocks etc.. on Windows, XCode on macOS 
 Make build system on Unix/Linux and X



From the [CMake](https://cmake.org/overview/) website,

CMake is an extensible, open-source system that manages the build
process in an operating system and in a compiler-independent manner.
Unlike many cross-platform systems, CMake is designed to be used in 
conjunction with the native build environment. Simple configuration
files placed in each source directory (called CMakeLists.txt files) 
are used to generate standard build files (e.g., makefiles on Unix 
and projects/workspaces in Windows MSVC) which are used in the usual 
way. CMake can generate a native build environment that will compile 
source code, create libraries, generate wrappers and build executables 
in arbitrary combinations. CMake supports in-place and out-of-place 
builds, and can therefore support multiple builds from a single 
source tree. CMake also supports static and dynamic library builds. 


## Why CMake?
CMake eases the process of building an application for various platforms.

*) **Flexibility** in choosing different compilers, libraries

*) **Portability** across different architectures (operating systems)

*) **Dependencies** in the source code. While Makefiles resolve the dependencies
in C, C++ code, they are not helpful for the code written in Fortran.
CMake resolves dependencies among the Fortran modules.

*) **Testing:** Unit and integration tests can be developed using **CTest**.

*) Managing complex software projects with the source code consisting of 
hundreds of files.

## How to use CMake?
To use CMake, you need to create configuration scripts/files called 
*CMakeLists.txt* which are used by CMake to generate build files,
for example, Makefiles on Unix machines and projects/workspaces for
Microsoft Visual Studio on Windows machines.

If there are multiple models, then a separate CMakeLists.txt file needs
to be created for each module.

CMake syntax looks similar to that of a high-level programming language.
In fact, CMake scripts are full of calls to inbuilt functions. CMake 
also supports variables, conditional statements and loops, offering the user the 
flexibility in developing single script file that can be used across
multiple platforms.

### Frequntly used CMake functions

* `cmake_minimum_required` - sets minimum version of cmake to be used

* `set` - creates a variable with the specified value
~~~
set(COPT, "-w -g -O2")
~~~
{: .language-bash}

* `message` - prints the given message to the screen
~~~
message("Compiler is Intel...")
message("Compiler options: ${COPT}")
~~~
{: .language-bash}

* `include_directories` - sets the list of directories to look for the header files

* `link_directories` - sets the list of directories to look for the library (.so, .a) files

* `add_executable` - adds the executable target with a given name

* `add_library` - adds a library

* `target_link_libraries` - sets the list of libraries to be linked when building a particular target

* `install` - sets the path to the folder where the executables should be installed



{% include links.md %}

