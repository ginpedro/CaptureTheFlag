#include "Blackboard.h"

Blackboard::Blackboard()
{
	
}

void Blackboard::postRequest(bbRequest r) {
	reqList.push_back(r);
}

std::list<bbRequest*> Blackboard::getNowRequests() {
	std::list<bbRequest*> pReq;
	for (std::list<bbRequest>::iterator it = reqList.begin(); it != reqList.end(); ++it) {
		if (it->getUrgency() == now) {
			pReq.push_back(&(*it));
		}
	}
	return pReq;
}

std::list<bbRequest*> Blackboard::getAllRequests() {
	std::list<bbRequest*> pReq;
	for (std::list<bbRequest>::iterator it = reqList.begin(); it != reqList.end(); ++it) {
		pReq.push_back(&(*it));
	}
	return pReq;
}

void Blackboard::Update()
{
	for (std::list<bbRequest>::iterator it = reqList.begin(); it != reqList.end(); ++it) {
		if (it->getUrgency() != now)
		{
			it->setUrgency(it->getUrgency()-1);
		}
	}	
}