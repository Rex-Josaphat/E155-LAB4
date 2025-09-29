// Josaphat Ngoga
// jngoga@g.hmc.edu
// 9/25/2025

// Header file for basic timers 6 and 7

#ifndef TIM6_7_H
#define TIM6_7_H

#include <stdint.h>

///////////////////////////////////////////////////////////////////////////////
// Definitions
///////////////////////////////////////////////////////////////////////////////

#define __IO volatile

// Base addresses for TIM6 and TIM7 ports
#define TIM6_BASE (0x40001000UL)
#define TIM7_BASE (0x40001400UL)

// TIM6 and TIM7 Typedef Struct
typedef struct {
    __IO uint32_t CR1; // TIM Control Register 1
    __IO uint32_t CR2; // TIM Control Register 2
    uint32_t      RESERVED1; // Reserved
    __IO uint32_t DIER; // TIM DMA/Interrupt Enable Register
    __IO uint32_t SR; // TIM Status Register
    __IO uint32_t EGR; // TIM Event Generation Register
    uint32_t      RESERVED2; // Reserved
    uint32_t      RESERVED3; // Reserved
    uint32_t      RESERVED4; // Reserved
    __IO uint32_t CNT; // TIM Counter
    __IO uint32_t PSC; // TIM Prescaler
    __IO uint32_t ARR; // TIM  Auto Reload Register
}TIM6_7;

// Pointers to Specific TIM Peripherals
#define TIM6 ((TIM6_7 *) TIM6_BASE)
#define TIM7 ((TIM6_7 *) TIM7_BASE)

///////////////////////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////////////////////
void counterON(TIM6_7* TIM);
void setDelay(TIM6_7* TIM, uint32_t ms);
void resetFlag(TIM6_7* TIM);
void resetTIM(TIM6_7* TIM);
void setPrescaler(TIM6_7* TIM, uint32_t val);
void setArr(TIM6_7* TIM, uint32_t val);

// Top function: TIMdelay picks TIM6 used for delay and TIMwave picks TIM7 used to generate square wave
void genPWM(uint32_t freq, uint32_t dur, int pin, TIM6_7* TIMdelay, TIM6_7* TIMwave);

#endif