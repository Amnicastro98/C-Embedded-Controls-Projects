/*
 * Excel Commissioning File Simulation System
 *
 * This program simulates working with commissioning files (CSV format) commonly used
 * in embedded control systems for parameter configuration, calibration data, and
 * system setup. It demonstrates file I/O, CSV parsing, parameter validation, and
 * data persistence - essential skills for embedded software engineers.
 *
 * Key Features Demonstrated:
 * - File input/output operations (reading/writing CSV files)
 * - Data parsing and validation
 * - Memory management with structures
 * - User interface design
 * - Error handling and recovery
 * - Modular programming principles
 */

#include <stdio.h>      // Standard I/O functions (printf, scanf, fopen, etc.)
#include <stdlib.h>     // Memory allocation and utility functions
#include <string.h>     // String manipulation functions
#include <stdbool.h>    // Boolean data type support

// System configuration constants
#define MAX_LINE_LENGTH 256      // Maximum length of a CSV line
#define MAX_PARAMETERS 50        // Maximum number of parameters the system can handle
#define MAX_NAME_LENGTH 32       // Maximum length for parameter names and values
#define COMMISSIONING_FILE "system_config.csv"  // Default commissioning file name

/*
 * Structure representing a single system parameter
 * This is the core data structure for storing parameter information
 */
typedef struct {
    char name[MAX_NAME_LENGTH];         // Parameter identifier (e.g., "motor_speed_rpm")
    char value[MAX_NAME_LENGTH];        // Parameter value as string (e.g., "1500")
    char unit[MAX_NAME_LENGTH];         // Unit of measurement (e.g., "RPM", "Celsius")
    char description[MAX_NAME_LENGTH];  // Human-readable description
    bool is_valid;                      // Flag indicating if parameter value is valid
} system_parameter_t;

/*
 * Main structure representing the commissioning system
 * Contains all parameters and system state information
 */
typedef struct {
    system_parameter_t parameters[MAX_PARAMETERS];  // Array of system parameters
    int parameter_count;                           // Current number of parameters
    char system_name[MAX_NAME_LENGTH];             // Name of the control system
    bool is_loaded;                               // Flag indicating if config was loaded from file
} commissioning_system_t;

/*
 * Initialize the commissioning system with default values
 * This function sets up the system with some sample parameters for demonstration
 * In a real embedded system, these might be loaded from EEPROM or flash memory
 */
void init_commissioning_system(commissioning_system_t* system, const char* name) {
    // Reset system state
    system->parameter_count = 0;        // Start with no parameters
    system->is_loaded = false;          // Not loaded from file yet
    strcpy(system->system_name, name);  // Set the system name

    // Add some default parameters for demonstration
    // Parameter 1: Motor speed control
    strcpy(system->parameters[0].name, "motor_speed_rpm");
    strcpy(system->parameters[0].value, "1500");
    strcpy(system->parameters[0].unit, "RPM");
    strcpy(system->parameters[0].description, "Motor operating speed");
    system->parameters[0].is_valid = true;  // Mark as valid
    system->parameter_count++;               // Increment parameter count

    // Parameter 2: Temperature safety limit
    strcpy(system->parameters[1].name, "temperature_limit");
    strcpy(system->parameters[1].value, "85");
    strcpy(system->parameters[1].unit, "Celsius");
    strcpy(system->parameters[1].description, "Maximum temperature limit");
    system->parameters[1].is_valid = true;
    system->parameter_count++;

    // Parameter 3: Pressure control setpoint
    strcpy(system->parameters[2].name, "pressure_setpoint");
    strcpy(system->parameters[2].value, "2.5");
    strcpy(system->parameters[2].unit, "bar");
    strcpy(system->parameters[2].description, "Pressure control setpoint");
    system->parameters[2].is_valid = true;
    system->parameter_count++;
}

/*
 * Validate a parameter value based on its type and constraints
 * This function ensures parameter values are within safe operating ranges
 * Critical for embedded systems to prevent hardware damage or unsafe operation
 */
