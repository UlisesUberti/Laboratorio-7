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
• La librería deberá proporcionar una función para ajustar la hora actual.
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
#include "unity.h"
#include "clock.h"
/* === Macros definitions ==========================================================================================*/
// Defino la cantidad de pulsos por segundo
#define CLOCK_TICKS_PER_SECOND 5
/* === Private data type declarations==============================================================================*/

/* === Private function declarations ===============================================================================*/
void Simulate_Seconds(clock_t clock, uint8_t seconds);
/* === Private variable definitions================================================================================*/

/* === Public variable definitions =================================================================================*/

/* === Private function definitions ================================================================================*/

void Simulate_Seconds(clock_t clock, uint8_t seconds) {
    // Bucle con duracion que depende de la cantida de segundos a pasar
    for (uint8_t i = 0; i < CLOCK_TICKS_PER_SECOND * seconds; i++) {
        Clock_New_Tick(clock);
    }
}
// Si inicalizo el reloj pero esta en hora invalida lo pongo en 00:00

void test_set_up_with_invalid_time(void) {
    // time_t es un puntero a una estructura que permite recibir la hora
    clock_time_t current_time = {
        .bcd = {1, 2, 3, 4, 5, 6},
    };
    // Esta prueba testea a traves de una funcion QUE el reloj esta en hora invalida
    clock_t clock = Clock_Create(CLOCK_TICKS_PER_SECOND);
    // Si llamo a la funcion que determina que el si el tiempo es valido espero un false
    // TEST_ASSERT_FALSE(Clock_Time_Valid(clock));
    // Necesito una funcion para obtener la hora del reloj
    TEST_ASSERT_FALSE(Clock_Get_Time(clock, &current_time));
    // Necesito comparar la hora del reloj con la hora esperada
    TEST_ASSERT_EACH_EQUAL_UINT8(0, current_time.bcd, 6);
}

// Ajusto la hora del reloj a un horario valido y verifico que es valida
void test_set_up_and_adjust_with_valid_time(void) {
    // Seteo un nuevo horario
    clock_time_t new_time = {.time = {
                                 .seconds = {0, 0},
                                 .minutes = {0, 0},
                                 .hours = {0, 0},
                             }};

    clock_time_t current_time = {0};
    // Creo el objeto nuevamente
    clock_t clock = Clock_Create(CLOCK_TICKS_PER_SECOND);
    // Tets True ya que le paso una hora valida entonces significa que set time me devolvio un true
    TEST_ASSERT_TRUE(Clock_Set_Time(clock, &new_time));
    // Ahora verifico que el horario es valido con la funcion get_time
    TEST_ASSERT_TRUE(Clock_Get_Time(clock, &new_time));
    // Ahora cuando compare new_time y current_time deben ser vectores iguales
    TEST_ASSERT_EQUAL_UINT8_ARRAY(new_time.bcd, current_time.bcd, 6);
}

// Despues de n ciclos de reloj la hora avanza un segundo
void test_clock_avance_one_second(void) {
    clock_time_t current_time = {0};
    static const clock_time_t Expect_Value = {.time = {
                                                  .hours = {0, 0},
                                                  .minutes = {0, 0},
                                                  .seconds = {1, 0},
                                              }};
    clock_t clock = Clock_Create(CLOCK_TICKS_PER_SECOND);
    // Seteo en un hora valida
    Clock_Set_Time(clock, &(clock_time_t){0});
    // Funcion para simular que paso un segundo
    Simulate_Seconds(clock, 1);
    // Pido la hora actual
    Clock_Get_Time(clock, &current_time);
    // Comparo la hora actual con la misma hora mas un segundo
    // E
    TEST_ASSERT_EQUAL_MEMORY(Expect_Value.bcd, current_time.bcd, sizeof(clock_time_t));
}
/* === Public function implementation ==============================================================================*/

/* === End of documentation========================================================================================*/
