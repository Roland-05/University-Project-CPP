#include <sstream>
#include <fstream>
#include <string>
#include <array>
#include <random>
#include <iostream>
#include <ctime>
#include <cmath>
#include "header.h"



Task readTasksFileLine(std::string& line) {

    // create a stream from the files line
    std::istringstream ss(line);

    // declare string variables to be used for Task struct
    // Use temp variables for non string types as getline can only parse into strings.
    std::string taskId, description, workers, temp_uncertainty, temp_difficulty, tempPriorityLabel;
    // declare double variables for Task struct
    double uncertainty, difficulty;
    // declare priority Label as an int, 1 indicates high priority and 0 low priority
    int priorityLabel;
    // declare an array of strings, size set to 20 as no more than 20 workers. 
    std::array<std::string, 20> workerIDs;

    
    getline(ss, taskId, ','); // Extract task ID up to the first comma
    
    getline(ss, description, ';'); // Extract task description up to the semicolon
    
    getline(ss, temp_uncertainty, '$'); // Extract the uncertainty as a string up to the '&' delimiter

    getline(ss, temp_difficulty, '%'); // Extract the difficulty as a string up to the '%' delimiter

    // Convert the string values to doubles
    uncertainty = std::stod(temp_uncertainty);
    difficulty = std::stod(temp_difficulty);

    // Extract the priority label as a string up to the '&' delimiter
    getline(ss, tempPriorityLabel, '&');
    // Convert the string to an integer
    priorityLabel = std::stoi(tempPriorityLabel);

    // discard "workers" prefix
    std::string dummy;
    getline(ss, dummy, ':');  // this will read "workers:" and discard it

    // contain the full list of workers
    std::string workersList;
    // parse the list of workers separated by commas into the string
    getline(ss, workersList);

    // Create a stream for the list of workers
    std::istringstream workerStream(workersList);

    //Set index to equal 0 which will eventually give the number of workers assigned to the task
    int index = 0;

    // Declare a string variable to store a unique workerID
    std::string workerID;
    // Loop through list of workers stream, extracting each workerID until none left
    while (getline(workerStream, workerID, ',')) {

        // Trim whitespace and carriage return
        // The last worker ID had a trailing '\r' (from Windows line endings),
        // which caused it not to match when searching for the worker.
        workerID.erase(0, workerID.find_first_not_of(" \t\r\n"));
        workerID.erase(workerID.find_last_not_of(" \t\r\n") + 1);
        // Store the workerID in the array at an incremental position/index
        workerIDs[index++] = workerID;
       
    }
    // Initialise a Task object with its ID, description, uncertainty, difficulty, and priority
    Task task;
    task.taskId = taskId;
    task.description = description;
    task.uncertainty = uncertainty;
    task.difficulty = difficulty;
    task.priorityLabel = priorityLabel;

    // Copy only valid index elements into task.workers
    for (int i = 0; i < index; i++) {
        task.workers[i] = workerIDs[i];
    }
    // Get the number of workers assigned to the task and intialise it to the task object
    task.numWorkersAssigned = index;
    // Return the task object
    return task;

}


int readAllTasks(std::string& filename, Task tasks[]) {
    // open the tasks.txt file
    std::ifstream inFile;
    inFile.open(filename);

    if (!inFile) {  // check if file opened successfully
        std::cerr << "Error opening tasks file: " << filename << std::endl;
        return 0;   // return 0 tasks if file cannot be opened
    }

    // declare line of type string to store a line of the file
    std::string line;
    // intialise count variable to 0
    int count = 0;

    while (getline(inFile, line)) {
        // Parse the line into a task object using the the read tasksFileLine function
        // and store it into the tasks array at the current index
        tasks[count] = readTasksFileLine(line);
        // Increment count to move on to the next position in the workers array
        count++;
    }
    inFile.close();
    // Return the total number of tasks
    return count;
    
}

// return a pointer in case no worker is found
Worker* findWorkerById(const std::string& id, Worker workers[], int numWorkers) {
    // loop for all workers
    for (int i = 0; i < numWorkers; i++) {
        // check if the id matches any of the workers id's
        if (id == workers[i].workerID) {
            return &workers[i]; // return pointer to the worker that matches the id
        }
    }
    // return a nullptr if no worker matching the id is found
    return nullptr;
}


Worker readWorkersFileLine(std::string& line) {
    // Create a string stream from the input line to parse its contents
    std::istringstream ss(line); 

    // Declare string variables to be used for Worker struct
    // Use temp variables for non string types as getline can only parse into strings.
    std::string workerID, name, temp_variability, temp_ability, temp_experienceLabel;
    double variability, ability;
    int experienceLabel;

    // Extract values from the line using specific delimiters
    getline(ss, workerID, ',');          // Read workerID up to the comma
    getline(ss, name, '%');              // Read name up to the '%' character
    getline(ss, temp_variability, '$');  // Read variability as string up to '$'
    getline(ss, temp_ability, ';');      // Read ability as string up to ';'
    getline(ss, temp_experienceLabel);   // Read the rest of the line as experienceLabel

    // Convert string representations to numeric types
    experienceLabel = std::stod(temp_experienceLabel); // Convert experienceLabel to int
    variability = std::stod(temp_variability);        // Convert variability to double
    ability = std::stod(temp_ability);                // Convert ability to double

    // Create a Worker object and assign all parsed and converted values
    Worker worker;
    worker.workerID = workerID;
    worker.name = name;
    worker.variability = variability;
    worker.ability = ability;
    worker.experienceLabel = experienceLabel; 
    
    // Return the Worker object
    return worker;
}


