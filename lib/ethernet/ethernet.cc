#include <ethernet.h>

#pragma region Thread

__attribute__((weak)) void Ethernet_thread(void* pvParameter);

void Ethernet_t::CreateThread() {
    if (!thread_init_status) {
        xTaskCreatePinnedToCore (
		    Ethernet_thread,
		    thread_name,
            stack_depth,
            NULL,
            thread_priority,
            &thread_handler,
            ARDUINO_RUNNING_CORE
	    );
        thread_init_status = true;
    } else {
        if(Serial)
            Serial.println("Ethernet_Thread is already exists");
    }
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
    IPAddress static_ip(1, 145, 14, 19);
    IPAddress gateway(1, 145, 14, 1);
    IPAddress subnet(255, 255, 255, 0);
    
    if (!ethernet.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_REFCLK)) {
        if (Serial) {
            Serial.println("Initializing Ethernet failed");
        }
        return false;
    } else {
        if (Serial) {
            Serial.println("Ethernet Initialized");
        }
        if(!ethernet.config(static_ip, gateway, subnet)) {
            if (Serial) {
                Serial.println("Configuring IP failed");
            }
            return false;
        } else {
            if (Serial) {
                Serial.println("IP configured");
            }
            if(!udp.begin(locol_port)) {
                if (Serial) {
                    Serial.println("Beginning UDP failed");
                }
                return false;
            } else {
                if (Serial) {
                    Serial.println("Begin UDP listening");
                    Serial.println();
                }
                getETHStatus();
            }
        }
    }
    return true;
}

bool Ethernet_t::Init(IPAddress static_ip, IPAddress gateway, IPAddress subnet) {
    if (!ethernet.begin(ETH_ADDR, ETH_POWER_PIN, ETH_MDC_PIN, ETH_MDIO_PIN, ETH_TYPE, ETH_REFCLK)) {
        if (Serial) {
            Serial.println("Initializing Ethernet failed");
        }
        return false;
    } else {
        if (Serial) {
            Serial.println("Ethernet Initialized");
        }
        if(!ethernet.config(static_ip, gateway, subnet)) {
            if (Serial) {
                Serial.println("Configuring IP failed");
            }
            return false;
        } else {
            if (Serial) {
                Serial.println("IP configured");
            }
            if(!udp.begin(locol_port)) {
                if (Serial) {
                    Serial.println("Beginning UDP failed");
                }
                return false;
            } else {
                if (Serial) {
                    Serial.println("Begin UDP listening");
                    Serial.println();
                }
                getETHStatus();
            }
        }
    }
    return true;
}

void Ethernet_t::getETHStatus() {
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