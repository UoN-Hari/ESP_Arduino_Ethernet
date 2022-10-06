#include <Arduino.h>
#include <ethernet.h>
#include <can.h>
#include "motor_task.h"

bool HWinit(uint8_t&);

void setup()
{
	uint8_t error;
	/* Wait hardware initializing */
	while (!HWinit(error));

	/* Thread initialize */
	do {
		if (error == 1) break;
		Ethernet_t::getInstance().CreateThread();
		if (error == 2) break;
		Control::CreateThread();
	} while(0);
}

void loop()
{
	vTaskDelay(1);
}

bool HWinit(uint8_t& error_code) {
	ESP_CAN::CAN can;

    const uint8_t static_ip[] = {1,145,14,19};
	const uint8_t gateway[] = {1,145,14,1};
	const uint8_t subnet[] = {255,255,255,0};

	Serial.begin(115200);

	if(!Ethernet_t::getInstance().Init(static_ip, gateway, subnet)) {
		error_code = 1;
	}
		

	can.CAN_Setup(GPIO_NUM_33, GPIO_NUM_35, b1000k);
	
	if (can.CAN_Start() != ESP_OK) {
		error_code = 2;
	}
	
	return true;
}