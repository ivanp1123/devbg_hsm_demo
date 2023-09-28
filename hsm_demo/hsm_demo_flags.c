#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> // For sleep() function

// Define boolean flags to represent the statechart states and conditions
bool isUnarmed = true;
bool isArmed = false;
bool isWireCut = false;
bool isRedWire = false;
bool isPinkWire = false;
bool isPhoneCallReceived = false;
bool isIntendedCaller = false;
bool isCounting = false;
bool isCountZero = false;

// Function to simulate the "arm button press" event
void armButtonPress() {
    if (isUnarmed) {
        isUnarmed = false;
        isArmed = true;
        printf("Armed the bomb.\n");
    }
}

// Function to simulate the "wire cut event" and associated actions
void wireCutEvent(bool isRed) {
    if (isArmed) {
        isArmed = false;
        if (isRed) {
            isRedWire = true;
            printf("Red wire cut. Green LED turned on.\n");
        } else {
            isPinkWire = true;
            printf("Pink wire cut. Red LED turned on.\n");
        }
    }
}

// Function to simulate the "phone call received" event and associated actions
void phoneCallReceived(bool intendedCaller) {
    if (isArmed) {
        isWaitForTrigger = false;
        isCounting = true;
        isIntendedCaller = intendedCaller;
        printf("Phone call received. Blinking orange LED turned on.\n");
    }
}

// Function to simulate the countdown timer and associated actions
void countdownTimer() {
    if (isCounting) {
        printf("Timer tick.\n");
        if (isCountZero) {
            printf("Boom! You've triggered the bomb.\n");
            // Additional actions for the "Boom" state
        } else {
            // Decrease the countdown and check if it reached zero
            // In this simulation, we'll just decrement a counter to represent the timer.
            // In a real application, you would use a timer or delay function.
            static int countdown = 5;
            countdown--;
            if (countdown == 0) {
                isCountZero = true;
            }
        }
    }
}

int main() {
    // Simulate the statechart behavior

    // Initial state is Unarmed
    armButtonPress(); // Transition to Armed state
    wireCutEvent(true); // Cut the red wire
    phoneCallReceived(true); // Receive an intended phone call
    countdownTimer(); // Wait for countdown

    // Simulate more transitions and events as needed...

    return 0;
}
