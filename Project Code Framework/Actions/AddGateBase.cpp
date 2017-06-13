#include "AddGateBase.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"


AddGate::AddGate(ApplicationManager *pApp):Action(pApp),usrcancelled(false),undone(false)
{
}

void AddGate::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	GraphicsInfo GInfo; //Gfx info to be used to construct the ghosted AND2 gate

	int iX,iY;
	int wdth = UI.GATE_Width;
	int hght = UI.GATE_Height;
	//Print Action Message
	
	
	pOut->PrintMsg(desciption + ": Click to add the gate");
    // Loop until there is a mouse click
	while(pIn->GetMouseClick(iX, iY) == NO_CLICK)
	{
		iX+=wdth/2;
		iY+=hght/2;
		pIn->GetMouseCoord(iX, iY);
		pManager->FastUpdateInterface();
		
		iX=max(UI.GATE_Width/2,iX);
		iY=max(UI.DrawingAreaYsrt + UI.GATE_Height/2,iY);
		
		
		iX=min(UI.width-UI.GATE_Width*3/2,iX);
		iY=min(UI.height-UI.StatusBarHeight-UI.GATE_Height*3/2,iY);
		
		GInfo.x1 = iX;// - UI.GATE_Width/2;
		GInfo.x2 = iX + wdth;
		GInfo.y1 = iY;// - UI.GATE_Height/2;
		GInfo.y2 = iY + hght;

		DrawDrag(GInfo);
		
		pOut->PrintMsg(desciption + ": Click to add the gate: "+ to_string(iX) + "," + to_string(iY-UI.DrawingAreaYsrt)); 

		pOut->UpdateBuffer();

	}

	if(iY>=UI.DrawingAreaYsrt && iY<=UI.height-UI.StatusBarHeight)
	{
		iX=max(UI.GATE_Width/2,iX);
		iY=max(UI.DrawingAreaYsrt + UI.GATE_Height/2,iY);
		
		
		iX=min(UI.width-UI.GATE_Width*3/2,iX);
		iY=min(UI.height-UI.StatusBarHeight-UI.GATE_Height*3/2,iY);	
	}
	else
	{
		usrcancelled=true;
	}
	
	this->Cx=iX;
	this->Cy=iY;

	//Clear Status Bar
	pOut->ClearStatusBar();	
}

void AddGate::Execute()
{
	//Get Center point of the Gate
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();

	//Calculate the rectangle Corners
	int Len = UI.GATE_Width;
	int Wdth = UI.GATE_Height;
	
	GraphicsInfo GInfo; //Gfx info to be used to construct the gate

	GInfo.x1 = Cx;
	GInfo.x2 = Cx + Len;
	GInfo.y1 = Cy;
	GInfo.y2 = Cy + Wdth;

	if(pManager->CheckConflict_GATE(GInfo))
	{
		pOut->PrintMsg("This area is already occupied, please choose another area");
		return;
	}

	if(usrcancelled)
	{
		pOut->PrintMsg("Operation cancelled, user clicked outside drawing area");
		return;
	}
	

	CanBeUndone=true;

	pA=CreateComponent(GInfo); 
	
	pManager->AddComponent(pA);

	pOut->PrintMsg("Success");
	
}

void AddGate::Undo()
{
	pManager->RemoveByPTR(pA);
	undone=true;
	pManager->GetOutput()->PrintMsg("Removed "+desciption);
}

void AddGate::Redo()
{
	pManager->AddComponent(pA);
	undone=false;
	pManager->GetOutput()->PrintMsg("Restored "+desciption);	
}

AddGate::~AddGate()
{
	if(undone)
		delete pA; 
}
