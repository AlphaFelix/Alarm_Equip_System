# Alarm_System
System for registering and handling alarms and equipment.

To run, compile the main with the others .c archives and execute the main.exe.
```c
g++ main.c data.c input.c output.c stateMachine.c -o main
./main
```
## Application itens
- [X] Equipment registration (CRUD);
- [X] Alarm registration (CRUD);
- [X] Manipulation of alarms and equipments;
- [X] Console interface;
- [X] All system data saved in a txt;

## Libraries
The system is divided into multiple libraries, each responsible for a part of the code. In the main.c, the code is in an infinite loop.

### data.h 
Library in charge of creating the txt database and manipulating system data.

### input.h
Library in charge of handling the user inputs, mainly the keyboard in this case.

### output.h
Library in charge of controlling the menu that is printed on the terminal.

### stateMachine.h
Library in charge of creating and controlling the state machine

## Next upgrades :
* Substitution of the conio.h Library;
* Asynchronous keyboard input;
* Terminal refresh following changes in variables;
* Optimization of the menus, states and database;
* Use of buffers to adequate the variables to the size of the strings;
* Restrict the input to only accept the precise types; 
* Graphical user interface;

## Next Version:
The upcoming version may facilitate some of the updates, but it requires a redesign of the system.
* Use of threads and mutex;      
