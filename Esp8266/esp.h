/*
    

*/
#include<dos.h>
#include<string.h>
#include"../defines.h"
//supporting function

Position getCurrentPosition();
long getRSSI(int Wifi_number);// In this function, we connect to that specific wifi, get rssi value and return it.

struct Wifi_Station{
    Position wifi_position;
    string SSID;
    float constantA;
};

struct Wifi_Station Staions[3];
struct Line{
  int a,b,c;  // Represents ax+by=c
};