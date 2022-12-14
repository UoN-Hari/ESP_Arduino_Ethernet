#include <ros_eth/eth_rosmsg.h>

RosETH::RosETH(/* args */)
{
}

RosETH::~RosETH()
{
}

bool RosETH::getMsg(geometry_msgs::TwistStamped* msg) {
    int packet_size = Ethernet_t::getInstance().udp.parsePacket();

    if(packet_size) {
        buffer = new char[packet_size];

        Ethernet_t::getInstance().udp.read(buffer, packet_size);
        msg->deserialize((unsigned char*)buffer);

        delete buffer;
        return true;
    }
    return false;
}

bool RosETH::getMsg(geometry_msgs::Twist* msg) {
    int packet_size = Ethernet_t::getInstance().udp.parsePacket();

    if(packet_size) {
        buffer = new char[packet_size];

        Ethernet_t::getInstance().udp.read(buffer, packet_size);
        msg->deserialize((unsigned char*)buffer);
        
        delete buffer;
        return true;
    }
    return false;
}