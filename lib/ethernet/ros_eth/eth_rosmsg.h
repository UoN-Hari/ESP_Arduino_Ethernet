#ifndef ETHERNET_ETH_ROSMSG_H
#define ETHERNET_ETH_ROSMSG_H

#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/Twist.h>
#include <ethernet.h>


class RosETH
{
private:
    char* buffer;
public:
    RosETH(/* args */);
    ~RosETH();

    void getMsg(geometry_msgs::TwistStamped* msg);
    void getMsg(geometry_msgs::Twist* msg);
};

RosETH::RosETH(/* args */)
{
}

RosETH::~RosETH()
{
}

void RosETH::getMsg(geometry_msgs::TwistStamped* msg) {
    int packet_size = Ethernet_t::getInstance().udp.parsePacket();

    if(packet_size) {
        buffer = new char[packet_size];

        Ethernet_t::getInstance().udp.read(buffer, packet_size);
        msg->deserialize((unsigned char*)buffer);

        delete buffer;
    }
    
}

void RosETH::getMsg(geometry_msgs::Twist* msg) {
    int packet_size = Ethernet_t::getInstance().udp.parsePacket();

    if(packet_size) {
        buffer = new char[packet_size];

        Ethernet_t::getInstance().udp.read(buffer, packet_size);
        msg->deserialize((unsigned char*)buffer);
        
        delete buffer;
    }
    
}

#endif