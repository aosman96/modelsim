#ifndef _DSGN_DELETE_H
#define _DSGN_DELETE_H
#include "Action.h"
#include <string>
#include <vector>
#include <unordered_set>
using std::string;
using std::vector;
using std::unordered_set;
class InputPin;
class OutputPin;
class Component;
class Connection;

class Delete:public Action
{
	vector <Component*> SelectComponents;
	unordered_set<Connection*> AllConnections;//For Undo
	bool undone;
	int count;
public:
	Delete(ApplicationManager *pApp);
	virtual ~Delete(void);

	//Reads parameters required for action to Execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif 