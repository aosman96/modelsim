#ifndef _EXIT_ACT_H
#define _EXIT_ACT_H

#include "Action.h"


class Exit:public Action
{
	bool save_file;
public:
	Exit(ApplicationManager *pApp);
	virtual ~Exit(void);

	//Reads parameters required for action to execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};


#endif