int readAllWorkers(std::string& filename, Worker workers[]) {
    // Open the workers.txt file
    std::ifstream inFile;
    inFile.open(filename);

    if (!inFile) {  // check if file opened successfully
        std::cerr << "Error opening workers file: " << filename << std::endl;
        return 0;   // return 0 workers if file cannot be opened
    }

    // Declare line of type string to store a line of the file
    std::string line;
    // Initialise count to 0. This will eventually store the total number of workers 
    int count = 0;

    // loop for every line in the file 
    while (getline(inFile, line)) {
        // Parse the current line into a worker object using the read workersFileLine function
        // and store it into the workers array at the current index
        workers[count] = readWorkersFileLine(line);
        // Increment count to move to the next position in the workers array
        count++;
    }

    inFile.close(); // Close the file

    // Return the total number of workers
    return count;



}

// Calculate the average performance of a worker on a given task
// Takes into account worker ability, variability, experience, 
// task difficulty, uncertainty, and priority
double calculateAveragePerformance(const Task& task, const Worker& worker) {
    // Declare variables mean, standardDeviation and performance score
    double mean, standardDeviation, performanceScore;

    // Calculate mean performance as worker ability minus task difficulty
    mean = worker.ability - task.difficulty;
    // Calculate standard deviation as sum of task uncertainty and worker variability
    standardDeviation = task.uncertainty + worker.variability;

    // Declare variable that will store the number of samples 
    int numSamples;
    // Determine number of samples based on task priority
    if (task.priorityLabel == 1) {
        numSamples = 15; // High priority task gets more samples
    } else {
        numSamples = 10; // Normal priority task
    }

    double sum = 0; // Initialise sum of performance samples

    // Create a random number generator seeded with current time
    std::default_random_engine generator(std::time(nullptr));
    // Define a normal distribution with the calculated mean and standard deviation
    std::normal_distribution<double> dist(mean, standardDeviation);

    // Generate performance samples and accumulate their sum
    for (int i = 0; i < numSamples; i++) {
        sum += dist(generator);
    }

    // Calculate the average performance over all samples
    double average = sum / numSamples;

    // Apply experience bonus if worker has experience label 1
    if (worker.experienceLabel == 1) {
        average += 2;
    }

    // Return the final average performance
    return average;
}


void processAndPrintTaskInfo(Worker workers[], Task tasks[], std::string& outputFileName, int numWorkers, int numTasks) {
    // Create and open an output file stream to write results to the specified file
    std::ofstream outFile;
    outFile.open(outputFileName);

    // Check if the file could not be opened
    if (!outFile) {

        std::cerr << "Error opening file: " << outputFileName << std::endl;
        return; // Exit the function if file opening fails
    }
    
    // Write header for the worker information section
    outFile << "WorkerID" << "\t" << "Name" << "\t" << "Variability"
              << "\t" << "Ability" << "\t" << "Experience" << std::endl;

    // Loop through all workers and write their information to the file
    for (int i = 0; i < numWorkers; i++) {
        Worker worker = workers[i];

        outFile << i << "\t" << "\t"
                << worker.name 
                << "\t" << "\t"
                << worker.variability 
                << "\t" 
                << worker.ability << "\t" 
                << worker.experienceLabel << std::endl;
    }

    // Process each task and print its details
    for (int t = 0; t < numTasks; t++) {
        Task& task = tasks[t];

        // Separator line for readability
        outFile << "==================================================================" << std::endl;

        // Print task information
        outFile << "processing taskId:\t" << task.taskId << std::endl;
        outFile << "description\t:\t" << task.description << std::endl;
        outFile << "uncertainty\t:\t" << task.uncertainty << std::endl;
        outFile << "difficulty\t:\t" << task.difficulty << std::endl;
        outFile << "priority\t:\t" << task.priorityLabel << std::endl;

        // Print IDs of all workers assigned to this task
        outFile << "workers\t\t:\t";
        for (int i = 0; i < task.numWorkersAssigned; i++) {
            std::string workerID = task.workers[i];
            if (i == task.numWorkersAssigned - 1) {
                outFile << workerID << std::endl; // Last worker: end the line
            } else {
                outFile << workerID << ","; // Separate workers with a comma
            }
        }

        outFile << "==================================================================" << std::endl;

        // Variables to track the highest average performance and corresponding worker
        double highestAverage = 0;
        std::string bestWorkerID = ""; // Initilise default in case no workers are found

        // Loop through each worker assigned to the task and calculate performance
        for (int i = 0; i < task.numWorkersAssigned; i++) {
            outFile << "Trial (" << i + 1 << "/" << task.numWorkersAssigned << ")" << std::endl;

            std::string workerID = task.workers[i];

            // Find the worker object by ID
            Worker* worker = findWorkerById(workerID, workers, numWorkers);
            outFile << "------------------------------------------------------------------" << std::endl;

            if (!worker) {
                continue; // Skip this iteration if worker is not found
            }

            // Indicate if the worker is senior or ordinary
            if (worker->experienceLabel == 1) {
                outFile << "Senior workers: " << worker->workerID << std::endl;
            } else {
                outFile << "Ordinary workers: " << worker->workerID << std::endl;
            }

            outFile << "------------------------------------------------------------------" << std::endl;

            // Calculate the average performance of the worker for this task
            double average = calculateAveragePerformance(task, *worker);
            outFile << "The average performance is " << std::round(average) << std::endl;
            outFile << "------------------------------------------------------------------" << std::endl;

            // Track the worker with the highest performance
            if (average > highestAverage) {
                highestAverage = average;
                bestWorkerID = worker->workerID;
            }
        }

        // Print the worker assigned to the task based on highest performance
        outFile << "------------------------------------------------------------------" << std::endl;
        outFile << "This task is assigned to worker " << bestWorkerID << "\n" << std::endl;
    }

    // Close the output file to save all changes
    outFile.close();
}
