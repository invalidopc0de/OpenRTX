/***************************************************************************
 *   Copyright (C) 2020 - 2022 by Mark Saunders                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, see <http://www.gnu.org/licenses/>   *
 ***************************************************************************/

#include <interfaces/delays.h>
#include <iodefine.h>
#include <stdint.h>

#include "R5F6166x.h"

#define MICROSECOND_DIVIDER 8
#define MILLISECOND_DIVIDER 8000

static volatile uint32_t timer_counter;

void INT_TGI0A_TPU0(void)
{
    timer_counter++;
}

/**
 * Implementation of the delay functions for R5F6166x MCU.
 */

void delayUs(unsigned int useconds)
{
}

void delayMs(unsigned int mseconds)
{
    // Start timer
    timer_counter = 0;

    // Reset module
    MSTP.CRA.BIT._TPUL = 0;
    // Set countup source
    TPU0.TCR.BIT.TPSC = 0;
    // Set clear criteria
    TPU0.TCR.BIT.CCLR = 1;

    // Set value
    TPU0.TGRA = MILLISECOND_DIVIDER;

    set_imask_ccr(0);
    TPU0.TIER.BIT.TGIEA = 1;
    set_imask_ccr(1);

    TPU.TSTR.BIT.CST0 = 1;

    // Wait until time has elapsed
    while (timer_counter < mseconds)
    {
    };

    // Stop timer
    TPU.TSTR.BIT.CST0 = 0;
}