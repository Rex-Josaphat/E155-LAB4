// Josaphat Ngoga
// jngoga@g.hmc.edu
// 9/21/2025

// Main file for running tones and frequencites. It also executes duration logic

#include "lib/RCC.h"
#include "lib/TIM6_7.h"
#include "lib/GPIO.h"
#include <stdint.h>

// Für Elise: Beethoven Pitch in Hz, duration in ms
const int Fur_Elise[][2] = {
    {659,125}, {623,125}, {659,125} , {623,125}, {659,125}, {494,125}, {587,125}, {523,125}, {440,250}, {0,125}  ,
    {262,125}, {330,125}, {440,125} , {494,250}, {0,125}  , {330,125}, {416,125}, {494,125}, {523,250}, {0,125}  ,
    {330,125}, {659,125}, {623,125} , {659,125}, {623,125}, {659,125}, {494,125}, {587,125}, {523,125}, {440,250},
    {0,125}  , {262,125}, {330,125} , {440,125}, {494,250}, {0,125}  , {330,125}, {523,125}, {494,125}, {440,250},
    {0,125}  , {494,125}, {523,125} , {587,125}, {659,375}, {392,125}, {699,125}, {659,125}, {587,375}, {349,125},
    {659,125}, {587,125}, {523,375} , {330,125}, {587,125}, {523,125}, {494,250}, {0,125}  , {330,125}, {659,125},
    {0,250}  , {659,125}, {1319,125}, {0,250}  , {623,125}, {659,125}, {0,250}  , {623,125}, {659,125}, {623,125},
    {659,125}, {623,125}, {659,125} , {494,125}, {587,125}, {523,125}, {440,250}, {0,125}  , {262,125}, {330,125},
    {440,125}, {494,250}, {0,125}   , {330,125}, {416,125}, {494,125}, {523,250}, {0,125}  , {330,125}, {659,125},
    {623,125}, {659,125}, {623,125} , {659,125}, {494,125}, {587,125}, {523,125}, {440,250}, {0,125}  , {262,125},
    {330,125}, {440,125}, {494,250} , {0,125}  , {330,125}, {523,125}, {494,125}, {440,500}, {0,0}    };


// Faded: Alan Walker Pitch in Hz, duration in ms
const int Faded[][2] = {
    {370,666}, {370,666}, {370,666}, {466,666}, {622,666}, {622,666}, {622,666}, {554,666}, {466,666}, {466,666}, 
    {466,666}, {466,666}, {698,666}, {698,666}, {698,666}, {622,666}, {165,333}, {247,333}, {392,666}, {196,333}, 
    {247,333}, {392,666}, {165,333}, {247,333}, {392,666}, {196,333}, {247,333}, {494,666}, {131,333}, {196,333}, 
    {659,666}, {165,333}, {196,333}, {659,666}, {131,333}, {196,333}, {659,666}, {165,333}, {196,333}, {587,666}, 
    {196,333}, {294,333}, {494,666}, {247,333}, {294,333}, {494,666}, {196,333}, {294,333}, {494,666}, {247,333}, 
    {294,333}, {494,666}, {147,333}, {220,333}, {370,666}, {185,333}, {220,333}, {370,666}, {147,333}, {220,333}, 
    {370,666}, {185,333}, {220,333}, {330,666}, {466,666}, {370,666}, {370,666}, {370,666}, {466,666}, {622,666}, 
    {622,666}, {622,666}, {554,666}, {466,666}, {466,666}, {466,666}, {466,666}, {698,666}, {698,666}, {698,666}, 
    {622,666}, {0,0}    };


int main(void) {

    // Define Pins Used
    int tunePin = 9; // PWM Output Pin
    int song1Pin = 7; // Previous Song
    int song2Pin = 4; // Next Song
    
    // Configure AHB Prescale (Divide SYSCLK (4MHz) by 4 to 1MHz)
    RCC->CFGR |=  (0b1001 << 4);
    
    // Enable GPIO and Timers
    RCC->AHB2ENR |= (1 << 0); // Enable GPIOA
    RCC->APB1ENR1 |= (1 << 4); // Enable TIM6
    RCC->APB1ENR1 |= (1 << 5); // Enable TIM7
    
    // Set Prescalers
    setPrescaler(TIM6, 999); // Divide input clock frequency to counter frequency of 1kHz
    setPrescaler(TIM7, 0); // Maintain input frequency of 1MHz for wave gen
    
    // Enable internal pull up for onboard switches
    swPullUp(song1Pin);
    swPullUp(song2Pin);

    // Set Pin Modes
    pinMode(tunePin, GPIO_OUTPUT);
    pinMode(song1Pin, GPIO_INPUT);
    pinMode(song2Pin, GPIO_INPUT);

    // Execute Logic
    while (1) {

        // Read Song Pins
        volatile int sw1 = digitalRead(song1Pin); // Set to play Für Elise
        volatile int sw2 = digitalRead(song2Pin); // Set to play Faded

        // Switching Logic
        if (!sw1) {
            int tunes = sizeof(Fur_Elise) / sizeof(Fur_Elise[0]);
            for (int i = 0; i < tunes; i++){
                uint32_t freq = Fur_Elise[i][0];
                uint32_t dur = Fur_Elise[i][1];

                genPWM(freq, dur, tunePin, TIM6, TIM7); // Play song
            }
        }

        if (!sw2) {
            int tunes = sizeof(Faded) / sizeof(Faded[0]);
            for (int i = 0; i < tunes; i++){
                uint32_t freq = Faded[i][0];
                uint32_t dur = Faded[i][1];

                genPWM(freq, dur, tunePin, TIM6, TIM7); // Play song
            }
        }
    }
    return 0;
}