#include "EditAction.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Components\Connection.h"

Edit::Edit(ApplicationManager *pApp):Action(pApp)
{
	SelectComponents=pApp->GetSelectedComponentList();
	usrcancel=false;
}

Edit::~Edit(void)
{
}

void Edit::ReadActionParameters()
{
	Output* pOut=pManager->GetOutput();
	Input* pIn=pManager->GetInput();
	Label = SelectComponents[0]->GetLabel();
	Label = pIn->GetString(pOut,"Please Enter Label (Press Esc to cancel) : ",Label);
	if(Label=="")
	{
		usrcancel=true;
		return;
	}
}

void Edit::Execute()
{
	if(SelectComponents.size()==0)return;
	Output* pOut=pManager->GetOutput();
	Input* pIn=pManager->GetInput();
	ReadActionParameters();
	if(usrcancel)
	{
		CanBeUndone=false;
		pOut->PrintMsg("Operation Cancelled");
		return;
	}
	
	OrignalLabels.push_back(SelectComponents[0]->GetLabel());
	SelectComponents[0]->SetLabel(Label);

	for(UINT i=1;i<SelectComponents.size();i++)
	{
		OrignalLabels.push_back(SelectComponents[i]->GetLabel());
		SelectComponents[i]->SetLabel(Label+"_"+to_string(i));
	}

	CanBeUndone=true;
	pOut->PrintMsg("Ready");
}

void Edit::Undo()
{
	for(UINT i=0;i<SelectComponents.size();i++)
		SelectComponents[i]->SetLabel(OrignalLabels[i]);
	pManager->GetOutput()->PrintMsg("Undo Rename");
}

void Edit::Redo()
{
	SelectComponents[0]->SetLabel(Label);

	for(UINT i=1;i<SelectComponents.size();i++)
		SelectComponents[i]->SetLabel(Label+"_"+to_string(i));
	pManager->GetOutput()->PrintMsg("Redo Rename");
}


