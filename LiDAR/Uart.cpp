#include"Uart.h"
#define UART uart_instance[1]

char arr[] = {(char)(0xA5),(char)(0x5A), (char)(0x5),(char)(0x0),(char)(0x0) ,(char)(0x40) ,(char)(0x81)};

char arr1[] = {(char)(0xA5),(char)(0x5A), (char)(0x3),(char)(0x0),(char)(0x0) ,(char)(0x0) ,(char)(0x6)};

const string GET_SCAN_RESPONSE_DESCRIPTOR(arr);
const string GET_HEALTH_RESPONSE_DESCRIPTOR (arr1);


std::string request_for_idlestate()
{
   std::string arr;
   arr.push_back((char)(0xA5));
   arr.push_back((char)(0x25));
   return arr;
}

std::string request_for_reset()
{
  std::string arr ;
  arr.push_back((char)(0xA5));
  arr.push_back(((char)(0x40));
  return arr;
}

std::string request_for_scan()
{
  std::string arr ;
  arr.push_back((char)(0xA5));
  arr.push_back((char)(0x20));
  return arr;
}


std::string request_for_gethealth()
{
  std::string arr ;
  arr.push_back((char)(0xA5));
  arr.push_back((char)(0x52));
  return arr;
}

// Note : We have to change read_uart_string function for scan call
//Format of scan result :
// Starts with (A5)(5A)(0X05)(0X00)(0X00)(0X40)(0X81)
// char* 
// Then for each 5 bytes, quality,diatance,angle can be read;

std::vector<rplidar_response_node> getscan()
{
    std::vector< rplidar_response_node > RPLIDAR_response;
    int baud_rate = 115200;
    set_baud_rate(UART,baud_rate);
    flush_uartrplidar_response_node(UART);
    std::string s = request_for_scan();
    char S[3];
    S[0] = s[0];S[1] = s[1]; S[2] = '\0';
    write_uart_string(UART,S);
// first we will be getting response descriptor 
// A5 5A 05 00 00 40 81 , 7 bytes , let us define some RESPONSE_DESCRIPTOR STRING

    std::string temp;
    for(int i = 1;i<=7;i++)
    {
          while ((UART->status & STS_RX_NOT_EMPTY) == 0);
          temp.push_back(UART->rcv_reg);
    }

    assert(temp == GET_SCAN_RESPONSE_DESCRIPTOR);

    bool b = true;

    while(1)
    {
        std::string temp;
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
            if((int)(temp[0]%2) == 1){
                goto_idle_state();
                break;
            }
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

void reset()
{
    std::string s = request_for_reset();
    char S[3];
    S[0] = s[0];S[1] = s[1]; S[2] = '\0';
    write_uart_string(UART,S);
}

void goto_idlestate()
{
    std::string s = request_for_idlestate();
    char S[3];
    S[0] = s[0];S[1] = s[1]; S[2] = '\0';
    write_uart_string(UART,S);
}

rplidar_response_device_health gethealth()
{
  rplidar_response_device_health Health;
  // fill attributes by sending command
  std::string s = request_for_gethealth();
  char S[3];
  S[0] = s[0];S[1] = s[1]; S[2] = '\0';
  write_uart_string(UART,S);
// first we will be getting response descriptor 
// A5 5A 03 00 00 00 06 , 7 bytes , let us define some RESPONSE_DESCRIPTOR STRING
  std::string temp;
  for(int i = 1;i<=7;i++)
  {
    while ((UART->status & STS_RX_NOT_EMPTY) == 0);
    temp.push_back(UART->rcv_reg);
  }

  assert(temp == GET_HEALTH_RESPONSE_DESCRIPTOR);
  temp="";
  for(int i=1;i<=3;i++){
    while ((UART->status & STS_RX_NOT_EMPTY) == 0);
        temp.push_back(UART->rcv_reg);
  }
  Health.status = temp[0];
  int t1 = (int)temp[2];
  t1 = t1<<8;
  t1 += (int)temp[1];
  Health.error_code = (unsigned short int) t1;
  return Health;
}


