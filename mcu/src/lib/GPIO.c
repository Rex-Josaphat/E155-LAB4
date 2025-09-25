// Josaphat Ngoga
// jngoga@g.hmc.edu
// 9/23/2025

// Source code for GPIO functions

#include "GPIO.h"

void pinMode(int pin, int function, GPIO* GPIO) {
    switch (function) {
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

int digitalRead(int pin, GPIO* GPIO) {
    return ((GPIO->IDR) >> pin) & 1;
}

void digitalWrite(int pin, int val, GPIO* GPIO) {
    GPIO->ODR |= (1 << pin);
}

void togglePin(int pin, GPIO* GPIO) {
    // Use XOR to toggle
    GPIO->ODR ^= (1 << pin);
}

void swPullUp(int pin, GPIO* GPIO) {
    GPIO->PUPDR &= ~(0x3 << (2 * pin)); // Clear the 2 bits for this pin
    GPIO->PUPDR |=  (0x1 << (2 * pin)); // Set Pin to 01 (pull-up)
}