# P-RAY code repository
A Self study project for learning Ray tracing currently CPU based.
The project is based on the book "Ray Tracing from the Ground Up" by Kevin Suffern.

## Building
#### Linux
1) First make sure you have CMake, Git, and GCC by typing as root (sudo) `apt-get install g++ cmake git` and then get the required packages:
Using root (sudo) and type `apt-get install  libglm-dev libglew-dev libglfw3-dev`.
2) Create a build directory and change directory to the new build dir. There we run the `cmake ..`, it will generate necessary files and check for all the dependancies and create a make file. Then just type `make` in the terminal. This will generate the executables in the build folder.

#### Windows
If you have Visual Studio then Jump to Step 2 in the Linux build instruction. You can also try for MinGW compiler.

To sum it up:
```
git clone  https://github.com/surajsubudhi10/CG184.git
mkdir build
cd build
cmake ../.
make .
```

## Features


## Examples