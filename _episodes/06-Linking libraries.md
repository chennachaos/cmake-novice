---
title: "Linking and adding libraries"
teaching: 15
exercises: 15
questions:
- "How to link pre-installed libraries with application?"
- "How to link multiple libraries with an application?"
- "How to build and link libraries using source code?"
objectives:
- "To learn to link pre-installed libraries with application"
- "To learn to build and link libraries using source code"
keypoints:
- "We directories with header files using the `include_directories` function"
- "We add the libraries to be using the `link_directories` and 
  `target_link_libraries` functions"
---

## Linking pre-installed libraries manually
Many a times we will end up in situations where the software libraries
are not available in the form of modules, which is often the case on
our personal computers. In such situations, we have to link the libraries
manually by specifying the paths to the library files.

### Header files
To use the header files, we specify the path to the directory (where
the header files of the pre-installed library that we want to use) are
located to the CMake's `include_directories` function. For example, to 
use the header file `mpi.h` from the OpenMPI library, we write

```cmake
include_directories(
/usr/include/openmpi 
)
```

We can specify multiple libraries as follows.

```cmake
include_directories(
/usr/include/openmpi 
/usr/include/petsc 
/usr/include/boost
)
```

This is all one needs to do for the header files. CMake will look into all
these directories for the `.h` files used in the current project. We can also
add our own header files by adding the corresponding path. The paths can be
absolute or relative.

**Note:** These paths need not be in separate lines. Multiple paths can be specified
by separating them with spaces. Specifying them in separate lines is a good practice
since it gives a better visual picture of the libraries used in the project.


### Library files (*.so, *.a)
Similarly, we need to specify the paths to the directories of the library files using
the CMake's `link_directories` function. For example, to link blas and lapack libraries,

```cmake
link_directories(
/usr/lib/libblas
/usr/lib/lapack 
)

target_link_libraries(test_target blas  lapack)
```

Note that, for linking the library files, we not only have to specify the paths
using the `link_directories` function but also have to add the libraries that we want 
to the link to the target using the `target_link_libraries` function.

We can specify as many .so files to link as we want. For example,

```cmake

target_link_libraries(test_target stdc++ m gmp  mpfr  stdc++ gfortran gomp 
pthread blas  lapack  metis parmetis  petsc  mpi  mpi_cxx  superlu 
pardiso600-GNU720-X86-64  boost_thread boost_system  CGAL CGAL_Core 
CGAL_ImageIO vtkCommonCore-6.3  vtkIOCore-6.3  vtkIOGeometry-6.3  vtkIOXML-6.3)

```

## Building libraries from source code
Suppose we have a set of functions that we want to use a library. We can
do so by using the function `add_library`.

Let us consider that we have `myFunctions.h` and `myFunctions.cpp` in 
`myFunctions` folder in the current directory. Then, we can built this as a 
library and link it against a target as follows.

**Step 1:** Create a `CMakeLists.txt` file inside `myFunctions` folder
with the following line. 
```cmake
add_library(myFunctions myFunctions.cxx)
```

**Step 2:** Add the following lines to the main `CMakeLists.txt` file
of the project. 

```cmake
# add the MathFmyFunctionsunctions library
add_subdirectory(MathmyFunctionsFunctions)

# add the executable
add_executable(test_target test_program.cpp)

target_link_libraries(test_target myFunctions)
```


{% include links.md %}
