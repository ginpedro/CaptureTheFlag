#ifndef BBREQUEST_H
#define BBREQUEST_H
#pragma warning (disable:4786)

#include "Raven_Bot.h";

struct offer
{
	Raven_Bot* sender;
	double cost;
}

enum {help_defend_flag, help_capture_flag};

class bbRequest
{
private:
	int type;
	offer bestOffer;
public:
	bbRequest();
	setType(int val){type = val;};
	getType(){return type;};
	//double calculate();
}

#endif