bool validate_parameter(const char* name, const char* value) {
    // Motor speed validation - prevent overspeed conditions
    if (strcmp(name, "motor_speed_rpm") == 0) {
        int speed = atoi(value);  // Convert string to integer
        return (speed >= 0 && speed <= 3000); // 0-3000 RPM range (realistic motor limits)
    }
    // Temperature safety validation - prevent overheating
    else if (strcmp(name, "temperature_limit") == 0) {
        int temp = atoi(value);   // Convert string to integer
        return (temp >= 0 && temp <= 100); // 0-100°C range (safe operating temperatures)
    }
    // Pressure control validation - prevent overpressure
    else if (strcmp(name, "pressure_setpoint") == 0) {
        float pressure = atof(value);  // Convert string to float for decimal precision
        return (pressure >= 0.0f && pressure <= 10.0f); // 0-10 bar range (typical system limits)
    }

    // For unknown parameters, assume they are valid (extensible design)
    return true; // Default validation passes - allows for custom parameters
}

/*
 * Save the commissioning parameters to a CSV file
 */
bool save_commissioning_file(commissioning_system_t* system) {
    FILE* file = fopen(COMMISSIONING_FILE, "w");
    if (file == NULL) {
        printf("Error: Cannot create commissioning file\n");
        return false;
    }

    // Write CSV header
    fprintf(file, "Parameter,Value,Unit,Description,Valid\n");

    // Write each parameter
    for (int i = 0; i < system->parameter_count; i++) {
        fprintf(file, "%s,%s,%s,%s,%s\n",
                system->parameters[i].name,
                system->parameters[i].value,
                system->parameters[i].unit,
                system->parameters[i].description,
                system->parameters[i].is_valid ? "true" : "false");
    }

    fclose(file);
    printf("Commissioning file saved successfully: %s\n", COMMISSIONING_FILE);
    return true;
}

/*
 * Load commissioning parameters from a CSV file
 */
bool load_commissioning_file(commissioning_system_t* system) {
    FILE* file = fopen(COMMISSIONING_FILE, "r");
    if (file == NULL) {
        printf("Commissioning file not found. Using default parameters.\n");
        return false;
    }

    char line[MAX_LINE_LENGTH];
    int line_count = 0;
    system->parameter_count = 0;

    // Skip header line
    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return false;
    }

    // Read parameter lines
    while (fgets(line, sizeof(line), file) && system->parameter_count < MAX_PARAMETERS) {
        line_count++;

        // Parse CSV line (simple parsing - assumes no commas in values)
        char* token = strtok(line, ",");
        if (token == NULL) continue;

        // Remove newline character
        token[strcspn(token, "\n")] = 0;

        strcpy(system->parameters[system->parameter_count].name, token);

        token = strtok(NULL, ",");
        if (token) strcpy(system->parameters[system->parameter_count].value, token);

        token = strtok(NULL, ",");
        if (token) strcpy(system->parameters[system->parameter_count].unit, token);

        token = strtok(NULL, ",");
        if (token) strcpy(system->parameters[system->parameter_count].description, token);

        token = strtok(NULL, ",");
        if (token) {
            system->parameters[system->parameter_count].is_valid = (strcmp(token, "true") == 0);
        }

        // Validate the loaded parameter
        system->parameters[system->parameter_count].is_valid =
            validate_parameter(system->parameters[system->parameter_count].name,
                             system->parameters[system->parameter_count].value);

        system->parameter_count++;
    }

    fclose(file);
    system->is_loaded = true;
    printf("Loaded %d parameters from commissioning file\n", system->parameter_count);
    return true;
}

/*
 * Display all commissioning parameters
 */
void display_parameters(commissioning_system_t* system) {
    printf("\n=== %s Commissioning Parameters ===\n", system->system_name);
    printf("%-20s %-15s %-10s %-25s %s\n", "Parameter", "Value", "Unit", "Description", "Status");
    printf("--------------------------------------------------------------------------------\n");

    for (int i = 0; i < system->parameter_count; i++) {
        printf("%-20s %-15s %-10s %-25s %s\n",
               system->parameters[i].name,
               system->parameters[i].value,
               system->parameters[i].unit,
               system->parameters[i].description,
               system->parameters[i].is_valid ? "VALID" : "INVALID");
    }
    printf("================================================================================\n");
}

/*
 * Update a parameter value with validation
 */
bool update_parameter(commissioning_system_t* system, const char* name, const char* new_value) {
    for (int i = 0; i < system->parameter_count; i++) {
        if (strcmp(system->parameters[i].name, name) == 0) {
            // Validate the new value
            if (!validate_parameter(name, new_value)) {
                printf("Error: Invalid value '%s' for parameter '%s'\n", new_value, name);
                return false;
            }

            strcpy(system->parameters[i].value, new_value);
            system->parameters[i].is_valid = true;
            printf("Parameter '%s' updated to '%s'\n", name, new_value);
            return true;
        }
    }

    printf("Error: Parameter '%s' not found\n", name);
    return false;
}

