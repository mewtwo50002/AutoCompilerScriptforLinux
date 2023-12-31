# AutoCompilerScriptforLinux
A C++ utility for  C++ file compilation and automated logging. Ideal for managing assignments and labs with an intuitive interface.
This C++ program, FolderSwitcher-and-Compiler, is a versatile utility designed to assist users in navigating and compiling files within different directories, commonly used in educational settings, such as assignments and lab work. It combines file management, directory navigation, and compilation tasks into a single interactive tool.

IMPORTANT 
Files must be in a specific structure to work

Example: cs120/Assignment/assignment1/(all the files in the assignment1 folder)
edit: Now with the first release, you are able to custumize to change the code easily

The reason for this is it was built for a file directory that I use.

Key Features:

Directory Navigation: Easily switch between different directories representing assignments and labs by specifying 'A' or 'L' when prompted.

File Compilation: Compile C++ source files (.cpp) into executables with the GCC (GNU Compiler Collection) compiler.

Logging: Automatically create and maintain log files (log_filename_time code was launched at.txt) to record compilation timestamps.

Timestamps: Display timestamps for compilation events, including the initial compilation.

Interactive: Provides a user-friendly command-line interface for input and interaction.

How to Use:

Run the program and select whatever file you edited
Enter the child folder number.
Specify the filename (without the .cpp extension) you want to compile.
The program will compile the file, create or update log files, and display compilation timestamps.
It will wait for 5 seconds and then recompile, continuously updating the log.
This repository contains the source code for the AutoCompilerforLinux. Feel free to explore, use, and customize it to suit your needs for managing work efficiently.

