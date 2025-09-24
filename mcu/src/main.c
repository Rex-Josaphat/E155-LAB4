// Josaphat Ngoga
// jngoga@g.hmc.edu
// 9/21/2025

// Main file for running tones and frequencites. It also executes duration logic

#include <stdint.h>
#include <lib/GPIO.h>
#include <lib/RCC.h>

// Für Elise: Pitch in Hz, duration in ms
const int Für_Elise[][2] = {
    {659, 125},
    {623, 125},
    {659, 125},
    {623, 125},
    {659, 125},
    {494, 125},
    {587, 125},
    {523, 125},
    {440, 250},
    {0, 125},
    {262, 125},
    {330, 125},
    {440, 125},
    {494, 250},
    {0, 125},
    {330, 125},
    {416, 125},
    {494, 125},
    {523, 250},
    {0, 125},
    {330, 125},
    {659, 125},
    {623, 125},
    {659, 125},
    {623, 125},
    {659, 125},
    {494, 125},
    {587, 125},
    {523, 125},
    {440, 250},
    {0, 125},
    {262, 125},
    {330, 125},
    {440, 125},
    {494, 250},
    {0, 125},
    {330, 125},
    {523, 125},
    {494, 125},
    {440, 250},
    {0, 125},
    {494, 125},
    {523, 125},
    {587, 125},
    {659, 375},
    {392, 125},
    {699, 125},
    {659, 125},
    {587, 375},
    {349, 125},
    {659, 125},
    {587, 125},
    {523, 375},
    {330, 125},
    {587, 125},
    {523, 125},
    {494, 250},
    {0, 125},
    {330, 125},
    {659, 125},
    {0, 250},
    {659, 125},
    {1319, 125},
    {0, 250},
    {623, 125},
    {659, 125},
    {0, 250},
    {623, 125},
    {659, 125},
    {623, 125},
    {659, 125},
    {623, 125},
    {659, 125},
    {494, 125},
    {587, 125},
    {523, 125},
    {440, 250},
    {0, 125},
    {262, 125},
    {330, 125},
    {440, 125},
    {494, 250},
    {0, 125},
    {330, 125},
    {416, 125},
    {494, 125},
    {523, 250},
    {0, 125},
    {330, 125},
    {659, 125},
    {623, 125},
    {659, 125},
    {623, 125},
    {659, 125},
    {494, 125},
    {587, 125},
    {523, 125},
    {440, 250},
    {0, 125},
    {262, 125},
    {330, 125},
    {440, 125},
    {494, 250},
    {0, 125},
    {330, 125},
    {523, 125},
    {494, 125},
    {440, 500},
    {0, 0}};

int main(void)
{

    // Define Pins Used
    // int tunePin
    // int song1Pin
    // int song2Pin

    // Enable GPIO and Timers

    // Set Pin Modes

    // Enable Timer Counter

    // Configure ABP Prescale

    // Set Timer 15 Prescale

    // Set Timer 16 Prescale

    // Execute Logic

    int tunes;

    while (1)
    {

        // Read Song Pins
        // volatile int sw1 = digitalRead(); // Set to play Für Elise
        // volatile int sw2 = digitalRead(); // Set to play Happy

        // Switching Logic
        //     if (!sw1) {
        //         tunes = sizeof(Für_Elise);
        //         for (int i = 0; i < tunes; i++){
        //             // Play song
        //         }
        //     }

        //     if (!sw2) {
        //         tunes = sizeof(Für_Elise);
        //         for (int i = 0; i < tunes; i++){
        //             // Play song
        //         }
        //     }
        // }
        // return 0;
    }