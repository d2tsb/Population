#include "agentcluster.h"
#include <ctime>


#define STDCOUTHI2 std::cout << "HI 2" << std::endl; 
#define STDCOUTHI3 std::cout << "HI 3" << std::endl; 

#define INDEXOUTOFBOUNDEXCEPTION 89

class field
{
  private:
    int x_max = BORDER_X_MAX;
    int x_min = BORDER_X_MIN;
    int y_max = BORDER_Y_MAX;
    int y_min = BORDER_Y_MIN;
    long iteration = 0;
    std::vector<std::vector<AgentCluster>> Field;
  public: 


  // get highest averageGrade / Grade median
  // update


  field(unsigned xMax, unsigned xMin,
        unsigned yMax, unsigned yMin)
  {
    this->x_max = xMax;
    this->x_min = xMin;
    this->y_max = yMax;
    this->y_max = yMin;
    std::cout << "i don't understand why you dont work .askidjalks " << std::endl; 
    try
    {

      std::vector<std::vector<AgentCluster>> temp ( x_max ); //, 
            //std::vector <AgentCluster> (y_max)); // does not work
      std::cout << temp.size() << std::endl; 

      for (unsigned i = 0; i < x_max; i++)
      {
        std::vector <AgentCluster> temp_inner;
        temp_inner.reserve(20); 
        std::cout << "capacity: " << temp_inner.capacity() << std::endl; 

        for (unsigned j = 0; j < y_max; j++)
        {
          temp_inner.push_back(AgentCluster());
        }
        std::cout << temp_inner.size() << std::endl; 
        temp.push_back(temp_inner);
      }
      
      
  // std::cout << "i don't understand why you dont work helloaosoooooo ?  . " << std::endl; 

      /*
      
      
      for (unsigned i = 0; i < x_max; i++)
        {
          std::vector<AgentCluster> temp;
          for (unsigned j = 0; j < y_max; j++)
          {
            temp.push_back(AgentCluster(0));
          }
      
          Field.push_back(temp);
        }
      */
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    
 }

  void InitNAgentsToIndex(unsigned N, unsigned x = 0, unsigned y = 0)
  {
    // x and y have to be in Range.
    if (x > x_max || x < x_min || y > y_max || y < y_min)
      throw INDEXOUTOFBOUNDEXCEPTION;

    Field[x][y] = AgentCluster(N);
  }

  void update()
  {
    for (int i = 0; i < Field.size(); i++)
    {
      for (int j = 0; j < Field[i].size(); j++)
      {
        if (iteration)
        {
          this->Field[i][j] /*x,y */.updateWeights();
          this->Field[i][j].makeMove();
          // einmal bitte umsortieren.
          // restructure
          for (int k = 0; k < this->Field[i][j].getQuantity(); ++k)
          {
            Agent temp = this->Field[i][j].getBack();
            position pos_temp = temp.getPosition();
            this->Field[pos_temp.x][pos_temp.y].PushBack(temp);
            this->Field[i][j].PopBack();
          } // moving the elements to the right cluster.
        }
      }
    }
    ++iteration;
  }

  void TUI_LOOP()
  {
    for (;;)
    { 
      std::cout << "HI"; 
      update();
      std::cout << "HI"; 
      Sleep(1);

      //clear terminal
      //clearScreen(); 
      //write title - or description
      //print results.
      for (int i = 0; i < Field.size(); i++)
      {
        for (int j = 0; j < Field[i].size(); j++)
        {
            this->Field[i][j].printAgentClusterState();
        }
        std::cout << std::endl; 
      }
      std::cout << std::endl; 


    }
  }
};
