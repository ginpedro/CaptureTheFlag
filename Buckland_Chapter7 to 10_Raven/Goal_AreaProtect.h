#ifndef GOAL_AP_H
#define GOAL_AP_H
#pragma warning (disable:4786)

#include "Goals/Goal.h"
#include "goals/Raven_Goal_Types.h"
#include "Raven_Bot.h"





class Goal_AreaProtect : public Goal<Raven_Bot>
{
private:

  Vector2D    m_vStrafeTarget;

  bool        m_bClockwise;

  Vector2D  GetStrafeTarget()const;


public:

  Goal_AreaProtect(Raven_Bot* pBot):Goal<Raven_Bot>(pBot, goal_spec_strafe),
                                        m_bClockwise(RandBool())
  {}


  void Activate();

  int  Process();

  void Render();

  void Terminate();
 
};






#endif
