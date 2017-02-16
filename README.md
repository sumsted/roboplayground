Robotplayground
===============

Makeblock mBot project, Arduino using C++

Sample code from Makeblock mbot firmware and code generated from sketch was used in the creation of this project.

Features
--------

1. All cpp code, the ino is empty
2. robotplayground.cpp contains setup and loop and instantiates SubSystems, Commands and SerialController
3. All mBot device interfaces are in SubSystems
4. Orchestration of mBot is in Commands
5. SerialController has the code that interfaces with the makeblock bloothtooth app
6. Handlers for ir remote and ir commands from master bot are in robotplayground.cpp
7. Use the board button to switch from master (red) to slave (blue)
8. Both master and slave may take commands from bluetooth
9. Master takes commands from ir remote
10. Slave ignores ir remote and takes commands from master
