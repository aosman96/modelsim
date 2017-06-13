#ifndef _ADD_Led_H
#define _ADD_Led_H

#include "action.h"

class Led;

class AddLed : public Action
{
private:
	//Parameters for rectangular area to be occupied by the Led
	int Cx, Cy;	//Center point of the Led
	bool usercancelled;
	Led* pA;
	bool undone;
	
public:
	AddLed(ApplicationManager *pApp);
	virtual ~AddLed(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif