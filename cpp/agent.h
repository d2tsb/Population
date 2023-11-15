#include "defines.h"
#include <random>
#include <cmath>
#include "TUI.h"

#define RANDSTEPSIZE 0.01
#define HIGHESTGRADE 600000
#define BORDER_X_MAX 100
#define BORDER_Y_MAX 100
#define BORDER_X_MIN 0 
#define BORDER_Y_MIN 0
#define MAXQUANTITY 50

struct position
{
  unsigned x = 0; 
  unsigned y = 0; 

  position(unsigned x__, unsigned y__) : x(x__), y(y__)
  {}
  position(){}
};


#define Float float

enum DIRECTION
{
  NORTH,
  SOUTH,
  WEST,
  EAST,
  NO_DIRECTION
};


struct AgentDistribution
{ Float north_prob = 0.25;
  Float south_prob = 0.25;
  Float west_prob = 0.25;
  Float east_prob = 0.25;

  AgentDistribution( 
    Float np, Float sp, Float wp, Float ep
  ): north_prob(np), 
    south_prob(sp),
    west_prob(wp),
    east_prob(ep)
  {
    normalize(); 
  }
  AgentDistribution()
  {
    north_prob = south_prob = west_prob = east_prob = 0.25; 
  }


  void normalize()
  {
    const Float norm = std::sqrt(  
      std::pow(north_prob, 2)+ 
      std::pow(south_prob, 2)+ 
      std::pow(west_prob, 2)+ 
      std::pow(east_prob, 2)
    );
    north_prob /= norm; 
    south_prob /= norm; 
    west_prob /= norm; 
    east_prob /= norm; 
  }
};


#include <time.h>
   
std::random_device rd;
std::mt19937 gen(rd());
void seedGenerator()
{
  gen.seed(time(NULL));
}

DIRECTION dice (AgentDistribution ad)
{ 
  std::discrete_distribution<> d({
    ad.north_prob,
    ad.south_prob,
    ad.west_prob,
    ad.east_prob
  });
  switch ( d(gen) % 4)
  {
    case 0: 
  	  return NORTH; 
    case 1: 
      return SOUTH;
    case 2: 
      return WEST;
    case 3: 
      return EAST;

  }
  return NORTH; 
}



class Agent //typical Agent in the Population Game
{

  private:
    unsigned Grade = 1; 
    bool canIncrementGrade = 0; 
    unsigned stepsLeftToBeAbletoElevate = 5; 
    AgentDistribution ad = {0.25, 0.25, 0.25, 0.25}; 

    int pos_x = 0; 
    int pos_y = 0; 
    void incrementGrade__()
    {
      if (canIncrementGrade) 
        Grade == HIGHESTGRADE ? 0 : ++Grade; 
    }

    DIRECTION last_direction = NO_DIRECTION; 


  public: 
    void incrementGrade(float OtherGrade, DIRECTION lastDirection)
    {
      if (NO_DIRECTION)
      {
        return; //do nothing
      }
      if ( canIncrementGrade )
      {
        /*incrementGrade and update*/
        float tempGrade = this->Grade;  
        tempGrade += OtherGrade; 
        tempGrade = Grade/tempGrade; 

        DIRECTION last_direction_temp = last_direction == NO_DIRECTION ? dice(AgentDistribution()) : last_direction;

        if ( tempGrade > 0) //this has the stronger grade
        {
          //increment the probability of the last direction to
          switch(last_direction_temp)
          {
            case NORTH: 
              ad.north_prob += RANDSTEPSIZE; 
              ad.normalize();
              break; 

            case SOUTH:
              ad.south_prob+= RANDSTEPSIZE; 
              ad.normalize();
              break; 
            case WEST:
              ad.west_prob+= RANDSTEPSIZE; 
              ad.normalize();
              break;
            case EAST:
              ad.east_prob+= RANDSTEPSIZE; 
              ad.normalize();
              break;
          }
        }
        else { //other has the stronger grade
          float tempGrade = this->Grade;  
          tempGrade += OtherGrade; 
          tempGrade = Grade/tempGrade; 
          if ( tempGrade > 0) //this has the stronger grade
          {
            //increment the probability of the last direction to
            switch(last_direction_temp)
            {
              case NORTH: 
                ad.north_prob -= RANDSTEPSIZE; 
                ad.normalize();
                break; 

              case SOUTH:
                ad.south_prob-= RANDSTEPSIZE; 
                ad.normalize();
                break; 
              case WEST:
                ad.west_prob-= RANDSTEPSIZE; 
                ad.normalize();
                break;
              case EAST:
                ad.east_prob-= RANDSTEPSIZE; 
                ad.normalize();
                break;
            }
          }
        }
      }
      else {
        if ( stepsLeftToBeAbletoElevate > 0)
        {
          --stepsLeftToBeAbletoElevate;
        }
        else {
          canIncrementGrade = true; 
        }
      }

    }
    unsigned getGrade()
    {
     return Grade;  
    }
    DIRECTION getLastDirection()
    {
      return last_direction;
    }


    void makeMove()
    {
      DIRECTION rolled = dice(ad);

      switch (rolled)
      {
        case NORTH:
          ++pos_y;  
          pos_y > BORDER_Y_MAX ? --pos_y & reset() : pos_y; 
          this->last_direction = NORTH; 
          break; 
        case SOUTH:
          --pos_y;  
          pos_y < BORDER_Y_MIN ? ++pos_y & reset() : pos_y; 
          this->last_direction = SOUTH; 
          break; 
        case WEST:
          --pos_x;  
          pos_x > BORDER_X_MAX ? --pos_x & reset() : pos_x; 
          this->last_direction = WEST; 
          break; 
        case EAST:
          ++pos_x;  
          pos_x < BORDER_X_MIN ? --pos_x & reset() : pos_x; 
          this->last_direction = EAST; 
          break; 
        default:
          break; 
      }


    }

    unsigned reset()
    //after border was hit
    {
      //Grade = 1; 
      --Grade < 1 ? Grade++ : 0;  
      //canIncrementGrade = 0; 
      //stepsLeftToBeAbletoElevate = 5; 
      ad = AgentDistribution(); 

      /*
      pos_x = 0; 
      pos_y = 0; 
      last_direction = NORTH; 
      */
      return 0;

    }
    position getPosition()
    {
      return position(pos_x, pos_y);
    }

    Agent(int w)
    {}
    Agent()
    {}
};