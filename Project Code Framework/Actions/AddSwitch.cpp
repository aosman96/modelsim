#include "AddSwitch.h"
#include "..\ApplicationManager.h"
#include "..\Components\Switch.h"

AddSwitch::AddSwitch(ApplicationManager *pApp):Action(pApp),usercancelled(false),undone(false)
{
}

void AddSwitch::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	GraphicsInfo GInfo; //Gfx info to be used to construct the ghosted AND2 switch

	int iX,iY;
	int wdth = UI.Switch_Width;
	int hght = UI.Switch_Height;
	//Print Action Message
	pOut->PrintMsg("Switch: Click to add the switch");
	
	
	
    // Loop until there is a mouse click
	while(pIn->GetMouseClick(iX, iY) == NO_CLICK)
	{
		iX+=wdth/2;
		iY+=hght/2;
		pIn->GetMouseCoord(iX, iY);
		pManager->FastUpdateInterface();
		
		iX=max(UI.Switch_Width/2,iX);
		iY=max(UI.DrawingAreaYsrt + UI.Switch_Height/2,iY);
		
		
		iX=min(UI.width-UI.Switch_Width*3/2,iX);
		iY=min(UI.height-UI.StatusBarHeight-UI.Switch_Height*3/2,iY);
		
		GInfo.x1 = iX;// - UI.Switch_Width/2;
		GInfo.x2 = iX + wdth;
		GInfo.y1 = iY;// - UI.Switch_Height/2;
		GInfo.y2 = iY + hght;

		pOut->DrawSWITCH(GInfo);
		
		pOut->PrintMsg("Switch: Click to add the switch: "+ to_string(iX) + "," + to_string(iY-UI.DrawingAreaYsrt)); 
		pOut->UpdateBuffer();

	}

	if(iY>=UI.DrawingAreaYsrt && iY<=UI.height-UI.StatusBarHeight)
	{
		iX=max(UI.Switch_Width/2,iX);
		iY=max(UI.DrawingAreaYsrt + UI.Switch_Height/2,iY);
		
		
		iX=min(UI.width-UI.Switch_Width*3/2,iX);
		iY=min(UI.height-UI.StatusBarHeight-UI.Switch_Height*3/2,iY);	
	}
	else
	{
		usercancelled=true;
		
	}


	
	this->Cx=iX;
	this->Cy=iY;

	//Clear Status Bar
	pOut->ClearStatusBar();	
}

void AddSwitch::Execute()
{
	//Get Center point of the switch
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();
	


	//Calculate the rectangle Corners
	int Len = UI.Switch_Width;
	int Wdth = UI.Switch_Height;
	
	GraphicsInfo GInfo; //Gfx info to be used to construct the switch

	GInfo.x1 = Cx;
	GInfo.x2 = Cx + Len;
	GInfo.y1 = Cy;
	GInfo.y2 = Cy + Wdth;

	if(pManager->CheckConflict_GATE(GInfo))
	{
		pOut->PrintMsg("This area is already occupied, please choose another area");
		return;
	}

	if(usercancelled)
	{
		pOut->PrintMsg("Operation cancelled, user clicked outside drawing area");
		return;
	}

	CanBeUndone=true;
	pA=new Switch(GInfo); 
	
	pManager->AddComponent(pA);
	pOut->PrintMsg("Success");
	
}
void AddSwitch::Undo()
{
	pManager->RemoveByPTR(pA);
	undone=true;
}

void AddSwitch::Redo()
{
	pManager->AddComponent(pA);
	undone=false;
	
}

AddSwitch::~AddSwitch()
{
	if(undone)
		delete pA; 
}

