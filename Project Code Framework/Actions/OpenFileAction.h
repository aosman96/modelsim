#ifndef _OPENFILE_ACT_H
#define _OPENFILE_ACT_H
#include "Action.h"

#include <string>
using std::string;

class OpenFileAction:public Action
{
	bool usrcancel;
	string FileName;
public:
	OpenFileAction(ApplicationManager *pApp);
	virtual ~OpenFileAction(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};


#endif