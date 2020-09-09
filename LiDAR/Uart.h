#include"../defines.h"

std::string request_for_stop();
std::string request_for_reset();
std::string request_for_scan();
std::string request_for_getinfo();
std::string request_for_gethealth();
std::vector<rplidar_response_node> getscan();
void reset();
rplidar_response_device_health gethealth();

typedef struct rplidar_response_node {
    unsigned short int   angle_of_obstacle; 
    unsigned int   distance_of_obstacle; 
    unsigned char    quality_of_scan;  
} __attribute__((packed)) rplidar_response_node;


typedef struct rplidar_response_device_health {
    unsigned char   status;
    unsigned short int  error_code;
} __attribute__((packed)) rplidar_response_device_health;

