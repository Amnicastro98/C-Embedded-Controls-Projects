/*
 * Sensor & Actuator Integration Simulation
 * ========================================
 *
 * This program simulates an embedded control system that demonstrates:
 * - Sensor data acquisition (ADC simulation)
 * - Actuator control (DAC simulation)
 * - Digital I/O operations (bitwise manipulation)
 * - Real-time control logic
 * - Hardware abstraction layers
 *
 * Skills demonstrated: structs, arrays, bitwise operations, functions, embedded programming
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
#include <string.h>

// Cross-platform compatibility for Windows and Unix-like systems
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
// Define usleep for Windows (Sleep takes milliseconds)
#define usleep(x) Sleep((x) / 1000)
#else
#include <unistd.h>
#endif

// Simulated ADC/DAC Constants
// ADC: Analog-to-Digital Converter simulation
#define ADC_RESOLUTION 12        // 12-bit ADC (0-4095 range)
#define ADC_VREF 3.3f           // 3.3V reference voltage for ADC

// DAC: Digital-to-Analog Converter simulation
#define DAC_RESOLUTION 8        // 8-bit DAC (0-255 range)
#define DAC_VREF 5.0f           // 5.0V reference voltage for DAC

// Digital I/O Pin Definitions (simulated hardware pins)
// These represent physical pins on a microcontroller
#define PIN_TEMP_SENSOR 0       // Pin for temperature sensor
#define PIN_PRESSURE_SENSOR 1   // Pin for pressure sensor
#define PIN_LEVEL_SENSOR 2      // Pin for level sensor
#define PIN_MOTOR_RELAY 3       // Pin for motor relay control
#define PIN_VALVE_SOLENOID 4    // Pin for valve solenoid control
#define PIN_LED_INDICATOR 5     // Pin for LED indicator

// Sensor Types
typedef enum {
    SENSOR_TEMPERATURE = 0,
    SENSOR_PRESSURE = 1,
    SENSOR_LEVEL = 2
} sensor_type_t;

// Actuator Types
typedef enum {
    ACTUATOR_MOTOR = 0,
    ACTUATOR_VALVE = 1,
    ACTUATOR_LED = 2
} actuator_type_t;

// Sensor Structure
typedef struct {
    sensor_type_t type;
    char name[20];
    float value;              // Current reading
    float min_range;          // Minimum range
    float max_range;          // Maximum range
    uint8_t pin;              // Digital pin
    uint8_t adc_channel;      // ADC channel
} sensor_t;

// Actuator Structure
typedef struct {
    actuator_type_t type;
    char name[20];
    float setpoint;           // Desired value
    float current_value;      // Current output
    uint8_t pin;              // Digital pin
    uint8_t dac_channel;      // DAC channel
    uint8_t state;            // On/Off state
} actuator_t;

// System Structure
typedef struct {
    sensor_t sensors[3];
    actuator_t actuators[3];
    uint16_t digital_inputs;  // 16-bit digital input register
    uint16_t digital_outputs; // 16-bit digital output register
    float system_voltage;
} system_t;

// Function Prototypes
void system_init(system_t* sys);
uint16_t adc_read(uint8_t channel);
void dac_write(uint8_t channel, uint16_t value);
void digital_write(system_t* sys, uint8_t pin, uint8_t state);
uint8_t digital_read(system_t* sys, uint8_t pin);
float simulate_sensor_reading(sensor_type_t type);
void update_sensors(system_t* sys);
void update_actuators(system_t* sys);
void control_logic(system_t* sys);
void display_status(system_t* sys);

/*
 * Main function - Program entry point
 * ===================================
 * This function initializes the system and runs the main simulation loop.
 * It handles both automatic operation and manual user commands.
 */
