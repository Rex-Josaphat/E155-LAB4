// Josaphat Ngoga
// jngoga@g.hmc.edu
// 9/25/2025

#include "TIM6_7.h"
#include "GPIO.h"
#include <stdint.h>

// Enable counter on TIM
void counterON(TIM6_7* TIM) {
    TIM->CR1 |= (1 << 0);
}

// Set update interrupt for TIM when counter is done to acknowledge overflow
void resetFlag(TIM6_7* TIM) {
    TIM->SR &= ~(1 << 0);
}

// Clear TIM count status
void resetTIM(TIM6_7* TIM) {
    TIM->SR &= ~(1 << 0); // Clear TIM UIF
    TIM->CNT = 0; // Reset TIM counter to 0
}

// Divide input SYS Clock (4MHZ) to required TIM Frequency
void setPrescaler(TIM6_7* TIM, uint32_t val) {
    TIM->PSC = val-1;
} 

// Set counter
void setArr(TIM6_7* TIM, uint32_t val) {
    TIM->ARR = val;
}

// Implement ms delay counter
void setDelay(TIM6_7* TIM, int ms) {
    setArr(TIM, ms-1);
    resetTIM(TIM);
    counterON(TIM); // Enable Counter for specified TIM
    while (!(TIM->SR)) {} // Wait for counter overflow
}

void genPWM(uint32_t freq, uint32_t dur, int pin, TIM6_7* TIMdelay, TIM6_7* TIMwave) {
    if (dur <= 0) return;
    
    if (freq == 0) { // Base case
        setDelay(TIMdelay, dur);
    } else {
        // Configure timers
        setArr(TIMdelay, dur-1);
        setArr(TIMwave, (1000000 / (2 * freq))-1); // half-period @1MHz
        
        // Restore timers to known (zero) state
        resetTIM(TIMdelay);
        resetTIM(TIMwave);

        // Ensure Timer Counters are ON
        counterON(TIMdelay); // Turn on delay counter
        counterON(TIMwave); // Turn on wave counter

        // Generate square wave for spefified frequeny and delay
        while (!(TIMdelay->SR)) {
            digitalWrite(pin, 1); // Drive HIGH for one half-period
            while(!(TIMwave->SR)) {} // Wait for half-period overflow
            resetFlag(TIMwave); // Clear UIF on wave timer (prepare for next half)
            
            if ((TIMdelay->SR) != 0) break;  // If total duration elapsed mid-cycle, exit cleanly

            digitalWrite(pin, 0); // Drive LOW for one half-period
            while(!(TIMwave->SR)) {} // Wait for half-period overflow
            resetFlag(TIMwave); // Clear UIF on wave timer
        }
    }
}