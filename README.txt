Readme
--------
MCUXpresso Projects for IoT Mini Prototype Board (OM4008) with LPC54018 IoT (OM4007)

Common to all projects:
* Projects are only for MCUXpresso (v10.2.0_prc2) at this time
* All projects use FreeRTOS and are based on examples in the SDK from https://mcuxpresso.nxp.com/.
* The projects have been created using New Project... in MCUXpresso so that they can support
  both C and C++ at the same time. The ePaper code is C++.
* Skeleton code to initialize the Click1 / Click2 / Arduino pins on the board
* A DataStore concept which handles data shared between tasks and a subscription type
  notification via FreeRTOS event groups
* Support for 2.66" ePaper display from Pervasive Displays (black/white/red)

LPC54018_IoT_Base
-----------------
A project with unused skeleton code for Click1 / Click2 / Arduino expansion.

The project has two tasks:
1. led_accel_task_entry blinks with the LEDs and if the User Button is pressed 
   it gets reported to the DataStore. The task also echoes any character
   typed in the terminal back to the user.
2. epd_task_entry waits for the DataStore to report a button press and then 
   updates the ePaper display. If there has been no updates in 60s the ePaper
   display is refreshed anyway.
   
LPC54018_IoT_Base_plus_click2
-----------------------------
Based on LPC54018_IoT_Base but with the following changes:
1. The project is configured to have a Weather Click module (https://www.mikroe.com/weather-click)
   inserted in socket 2 on the IoT Mini Prototype Board.
2. The code for the click module is in the exp_click2/ folder and it has its own
   task publishes the weather data in the DataStore every 5 seconds
3. The epaper task updates the display with the weather data from the DataStore

LPC54018_IoT_Base_plus_aws
--------------------------
Based on LPC54018_IoT_Base but with the following changes:
*  FreeRTOS replaced with the setup from the SDK's shadow_wifi_qspi_xip example
*  The wifi module on the IoT board is enabled and used. SSID and password must be
   configured in amazon-freertos/include/aws_clientcredential.h for it to work
*  A connection to AWS must be configured according to the NXP/Amazon instructions
   which will generate the amazon-freertos/include/aws_clientcredential_keys.h file
   that is needed to compile this project.
*  The led_accel_task_entry task no longer echoes typed characters and is mainly focused
   on detecting button clicks
*  The epd_task_entry task also detects changes in a "message" that can be set from
   the AWS and pushed to the device. This message will be shown in the lower left corner
   of the ePaper display.
*  The aws_shadow_lightbulb_on_off.c file has been modified to subscribe to changes
   from both the DataStore and AWS. The button presses come from the DataStore and
   are published in AWS. The message to display on the ePaper comes from AWS and is
   published in the DataStore.