int main() {
    system_t sys;        // Main system structure containing all sensors and actuators
    char command;        // Variable to store user keyboard input

    // Display program header
    printf("Sensor & Actuator Integration Simulation\n");
    printf("========================================\n\n");

    // Initialize random number generator with current time
    // This ensures different sensor readings each time the program runs
    srand(time(NULL));

    // Initialize all sensors and actuators with default values
    system_init(&sys);

    // Display initialization complete message and command instructions
    printf("System initialized. Starting simulation...\n\n");
    printf("Commands: r (read sensors), c (run control), q (quit)\n\n");

    // Main program loop - runs indefinitely until user quits
    while (1) {
        // Check for keyboard input (non-blocking)
        if (_kbhit()) {
            command = _getch();  // Get the pressed key

            if (command == 'q') {
                // User wants to quit
                printf("Exiting simulation...\n");
                return 0;
            } else if (command == 'r') {
                // Manual sensor reading command
                update_sensors(&sys);
                display_status(&sys);
            } else if (command == 'c') {
                // Manual control logic execution
                control_logic(&sys);
                display_status(&sys);
            }
        }

        // Continuous automatic simulation loop
        // This runs every 500ms regardless of user input
        update_sensors(&sys);     // Read all sensor values
        control_logic(&sys);      // Execute control algorithms
        display_status(&sys);     // Show current system state
        usleep(500000);           // Wait 500 milliseconds (0.5 seconds)
    }

    return 0;
}

/*
 * Initialize the system with default sensor and actuator configurations.
 * This function sets up sensor types, names, ranges, pins, and ADC channels.
 * It also initializes actuators with their types, names, pins, DAC channels, and default setpoints.
 * Digital input/output registers and system voltage are initialized to default values.
 */
void system_init(system_t* sys) {
    // Initialize sensors
    strcpy(sys->sensors[0].name, "Temperature");
    sys->sensors[0].type = SENSOR_TEMPERATURE;
    sys->sensors[0].min_range = 0.0f;
    sys->sensors[0].max_range = 100.0f;
    sys->sensors[0].pin = PIN_TEMP_SENSOR;
    sys->sensors[0].adc_channel = 0;

    strcpy(sys->sensors[1].name, "Pressure");
    sys->sensors[1].type = SENSOR_PRESSURE;
    sys->sensors[1].min_range = 0.0f;
    sys->sensors[1].max_range = 10.0f;
    sys->sensors[1].pin = PIN_PRESSURE_SENSOR;
    sys->sensors[1].adc_channel = 1;

    strcpy(sys->sensors[2].name, "Level");
    sys->sensors[2].type = SENSOR_LEVEL;
    sys->sensors[2].min_range = 0.0f;
    sys->sensors[2].max_range = 100.0f;
    sys->sensors[2].pin = PIN_LEVEL_SENSOR;
    sys->sensors[2].adc_channel = 2;

    // Initialize actuators
    strcpy(sys->actuators[0].name, "Motor");
    sys->actuators[0].type = ACTUATOR_MOTOR;
    sys->actuators[0].pin = PIN_MOTOR_RELAY;
    sys->actuators[0].dac_channel = 0;
    sys->actuators[0].setpoint = 50.0f;

    strcpy(sys->actuators[1].name, "Valve");
    sys->actuators[1].type = ACTUATOR_VALVE;
    sys->actuators[1].pin = PIN_VALVE_SOLENOID;
    sys->actuators[1].dac_channel = 1;
    sys->actuators[1].setpoint = 25.0f;

    strcpy(sys->actuators[2].name, "LED");
    sys->actuators[2].type = ACTUATOR_LED;
    sys->actuators[2].pin = PIN_LED_INDICATOR;
    sys->actuators[2].dac_channel = 2;
    sys->actuators[2].setpoint = 100.0f;

    // Initialize digital I/O
    sys->digital_inputs = 0;
    sys->digital_outputs = 0;
    sys->system_voltage = 24.0f;
}

/*
 * Simulate ADC reading from a specified channel.
 * In real hardware, this would read from an analog-to-digital converter.
 * Here we simulate realistic ADC behavior with noise and random variation.
 *
 * @param channel: ADC channel number (0-2 for our sensors)
 * @return: 12-bit ADC value (0-4095)
 */
