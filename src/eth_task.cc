#include <Arduino.h>
#include <ros.h>
#include <ethernet.h>
#include <geometry_msgs/Twist.h>

geometry_msgs::Twist ros_msg;
unsigned char eth_msg[ETH_RX_BUF_LEN];

void Ethernet_thread(void* pvParameter) {
    
    for(;;) {
        // Ethernet_t::getInstance().udp.read(eth_msg, Ethernet_t::getInstance().udp.available());
        // ros_msg.deserialize((unsigned char*&)eth_msg);
        // Serial.printf("%s\n", eth_msg);
        vTaskDelay(10);
    }
}