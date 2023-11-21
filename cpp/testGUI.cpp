#include "GUI.h"
#include "stopwatch.h"

int main () 
{
  Stopwatch sw; 
  GUI x;
  sw.reset(); 
  sw.start();
  x.clearAll();
  //x.emptyCanvas(); 
  sw.finish();
  std::cout << std::endl; 
  //std::cout << "time of emptyCanvas" << std::endl; 
  //sw.print_duration_in_milliseconds(); 

  // sw.reset(); 
  // sw.start();
  // x.emptyCanvasEvenFaster(); 
  // sw.finish();
  // sw.print_duration_in_milliseconds(); 


}