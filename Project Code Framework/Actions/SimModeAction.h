#ifndef _SIM_MODE_CLK_H
#define _SIM_MODE_CLK_H

#include "Action.h"
class Component;

class SimModeAction:public Action
{
	Component* comp;
public:
	SimModeAction(ApplicationManager *pApp);
	virtual ~SimModeAction(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};


#endif