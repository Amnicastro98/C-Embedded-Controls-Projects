/*
 * Debugging & Fault Simulation System
 * ===================================
 *
 * This program demonstrates advanced debugging techniques and fault simulation
 * for embedded systems. It showcases:
 * - Comprehensive error handling and fault detection
 * - Multi-level logging system with file I/O
 * - State tracking and recovery mechanisms
 * - Fault injection for testing robustness
 * - Diagnostic tools and system monitoring
 * - Assertion-based debugging
 *
 * Skills demonstrated: error handling, logging, state machines, file I/O, debugging techniques
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <errno.h>

// Cross-platform compatibility
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#define usleep(x) Sleep((x) / 1000)
#define kbhit _kbhit
#define getch _getch
#else
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

// Unix-compatible kbhit and getch implementations
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int getch(void) {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

#define usleep(x) usleep(x)
#endif

// Configuration Constants
#define MAX_LOG_ENTRIES 1000
#define LOG_FILE_PATH "system_debug.log"
#define MAX_FAULT_HISTORY 50
#define WATCHDOG_TIMEOUT_MS 5000
#define SYSTEM_HEALTH_CHECK_INTERVAL_MS 1000

// Error Codes
typedef enum {
    ERR_NONE = 0,
    ERR_SENSOR_FAILURE = 1,
    ERR_ACTUATOR_STUCK = 2,
    ERR_COMMUNICATION_LOST = 3,
    ERR_POWER_FLUCTUATION = 4,
    ERR_MEMORY_CORRUPTION = 5,
    ERR_WATCHDOG_TIMEOUT = 6,
    ERR_INVALID_STATE = 7,
    ERR_FILE_IO_ERROR = 8,
    ERR_SYSTEM_OVERLOAD = 9
} error_code_t;

// Log Levels
typedef enum {
    LOG_DEBUG = 0,
    LOG_INFO = 1,
    LOG_WARNING = 2,
    LOG_ERROR = 3,
    LOG_CRITICAL = 4
} log_level_t;

// System States
typedef enum {
    STATE_INIT = 0,
    STATE_RUNNING = 1,
    STATE_FAULT = 2,
    STATE_RECOVERY = 3,
    STATE_SHUTDOWN = 4
} system_state_t;

// Fault Types for Simulation
typedef enum {
    FAULT_NONE = 0,
    FAULT_SENSOR_NOISE = 1,
    FAULT_ACTUATOR_FAIL = 2,
    FAULT_COMM_BREAK = 3,
    FAULT_POWER_SPIKE = 4,
    FAULT_MEMORY_LEAK = 5
} fault_type_t;

// Log Entry Structure
typedef struct {
    time_t timestamp;
    log_level_t level;
    error_code_t error_code;
    char message[256];
    char function[64];
    int line_number;
} log_entry_t;

// Fault History Structure
typedef struct {
    time_t timestamp;
    fault_type_t fault_type;
    error_code_t error_code;
    uint8_t resolved;
    char description[128];
} fault_record_t;

// System Health Structure
typedef struct {
    system_state_t current_state;
    uint32_t uptime_seconds;
    uint16_t fault_count;
    uint16_t recovery_count;
    float cpu_usage_percent;
    float memory_usage_percent;
    uint32_t last_health_check;
} system_health_t;

// Debug Monitor Structure
typedef struct {
    log_entry_t log_buffer[MAX_LOG_ENTRIES];
    int log_count;
    fault_record_t fault_history[MAX_FAULT_HISTORY];
    int fault_count;
    system_health_t health;
    FILE* log_file;
    uint8_t fault_injection_enabled;
    fault_type_t active_fault;
} debug_monitor_t;

// Function Prototypes
void debug_init(debug_monitor_t* monitor);
void debug_shutdown(debug_monitor_t* monitor);
void log_message(debug_monitor_t* monitor, log_level_t level, error_code_t error,
                const char* message, const char* function, int line);
void inject_fault(debug_monitor_t* monitor, fault_type_t fault);
void check_system_health(debug_monitor_t* monitor);
void attempt_fault_recovery(debug_monitor_t* monitor);
void save_log_to_file(debug_monitor_t* monitor);
void display_debug_info(debug_monitor_t* monitor);
void assert_system_state(debug_monitor_t* monitor, system_state_t expected_state);

// Macro for easy logging
#define LOG_DEBUG(monitor, msg) log_message(monitor, LOG_DEBUG, ERR_NONE, msg, __func__, __LINE__)
#define LOG_INFO(monitor, msg) log_message(monitor, LOG_INFO, ERR_NONE, msg, __func__, __LINE__)
#define LOG_WARNING(monitor, error, msg) log_message(monitor, LOG_WARNING, error, msg, __func__, __LINE__)
#define LOG_ERROR(monitor, error, msg) log_message(monitor, LOG_ERROR, error, msg, __func__, __LINE__)
#define LOG_CRITICAL(monitor, error, msg) log_message(monitor, LOG_CRITICAL, error, msg, __func__, __LINE__)

// Assertion macro with logging
#define ASSERT_STATE(monitor, condition, error, msg) \
    do { \
        if (!(condition)) { \
            LOG_CRITICAL(monitor, error, msg); \
            assert(condition); \
        } \
    } while(0)

// Simulated system components that can fail
int simulate_sensor_reading(debug_monitor_t* monitor);
int simulate_actuator_control(debug_monitor_t* monitor, int command);
int simulate_communication(debug_monitor_t* monitor);
float simulate_power_monitoring(debug_monitor_t* monitor);

// Fault simulation functions
void simulate_sensor_noise(debug_monitor_t* monitor);
void simulate_actuator_failure(debug_monitor_t* monitor);
void simulate_communication_break(debug_monitor_t* monitor);
void simulate_power_fluctuation(debug_monitor_t* monitor);
void simulate_memory_corruption(debug_monitor_t* monitor);

/*
 * Main function - Program entry point
 * ===================================
 * Demonstrates comprehensive debugging and fault simulation system
 */
