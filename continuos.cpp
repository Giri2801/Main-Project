#include <vector>
#include "uart.h"
#define UART uart_instance[1]

char* request_for_scan()
{
    char* arr = (char *)malloc(2*sizeof(char));
    arr[0] = (char)(0xA5);
    arr[1] = (char)(0x20);
    return arr;
}

vector<rplidar_response_node> getscan()
{
    vector< rplidar_response_node > RPLIDAR_response;
    int baud_rate = 115200;
    set_baud_rate(UART,baud_rate);
    flush_uartrplidar_response_node(UART);
    char* S = request_for_scan()
    write_uart_string(UART,S);
    free(S);
// first we will be getting response descriptor 
// A5 5A 05 00 00 40 81 , 7 bytes , let us define some RESPONSE_DESCRIPTOR STRING

    string temp;
    for(int i = 1;i<=7;i++)
    {
          while ((UART->status & STS_RX_NOT_EMPTY) == 0);
          temp.push_back(UART->rcv_reg);
    }

    assert(temp == RESPONSE_DESCRIPTOR);

    bool b = true;

    while(1)
    {
        string temp;
        for(int i = 1;i<=5;i++)
        {
            while ((UART->status & STS_RX_NOT_EMPTY) == 0);
            temp.push_back(UART->rcv_reg);
        }
    // so 5 bytes (Distance,Distance,Angle,Angle,quality)
        if(b)
        {
            if((int)(temp[0]%2) == 1)
                b = false;
            else
              assert(false);
        }
        else
        {
            if((int)(temp[0]%2) == 1)
                break;
        }
        
        rplidar_response_node Sample;
      // Data check bit
        if(((int)temp[1])%2 == 0)
            continue;

      // Quality
        Sample.quality_of_scan = (((int)temp[0])>>2);

      // Angle
        int angle = (((int)temp[1])>>1);
        angle += (((int)temp[2])<<8);
        Sample.angle_of_obstacle = (angle * (1.0))/(1<<6);

       // distance in millimeters  
        int distance = (int)temp[3];
        distance += (((int)temp[4])<<7);
        Sample.distance_of_obstacle = (distance*(1.0))/(1<<2) ; 
        
        RPLIDAR_response.push_back(Sample);

    }

    return RPLIDAR_response;
}