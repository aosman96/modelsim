#ifndef _DSGN_MOVE_H
#define _DSGN_MOVE_H
#include "Action.h"
#include "../Defs.H"
#include <vector>
using std::vector;
class Component;

class Move:public Action
{
	vector<Component*> SelectComponents;
	GraphicsInfo CircuitRectangle;
	int deltaX,deltaY;
	int MovedItems;
	bool usrcancel;
	bool unsupported;
	void Drag();
	bool MoveItems(int dx,int dy);
	void GetSelectedCircuitCorners();
public:
	Move(ApplicationManager *pApp);
	virtual ~Move(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif 