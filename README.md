[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![GitHub release](https://img.shields.io/github/downloads/Naereen/StrapDown.js/v1.0.0/total.svg)](https://github.com/devMichani/nano-db-manager.git)

# nano-db-manager
Application of simulation of the internal functioning of a relational database engine. Application written in c++17 to manage database on a small scale, school project for the subject of __file__ __structure__

# Database
>   A database is an organized collection of data.

# Requirements
The project can be used with __C++11__. However, it requires __C++17__ to build, including compiler and standard library support. required to build the library __GCC 9.1.0__

# Installation of Package GCC
```sh
# normally this package is already installed in most unix-based 
# distributions e.g. GNU/Linux, Freebsd, etc.
# Install GCC in operating systems based on Debian.
$ sudo apt update
$ sudo apt install build-essential
$ sudo apt-get install manpages-dev
# Install GCC in operating systems based on ArchLinux
# alternative to build-essential
$ sudo pacman -Sy base-devel
# Install only gcc
$ sudo pacman -S gcc 
# Install GCC in operating systems based on redhat
$ sudo dnf install gcc
$ sudo dnf groupinstall "Development Tools"
# Finally check the installed version
$ gcc --version
```

# Installation of nano-db-manager
```sh
# Check out the project.
$ git clone https://github.com/devMichani/nano-db-manager.git
# Go to the project directory
$ cd nano-db-manager
# Generate a the executable file with make. 
$ make
# If you need to clean and rebuild the project just use make clean and make. 
$ make clean && make
# to run the project just go to the directory where the executable file is located.
$ cd /build/bin 
# Run the program.
$ ./nanodb
```

License
----

GNU Lesser General Public License v3.0

Oh Yeah! Free Software,  it's great, enjoy!
