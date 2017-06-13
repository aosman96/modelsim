#ifndef _SAVEFILE_ACT_H
#define _SAVEFILE_ACT_H
#include "Action.h"

#include <string>
using std::string;

class SaveFileAction:public Action
{
	string FileName;
	bool save;
public:
	SaveFileAction(ApplicationManager *pApp);
	virtual ~SaveFileAction(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};


#endif