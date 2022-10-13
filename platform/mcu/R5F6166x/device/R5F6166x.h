//
// Created by mark on 10/12/22.
//

#ifndef R5F6166x_H
#define R5F6166x_H

// Default clocks:
// System Clock = 1/2 * EXTAL (16Mhz) = 8Mhz
// Peripheral Clock = 1/2 * EXTAL (16Mhz) = 8Mhz
// External Bus Clock = 1/2 * EXTAL (16Mhz) = 8Mhz

// Helper for masking interrupts
__inline__ void set_imask_ccr(unsigned char mask)
{
    if (mask == 1)
    {
        asm("orc.b #0x80, ccr");
    }
    else
    {
        asm("andc.b #0x7f, ccr");
    }
}

#endif  // R5F6166x_H
