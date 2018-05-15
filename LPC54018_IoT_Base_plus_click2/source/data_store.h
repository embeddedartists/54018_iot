#ifndef _DATA_STORE_H_
#define _DATA_STORE_H_

#include "FreeRTOS.h"
#include "event_groups.h"
#include "semphr.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define DS_MAX_MSG_LEN  50

typedef struct
{
	char msg[DS_MAX_MSG_LEN+1];
	bool button_pressed;
	float temperature;
	float pressure;
	float humidity;
} data_store_t;

#define DS_MSG_CHANGED      (1<<0)
#define DS_BUTTON_CHANGED   (1<<1)
#define DS_WEATHER_CHANGED  (1<<2)

/*******************************************************************************
 * API
 ******************************************************************************/


#if defined(__cplusplus)
extern "C" {
#endif

bool ds_initialize(const char* msg, bool button_pressed, float temperature, float pressure, float humidity);

/* Copies the shared data into the provided argument */
bool ds_read(data_store_t* data);

/* Updates the shared data */
bool ds_write_message(const char* msg);
bool ds_write_message_chars(const char* msg, int start_offset, int end_offset);
bool ds_write_button(bool pressed);
bool ds_write_weather_data(float temperature, float pressure, float humidity);

/* Starts a subscription. See examples of usage in TaskEPD and aws_shadow. */
EventGroupHandle_t ds_subscribe();
void ds_unsubscribe(EventGroupHandle_t handle);


#if defined(__cplusplus)
}
#endif

#endif /* _DATA_STORE_H_ */

/*******************************************************************************
 * EOF
 ******************************************************************************/
