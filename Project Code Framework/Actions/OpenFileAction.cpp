#include "OpenFileAction.h"
#include "ChangeToDesign.h"
#include "..\ApplicationManager.h"
#include <fstream>
#include <exception>
using std::ifstream;
using std::exception;

OpenFileAction::OpenFileAction(ApplicationManager *pApp):Action(pApp),usrcancel(false),FileName(UI.filename)
{
	CanBeUndone=false;
}

OpenFileAction::~OpenFileAction(void)
{
}

void OpenFileAction::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut= pManager->GetOutput();
	int answer=0;
	
	if(UI.enable_save)
	{
		answer=pOut->Display_MessageBox("Warning: If you proceed changes made to \"" + (FileName=="" ? "Untitled" : FileName) +"\" will be lost. \n Do you want to continue?","Logic Simulator",MB_YESNO|MB_ICONEXCLAMATION);
		if(answer==IDNO){
			usrcancel=true;
			return;
		}
	}
	usrcancel=!pIn->GetOpenFilename(FileName);
}

void OpenFileAction::Execute()
{
	Output* pOut=pManager->GetOutput();
	ReadActionParameters();
	string except;
	if(usrcancel)
		return;

	pManager->ResetApp(); //Everthing must be deleted before opening the new file
	pManager->ResetActionLevel();

	ifstream file;
	try{
		file.open(FileName);
		pManager->LoadFile(file);
		file.close();
		pOut->PrintMsg("File Loaded");
		UI.SelectedTab=API_TAB;
	}
	catch(exception& e)
	{
		except=e.what();
		pOut->Display_MessageBox("File is in wrong format or contains invalid data\n"+except+"\nFile Loading operation terminated","Logic Simulator",MB_OK|MB_ICONERROR);
		pManager->ResetApp();
		pOut->PrintMsg("Failed");
	}
	UI.filename=FileName;
	UI.enable_save=false;
	
}

void OpenFileAction::Undo()
{}

void OpenFileAction::Redo()
{}


