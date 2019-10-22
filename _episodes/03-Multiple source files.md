---
title: "Using CMake with multiple source files"
teaching: 20
exercises: 20
questions:
- "How to setup the CMakeLists.txt file for multiple source files?"
- "How to organise directories?"
objectives:
- "To learn to create CMakeLists.txt for a project with
  multiple source files"
keypoints:
- "First key point. Brief Answer to questions. (FIXME)"
---

## CMake for building a project with multiple source files
In this episode, we will learn how to build a project that consists of
multiple source files.

In order to effectively manage a complex software project that
consists of multiple source files, it is recommended to organise the project
using multiple directories. The directory structure for a software 
project using CMake is depicted in the following figure.

![CMake directory structure](../fig/cmake-dir-structure.png)

As shown, the project directory consists of

* a `src` folder which contains all the source files. The `src` folder
  may contain subfolders.

* a `CMakeLists.txt` file with the configuration options.

* a `build` folder for managing the configuration and compilation of the
  source code.

* a `bin` directory for installing the executables.


To better understand this, let us build the executable(s) for Example 2.
Copy the ex2 folder from the database into the current working directory and 
change the working directory to `ex2`.

The CMakeLists.txt file contains the following content.
~~~
cmake_minimum_required(VERSION 2.8.1)

project(Math)

include_directories(./src/add  ./src/mul)

file(GLOB sources src/*/*.cpp)

add_executable(ex2test1 ./src/ex2test1.cpp ${sources})
add_executable(ex2test2 ./src/ex2test2.cpp ${sources})

install(TARGETS ex2test1 ex2test2 RUNTIME DESTINATION /home/s.engkadac/cmakecourse/ex2/bin)
~~~
{: .language-bash}

We now have some additional lines when compared to the file from the
example 1.

* **include_directories** - when we are working with multiple source 
files or external libraries, we have to specify the locations of 
the header files for the compiler to look for. This is done with 
the command **include_directories**.

* **file GLOB** gets the list of files matching the wildcard which can be
passed to the *add_executable* command as the list of dependencies.

Unlike the previous example, we now have two executables in this example.
We can build all the executables at once using a single execution of
the `make` command.



Executing the above command produces the following output.
~~~
[s.engkadac@sl2 hello]$ cmake CMakeLists.txt 
-- The C compiler identification is GNU 7.3.0
-- The CXX compiler identification is GNU 7.3.0
-- Check for working C compiler: /apps/compilers/gnu/7.3.0/bin/gcc
-- Check for working C compiler: /apps/compilers/gnu/7.3.0/bin/gcc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working CXX compiler: /apps/compilers/gnu/7.3.0/bin/g++
-- Check for working CXX compiler: /apps/compilers/gnu/7.3.0/bin/g++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Configuring done
-- Generating done
-- Build files have been written to: /home/s.engkadac/cmakecourse/hello
~~~
{: .output}


> ## cmake .
> We can achieve the same by simply executing
> ~~~
> cmake .
> ~~~
> {: .language-bash}
> This command runs the configuration step using the CMakeLists.txt 
file available in the current working directory.
{: .callout}


If we execute `ls -l` command, then we see several new files
and a folder being created.
~~~
[s.engkadac@sl2 hello]$ ls -l
total 36
-rw-rw-r--. 1 s.engkadac s.engkadac 12113 Sep 11 12:16 CMakeCache.txt
drwxrwxr-x. 5 s.engkadac s.engkadac  4096 Sep 11 12:16 CMakeFiles
-rw-rw-r--. 1 s.engkadac s.engkadac  1612 Sep 11 12:16 cmake_install.cmake
-rw-r--r--. 1 s.engkadac s.engkadac   104 Sep 11 12:09 CMakeLists.txt
-rw-r--r--. 1 s.engkadac s.engkadac   105 Sep 11 12:08 hello_cmake.cpp
-rw-rw-r--. 1 s.engkadac s.engkadac  4943 Sep 11 12:16 Makefile
~~~
{: .output}

As we can notice, CMake has identified the environment as Linux and 
has created a `Makefile` for this project. Once we have the Makefile(s),
we can compile the source code and build the executable.
~~~
[s.engkadac@sl2 hello]$ make
Scanning dependencies of target hello_cmake
[100%] Building CXX object CMakeFiles/hello_cmake.dir/hello_cmake.cpp.o
Linking CXX executable hello_cmake
[100%] Built target hello_cmake
~~~
{: .output}

The last in the output tells us that the executable `hello_cmake` has been
successfully generated. We can now execute it.
~~~
[s.engkadac@sl2 hello]$ ./hello_cmake 
Hello CMake!
~~~
{: .output}


{% include links.md %}

