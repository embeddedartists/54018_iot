#ifndef _I2C_HANDLER_H_
#define _I2C_HANDLER_H_

#include "fsl_i2c.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @addtogroup pin_mux
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif

int i2c_handler_initialize(void);
void i2c_handler_take(void);

status_t i2c_handler_transfer(i2c_master_transfer_t *transfer);

status_t i2c_handler_read(uint16_t slaveAddress7bit, void* data, size_t dataSize);
status_t i2c_handler_write(uint16_t slaveAddress7bit, void* data, size_t dataSize);

void i2c_handler_give(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _I2C_HANDLER_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