uint16_t adc_read(uint8_t channel) {
    // Generate random base value between 0 and 1
    float base_value = (float)rand() / RAND_MAX;

    // Add realistic noise (±5%) to simulate real-world ADC imperfections
    float noise = ((float)rand() / RAND_MAX - 0.5f) * 0.1f;

    // Calculate final ADC value with 12-bit resolution (0-4095)
    uint16_t adc_value = (uint16_t)(base_value * 4095.0f * (1.0f + noise));

    return adc_value;
}

/*
 * Simulate DAC writing to a specified channel.
 * In real hardware, this would set the output voltage of a digital-to-analog converter.
 * Here we calculate and display the resulting voltage.
 *
 * @param channel: DAC channel number (0-2 for our actuators)
 * @param value: 8-bit DAC value (0-255)
 */
void dac_write(uint8_t channel, uint16_t value) {
    // Calculate output voltage: value/255 * 5.0V reference
    float voltage = (float)value / 255.0f * DAC_VREF;

    // Display the DAC output voltage (simulating hardware behavior)
    printf("DAC Channel %d: Set to %.2fV\n", channel, voltage);
}

/*
 * Digital write using bitwise operations.
 * Sets or clears a specific bit in the digital output register.
 * This simulates controlling digital output pins on a microcontroller.
 *
 * @param sys: Pointer to system structure
 * @param pin: Pin number to control (0-15)
 * @param state: Desired state (0 = LOW, 1 = HIGH)
 */
void digital_write(system_t* sys, uint8_t pin, uint8_t state) {
    if (state) {
        // Set the bit: OR with (1 << pin) to turn pin ON
        sys->digital_outputs |= (1 << pin);
    } else {
        // Clear the bit: AND with ~(1 << pin) to turn pin OFF
        sys->digital_outputs &= ~(1 << pin);
    }
}

/*
 * Digital read using bitwise operations.
 * Reads the state of a specific bit in the digital input register.
 * This simulates reading digital input pins on a microcontroller.
 *
 * @param sys: Pointer to system structure
 * @param pin: Pin number to read (0-15)
 * @return: Pin state (0 = LOW, 1 = HIGH)
 */
uint8_t digital_read(system_t* sys, uint8_t pin) {
    // Check if bit is set: AND with (1 << pin), return 1 if set, 0 if clear
    return (sys->digital_inputs & (1 << pin)) ? 1 : 0;
}

/*
 * Simulate realistic sensor readings based on sensor type.
 * Generates random values within typical operating ranges for each sensor type.
 * This simulates real-world sensor behavior with natural variation.
 *
 * @param type: The type of sensor (temperature, pressure, or level)
 * @return: Simulated sensor reading value
 */
float simulate_sensor_reading(sensor_type_t type) {
    float base_value;

    switch (type) {
        case SENSOR_TEMPERATURE:
            // Temperature range: 20-80°C (typical industrial range)
            base_value = 20.0f + (float)rand() / RAND_MAX * 60.0f;
            break;
        case SENSOR_PRESSURE:
            // Pressure range: 0-8 bar (typical system pressure)
            base_value = (float)rand() / RAND_MAX * 8.0f;
            break;
        case SENSOR_LEVEL:
            // Level range: 0-100% (tank level percentage)
            base_value = (float)rand() / RAND_MAX * 100.0f;
            break;
        default:
            base_value = 0.0f;
    }

    return base_value;
}

/*
 * Update all sensor readings in the system.
 * This function simulates the complete sensor data acquisition process:
 * 1. Read ADC values from each sensor channel
 * 2. Convert ADC values to voltages
 * 3. Generate realistic sensor readings based on sensor type
 *
 * @param sys: Pointer to system structure
 */
void update_sensors(system_t* sys) {
    for (int i = 0; i < 3; i++) {
        // Step 1: Read raw ADC value from sensor's ADC channel
        uint16_t adc_value = adc_read(sys->sensors[i].adc_channel);

        // Step 2: Convert ADC reading to voltage (though not used in final calculation)
        float voltage = (float)adc_value / 4095.0f * ADC_VREF;

        // Step 3: Generate realistic sensor reading based on sensor type
        sys->sensors[i].value = simulate_sensor_reading(sys->sensors[i].type);
    }
}

/*
 * Update all actuator outputs in the system.
 * This function handles the complete actuator control process:
 * 1. Convert setpoint values to DAC values
 * 2. Write DAC values to control analog outputs
 * 3. Update digital outputs for on/off control
 * 4. Update current values to match setpoints
 *
 * @param sys: Pointer to system structure
 */
void update_actuators(system_t* sys) {
    for (int i = 0; i < 3; i++) {
        // Convert setpoint percentage (0-100%) to DAC value (0-255)
        uint16_t dac_value = (uint16_t)(sys->actuators[i].setpoint / 100.0f * 255.0f);

        // Write the DAC value to control analog output
        dac_write(sys->actuators[i].dac_channel, dac_value);

        // Update digital output pin state (on/off control)
        digital_write(sys, sys->actuators[i].pin, sys->actuators[i].state);

        // Update current value to reflect the setpoint
        sys->actuators[i].current_value = sys->actuators[i].setpoint;
    }
}

/*
 * Execute control logic based on current sensor readings.
 * This implements a simple PID-like control system:
 * - Temperature > 50°C: Turn on motor at 75% speed
 * - Pressure > 6 bar: Open valve at 80% position
 * - Level < 20%: Turn on LED indicator at 100% brightness
 *
 * @param sys: Pointer to system structure
 */
void control_logic(system_t* sys) {
    // Temperature control logic
    if (sys->sensors[0].value > 50.0f) {
        sys->actuators[0].state = 1;        // Turn motor ON
        sys->actuators[0].setpoint = 75.0f; // Set to 75% speed
    } else {
        sys->actuators[0].state = 0;        // Turn motor OFF
        sys->actuators[0].setpoint = 25.0f; // Set to 25% speed when off
    }

    // Pressure control logic
    if (sys->sensors[1].value > 6.0f) {
        sys->actuators[1].state = 1;        // Open valve
        sys->actuators[1].setpoint = 80.0f; // Set to 80% open
    } else {
        sys->actuators[1].state = 0;        // Close valve
        sys->actuators[1].setpoint = 20.0f; // Set to 20% open when closed
    }

    // Level control logic
    if (sys->sensors[2].value < 20.0f) {
        sys->actuators[2].state = 1;         // Turn LED ON
        sys->actuators[2].setpoint = 100.0f; // Set to 100% brightness
    } else {
        sys->actuators[2].state = 0;         // Turn LED OFF
        sys->actuators[2].setpoint = 0.0f;   // Set to 0% brightness
    }

    // Apply the control decisions to actuators
    update_actuators(sys);
}

/*
 * Display comprehensive system status information.
 * Shows current readings for all sensors and actuators,
 * plus digital I/O register states and system voltage.
 *
 * @param sys: Pointer to system structure
 */
void display_status(system_t* sys) {
    printf("\n=== System Status ===\n");

    // Display sensor readings
    printf("Sensors:\n");
    for (int i = 0; i < 3; i++) {
        printf("  %s: %.2f %s\n",
               sys->sensors[i].name,
               sys->sensors[i].value,
               (sys->sensors[i].type == SENSOR_TEMPERATURE) ? "°C" :
               (sys->sensors[i].type == SENSOR_PRESSURE) ? "bar" : "%");
    }

    // Display actuator states
    printf("Actuators:\n");
    for (int i = 0; i < 3; i++) {
        printf("  %s: %s (%.1f%%)\n",
               sys->actuators[i].name,
               sys->actuators[i].state ? "ON" : "OFF",
               sys->actuators[i].current_value);
    }

    // Display digital I/O register values in hexadecimal
    printf("Digital I/O: Inputs=0x%04X, Outputs=0x%04X\n",
           sys->digital_inputs, sys->digital_outputs);
    printf("System Voltage: %.1fV\n", sys->system_voltage);
}
