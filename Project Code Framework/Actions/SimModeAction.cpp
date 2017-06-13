#include "SimModeAction.h"
#include "..\ApplicationManager.h"
#include "..\Components\Switch.h"

SimModeAction::SimModeAction(ApplicationManager *pApp):Action(pApp),comp(NULL)
{
	CanBeUndone=false;
}

SimModeAction::~SimModeAction(void)
{}

void SimModeAction::ReadActionParameters()
{
	int x,y;
	Input* inputinterface=pManager->GetInput();
	inputinterface->GetLastPointClicked(x,y);
	comp=pManager->GetComponentAt(x,y);
}

void SimModeAction::Execute()
{
	Output* pOut=pManager->GetOutput();
	ReadActionParameters();

	if(!comp){
		pOut->PrintMsg("Simulation Started");
		return;
	}

	Switch*s=dynamic_cast<Switch*> (comp);
	
	string probe_msg;
	if(s)
	{
		s->toggle();
		pOut->PrintMsg("Switch \""+ s->GetLabel() + "\" toggled to "+(comp->GetOpStatus() ? "ON" : "OFF"));
		pManager->OperateCicuit();
	}
	else 
	{
		probe_msg=string(typeid(*comp).name())+", level: " +to_string(comp->getLevel()/2+1);
		probe_msg+=", Operation Status: ";
		probe_msg+=(comp->GetOpStatus() ? "HIGH" : "LOW");
		pOut->PrintMsg(probe_msg);
	}
}

void SimModeAction::Undo()
{}

void SimModeAction::Redo()
{}

