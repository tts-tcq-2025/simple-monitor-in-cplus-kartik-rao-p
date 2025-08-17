#include <stdio.h>    // For printf
#include <stdbool.h>  // For bool type
#include <assert.h>   // For assert macro
#include <string.h>   // Not strictly needed for this example, but good to include for string operations if they were more complex.

// Enum for different check types
typedef enum {
    TEMPERATURE,
    SOC,
    CHARGE_RATE
} CheckType;

// Function to check if a value is within a given range
bool checkRange(float value, float min, float max, const char* errorMsg) {
    if (value < min || value > max) {
        printf("%s\n", errorMsg); // Use printf instead of cout
        return false;
    }
    return true;
}


// Function for temperature check
bool checkTemperature(float v) {
    return checkRange(v, 0, 45, "Temperature out of range!");
}

// Function for SOC check
bool checkSOC(float v) {
    return checkRange(v, 20, 80, "State of Charge out of range!");
}

// Function for Charge Rate check
bool checkChargeRate(float v) {
    return checkRange(v, 0, 0.8, "Charge Rate out of range!");
}


// Define a type for a function pointer that takes a float and returns a bool
typedef bool (*CheckFunctionPtr)(float);

// Structure to hold a CheckType and its corresponding function pointer
// This replaces a single entry in the C++ std::map
typedef struct {
    CheckType type;
    CheckFunctionPtr checker_func;
} CheckEntry;

// Static array of CheckEntry structs to store all checkers.
static const CheckEntry checkers[] = {
    {TEMPERATURE, checkTemperature},
    {SOC, checkSOC},
    {CHARGE_RATE, checkChargeRate}
};

// Calculate the number of elements in the checkers array
static const int NUM_CHECKERS = sizeof(checkers) / sizeof(checkers[0]);


// Function to check a parameter based on its type
bool checkParameter(CheckType check, float value) {
    // Iterate through the 'checkers' array to find the correct function
    for (int i = 0; i < NUM_CHECKERS; ++i) {
        if (checkers[i].type == check) {
            // Call the function through the function pointer
            return checkers[i].checker_func(value);
        }
    }
    // Unknown check type (no equivalent in the map)
    return false;
}

// Function to check if the battery is OK
bool batteryIsOk(float temperature, float soc, float chargeRate) {
    // Logical AND of all checks
    return checkParameter(TEMPERATURE, temperature) &&
           checkParameter(SOC, soc) &&
           checkParameter(CHARGE_RATE, chargeRate);
}

// Main function for testing
int main() {
    // Use assert macro for testing. It evaluates the condition; if false, it prints an error and aborts.
    assert(batteryIsOk(25, 70, 0.7) == true);
    assert(batteryIsOk(50, 85, 0) == false); // This should fail if conditions are not met

    printf("All tests passed.\n"); // Use printf instead of cout
    return 0;
}
