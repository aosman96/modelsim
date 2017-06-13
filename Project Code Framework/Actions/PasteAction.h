#ifndef _DSGN_PASTE_H
#define _DSGN_PASTE_H
#include "Action.h"
#include <string>
#include <vector>
using std::string;
using std::vector;
class InputPin;
class OutputPin;
class Component;
struct GraphicsInfo;

class Paste:public Action
{
	vector <Component*> Clipboard;
	bool undone;
	bool cancel;
	int count;
	void Drag(vector<Component*>& list);
	void GetRectangle(vector<Component*>& list,GraphicsInfo& rect); 
	bool CheckArea(vector<Component*>& list,int deltaX,int deltaY);
public:
	Paste(ApplicationManager *pApp);
	virtual ~Paste(void);

	//Reads parameters required for action to Execute
	virtual void ReadActionParameters();
	//Execute action (code depends on action type)
	virtual void Execute();

	virtual void Undo();
	virtual void Redo();
};

#endif 