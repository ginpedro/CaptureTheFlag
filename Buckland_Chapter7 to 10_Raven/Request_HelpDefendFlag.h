#ifndef BBREQUEST_HDF_H
#define BBREQUEST_HDF_H
#pragma warning (disable:4786)

#include "bbRequest.h"

class Request_HelpDefendFlag: public bbRequest
{
private:
	
public:
	Request_HelpDefendFlag(Raven_Bot* owner);
	void calculatePrice(Raven_Bot* pBot, double distFlag, int hp);
};

#endif