#include <ethernet.h>
#include <can.h>
#include <pid.h>
#include "main.h"
#include "motor_task.h"

void setup () {
	//Wait system to be initialized
	vTaskDelay (100);
	
	//Initialize Hardware
	const uint8_t static_ip[] = { 1,145,14,19 };
	const uint8_t gateway[] = { 1,145,14,1 };
	const uint8_t subnet[] = { 255,255,255,0 };

	do {
		Serial.begin (921600);
	} while (!Serial);

	Ethernet_t::getInstance ().Init (static_ip, gateway, subnet);
	CAN::open (CAN_TX_PIN, CAN_RX_PIN, b1000k);

	//Initialize Thread Tasks
	Ethernet_t::getInstance ().CreateThread ();
	Control::CreateThread ();

	//Delete default task
	vTaskDelete (NULL);
}

void loop () {}