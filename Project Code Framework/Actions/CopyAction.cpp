#include "CopyAction.h"
#include "..\ApplicationManager.h" 
#include "..\Components\Component.h"
#include "..\Components\Connection.h"

Copy::Copy(ApplicationManager *pApp):Action(pApp)
{
	SelectComponents=pApp->GetSelectedComponentList();
	CanBeUndone=false;
}

Copy::~Copy(void)
{
}

void Copy::ReadActionParameters()
{
}

void Copy::Execute()
{
	vector<Component*> list;
	vector<Component*> oldlist;
	Component* c;
	Output* pOut=pManager->GetOutput();
	
	int count=0;

	//Old List will be cleared
	oldlist=pManager->GetClipBoard();


	for(auto Selected:SelectComponents)
	{
		c=Selected->CreateCopy();
		if(c){
			list.push_back(c);
			count++;
		}
	}

	if(count==0)
	{
		pOut->PrintMsg("Ignored");
	}
	else{
		for(auto& c:oldlist)
			delete c;

		pManager->SetClipBoard(list);
		pOut->PrintMsg(to_string(count)+" item(s) copied to the clipboard");
		UI.enable_paste=true;
	}
}

void Copy::Undo()
{}

void Copy::Redo()
{}


