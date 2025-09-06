#include <stdio.h>  // Standard input/output library for printf
#include <math.h>   // Math library for mathematical functions

// PID Controller structure to hold gains and state variables
typedef struct {
    double Kp;  // Proportional gain
    double Ki;  // Integral gain
    double Kd;  // Derivative gain
    double integral;         // Integral sum for I term
    double previous_error;   // Previous error for D term
} PIDController;

// Initialize PID controller with given gains
void initPID(PIDController *pid, double kp, double ki, double kd) {
    pid->Kp = kp;               // Set proportional gain
    pid->Ki = ki;               // Set integral gain
    pid->Kd = kd;               // Set derivative gain
    pid->integral = 0.0;        // Initialize integral sum to zero
    pid->previous_error = 0.0;  // Initialize previous error to zero
}

// Calculate PID output based on setpoint, current value, and time step
double calculatePID(PIDController *pid, double setpoint, double current_value, double dt) {
    double error = setpoint - current_value;          // Calculate error
    pid->integral += error * dt;                       // Update integral sum
    double derivative = (error - pid->previous_error) / dt;  // Calculate derivative
    pid->previous_error = error;                       // Store current error for next derivative calculation
    // PID output is sum of proportional, integral, and derivative terms
    return pid->Kp * error + pid->Ki * pid->integral + pid->Kd * derivative;
}

// Simple plant model: simulate motor speed update based on input, load, inertia, and time step
double updatePlant(double current_speed, double input, double load, double inertia, double dt) {
    double acceleration = (input - load) / inertia;   // Calculate acceleration from net force and inertia
    return current_speed + acceleration * dt;         // Update speed based on acceleration and time step
}

int main() {
    PIDController pid;                 // Declare PID controller instance
    initPID(&pid, 1.0, 0.1, 0.05);    // Initialize PID with example gains

    double inertia = 1.0;              // Motor inertia
    double load = 0.5;                 // Constant load on motor
    double dt = 0.1;                   // Time step for simulation

    double setpoint;                    // Desired motor speed (RPM)
    printf("Enter desired motor speed (RPM): ");
    scanf("%lf", &setpoint);           // Read user input for setpoint
    double current_speed = 0.0;        // Initial motor speed
    int steps = 100;                   // Number of simulation steps

    printf("PID Controller Simulation for Motor Speed Control\n");
    printf("Setpoint: %.2f RPM\n", setpoint);
    printf("Time\tSpeed\tPID Output\n");

    for (int i = 0; i < steps; i++) {
        double pid_output = calculatePID(&pid, setpoint, current_speed, dt);  // Calculate PID output
        current_speed = updatePlant(current_speed, pid_output, load, inertia, dt);  // Update motor speed

        printf("%.1f\t%.2f\t%.2f\n", i * dt, current_speed, pid_output);    // Print time, speed, and PID output
    }

    return 0;   // End of program
}
