#ifndef _ADD_Switch_H
#define _ADD_Switch_H

#include "action.h"

class Switch;

class AddSwitch : public Action
{
private:
	//Parameters for rectangular area to be occupied by the switch
	int Cx, Cy;	//Center point of the switch
	bool usercancelled;
	bool undone;
	
	Switch* pA;
public:
	AddSwitch(ApplicationManager *pApp);
	virtual ~AddSwitch(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif