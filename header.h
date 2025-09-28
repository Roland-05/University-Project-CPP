#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <array>


// Struct: Task
// Represents a single task with details about difficulty, uncertainty, priority, 
// and the workers assigned to it.

struct Task {
    std::string taskId;                          // Unique identifier for the task
    std::string description;                     // Task description
    double uncertainty;                          // Uncertainty level of task performance
    double difficulty;                           // Task difficulty level
    int priorityLabel;                            // Priority of the task (1 = high, else normal)
    std::array<std::string, 20> workers;         // IDs of assigned workers (max 20)
    int numWorkersAssigned;                       // Number of workers currently assigned
};


// Struct: Worker
// Represents a worker with performance-related attributes.

struct Worker {
    std::string workerID;     // Unique identifier for the worker
    std::string name;         // Worker's name
    double variability;       // Variability in performance
    double ability;           // Ability level
    int experienceLabel;      // Experience level (1 = senior, 0 = ordinary)
};

// Function prototypes


// Reads a single line from a tasks file and returns a Task struct
Task readTasksFileLine(std::string& line);

// Reads all tasks from a file into the provided array, returns number of tasks read
int readAllTasks(std::string& filename, Task tasks[]);

// Reads a single line from a workers file and returns a Worker struct
Worker readWorkersFileLine(std::string& line);

// Reads all workers from a file into the provided array, returns number of workers read
int readAllWorkers(std::string& filename, Worker workers[]);

// Finds a worker by their ID in the given array and returns a pointer to it
// Returns nullptr if the worker is not found
Worker* findWorkerById(const std::string& id, Worker workers[], int numWorkers);

// Calculates the average performance of a worker on a given task
double calculateAveragePerformance(const Task& task, const Worker& worker);

// Processes all tasks and workers and writes detailed output to a file
void processAndPrintTaskInfo(Worker workers[], Task tasks[], std::string& outputFileName, int numWorkers, int numTasks);

#endif
