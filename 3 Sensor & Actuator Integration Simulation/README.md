# Sensor & Actuator Integration Simulation

This project simulates an embedded control system that reads sensor inputs (temperature, pressure, level) and controls actuators (motor, valve, LED) accordingly. The output shows real-time sensor readings, actuator states, DAC voltages, and digital I/O status. The simulation runs continuously, automatically updating sensor values and control logic every 500ms. You can also manually trigger sensor reads (`r` key) and control cycles (`c` key). Press `q` to quit.

A C program that simulates the integration of sensors and actuators in an embedded control system. This project demonstrates hardware signal processing, ADC/DAC simulation, and real-time control logic.


## Features

- **Sensor Simulation**: Temperature, pressure, and level sensors with realistic readings
- **Actuator Control**: Motor, valve, and LED actuators with setpoint control
- **ADC/DAC Simulation**: 12-bit ADC and 8-bit DAC with noise simulation
- **Digital I/O**: Bitwise operations for digital input/output control
- **Control Logic**: Automated responses based on sensor readings
- **Real-time Display**: Continuous system status monitoring

## Skills Demonstrated

- **Structs**: Complex data structures for sensors and actuators
- **Arrays**: Managing multiple devices in arrays
- **Bitwise Operations**: Digital I/O manipulation using bit masks
- **Functions**: Modular code organization
- **ADC/DAC Simulation**: Analog-to-digital and digital-to-analog conversion
- **Embedded Programming**: Hardware abstraction and control

## System Architecture

### Sensors
- **Temperature Sensor**: 0-100°C range, ADC channel 0
- **Pressure Sensor**: 0-10 bar range, ADC channel 1
- **Level Sensor**: 0-100% range, ADC channel 2

### Actuators
- **Motor**: Digital control via relay, DAC channel 0
- **Valve**: Digital control via solenoid, DAC channel 1
- **LED**: Digital control for indication, DAC channel 2

### Control Logic
- Motor activates when temperature > 50°C
- Valve opens when pressure > 6 bar
- LED illuminates when level < 20%

## How to Compile and Run

### Windows (MSYS2)
1. Open MSYS2 MinGW x64 terminal
2. Navigate to the project directory
3. Compile: `gcc sensor_actuator_sim.c -o sensor_actuator_sim.exe -lm`
4. Run: `./sensor_actuator_sim.exe`

### Linux/Mac
1. Navigate to the project directory
2. Compile: `gcc sensor_actuator_sim.c -o sensor_actuator_sim -lm`
3. Run: `./sensor_actuator_sim`

## Usage

The program provides an interactive simulation:

- `r` (Read sensors): Manually triggers a sensor reading cycle, updating all three sensors (temperature, pressure, level) with new random values and displays the current system status.
- `c` (Run control): Manually executes the control logic that checks sensor values and updates actuators accordingly:
  - Motor ON if temperature > 50°C
  - Valve ON if pressure > 6 bar
  - LED ON if level < 20%
- `q` - Quit the program

The simulation also runs continuously, updating sensors and control logic automatically every 500ms.

## Technical Details

### ADC Simulation
- 12-bit resolution (0-4095)
- 3.3V reference voltage
- ±5% noise simulation for realism

### DAC Simulation
- 8-bit resolution (0-255)
- 5.0V reference voltage
- Voltage output calculation: `voltage = (value / 255) * 5.0`

### Digital I/O
- 16-bit input/output registers
- Bitwise operations for pin control
- Pin mapping for different devices

## Example Output

```
Sensor & Actuator Integration Simulation
========================================

System initialized. Starting simulation...

Commands: r (read sensors), c (run control), q (quit)

=== System Status ===
Sensors:
  Temperature: 65.23 °C
  Pressure: 4.12 bar
  Level: 78.45 %

Actuators:
  Motor: ON (75.0%)
  Valve: OFF (20.0%)
  LED: OFF (0.0%)

Digital I/O: Inputs=0x0000, Outputs=0x0008
System Voltage: 24.0V
```

## Learning Outcomes

This project helps understand:
- Sensor data acquisition and processing
- Actuator control and feedback systems
- Analog-to-digital conversion principles
- Digital signal processing
- Real-time embedded system design
- Hardware abstraction layers

## Code Structure

- **sensor_actuator_sim.c**: Main simulation program
- **Structures**: sensor_t, actuator_t, system_t for data organization
- **Functions**: Modular functions for ADC, DAC, digital I/O, and control logic
- **Simulation**: Realistic sensor readings with noise and variation

This project demonstrates practical embedded programming skills that are essential for industrial control systems, IoT devices, and robotics applications.
