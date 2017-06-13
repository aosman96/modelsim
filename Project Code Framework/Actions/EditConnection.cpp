#include "EditConnection.h"
#include "..\ApplicationManager.h"
#include "..\Components\InputPin.h"
#include "..\Components\OutputPin.h"
#include "..\Components\Connection.h"

EditConnection::EditConnection(ApplicationManager *pApp):Action(pApp),src(NULL),des(NULL),usr_cancel(false)
{
	conn=dynamic_cast<Connection*>(pManager->GetSelectedComponentList()[0]);
}

EditConnection::~EditConnection(void)
{
}

void EditConnection::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	int illustrations_size=0;

	Point p;
	vector<Point> illustrations;

	illustrations.push_back(p);
	illustrations.push_back(p);

	bool src_connected=false;
	bool des_connected=false;

	int iX,iY;

	while(!src_connected)
	{
		// Loop until there is a mouse click 
		while(pIn->GetMouseClick(iX, iY) == NO_CLICK)
		{
			pIn->GetMouseCoord(iX,iY);
			if(iY>UI.DrawingAreaYsrt && iY<UI.height-UI.StatusBarHeight)
			{
				pManager->HighlightPinsAT(iX,iY);
				pOut->PrintMsg("Click to add the start of the wire: " + to_string(iX) + "," + to_string(iY-UI.DrawingAreaYsrt)); 
			}
			else
				pOut->PrintMsg("Click to add the start of the wire: ");
			pManager->FastUpdateInterface();
			pOut->UpdateBuffer();
		}



		if(iY<UI.DrawingAreaYsrt || iY>UI.height-UI.StatusBarHeight)	//Clicking outside the drawing area is considered as the user cancelled the operation
		{
			usr_cancel=true;
			return;
		}

		src=pManager->ReturnOutputPinAT(iX,iY);	
	
		if(pManager->ReturnInputPinAT(iX,iY))
			pOut->PrintMsg("Wire start must be an output pin of gate,not an input pin. Please choose a valid output pin");
		else if(!src)
			pOut->PrintMsg("Please choose a valid output pin as a starting point of the wire");
		else if(!src->Connectable())
			pOut->PrintMsg("Maxium fanout of this gate is reached, Please choose another output pin or consider using a buffer");
		else 
			src_connected=true;
	}
	
	illustrations[0].x=iX;
	illustrations[0].y=iY;

	final_points.push_back(illustrations[0]);

	pOut->UpdateBuffer();

	while(!des_connected)
	{
		// Loop until there is a mouse click
		while(pIn->GetMouseClick(iX, iY) == NO_CLICK)
		{
			pIn->GetMouseCoord(iX,iY);
			if(iY>UI.DrawingAreaYsrt && iY<UI.height-UI.StatusBarHeight)
			{
				pManager->HighlightPinsAT(iX,iY);
				pOut->PrintMsg("Click to add the end of the wire: " + to_string(iX) + "," + to_string(iY-UI.DrawingAreaYsrt)); 
				illustrations[0].x=iX;
				illustrations[1].x=iX;
				illustrations[1].y=iY;
			}
			else
				pOut->PrintMsg("Click to add the end of the wire: ");
			pManager->FastUpdateInterface();
		
			pOut->DrawConnection(final_points,true,false);
			pOut->DrawConnection(illustrations.front(),final_points.back(),true,false);
			pOut->DrawConnection(illustrations,true,false);
			pOut->UpdateBuffer();
		}

		if(iY<UI.DrawingAreaYsrt || iY>UI.height-UI.StatusBarHeight)	//Clicking outside the drawing area is considered as the user cancelled the operation
		{
			usr_cancel=true;
			return;
		}

		des=pManager->ReturnInputPinAT(iX,iY);

		if(pManager->ReturnOutputPinAT(iX,iY))
			pOut->PrintMsg("Wire end must be an input pin of gate,not an output pin. Please choose a valid input pin");
		else if(!des)
		{
			final_points.push_back(illustrations[0]);
			final_points.push_back(illustrations[1]);	
			illustrations[0].y=iY;
			illustrations[1].y=iY;
		}
		else if(des->is_connected())
			pOut->PrintMsg("This pin is already connected");
		else 
		{
			illustrations[0].x=iX;
			illustrations[1].x=iX;
			illustrations[1].y=iY;

			final_points.push_back(illustrations[0]);
			final_points.push_back(illustrations[1]);
			des_connected=true;
		}
	}
	pOut->ClearStatusBar();	
}

void EditConnection::Execute()
{	
	if(!conn)return;

	//Undo related data
	Orig_points=conn->GetPoints();
	Origsrc=conn->getSourcePin();
	Origdes=conn->getDestPin();


	conn->SetPoints(final_points);
	conn->Disconnet();
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	
	
	ReadActionParameters();
	
	pManager->HighlightPinsAT(-1,-1);//reset the highlighted pins

	if(usr_cancel)
	{
		conn->SetPoints(Orig_points);
		conn->Reconnect();
		pOut->PrintMsg("Operation cancelled");
		return;
	}
	
	CanBeUndone=true;	

	conn->SetPoints(final_points);
	conn->setSourcePin(src);
	conn->setDestPin(des);

	pOut->PrintMsg("Success");
	
}

void EditConnection::Undo()
{
	conn->SetPoints(Orig_points);
	conn->setSourcePin(Origsrc);
	conn->setDestPin(Origdes);
}

void EditConnection::Redo()
{
	conn->SetPoints(final_points);
	conn->setSourcePin(src);
	conn->setDestPin(des);
}

