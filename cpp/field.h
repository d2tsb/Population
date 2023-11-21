#include <ctime>
#include "GUI.h"

#define INDEXOUTOFBOUNDEXCEPTION 89

class field
{
private:
  int x_max = BORDER_X_MAX;
  int x_min = BORDER_X_MIN;
  int y_max = BORDER_Y_MAX;
  int y_min = BORDER_Y_MIN;
  long iteration = 0;
  Vector<Vector<AgentCluster>> Field;

public:
  // get highest averageGrade / Grade median
  // update

  field(unsigned xMax = BORDER_X_MAX, unsigned xMin = BORDER_X_MIN,
        unsigned yMax = BORDER_Y_MAX, unsigned yMin = BORDER_Y_MIN)
  {
    this->x_max = xMax;
    this->x_min = xMin;
    this->y_max = yMax;
    this->y_min = yMin;
    try
    {
      Field.resize(x_max);
      for (unsigned i = 0; i < x_max; i++)
      {
        Field[i] = Vector<AgentCluster>(y_max);
        Field[i].resize(y_max);
      }
      std::cout << "size of Field: " << Field.getSize() << std::endl;
      std::cout << "size of Field: " << Field[0].getSize() << std::endl;
      std::cout << "size of Field: " << Field[0][0].amountOfAgents() << std::endl;
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  void InitNAgentsToIndex(unsigned N, unsigned x = 0, unsigned y = 0)
  {
    // x and y have to be in Range.
    if (x > x_max || x < x_min || y > y_max || y < y_min)
      throw INDEXOUTOFBOUNDEXCEPTION;
    // HI_("initNagents")
    Field[x][y].fill(N, x, y);
  }
  void update()
  {
    // HI_("bla")
    for (int i = 0; i < Field.getSize(); i++)
    {
      for (int j = 0; j < Field[i].getSize(); j++)
      {
        if (iteration)
        {
          this->Field[i][j] /*x,y */.updateWeights();
          this->Field[i][j].makeMove();
          // einmal bitte umsortieren.
          // restructure
          if (this->Field[i][j].amountOfAgents())
          {

            for (int k = 0; k < this->Field[i][j].amountOfAgents(); ++k)
            {
              Agent temp = this->Field[i][j].getBack();
              position pos_temp = temp.getPosition();
              this->Field[pos_temp.x][pos_temp.y].PushBack(temp);
              this->Field[i][j].PopBack();
            } // moving the elements to the right cluster.
          }
        }
      }
    }
    ++iteration;
  }

  void TUI_LOOP(unsigned updateRateInMillsecs = 1000)
  {
    GUI x; 
    x.clearAll();
    x.emptyCanvas();
    for (;;)
    {
      update();
      Sleep(updateRateInMillsecs);

      // clear terminal
      // write title - or description
      // print results.
      //   for (int i = 0; i < Field.getSize(); i++)
      //   {
      //     for (int j = 0; j < Field[i].getSize(); j++)
      //     {
      //       this->Field[i][j].printAgentClusterState();
      //     }
      //     std::cout << std::endl;
      //   }
      //   std::cout << std::endl;
      x.printField(this->Field);
    }
  }
};
