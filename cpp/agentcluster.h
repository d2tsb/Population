#include "agent.h"
#include "Vector.h"

class AgentCluster

{

private:
  Vector<Agent> agents;

public:
  // cycle:
  // update weights,   //move and store last direction made
  //
  void updateWeights()
  {
    for (unsigned i = 0; i < agents.getSize(); i++)
    {
      for (unsigned j = 0; j < agents.getSize(); j++)
      {
        if (j != i)
        {
          agents[i].incrementGrade(agents[j].getGrade(), agents[j].getLastDirection());
        }
      }
    }
  }
  void makeMove()
  {
    for (unsigned i = 0; i < agents.getSize(); i++)
      this->agents[i].makeMove(); // will store last move made.
  }

  void fill(unsigned quantity, unsigned pos_x, unsigned pos_y)
  {
    agents.resize(quantity);
    agents.fill(Agent(pos_x, pos_y));
  }


  Float getQuantity()
  {
    return this->agents.getSize();
  }
  Float getGradeMedian()
  {
    Float res = 0;
    for (unsigned i = 0; i < agents.getSize(); i++)
    {
      res += agents[i].getGrade();
    }
    return res / ((this->getQuantity() == 0) ? 1 : this->getQuantity());
  }

  void remove(unsigned index);
  AgentCluster()
  {
    //std::cout << "I m made." << std::endl;
  }

  unsigned peak()
  {
    unsigned tempGrade = 0; 
    for (unsigned i = 0; i < agents.getSize(); i++)
    {
      const unsigned grade = agents[i].getGrade();
      if ( grade > tempGrade) 
      {
        tempGrade = grade; 
      }
    }
    return tempGrade; 
  }


  AgentCluster(const unsigned N)
  {
    try
    {
      this->agents.reserve(N);
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
    }
  }

  Agent getBack()
  {
    return this->agents.last();
  }
  void PopBack()
  {
    this->agents.pop_back();
  }
  bool empty()
  {
    return agents.empty(); 
  }

  unsigned amountOfAgents()
  {
    return this->agents.getSize(); 
  }
  void PushBack(Agent a)
  {
    this->agents.push_back(a);
  }

  void printAgentClusterState()
  {
    // Float QuantityRatio = this->getQuantity() / MAXQUANTITY;
    unsigned GradeAverage = ((unsigned)this->getGradeMedian());
    //std::cout << amountOfAgents();
    std::cout << GradeAverage;
    /*
    if (GradeAverage < 5)
    {
      setTextColor(BLUE_TXT);
      wprintf(L"\u2588");
    }
    else if (GradeAverage < 10)
    {
      setTextColor(CYAN_TXT);
      wprintf(L"\u2588");
    }

    else if (GradeAverage < 20)
    {
      setTextColor(GREEN_TXT);
      wprintf(L"\u2588");
    }
    else if (GradeAverage < 40)
    {
      setTextColor(YELLOW_TXT);
      wprintf(L"\u2588");
    }
    else if (GradeAverage < 80)
    {

      setTextColor(MAGENTA_TXT);
      wprintf(L"\u2588");
    }
    else if (GradeAverage > 100)
    {
      setTextColor(RED_TXT);
      wprintf(L"\u2588");
    }

    resetColor();
  */
  }
};