/*
 * Add a new parameter to the system
 */
bool add_parameter(commissioning_system_t* system, const char* name, const char* value,
                  const char* unit, const char* description) {
    if (system->parameter_count >= MAX_PARAMETERS) {
        printf("Error: Maximum number of parameters reached\n");
        return false;
    }

    // Check if parameter already exists
    for (int i = 0; i < system->parameter_count; i++) {
        if (strcmp(system->parameters[i].name, name) == 0) {
            printf("Error: Parameter '%s' already exists\n", name);
            return false;
        }
    }

    // Validate the value
    if (!validate_parameter(name, value)) {
        printf("Error: Invalid value '%s' for parameter '%s'\n", value, name);
        return false;
    }

    // Add the new parameter
    strcpy(system->parameters[system->parameter_count].name, name);
    strcpy(system->parameters[system->parameter_count].value, value);
    strcpy(system->parameters[system->parameter_count].unit, unit);
    strcpy(system->parameters[system->parameter_count].description, description);
    system->parameters[system->parameter_count].is_valid = true;
    system->parameter_count++;

    printf("Parameter '%s' added successfully\n", name);
    return true;
}

/*
 * Main menu system for user interaction
 */
void show_menu() {
    printf("\n=== Commissioning File System Menu ===\n");
    printf("1. Display all parameters\n");
    printf("2. Update parameter value\n");
    printf("3. Add new parameter\n");
    printf("4. Save to file\n");
    printf("5. Load from file\n");
    printf("6. Validate all parameters\n");
    printf("0. Exit\n");
    printf("Choice: ");
}

/*
 * Main program entry point
 * This function implements the main program loop and user interface
 * Demonstrates typical embedded system startup sequence and menu-driven interface
 */
int main() {
    // Declare system structure and user input variables
    commissioning_system_t system;                    // Main system structure
    char choice;                                      // User menu choice
    char param_name[MAX_NAME_LENGTH];                 // Parameter name input buffer
    char param_value[MAX_NAME_LENGTH];                // Parameter value input buffer
    char param_unit[MAX_NAME_LENGTH];                 // Parameter unit input buffer
    char param_desc[MAX_NAME_LENGTH];                 // Parameter description input buffer

    // System initialization - first step in embedded system startup
    init_commissioning_system(&system, "Industrial Control System");
    printf("Commissioning File Simulation System Started\n");
    printf("System: %s\n", system.system_name);

    // Attempt to load existing configuration - demonstrates persistence
    load_commissioning_file(&system);

    // Main program loop - typical embedded system infinite loop
    while (1) {
        // Display menu and get user choice
        show_menu();
        scanf(" %c", &choice);  // Note: space before %c to consume whitespace

        // Process user choice using switch statement - common in embedded systems
        switch (choice) {
            case '1':  // Display current parameters
                display_parameters(&system);
                break;

            case '2':  // Update existing parameter
                printf("Enter parameter name: ");
                scanf("%s", param_name);
                printf("Enter new value: ");
                scanf("%s", param_value);
                update_parameter(&system, param_name, param_value);
                break;

            case '3':  // Add new parameter
                printf("Enter parameter name: ");
                scanf("%s", param_name);
                printf("Enter value: ");
                scanf("%s", param_value);
                printf("Enter unit: ");
                scanf("%s", param_unit);
                printf("Enter description: ");
                scanf("%s", param_desc);
                add_parameter(&system, param_name, param_value, param_unit, param_desc);
                break;

            case '4':  // Save configuration to file
                save_commissioning_file(&system);
                break;

            case '5':  // Load configuration from file
                load_commissioning_file(&system);
                break;

            case '6':  // Validate all parameters
                printf("Validating all parameters...\n");
                // Re-validate all parameters - demonstrates safety checking
                for (int i = 0; i < system.parameter_count; i++) {
                    system.parameters[i].is_valid =
                        validate_parameter(system.parameters[i].name, system.parameters[i].value);
                }
                printf("Validation complete\n");
                break;

            case '0':  // Exit program
                printf("Exiting Commissioning System\n");
                return 0;  // Clean exit with success code

            default:  // Handle invalid input
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    // This line is never reached due to infinite loop, but good practice to include
    return 0;
}
