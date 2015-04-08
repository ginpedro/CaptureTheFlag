#include "Request_HelpDefendFlag.h";

Request_HelpDefendFlag::Request_HelpDefendFlag(Raven_Bot* owner):bbRequest(owner)
{
	setType(help_defend_flag);
}

void Request_HelpDefendFlag::calculatePrice(Raven_Bot* pBot, double distFlag,int hp)
{
	double rst = distFlag/hp;
	offer b = getBestOffer();

	if ((b.cost == -1)||(rst < b.cost)){
		setBestOffer(pBot, rst);
	}
	
}