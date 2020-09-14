#include"defines.h"

//write code for testing our final Lidar Module

int main(){
  if(ishealthok()){
    vector<int> temp=getscan();
    for(int i=0;i<360;i++){
      printf("Angle %d : %d",i,temp[i]);
    }
  }
  return 0;
}