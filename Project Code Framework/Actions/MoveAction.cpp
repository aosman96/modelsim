#include "MoveAction.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Utility\RTTI.h"
#include "..\Components\Connection.h"

Move::Move(ApplicationManager *pApp):Action(pApp)
{
	SelectComponents=pApp->GetSelectedComponentList();
	GetSelectedCircuitCorners();
	usrcancel=false;
	unsupported=false;
}

Move::~Move(void)
{
}

void Move::ReadActionParameters()
{
	Output* pOut=pManager->GetOutput();
	Input* pIn=pManager->GetInput();
	int x=0,y=0,d1,d2;
	int intialX,intialY;
	pIn->GetLastPointClicked(intialX,intialY);
	
	while(pIn->GetMouseClick(d1,d2)==NO_CLICK)
	{
		pIn->GetMouseCoord(x,y);
		deltaX=x-intialX;
		deltaY=y-intialY;
		if(deltaX<0)
		{
			deltaX=-1*deltaX;
			deltaX=min(CircuitRectangle.x1-10,deltaX);
			deltaX=-1*deltaX;
		}
		else
		{
			deltaX=min(UI.width-CircuitRectangle.x2-20,deltaX);
		}
		if(deltaY<0)
		{
			deltaY=-1*deltaY;
			deltaY=min(CircuitRectangle.y1-UI.DrawingAreaYsrt-10,deltaY);
			deltaY=-1*deltaY;
		}
		else
		{
			deltaY=min(UI.height-UI.StatusBarHeight-CircuitRectangle.y2-10,deltaY);
		}

		if(deltaX!=0 && deltaY!=0){
			Drag();
			pOut->PrintMsg("Move " + to_string(SelectComponents.size())+ " item(s) with displacement: " + to_string(deltaX) + "," + to_string(deltaY));
		}
	
		pOut->UpdateBuffer();
	}
	
	if(y<UI.DrawingAreaYsrt || y>UI.height-UI.StatusBarHeight || (deltaX==0 && deltaY==0))
	{
		usrcancel=true;
		return;
	}

}

void Move::GetSelectedCircuitCorners()
{
	CircuitRectangle.x1=UI.width+10; //Imposible but set to be able to calculate the min
	CircuitRectangle.y1=UI.height+10;
	CircuitRectangle.x2=-1; //Imposible but set to be able to calculate the max
	CircuitRectangle.y2=-1;
	GraphicsInfo currentcomp;
	int n=SelectComponents.size();
	for(int i=0;i<n;i++)
	{
		SelectComponents[i]->GetComponentCorners(currentcomp);
		
		CircuitRectangle.x1=min(CircuitRectangle.x1,currentcomp.x1);
		CircuitRectangle.y1=min(CircuitRectangle.y1,currentcomp.y1);
		CircuitRectangle.x2=max(CircuitRectangle.x2,currentcomp.x2);
		CircuitRectangle.y2=max(CircuitRectangle.y2,currentcomp.y2);
	}
	CircuitRectangle.x1-=10;
	CircuitRectangle.y1-=10;
	CircuitRectangle.x2+=10;
	CircuitRectangle.y2+=10;
}

void Move::Drag()
{
	Output* OutputInterface=pManager->GetOutput();
	int midpointX=(CircuitRectangle.x1+CircuitRectangle.x2)/2,midpointY=(CircuitRectangle.y1+CircuitRectangle.y2)/2;
	
	OutputInterface->ClearDrawingArea();
	pManager->DrawNonSelectedItems();

	for(auto& Comp:SelectComponents)
		Comp->DrawWithDisplacement(OutputInterface,deltaX,deltaY);

	OutputInterface->DrawLine(midpointX,midpointY,midpointX+deltaX,midpointY+deltaY); 
	OutputInterface->DrawTransparentRectangle(CircuitRectangle,deltaX,deltaY);
}

bool Move::MoveItems(int deltaX,int deltaY)
{
	GraphicsInfo SMALLRECT;
	bool overlap=false;
	MovedItems=0;
	for(UINT i=0;i<SelectComponents.size();i++)
	{
		SelectComponents[i]->GetComponentCorners(SMALLRECT);
		SMALLRECT.x1+=deltaX;
		SMALLRECT.x2+=deltaX;
		SMALLRECT.y1+=deltaY;
		SMALLRECT.y2+=deltaY;
		
		if(pManager->CheckConflict_MOVE(SMALLRECT) && is_not_a(SelectComponents[i],Connection)){
			overlap=true;
			SelectComponents[i]->un_select();
			SelectComponents.erase(SelectComponents.begin()+i);
			i--;
		}
		else
		{
			MovedItems++;
			SelectComponents[i]->Move(deltaX,deltaY);
		}
	}
	return overlap;
}

void Move::Execute()
{
	Output* pOut=pManager->GetOutput();
	Input* pIn=pManager->GetInput();
	ReadActionParameters();
	bool overlap;
	if(usrcancel)
	{
		CanBeUndone=false;
		return;
	}
	overlap=MoveItems(deltaX,deltaY);
	if(overlap){
		pOut->PrintMsg("Moving some items ignored due to possible overlap !");
		pManager->SetSelectedComponentList(SelectComponents);
	}
	else
		pOut->PrintMsg("Ready");
	if(MovedItems!=0)
		CanBeUndone=true;
}

void Move::Undo()
{
	for(auto Comp:SelectComponents)
		Comp->Move(-1*deltaX,-1*deltaY);
	pManager->ResetSelectedComponentList();
	pManager->GetOutput()->PrintMsg("Undo moving items");
}

void Move::Redo()
{
	for(auto Comp:SelectComponents)
		Comp->Move(deltaX,deltaY);
	pManager->GetOutput()->PrintMsg("Redo moving items");	
}


