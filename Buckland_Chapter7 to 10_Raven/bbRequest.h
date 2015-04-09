#ifndef BBREQUEST_H
#define BBREQUEST_H
#pragma warning (disable:4786)

#include "Raven_Bot.h"

struct offer
{
	Raven_Bot* sender;
	double cost;
};

enum {help_defend_flag, help_capture_flag};

enum {now, urgent, please, ifyoucan};

class bbRequest
{
private:
	Raven_Bot* rBot;
	int type;
	offer bestOffer;
	int urgency;
public:
	bbRequest(Raven_Bot* owner) {rBot = owner; bestOffer.sender = NULL; bestOffer.cost = -1;}
	void setType(int val){type = val;}
	int getType(){return type;}
	offer getBestOffer() {return bestOffer;}
	void setBestOffer(Raven_Bot* pBot, double cost) {bestOffer.sender = pBot; bestOffer.cost = cost;}
	Raven_Bot* getOwner() {return rBot;}
	void setUrgency(int val){urgency = val;}
	int getUrgency(){return urgency;}
	//double calculate();
};

#endif