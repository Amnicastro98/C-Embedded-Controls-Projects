# PID Controller Simulation

A simple C program that simulates a PID (Proportional-Integral-Derivative) controller for motor speed control. This project demonstrates embedded control logic, floating-point calculations, and simulation of sensors/actuators in C.

## Features

- PID controller implementation with tunable gains (Kp, Ki, Kd)
- Simulated motor plant model with inertia and load
- User input for desired setpoint (RPM)
- Console output showing time, speed, and PID output over simulation steps
- Educational comments in the code

## Requirements

- GCC compiler
- Linux/Windows/Mac with terminal access

## How to Compile and Run

### Linux/Mac
1. Clone or download the repository.
2. Navigate to the project directory.
3. Compile the program:
   ```
   gcc pid_simulation.c -o pid_simulation -lm
   ```
4. Run the executable:
   ```
   ./pid_simulation
   ```
5. Enter the desired motor speed (RPM) when prompted.

### Windows
1. Install MSYS2 from https://www.msys2.org/
2. Open MSYS2 MinGW x64 terminal (not the base MSYS terminal)
3. Install GCC: `pacman -S mingw-w64-x86_64-gcc`
4. Navigate to the project directory. Example: cd "C:\Users\Username\Desktop ... "
5. Compile: `gcc pid_simulation.c -o pid_simulation.exe -lm`
6. Run: `./pid_simulation.exe`

## Example Output

```
PID Controller Simulation for Motor Speed Control
Enter desired motor speed (RPM): 100
Setpoint: 100.00 RPM
Time    Speed   PID Output
0.0     15.05   151.00
0.1     22.93   79.27
...
```

## Explanation

- **PID Controller**: Adjusts the control effort based on the error (setpoint - current speed), its integral, and derivative.
- **Plant Model**: Simulates motor speed changes based on input, inertia, and load.
- **Tuning**: Modify Kp, Ki, Kd in the code for different responses (e.g., stability vs. speed).



