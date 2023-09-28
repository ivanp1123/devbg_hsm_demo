#include <stdio.h>
#include <stdbool.h>

// Define states
enum State {
    Unarmed,
    Armed,
    Wait_For_Trigger,
    Final_Countdown,
    Boom
};

// Define events
enum Event {
    ArmButtonPress,
    WireCutRed,
    WireCutPink,
    PhoneCallReceived,
    TimerTick
};

// Define a structure for a state transition
struct Transition {
    enum State current;
    enum Event event;
    enum State next;
    void (*action)();
};

// Define boolean flags for conditions
bool isIntendedCaller = false;
bool isCounting = false;

// Function to simulate actions
void turnOnGreenLed() {
    printf("Green LED turned on.\n");
}

void turnOnRedLed() {
    printf("Red LED turned on.\n");
}

void turnOnBlinkingOrangeLed() {
    printf("Blinking orange LED turned on.\n");
}

void decreaseCounter() {
    printf("Countdown decreased.\n");
}

void expressPity() {
    printf("Expressing pity on cutting the wrong wire.\n");
}

// Function to handle the "arm button press" event
void armButtonPressAction() {
    printf("Armed the bomb.\n");
}

// Function to handle the "wire cut" events
void wireCutRedAction() {
    isCounting = true;
    turnOnGreenLed();
}

void wireCutPinkAction() {
    printf("Boom! You've triggered the bomb.\n");
    expressPity();
}

// Function to handle the "phone call received" event
void phoneCallReceivedAction() {
    isIntendedCaller = true;
    turnOnBlinkingOrangeLed();
}

// Function to handle the "timer tick" event
void timerTickAction() {
    if (isCounting) {
        decreaseCounter();
        if (isIntendedCaller) {
            if (isCounting) {
                turnOnBlinkingOrangeLed();
            }
            if (!isCounting) {
                printf("Boom! You've triggered the bomb.\n");
                expressPity();
            }
        }
    }
}

// Define the state transition table
const struct Transition transitions[] = {
    {Unarmed, ArmButtonPress, Armed, armButtonPressAction},
    {Armed, WireCutRed, Unarmed, wireCutRedAction},
    {Armed, WireCutPink, Boom, wireCutPinkAction},
    {Armed, PhoneCallReceived, Final_Countdown, phoneCallReceivedAction},
    {Final_Countdown, TimerTick, Final_Countdown, timerTickAction},
    {Final_Countdown, TimerTick, Boom, NULL}
};

int main() {
    // Initialize the initial state
    enum State currentState = Unarmed;

    // Simulate the statechart behavior
    for (int i = 0; i < sizeof(transitions) / sizeof(transitions[0]); i++) {
        if (transitions[i].current == currentState) {
            printf("Transition: %d --> %d\n", currentState, transitions[i].next);
            currentState = transitions[i].next;
            if (transitions[i].action) {
                transitions[i].action();
            }
        }
    }

    return 0;
}
