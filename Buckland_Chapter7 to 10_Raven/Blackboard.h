#ifndef BLACKBOARD_H
#define BLACKBOARD_H
#pragma warning (disable:4786)

#include "bbRequest.h"
#include "Raven_Map.h"

class Raven_Game;


class Blackboard
{
private:
	std::list<bbRequest*> reqList;//lista de requests
	bool newreqAvaliable;//se ha algum request novo desde o ultimo update
	std::list<Raven_Bot*> bots;
	std::list<Raven_Bot*> ebots;
	rectMapRegion base;
	rectMapRegion flag;
	//rectMapRegion side;
	rectMapRegion ebase;
	rectMapRegion eflag;
	//rectMapRegion eside;

public:
	Blackboard();
	void postRequest(bbRequest* req);//adicionar request
	std::list<bbRequest*> getNowRequests();//pegar requests urgentes
	std::list<bbRequest*> getAllRequests();//pegar todos requests
	std::list<bbRequest*> getUnacceptedRequests();//pegar requests nao aceitados
	bool notPresent(int reqType);//verificar se um request ja nao foi postado (temporario)
	bool newReqAvaliable(){return newreqAvaliable;}
	void Update();//atualizar os contadores e estados dos requests, etc
	void SetConf(int team, Raven_Game* world);

	void Arbitrate();

	bool regionContains(rectMapRegion reg, Vector2D p)
	{
		  if ((p.x > reg.x0) && (p.y > reg.y0) && (p.x < (reg.x0+reg.xsize)) && (p.y < (reg.y0+reg.ysize)))
		  {
			return true;
		  }else
		  {
			return false;
		  }
	}
};

#endif