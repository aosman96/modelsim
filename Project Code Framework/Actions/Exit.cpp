#include "Exit.h"
#include "..\ApplicationManager.h"
#include "SaveFileAction.h"  

Exit::Exit(ApplicationManager *pApp):Action(pApp)
{
	save_file=false;
	CanBeUndone=false;
}

Exit::~Exit(void)
{
}

void Exit::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	int ans=0;	
	if(UI.enable_save)
		ans=pOut->Display_MessageBox("Do you want to save changes to \"" + (UI.filename=="" ? "Untitled" : UI.filename) + "\" ?","Logic Simulator",MB_YESNO|MB_ICONQUESTION);
	if(ans==IDYES)
		save_file=true;
}

void Exit::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	SaveFileAction* SaveAct;

	if(save_file)
	{
		SaveAct=new SaveFileAction(this->pManager);
		SaveAct->Execute();
		delete SaveAct;
	}
}

void Exit::Undo()
{}

void Exit::Redo()
{}


