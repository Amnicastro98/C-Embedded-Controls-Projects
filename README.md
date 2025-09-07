# C Embedded Controls Projects

A comprehensive collection of C programming projects demonstrating embedded systems concepts, industrial control systems, and real-time programming techniques. These projects showcase practical skills essential for embedded software engineering roles.

## Project Overview

This repository contains 5 progressive projects that build upon each other, demonstrating increasingly complex embedded systems concepts from basic control algorithms to advanced fault handling and system integration.

## Project Website

https://amnicastro98.github.io/Embedded-Software-Website/

## Projects

### 1. [PID Controller Simulation](./1%20PID%20Controller%20Simulation/)
**Focus**: Control Systems & Algorithms

A simple C program that simulates a PID (Proportional-Integral-Derivative) controller for motor speed control. This project demonstrates embedded control logic, floating-point calculations, and simulation of sensors/actuators in C.

**Key Features:**
- PID controller implementation with tunable gains (Kp, Ki, Kd)
- Simulated motor plant model with inertia and load
- Real-time setpoint control and response monitoring
- Educational comments explaining control theory

**Skills Demonstrated:**
- Control algorithm implementation
- Floating-point mathematics in embedded systems
- Real-time simulation techniques
- System modeling and plant simulation

---

### 2. [VFD Emulator](./2%20VFD%20Emulator/)
**Focus**: Industrial Motor Control

A C program that emulates the operation of a Variable Frequency Drive for motor speed control. This project demonstrates industrial drive control concepts, state machines, and real-time simulation.

**Key Features:**
- Complete VFD state machine (OFF → STARTING → RUNNING → STOPPING)
- V/F (Voltage/Frequency) scalar control algorithm
- Ramp control for smooth acceleration/deceleration
- Simulated 3-phase motor with inertia and torque
- Interactive command interface

**Skills Demonstrated:**
- State machine implementation
- Industrial motor control concepts
- Real-time system simulation
- Command-line interface design
- Numerical control algorithms

---

### 3. [Sensor & Actuator Integration Simulation](./3%20Sensor%20&%20Actuator%20Integration%20Simulation/)
**Focus**: Hardware Interface & I/O Systems

This project simulates an embedded control system that reads sensor inputs (temperature, pressure, level) and controls actuators (motor, valve, LED) accordingly. Demonstrates hardware signal processing, ADC/DAC simulation, and real-time control logic.

**Key Features:**
- Multi-sensor simulation (temperature, pressure, level)
- Actuator control with setpoint management
- ADC/DAC simulation with realistic noise
- Digital I/O with bitwise operations
- Automated control logic and real-time monitoring

**Skills Demonstrated:**
- Sensor data acquisition and processing
- Actuator control and feedback systems
- Analog-to-digital conversion principles
- Digital signal processing
- Hardware abstraction layers
- Real-time embedded system design

---

### 4. [Debugging-Fault Simulation](./4%20Debugging-Fault%20Simulation/)
**Focus**: System Reliability & Diagnostics

This project demonstrates advanced debugging techniques and fault simulation for embedded systems. Showcases comprehensive error handling, logging, state tracking, and recovery mechanisms essential for robust embedded software.

**Key Features:**
- Multi-level logging system (Debug, Info, Warning, Error, Critical)
- File I/O logging with persistent storage
- Fault simulation (sensor noise, actuator failure, communication breakdown)
- Automatic recovery mechanisms
- Real-time debug display and performance metrics

**Skills Demonstrated:**
- Comprehensive error handling strategies
- Multi-level logging and debugging
- Fault injection and recovery testing
- System health monitoring
- State validation and assertions
- File I/O with error handling

---

### 5. [Excel Commissioning File System](./5%20Excel%20Commissioning%20File%20System/)
**Focus**: Configuration Management & Data Persistence

This project simulates a commissioning file system commonly used in embedded control systems for parameter configuration, calibration data, and system setup. Demonstrates file I/O, CSV parsing, parameter validation, and data persistence.

**Key Features:**
- CSV file I/O operations (read/write configuration files)
- Parameter validation with safety limits
- Interactive menu-driven interface
- Data persistence and recovery
- System commissioning workflow simulation

**Skills Demonstrated:**
- File input/output operations
- CSV parsing and data validation
- Configuration file management
- Parameter validation and safety limits
- Data persistence and recovery
- User interface design

## Technical Requirements

### Development Environment
- **Compiler**: GCC (MinGW on Windows, native on Linux/Mac)
- **Standard**: C99 compatible
- **Libraries**: Standard C libraries (stdio, stdlib, string, math)

### Platform Support
- **Windows**: MSYS2 with MinGW-w64
- **Linux**: GCC with standard libraries
- **macOS**: Clang/GCC with standard libraries

## Getting Started

### Quick Setup (All Projects)
```bash
# Clone or download the repository
cd "C Embedded Controls Projects"

# Each project contains its own compilation instructions
# Navigate to any project directory and follow its README
cd "1 PID Controller Simulation"
gcc pid_simulation.c -o pid_simulation -lm
./pid_simulation
```

### Project Dependencies
- **Math Library**: Required for floating-point operations (`-lm` flag)
- **Time Library**: Used in simulation timing
- **Standard I/O**: File operations and console I/O

## Learning Progression

The projects are designed to build progressively:

1. **Foundation**: Basic control algorithms and simulation
2. **Control Systems**: Industrial motor control and state machines
3. **Hardware Integration**: Sensor/actuator interfaces and I/O
4. **System Reliability**: Debugging, fault handling, and diagnostics
5. **Data Management**: Configuration files and persistence

## Skills Demonstrated

### Core Programming Skills
- C programming fundamentals
- Data structures and algorithms
- Memory management
- File I/O operations
- Error handling and recovery

### Embedded Systems Concepts
- Real-time programming
- Hardware abstraction
- Interrupt handling simulation
- State machine implementation
- Control algorithm design

### System Design & Architecture
- Modular code organization
- Interface design
- Configuration management
- Logging and debugging
- Testing and validation

## Contributing

This repository is designed for educational purposes. Each project includes:
- Comprehensive documentation
- Educational code comments
- Build automation (Makefiles)
- Example configurations
- Usage instructions

## License

MIT License


---
