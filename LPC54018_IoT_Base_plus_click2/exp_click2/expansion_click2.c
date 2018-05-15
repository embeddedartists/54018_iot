
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
#include "expansion_click2.h"
#include "data_store.h"

#include "BME280_Driver.h"
#include "BME280_Defs.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define F2I_I(__f)  (((int)((__f)*100))/100)
#define F2I_F(__f)  (((int)((__f)*1000))%10)
#define F2I(__f)  F2I_I(__f),F2I_F(__f)

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

static void BME280_INIT()
{
    BME280_SetStandbyTime(BME280_STANDBY_TIME_1_MS);                              // Standby time 1ms
    BME280_SetFilterCoefficient(BME280_FILTER_COEFF_16);                          // IIR Filter coefficient 16
    BME280_SetOversamplingPressure(BME280_OVERSAMP_16X);                          // Pressure x16 oversampling
    BME280_SetOversamplingTemperature(BME280_OVERSAMP_2X);                        // Temperature x2 oversampling
    BME280_SetOversamplingHumidity(BME280_OVERSAMP_1X);                           // Humidity x1 oversampling
    BME280_SetOversamplingMode(BME280_NORMAL_MODE);
}

static int weather_prepare(void)
{
    char id = BME280_GetID();
    if (id != BME280_CHIP_ID) {
        PRINTF("Wrong ID from BME280. Expected 0x%x but got 0x%x\n", BME280_CHIP_ID, id);
        return -1;
    }

    delay(200);
    BME280_ReadCalibrationParams();                                               //Read calibration parameters
    BME280_SetOversamplingPressure(BME280_OVERSAMP_1X);
    BME280_SetOversamplingTemperature(BME280_OVERSAMP_1X);
    BME280_SetOversamplingHumidity(BME280_OVERSAMP_1X);
    BME280_SetOversamplingMode(BME280_FORCED_MODE);

    while(BME280_IsMeasuring());
    BME280_ReadMeasurements();

    BME280_INIT();
    return 0;
}

static void click2_task_entry(void* args)
{
	if (weather_prepare() == 0) {
	    while (true) {
			while(BME280_IsMeasuring());
			BME280_ReadMeasurements();

			float tmp_t = BME280_GetTemperature();
			float tmp_p = BME280_GetPressure();
			float tmp_h = BME280_GetHumidity();
			PRINTF("Temp: %d.%02dC (%d), Pressure: %d.%02dpA, Humidity: %d.%02dRf\n", F2I(tmp_t), (int)(tmp_t*100), F2I(tmp_p), F2I(tmp_h));

			// Push changes so that other tasks can use it
			if (!ds_write_weather_data(tmp_t, tmp_p, tmp_h)) {
				PRINTF("Failed to update weather data in shared storage\n");
			}

			BME280_INIT();
			delay(5000);
	    }
	} else {
		PRINTF("Failed to initialize Weather Task!\n");
		vTaskDelete(NULL);
	}
}

int expansion_click2_prepare(void)
{
    TaskHandle_t xCreatedTask;

    if (xTaskCreate(click2_task_entry,                   /* pointer to the task */
                    "Click 2",                           /* task name for kernel awareness debugging */
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
