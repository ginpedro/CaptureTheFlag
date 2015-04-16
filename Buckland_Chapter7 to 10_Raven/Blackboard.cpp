#include "Blackboard.h"
#include "../Common/Debug/DebugConsole.h"

#include "Raven_Game.h"


Blackboard::Blackboard()
{
	newreqAvaliable = false;	
}

void Blackboard::SetConf(int team, Raven_Game* world)
{
	newreqAvaliable = false;
	std::list<Raven_Bot*> tmp = world->GetAllBots();
	for (std::list<Raven_Bot*>::const_iterator it = tmp.begin(); it != tmp.end(); ++it)
	{
		if ((*it)->getTeam() == team)
		{
			bots.push_back(*it);
		}else
		{
			ebots.push_back(*it);
		}
	}
	std::list<rectMapRegion> reg = world->GetMap()->getRegions();
	int eteam;
	if (team == 1) {eteam = 2;} else {eteam = 1;}
	Vector2D basepoint = world->GetMap()->GetTeamSpawnpoint(team);
	Vector2D flagpoint = world->GetMap()->GetFlagpoint(team);
	Vector2D ebasepoint = world->GetMap()->GetTeamSpawnpoint(eteam);
	Vector2D eflagpoint = world->GetMap()->GetFlagpoint(eteam);
	for (std::list<rectMapRegion>::const_iterator it = reg.begin(); it != reg.end(); ++it)
	{
		if (regionContains(*it,basepoint))
		{
			base = *it;//regiao da base
		}
		if (regionContains(*it,flagpoint))
		{
			flag = *it;//regiao da flag
		}	
		if (regionContains(*it,ebasepoint))
		{
			ebase = *it;//regiao da base inimiga
		}
		if (regionContains(*it,eflagpoint))
		{
			eflag = *it;//regiao da flag inimiga
		}
	}
	//for (std::list<rectMapRegion>::const_iterator it = reg.begin(); it != reg.end(); ++it)
	//{
	//	//if (regionContains(*it,Vector2D(base.x0+1,) {side = *it;}
	//	
	//}


}

void Blackboard::postRequest(bbRequest* r) {
	reqList.push_back(r);
	newreqAvaliable = true;
	debug_con << "adicionado request, " << reqList.size() << " no quadro \n";
}

std::list<bbRequest*> Blackboard::getNowRequests() {
	std::list<bbRequest*> pReq;
	for (std::list<bbRequest*>::iterator it = reqList.begin(); it != reqList.end(); ++it) {
		if ((*it)->getUrgency() == now) {
			pReq.push_back(*it);
		}
	}
	return pReq;
}

std::list<bbRequest*> Blackboard::getAllRequests() {
	return reqList;
}

std::list<bbRequest*> Blackboard::getUnacceptedRequests()
{	
	std::list<bbRequest*> pReq;
	if (!reqList.empty())
	{
		for (std::list<bbRequest*>::iterator it = reqList.begin(); it != reqList.end(); ++it) {
			if ((*it)->getStatus() == unaccepted)
			{
				pReq.push_back(*it);
			}
		}	
	}
	return pReq;
}

void Blackboard::Update()
{
	bool newreqa = false;
	if (!reqList.empty())
	{
		for (std::list<bbRequest*>::iterator it = reqList.begin(); it != reqList.end(); ++it) {
			//if ((*it)->getStatus() == failed)
			//{//REMOVE NAO ESTA DANDO CERTO
			//	//reqList.remove(*it);
			//	//debug_con << "removido request, " << reqList.size() << " no quadro \n";
			//}
			if ((*it)->getUrgency() != now /*&& (*it)->getStatus() != failed*/)
			{
				(*it)->setUrgency((*it)->getUrgency()-1);
				debug_con << "--request de urgencia " << (*it)->getUrgency() << " no quadro, estado "<< (*it)->getStatus() << "\n";
				if ((*it)->getNumSent() != (*it)->getNumRec())
				{
					newreqa = true;
				}
			}
			else
			{
				if (((*it)->getBestOffer().cost != -1) && ((*it)->getStatus() == unaccepted)/* && ((*it)->getUrgency() == now)*/)
				{//se alguem ja ofereceu os servicos e o prazo esta no limite, pegue o que estiver registrado
					(*it)->setStatus(inprogress);	
					debug_con << "--request: custo " << (*it)->getBestOffer().cost << " no quadro, estado "<< (*it)->getStatus() << "\n";
				}else
				{//se ninguem aceitou, marque como falha <--- remover
					//(*it)->setStatus(failed);
					//reqList.erase(it);
					//TODO: MARCAR PARA REMOVER
				}
				
			}
		}	
	}
	newreqAvaliable = newreqa;
}

bool Blackboard::notPresent(int reqType)
{
  if (!reqList.empty())
  { //debug_con << "verificando requests, " << reqList.size() << " no quadro";
	for (std::list<bbRequest*>::iterator it = reqList.begin(); it != reqList.end(); ++it) {
		if ((*it)->getType() == reqType) {
			return false;
		}
	}    
  }
  return true;
}

void Blackboard::Arbitrate()
{
	
	for (std::list<Raven_Bot*>::const_iterator it = bots.begin(); it != bots.end(); ++it)
	{
		
	}
	//pegar codigo dos goal evaluators (que serao usados) e adicionar outros calculos
	//calcular o valor de desirability de um goal para um bot, para todos os bots
	//pode-se levar em consideracao os goals de outros bots e requests no quadro para ajudar o calculo
	//usar o goalthink do bot (funcao set goal do goal evaluator) para setar o novo goal
	


}