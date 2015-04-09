#ifndef BLACKBOARD_H
#define BLACKBOARD_H
#pragma warning (disable:4786)

#include "bbRequest.h"

class Blackboard
{
private:
	std::list<bbRequest> reqList;
public:
	Blackboard();
	void postRequest(bbRequest req);
	std::list<bbRequest*> getNowRequests();
	std::list<bbRequest*> getAllRequests();
	void Update();
};

#endif