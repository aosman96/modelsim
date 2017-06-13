#include "PasteAction.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Defs.H"

Paste::Paste(ApplicationManager *pApp):Action(pApp),undone(false)
{
	Clipboard=pApp->GetClipBoard();
	CanBeUndone=true;
	cancel=false;
}

void Paste::ReadActionParameters()
{
}

void Paste::Execute()
{
	Component* newcopy;
	vector <Component*> new_clipboard;
	Output* pOut=pManager->GetOutput();
	count=0;
	
	pManager->ResetSelectedComponentList();

	Drag(Clipboard);

	if(cancel)
	{
		CanBeUndone=false;
		return;
	}
	for(auto item:Clipboard)
	{
		item->updateID();
		pManager->AddComponent(item);
		newcopy=item->CreateCopy();
		new_clipboard.push_back(newcopy);
		count++;
	}

	pManager->SetClipBoard(new_clipboard);
	pManager->SetSelectedComponentList(Clipboard);
	pOut->PrintMsg(to_string(count)+" item(s) Pasted");
	UI.enable_edit=UI.enable_copy_cut_delete=true;
}

bool Paste::CheckArea(vector<Component*>& list,int deltaX,int deltaY)
{
	int n=list.size();
	GraphicsInfo SMALLRECT;
	for(int i=0;i<n;i++)
	{
		list[i]->GetComponentCorners(SMALLRECT);
		SMALLRECT.x1+=deltaX;
		SMALLRECT.x2+=deltaX;
		SMALLRECT.y1+=deltaY;
		SMALLRECT.y2+=deltaY;
		if(pManager->CheckConflict_GATE(SMALLRECT))
		{
			return false;
		}
	}
	return true;
}

void Paste::Drag(vector<Component*>& list)
{
	int deltaX=0,deltaY=0,tx,ty,x,y;
	GraphicsInfo Rectangle;
	GetRectangle(list,Rectangle);
	Output* pOut=pManager->GetOutput();
	Input* pIn=pManager->GetInput();
	int n=list.size();
	
		while(pIn->GetMouseClick(tx,ty)==NO_CLICK)
		{
			pIn->GetMouseCoord(x,y);
		
			deltaX=x-Rectangle.x1;
			deltaY=y-Rectangle.y1;
		
			if(deltaX<0)
			{
				deltaX=-1*deltaX;
				deltaX=min(Rectangle.x1-10,deltaX);
				deltaX=-1*deltaX;
			}
			else
			{
				deltaX=min(UI.width-Rectangle.x2-20,deltaX);
			}
			if(deltaY<0)
			{
				deltaY=-1*deltaY;
				deltaY=min(Rectangle.y1-UI.DrawingAreaYsrt-10,deltaY);
				deltaY=-1*deltaY;
			}
			else
			{
				deltaY=min(UI.height-UI.StatusBarHeight-Rectangle.y2-10,deltaY);
			}

			pOut->ClearDrawingArea();

			pManager->FastUpdateInterface();

			for(int i=0; i<n; i++)
				list[i]->DrawWithDisplacement(pOut,deltaX,deltaY);

			pOut->DrawTransparentRectangle(Rectangle,deltaX,deltaY);
			pOut->PrintMsg("Choose Position to paste into: " + to_string(x) + "," + to_string(y-UI.DrawingAreaYsrt));
			pOut->UpdateBuffer();
		}



	if(!CheckArea(list,deltaX,deltaY)){
		pOut->PrintMsg("You can not paste into this area, please choose another area");
		cancel=true;	
		return;
	}
	
	for(int i=0;i<n;i++)
		list[i]->Move(deltaX,deltaY);
}

void Paste::GetRectangle(vector<Component*>& list,GraphicsInfo& rect)
{
	rect.x1=UI.width+10; //Imposible but set to be able to calculate the min
	rect.y1=UI.height+10;
	rect.x2=-1; //Imposible but set to be able to calculate the max
	rect.y2=-1;
	GraphicsInfo currentcomp;
	int n=list.size();
	for(int i=0;i<n;i++)
	{
		list[i]->GetComponentCorners(currentcomp);
		
		rect.x1=min(rect.x1,currentcomp.x1);
		rect.y1=min(rect.y1,currentcomp.y1);
		rect.x2=max(rect.x2,currentcomp.x2);
		rect.y2=max(rect.y2,currentcomp.y2);
	}
	rect.x1-=10;
	rect.y1-=10;
	rect.x2+=10;
	rect.y2+=10;
}

void Paste::Undo()
{
	for(auto Comp:Clipboard)
		pManager->RemoveByPTR(Comp);
	undone=true;
	pManager->ResetSelectedComponentList();
	pManager->GetOutput()->PrintMsg(to_string(count)+" item(s) removed");
}

void Paste::Redo()
{
	for(auto Comp:Clipboard)
		pManager->AddComponent(Comp);
	undone=false;
	pManager->GetOutput()->PrintMsg(to_string(count)+" item(s) restored");
}


Paste::~Paste(void)
{
	if(undone)
	{
		for(auto& Comp:Clipboard)
			delete Comp;
	}
}