// Josaphat Ngoga
// jngoga@g.hmc.edu
// 9/21/2025

// Main file for running tones and frequencites. It also executes duration logic

#include <stdint.h>
#include <lib/GPIO.h>
#include <lib/RCC.h>
#include <lib/TIM6_7.h>

// Für Elise: Pitch in Hz, duration in ms
const int Für_Elise[][2] = {
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

int main(void) {

    // Define Pins Used
    int tunePin = 10; // PWM Output Pin
    int song1Pin = 4; // Previous Song
    int song2Pin = 7; // Next Song
    
    // Configure ABP Prescale (Divide SYSCLK (4MHz) by 4 to 1MHz)
    RCC->CFGR |=  (1 << 4);
    RCC->CFGR &= ~(1 << 5);
    RCC->CFGR &= ~(1 << 6);
    RCC->CFGR |=  (1 << 7);
    
    // Enable GPIO and Timers
    RCC->AHB2ENR |= (1 << 0); // Enable GPIOA
    timerEnable(RCC, 6); // Enable TIM6
    timerEnable(RCC, 7); // Enable TIM7
    
    // Enable internal pull up for onboard switches
    swPullUp(song1Pin, GPIOA);
    swPullUp(song2Pin, GPIOA);
    
    // Set Pin Modes
    pinMode(tunePin, GPIO_OUTPUT, GPIOA);
    pinMode(song1Pin, GPIO_INPUT, GPIOA);
    pinMode(song2Pin, GPIO_INPUT, GPIOA);

    // Set TIM Prescalers
    setPrescaler(TIM6, 0b1111101000); // Divide input clock frequency to counter frequency of 1kHz
    setPrescaler(TIM7, 0); // Maintain input frequency of 1MHz for wave gen

    // Execute Logic
    while (1) {

        // Read Song Pins
        volatile int sw1 = digitalRead(song1Pin, GPIOA); // Set to play Für Elise
        volatile int sw2 = digitalRead(song2Pin, GPIOA); // Set to play Happy

        // Switching Logic
        if (!sw1) {
            for (int i = 0; i < sizeof(Für_Elise); i++){
                // Play song
            }
        }

        if (!sw2) {
            for (int i = 0; i < sizeof(Für_Elise); i++){
                // Play song
            }
        }
    }
    return 0;
}