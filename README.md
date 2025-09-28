# Worker Task Simulation

**Assignment:** Assessment 1 – Worker Task Simulation  
**Author:** Roland  

This program simulates task performance by multiple workers, calculates their average performance on each task, and assigns the task to the best-performing worker.
Comments are intentionally verbose to meet academic marking requirements. In practice, I aim for clean, maintainable code with concise documentation.

---

## Files Included
- **driver.cpp** – Contains `main()`. Handles reading the input files (`Tasks.txt` and `Workers.txt`) and calling functions to process and output task information.  
- **header.h** – Header file containing the function prototypes and struct definitions (`Worker` and `Task`).  
- **header.cpp** – Implementation file containing the function definitions for reading files, calculating average performance, and processing/printing task info.  
- **README.md** – This file describing the content and how to run the code.  

---

## How to Run
1. Ensure `Tasks.txt` and `Workers.txt` are in the same directory as your source code.  
2. Navigate to the directory containing `driver.cpp`, `header.h`, `header.cpp`, `Tasks.txt`, and `Workers.txt`.  
3. Compile the code using a C++17 compliant compiler:  
   ```bash
   g++ driver.cpp header.cpp -std=c++17 -o program
