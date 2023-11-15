#include "agent.h"


class AgentCluster

{

  private: 
   std::vector<Agent> agents; 
  public: 

  //cycle:
  //update weights,   //move and store last direction made
  // 
  void updateWeights(){
    for ( unsigned i = 0; i < agents.size(); i++ )
    {
      for ( unsigned j = 0; j < agents.size(); j++ )
      {
        if ( j != i)
        {
          agents[i].incrementGrade(agents[j].getGrade(), agents[j].getLastDirection());
        }
      }
    }
  }
  void makeMove()
  {
    for ( unsigned i = 0; i < agents.size(); i++)
      this->agents[i].makeMove(); //will store last move made.
  }

  Float getQuantity() 
  {
    return this->agents.size(); 
  }
  Float getGradeMedian() 
  {
    Float res = 0; 
    for ( unsigned i = 0; i < agents.size(); i++)
    {
      res += agents[i].getGrade(); 
    }
    return res / (this->getQuantity() == 0) ? 1 : this->getQuantity(); 
  }

  void remove(unsigned index)
  {


  }
  AgentCluster()
  {
    std::cout << "I m made." << std::endl; 

  }

  AgentCluster ( const unsigned N )
  {

    std::cout << "I m madddqawsdasdasde 2." << std::endl; 
    try
    {
      /* code */
    this->agents.reserve(20);
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
    
    /*
    

     for ( unsigned i = 0; i < N; i++)
    {
      this->agents.push_back(Agent(0));
    }

    
    */
     }


  Agent getBack()
  {
    return this->agents.back(); 
  }

  void PopBack()
  {
    this->agents.pop_back(); 
  }

  void PushBack(Agent a)
  {
    this->agents.push_back(a); 
  }



  void printAgentClusterState()
  {
    //Float QuantityRatio = this->getQuantity() / MAXQUANTITY; 
    unsigned GradeAverage = ((unsigned) this->getGradeMedian()) ; 

    
    if ( GradeAverage < 5)
    {
      setTextColor(BLUE_TXT);
      wprintf(L"\u2588");
    }
    else if (GradeAverage < 10) {
      setTextColor(CYAN_TXT);
      wprintf(L"\u2588");
 

    }

    else if (GradeAverage < 20) {
     setTextColor(GREEN_TXT);
      wprintf(L"\u2588");
 


    }
    else if (GradeAverage < 40) {
     setTextColor(YELLOW_TXT);
      wprintf(L"\u2588");
 

    }
    else if (GradeAverage < 80) {

     setTextColor(MAGENTA_TXT);
      wprintf(L"\u2588");
 
    }
    else if (GradeAverage > 100) {
     setTextColor(RED_TXT);
      wprintf(L"\u2588");
 

    }

      resetColor(); 





  }
};
