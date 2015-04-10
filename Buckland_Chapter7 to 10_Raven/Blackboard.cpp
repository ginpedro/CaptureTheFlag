#include "Blackboard.h"
#include "../Common/Debug/DebugConsole.h"


Blackboard::Blackboard()
{
	newreqAvaliable = false;	
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
			if ((*it)->getUrgency() == failed)
			{//REMOVE NAO ESTA DANDO CERTO
				//reqList.remove(*it);
				//debug_con << "removido request, " << reqList.size() << " no quadro \n";
			}
			if ((*it)->getUrgency() != now && (*it)->getUrgency() != failed)
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
				if (((*it)->getBestOffer().cost != -1) && ((*it)->getStatus() == unaccepted) && ((*it)->getUrgency() == now))
				{//se alguem ja ofereceu os servicos e o prazo esta no limite, pegue o que estiver registrado
					(*it)->setStatus(inprogress);	
					debug_con << "--request: custo " << (*it)->getBestOffer().cost << " no quadro, estado "<< (*it)->getStatus() << "\n";
				}else
				{//se ninguem aceitou, marque como falha
					(*it)->setUrgency(failed);					
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