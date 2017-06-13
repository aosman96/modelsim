#ifndef _ADD_CONNECTION
#define _ADD_CONNECTION

#include "action.h"
#include <vector>
#include "../Defs.H"
using std::vector;

class OutputPin;
class InputPin;
class Connection;

class AddConnection :public Action
{
private:
	bool usr_cancel;
	vector <Point> final_points;	//the edges of all wires
	OutputPin* src;
	InputPin* des;
	Connection *pA;
	bool undone;
	
public:
	AddConnection(ApplicationManager *pApp);
	virtual ~AddConnection(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif