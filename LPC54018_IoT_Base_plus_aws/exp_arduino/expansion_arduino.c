
/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"
#include "semphr.h"
#include "event_groups.h"

/* SDK Included Files */
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "fsl_i2c_freertos.h"
#include "fsl_inputmux.h"
#include "fsl_pint.h"

#include "expansion.h"
#include "expansion_arduino.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

#define delay(__ms)  vTaskDelay((__ms) / portTICK_PERIOD_MS)

/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

static void arduino_task_entry(void* args)
{
    while (true) {
        delay(5000);
    }
}


int expansion_arduino_prepare(void)
{
    TaskHandle_t xCreatedTask;
    if (xTaskCreate(arduino_task_entry,                   /* pointer to the task */
                    "Arduino",                           /* task name for kernel awareness debugging */
                    EXPANSION_TASK_DEFAULT_STACK,        /* task stack size */
                    NULL,                                /* optional task startup argument */
                    EXPANSION_TASK_DEFAULT_PRIO,         /* initial priority */
                    &xCreatedTask                        /* optional task handle to create */
                    ) != pdPASS)
    {
        return -1;
    }
    return 0;
}

