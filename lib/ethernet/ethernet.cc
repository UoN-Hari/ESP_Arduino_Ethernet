#include <ethernet.h>

#pragma region Thread

__attribute__((weak)) void Ethernet_thread(void* pvParameter);

void Ethernet_t::CreateThread() {
    xTaskCreatePinnedToCore (
		Ethernet_thread,
		thread_name,
        stack_depth,
        NULL,
        thread_priority,
        &thread_handler,
        ARDUINO_RUNNING_CORE
	);
}

__attribute__((weak)) void Ethernet_thread(void* pvParameter) {
    /* Initialize */

    /* Loop */
    for(;;) {
        if(Serial)
            Serial.println("CPU1 is ready");
        vTaskDelay(1000);
    }

}

#pragma endregion Thread

#pragma region Ethernet

bool Ethernet_t::Init() {
    /* Create Thread */
    IPAddress static_ip(1, 145, 14, 19);
    IPAddress gateway(1, 145, 14, 1);
    IPAddress subnet(255, 255, 255, 0);
    
    ethernet.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_REFCLK);
    ethernet.config(static_ip, gateway, subnet);
    udp.begin(locol_port);

    PrintETHInfo();

    return true;
}

void Ethernet_t::PrintETHInfo() {
    if(Serial) {
        Serial.print("ETH MAC: ");
        Serial.println(ethernet.macAddress());
        Serial.print("IPv4: ");
        Serial.println(ethernet.localIP());
        if (ethernet.fullDuplex())
            Serial.println("FULL_DUPLEX");
        Serial.print("Speed: ");
        Serial.print(ethernet.linkSpeed());
        Serial.println(" Mbps");
    }
}

#pragma endregion Ethernet

#pragma region ClassImplementation

Ethernet_t Ethernet_t::instance;

Ethernet_t& Ethernet_t::getInstance() {
    return instance;
}

Ethernet_t::Ethernet_t(/* args */) {
    
}

Ethernet_t::~Ethernet_t() {
    vTaskDelete(&thread_handler);
}

#pragma endregion ClassImplementation