

#include "board.h"

#include "pin_mux.h"
#include "clock_config.h"
//#include "fsl_gpio.h"
//#include "fsl_iomuxc.h"
#include "fsl_debug_console.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "fsl_i2c_freertos.h"
#include "i2c_handler.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Variables
 ******************************************************************************/

static SemaphoreHandle_t s_OkToUseI2C = NULL;
static i2c_rtos_handle_t  rtos_handle = {0};

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define EXAMPLE_I2C_MASTER_IRQ FLEXCOMM2_IRQn

#define EXAMPLE_I2C_MASTER_BASE (I2C2_BASE)

#define I2C_MASTER_CLOCK_FREQUENCY (12000000)

#define EXAMPLE_I2C_MASTER ((I2C_Type *)EXAMPLE_I2C_MASTER_BASE)

#define I2C_BAUDRATE (400000) /* 100K */
#define I2C_DATA_LENGTH (32)  /* MAX is 256 */


/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

int i2c_handler_initialize(void)
{
	s_OkToUseI2C = xSemaphoreCreateBinary();
	if (s_OkToUseI2C == NULL) {
		PRINTF("Failed to create i2c semaphore\n");
		return -1;
	}
	xSemaphoreGive(s_OkToUseI2C);
	
    /* attach 12 MHz clock to FLEXCOMM2 (I2C master) */
    CLOCK_AttachClk(kFRO12M_to_FLEXCOMM2);

    i2c_master_config_t config;
    uint32_t sourceClock;

    NVIC_SetPriority(EXAMPLE_I2C_MASTER_IRQ, 3);
    EnableIRQ(EXAMPLE_I2C_MASTER_IRQ);

    /*
     * masterConfig.baudRate_Bps = 100000U;
     * masterConfig.enableStopHold = false;
     * masterConfig.glitchFilterWidth = 0U;
     * masterConfig.enableMaster = true;
     */
    I2C_MasterGetDefaultConfig(&config);
    config.baudRate_Bps = I2C_BAUDRATE;
    sourceClock = I2C_MASTER_CLOCK_FREQUENCY;

    status_t status = I2C_RTOS_Init(&rtos_handle, EXAMPLE_I2C_MASTER, &config, sourceClock);
    if (status != kStatus_Success)
    {
        PRINTF("I2C master: error during init, %d", status);
			return -2;
    }
		return 0;
}

void i2c_handler_take(void)
{
	//xSemaphoreTake(s_OkToUseI2C, portMAX_DELAY);
}
void i2c_handler_give(void)
{
	//xSemaphoreGive(s_OkToUseI2C);
}

status_t i2c_handler_transfer(i2c_master_transfer_t *transfer)
{
	return I2C_RTOS_Transfer(&rtos_handle, transfer);
}

status_t i2c_handler_read(uint16_t slaveAddress7bit, void* data, size_t dataSize)
{
	i2c_master_transfer_t tr = {0};
	tr.slaveAddress = slaveAddress7bit;
	tr.direction = kI2C_Read;
	//tr.subaddress = subaddress;
	//tr.subaddressSize = 1;
	tr.data = data;
	tr.dataSize = dataSize;
	return I2C_RTOS_Transfer(&rtos_handle, &tr);
}

status_t i2c_handler_write(uint16_t slaveAddress7bit, void* data, size_t dataSize)
{
	i2c_master_transfer_t tr = {0};
	tr.slaveAddress = slaveAddress7bit;
	tr.direction = kI2C_Write;
	//tr.subaddress = subaddress;
	//tr.subaddressSize = 1;
	tr.data = data;
	tr.dataSize = dataSize;
	return I2C_RTOS_Transfer(&rtos_handle, &tr);
}

