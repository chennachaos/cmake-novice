---
title: Setup
---

## Data files

You need to download some files for the exercises in this course.
1. Down [exercises.zip](../data/exercises.zip)
2. Unzip/extract files.
2. Copy `exercises` folder to your home directory on your account on Sunbird.
   If you are working locally, then copy it to some convenient location.

## Terminal

For this course, we will use `Sunbird`, the Supercomputing Wales cluster.
If you do not already have account on Sunbird, then please apply for one
before attending the course. Go to the website
<https://my.supercomputing.wales/> and then login with your university credentials.
Once you login, then request to join a project.

For accessing Sunbird, you need an SSH client and the FileZilla application.
For the details on installing these software on your laptop, refer to
 <https://edbennett.github.io/SCW-tutorial/setup>

## Laptops with Linux or Mac OS
If you have a Linux-based or Mac OS on your laptop, then you can work from
them without having to access Sunbird.

In case, you prefer this option, then install GNU compilers and CMake from
the package list.

### Ubuntu
On Ubuntu, you can install CMake using the following command.
~~~
sudo apt-get install cmake
~~~
{: .language-bash}

Note that you need the password for the `root`.

### Mac OS
Refer to <https://tudat.tudelft.nl/installation/setupDevMacOs.html> for 
the CMake installation instructions on Mac OS.

## Windows
Installation of CMake on Windows is so much more involved. We do not recommend
it unless you have no other option of using CMake. For the details, refer to
<https://tudat.tudelft.nl/installation/setupDevWindows.html>


{% include links.md %}
