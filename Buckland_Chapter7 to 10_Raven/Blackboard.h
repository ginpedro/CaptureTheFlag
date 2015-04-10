#ifndef BLACKBOARD_H
#define BLACKBOARD_H
#pragma warning (disable:4786)

#include "bbRequest.h"

class Blackboard
{
private:
	std::list<bbRequest*> reqList;//lista de requests
	bool newreqAvaliable;//se ha algum request novo desde o ultimo update
public:
	Blackboard();
	void postRequest(bbRequest* req);//adicionar request
	std::list<bbRequest*> getNowRequests();//pegar requests urgentes
	std::list<bbRequest*> getAllRequests();//pegar todos requests
	std::list<bbRequest*> getUnacceptedRequests();//pegar requests nao aceitados
	bool notPresent(int reqType);//verificar se um request ja nao foi postado (temporario)
	bool newReqAvaliable(){return newreqAvaliable;}
	void Update();//atualizar os contadores e estados dos requests, etc
};

#endif