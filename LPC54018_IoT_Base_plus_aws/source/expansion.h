#ifndef _EXPANSION_H_
#define _EXPANSION_H_


/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define EXPANSION_USE_CLICK_1   0
#define EXPANSION_USE_CLICK_2   0
#define EXPANSION_USE_ARDUINO   0

#define EXPANSION_TASK_DEFAULT_PRIO      3
#define EXPANSION_TASK_DEFAULT_STACK   512 /* Actual stack is this size x4 */

/* There is a pin change for the click module's INT pin between rev PA3 and
 * rev A of the IoT Mini Prototype Board. Select one of the two defines below
 * depending on which revision is being used.
 */
#define REV_PA3
//#define REV_A

#if !defined(REV_PA3) && !defined(REV_A)
  #error Must define either REV_PA3 or REV_A
#endif
#if defined(REV_PA3) && defined(REV_A)
  #error Must define either REV_PA3 or REV_A not both
#endif
#if EXPANSION_USE_ARDUINO==1 && (EXPANSION_USE_CLICK_1==1 || EXPANSION_USE_CLICK_2==1)
  #error Cannot use both ARDUINO and CLICK module pinning at the same time
#endif

/*******************************************************************************
 * API
 ******************************************************************************/


void expansion_initPins(void);


#endif /* _EXPANSION_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
