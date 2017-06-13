#include "AddLed.h"
#include "..\ApplicationManager.h"
#include "..\Components\Led.h"

AddLed::AddLed(ApplicationManager *pApp):Action(pApp),usercancelled(false),undone(false)
{
}

void AddLed::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	GraphicsInfo GInfo; //Gfx info to be used to construct the ghosted AND2 Led

	int iX,iY;
	int wdth = UI.Led_Width;
	int hght = UI.Led_Height;
	//Print Action Message
	pOut->PrintMsg("Led: Click to add the Led");
	
	
    // Loop until there is a mouse click
	while(pIn->GetMouseClick(iX, iY) == NO_CLICK)
	{
		iX+=wdth/2;
		iY+=hght/2;
		pIn->GetMouseCoord(iX, iY);
		pManager->FastUpdateInterface();
		
		iX=max(UI.Led_Width/2,iX);
		iY=max(UI.DrawingAreaYsrt + UI.Led_Height/2,iY);
		
		
		iX=min(UI.width-UI.Led_Width*3/2,iX);
		iY=min(UI.height-UI.StatusBarHeight-UI.Led_Height*3/2,iY);
		
		GInfo.x1 = iX;// - UI.Led_Width/2;
		GInfo.x2 = iX + wdth;
		GInfo.y1 = iY;// - UI.Led_Height/2;
		GInfo.y2 = iY + hght;

		pOut->DrawLED(GInfo);
		
		pOut->PrintMsg("Led: Click to add the Led: "+ to_string(iX) + "," + to_string(iY-UI.DrawingAreaYsrt)); 
		pOut->UpdateBuffer();

	}

	if(iY>=UI.DrawingAreaYsrt && iY<=UI.height-UI.StatusBarHeight)
	{
		iX=max(UI.Led_Width/2,iX);
		iY=max(UI.DrawingAreaYsrt + UI.Led_Height/2,iY);
		
		
		iX=min(UI.width-UI.Led_Width*3/2,iX);
		iY=min(UI.height-UI.StatusBarHeight-UI.Led_Height*3/2,iY);	
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

void AddLed::Execute()
{
	//Get Center point of the Led
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	ReadActionParameters();
	


	//Calculate the rectangle Corners
	int Len = UI.Led_Width;
	int Wdth = UI.Led_Height;
	
	GraphicsInfo GInfo; //Gfx info to be used to construct the  Led

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
	pA=new Led(GInfo); 
	
	pManager->AddComponent(pA);
	pOut->PrintMsg("Success");
	
}

void AddLed::Undo()
{
	pManager->RemoveByPTR(pA);
	undone=true;
}

void AddLed::Redo()
{
	pManager->AddComponent(pA);
	undone=false;
	
}

AddLed::~AddLed()
{
	if(undone)
		delete pA; 
}

