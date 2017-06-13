#ifndef _CHNGSIM_H
#define _CHNGSIM_H

#include "Action.h"


class ChangeToSimulation:public Action
{

public:
	ChangeToSimulation(ApplicationManager *pApp);
	virtual ~ChangeToSimulation(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};


#endif