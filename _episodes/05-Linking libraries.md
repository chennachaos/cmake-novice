---
title: "Linking libraries"
teaching: 15
exercises: 15
questions:
- "Key question (FIXME)"
objectives:
- "First learning objective. (FIXME)"
keypoints:
- "First key point. Brief Answer to questions. (FIXME)"
---

## Linking to well known packages: find modules

Very often building software requires pointing the compiler towards the proper
header files, and the linker towards the proper static libraries.  
If the headers and the libraries are part of an established package, it is
likely that there is a *find module* already created that may help you with
locating said package on the system where you are building the software.  
A list of find modules that are provided by the CMake distribution is available here: [A list of find modules available in CMake](https://cmake.org/cmake/help/latest/manual/cmake-modules.7.html)

In the following example we want to compile our programs 

```cmake
find_package(MPI REQUIRED)

file(GLOB_RECURSE sources src/*.f90)
add_executable(main programs/main.f90 ${sources})
target_include_directories(main PRIVATE ${MPI_Fortran_INCLUDE_PATH})
target_link_libraries(main ${MPI_Fortran_LIBRARIES})
```


{% include links.md %}
