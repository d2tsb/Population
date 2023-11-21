#include "field.h"


int main () 
{
  seedGenerator(); 
  //blankCanvas(20, 20);
  //std::cout << dice(AgentDistribution(0.25, 0.25, 0.3, 0.2)) << std::endl; 
  //std::cout << dice(AgentDistribution(0.0, 0.0, 0.0,  1.0)) << std::endl; 
  field f(BORDER_X_MAX, BORDER_X_MIN, BORDER_Y_MAX, BORDER_Y_MIN);
  f.InitNAgentsToIndex(5, 0, 0);
  f.InitNAgentsToIndex(5, 25, 25);
  f.InitNAgentsToIndex(10, 53, 54);
  f.InitNAgentsToIndex(20, 6, 7);
  f.InitNAgentsToIndex(10, 2, 70);
  f.TUI_LOOP(50); 
   
}