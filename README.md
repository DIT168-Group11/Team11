# Communicating and Lane-Following Vehicle Swarm

## Introduction
This project is a part of a collaboration between different teams in order to acheive communication between cars, and autonomous lane following.

## Description of folder layout

  ### Representation of the layout
  - src 
  - test 
  - lib 
  - bin 
  - build 
  - doc
  - include
  - docker

  ### How the layout works
  - src is used for storing the source files for the application.
  - test is a folder where all the tests cam be found.
  - lib is used to store all the libraries needed for the program to run.
  - bin a folder that consists of all the executables.
  - build contains all object files.
  - doc is used for storing documentation and notes from the developers
  - include is a folder where all the header files can be found.
  - docler location of the docker build files.

## Cloning, Building and Testing the Project

### Cloning
Clone the file using git with fetching information from our githubpage using the link from our repository or download it from the github page as a .Zip file. 

### Building
Go to the build folder using terminal and use `cmake ..` command and afterward run the `make` command.

### Testing
After you are done with the building run the main binary `./main` open a new terminal in the build folder and run the main binary `./main` again, after doing so the program should expect you to write a number after entering it the second terminal should be showing the entered nummber.
