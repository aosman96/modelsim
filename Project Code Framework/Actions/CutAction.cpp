#include "CutAction.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"

Cut::Cut(ApplicationManager *pApp):Action(pApp),undone(false)
{
	SelectComponents=pApp->GetSelectedComponentList();
	CanBeUndone=true;
}

void Cut::ReadActionParameters()
{
}

void Cut::Execute()
{
	vector<Component*> list;
	vector<Component*> oldlist;
	vector <Connection*> CompCons;
	Component* c;
	Connection* con;
	Output* pOut=pManager->GetOutput();
	count=0;
	
	pManager->ResetSelectedComponentList();
	
	UINT i=0,j=0;
	
	oldlist=pManager->GetClipBoard();
	
	//Remove Connections first from the selection list
	while(i<SelectComponents.size())
	{
		con=dynamic_cast<Connection*> (SelectComponents[i]);
		if(con)
			SelectComponents.erase(SelectComponents.begin()+i);
		else
			i++;
	}

	for(auto Selected:SelectComponents)
	{
		c=Selected->CreateCopy();
		list.push_back(c);
		CompCons=Selected->GetAllConnections();
		for(auto CompConnection:CompCons)
		{
			CompConnection->Disconnet();
			AllConnections.push_front(CompConnection);
			pManager->RemoveByPTR(CompConnection);
		}
		pManager->RemoveByPTR(Selected);
		count++;
	}

	pManager->ResetSelectedComponentList();
	
	if(count==0)
	{
		pOut->PrintMsg("Ignored");
		CanBeUndone=false;
	}
	else{
		for(auto& c:oldlist)
			delete c;

		pManager->SetClipBoard(list);
		pOut->PrintMsg(to_string(count)+" item(s) cut to the clipboard");
		UI.enable_paste=true;
		CanBeUndone=true;
	}
	UI.enable_copy_cut_delete=false;
	UI.enable_edit=false;
	UI.enable_editconn=false;
}

void Cut::Undo()
{
	for(auto c:SelectComponents)
		pManager->AddComponent(c);
	

	for(auto it:AllConnections)
	{
		pManager->AddComponent(it);
		it->Reconnect();
	}

	undone=true;
	pManager->GetOutput()->PrintMsg(to_string(count)+" item(s) restored");
}

void Cut::Redo()
{
	for(auto& c:SelectComponents)
		pManager->RemoveByPTR(c);
	

	for(auto& it:AllConnections)
	{
		pManager->RemoveByPTR(it);
		it->Disconnet();
	}

	undone=false;
	pManager->GetOutput()->PrintMsg(to_string(count)+" item(s) cut to the clipboard");
}

Cut::~Cut(void)
{
	if(!undone)
	{
		for(auto& c:SelectComponents)
			delete c;
	
		for(auto& it:AllConnections)
			delete it;
	}
}