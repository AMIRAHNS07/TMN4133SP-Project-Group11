# TMN4133SP-Project-Group11
SYSTEM PROGRAMMING PROJECT - supercommand

*Project Overview*
This project is a System Programming assignment for the course TMN4133. The objective is to implement a tool/command in C that provides various system operations through a command-line interface (CLI) on a Linux system. The tool allows users to perform file operations, directory operations, and keylogger functionality using system calls.

*Features*
1. File Operations:
- Create/Open a new file.
- Change file permissions.
- Read from a file and print to standard output.
- Write to a file from standard input.
- Delete a file.
  
2. Directory Operations:
- Create a directory.
- Remove a directory.
- Print the current working directory.
- List the contents of a directory.

3. Keylogger Operations:
- Run in the background of the terminal.
- Record keystrokes and save them to a file (keylog.txt).
- Add a timestamp to each keystroke entry.

*Requirements*
- Linux terminal (Ubuntu or any Linux distribution)
- Text editor (e.g., vi, nano)
- GCC compiler (GNU glibc)

*How to Compile*
(a) Clone the repository: 
git clone <repository-url>
cd <repository-folder>

(b) Compile the project using GCC:
gcc -o supercommand supercommand.c directory.c file_operations.c keylogger.c

*How to Use*
The supercommand tool allows users to interact with the system using the following command-line syntax: ./supercommand -m <mode> <operation> <file/dir/path>

*Modes and Operations*
1. File Operations (mode 1)
- Create a new file: ./supercommand -m 1 1 <filename>
- Change file permissions: ./supercommand -m 1 2 <filename> <permissions>
- Read from a file: ./supercommand -m 1 3 <filename>
- Write to a file: ./supercommand -m 1 4 <filename>
- Delete a file: ./supercommand -m 1 5 <filename>

2. Directory Operations (mode 2)
- Create a directory: ./supercommand -m 2 1 <dir_name>
- Remove a directory: ./supercommand -m 2 2 <dir_name>
- Print the current working directory: ./supercommand -m 2 3
- List the contents of a directory: ./supercommand -m 2 4 <dir_name>

3. Keylogger Operations (mode 3)
- Start recording keystrokes: ./supercommand -m 3 <logfile>

Example Commands: 
- Create a new file: ./supercommand -m 1 1 newfile.txt
  Mode 1 means file operations.
  Operation 1 means creating a new file.
  newfile.txt is the name of the file to be created.
  
- List contents of the current directory: ./supercommand -m 2 4 .
  Mode 2 means directory operations.
  Operation 4 means listing the directory contents.
  . refers to the current directory.
  
- Start logging keystrokes: ./supercommand -m 3 keylog.txt
  Mode 3 means keylogger operations.
  keylog.txt is the file where keystrokes will be recorded.

*Contributing*
To contribute to this project, please fork the repository and create a pull request with a detailed explanation of the changes you've made.

Steps to Contribute:
1. Fork the repository.
2. Create a feature branch:git checkout -b feature-branch
3. Make your changes and commit them: git commit -am "Add feature description"
4. Push to your forked repository:git push origin feature-branch
5. Create a pull request to the main repository.

*License*
This project is licensed under the MIT License - see the LICENSE file for details.

*Acknowledgements*
- Special thanks to our course instructor, Dr. Johari bin Abdullah for providing the project specifications.
- Special thanks to ChatGPT for helping with code generation, debugging, and writing documentation!

 
