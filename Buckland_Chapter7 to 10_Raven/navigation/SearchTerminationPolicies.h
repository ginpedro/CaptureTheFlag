#ifndef TERMINATION_POLICIES_H
#define TERMINATION_POLICIES_H
//-----------------------------------------------------------------------------
//
//  Name:   SearchTerminationPolicies.h
//
//  Author: Mat Buckland (www.ai-junkie.com)
//
//  Desc:   class templates to define termination policies for Dijkstra's
//          algorithm
//-----------------------------------------------------------------------------

#include "misc/utils.h"
#include "../Raven_Bot.h"
#include "../Raven_SensoryMemory.h"
#include "../Raven_Game.h"

template <class trigger_type, class graph_type>
class TerminatePolicy
{
public:
	TerminatePolicy(){}
	virtual bool isSatisfied(const graph_type& G, int target, int CurrentNodeIdx)=0;
};


//--------------------------- FindNodeIndex -----------------------------------

//the search will terminate when the currently examined graph node
//is the same as the target node.
template <class trigger_type, class graph_type>
class FindNodeIndex : public TerminatePolicy<typename trigger_type, typename graph_type>
{
public:
	FindNodeIndex():TerminatePolicy<trigger_type, graph_type>(){}
  bool isSatisfied(const graph_type& G, int target, int CurrentNodeIdx)
  {
    return CurrentNodeIdx == target;
  }
};

//--------------------------- FindActiveTrigger ------------------------------

//the search will terminate when the currently examined graph node
//is the same as the target node.
template <class trigger_type, class graph_type>
class FindActiveTrigger : public TerminatePolicy<typename trigger_type, typename graph_type>
{
public:
	FindActiveTrigger():TerminatePolicy<trigger_type, graph_type>(){}
  bool isSatisfied(const graph_type& G, int target, int CurrentNodeIdx)
  {
    bool bSatisfied = false;

    //get a reference to the node at the given node index
    const graph_type::NodeType& node = G.GetNode(CurrentNodeIdx);

    //if the extrainfo field is pointing to a giver-trigger, test to make sure 
    //it is active and that it is of the correct type.
    if ((node.ExtraInfo() != NULL) && 
         node.ExtraInfo()->isActive() && 
        (node.ExtraInfo()->EntityType() == target) )
    {    
      bSatisfied = true;
    }

    return bSatisfied;
  }
};


template <class trigger_type, class graph_type>
class FindSecurePlace : public TerminatePolicy<typename trigger_type, typename graph_type>
{
private:
	Raven_Bot* runner;
	std::list<Raven_Bot*> SensedBots;
	double dmax;

public:
	FindSecurePlace(Raven_Bot* pbot, double MaxDistAccept):TerminatePolicy<trigger_type, graph_type>(){
		runner = pbot;
		dmax = MaxDistAccept;
		SensedBots = runner->GetSensoryMem()->GetListOfRecentlySensedOpponents();
	}

	bool isSatisfied(const graph_type& G, int target, int CurrentNodeIdx) {
		//std::list<Raven_Bot*> SensedBots;
		//SensedBots = runner->GetSensoryMem()->GetListOfRecentlySensedOpponents();

		if (SensedBots.empty()) {return true;}

		Vector2D posA = G.GetNode(CurrentNodeIdx).Pos();
		Vector2D posB;

		double dmaxSq = dmax*dmax;
		double d;
		double E = 0;
		double q = 0;
		std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
		for (curBot; curBot != SensedBots.end(); ++curBot) {
			if ((*curBot)->isAlive() && (*curBot != runner)) {
				q += 1;
				posB = (*curBot)->Pos();
				d = Vec2DDistance(posA, posB);

				if (runner->GetWorld()->isLOSOkay(posA, posB)) {
					E += dmaxSq / (d*d);
				}
				else if (d < dmax) {
					E += dmax * (dmax-d) / (d*d);
				}
			}
		}
		if (q == 0) {return true;}
		else {
			return (E / q) < 0.5;
		}
	}
};

template <class trigger_type, class graph_type>
class FindSecureActiveTrigger : public TerminatePolicy<typename trigger_type, typename graph_type>
{
private:
	Raven_Bot* runner;
	std::list<Raven_Bot*> SensedBots;
	double dmax;

public:
	FindSecureActiveTrigger(Raven_Bot* pbot, double MaxDistAccept):TerminatePolicy<trigger_type, graph_type>(){
		runner = pbot;
		dmax = MaxDistAccept;
		SensedBots = pbot->GetSensoryMem()->GetListOfRecentlySensedOpponents();
	}

	bool isSatisfied(const graph_type& G, int target, int CurrentNodeIdx) {
		bool bSatisfied = false;

		//get a reference to the node at the given node index
		const graph_type::NodeType& node = G.GetNode(CurrentNodeIdx);

		//if the extrainfo field is pointing to a giver-trigger, test to make sure 
		//it is active and that it is of the correct type.
		if ((node.ExtraInfo() != NULL) && 
			 node.ExtraInfo()->isActive() && 
			(node.ExtraInfo()->EntityType() == target) )
		{    
			if (SensedBots.empty()) {return true;}

			Vector2D posA = G.GetNode(CurrentNodeIdx).Pos();
			Vector2D posB;

			double dmaxSq = dmax*dmax;
			double d;
			double E = 0;
			double q = 0;
			std::list<Raven_Bot*>::const_iterator curBot = SensedBots.begin();
			for (curBot; curBot != SensedBots.end(); ++curBot) {
				if ((*curBot)->isAlive() && (*curBot != runner)) {
					q += 1;
					posB = (*curBot)->Pos();
					d = Vec2DDistance(posA, posB);

					E += dmaxSq / (d*d);
				}
			}
			if (q == 0) {bSatisfied = true;}
			else {
				bSatisfied = (E / q) < 1;
			}
		}

		return bSatisfied;
	}
};
  
#endif