#ifndef _DSGN_SELECTION_H
#define _DSGN_SELECTION_H
#include "Action.h"
#include "../Defs.H"
#include <vector>
using std::vector;
class Component;

class Select:public Action
{
	vector<Component*> SelectComponents;
	DesignSelectActions act;
	GraphicsInfo RectangleArea;
public:
	Select(ApplicationManager *pApp);
	virtual ~Select(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif 