#README.txt
Assignment: Assessment 1 – Worker Task Simulation
Author: Roland Almeda
This program simulates task performance by multiple workers, calculates their average performance on each task, and assigns the task to the best-performing worker.
Files included:
driver.cpp – Contains main(). Handles reading the input files (Tasks.txt and Workers.txt) and calling functions to process and output task information.
header.h – Header file containing the function prototypes and struct definitions (Worker and Task).
header.cpp – Implementation file containing the actual function definitions for reading files, calculating average performance, and processing/printing task info.
README.txt – This file describing the content and how to run the code.

How to run:
Ensure Tasks.txt and Workers.txt are in the same directory as your source code.
Navigate to the directory containing driver.cpp, header.h, header.cpp, Tasks.txt, and Workers.txt.
Compile the code using a C++17 compliant compiler using this command:
g++ driver.cpp header.cpp -std=c++17 -o program
Run the program by providing the input files and output file name as command-line arguments:
./program Tasks.txt Workers.txt Output.txt
Check Output.txt for the results.
