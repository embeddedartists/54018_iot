/*
 * Copyright (c) 2017, NXP Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    main.cpp
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC54018.h"
#include "fsl_debug_console.h"
#include "FreeRTOS.h"
#include "task.h"

#include "TaskEPD.h"

#include "i2c_handler.h"

#include "fsl_reset.h"
#include "expansion.h"
#if EXPANSION_USE_CLICK_1
#  include "expansion_click1.h"
#endif
#if EXPANSION_USE_CLICK_2
#  include "expansion_click2.h"
#endif
#if EXPANSION_USE_ARDUINO
#  include "expansion_arduino.h"
#endif
#include "data_store.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

typedef int (*task_prepare)(void);
typedef struct {
	task_prepare prep;
	const char* descr;
} task_info;

typedef struct {
	int port1;
	int pin1;
	int port2;
	int pin2;
	const char* descr;
} pin_pair_t;

#define NUM_TASKS ((int)(sizeof(TASKS)/sizeof(TASKS[0])))
#define NUM_PIN_PAIRS ((int)(sizeof(PIN_PAIRS)/sizeof(PIN_PAIRS[0])))

#define delay(__ms)  vTaskDelay((__ms) / portTICK_PERIOD_MS)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

static int led_accel_task_prepare(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

static task_info TASKS[] = {
	{ led_accel_task_prepare,            "LED & Accel" },
	{ display_task_prepare,              "Display" },
#if EXPANSION_USE_CLICK_1
	{ expansion_click1_prepare,          "Click 1" },
#endif
#if EXPANSION_USE_CLICK_2
	{ expansion_click2_prepare,          "Click 2" },
#endif
#if EXPANSION_USE_ARDUINO
	{ expansion_arduino_prepare,         "Arduino" },
#endif
};


/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

void printGreeting(void)
{
		PRINTF("*******************************************************\r\n");
		PRINTF("*                                                     *\r\n");
		PRINTF("* LPC54018_IoT_Base                                   *\r\n");
		PRINTF("* (C) Embedded Artists AB 2018                        *\r\n");
		PRINTF("*                                                     *\r\n");
#if defined(REV_PA3)
		PRINTF("* For rev PA3 of IoT board                            *\r\n");
#endif
#if defined(REV_A)
		PRINTF("* For rev A of IoT board                              *\r\n");
#endif
		PRINTF("*******************************************************\r\n");
		PRINTF("\r\n");
		PRINTF("Version: 1.0, (build %s)\r\n", __DATE__ " @" __TIME__);

		uint32_t addr = (uint32_t)printGreeting;
	  if ((addr & 0xf0000000) == 0x10000000) {
			PRINTF("Running in Flash\r\n");
		} else {
			PRINTF("Running in RAM\r\n");
		}
		PRINTF("SystemCoreClock: %u MHz\r\n", SystemCoreClock/1000000);

		PRINTF("\r\n");
		DbgConsole_Flush();
}


void extra_pin_init(void)
{
    /* Define the init structure for the output LED pin*/
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput, 1,
    };
    GPIO_PortInit(GPIO, 0);
    GPIO_PortInit(GPIO, 1);
    GPIO_PortInit(GPIO, 3);

    GPIO_PinInit(GPIO, 0, 17, &led_config);
    GPIO_PinInit(GPIO, 0, 18, &led_config);
    GPIO_PinInit(GPIO, 0, 19, &led_config);

    led_config.pinDirection = kGPIO_DigitalOutput;
    led_config.outputLogic = 0;
    GPIO_PinInit(GPIO, 1, 20, &led_config); // ePaper D/C
    GPIO_PinInit(GPIO, 1, 21, &led_config); // ePaper CS
    //GPIO_PinInit(GPIO, 1, 22, &led_config); // ePaper Discharge & wifi SSEL
    GPIO_PinInit(GPIO, 1, 23, &led_config); // ePaper RES
    GPIO_PinInit(GPIO, 1, 24, &led_config); // ePaper BS1
    GPIO_PinInit(GPIO, 1, 25, &led_config); // ePaper PanelOn
    GPIO_PinInit(GPIO, 1, 28, &led_config);
    GPIO_PinInit(GPIO, 1, 29, &led_config);

    led_config.pinDirection = kGPIO_DigitalInput;
    GPIO_PinInit(GPIO, 1, 1, &led_config); // User Button
    GPIO_PinInit(GPIO, 0, 4, &led_config); // ISP0 Button
    GPIO_PinInit(GPIO, 0, 5, &led_config); // ISP1 Button
    GPIO_PinInit(GPIO, 0, 6, &led_config); // ISP2 Button

    //GPIO_PinInit(GPIO, 3, 23, &led_config);
    //GPIO_PinInit(GPIO, 3, 24, &led_config);

    led_config.pinDirection = kGPIO_DigitalInput;
    GPIO_PinInit(GPIO, 1, 30, &led_config); // ePaper BUSY

    led_config.pinDirection = kGPIO_DigitalOutput;
    led_config.outputLogic = 1;
    GPIO_PinInit(GPIO, 0, 17, &led_config); // RGB RED
    GPIO_PinInit(GPIO, 0, 18, &led_config); // RGB GREEN
    GPIO_PinInit(GPIO, 0, 19, &led_config); // RGB BLUE
    GPIO_PinInit(GPIO, 3,  3, &led_config); // LED2 (RED)
    GPIO_PinInit(GPIO, 3, 14, &led_config); // LED1 (RED)
}

static void led_accel_task_entry(void* args)
{
	uint8_t tmp = 0;
	int mode = 0;
	TickType_t ttTarget;
	bool buttonPressed = false;
	bool tmpPressed;

	PRINTF("Checking accelerometer...\n");
	if (i2c_handler_read(0x1D, &tmp, 1) != kStatus_Success) {
		PRINTF("Accelerometer: FAILED - not detected!\n");
	} else {
		PRINTF("Accelerometer: PASSED\n");
	}

	PRINTF("\nType to get the characters echoed:\n");

	ttTarget = xTaskGetTickCount();
	while(true) {
		char c = '\0';
		TickType_t ttNow = xTaskGetTickCount();
		if (ttNow >= ttTarget) {
			switch (mode) {
				case 0:
					GPIO_PinWrite(GPIO, 3, 3, 0);  // LED2 (RED)
					GPIO_PinWrite(GPIO, 3, 14, 1); // LED1 (RED)
					break;
				case 1:
					GPIO_PinWrite(GPIO, 3, 3, 1);  // LED2 (RED)
					GPIO_PinWrite(GPIO, 3, 14, 0); // LED1 (RED)
					break;
			}
			mode = (mode + 1) % 2;
			ttTarget = ttNow + 100;
		}

		// User Button
		tmpPressed = GPIO_PinRead(GPIO, 1, 1) == 0;
		if (tmpPressed != buttonPressed) {
			ds_write_button(tmpPressed);
			buttonPressed = tmpPressed;
		}

		// SW3 - ISP1 Button controlls RGB RED
		GPIO_PinWrite(GPIO, 0, 17, GPIO_PinRead(GPIO, 0, 5) & 1);

		// SW4 - ISP0 Button controlls RGB GREEN
		GPIO_PinWrite(GPIO, 0, 19, GPIO_PinRead(GPIO, 0, 6) & 1);

		// SW1 - ISP0 Button controlls RGB BLUE
		GPIO_PinWrite(GPIO, 0, 18, GPIO_PinRead(GPIO, 0, 4) & 1);

		if (DbgConsole_TryGetchar(&c) == kStatus_Success) {
			PRINTF("%c", c);
		}
		delay(50);
	}
}

static int led_accel_task_prepare(void)
{
	TaskHandle_t xCreatedTask;
	if (xTaskCreate(led_accel_task_entry,            /* pointer to the task */
					"led_accel",                     /* task name for kernel awareness debugging */
					EXPANSION_TASK_DEFAULT_STACK,    /* task stack size */
					NULL,                            /* optional task startup argument */
					EXPANSION_TASK_DEFAULT_PRIO,     /* initial priority */
					&xCreatedTask                    /* optional task handle to create */
					) != pdPASS)
	{
		return -1;
	}
	return 0;
}

/*
 * @brief   Application entry point.
 */
int main(void) {

	int error=0, idx=0;

    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    expansion_initPins();
	SystemCoreClockUpdate();

  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

	printGreeting();

	do {
		extra_pin_init();

		error = i2c_handler_initialize();
		if (error != 0) {
			break;
		}

		if (!ds_initialize("Powered by Amazon", false)) {
	        PRINTF("Failed to initialize storage for shared variables, stopping demo.\n");
	        break;
		}

		for (idx = 0; idx < NUM_TASKS; idx++) {
			PRINTF("Preparing %s ...\n", TASKS[idx].descr);
			error = TASKS[idx].prep();
			if (error != 0) {
				PRINTF("Failed to prepare for %s task, error=%d, aborting!\n", TASKS[idx].descr, error);
				break;
			}
		}
		if (error != 0) {
			PRINTF("OOPS! OOPS! OOPS!\r\n");
			break;
		}

		PRINTF("\nPreparation completed. Starting RTOS!\n");
		vTaskStartScheduler();

	} while (0);

  /* Will not get here unless a task calls vTaskEndScheduler ()*/
  return 0;
}

