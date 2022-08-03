#include <Arduino.h>
#include <ethernet.h>

bool HWinit(uint8_t&);

void setup()
{
	uint8_t error;
	/* Wait hardware initializing */
	while (!HWinit(error));

	/* Thread initialize */
	if(error != 1)
		Ethernet_t::getInstance().CreateThread();
}

void loop()
{
	vTaskDelay(1);
}

bool HWinit(uint8_t& error_code) {
	Serial.begin(115200);
	if(!Ethernet_t::getInstance().Init())
		error_code = 1;
	return true;
}