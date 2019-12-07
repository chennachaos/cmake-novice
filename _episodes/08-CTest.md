---
title: "CTest"
teaching: 20
exercises: 15
questions:
- "Key question (FIXME)"
objectives:
- "Use CTest to run a suite of automatic tests"
keypoints:
- "enable_testing()"
- "add_test()"
- "configure_file()"
---

CTest is the testing framework associated to CMake. It can be used to run a
batch of test programs.  
Compared to unit test frameworks like `pytest` and `unittest` for Python,
`Googletest` for C++ or `JUnit` for Java, which allow you to define tests
as smaller units of code, CTest requires the user to write tests as
program invocations. It can require more boilerplate code than other 
frameworks and tend to encourage copy-paste. On the other hand, its use is
pretty simple and language-independent (it is based on the CMake syntax
and on the underlying shell for execution of the tests).

## Adding tests to the build system.

For this section, we will be writing the CTest-related part of a 
CMake-built project. You can clone the repository [here](https://github.com/mmesiti/sudoku). 

```bash
git clone https://github.com/mmesiti/sudoku.git
cd sudoku
```
The `master` branch contains all the tests.
Please checkout to the `notest` branch:
```bash
git checkout notest
```
create a `build` directory to sandbox all our activities, and build the 
software
```bash
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=.
make 
```
You might need to load a module that allows the use of a recent compiler, 
and a recent cmake version:
```
module load cmake
module load compiler/gnu
```
In case of errors, you might also need to clear the CMake cache. There is
already a directory `test` containing the source code of some test 
programs. We are now going to add some of them to the build system and 

FIXME








{% include links.md %}

