#include"defines.h"
#include<stdio.h>
using namespace std;

set<Obstacle> Obstacle_Array;// Obstacle structure has 3 data members : the x,y coordinates ofobstacle and angle at which vehicle is approaching it wr.t the linedrawn from obstacle to goal. It is  a tuple ( x , y , theta )

Position start;
Position Goal; 


void init() {
  //Set destination and other route specific variables;
  //Set initialization values for IPS ( Indoor positioning system);
  Obstacle_Array.clear();
  //Check LiDAR health;
}

void stop(){
  stop_scanning();
}

int main() {
  init();
  Position curr_position = Start;
  while ( curr_desination != Goal) {
    vector< int > D = scandata();
    Angle G,Distance S;
    {G,S} = check_direction_to_move(D);
    curr_position = move_accordingly(G,S);
  }
}

pair<Angle,Distance> check_direction_to_move(vector< int > D){
  Angle Init=get_direction_towards_goal();// Uses IPS
  Angle curr = get_curr_direction(); // Uses IPS
  Distance S;
  { Init,S } = Find_best_direction( Init,curr ,D);
  If (S < max_movable_distance ) {
    { x,y } = getxy ( curr_position , Init , S );
    Angle A= get_angle ( {x,y} , goal ,Init );
    Obstacle curr_obstacle( x,y,A);
    Obstacle_Array.insert ( curr_obstacle );
  }
  Return { Init,S };
}

pair <Angle,Distance> Find_best_direction(Angle towards_goal,Angle curr,vector< int > D){
  Angle optimal = ((toward_goal-curr)+360)%(360);      
  Angle left = optimal,right = optimal;      
  bool L=false, R=false;      
  Distance D1=-1,D2=-1;      
  while( !(left == 0 && right == 359))      
  {
    {L,D1} = check_obstacle(left,D);
    {R,D2} = check_obstacle(right,D);           
    if(L==True or R==True) break;           
    if(left>0) left--;
    if(right<358)right++;      
  }       
  if(L==True or R==True)       
  {
    if( L==true && R==true ) 
    {
      if(D1>D2) return {left,D1};
      return {right,D2};
    }
    else if( L==true) 
    {
      return {left,D1};
    }
    else return {right,D2};       
  }      // L or R will always be true      
  stop();
}
pair<bool,Distance> check_obstacle(Angle angle, vector< int > Data)
{
  // from scan_data() check whether we have obstacle in thisdirection or not
  {x,y} = get_cordinates(curr_position);
  if ( D[ angle ] == -1 ) 
  {
    return { True , max_movable_distance};
  }
  else if( Data[angle] > min_allowed_obstacle_dist ) {              
    int r = D[angle];              
    int x1 = x + r*cos(angle);              
    int y1 = y + r*sin(angle); 
    Angle theta = get_angle({x,y},goal,angle);             
    if(Obstacle_Array.find({x1,y1,theta}) == Obstacle_Array.end())    
      return { true , min(D[angle],max_movable_distance) };
  }
  return  {false,-1};
}
    
Position Move_accordingly( Angle G, Distance S) 
{
  rotate_by_angle( G );
  move_distance(S);
  curr= get_current_position() // IPS
  return curr;
}