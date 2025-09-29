// Josaphat Ngoga
// jngoga@g.hmc.edu
// 9/23/2025

// Source code for GPIO functions

#include "GPIO.h"

void pinMode(int pin, int function) {
    switch (function)
    {
    case GPIO_INPUT:
        GPIO->MODER &= ~(0b11 << 2 * pin);
        break;
    case GPIO_OUTPUT:
        GPIO->MODER |= (0b1 << 2 * pin);
        GPIO->MODER &= ~(0b1 << (2 * pin + 1));
        break;
    case GPIO_ALT:
        GPIO->MODER &= ~(0b1 << 2 * pin);
        GPIO->MODER |= (0b1 << (2 * pin + 1));
        break;
    case GPIO_ANALOG:
        GPIO->MODER |= (0b11 << 2 * pin);
        break;
    }
}

int digitalRead(int pin) {
    return ((GPIO->IDR) >> pin) & 1;
}

void digitalWrite(int pin, int val) {
    if (val)
    {
        GPIO->ODR |= (1 << pin); // Turn ON pin
    }
    else
    {
        GPIO->ODR &= ~(1 << pin); // Turn OFF pin
    }
}

void togglePin(int pin) {
    // Use XOR to toggle
    GPIO->ODR ^= (1 << pin);
}

void swPullUp(int pin) {
    GPIO->PURPDR &= ~(0x3 << (2 * pin)); // Clear the 2 bits for this pin
    GPIO->PURPDR |= (0x1 << (2 * pin));  // Set Pin to 01 (pull-up)
}