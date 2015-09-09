#ifndef LOABRO_HAL_EXT
#define LOBARO_HAL_EXT

//C NewLib
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

//StdPeriph Driver for STM32F103RC
#include "stm32f10x.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
//add more headers if needed!

//ZWIR4512 6LoWPAN Stack
#define _ZWIR4512AC2_ //Zwir4512 HW Version: AC2

#define IPV6FRMT2 "[%02x%02x:%02x%02x:%02x%02x:%02x%02x:" \
                 "%02x%02x:%02x%02x:%02x%02x:%02x%02x]"

#include "ZWIR45xx-6LoWPAN.h"
#include "ZWIR45xx-UART1.h"
#include "ZWIR45xx-UART2.h"
#include "ZWIR451x-GPIO.h"
#include "ZWIR45xx-SPI1.h"

#endif
