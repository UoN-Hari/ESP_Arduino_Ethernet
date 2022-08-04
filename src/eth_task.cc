#include <Arduino.h>
#include <ros.h>
#include <ethernet.h>
#include <geometry_msgs/TwistStamped.h>
#include <cstring>
#include <codecvt>
#include <ros_eth/eth_rosmsg.h>

// char* eth_msg;
RosETH rosmsg;
char* eth_msg;
geometry_msgs::TwistStamped twist;

void Ethernet_thread(void* pvParameter) {
    
    for(;;) {
        // int packet_size = Ethernet_t::getInstance().udp.parsePacket();
        
        // if (packet_size) {
        //     eth_msg = new char[packet_size];

        //     Ethernet_t::getInstance().udp.read(eth_msg, packet_size);
        //     twist.deserialize((unsigned char*)eth_msg);
        //     Serial.println(twist.header.stamp.sec);
        //     Serial.println(packet_size);

        //     delete eth_msg;
        // }
        

        rosmsg.getMsg(&twist);
        Serial.println(twist.header.stamp.sec);
        vTaskDelay(10);
    }
}