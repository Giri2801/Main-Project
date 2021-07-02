#include"defines.h"

int main()
{
  initializeMotor();
  rotate(90,true);
  rotate(180,false);
  go_straight(1000);
  return 0;
}
