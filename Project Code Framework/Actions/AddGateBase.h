#ifndef _ADD_GATE_BASE_H
#define _ADD_GATE_BASE_H

#include "action.h"
#include <string>
using std::string;

class Component;
struct GraphicsInfo;

class AddGate :	public Action
{
private:
	//Parameters for rectangular area to be occupied by the gate
	int Cx, Cy;	//Center point of the gate
	bool usrcancelled;
	bool undone;
	Component *pA;

protected:
	string desciption;
	virtual Component* CreateComponent(const GraphicsInfo& gfx)=0;
	virtual void DrawDrag(const GraphicsInfo& gfx)=0;

public:
	AddGate(ApplicationManager *pApp);
	virtual ~AddGate(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();

	
};

#endif