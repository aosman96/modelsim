#ifndef _DSGN_CUT_H
#define _DSGN_CUT_H
#include "Action.h"
#include <string>
#include <vector>
#include <forward_list>
using std::string;
using std::vector;
using std::forward_list;
class InputPin;
class OutputPin;
class Component;
class Connection;

class Cut:public Action
{
	vector <Component*> SelectComponents;
	forward_list<Connection*> AllConnections;//For Undo
	bool undone;
	int count;
public:
	Cut(ApplicationManager *pApp);
	virtual ~Cut(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif 