#include "defines.h"
#include "TUI.h"



class GUI 
{
  unsigned x_dim; 
  unsigned y_dim; 
  public:
    GUI (unsigned x , unsigned y ):
    x_dim(x), y_dim(y)
    {

    }
    GUI ()
    {
      x_dim = BORDER_X_MAX;
      y_dim = BORDER_Y_MAX;
    }
  
    void emptyCanvas()
    {
      for ( unsigned i = 0; i<x_dim; i++)
      {
        moveTo(i,0);
        for ( unsigned j = 0; j<y_dim; j++)
        {
          printf("%c", ' ');
          moveTo(i,j);
        }
      }

    }







};

