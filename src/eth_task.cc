#include <Arduino.h>
#include <ros.h>
#include <ethernet.h>
#include <geometry_msgs/Twist.h>

geometry_msgs::Twist ros_msg;
char eth_msg[ETH_RX_BUF_LEN];

void Ethernet_thread(void* pvParameter) {
    
    for(;;) {
        int packet_size = Ethernet_t::getInstance().udp.parsePacket();
        if (packet_size) {
            Ethernet_t::getInstance().udp.read(eth_msg, packet_size);
            Serial.println(eth_msg);
        }
        // ros_msg.deserialize((unsigned char*&)eth_msg);
        // Serial.printf("%s\n", eth_msg);
        vTaskDelay(10);
    }
}