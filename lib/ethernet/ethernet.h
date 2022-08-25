#ifndef ETHERNET_ETHERNET_H
#define ETHERNET_ETHERNET_H

#include <Arduino.h>
#include <ETH.h>
#include <WiFiUdp.h>
#include <AsyncUDP.h>

#define PRIORITY_REALTIME 4u
#define PRIORITY_HIGH     3u
#define PRIORITY_MIDIUM   2u
#define PRIORITY_LOW      1u

#define ETH_ADDR        1
#define ETH_POWER_PIN   5
#define ETH_MDC_PIN     23
#define ETH_MDIO_PIN    18
#define ETH_TYPE        ETH_PHY_IP101
#define ETH_REFCLK      ETH_CLOCK_GPIO0_IN

class Ethernet_t {
/* Thread */
private:
    TaskHandle_t thread_handler;
    const uint32_t stack_depth = 1024;
    const uint8_t thread_priority = PRIORITY_REALTIME;
    const char* thread_name = "Ethernet";
    bool thread_init_status = false;
public:
    /**
     * @brief Create a new Thread that running in CPU1
     * 
     */
    void CreateThread();

    friend void Ethernet_thread(void* pvParameter);
    friend class RosETH;


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
    bool Init(IPAddress static_ip, IPAddress gateway, IPAddress subnet);

    /**
     * @brief This function can get current ethernet connection status, 
     *        require the avalibility of serial port
     * 
     */
    void getETHStatus();


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


/**
 * @brief The Thread entry function, 
 *        have a weak implementation and can be rewrite by user
 * 
 * @param pvParameter the parameters of thread
 */
extern void Ethernet_thread(void* pvParameter);

#endif