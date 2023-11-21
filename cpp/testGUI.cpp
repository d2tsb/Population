#include "GUI.h"
#include "stopwatch.h"

int main () 
{
  Stopwatch sw; 
  sw.reset(); 
  GUI x;
  sw.start();
  x.emptyCanvas(); 
  sw.finish();
  sw.print_duration_in_milliseconds(); 

}