# Excel Commissioning File Simulation System

## Overview

This project simulates a commissioning file system commonly used in embedded control systems for industrial automation, robotics, and process control applications. It demonstrates the ability to create, read, write, and validate configuration files (CSV format) that contain system parameters, calibration data, and operational settings.

## What to Expect

When you run the commissioning system, you'll see an interactive menu that allows you to:

- **Display Parameters**: View all current system parameters with their values, units, and validation status
- **Update Values**: Modify parameter values with automatic validation
- **Add Parameters**: Create new system parameters
- **Save/Load Files**: Persist configuration data to/from CSV files
- **Validate Data**: Check parameter values against acceptable ranges

The system simulates real-world commissioning scenarios where engineers need to configure control systems, set operational limits, and validate parameter settings before deployment.

## Features

### Core Functionality
- **CSV File I/O**: Read and write commissioning data in standard CSV format
- **Parameter Management**: Add, update, and validate system parameters
- **Data Validation**: Range checking and type validation for parameter values
- **Persistent Storage**: Save and load configuration files
- **Interactive Menu**: User-friendly command-line interface

### Parameter Types
- **Motor Control**: Speed settings, current limits, PID gains
- **Sensor Configuration**: Calibration offsets, measurement ranges
- **System Limits**: Temperature limits, pressure setpoints, voltage constraints
- **Process Control**: Flow rates, control setpoints, operational parameters

## Usage

### Compilation
```bash
# On Windows with MinGW
make
or
gcc commissioning_system.c -o commissioning_system.exe -std=c99 -Wall

# On Linux/Mac
gcc commissioning_system.c -o commissioning_system -std=c99 -Wall
```

### Running the System
```bash
./commissioning_system
```

### Menu Options
1. **Display all parameters** - Shows current configuration
2. **Update parameter value** - Modify existing parameter
3. **Add new parameter** - Create new configuration item
4. **Save to file** - Export configuration to CSV
5. **Load from file** - Import configuration from CSV
6. **Validate all parameters** - Check all values against limits
0. **Exit** - Close the system

## Skills Demonstrated

### File I/O Operations
- Reading and writing CSV files
- File error handling
- Data persistence and recovery

### Data Processing
- CSV parsing and formatting
- String manipulation
- Data validation and error checking

### System Design
- Structured data management
- Modular function design
- Memory management

### Embedded Systems Concepts
- Parameter configuration
- System commissioning workflows
- Configuration file management

## Example Usage

```
=== Commissioning File System Menu ===
1. Display all parameters
2. Update parameter value
3. Add new parameter
4. Save to file
5. Load from file
6. Validate all parameters
0. Exit
Choice: 1

=== Industrial Control System Commissioning Parameters ===
Parameter            Value           Unit       Description               Status
--------------------------------------------------------------------------------
motor_speed_rpm       1800            RPM        Motor operating speed     VALID
temperature_limit     75              Celsius    Maximum temperature limit VALID
pressure_setpoint     3.2             bar        Pressure control setpoint VALID
================================================================================
```

## CSV File Format

The system uses a standard CSV format for configuration files:

```csv
Parameter,Value,Unit,Description,Valid
motor_speed_rpm,1800,RPM,Motor operating speed,true
temperature_limit,75,Celsius,Maximum temperature limit,true
pressure_setpoint,3.2,bar,Pressure control setpoint,true
```

## Parameter Validation

The system includes built-in validation for common parameter types:

- **Motor Speed**: 0-3000 RPM
- **Temperature**: 0-100°C
- **Pressure**: 0-10 bar
- **Voltage**: 0-50V
- **Current**: 0-20A

## Educational Value

This project demonstrates:

- **Industrial Control Systems**: Parameter configuration and validation
- **Data Persistence**: File-based configuration management
- **User Interface Design**: Command-line menu systems
- **Error Handling**: Robust input validation and error recovery
- **Modular Programming**: Clean separation of concerns

## Requirements

- C99 compatible compiler (GCC, Clang, MSVC)
- Standard C libraries (stdio, stdlib, string)
- Windows: MinGW for full functionality
- Linux/Mac: Standard Unix libraries

## Files Included

- `commissioning_system.c` - Main program source code
- `sample_config.csv` - Example configuration file
- `Makefile` - Build automation
- `README.md` - This documentation
