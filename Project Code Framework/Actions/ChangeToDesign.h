#ifndef _CHNGDSN_H
#define _CHNGDSN_H

#include "Action.h"


class ChangeToDesign:public Action
{
	
public:
	ChangeToDesign(ApplicationManager *pApp);
	virtual ~ChangeToDesign(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};


#endif