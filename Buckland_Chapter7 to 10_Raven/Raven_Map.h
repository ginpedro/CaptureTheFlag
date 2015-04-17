#ifndef RAVEN_MAP_H
#define RAVEN_MAP_H
#pragma warning (disable:4786)
//-----------------------------------------------------------------------------
//
//  Name:   Raven_Map.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   this class creates and stores all the entities that make up the
//          Raven game environment. (walls, bots, health etc)
//
//          It can read a Raven map editor file and recreate the necessary
//          geometry.
//-----------------------------------------------------------------------------
#include <vector>
#include <string>
#include <list>
#include "graph/SparseGraph.h"
#include "2d/Wall2D.h"
#include "triggers/Trigger.h"
#include "Raven_Bot.h"
#include "Graph/GraphEdgeTypes.h"
#include "Graph/GraphNodeTypes.h"
#include "misc/CellSpacePartition.h"
#include "triggers/TriggerSystem.h"

class BaseGameEntity;
class Raven_Door;

struct rectMapRegion
{
	int x0,y0,xsize,ysize;
	Vector2D center;
};
struct circleMapRegion
{
	double radius;
	Vector2D center;
};

class Raven_Map
{
public:

  typedef NavGraphNode<Trigger<Raven_Bot>*>         GraphNode;
  typedef SparseGraph<GraphNode, NavGraphEdge>      NavGraph;
  typedef CellSpacePartition<NavGraph::NodeType*>   CellSpace;

  typedef Trigger<Raven_Bot>                        TriggerType;
  typedef TriggerSystem<TriggerType>                TriggerSystem;
  
private:
	std::list<rectMapRegion> regions;
	std::list<circleMapRegion> dangerzones;

  //the walls that comprise the current map's architecture. 
  std::vector<Wall2D*>                m_Walls;

  //trigger are objects that define a region of space. When a raven bot
  //enters that area, it 'triggers' an event. That event may be anything
  //from increasing a bot's health to opening a door or requesting a lift.
  TriggerSystem                      m_TriggerSystem;    

  //this holds a number of spawn positions. When a bot is instantiated
  //it will appear at a randomly selected point chosen from this vector
  std::vector<Vector2D>              m_SpawnPoints;

  //NEW: Guardar referencias a pontos importantes.
  std::list<Vector2D>			 team1spawn;//pontos de spawn team 1
  std::list<Vector2D>			 team2spawn;//pontos de spawn team 2
  Vector2D						 team1flag;//ponto da bandeira team 1
  Vector2D						 team2flag;//ponto da bandeira team 2


  //a map may contain a number of sliding doors.
  std::vector<Raven_Door*>           m_Doors;
 
  //this map's accompanying navigation graph
  NavGraph*                          m_pNavGraph;  

  //the graph nodes will be partitioned enabling fast lookup
  CellSpace*                        m_pSpacePartition;

  //the size of the search radius the cellspace partition uses when looking for 
  //neighbors 
  double                             m_dCellSpaceNeighborhoodRange;

  int m_iSizeX;
  int m_iSizeY;
  
  void  PartitionNavGraph();

  //this will hold a pre-calculated lookup table of the cost to travel from
  //one node to any other.
  std::vector<std::vector<double> >  m_PathCosts;


    //stream constructors for loading from a file
  void AddWall(std::ifstream& in);
  void AddSpawnPoint(std::ifstream& in);
  void AddHealth_Giver(std::ifstream& in);
  void AddWeapon_Giver(int type_of_weapon, std::ifstream& in);
  void AddDoor(std::ifstream& in);
  void AddDoorTrigger(std::ifstream& in);
  //NEW
  void AddFlag(std::ifstream& in);
  void Clear();
  
public:
  
  Raven_Map();  
  ~Raven_Map();

  void Render();

  //loads an environment from a file
  bool LoadMap(const std::string& FileName); 

  //adds a wall and returns a pointer to that wall. (this method can be
  //used by objects such as doors to add walls to the environment)
  Wall2D* AddWall(Vector2D from, Vector2D to);

  void    AddSoundTrigger(Raven_Bot* pSoundSource, double range);

  double   CalculateCostToTravelBetweenNodes(int nd1, int nd2)const;

  //returns the position of a graph node selected at random
  Vector2D GetRandomNodeLocation()const;
  
  
  void  UpdateTriggerSystem(std::list<Raven_Bot*>& bots);

  const Raven_Map::TriggerSystem::TriggerList&  GetTriggers()const{return m_TriggerSystem.GetTriggers();}
  const std::vector<Wall2D*>&        GetWalls()const{return m_Walls;}
  NavGraph&                          GetNavGraph()const{return *m_pNavGraph;}
  std::vector<Raven_Door*>&          GetDoors(){return m_Doors;}
  const std::vector<Vector2D>&       GetSpawnPoints()const{return m_SpawnPoints;}
  CellSpace* const                   GetCellSpace()const{return m_pSpacePartition;}
  Vector2D                           GetRandomSpawnPoint(){return m_SpawnPoints[RandInt(0,m_SpawnPoints.size()-1)];}
  int                                GetSizeX()const{return m_iSizeX;}
  int                                GetSizeY()const{return m_iSizeY;}
  int                                GetMaxDimension()const{return Maximum(m_iSizeX, m_iSizeY);}
  double                             GetCellSpaceNeighborhoodRange()const{return m_dCellSpaceNeighborhoodRange;}
  Vector2D			 GetTeamSpawnpoint(int team)
  {
	if (team == 1)
	{
		std::list<Vector2D>::const_iterator iter = team1spawn.begin();
		Vector2D ret = *iter;
		team1spawn.pop_front();
		team1spawn.push_back(ret);
		return ret;
	}
	else
	{
		std::list<Vector2D>::const_iterator iter = team2spawn.begin();
		Vector2D ret = *iter;
		team2spawn.pop_front();
		team2spawn.push_back(ret);
		return ret;
	}
  }
  Vector2D			 GetFlagpoint(int team)
  {
	if (team == 1)
	{
		return team1flag;
	}else
	{
		return team2flag;
	}
  }
  std::list<rectMapRegion> getRegions() { return regions; };
  std::list<circleMapRegion> getDZones() { return dangerzones; };
};



#endif