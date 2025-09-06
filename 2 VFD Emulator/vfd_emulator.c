#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#ifdef _WIN32
#include <windows.h>
#define usleep(x) Sleep((x) / 1000)  // Windows-compatible usleep
#else
#include <unistd.h>
#endif

// VFD Emulator Constants
#define MAX_FREQUENCY 60.0f      // Maximum allowable frequency in Hz
#define MIN_FREQUENCY 0.0f       // Minimum frequency (off) in Hz
#define NOMINAL_VOLTAGE 480.0f   // Nominal motor voltage in Volts
#define MOTOR_INERTIA 0.5f       // Simulated motor inertia (not used in this simplified model)
#define RAMP_RATE 10.0f          // Frequency ramp rate in Hz per second
#define SIMULATION_STEP 0.1f     // Simulation time step in seconds

// VFD Operating States enumeration
typedef enum {
    STATE_OFF = 0,       // VFD is powered off, no output
    STATE_STARTING = 1,  // VFD is starting, ramping frequency up to target
    STATE_RUNNING = 2,   // VFD is running at target frequency
    STATE_STOPPING = 3   // VFD is stopping, ramping frequency down to zero
} vfd_state_t;

// VFD Structure to hold all relevant state and parameters
typedef struct {
    vfd_state_t state;          // Current operational state of the VFD
    float target_frequency;     // Desired output frequency setpoint (Hz)
    float current_frequency;    // Current actual output frequency (Hz)
    float output_voltage;       // Calculated output voltage (Volts) using V/F ratio
    float motor_speed;          // Simulated motor speed in RPM
    float motor_torque;         // Simulated motor torque in Nm
    float ramp_time;            // Time spent ramping (not used in this simplified model)
} vfd_t;

// Function Prototypes
void vfd_init(vfd_t* vfd);
void vfd_set_frequency(vfd_t* vfd, float frequency);
void vfd_start(vfd_t* vfd);
void vfd_stop(vfd_t* vfd);
void vfd_update(vfd_t* vfd, float dt);
void vfd_display_status(vfd_t* vfd);
float calculate_voltage(float frequency);
float simulate_motor_torque(float frequency, float speed);

int main() {
    vfd_t vfd;                 // Declare VFD instance
    char command;              // User input command
    float target_freq;         // Frequency input by user

    printf("VFD (Variable Frequency Drive) Emulator\n");
    printf("=======================================\n\n");

    vfd_init(&vfd);            // Initialize VFD to default state

    // Display available commands to user
    printf("Commands:\n");
    printf("s - Start VFD\n");
    printf("x - Stop VFD\n");
    printf("f <freq> - Set frequency (0-60 Hz)\n");
    printf("q - Quit\n\n");

    // Main simulation loop - runs continuously until quit
    while (1) {
        // Check for keyboard input without blocking
        if (_kbhit()) {
            char command = _getch();
            if (command == 'q') {
                printf("Exiting...\n");
                return 0;
            } else if (command == 's') {
                vfd_start(&vfd);  // Start the VFD
            } else if (command == 'x') {
                vfd_stop(&vfd);   // Stop the VFD
            } else if (command == 'f') {
                // Prompt user for frequency input
                printf("Enter frequency (0-60 Hz): ");
                scanf("%f", &target_freq);
                if (target_freq >= MIN_FREQUENCY && target_freq <= MAX_FREQUENCY) {
                    vfd_set_frequency(&vfd, target_freq);  // Set new frequency
                } else {
                    printf("Invalid frequency! Must be between 0-60 Hz\n");
                }
            } else {
                printf("Invalid command!\n");
            }
        }

        // Update VFD state and motor simulation
        vfd_update(&vfd, SIMULATION_STEP);
        // Display current status
        vfd_display_status(&vfd);
        // Delay for real-time simulation (100ms)
        usleep(100000);
    }

    return 0;
}

// Initialize VFD structure with default values
void vfd_init(vfd_t* vfd) {
    vfd->state = STATE_OFF;
    vfd->target_frequency = 0.0f;
    vfd->current_frequency = 0.0f;
    vfd->output_voltage = 0.0f;
    vfd->motor_speed = 0.0f;
    vfd->motor_torque = 0.0f;
    vfd->ramp_time = 0.0f;
}

// Set the target frequency if VFD is running
void vfd_set_frequency(vfd_t* vfd, float frequency) {
    if (vfd->state == STATE_RUNNING) {
        vfd->target_frequency = frequency;
        printf("Target frequency set to %.1f Hz\n", frequency);
    } else {
        printf("VFD must be running to set frequency!\n");
    }
}

// Start the VFD if it is off
void vfd_start(vfd_t* vfd) {
    if (vfd->state == STATE_OFF) {
        vfd->state = STATE_STARTING;
        vfd->target_frequency = 30.0f;  // Default start frequency
        printf("VFD starting...\n");
    } else {
        printf("VFD is already running!\n");
    }
}

// Stop the VFD if it is running or starting
void vfd_stop(vfd_t* vfd) {
    if (vfd->state == STATE_RUNNING || vfd->state == STATE_STARTING) {
        vfd->state = STATE_STOPPING;
        vfd->target_frequency = 0.0f;
        printf("VFD stopping...\n");
    } else {
        printf("VFD is not running!\n");
    }
}

// Update the VFD state and simulate motor response over time step dt
// This function implements the state machine and physics simulation
void vfd_update(vfd_t* vfd, float dt) {
    float freq_diff;        // Difference between target and current frequency
    float ramp_increment;   // Amount to change frequency per time step

    // State machine implementation
    switch (vfd->state) {
        case STATE_STARTING:
            // Ramp up frequency towards target frequency at RAMP_RATE Hz/s
            freq_diff = vfd->target_frequency - vfd->current_frequency;
            ramp_increment = RAMP_RATE * dt;

            if (fabs(freq_diff) < ramp_increment) {
                // Close enough to target, snap to exact value and change state
                vfd->current_frequency = vfd->target_frequency;
                vfd->state = STATE_RUNNING;
                printf("VFD reached running state\n");
            } else {
                // Increment/decrement frequency towards target
                vfd->current_frequency += (freq_diff > 0) ? ramp_increment : -ramp_increment;
            }
            break;

        case STATE_RUNNING:
            // Maintain or adjust frequency towards new target if changed
            freq_diff = vfd->target_frequency - vfd->current_frequency;
            ramp_increment = RAMP_RATE * dt;

            if (fabs(freq_diff) > ramp_increment) {
                // Still ramping to new frequency
                vfd->current_frequency += (freq_diff > 0) ? ramp_increment : -ramp_increment;
            } else {
                // At target frequency
                vfd->current_frequency = vfd->target_frequency;
            }
            break;

        case STATE_STOPPING:
            // Ramp down frequency to zero
            freq_diff = 0.0f - vfd->current_frequency;
            ramp_increment = RAMP_RATE * dt;

            if (fabs(vfd->current_frequency) < ramp_increment) {
                // Close to zero, set to zero and turn off
                vfd->current_frequency = 0.0f;
                vfd->state = STATE_OFF;
                printf("VFD stopped\n");
            } else {
                // Decrement frequency towards zero
                vfd->current_frequency += (freq_diff > 0) ? ramp_increment : -ramp_increment;
            }
            break;

        case STATE_OFF:
        default:
            // Ensure frequency is zero when off
            vfd->current_frequency = 0.0f;
            break;
    }

    // Calculate output voltage using constant V/F (Volts per Hz) ratio
    vfd->output_voltage = calculate_voltage(vfd->current_frequency);

    // Simulate motor speed: synchronous speed = frequency * 60 / poles
    // Actual speed includes slip (motor can't reach synchronous speed)
    vfd->motor_speed = vfd->current_frequency * 60.0f / 2.0f * 0.98f;

    // Calculate motor torque based on slip
    vfd->motor_torque = simulate_motor_torque(vfd->current_frequency, vfd->motor_speed);
}

// Display current VFD state and motor parameters
void vfd_display_status(vfd_t* vfd) {
    const char* state_names[] = {"OFF", "STARTING", "RUNNING", "STOPPING"};

    printf("State: %s | Freq: %.1f Hz | Volt: %.1f V | Speed: %.1f RPM | Torque: %.2f Nm\n",
           state_names[vfd->state],
           vfd->current_frequency,
           vfd->output_voltage,
           vfd->motor_speed,
           vfd->motor_torque);
}

// Calculate output voltage based on frequency using constant V/F ratio
float calculate_voltage(float frequency) {
    if (frequency <= 0.0f) return 0.0f;
    return (frequency / MAX_FREQUENCY) * NOMINAL_VOLTAGE;
}

// Simulate motor torque based on slip
// In induction motors, torque is proportional to slip
// Slip = (synchronous speed - actual speed) / synchronous speed
// Here we use a simplified calculation for demonstration
float simulate_motor_torque(float frequency, float speed) {
    // Calculate slip in Hz: frequency - (speed / 30)
    // Since synchronous speed = frequency * 30 RPM for 2-pole motor
    // speed / 30 gives frequency equivalent of actual speed
    float slip = frequency - (speed * 2.0f / 60.0f);  // Convert RPM to Hz equivalent
    // Torque = slip * constant (simplified model)
    return slip * 10.0f;
}
