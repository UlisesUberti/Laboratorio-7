/*********************************************************************************************************************
Copyright (c) 2025, Uberti,Ulises Leandro <ubertileandro0@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*********************************************************************************************************************/

/** @file test_reloj.c
 * @brief Código fuente de test_reloj.c
 * @author Uberti, Ulises Leandro
 * */

/*
- La librería deberá mantener la hora actual, con precisión de segundos, a partir de la llamada
a una función que se produce una cierta cantidad de veces por segundo.
• Lalibrería deberá proporcionar una función para ajustar la hora actual.
• La librería deberá permitir la configuración, una vez al inicio, de la cantidad de veces por
segundo que se llamará a la función para mantener la hora actualizada.
• Lalibrería deberá informar que la hora actual es inválida hasta que se llama a la función para
ajustar la hora por primera vez.
• Lalibrería deberá proporcionar una función para fijar la hora de la alarma.
• Lalibrería deberá proporcionar una función para consultar la hora fijada para la alarma.
• Lalibrería deberá proporcionar una función para habilitar y deshabilitar la alarma.
• Lalibrería deberá proporcionar una función para consultar si la alarma está, o no, habilitada.
• La librería deberá generar un evento cuando la alarma esté habilitada y además hora actual
coincida con la hora de la alarma.
• La librería deberá proporcionar una función para posponer la alarma una cantidad arbitraria
de minutos.
• La librería deberá manejar todas las horas como un arreglo de bytes en formato BCD sin
compactar, con la decena de horas en la primera posición y la unidad de los segundos en la
última posición del vector
*/

/* === Headers files inclusions ====================================================================================*/
#include "clock.h"
#include <stddef.h>
#include <string.h>
/* === Macros definitions ==========================================================================================*/

/* === Private data type declarations==============================================================================*/

/* === Private function declarations ===============================================================================*/

/* === Private variable definitions================================================================================*/

/* === Public variable definitions =================================================================================*/

/* === Private function definitions ================================================================================*/

/**
 * @brief Funcion que crea el objeto Reloj
 *
 * @return clock_t puntero al objeto
 */
clock_t Clock_Create() {
    return NULL;
}

/**
 * @brief Funcion que retorna si la hora es invalida o valida
 *
 * @param clock
 * @param result
 * @return true
 * @return false
 */
bool Clock_Get_Time(clock_t clock, clock_time_t * result) {
    (void)clock;
    (void)result; // significa que no quiero usar la variable y la estoy usando
    return false; // retorna una hora invalida
}

bool Clock_Set_Time(clock_t clock, clock_time_t * newtime) {
    (void)clock;
    (void)newtime;
    return true;
}
/* === Public function implementation ==============================================================================*/

/* === End of documentation========================================================================================*/
