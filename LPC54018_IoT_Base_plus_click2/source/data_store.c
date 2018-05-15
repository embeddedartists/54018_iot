

#include "board.h"

#include "data_store.h"

#include "string.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define NUM_GROUPS 5

#define DEFAULT_TIMEOUT_MS  2000
#define DEFAULT_TIMEOUT_TICKS  (DEFAULT_TIMEOUT_MS / portTICK_PERIOD_MS)

/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Variables
 ******************************************************************************/

static data_store_t shared_data;
static SemaphoreHandle_t xSem;

static EventGroupHandle_t groups[NUM_GROUPS] = {0};


/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Prototypes
 ******************************************************************************/


/*******************************************************************************
 * Code
 ******************************************************************************/

static void notify_all(uint32_t bitmask)
{
	int i;
	for (i = 0; i < NUM_GROUPS; i++) {
		if (groups[i] != NULL) {
			xEventGroupSetBits(groups[i], bitmask);
		}
	}
}

#if defined(__cplusplus)
extern "C" {
#endif

bool ds_initialize(const char* msg, bool button_pressed, float temperature, float pressure, float humidity)
{
	memset(shared_data.msg, 0, sizeof(shared_data.msg));
	strncpy(shared_data.msg, msg, DS_MAX_MSG_LEN);
	shared_data.button_pressed = button_pressed;
	shared_data.temperature = temperature;
	shared_data.pressure = pressure;
	shared_data.humidity = humidity;

	xSem = xSemaphoreCreateBinary();
	xSemaphoreGive(xSem);
	return (xSem != NULL);
}

/* Copies the shared data into the provided argument */
bool ds_read(data_store_t* data)
{
	if (xSemaphoreTake(xSem, DEFAULT_TIMEOUT_TICKS)) {

		memcpy(data, &shared_data, sizeof(shared_data));

		xSemaphoreGive(xSem);
		return true;
	} else {
		return false; // got a timeout
	}
}

/* Updates the shared data */
bool ds_write_message(const char* msg)
{
	if (xSemaphoreTake(xSem, DEFAULT_TIMEOUT_TICKS)) {

		strncpy(shared_data.msg, msg, DS_MAX_MSG_LEN);
		notify_all(DS_MSG_CHANGED);

		xSemaphoreGive(xSem);
		return true;
	} else {
		return false; // got a timeout
	}
}

bool ds_write_message_chars(const char* msg, int start_offset, int end_offset)
{
	if (xSemaphoreTake(xSem, DEFAULT_TIMEOUT_TICKS)) {

		int len = end_offset - start_offset;
		if (len > DS_MAX_MSG_LEN) {
			len = DS_MAX_MSG_LEN;
		}
		strncpy(shared_data.msg, &msg[start_offset], len);
		shared_data.msg[len] = '\0';

		notify_all(DS_MSG_CHANGED);

		xSemaphoreGive(xSem);
		return true;
	} else {
		return false; // got a timeout
	}
}

bool ds_write_button(bool pressed)
{
	if (xSemaphoreTake(xSem, DEFAULT_TIMEOUT_TICKS)) {

		shared_data.button_pressed = pressed;
		notify_all(DS_BUTTON_CHANGED);

		xSemaphoreGive(xSem);
		return true;
	} else {
		return false; // got a timeout
	}
}

bool ds_write_weather_data(float temperature, float pressure, float humidity)
{
	if (xSemaphoreTake(xSem, DEFAULT_TIMEOUT_TICKS)) {

		shared_data.temperature = temperature;
		shared_data.pressure = pressure;
		shared_data.humidity = humidity;
		notify_all(DS_WEATHER_CHANGED);

		xSemaphoreGive(xSem);
		return true;
	} else {
		return false; // got a timeout
	}
}

/* Starts a subscription. See examples of usage in TaskEPD and aws_shadow. */
EventGroupHandle_t ds_subscribe()
{
	EventGroupHandle_t hnd = NULL;
	if (xSemaphoreTake(xSem, DEFAULT_TIMEOUT_TICKS)) {

		int i;
		for (i = 0; i < NUM_GROUPS; i++) {
			if (groups[i] == NULL) {
				hnd = xEventGroupCreate();
				groups[i] = hnd;
				break;
			}
		}

		xSemaphoreGive(xSem);
	}
	return hnd;
}

void ds_unsubscribe(EventGroupHandle_t handle)
{
	if (handle == NULL) {
		return;
	}

	if (xSemaphoreTake(xSem, DEFAULT_TIMEOUT_TICKS)) {

		int i;
		for (i = 0; i < NUM_GROUPS; i++) {
			if (groups[i] == handle) {
				vEventGroupDelete(handle);
				groups[i] = NULL;
				break;
			}
		}
		xSemaphoreGive(xSem);
	}
}

#if defined(__cplusplus)
}
#endif
