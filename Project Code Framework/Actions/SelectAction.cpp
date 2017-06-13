#include "SelectAction.h"
#include "..\ApplicationManager.h"
#include "..\Components\Component.h"
#include "..\Utility\RTTI.h"
#include "..\Components\Connection.h"

Select::Select(ApplicationManager *pApp):Action(pApp)
{
	CanBeUndone=false;
	SelectComponents=pApp->GetSelectedComponentList();
	act=NO_SELECT_ACT;
}

Select::~Select(void)
{
}

void Select::ReadActionParameters()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	int iX,iY;
	pIn->GetLastPointClicked(iX,iY);

	RectangleArea.x1=iX;
	RectangleArea.y1=iY;
	
	RectangleArea.x2=iX;
	RectangleArea.y2=iY;

	Component* ClickedItem=NULL;
	
	ClickedItem=pManager->GetComponentAt(iX,iY);

	if(!ClickedItem && SelectComponents.size()>0)  //Some componenets where previously selected and user clicked on an empty area -> user wants to unselect all
		act=UNSELECT_ALL;
	else if(!ClickedItem && SelectComponents.size()==0)  //NO componenets where previously selected and user clicked on an empty area -> user wants to multiselect
		act=MULTI_SELECT;
	else if(ClickedItem && !ClickedItem->is_selected()) //User clicked on a single item that is not selected -> User wants to unselect all then select this component
		act=SINLGE_SELECT;
	else 
		return;

}

void Select::Execute()
{
	Input* pIn = pManager->GetInput();
	Output* pOut = pManager->GetOutput();
	int x,y;

	GraphicsInfo CorrectedRectangleArea;
	CorrectedRectangleArea.x1=RectangleArea.x1;
	CorrectedRectangleArea.y1=RectangleArea.y1;

	ReadActionParameters();

	switch (act)
	{
	case NO_SELECT_ACT:
		return;
	
	case SINLGE_SELECT:
		SelectComponents.clear();
		SelectComponents=pManager->GetComponentsInsideAndSelect(RectangleArea);
		break;

	case MULTI_SELECT:
		
		
		while(pIn->GetMouseClick(x,y)==NO_CLICK)
		{
			pIn->GetMouseCoord(x,y);
			
			RectangleArea.x2=max(3,x);
			RectangleArea.x2=min(UI.width-20,RectangleArea.x2);
			RectangleArea.y2=max(UI.DrawingAreaYsrt,y);
			RectangleArea.y2=min(UI.height-UI.StatusBarHeight,RectangleArea.y2);

				if(RectangleArea.x2<RectangleArea.x1)
				{
					CorrectedRectangleArea.x1=RectangleArea.x2;
					CorrectedRectangleArea.x2=RectangleArea.x1;
				}
				else
				{
					CorrectedRectangleArea.x1=RectangleArea.x1;
					CorrectedRectangleArea.x2=RectangleArea.x2;
				}

				if(RectangleArea.y2<RectangleArea.y1)
				{
					CorrectedRectangleArea.y1=RectangleArea.y2;
					CorrectedRectangleArea.y2=RectangleArea.y1;
				}
				else
				{
					CorrectedRectangleArea.y1=RectangleArea.y1;
					CorrectedRectangleArea.y2=RectangleArea.y2;
				}

			pManager->SelectComponentsInside(CorrectedRectangleArea);
			pManager->FastUpdateInterface();
			pOut->DrawTransparentRectangle(RectangleArea);
			pOut->PrintMsg(to_string(RectangleArea.x2)+","+to_string(RectangleArea.y2-UI.DrawingAreaYsrt));
			pOut->UpdateBuffer();
		}
		SelectComponents=pManager->GetComponentsInsideAndSelect(CorrectedRectangleArea);
		
		break;
	case UNSELECT_ALL:
		SelectComponents.clear();
		pManager->ResetSelectedComponentList();
		break;
	}

	pManager->SetSelectedComponentList(SelectComponents);
	
	if(SelectComponents.size()){
		pOut->PrintMsg(to_string(SelectComponents.size())+" Item(s) selected");
		UI.enable_edit=UI.enable_copy_cut_delete=true;
		
		if(SelectComponents.size()==1 && is_a(SelectComponents[0],Connection))
			UI.enable_editconn=true;
	}
	else{
		pOut->PrintMsg("Ready");
		UI.enable_editconn=UI.enable_edit=UI.enable_copy_cut_delete=false;	
	}
	
}

void Select::Undo()
{}

void Select::Redo()
{}


