---
title: "HelloWorld using CMake"
teaching: 10
exercises: 10
questions:
- "How to use CMake for building applications?"
objectives:
- "To learn CMake using a simple example"
keypoints:
- "First key point. Brief Answer to questions. (FIXME)"
---

## Writing CMakeLists.txt
In this episode, we will start using CMake for building an executable
for the simple Hello World program written in C++. The source code 
`hello_cmake.cpp` is available in the course material that can be downloaded
from the `setup` page of this course.

This might be an overkill to build the executable for an application 
with a single source file. However, this demonstrates the important steps
involved in using CMake for building the executables for complex projects.


To start, create a new folder `hello` and copy the `hello_cmake.cpp` 
file into it. Then, create *CMakeLists.txt* file with the following content.
~~~
cmake_minimum_required(VERSION 2.8.1)

project(HelloCMake)

add_executable(hello_cmake hello_cmake.cpp)
~~~
{: .language-cmake}

Our CMakeLists.txt file consists of three lines.
* The first line sets the minimum version of CMake required 
  to compile this project. In this exampple, it is major 
  version 2, minor version 8 and the patch version 1.
  This is not often necessary but is a good practice to include 
  it for future reference, in case there are changes in
  the later releases of CMake.
  Always use the version that is available on your systems.

* The second line sets the name of the project.

* The last line specifies that the executable `hello_cmake` is to
  be built using the source file `hello_cmake.cpp`.

Now, let us how we can compile the source code and build the executable
using this CMakeLists.txt file. For this exercise, we use the GNU compiler.

Load the GNU compiler.
~~~
module purge
module load compiler/gnu/7/3
~~~
{: .language-bash}


Once we have created the CMakeLists.txt file, we can build the
project to generate the executable. The build process involves
three steps.

**1.) Configuration Step:** In this step, CMake creates the appropriate
configuration files for the build system, Make or MSVC. To do this,
we execute the command
~~~
cmake CMakeLists.txt
~~~
{: .language-bash}

**2.) Build step:** This step involves compiling the source code,
and generating the executable. This is done by executing
~~~
make
~~~
{: .language-bash}

**3.) Installation step:** This step copies the successfully generated
executables to the path specified. This step is not necessary for this
example. But it is very useful in organising the source code into multiple
folder when dealing with the large projects.
~~~
make install
~~~
{: .language-bash}



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


Hurray!! We have successfully built an executable that works as intended.
In the next example, we will look at building an executable for a more 
complex project that consists of multiple source files.

{% include links.md %}

