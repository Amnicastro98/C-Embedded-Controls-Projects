# VFD (Variable Frequency Drive) Emulator

A C program that emulates the operation of a Variable Frequency Drive for motor speed control. This project demonstrates industrial drive control concepts, state machines, and real-time simulation.

## Features

- Complete VFD state machine (OFF → STARTING → RUNNING → STOPPING)
- V/F (Voltage/Frequency) scalar control
- Ramp control for smooth acceleration/deceleration
- Simulated 3-phase motor with inertia
- Real-time command interface
- Educational comments explaining industrial control concepts

## Skills Demonstrated

- C programming for embedded systems
- State machine implementation
- Numerical calculations and control algorithms
- Input/output signal simulation
- Real-time system simulation
- Industrial motor control concepts

## How to Compile and Run

### Windows (MSYS2)
1. Open MSYS2 MinGW x64 terminal
2. Navigate to the project directory
3. Compile: `gcc vfd_emulator.c -o vfd_emulator.exe -lm`
4. Run: `./vfd_emulator.exe`

### Linux/Mac
1. Navigate to the project directory
2. Compile: `gcc vfd_emulator.c -o vfd_emulator -lm`
3. Run: `./vfd_emulator`

## Usage

The program provides an interactive command interface:

- `s` - Start the VFD
- `x` - Stop the VFD
- `f <freq>` - Set target frequency (0-60 Hz)
- `q` - Quit the program

## Example Output

```
VFD (Variable Frequency Drive) Emulator
=======================================

Commands:
s - Start VFD
x - Stop VFD
f <freq> - Set frequency (0-60 Hz)
q - Quit

Enter command: s
VFD starting...
State: STARTING | Freq: 3.0 Hz | Volt: 24.0 V | Speed: 90.0 RPM | Torque: 27.00 Nm
State: STARTING | Freq: 6.0 Hz | Volt: 48.0 V | Speed: 180.0 RPM | Torque: 24.00 Nm
...
State: RUNNING | Freq: 30.0 Hz | Volt: 240.0 V | Speed: 900.0 RPM | Torque: 0.00 Nm
```

## Technical Details

- **V/F Control**: Maintains constant voltage-to-frequency ratio for optimal motor performance
- **Ramp Control**: Prevents sudden speed changes that could damage equipment
- **State Machine**: Ensures safe and predictable drive operation
- **Motor Simulation**: Models real-world motor behavior with inertia and torque

## Learning Outcomes

This project helps understand:
- How industrial VFDs work
- Motor control principles
- State-based system design
- Real-time simulation techniques
- Command-line interface design
