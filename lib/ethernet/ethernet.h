#ifndef ETHERNET_ETHERNET_H
#define ETHERNET_ETHERNET_H

#include <Arduino.h>
#include <ETH.h>
#include <WiFiUdp.h>
#include <AsyncUDP.h>

#define ETH_ADDR        1
#define ETH_POWER_PIN   5
#define ETH_MDC_PIN     23
#define ETH_MDIO_PIN    18
#define ETH_TYPE        ETH_PHY_IP101
#define ETH_REFCLK      ETH_CLOCK_GPIO0_IN

class Ethernet_t {
/* Ethernet */
private:
    WiFiUDP udp;
    ETHClass ethernet;
    uint32_t locol_port = 8888;
public:
    /**
     * @brief This function initialize the ethernet port with an ip address
     * 
     * @return true is initialized ethernet successfully, 
     * @return false is failed in initializing ethernet
     */
    bool Init();
    bool Init (IPAddress static_ip, IPAddress gateway, IPAddress subnet);

    /**
     * @brief This function can get current ethernet connection status, 
     *        require the avalibility of serial port
     * 
     */
    void getETHStatus ();

    friend class RosETH;

/* Singuleton */
private:
    static Ethernet_t instance;
private:
    /* Constructor and Destructor */
    Ethernet_t();
    ~Ethernet_t();
    Ethernet_t(const Ethernet_t&);
    Ethernet_t& operator=(const Ethernet_t&);
public:
    /**
     * @brief This class is a singuleton class, 
     *        only this function can get the instance of this class
     * 
     * @return Ethernet_t& The instance of the class
     */
    static Ethernet_t& getInstance();
};

#endif