int main() {
    debug_monitor_t monitor;
    char command;
    int simulation_running = 1;

    printf("Debugging & Fault Simulation System\n");
    printf("===================================\n\n");

    // Initialize debug monitoring system
    debug_init(&monitor);
    LOG_INFO(&monitor, "System initialization started");

    printf("System initialized. Starting fault simulation...\n\n");
    printf("Commands: f (inject fault), r (attempt recovery), d (debug info), q (quit)\n\n");

    // Main simulation loop
    while (simulation_running) {
        // Periodic health check
        check_system_health(&monitor);

        // Simulate system operations with potential faults (controlled frequency)
        if (monitor.fault_injection_enabled) {
            static int fault_call_count = 0;
            static int last_fault_trigger = 0;
            fault_call_count++;

            // Only trigger fault simulation every 4th call for faster response
            if (fault_call_count % 4 == 0 && fault_call_count != last_fault_trigger) {
                last_fault_trigger = fault_call_count;
                switch (monitor.active_fault) {
                    case FAULT_SENSOR_NOISE:
                        simulate_sensor_noise(&monitor);
                        break;
                    case FAULT_ACTUATOR_FAIL:
                        simulate_actuator_failure(&monitor);
                        break;
                    case FAULT_COMM_BREAK:
                        simulate_communication_break(&monitor);
                        break;
                    case FAULT_POWER_SPIKE:
                        simulate_power_fluctuation(&monitor);
                        break;
                    case FAULT_MEMORY_LEAK:
                        simulate_memory_corruption(&monitor);
                        break;
                    default:
                        break;
                }
            }
        }

        // Check for user input
        if (kbhit()) {
            command = getch();
            switch (command) {
                case 'q':
                    LOG_INFO(&monitor, "User requested system shutdown");
                    simulation_running = 0;
                    break;
                case 'f':
                    // Inject a random fault for testing
                    inject_fault(&monitor, rand() % 5 + 1);
                    break;
                case 'r':
                    // Attempt fault recovery
                    attempt_fault_recovery(&monitor);
                    break;
                case 'd':
                    // Display debug information
                    display_debug_info(&monitor);
                    break;
                default:
                    printf("Unknown command. Use: f, r, d, q\n");
            }
        }

        // Simulate normal system operations
        simulate_sensor_reading(&monitor);
        simulate_actuator_control(&monitor, rand() % 100);
        simulate_communication(&monitor);
        simulate_power_monitoring(&monitor);

        usleep(100000); // 0.1 second delay for better responsiveness
    }

    // Cleanup and shutdown
    debug_shutdown(&monitor);
    printf("System shutdown complete.\n");

    return 0;
}

