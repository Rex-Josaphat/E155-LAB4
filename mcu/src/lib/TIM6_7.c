// Josaphat Ngoga
// jngoga@g.hmc.edu
// 9/25/2025

#include "TIM6_7.h"
#include "GPIO.h"
#include <stdint.h>

// Clear TIM count status
void resetTIM(TIM6_7* TIM) {
    TIM->SR &= ~(1 << 0); // Clear TIM UIF
    TIM->CNT = 0; // Reset TIM counter to 0
}

// Divide input SYS Clock (4MHZ) to required TIM Frequency
void setPrescaler(TIM6_7* TIM, uint32_t val) {
    TIM->PSC = val;
    TIM->EGR |= (1 << 0); // update event (UG bit)    
}   

// Enable counter for Specified TIM
void counterON(TIM6_7* TIM) {
    TIM->CR1 |= (1 << 0);
}

// Set counter
void setArr(TIM6_7* TIM, uint32_t val) {
    TIM->ARR = val;
}

// Implement ms delay counter
void setDelay(TIM6_7* TIM, uint32_t ms) {
    setArr(TIM, ms-1);
    resetTIM(TIM);
    counterON(TIM); // Enable Counter for specified TIM
    while (!(TIM->SR & 1)) {} // Wait for counter overflow
}

void genPWM(uint32_t freq, uint32_t dur, int pin, TIM6_7* TIMdelay, TIM6_7* TIMwave) {
    if (dur <= 0) return;
    
    if (freq == 0) { // Base case
        setDelay(TIMdelay, dur);
    } else {
        // Configure timers
        uint32_t half_freq = 1000000 / (2 * freq); // half-period in us @1MHz
        setArr(TIMdelay, dur-1);
        setArr(TIMwave, half_freq - 1); // half-period @1MHz
        
        // Restore timers to known (zero) state
        resetTIM(TIMdelay);
        resetTIM(TIMwave);

        // Ensure Timer Counters are ON
        counterON(TIMdelay); // Turn on delay counter
        counterON(TIMwave); // Turn on wave counter

        // Generate square wave for spefified frequeny and delay
        while (!(TIMdelay->SR & 1)) {
            digitalWrite(pin, 1); // Drive HIGH for one half-period
            while(!(TIMwave->SR & 1)) {} // Wait for half-period overflow
            TIMwave->SR &= ~(1 << 0); // Clear UIF on wave timer (prepare for next half)
            
            if ((TIMdelay->SR) != 0) break;  // Check UIF: Exit if total duration elapsed mid-cycle

            digitalWrite(pin, 0); // Drive LOW for one half-period
            while(!(TIMwave->SR & 1)) {} // Wait for half-period overflow
            TIMwave->SR &= ~(1 << 0);// Clear UIF on wave timer
        }
    }
}