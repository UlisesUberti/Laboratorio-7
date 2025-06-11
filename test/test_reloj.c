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
- fijar la alarma y avanzar el reloj para que suene
- Fijar la alarma, desahibilitar y avanzar la hora para que el reloj no suene
- Hacer sonar la alarma y posponer
- Hacer sonar la alarma y cancelarla hasta el dia siguiente
-Ajustar la hora con valores invalidos y que los rechaze
*/

/* === Headers files inclusions ====================================================================================*/

#include "unity.h"
#include "clock.h"

/* === Macros definitions ==========================================================================================*/

// Defino la cantidad de pulsos por segundo
#define CLOCK_TICKS_PER_SECOND 5
#define TEST_ASSERT_TIME(Hours_Tens, Hours_Units, Minutes_Tens, Minutes_Units, Seconds_Tens, Seconds_Units,            \
                         current_time)                                                                                 \
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(Seconds_Units, current_time.bcd[0], "Diference in unit seconds");                  \
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(Seconds_Tens, current_time.bcd[1], "Diference in tens seconds");                   \
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(Minutes_Units, current_time.bcd[2], "Diference in unit minutes");                  \
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(Minutes_Tens, current_time.bcd[3], "Diference in tens minutes");                   \
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(Hours_Units, current_time.bcd[4], "Diference in unit hours");                      \
    TEST_ASSERT_EQUAL_UINT8_MESSAGE(Hours_Tens, current_time.bcd[5], "Diference in tens hours")

/* === Private data type declarations==============================================================================*/

clock_t clock;

/* === Private function declarations ===============================================================================*/

void Simulate_Seconds(clock_t clock, uint8_t seconds);
void Simulate_Minutes(clock_t clock, uint8_t minutes);
void Simule_Hours(clock_t clock, uint8_t hours);
// Declaro una funcion que se ejecutara antes de todas las pruebas | Setup es detectada por Unity
void setUp(void) {
    clock = Clock_Create(CLOCK_TICKS_PER_SECOND);
}

/* === Private variable definitions================================================================================*/

/* === Public variable definitions =================================================================================*/

/* === Private function definitions ================================================================================*/

void Simulate_Seconds(clock_t clock, uint8_t seconds) {
    // Bucle con duracion que depende de la cantida de segundos a pasar
    for (uint8_t i = 0; i < CLOCK_TICKS_PER_SECOND * seconds; i++) {
        Clock_New_Tick(clock);
    }
}
void Simulate_Minutes(clock_t clock, uint8_t minutes) {
    for (uint8_t i = 0; i < CLOCK_TICKS_PER_SECOND * minutes * 60; i++) {
        Clock_New_Tick(clock);
    }
}

// Si inicalizo el reloj pero esta en hora invalida lo pongo en 00:00
void test_set_up_with_invalid_time(void) {
    // time_t es un puntero a una estructura que permite recibir la hora
    clock_time_t current_time = {
        .bcd = {0, 0, 0, 0, 0, 0},
    };
    // Esta prueba testea a traves de una funcion QUE el reloj esta en hora invalida
    clock_t clock = Clock_Create(CLOCK_TICKS_PER_SECOND);
    // Si llamo a la funcion que determina que el si el tiempo es valido espero un false
    // TEST_ASSERT_FALSE(Clock_Time_Valid(clock));
    // Necesito una funcion para obtener la hora del reloj
    TEST_ASSERT_TRUE(Clock_Get_Time(clock, &current_time));
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
    // clock_t clock = Clock_Create(CLOCK_TICKS_PER_SECOND);
    // Tets True ya que le paso una hora valida entonces significa que set time me devolvio un true
    TEST_ASSERT_TRUE(Clock_Set_Time(clock, &new_time));
    // Ahora verifico que el horario es valido con la funcion get_time
    TEST_ASSERT_TRUE(Clock_Get_Time(clock, &new_time));
    // Ahora cuando compare new_time y current_time deben ser vectores iguales
    TEST_ASSERT_EQUAL_UINT8_ARRAY(new_time.bcd, current_time.bcd, 6);
}

