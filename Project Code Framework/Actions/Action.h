#ifndef _ACTION_H
#define _ACTION_H

class ApplicationManager; //forward class declaration


//Base class for all possible actions (abstract class)
class Action
{
protected:
	ApplicationManager *pManager;	//Actions needs AppMngr to do their job
	bool CanBeUndone;					//if this action can be undone
public:
	Action(ApplicationManager *pApp):CanBeUndone(false) { pManager = pApp; }	//constructor,assume all actions can not be undone unless otherwise stated
	bool CanBe_Undone(){return CanBeUndone;}
	//Reads parameters required for action to execute
	virtual void ReadActionParameters()=0;
	
	//Execute action (code depends on action type)
	virtual void Execute()=0;

	//To undo this action (code depends on action type)
	virtual void Undo()=0;

	//To redo this action (code depends on action type)
	virtual void Redo()=0;
	virtual ~Action(){};
};

#endif