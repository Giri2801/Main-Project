#include <stdio.h>
#include <string>
#include <vector>
#include <cassert>
#include "uart.h"
std::string request_for_idlestate();
std::string request_for_reset();
std::string request_for_scan();
std::string request_for_gethealth();


typedef struct rplidar_response_node {
    unsigned short int   angle_of_obstacle; 
    unsigned int   distance_of_obstacle; 
    unsigned char    quality_of_scan;  
} __attribute__((packed)) rplidar_response_node;


typedef struct rplidar_response_device_health {
    unsigned char   status;
    unsigned short int  error_code;
} __attribute__((packed)) rplidar_response_device_health;


std::vector<rplidar_response_node> getscan();
void goto_idle_state();
void reset();
rplidar_response_device_health gethealth();
