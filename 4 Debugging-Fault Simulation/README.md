# Debugging & Fault Simulation System

## Overview

This project demonstrates advanced debugging techniques and fault simulation for embedded systems. It showcases comprehensive error handling, logging, state tracking, and recovery mechanisms that are essential for robust embedded software development.

## What to Expect

When running the simulation, you will see a command-line interface with the following commands:

- `f` - Inject a controlled random fault to test the system's fault handling.
- `r` - Attempt to recover from any active faults.
- `d` - Display detailed debug information including system state, fault history, and performance metrics.
- `q` - Quit the simulation.

The system simulates faults such as sensor noise, actuator failure, communication breakdown, power fluctuations, and memory corruption. Faults only occur when explicitly injected, ensuring stable normal operation. The recovery mechanism attempts to resolve faults and return the system to a healthy running state.

You will see log messages indicating system events, fault activations, recoveries, and warnings/errors. The system also maintains a persistent log file `system_debug.log` for review.

This setup provides a realistic embedded system fault simulation environment with precise control over fault injection and recovery, useful for testing robustness and debugging strategies.

## Features

### Core Debugging Features
- **Multi-level Logging System**: Debug, Info, Warning, Error, and Critical log levels
- **File I/O Logging**: Persistent log storage with error handling
- **State Tracking**: Complete system state monitoring and validation
- **Assertion System**: Enhanced assertions with detailed logging

### Fault Simulation
- **Sensor Noise Injection**: Simulates ADC reading errors
- **Actuator Failure**: Demonstrates stuck actuator scenarios
- **Communication Breakdown**: Network/communication fault simulation
- **Power Fluctuations**: Voltage instability simulation
- **Memory Corruption**: Heap/stack corruption scenarios

### Error Handling & Recovery
- **Comprehensive Error Codes**: 10 different error types
- **Fault History Tracking**: Records and analyzes fault patterns
- **Automatic Recovery**: Attempts system recovery from faults
- **Health Monitoring**: CPU, memory, and system health tracking

### Diagnostic Tools
- **Real-time Debug Display**: Live system status monitoring
- **Performance Metrics**: CPU and memory usage tracking
- **Fault Statistics**: Recovery success rates and patterns
- **Watchdog Simulation**: Embedded system watchdog timer

## Usage

### Compilation
```bash
# On Windows with MinGW
gcc debug_fault_sim.c -o debug_fault_sim.exe -std=c99 -Wall

# On Linux/Mac
gcc debug_fault_sim.c -o debug_fault_sim -std=c99
```

### Running the Simulation
```bash
./debug_fault_sim
```

### Commands
- `f` - Inject random fault for testing
- `r` - Attempt fault recovery
- `d` - Display debug information
- `q` - Quit simulation

## Architecture

### Core Components

1. **Debug Monitor**: Central logging and fault tracking system
2. **System Health**: Performance and state monitoring
3. **Fault Injector**: Controlled fault simulation
4. **Recovery System**: Automatic and manual recovery mechanisms
5. **Log Persistence**: File-based log storage

### Data Structures

- `log_entry_t`: Individual log entries with timestamps and context
- `fault_record_t`: Fault history with resolution tracking
- `system_health_t`: System performance and state metrics
- `debug_monitor_t`: Main monitoring system structure

## Skills Demonstrated

### Error Handling
- Comprehensive error code system
- Graceful degradation under fault conditions
- Recovery strategy implementation

### Logging & Debugging
- Multi-level logging hierarchy
- File I/O with error handling
- Debug information formatting
- Performance impact minimization

### State Management
- Finite state machine implementation
- State validation and assertions
- Transition logging and tracking

### Testing & Simulation
- Fault injection techniques
- System robustness testing
- Recovery mechanism validation

## Example Output

```
Debugging & Fault Simulation System
===================================

System initialized. Starting fault simulation...

Commands: f (inject fault), r (attempt recovery), d (debug info), q (quit)

[ERROR] simulate_sensor_reading:45 - Sensor failure detected
[WARN] inject_fault:120 - Fault injection activated
[INFO] attempt_fault_recovery:150 - Attempting fault recovery
[INFO] attempt_fault_recovery:165 - Fault recovery successful
```

## Log File

The system creates `system_debug.log` for persistent logging:

```
=== Log Session Start ===
[2024-01-15 10:30:15] INFO: System initialization started
[2024-01-15 10:30:16] WARN: Fault injection activated
[2024-01-15 10:30:18] INFO: Fault recovery successful
=== Log Session End ===
```

## Educational Value

This project serves as a comprehensive example of:

- **Embedded Programming Best Practices**
- **Robust Error Handling Strategies**
- **Real-time System Design**
- **Debugging Methodology**
- **Fault Tolerance Implementation**

## Future Enhancements

- Network communication fault simulation
- Hardware interrupt simulation
- Multi-threaded fault scenarios
- Performance profiling integration
- Configuration file support

## Requirements

- C99 compatible compiler (GCC, Clang, MSVC)
- Standard C libraries (stdio, stdlib, string, time, assert)
- Windows: MinGW for _kbhit() and Sleep() functions
- Linux/Mac: Standard Unix libraries

