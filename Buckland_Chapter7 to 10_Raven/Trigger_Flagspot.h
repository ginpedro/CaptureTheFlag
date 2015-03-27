#ifndef FLAG_HOLDER_H
#define FLAG_HOLDER_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:     Trigger_HealthGiver.h
//
//  Author:   Mat Buckland
//
//  Desc:     If a bot runs over an instance of this class its health is
//            increased. 
//
//-----------------------------------------------------------------------------
#include "../Common/Triggers/Trigger.h"
#include "Triggers/TriggerRegion.h"
#include <iosfwd>
#include "Raven_Bot.h"



class Trigger_Flagspot : public Trigger<Raven_Bot>
{
private:

  //the amount of health an entity receives when it runs over this trigger
  //int   m_iHealthGiven;
  
  int m_iOwnerTeam;

public:

  Trigger_Flagspot(std::ifstream& datafile);

  //if triggered, the bot's health will be incremented
  void Try(Raven_Bot* pBot);
  
  //draws a box with a red cross at the trigger's location
  void Render();

  void Read (std::ifstream& is);

  int GetTeamOwner(){return m_iOwnerTeam;}

  void Update()
  {
  
	/*if (!isActive())
    {
      SetActive();
    }
  */
  }
};



#endif