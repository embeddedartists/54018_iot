
#include "fsl_common.h"
#include "fsl_iocon.h"
#include "pin_mux.h"
#include "expansion.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define IOCON_PIO_DIGITAL_EN        0x0100u   /*!< Enables digital function */
#define IOCON_PIO_FUNC0               0x00u   /*!< Selects pin function 0 */
#define IOCON_PIO_FUNC1               0x01u   /*!< Selects pin function 1 */
#define IOCON_PIO_FUNC2               0x02u   /*!< Selects pin function 2 */
#define IOCON_PIO_FUNC3               0x03u   /*!< Selects pin function 3 */
#define IOCON_PIO_FUNC4               0x04u   /*!< Selects pin function 4 */
#define IOCON_PIO_INPFILT_OFF       0x0200u   /*!< Input filter disabled */
#define IOCON_PIO_INV_DI              0x00u   /*!< Input function is not inverted */
#define IOCON_PIO_MODE_INACT          0x00u   /*!< No addition pin function */
#define IOCON_PIO_OPENDRAIN_DI        0x00u   /*!< Open drain is disabled */
#define IOCON_PIO_SLEW_STANDARD       0x00u   /*!< Standard mode, output slew rate control is enabled */
#define PIN29_IDX                       29u   /*!< Pin number for pin 29 in a port 0 */
#define PIN30_IDX                       30u   /*!< Pin number for pin 30 in a port 0 */
#define PORT0_IDX                        0u   /*!< Port index */


/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Variables
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

void expansion_initPins(void) {
#if EXPANSION_USE_CLICK_1 || EXPANSION_USE_CLICK_2 || EXPANSION_USE_ARDUINO
  CLOCK_EnableClock(kCLOCK_Iocon);                           /* Enables the clock for the IOCON block. 0 = Disable; 1 = Enable.: 0x01u */

  const uint32_t std_func0 = (
    IOCON_PIO_FUNC0 |                                        /* Pin is configured as FUNC0 */
    IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  const uint32_t std_func1 = (
    IOCON_PIO_FUNC1 |                                        /* Pin is configured as FUNC0 */
    IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  const uint32_t std_func2 = (
    IOCON_PIO_FUNC2 |                                        /* Pin is configured as FUNC2 */
    IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );
  const uint32_t std_func4 = (
    IOCON_PIO_FUNC4 |                                        /* Pin is configured as FUNC4 */
    IOCON_PIO_MODE_INACT |                                   /* No addition pin function */
    IOCON_PIO_INV_DI |                                       /* Input function is not inverted */
    IOCON_PIO_DIGITAL_EN |                                   /* Enables digital function */
    IOCON_PIO_INPFILT_OFF |                                  /* Input filter disabled */
    IOCON_PIO_SLEW_STANDARD |                                /* Standard mode, output slew rate control is enabled */
    IOCON_PIO_OPENDRAIN_DI                                   /* Open drain is disabled */
  );

  /* Shared pins - must have same function on all expansions */
  IOCON_PinMuxSet(IOCON, 3, 20, std_func1); // SPI CLK
  IOCON_PinMuxSet(IOCON, 3, 21, std_func1); // SPI MOSI
  IOCON_PinMuxSet(IOCON, 3, 22, std_func1); // SPI MISO
  IOCON_PinMuxSet(IOCON, 3, 26, std_func0); // UART RXD
  IOCON_PinMuxSet(IOCON, 3, 27, std_func0); // UART TXD
  //IOCON_PinMuxSet(IOCON, 3, 24, std_func0); // Used by I2C
  //IOCON_PinMuxSet(IOCON, 3, 23, std_func0); // Used by I2C

#if EXPANSION_USE_CLICK_1 || EXPANSION_USE_ARDUINO
  IOCON_PinMuxSet(IOCON, 0, 16, std_func0);
  IOCON_PinMuxSet(IOCON, 1,  0, std_func0);
  IOCON_PinMuxSet(IOCON, 3, 30, std_func0);
  IOCON_PinMuxSet(IOCON, 4,  5, std_func0);
#endif

#if EXPANSION_USE_CLICK_1
#ifdef REV_PA3
  IOCON_PinMuxSet(IOCON, 3, 19, std_func0);
#else
  IOCON_PinMuxSet(IOCON, 1,  4, std_func0);
#endif
#endif

#if EXPANSION_USE_CLICK_2 || EXPANSION_USE_ARDUINO
  IOCON_PinMuxSet(IOCON, 0, 31, std_func0);
  IOCON_PinMuxSet(IOCON, 2,  0, std_func0);
  IOCON_PinMuxSet(IOCON, 3, 28, std_func0);
#endif

#if EXPANSION_USE_CLICK_2
  IOCON_PinMuxSet(IOCON, 4,  6, std_func0);
#ifdef REV_PA3
  IOCON_PinMuxSet(IOCON, 3, 18, std_func0);
#else
  IOCON_PinMuxSet(IOCON, 1,  5, std_func0);
#endif
#endif

#if EXPANSION_USE_ARDUINO
#ifndef REV_PA3
  IOCON_PinMuxSet(IOCON, 3, 18, std_func0);
  IOCON_PinMuxSet(IOCON, 3, 19, std_func0);
#endif
  IOCON_PinMuxSet(IOCON, 3, 11, std_func0);
  IOCON_PinMuxSet(IOCON, 3, 12, std_func0);
  IOCON_PinMuxSet(IOCON, 3,  4, std_func0);
  IOCON_PinMuxSet(IOCON, 1,  1, std_func0);
  IOCON_PinMuxSet(IOCON, 2,  1, std_func0);
  IOCON_PinMuxSet(IOCON, 3, 29, std_func0);
  IOCON_PinMuxSet(IOCON, 3, 19, std_func0);
  IOCON_PinMuxSet(IOCON, 3, 18, std_func0);
  IOCON_PinMuxSet(IOCON, 4,  1, std_func0);
  IOCON_PinMuxSet(IOCON, 4,  3, std_func0);
  IOCON_PinMuxSet(IOCON, 4,  2, std_func0);
  IOCON_PinMuxSet(IOCON, 2,  2, std_func0);
  IOCON_PinMuxSet(IOCON, 3, 14, std_func0);
  IOCON_PinMuxSet(IOCON, 3, 10, std_func0);
  IOCON_PinMuxSet(IOCON, 3,  2, std_func0);
  IOCON_PinMuxSet(IOCON, 1,  3, std_func0);
  IOCON_PinMuxSet(IOCON, 1,  2, std_func0);
#endif

#endif /* #if EXPANSION_USE_CLICK_1 || EXPANSION_USE_CLICK_2 || EXPANSION_USE_ARDUINO */
}

