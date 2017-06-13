#include "ChangeToDesign.h"
#include "..\ApplicationManager.h"

ChangeToDesign::ChangeToDesign(ApplicationManager *pApp):Action(pApp)
{
	CanBeUndone=false;
}

ChangeToDesign::~ChangeToDesign(void)
{}

void ChangeToDesign::ReadActionParameters()
{}

void ChangeToDesign::Execute()
{
	pManager->DestroySimulationParameters();
	pManager->ResetCircuit();
	UI.AppMode=DESIGN;
	pManager->GetOutput()->PrintMsg("Ready");
}

void ChangeToDesign::Undo()
{}

void ChangeToDesign::Redo()
{}