/*
 * Initialize the debug monitoring system
 * Sets up logging, fault tracking, and system health monitoring
 */
void debug_init(debug_monitor_t* monitor) {
    // Initialize structure
    memset(monitor, 0, sizeof(debug_monitor_t));

    // Open log file
    monitor->log_file = fopen(LOG_FILE_PATH, "a");
    if (monitor->log_file == NULL) {
        printf("Warning: Could not open log file: %s\n", strerror(errno));
    }

    // Initialize system health
    monitor->health.current_state = STATE_INIT;
    monitor->health.uptime_seconds = 0;
    monitor->health.last_health_check = time(NULL);

    // Seed random number generator
    srand(time(NULL));

    LOG_INFO(monitor, "Debug monitoring system initialized");

    // Transition to running state after successful initialization
    monitor->health.current_state = STATE_RUNNING;
    LOG_INFO(monitor, "System transitioned to RUNNING state");
}

/*
 * Shutdown the debug monitoring system
 * Saves logs and cleans up resources
 */
void debug_shutdown(debug_monitor_t* monitor) {
    LOG_INFO(monitor, "Shutting down debug monitoring system");

    // Save final log entries
    save_log_to_file(monitor);

    // Close log file
    if (monitor->log_file != NULL) {
        fclose(monitor->log_file);
        monitor->log_file = NULL;
    }

    // Final system state check
    ASSERT_STATE(monitor, monitor->health.current_state != STATE_FAULT,
                ERR_INVALID_STATE, "System shutdown with unresolved faults");
}

/*
 * Log a message with timestamp and context information
 * Supports different log levels and error codes
 */
void log_message(debug_monitor_t* monitor, log_level_t level, error_code_t error,
                const char* message, const char* function, int line) {
    if (monitor->log_count >= MAX_LOG_ENTRIES) {
        // Log buffer full, remove oldest entries
        memmove(&monitor->log_buffer[0], &monitor->log_buffer[1],
                sizeof(log_entry_t) * (MAX_LOG_ENTRIES - 1));
        monitor->log_count = MAX_LOG_ENTRIES - 1;
    }

    // Create log entry
    log_entry_t* entry = &monitor->log_buffer[monitor->log_count++];
    entry->timestamp = time(NULL);
    entry->level = level;
    entry->error_code = error;
    strncpy(entry->message, message, sizeof(entry->message) - 1);
    strncpy(entry->function, function, sizeof(entry->function) - 1);
    entry->line_number = line;

    // Immediate console output for important messages
    if (level >= LOG_WARNING) {
        printf("[%s] %s:%d - %s\n",
               (level == LOG_WARNING) ? "WARN" :
               (level == LOG_ERROR) ? "ERROR" : "CRIT",
               function, line, message);
    }

    // Update system health based on error severity
    if (level >= LOG_ERROR) {
        monitor->health.fault_count++;
        if (monitor->health.current_state == STATE_RUNNING) {
            monitor->health.current_state = STATE_FAULT;
            LOG_WARNING(monitor, error, "System entered fault state");
        }
    }
}

/*
 * Inject a specific fault type for testing purposes
 * Demonstrates controlled fault simulation
 */
void inject_fault(debug_monitor_t* monitor, fault_type_t fault) {
    monitor->fault_injection_enabled = 1;
    monitor->active_fault = fault;

    // Record fault in history
    if (monitor->fault_count < MAX_FAULT_HISTORY) {
        fault_record_t* record = &monitor->fault_history[monitor->fault_count++];
        record->timestamp = time(NULL);
        record->fault_type = fault;
        record->resolved = 0;
        snprintf(record->description, sizeof(record->description),
                "Injected fault: %d", fault);
    }

    LOG_WARNING(monitor, ERR_NONE, "Fault injection activated");
}

/*
 * Perform comprehensive system health check
 * Monitors various system parameters and detects anomalies
 */