// Ajusto la hora del reloj a un horario invalido y verifico que la rechaza
void test_set_up_and_adjust_with_invalid_time(void) {
    // El objeto se crea en el setup entonces desestimo
    //  Seteo un horario invalido
    clock_time_t invalid_time = {.time = {.hours = {9, 9}, .minutes = {0, 0}, .seconds = {0, 0}}};
    // Seteo un horario valido al incializar
    clock_time_t current_time = {0};
    // Verifico que me retorna una hora invalida
    TEST_ASSERT_FALSE(Clock_Get_Time(clock, &invalid_time));
}

// Despues de n ciclos de reloj la hora avanza un segundo
void test_clock_avance_one_second(void) {
    // inicializo en 00:00:00
    clock_time_t current_time = {0};
    Clock_Set_Time(clock, &(clock_time_t){.time = {.hours = {0, 0}, .minutes = {0, 0}, .seconds = {0, 0}}});
    // Funcion para simular que paso un segundo
    Simulate_Seconds(clock, 1);
    // Pido la hora actual
    Clock_Get_Time(clock, &current_time);
    // Comparo la hora actual con la misma hora mas un segundo
    // TEST_ASSERT_EQUAL_MEMORY(Expect_Value.bcd, current_time.bcd, sizeof(clock_time_t));}
    TEST_ASSERT_TIME(0, 0, 0, 0, 0, 1, current_time);

    // Testeo de 9s a 10s
    // Seteo el tiempo en 00:00:09
    Clock_Set_Time(clock, &(clock_time_t){.time = {.hours = {0, 0}, .minutes = {0, 0}, .seconds = {9, 0}}});
    // Hago que pase 1 seg
    Simulate_Seconds(clock, 1);
    // Actualizo la hora del reloj
    Clock_Get_Time(clock, &current_time);
    // Testeo que el valor esperado sea 00:00:10
    TEST_ASSERT_TIME(0, 0, 0, 0, 1, 0, current_time);

    // Testeo que pasa de 00:00:59 a 00:01:00
    //   Seteo en 00:00:59
    Clock_Set_Time(clock, &(clock_time_t){.time = {.hours = {0, 0}, .minutes = {0, 0}, .seconds = {9, 5}}});
    // Hago pasar 1 seg
    Simulate_Seconds(clock, 1);
    // Actualizo la hora del reloj
    Clock_Get_Time(clock, &current_time);
    // testeo el valor esperado 00:01:00
    TEST_ASSERT_TIME(0, 0, 0, 1, 0, 0, current_time);

    // Testeo de 23:59:59 a 00:00:00
    //    Seteo en 23:59:59
    Clock_Set_Time(clock, &(clock_time_t){.time = {.hours = {3, 2}, .minutes = {9, 5}, .seconds = {9, 5}}});
    // Hago pasar 1 seg
    Simulate_Seconds(clock, 1);
    // Actualizo la hora del reloj
    Clock_Get_Time(clock, &current_time);
    // testeo el valor esperado 00:01:00
    TEST_ASSERT_TIME(0, 0, 0, 0, 0, 0, current_time);
}

// Fijar hora en la alarma y consultarla
void test_set_up_alarm_and_activate(void) {
    // Seteo un horario para la alarma
    clock_time_t alarm_time = {.time = {.hours = {6, 0}, .minutes = {3, 0}, .seconds = {0, 0}}};
    // verifico que se establecio un horario para la alarma y se activo
    TEST_ASSERT_TRUE(Clock_Set_Time_Alarm(clock, &alarm_time));
    // Verifico que el horario de la alarma es igual al ingresado
    // TEST_ASSERT_EQUAL_UINT8_ARRAY(alarm_time.bcd,, 6);
}

// fijar la alarma y avanzar el reloj para que suene
void test_alarm_working(void) {
    // Seteo la alarma en un horario
    clock_time_t alarm_time = {.time = {.hours = {6, 0}, .minutes = {0, 3}, .seconds = {0, 0}}};
    Clock_Set_Time_Alarm(clock, &alarm_time);
    // Seteo el reloj un segundo antes de ese horario
    clock_time_t current_time = {.time = {.hours = {6, 0}, .minutes = {9, 2}, .seconds = {9, 5}}};
    Clock_Set_Time(clock, &current_time);
    // Funcion que compare si suena cuando avanza un segundo
    Simulate_Seconds(clock, 1);
    Clock_Get_Time(clock, &current_time);
    TEST_ASSERT_TRUE(Clock_Alarm_Working(clock));
}

/* === Public function implementation ==============================================================================*/

/* === End of documentation========================================================================================*/
