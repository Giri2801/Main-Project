/*
https://github.com/nothans/thingspeak-esp-examples/blob/master/examples/RSSI_to_ThingSpeak.ino
http://tdmts.net/2017/02/04/using-wifi-rssi-to-estimate-distance-to-an-access-point/  
https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/readme.html
https://bbs.espressif.com/viewtopic.php?f=46&t=850
https://bbs.espressif.com/viewforum.php?f=67
https://iotandelectronics.wordpress.com/2016/10/07/how-to-calculate-distance-from-the-rssi-value-of-the-ble-beacon/
*/
#include "esp.h"

void initwifi()
{
  
}


Position intersection(Line L1,Line L2 )
{
    double temp=L1.a*1.00/L2.a;
    double y1=(L1.c-temp*L2.c)/(L1.b-temp*L2.b);
    double x1=(L1.c-y1*L1.b)/L1.a;
    return Position((int)x1,(int)y1);

}


long getRSSI(int Wifi_number)
{
     // code for connection.
     WiFi.begin(Stations[Wifi_number].SSID,Stations[Wifi_number.password]);
     while(WiFi.status() != WL_CONNECTED)
     {
        delay(500);
     }
     long rssi = WiFi.RSSI();
     return rssi;
}

int getDistance(long RSSI,int Wifi_number){
    //Use formula to get distance
    return (int)power(10,(Stations[Wifi_number].constantA-RSSI)/20)
}


Line getLine(Position p1,int d1,Position p2,int d2){
   Line L;
   L.a = 2*(p2.x - p1.x);
   L.b = 2*(p2.y - p1.y);
   L.c = (d1*d1)-(d2*d2)+(p2.x*p2.x)-(p1.x*p1.x)+(p2.y*p2.y)-(p1.y*p1.y);
}


Position getCurrentPosition(){
    int d[3];
    for(int i=0;i<3;i++){
        long rssi_val;
        rssi_val=getRSSI(i);
        d[i]=getDistance(rssi_val , i);
    }
    Line L1=getLine(Stations[0].wifi_position,d[0],Stations[1].wifi_position,d[1]);
    Line L2=getLine(Stations[1].wifi_position,d[1],Stations[2].wifi_position,d[2]);
    return intersection(L1, L2);
}