void check_system_health(debug_monitor_t* monitor) {
    time_t current_time = time(NULL);

    // Update uptime
    monitor->health.uptime_seconds = current_time - monitor->health.last_health_check;

    // Simulate CPU and memory usage monitoring
    monitor->health.cpu_usage_percent = 10.0f + (rand() % 40); // 10-50%
    monitor->health.memory_usage_percent = 20.0f + (rand() % 60); // 20-80%

    // Check for system overload
    if (monitor->health.cpu_usage_percent > 90.0f) {
        LOG_ERROR(monitor, ERR_SYSTEM_OVERLOAD, "CPU usage critical");
    }

    if (monitor->health.memory_usage_percent > 85.0f) {
        LOG_ERROR(monitor, ERR_MEMORY_CORRUPTION, "Memory usage critical");
    }

    // Watchdog simulation - only trigger once every 5 seconds
    static time_t last_watchdog_feed = 0;
    static int watchdog_logged = 0;

    if (last_watchdog_feed == 0) {
        last_watchdog_feed = current_time;
        watchdog_logged = 0;
    } else if (current_time - last_watchdog_feed >= 5) {  // 5 seconds
        if (!watchdog_logged) {
            LOG_CRITICAL(monitor, ERR_WATCHDOG_TIMEOUT, "Watchdog timeout detected");
            watchdog_logged = 1;
        }
        // Reset timer for next 5-second interval
        last_watchdog_feed = current_time;
    }

    monitor->health.last_health_check = current_time;
}

/*
 * Attempt to recover from detected faults
 * Implements various recovery strategies
 */
void attempt_fault_recovery(debug_monitor_t* monitor) {
    if (monitor->health.current_state != STATE_FAULT) {
        LOG_INFO(monitor, "No faults to recover from");
        return;
    }

    LOG_INFO(monitor, "Attempting fault recovery");

    // Reset fault injection
    monitor->fault_injection_enabled = 0;
    monitor->active_fault = FAULT_NONE;

    // Reset system state
    monitor->health.current_state = STATE_RECOVERY;
    monitor->health.recovery_count++;

    // Clear recent fault records
    for (int i = 0; i < monitor->fault_count; i++) {
        if (!monitor->fault_history[i].resolved) {
            monitor->fault_history[i].resolved = 1;
            LOG_INFO(monitor, "Fault resolved in recovery attempt");
        }
    }

    // Simulate recovery time
    usleep(2000000); // 2 seconds

    // Recovery is now more reliable - always succeed unless critical system failure
    // In real embedded systems, recovery would involve hardware resets, watchdog feeds, etc.
    monitor->health.current_state = STATE_RUNNING;
    LOG_INFO(monitor, "Fault recovery successful");

    // Reset CPU/memory to normal levels after recovery
    monitor->health.cpu_usage_percent = 15.0f + (rand() % 20); // 15-35%
    monitor->health.memory_usage_percent = 25.0f + (rand() % 25); // 25-50%
}

/*
 * Save log entries to file for persistent storage
 * Demonstrates file I/O error handling
 */
void save_log_to_file(debug_monitor_t* monitor) {
    if (monitor->log_file == NULL) {
        LOG_ERROR(monitor, ERR_FILE_IO_ERROR, "Log file not available");
        return;
    }

    fprintf(monitor->log_file, "\n=== Log Session End ===\n");
    fflush(monitor->log_file);

    // Check for file I/O errors
    if (ferror(monitor->log_file)) {
        LOG_ERROR(monitor, ERR_FILE_IO_ERROR, "Error writing to log file");
        clearerr(monitor->log_file);
    }
}

/*
 * Display comprehensive debug information
 * Shows system state, fault history, and performance metrics
 */
void display_debug_info(debug_monitor_t* monitor) {
    printf("\n=== Debug Information ===\n");
    printf("System State: %s\n",
           monitor->health.current_state == STATE_INIT ? "INIT" :
           monitor->health.current_state == STATE_RUNNING ? "RUNNING" :
           monitor->health.current_state == STATE_FAULT ? "FAULT" :
           monitor->health.current_state == STATE_RECOVERY ? "RECOVERY" : "SHUTDOWN");

    printf("Uptime: %u seconds\n", monitor->health.uptime_seconds);
    printf("Fault Count: %u\n", monitor->health.fault_count);
    printf("Recovery Count: %u\n", monitor->health.recovery_count);
    printf("CPU Usage: %.1f%%\n", monitor->health.cpu_usage_percent);
    printf("Memory Usage: %.1f%%\n", monitor->health.memory_usage_percent);

    printf("\nRecent Log Entries:\n");
    int start = monitor->log_count > 5 ? monitor->log_count - 5 : 0;
    for (int i = start; i < monitor->log_count; i++) {
        log_entry_t* entry = &monitor->log_buffer[i];
        printf("  [%s] %s\n",
               entry->level == LOG_DEBUG ? "DBG" :
               entry->level == LOG_INFO ? "INF" :
               entry->level == LOG_WARNING ? "WRN" :
               entry->level == LOG_ERROR ? "ERR" : "CRT",
               entry->message);
    }

    printf("\nFault History:\n");
    for (int i = 0; i < monitor->fault_count; i++) {
        fault_record_t* record = &monitor->fault_history[i];
        printf("  %s: %s\n",
               record->resolved ? "RESOLVED" : "ACTIVE",
               record->description);
    }
    printf("\n");
}

