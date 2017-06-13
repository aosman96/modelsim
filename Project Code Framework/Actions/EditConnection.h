#ifndef _EDIT_CONNECTION_H
#define _EDIT_CONNECTION_H

#include "action.h"
#include <vector>
#include "../Defs.H"
using std::vector;

class OutputPin;
class InputPin;
class Connection;

class EditConnection :public Action
{
private:
	bool usr_cancel;
	vector <Point> final_points;	//the edges of all wires
	vector <Point> Orig_points;	//the edges of all wires
	OutputPin* src;
	InputPin* des;
	OutputPin* Origsrc;
	InputPin* Origdes;
	Connection* conn;
public:
	EditConnection(ApplicationManager *pApp);
	virtual ~EditConnection(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();


};

#endif