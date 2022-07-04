Name: Nicholas Kong 
ID: 105737913
Class: CSCI 3453
Lab 2
Due Date: March 8, 2020

Structure of program:
---------------------
File organization: main.cpp
Functional organization: The c++ program has 3 functional scheduling algorithms which evaluates performance and takes in user input for number of processes, processes arrival times and processes burst times. 

Status: It works completely. All functions of the 3 scheduling algorithms are functional.

Hardware & Platform I used: 2.7 GHz Intel Core i5 processor with 8GB 1867 MHz DDR3 Memory.
Version 10.12.5


*******************************************************
*  Source files
*******************************************************

Name: main.cpp
	Main holds all of my functions. I have 3 functions which are: Shortest Remaining Task First, First Come First Serve, and Round Robin. For Shortest Remaining Task First, it will check all the burst times and since it is preemptive, it will take the CPU away from a current task and finish the shortest tasks first. First Come First Serve will do any task that comes first. Round Robin will take into account quantum and keep switching between process when the quantum for each process is met. 

*******************************************************
*  Circumstances of programs
*******************************************************

   The program runs successfully.
   
   The program was developed and tested on gnu g++ 4.4.2.  It was 
   compiled, run, and tested on gcc ouray.cudenver.edu.


*******************************************************
*  How to build and run the program
*******************************************************

1. Uncompress the homework.  The homework file is compressed.  
   To uncompress it use the following commands 
       % unzip [Nicholas_Kong_Lab3.zip]

   Now you should see a directory named homework with the files:
        main.cpp
        makefile
        KongReadMe.txt

2. Build the program.

    Change to the directory that contains the file by:
    % cd [Nicholas_Kong_Lab3] 

    Compile the program by:
    % make

3. Run the program by:
   % ./[main]

4. Delete the obj files, executables, and core dump by
   %./make clean

5. Run the program again 
   %./main

*******************************************************
*  How to build and run the program Option 2
*******************************************************

g++ main.cpp -o main.o
