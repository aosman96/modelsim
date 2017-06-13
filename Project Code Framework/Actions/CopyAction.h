#ifndef _DSGN_COPY_H
#define _DSGN_COPY_H
#include "Action.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
class InputPin;
class OutputPin;
class Component;

class Copy:public Action
{
	vector <Component*> SelectComponents;
public:
	Copy(ApplicationManager *pApp);
	virtual ~Copy(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif 