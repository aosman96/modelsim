#include "DeleteAction.h"
#include "..\ApplicationManager.h"  
#include "..\Components\Component.h"
#include "..\Components\Connection.h"

Delete::Delete(ApplicationManager *pApp):Action(pApp),undone(false)
{
	SelectComponents=pApp->GetSelectedComponentList();
	CanBeUndone=true;
}

void Delete::ReadActionParameters()
{
}

void Delete::Execute()
{
	vector <Connection*> CompCons;
	Connection* c;
	Output* pOut=pManager->GetOutput();
	count=0;
	
	pManager->ResetSelectedComponentList();

	//Sperate Connections from Components first
	UINT i=0,j=0;
	
	while(i<SelectComponents.size())
	{
		c=dynamic_cast<Connection*> (SelectComponents[i]);
		if(c)
		{
			AllConnections.insert(c);
			SelectComponents.erase(SelectComponents.begin()+i);
		}
		else
			i++;
	}

	for(auto Selected:SelectComponents)
	{
		CompCons=Selected->GetAllConnections();
		
		for(auto Connect:CompCons)
			AllConnections.insert(Connect);			
		
		pManager->RemoveByPTR(Selected);
		count++;
	}

	for(auto it:AllConnections)
	{
		pManager->RemoveByPTR(it);
		it->Disconnet();
	}

	count+=AllConnections.size();

	pOut->PrintMsg(to_string(count)+" item(s) Deleted");
	UI.enable_copy_cut_delete=false;
	UI.enable_edit=false;
	UI.enable_editconn=false;
}

void Delete::Undo()
{
	for(auto Comp:SelectComponents)
		pManager->AddComponent(Comp);
	

	for(auto it:AllConnections)
	{
		pManager->AddComponent(it);
		it->Reconnect();
	}

	undone=true;
	pManager->GetOutput()->PrintMsg(to_string(count)+" item(s) restored");
}

void Delete::Redo()
{
	for(auto Comp:SelectComponents)
		pManager->RemoveByPTR(Comp);
	

	for(auto it:AllConnections)
	{
		pManager->RemoveByPTR(it);
		it->Disconnet();
	}
	undone=false;
	pManager->GetOutput()->PrintMsg(to_string(count)+" item(s) Deleted");
}

Delete::~Delete(void)
{
	if(!undone)
	{
		for(auto& Comp:SelectComponents)
			delete Comp;
	
		for(auto& it:AllConnections)
			delete it;
	}
}
