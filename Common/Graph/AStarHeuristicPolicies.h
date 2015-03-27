#ifndef ASTAR_HEURISTIC_POLICIES_H
#define ASTAR_HEURISTIC_POLICIES_H
//-----------------------------------------------------------------------------
//
//  Name:   AStarHeuristicPolicies.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class templates defining a heuristic policy for use with the A*
//          search algorithm
//-----------------------------------------------------------------------------
#include "misc/utils.h"
#include "../../Buckland_Chapter7 to 10_Raven\Raven_Bot.h"
#include "../../Buckland_Chapter7 to 10_Raven\Raven_SensoryMemory.h"

//NEW: esse arquivo inteiro foi modificado. Todas as classes de funcoes heuristicas agora deve herdar da classe Heuristics
template<class graph_type>
class Heuristic
{
public:
	Heuristic(){}

    virtual double Calculate(const graph_type& G, int nd1, int nd2)=0;
};

//-----------------------------------------------------------------------------
//the euclidian heuristic (straight-line distance)
//-----------------------------------------------------------------------------
template <class graph_type>
class Heuristic_Euclid : public Heuristic<typename graph_type>
{
public:

  Heuristic_Euclid():Heuristic<graph_type>(){}

  //calculate the straight line distance from node nd1 to node nd2
  double Calculate(const graph_type& G, int nd1, int nd2)
  {
    return Vec2DDistance(G.GetNode(nd1).Pos(), G.GetNode(nd2).Pos());
  }
};

//-----------------------------------------------------------------------------
//this uses the euclidian distance but adds in an amount of noise to the 
//result. You can use this heuristic to provide imperfect paths. This can
//be handy if you find that you frequently have lots of agents all following
//each other in single file to get from one place to another
//-----------------------------------------------------------------------------
template <class graph_type>
class Heuristic_Noisy_Euclidian : public Heuristic<typename graph_type>
{
public:

  Heuristic_Noisy_Euclidian():Heuristic<graph_type>(){}

  //calculate the straight line distance from node nd1 to node nd2
  double Calculate(const graph_type& G, int nd1, int nd2)
  {
    return Vec2DDistance(G.GetNode(nd1).Pos(), G.GetNode(nd2).Pos()) * RandInRange(0.9f, 1.1f);
  }
};

//-----------------------------------------------------------------------------
//you can use this class to turn the A* algorithm into Dijkstra's search.
//this is because Dijkstra's is equivalent to an A* search using a heuristic
//value that is always equal to zero.
//-----------------------------------------------------------------------------
template <class graph_type>
class Heuristic_Dijkstra : public Heuristic<typename graph_type>
{
public:
  
  Heuristic_Dijkstra():Heuristic<graph_type>(){}
  
  double Calculate(const graph_type& G, int nd1, int nd2)
  {
    return 0;
  }
};


template<class graph_type>
class Heuristic_Avoid : public Heuristic<typename graph_type>
{
private: 
	Raven_Bot* runner;
	double dmax;

public:
	Heuristic_Avoid(Raven_Bot* pbot, double MaxDistAccept):Heuristic<graph_type>(){runner = pbot; dmax = MaxDistAccept;}
	double Calculate(const graph_type& G, int nd1, int nd2)
	{
		std::list<Raven_Bot*> SensedBots;
		SensedBots = runner->GetSensoryMem()->GetListOfRecentlySensedOpponents();

		double d = Vec2DDistance(G.GetNode(nd1).Pos(), G.GetNode(nd2).Pos());
		double dmaxSq = dmax*dmax;
		double dmaxCub = dmax*dmax*dmax;

		double dA;
		//double dB;
		double Ea = 0;
		//double Eb = 0
		double q;

		q = SensedBots.size();

		if (q == 0) {
			return d;//dSq / dmaxSq;
		}
		else {
			Vector2D posA = G.GetNode(nd2).Pos();
			//Vector2D posB = G.GetNode(nd2).Pos();

			std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
			for (curBot; curBot != SensedBots.end(); ++curBot) {
				if ((*curBot)->isAlive() && (*curBot != runner)) {
					q += 1;

					dA = Vec2DDistance((*curBot)->Pos(), posA);
					//dB = Vec2DDistance((*curBot)->Pos(), posB) - d;
					//
					//if (dB < (*curBot)->BRadius()) {
					//	dB = (*curBot)->BRadius();
					//}

					if (dA < dmax) {
						Ea += dmaxCub / (dA*dA);
					}
					else {
						Ea += dmaxSq / dA;
					}

					//if (dB <= dmax) {
					//	Eb += dmaxSq / (dB*dB);
					//}
				}
			}

			double W = Ea;//Eb - Ea;

			return d + W;//(dSq / dmaxSq) + (W / q);
		}
	}
};

#endif