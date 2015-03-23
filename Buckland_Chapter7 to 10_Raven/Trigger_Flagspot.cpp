#include "Trigger_Flagspot.h"
#include "misc/Cgdi.h"
#include "misc/Stream_Utility_Functions.h"
#include <fstream>
#include "lua/Raven_Scriptor.h"
#include "constants.h"
#include "Raven_ObjectEnumerations.h"


///////////////////////////////////////////////////////////////////////////////
Trigger_Flagspot::Trigger_Flagspot(std::ifstream& datafile):
      
     Trigger<Raven_Bot>(GetValueFromStream<int>(datafile))
{
  Read(datafile);
}


void Trigger_Flagspot::Try(Raven_Bot* pBot)
{
  if (isActive() && isTouchingTrigger(pBot->Pos(), pBot->BRadius()))
  {
	//NEW: Dizer que a bandeira foi capturada.
    //pBot->IncreaseHealth(m_iHealthGiven);
  } 
}


void Trigger_Flagspot::Render()
{
  if (isActive())
  {
    gdi->BlackPen();
	if (m_iOwnerTeam == 1) {gdi->RedBrush();}
	if (m_iOwnerTeam == 2) {gdi->BlueBrush();}
    const int sz = 5;
    gdi->Rect(Pos().x-sz, Pos().y-sz, Pos().x+sz+1, Pos().y+sz+1);
    gdi->BlackPen();
    gdi->Line(Pos().x-sz, Pos().y+sz, Pos().x-sz, Pos().y+sz+sz);
    //gdi->Line(Pos().x-sz, Pos().y, Pos().x+sz+1, Pos().y);
  }
}


void Trigger_Flagspot::Read(std::ifstream& in)
{
  double x, y, r;
  int GraphNodeIndex;
  int team;

  in >> x >> y  >> r >> GraphNodeIndex >> team;

  SetPos(Vector2D(x,y)); 
  SetBRadius(r);
  SetGraphNodeIndex(GraphNodeIndex);
  m_iOwnerTeam = team;

  //create this trigger's region of fluence
  AddCircularTriggerRegion(Pos(), script->GetDouble("DefaultGiverTriggerRange"));

  //SetRespawnDelay((unsigned int)(script->GetDouble("Health_RespawnDelay") * FrameRate));
  SetEntityType(type_flag);
}