/*
 * Assert system state with detailed logging
 * Enhanced assertion that provides debugging context
 */
void assert_system_state(debug_monitor_t* monitor, system_state_t expected_state) {
    if (monitor->health.current_state != expected_state) {
        char msg[128];
        snprintf(msg, sizeof(msg), "Expected state %d, got %d",
                expected_state, monitor->health.current_state);
        LOG_CRITICAL(monitor, ERR_INVALID_STATE, msg);
        assert(monitor->health.current_state == expected_state);
    }
}

// Simulated component functions with fault detection

int simulate_sensor_reading(debug_monitor_t* monitor) {
    static int consecutive_failures = 0;
    int reading = rand() % 100;

    // Simulate occasional sensor failures
    if (rand() % 100 < 5) { // 5% failure rate
        consecutive_failures++;
        if (consecutive_failures > 3) {
            LOG_ERROR(monitor, ERR_SENSOR_FAILURE, "Sensor failure detected");
            return -1;
        }
    } else {
        consecutive_failures = 0;
    }

    return reading;
}

int simulate_actuator_control(debug_monitor_t* monitor, int command) {
    // Simulate actuator response
    if (command < 0 || command > 100) {
        LOG_WARNING(monitor, ERR_INVALID_STATE, "Invalid actuator command");
        return -1;
    }

    // Normal operation - no random failures, only fail during explicit fault injection
    return command;
}

int simulate_communication(debug_monitor_t* monitor) {
    // Normal operation - no random failures, only fail during explicit fault injection
    return 0;
}

float simulate_power_monitoring(debug_monitor_t* monitor) {
    float voltage = 24.0f + ((rand() % 200 - 100) / 100.0f); // 23.0-25.0V

    if (voltage < 22.0f || voltage > 26.0f) {
        LOG_WARNING(monitor, ERR_POWER_FLUCTUATION, "Power fluctuation detected");
    }

    return voltage;
}

// Fault simulation implementations

void simulate_sensor_noise(debug_monitor_t* monitor) {
    static int noise_count = 0;
    noise_count++;
    if (noise_count % 5 == 0) {  // Only log every 5th call to reduce spam
        LOG_WARNING(monitor, ERR_SENSOR_FAILURE, "Sensor noise simulation active");
    }
    // Additional noise simulation logic would go here
}

void simulate_actuator_failure(debug_monitor_t* monitor) {
    static int actuator_count = 0;
    actuator_count++;
    if (actuator_count % 5 == 0) {  // Only log every 5th call to reduce spam
        LOG_ERROR(monitor, ERR_ACTUATOR_STUCK, "Actuator failure simulation active");
    }
    // Additional failure simulation logic would go here
}

void simulate_communication_break(debug_monitor_t* monitor) {
    static int comm_count = 0;
    comm_count++;
    if (comm_count % 5 == 0) {  // Only log every 5th call to reduce spam
        LOG_ERROR(monitor, ERR_COMMUNICATION_LOST, "Communication break simulation active");
    }
    // Additional communication failure logic would go here
}

void simulate_power_fluctuation(debug_monitor_t* monitor) {
    static int power_count = 0;
    power_count++;
    if (power_count % 5 == 0) {  // Only log every 5th call to reduce spam
        LOG_WARNING(monitor, ERR_POWER_FLUCTUATION, "Power fluctuation simulation active");
    }
    // Additional power simulation logic would go here
}

void simulate_memory_corruption(debug_monitor_t* monitor) {
    static int memory_count = 0;
    memory_count++;
    if (memory_count % 5 == 0) {  // Only log every 5th call to reduce spam
        LOG_CRITICAL(monitor, ERR_MEMORY_CORRUPTION, "Memory corruption simulation active");
    }
    // Additional memory corruption simulation would go here
}
