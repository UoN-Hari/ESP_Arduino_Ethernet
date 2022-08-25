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
    const uint8_t static_ip[] = {1,145,14,19};
	const uint8_t gateway[] = {1,145,14,1};
	const uint8_t subnet[] = {255,255,255,0};

	Serial.begin(115200);
	if(!Ethernet_t::getInstance().Init(static_ip, gateway, subnet))
		error_code = 1;
	return true;
}