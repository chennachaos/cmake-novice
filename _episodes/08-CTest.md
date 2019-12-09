---
title: "CTest"
teaching: 20
exercises: 15
questions:
- "What is testing?"
- "How can CTest help me with managing my tests?"
objectives:
- "Use CTest to run a suite of automatic tests"
keypoints:
- "`include(CTest)` to allow testing"
- "`add_test()` to create a new test specifying a command"
- "`configure_file()` to copy the necessary files in the build directory"
---

## The importance of test automation

When writing software, even the most reckless programmer wants to know if 
the code that has been written works right or not. Arguably most of people 
that write code go through the step of doing some sort of check, at least 
by running a small program and visually inspecting the results.  
This *might* be enough for throwaway code that is written once and never 
changed, but each time the code is changed in any significant way, a reasonable
programmer would check the correctness of the program again. As the code 
becomes more and more complex, this strategy just does not scale, to
the point that it may become too time consuming to verify with a 
satisfying degree of certainty that the program works after any change or 
extension, which means that no sensible person is going to be change or 
extend it any more.

There are many strategies to cope with this, each presenting its own advantages
and disadvantages. It is widely accepted, though, that an automatic test suite
is hugely beneficial in reducing the cost of understanding whether the code 
works right or not, making extensive changes to the code possible again. 

> ## Is it worth it?
> Think about some projects you are/were involved in where writing software
> was necessary.
> * Was there any test program you could run? Was an automatic test suite 
>   available? If so, was it useful?
> * If not, would an automatic test suite be beneficial? 
> * What are the trade-offs involved in writing a test suite? Would it be 
>   worth it?
{: .discussion}

## CTest and CMake

CTest is the testing framework associated to CMake. It can be used to run a
batch of test programs.  
Compared to unit test frameworks like Pytest and Unittest for Python,
Googletest for C++ or JUnit for Java, which allow you to define tests
as smaller units of code, CTest requires the user to write tests as
program invocations which need to return proper error codes.
It can require more boilerplate code than other 
frameworks, on the other hand its use 
is simple and language-independent, as it accepts any shell command as a test
definition.

## Adding tests to the build system

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
```bash
module load cmake
module load compiler/gnu
```
In case of errors, you might also need to clear the CMake cache. There is
already a directory `test` containing the source code of some test 
programs. We are now going to create a test and add it to the build system.
First of all, we need to add the `tests` directory in the
root `CMakeLists.txt`:
```cmake
enable_testing()
add_subdirectory(tests)
```
we can then, in the `tests` directory, create a `CMakeLists.txt` file 
with the following content:
```cmake
add_executable(test_algorithms test_algorithms.cpp)
target_link_libraries(test_algorithms common algo1 algo2)
```
This code does the following:
* creates the executable program from the source `test_algorithms.cpp` 
* links it with the library targets `common`, `algo1` and `algo2`.  

The program test reads a Sudoku table, runs one of the algorithms on it with 
a maximum number of iterations and checks whether or not a solution is found
and if it matches a known solution.
In order for this test to run, we need to copy a file containing the Sudoku
table for the test case to the directory where the tests are run
and the table containing the expected result. For this,
we use the `configure_file()` function in its simplest form ([documentation](https://cmake.org/cmake/help/latest/command/configure_file.html)): 
```cmake
configure_file(../example_tables/table1.txt table1.txt COPYONLY)
configure_file(output_table1.txt output_table1.txt COPYONLY)
```
We can then add the test command to check that the algorithm 1 works:
```cmake 
add_test(test_algorithms_11 test_algorithms table1.txt output_table1.txt 1) 
```
Now we can go build the test with `make` and run it with `make test`.

> ## foreach()
> In case we have more test cases to run the same programs on, we can
> use the `foreach()` construct:
> ```cmake
> foreach( ALGORITHM IN ITEMS 1 2)
>     foreach(TABLE IN ITEMS table1.txt table2.txt) 
>         add_test(test_algorithms_${ALGORITHM}_${TABLE} test_algorithms ${TABLE} output_${TABLE} ${ALGORITHM}) 
>     endforeach()
> endforeach()
> ```
{: .callout}

{% include links.md %}

