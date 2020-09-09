#include"Motor/PWM.h"
#include"Esp8266/esp.h"
#include"LiDAR/LiDAR.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include <utility> 

#define Distance int // distance in mm
#define Angle int //angle (between [0,360])
#define max_movable_distance 500  // distance to move if there is no obstacle in a particular direction
#define min_allowed_obstacle_dist 100

class Position {
  int x,y;
  Position(int x = -1,int y=-1): x , y {}
};

Distance distance_between(Position p1,Position p2)
{
  return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
}

struct obstacle {
  int x,y;
  Angle approach_angle;
};

typedef struct obstacle Obstacle;

