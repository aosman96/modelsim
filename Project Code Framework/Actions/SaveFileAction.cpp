#include "SaveFileAction.h"
#include "..\ApplicationManager.h"
#include <fstream>
using std::ofstream;

SaveFileAction::SaveFileAction(ApplicationManager *pApp):Action(pApp),FileName(UI.filename),save(true)
{
	CanBeUndone=false;
}

SaveFileAction::~SaveFileAction(void)
{
}

void SaveFileAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	if(FileName=="")
		save=pIn->GetSaveFilename(FileName);
}

void SaveFileAction::Execute()
{
	Output* pOut=pManager->GetOutput();
	
	ReadActionParameters();
	
	if(!save)
		return;

	ofstream file;
	file.open(FileName);
	pManager->SaveFile(file);
	file.close();

	pManager->ResetActionLevel();

	pOut->PrintMsg("File Saved");

	UI.filename=FileName;
	UI.enable_save=false;
}

void SaveFileAction::Undo()
{}

void SaveFileAction::Redo()
{}


