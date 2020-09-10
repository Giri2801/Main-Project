  //https://github.com/Slamtec/rplidar_sdk/blob/master/sdk/app/ultra_simple/main.cpp
#include"lidar.h"
#include "Uart.h"
//https://gitlab.com/shaktiproject/software/shakti-sdk/-/blob/master/software/projects/weatherstation/weatherstation.c

/*https://github.com/Slamtec/rplidar_sdk/blob/master/sdk/sdk/src/rplidar_driver.cpp


https://www.robotshop.com/media/files/pdf2/rpk-02-communication-protocol.pdf
*/
std::vector<int>  scandata()
{
    std::vector<int> arr(360,-1);
    std::vector<rplidar_response_node> data = getscan();
    goto_idlestate();
    for(auto it : data)
    {
       if(it. quality_of_scan == 0)continue;
       arr[it.angle_of_obstacle] = it.distance_of_obstacle;
    }
    return arr;
}

bool ishealthok(){
    rplidar_response_device_health Health;
    Health = gethealth();
    if(Health.status == 0) return true;
    goto_idlestate();
    return false;
}






