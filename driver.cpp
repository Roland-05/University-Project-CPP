#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <array>
#include "header.h"

// main() simply handles input arguments, declares arrays, and calls functions in header.cpp
// All parsing, processing, and output is handled by these functions to keep main() concise

int main(int argc, char* argv[]) {

    // Check if the correct number of command-line arguments is provided
    // The program expects no more than three arguments: Tasks file, Workers file, and Output file
    if (argc != 4) {
        std::cerr << "Please provide: Tasks.txt Workers.txt Output.txt" << std::endl;
        return 1; // exit with error code
    }

    // Get the file names from command-line arguments
    std::string tasksFile = argv[1]; // File containing tasks data
    std::string workersFile = argv[2]; // File containing workers data
    std::string outputFile = argv[3]; // File to write the output results to

    // Create arrays to store tasks and workers (will never store more than 20 workers or tasks
    Task tasks[20];
    Worker workers[20];

    // Read all tasks and workers from the input files
    // numTasks and numWorkers store how many tasks and workers were read
    int numTasks = readAllTasks(tasksFile, tasks);
    int numWorkers = readAllWorkers(workersFile, workers);
    
    // Process all tasks and workers and write detailed results to the output file
    processAndPrintTaskInfo(workers, tasks, outputFile, numWorkers, numTasks);
    
    // Program ends successfully
    return 0;
}




