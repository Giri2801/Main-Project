#include<stdio.h>
#include"uart.h"
#include "pinmux.h"

#define LIDAR_UART uart_instance[1]     
#define ESP_UART uart_instance[2]     

char* request_for_getinfo()
{
  char* arr = (char*)malloc(2*sizeof(char));
  arr[0] = (char)(0xA5);
  arr[1] = (char)(0x50);
  return arr;
}

char* request_for_gethealth()
{
  char* arr = (char*)malloc(2*sizeof(char));
  arr[0] = (char)(0xA5);
  arr[1] = (char)(0x52);
  return arr;
}

//uart enable interrupt???

void main()
{
    char arr[3];
  arr[0] = (char)(0xA5);
  arr[1] = (char)(0x52);
  arr[2] = '\0';
  char reset[3];
  reset[0] = (char) (0xA5);
  reset[1] = (char) (0x40);
  char stopmotor[3];
  stopmotor[1] = (char) (0xA5);
  stopmotor[1] = (char) (0x25);
    printf("\n Initializing .... \n");
    // Using PINMUX config 2
    printf("\n setting PIN MUX config to 2 .... \n");
    *pinmux_config_reg = 0x5;
    int brate = 115200;
    //int brate = 256000;
    printf("\n set LIDAR UART BAUD RATE.... \n");
    set_baud_rate(LIDAR_UART,brate);
    printf("\n sending data to LiDAR.... \n");
    flush_uart(LIDAR_UART);
    write_uart_string_withoutnull(LIDAR_UART,arr);
    //write_uart_character(LIDAR_UART,arr[0]);
    //write_uart_character(LIDAR_UART,arr[1]);
    //delay_loop(100000, 100000);
    printf("\n reading data from LiDAR.... \n");
   char a;
    for (int i =0; i < 13;i++) {
	    read_uart_character(LIDAR_UART,&a);
    	    printf("%x\n",a);
    }
#if 0
    //flush_uart(LIDAR_UART);
    printf("\n stop LiDAR motor.... \n");
    write_uart_character(LIDAR_UART,stopmotor[0]);
    write_uart_character(LIDAR_UART,stopmotor[1]);
    printf("\n resetting LiDAR.... \n");
    /*
    write_uart_character(LIDAR_UART,reset[0]);
    write_uart_character(LIDAR_UART,reset[1]);
    delay_loop(1000, 1000);
    */
    printf("\n sending data to LiDAR.... \n");
a1:
    //write_uart_string(LIDAR_UART, arr);
    flush_uart(LIDAR_UART);
    write_uart_character(LIDAR_UART,arr[0]);
    write_uart_character(LIDAR_UART,arr[1]);
    delay_loop(100000, 100000);
    printf("\n reading data from LiDAR.... \n");
    /*
    //char* health = (char*)malloc(12*sizeof(char));
    char health[13];
    read_uart_string(LIDAR_UART , health);
    printf("%s",health);
    */
    /*
    char a;
    for (int i =0; i < 13;i++) {
	    read_uart_character(LIDAR_UART,&a);
    	    printf("%c",a);
    }
    flush_uart(LIDAR_UART);
    */
/*
    write_uart_string(LIDAR_UART, request_for_getinfo());
    char* info = (char*)malloc(30*sizeof(char));
    read_uart_string(LIDAR_UART , info );
    printf("%s",info);
   */
#endif
}
