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
generate an executable.  
Building software can be a very complicated process that requires identifying
the depedencies in the source code and link them accordingly. If the software is
actively developed, these can also change over time.  
For medium to large projects, taking care of such dependencies is a tedious task
that is better performed automatically by a tool, usually called *build system*
(or, more precisely in some cases, *build system generator*).  
[Microsoft Visual Studio own `MSBuild`](https://docs.microsoft.com/en-us/cpp/build/creating-and-managing-visual-cpp-projects?view=vs-2019) on Windows and [the `autotools` suite](https://www.gnu.org/software/automake/manual/)
on Unix are two such tools that are commonly used to build software.
CMake has the advantage to be cross-platform and modern, and it is supported by 
many IDEs 
(integrated development environment) such as Microsoft Visual Studio, Eclipse,
NetBeans, QtCreator, Atom, Code Blocks and XCode.

From the [CMake](https://cmake.org/overview/) website,

> CMake is an extensible, open-source system that manages the build
> process in an operating system and in a compiler-independent manner.
> Unlike many cross-platform systems, CMake is designed to be used in 
> conjunction with the native build environment. Simple configuration
> files placed in each source directory (called CMakeLists.txt files) 
> are used to generate standard build files (e.g., makefiles on Unix 
> and projects/workspaces in Windows MSVC) which are used in the usual 
> way. CMake can generate a native build environment that will compile 
> source code, create libraries, generate wrappers and build executables 
> in arbitrary combinations. CMake supports in-place and out-of-place 
> builds, and can therefore support multiple builds from a single 
> source tree. CMake also supports static and dynamic library builds. 


## Why CMake?
CMake eases the process of building an application for various platforms.

* **Flexibility** in choosing different compilers and libraries.

* **Portability** across different architectures (operating systems)

* **Dependencies** in the source code. CMake has a dependency scanner that resolves 
dependencies in Fortran, C and C++ projects.

* **Testing:** Unit and integration tests can be developed using **CTest**.

* Managing complex software projects with the source code consisting of 
hundreds of files.

> ## A minimal solution
> The GNU compilers `gcc` and `gfortran` can generate the dependencies for
> each file when invoked with the `-MMD` flag (with `gfortran` also the flag 
> `-cpp` might be
> necessary). Of course, this process is automatic in CMake.
{: .callout}

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

CMake has also *modules*. A common use for modules is for external package
management: the `find_package` uses, under the hood, modules for each packa

### CMake Flavours
CMake has been used widely since 2000, the year of its creation. During these
years, CMake and its users have evolved, coming up with better practices. 
Those who want to write new `CMakeLists.txt` file today should try to stick to a
set of practices usually denoted as "modern CMake", which have the goal of
making the build system more robust and easier to maintain. 


### Building software 101

In order to reach the status where a program is running from the status where
only the sources are available, a number of steps needs to happen:
1. Compilation
2. Static Linking
3. Dynamic Linking

WHERE IS MY AWESOME GRAPH

#### Compilation
In the compilation, the source files (`.c`,`.cpp`,`.f*`,`.F*`) are translated
into object files (`.o`), once the necessary dependences are resolved and
processed (`.h`,`.hpp`,`.mod`).  In the case of Fortran, this step may also
create the *modulefiles*, with extension `.mod`.
The compiler (e.g., `c++`,`gcc`,`g++`,`gfortran` but also their `mpiXXX`
wrappers) are responsible for this step. It is crucial that the compilers are
informed

#### Static Linking

#### Dynamic Linking
CMake is not responsible for anything at this stage. This "last build stage" is 
performed only by the linker (`ld` on Linux systems).



### Frequently used CMake functions

* `cmake_minimum_required` - sets minimum version of cmake to be used

* `set` - creates a variable with the specified value
~~~
set(COPT, "-w -g -O2")
~~~
{: .language-cmake}

* `message` - prints the given message to the screen
~~~
message("Compiler is Intel...")
message("Compiler options: ${COPT}")
~~~
{: .language-cmake}

* `include_directories` - sets the list of directories to look for the header files

* `link_directories` - sets the list of directories to look for the library (.so, .a) files

* `add_executable` - adds the executable target with a given name

* `add_library` - adds a library

* `target_link_libraries` - sets the list of libraries to be linked when building a particular target

* `install` - sets the path to the folder where the executables should be installed


{% include links.md %}

