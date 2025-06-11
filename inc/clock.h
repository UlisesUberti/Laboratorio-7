/*********************************************************************************************************************
Copyright (c) 2025, Uberti,Ulises Leandro <ubertileandro0@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/

#ifndef CLOCK_H_
#define CLOCK_H_

/** @file clock.h
 ** @brief Codigo fuente de clock.h
 @author Uberti, Ulises Leandro
 **/

/* === Headers files inclusions ==================================================================================== */
#include <stdint.h>
#include <stdbool.h>

/* === Header for C++ compatibility ================================================================================ */

#ifdef __cplusplus
extern "C" {
#endif

/* === Public macros definitions =================================================================================== */

/* === Public data type declarations =============================================================================== */

typedef union {
    struct {
        uint8_t seconds[2];
        uint8_t minutes[2];
        uint8_t hours[2];
    } time;
    uint8_t bcd[6];
} clock_time_t;

typedef struct clock_s * clock_t;

/* === Public variable declarations ================================================================================ */

/* === Public function declarations ================================================================================ */

clock_t Clock_Create(uint16_t Ticks_Per_Second);

bool Clock_Get_Time(clock_t clock, clock_time_t * result);

void test_set_up_and_adjust_with_valid_time(void);

bool Clock_Set_Time(clock_t clock, clock_time_t * new_time);

void Clock_New_Tick(clock_t clock);

bool Clock_Set_Time_Alarm(clock_t clock, clock_time_t * alarm_time);

bool Clock_Alarm_Working(clock_t clock);
/* === End of conditional blocks =================================================================================== */

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_H_ */
