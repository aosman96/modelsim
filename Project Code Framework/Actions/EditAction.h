#ifndef _DSGN_EDIT_H
#define _DSGN_EDIT_H
#include "Action.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
class InputPin;
class OutputPin;
class Component;

class Edit:public Action
{
	string Label;
	vector<string> OrignalLabels;
	vector <Component*> SelectComponents;
	bool usrcancel;

public:
	Edit(ApplicationManager *pApp);
	virtual ~Edit(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif 