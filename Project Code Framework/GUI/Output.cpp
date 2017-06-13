#include "Output.h"
#include "../ApplicationManager.h"
#include "../Utility/PrecisionChecker.h"

Output::Output()
{
	//Initialize user interface parameters
	string title;

	UI.filename="";
	title="Untitled - Logic Simulator"; //intially, no file is loaded
	
	UI.AppMode = DESIGN;	//Design Mode is the startup mode
	UI.SelectedTab = API_TAB; //Design/Simulation is the startup
	UI.ScrollCount = PAGE_1;  //Edited By Kareem
	UI.enable_copy_cut_delete=false;
	UI.enable_paste=false;
	UI.enable_save=false;
	UI.enable_redo=false;
	UI.enable_undo=false;
	UI.enable_edit=false;
	UI.enable_editconn=false;
	//Initilaize interface colors
	UI.DrawColor = BLACK;
	UI.SelectColor = BLUE;
	UI.ConnColor = RED;
	UI.MsgColor = WHITE;		//By Ahmed
	UI.BkGrndColor = LIGHTGREY;
	UI.PinHoveredColor = DARKRED;
	//Create the drawing window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);	 
	pWind->SetBuffering(true);
	ChangeTitle(title);

	ClearDrawingArea();
	CreateTabToolbar();	//Create the desgin toolbar
	CreateStatusBar();		//Create Status bar
	PrintMsg("Ready");
	pWind->UpdateBuffer();
	pWind->SetWaitClose(false);
}

Input* Output::CreateInput() const
{
	//Create an Input Object & assign it to the Same Window
	Input* pIn = new Input(pWind);
	return pIn;
}


//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int wd, int h, int x, int y) const
{
	return new window(wd, h, x, y);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::ChangeTitle(string Title) const
{
	pWind->ChangeTitle(Title);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	//Ahmed - Img to status bar
	string StatusBarImg;
	StatusBarImg="Images\\Layout\\StatusBar.jpg";
	pWind->DrawImage(StatusBarImg,0,UI.height-UI.StatusBarHeight,UI.width,UI.StatusBarHeight);
}
//////////////////////////////////////////////////////////////////////////////////
void Output::PrintMsg(string msg)
{
	ClearStatusBar();	//Clear Status bar to print message on it
	// Set the Message offset from the Status Bar
	int MsgX = 25;
	int MsgY = UI.StatusBarHeight - 10;

	// Print the Message
    pWind->SetFont(20, BOLD | ITALICIZED, BY_NAME, "Arial"); 
	pWind->SetPen(UI.MsgColor); 
	pWind->DrawString(MsgX, UI.height - MsgY, msg);
	UpdateBuffer();
}
//////////////////////////////////////////////////////////////////////////////////


void Output::ClearStatusBar()const
{
	CreateStatusBar();
}

void Output::ClearToolBar() const
{
	//Ahmed - Changed to img
	string BarBackGround;
	BarBackGround="Images\\Layout\\ToolBarBackGround.jpg";
	pWind->DrawImage(BarBackGround,0,UI.TabsHeight,UI.width,UI.ToolBarHeight);
}

//////////////////////////////////////////////////////////////////////////////////////////
//Clears the drawing (desgin) area
void Output::ClearDrawingArea() const
{
	//Drawing Drawing Area Img. PRefered img rather than grey cuz grey is too dark on VS. - Ahmed
	string DrawingArea;
	DrawingArea="Images\\Layout\\DrawingAreaBackGround.jpg";
	pWind->DrawImage(DrawingArea,0,UI.TabsHeight+UI.ToolBarHeight,UI.width, UI.height-(UI.ToolBarHeight+UI.TabsHeight+UI.StatusBarHeight));
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the Design mode
void Output::CreateDesignToolBar() const  //==============>EDIT BY KARIM
{
	
	//You can draw the tool bar icons in any way you want.

	//First prepare List of images for each menu item
	string MenuItemImages[ITM_DSN_CNT];
	MenuItemImages[ITM_AND2] = "images\\Menu\\Menu_AND2.jpg";
	MenuItemImages[ITM_OR2]  = "images\\Menu\\Menu_OR2.jpg";

	MenuItemImages[ITM_INV]  = "images\\Menu\\Menu_NOT.jpg";
	MenuItemImages[ITM_Buff]  = "images\\Menu\\Menu_Buff.jpg";
	MenuItemImages[ITM_NAND2]  = "images\\Menu\\Menu_NAND2.jpg";
	MenuItemImages[ITM_NOR2]  = "images\\Menu\\Menu_NOR2.jpg";
	MenuItemImages[ITM_XOR2]  = "images\\Menu\\Menu_XOR2.jpg";
	MenuItemImages[ITM_XNOR2]  = "images\\Menu\\Menu_XNOR2.jpg";
	MenuItemImages[ITM_AND3]  = "images\\Menu\\Menu_AND3.jpg";
	MenuItemImages[ITM_OR3]  = "images\\Menu\\Menu_OR3.jpg";
	MenuItemImages[ITM_WIRE] = "images\\Menu\\Menu_conn.jpg";
	MenuItemImages[ITM_MORE1] = "images\\Menu\\RightArrow.jpg";
	MenuItemImages[ITM_BACK1] = "images\\Menu\\LeftArrow.jpg";

	MenuItemImages[ITM_XOR3] = "images\\Menu\\Menu_XOR3.jpg";
	MenuItemImages[ITM_NOR3] = "images\\Menu\\Menu_NOR3.jpg";	
	MenuItemImages[ITM_XNOR3] = "images\\Menu\\Menu_XNOR3.jpg";	
	MenuItemImages[ITM_LED] = "images\\Menu\\Menu_LED.jpg";
	MenuItemImages[ITM_WIRE] = "images\\Menu\\Menu_Wire.jpg";
	MenuItemImages[ITM_SWITCH] = "images\\Menu\\Menu_Switch.jpg";

	

	//============================> BY KARIM
	int LIMIT=min((1+UI.ScrollCount)*UI.disp_max,ITM_DSN_CNT)-UI.disp_max*UI.ScrollCount;
	int offset=(UI.ScrollCount)*UI.disp_max;

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	
	for(int i=0; i<LIMIT; i++)
	{
		//Ahmed----     -4 is a constant. The dark line at the end of the bar is 4 pixels constant from the img created========>>
		pWind->DrawImage(MenuItemImages[i+offset],i*UI.ToolItemWidth,UI.TabsHeight,UI.ToolItemWidth, UI.ToolBarHeight-4);
	}

}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the menu (toolbar) in the simulation mode
void Output::CreateSimulationToolBar() const
{
	//TODO: Write code to draw the simualtion toolbar (similar to that of design toolbar drawing)
	string MenuItemImages[ITM_SIM_CNT];
	MenuItemImages[ITM_TRUTH]  = "images\\Menu\\Menu_Truth.jpg";

	//TODO: Prepare image for each menu item and add it to the list

	//Draw menu item one image at a time
	//pWind->SetPen(RED,3);
	//EDIT BY KARIM (tobe further edited by Tarek/Osman Supposedly)
	for(int i=0; i<ITM_SIM_CNT; i++)
	{
		//Ahmed----     -4 is a constant. The dark line at the end of the bar is 4 pixels constant from the img created========>>
		pWind->DrawImage(MenuItemImages[i],i*UI.ToolItemWidth,UI.TabsHeight,UI.ToolItemWidth, UI.ToolBarHeight-4);
	}
}



void Output::CreateOptionsToolbar()const
{
	string MenuItemImages[ITM_OPTIONS_COUNT];
	
	if(UI.AppMode==DESIGN)
		MenuItemImages[ITM_ChangeMode] = "images\\Menu\\Menu_Chng_To_SIM.jpg";
	else
		MenuItemImages[ITM_ChangeMode] = "images\\Menu\\Menu_Chng_To_Design.jpg";

	MenuItemImages[ITM_OPEN] = "images\\Menu\\Menu_Open.jpg";

	if(UI.enable_save)
		MenuItemImages[ITM_SAVE]  = "images\\Menu\\Menu_Save.jpg";
	else
		MenuItemImages[ITM_SAVE]  = "images\\Menu\\Menu_Save_Disabled.jpg";

	if(UI.enable_edit && UI.AppMode==DESIGN)
		MenuItemImages[ITM_EDIT]= "images\\Menu\\Menu_Edit.jpg";
	else
		MenuItemImages[ITM_EDIT]= "images\\Menu\\Menu_Edit_Disabled.jpg";

	if(UI.enable_editconn)
		MenuItemImages[ITM_EDITCONN]= "images\\Menu\\Menu_EditConn.jpg";
	else
		MenuItemImages[ITM_EDITCONN]= "images\\Menu\\Menu_EditConn.jpg";

	if(UI.enable_copy_cut_delete && UI.AppMode==DESIGN)
	{
		MenuItemImages[ITM_CUT]  = "images\\Menu\\Menu_Cut.jpg";
		MenuItemImages[ITM_COPY]  = "images\\Menu\\Menu_Copy.jpg";
		MenuItemImages[ITM_DELETE] = "images\\Menu\\Menu_Delete.jpg";
	}
	else
	{
		MenuItemImages[ITM_CUT]  = "images\\Menu\\Menu_Cut_Disabled.jpg";
		MenuItemImages[ITM_COPY]  = "images\\Menu\\Menu_Copy_Disabled.jpg";
		MenuItemImages[ITM_DELETE] = "images\\Menu\\Menu_Delete_Disabled.jpg";
	}

	if(UI.enable_paste && UI.AppMode==DESIGN)
		MenuItemImages[ITM_PASTE]  = "images\\Menu\\Menu_Paste.jpg";
	else
		MenuItemImages[ITM_PASTE]  = "images\\Menu\\Menu_Paste_Disabled.jpg";



	if(UI.enable_undo && UI.AppMode==DESIGN)
		MenuItemImages[ITM_UNDO] = "images\\Menu\\Menu_Undo.jpg";
	else
		MenuItemImages[ITM_UNDO] = "images\\Menu\\Menu_Undo_Disabled.jpg";


	if(UI.enable_redo && UI.AppMode==DESIGN)
		MenuItemImages[ITM_REDO] = "images\\Menu\\Menu_Redo.jpg";
	else
		MenuItemImages[ITM_REDO] = "images\\Menu\\Menu_Redo_Disabled.jpg";


	MenuItemImages[ITM_EXIT]  = "images\\Menu\\Menu_Exit.jpg";
	
	//Draw menu item one image at a time
	//pWind->SetPen(RED,3);
	
	for(int i=0; i<ITM_OPTIONS_COUNT;i++)
	{
		//Ahmed----     -4 is a constant. The dark line at the end of the bar is 4 pixels constant from the img created========>>
		pWind->DrawImage(MenuItemImages[i],i*UI.ToolItemWidth,UI.TabsHeight,UI.ToolItemWidth, UI.ToolBarHeight-4);
	}

}

void Output::DrawLabel(string label_text,int iX,int iY,bool selected)
{
	int h,w;
	iX+=1;
	iY+=3;
	pWind->SetBrush(LIGHTGREY);
	pWind->SetPen(LIGHTGREY);
	
	
    pWind->SetFont(20, PLAIN , BY_NAME, "Arial"); 
	pWind->GetStringSize(w,h,label_text);

	pWind->DrawRectangle(iX,iY,iX+w,iY+h);
	
	pWind->SetPen(BLACK); 
	pWind->DrawString(iX, iY, label_text);
}

void Output::CreateTabToolbar()
{	
	ClearToolBar();

	string TabBarBackGround;
	TabBarBackGround="Images\\Layout\\TabsBar.jpg";
	pWind->DrawImage(TabBarBackGround,0,0,UI.width,UI.TabsHeight);

	string tabs[2];
	if(UI.SelectedTab==API_TAB && UI.AppMode==DESIGN)
	{
		tabs[0]="Images\\Layout\\Design-Selected.jpg";
		tabs[1]="Images\\Layout\\Options.jpg";
		pWind->DrawImage(tabs[0],0,0,UI.TabsItemWidth,UI.TabsHeight);
		pWind->DrawImage(tabs[1],UI.TabsItemWidth,0,UI.TabsItemWidth,UI.TabsHeight);
		CreateDesignToolBar();
	}
	else if(UI.SelectedTab==API_TAB && UI.AppMode==SIMULATION)
	{
		tabs[0]="Images\\Layout\\Simulation-Selected.jpg";
		tabs[1]="Images\\Layout\\Options.jpg";
		pWind->DrawImage(tabs[0],0,0,UI.TabsItemWidth,UI.TabsHeight);
		pWind->DrawImage(tabs[1],UI.TabsItemWidth,0,UI.TabsItemWidth,UI.TabsHeight);
		CreateSimulationToolBar();
	}
	
	else  //Options
	{
		if(UI.AppMode==DESIGN)
			tabs[0]="Images\\Layout\\Design.jpg";
		else
			tabs[0]="Images\\Layout\\Simulation.jpg";
		tabs[1]="Images\\Layout\\Options-Selected.jpg";
		pWind->DrawImage(tabs[0],0,0,UI.TabsItemWidth,UI.TabsHeight);
		pWind->DrawImage(tabs[1],UI.TabsItemWidth,0,UI.TabsItemWidth,UI.TabsHeight);
		CreateOptionsToolbar();
	}
	UpdateBuffer();
}


void Output::ReDrawUI()
{
	this->CreateTabToolbar();
	this->ClearDrawingArea();
	this->PrintMsg("Ready");
}

void Output::UpdateBuffer()
{
	pWind->UpdateBuffer();
}

//======================================================================================//
//								Components Drawing Functions							//
//======================================================================================//


void Output::DrawPins(const GraphicsInfo& r_GfxInfo,HighPins HoveredPin,int nInput)const
{
	pWind->SetPen(UI.PinHoveredColor, 0);    
    pWind->SetBrush(UI.PinHoveredColor);
	
	switch(HoveredPin)
	{
	case OUTPUT1:
		pWind->DrawRectangle(r_GfxInfo.x2 - precision, r_GfxInfo.y2 - UI.GATE_Height/2 -precision, r_GfxInfo.x2, r_GfxInfo.y2- UI.GATE_Height/2, FILLED);
		
		break;
	case INPUT1:
		if(nInput==2||nInput==3)
			pWind->DrawRectangle(r_GfxInfo.x1, r_GfxInfo.y1 + UI.GATE_Height/4-precision, r_GfxInfo.x1 + precision, r_GfxInfo.y1 + UI.GATE_Height/4, FILLED);
		else 
			pWind->DrawRectangle(r_GfxInfo.x1, r_GfxInfo.y1 + UI.GATE_Height/2 - precision, r_GfxInfo.x1 + precision, r_GfxInfo.y1 + UI.GATE_Height/2, FILLED);

		break;
	case INPUT2:
		if(nInput==2) 
			pWind->DrawRectangle(r_GfxInfo.x1, r_GfxInfo.y1 + UI.GATE_Height*3/4-precision, r_GfxInfo.x1 + precision, r_GfxInfo.y1 + UI.GATE_Height*3/4, FILLED);
		else if(nInput==3)
			pWind->DrawRectangle(r_GfxInfo.x1, r_GfxInfo.y1 + UI.GATE_Height/2 - precision, r_GfxInfo.x1 + precision, r_GfxInfo.y1 + UI.GATE_Height/2, FILLED);

		break;
	case INPUT3:
		pWind->DrawRectangle(r_GfxInfo.x1, r_GfxInfo.y1 + UI.GATE_Height*3/4-precision, r_GfxInfo.x1 + precision, r_GfxInfo.y1 + UI.GATE_Height*3/4, FILLED);
		break;
	}
}


void Output::DrawAND2(GraphicsInfo r_GfxInfo, bool selected, HighPins HoveredPin,int OffsetX,int OffsetY) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\2inputandSelected.jpg";
	else  
		GateImage = "Images\\Gates\\2inputand.jpg";
	
	//Draw AND2 Gate at Gfx_Info (1st corner)
	//Set the Image Width & Height by AND2 Image Parameter in UI_Info
	pWind->DrawImage(GateImage, r_GfxInfo.x1+OffsetX, r_GfxInfo.y1+OffsetY, UI.GATE_Width, UI.GATE_Height);

	DrawPins(r_GfxInfo,HoveredPin,2);

}

//Aded by Tarek. DrawFunctions
void Output::DrawOR2(GraphicsInfo r_GfxInfo, bool selected, HighPins HoveredPin,int OffsetX,int OffsetY) const
{
	string GateImage;
	if(selected)
		GateImage="Images\\Gates\\inputOr2Selected.jpg";
	else
		GateImage = "Images\\Gates\\inputOr2.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1+OffsetX, r_GfxInfo.y1+OffsetY, UI.GATE_Width, UI.GATE_Height);

	DrawPins(r_GfxInfo,HoveredPin,2);
}
void Output::DrawNOT(GraphicsInfo r_GfxInfo, bool selected, HighPins HoveredPin,int OffsetX,int OffsetY) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\notSelected.jpg";
	else  
		GateImage = "Images\\Gates\\not.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1+OffsetX, r_GfxInfo.y1+OffsetY, UI.GATE_Width, UI.GATE_Height);

	DrawPins(r_GfxInfo,HoveredPin,1);
}

void Output::DrawXOR2(GraphicsInfo r_GfxInfo, bool selected, HighPins HoveredPin,int OffsetX,int OffsetY) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\2inputxorSelected.jpg";
	else  
		GateImage = "Images\\Gates\\2inputxor.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1+OffsetX, r_GfxInfo.y1+OffsetY, UI.GATE_Width, UI.GATE_Height);

	DrawPins(r_GfxInfo,HoveredPin,2);

}

void Output::DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected, HighPins HoveredPin,int OffsetX,int OffsetY) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\2inputxnorSelected.jpg";
	else  
		GateImage = "Images\\Gates\\2inputxnor.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1+OffsetX, r_GfxInfo.y1+OffsetY, UI.GATE_Width, UI.GATE_Height);

	DrawPins(r_GfxInfo,HoveredPin,2);
}

void Output::DrawNOR2(GraphicsInfo r_GfxInfo, bool selected, HighPins HoveredPin,int OffsetX,int OffsetY) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\2inputnorSelected.jpg";
	else  
		GateImage = "Images\\Gates\\2inputnor.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1+OffsetX, r_GfxInfo.y1+OffsetY, UI.GATE_Width, UI.GATE_Height);

	DrawPins(r_GfxInfo,HoveredPin,2);
}
void Output::DrawNAND2(GraphicsInfo r_GfxInfo, bool selected, HighPins HoveredPin,int OffsetX,int OffsetY) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\2inputnandSelected.jpg";
	else  
		GateImage = "Images\\Gates\\2inputnand.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1+OffsetX, r_GfxInfo.y1+OffsetY, UI.GATE_Width, UI.GATE_Height);

	DrawPins(r_GfxInfo,HoveredPin,2);

}
void Output::DrawSWITCH(GraphicsInfo r_GfxInfo,bool pinHovered,bool swtiched, bool selected,int OffsetX,int OffsetY)const
{
	string GateImage;
	if(selected)
		GateImage="Images\\Leds\\SwitchSelected.jpg";

	else if(swtiched)	//use image in the highlighted case
		GateImage="Images\\Leds\\SwitchOn.jpg";
	else  
		GateImage = "Images\\Leds\\SwitchOff.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1+OffsetX, r_GfxInfo.y1+OffsetY, UI.GATE_Width, UI.GATE_Height);
	

	if(pinHovered){
		pWind->SetPen(UI.PinHoveredColor, 0);    
		pWind->SetBrush(UI.PinHoveredColor);
		pWind->DrawRectangle(r_GfxInfo.x2, r_GfxInfo.y1 + UI.Led_Height/2 - 5, r_GfxInfo.x2 + 5, r_GfxInfo.y1 + UI.Led_Height/2, FILLED);
	}
}

void Output::DrawLED(GraphicsInfo r_GfxInfo,bool pinHovered,bool lighted, bool selected,int OffsetX,int OffsetY) const
{
	string GateImage;

	if(selected)	
		GateImage = "Images\\Leds\\LedSelected.jpg";
	else  
		GateImage = "Images\\Leds\\Led.jpg";
	
		
	if(lighted)
		GateImage="Images\\Leds\\LedOn.jpg";

	pWind->DrawImage(GateImage, r_GfxInfo.x1+OffsetX, r_GfxInfo.y1+OffsetY, UI.Led_Width, UI.Led_Height);

	if(pinHovered){
		pWind->SetPen(UI.PinHoveredColor, 0);    
		pWind->SetBrush(UI.PinHoveredColor);
		pWind->DrawRectangle(r_GfxInfo.x1, r_GfxInfo.y1 + UI.Led_Height/2 - 5, r_GfxInfo.x1 + 5, r_GfxInfo.y1 + UI.Led_Height/2, FILLED);
	}
}
void Output::DrawBuffer(GraphicsInfo r_GfxInfo, bool selected, HighPins HoveredPin,int OffsetX,int OffsetY) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\bufferSelected.jpg";
	else  
		GateImage="Images\\Gates\\buffer.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1+OffsetX, r_GfxInfo.y1+OffsetY, UI.GATE_Width, UI.GATE_Height);
	DrawPins(r_GfxInfo,HoveredPin,1);
}

void Output::DrawAND3(GraphicsInfo r_GfxInfo, bool selected, HighPins HoveredPin,int OffsetX,int OffsetY) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\3inputandSelected.jpg";
	else  
		GateImage="Images\\Gates\\3inputand.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1+OffsetX, r_GfxInfo.y1+OffsetY, UI.GATE_Width, UI.GATE_Height);
	DrawPins(r_GfxInfo,HoveredPin,3);
}

void Output::DrawNOR3(GraphicsInfo r_GfxInfo, bool selected, HighPins HoveredPin,int OffsetX,int OffsetY) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\3inputnorSelected.jpg";
	else  
		GateImage="Images\\Gates\\3inputnor.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1+OffsetX, r_GfxInfo.y1+OffsetY, UI.GATE_Width, UI.GATE_Height);
	DrawPins(r_GfxInfo,HoveredPin,3);
}

void Output::DrawXOR3(GraphicsInfo r_GfxInfo, bool selected, HighPins HoveredPin,int OffsetX,int OffsetY) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\3inputxorSelected.jpg";
	else  
		GateImage="Images\\Gates\\3inputxor.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1+OffsetX, r_GfxInfo.y1+OffsetY, UI.GATE_Width, UI.GATE_Height);
	DrawPins(r_GfxInfo,HoveredPin,3);
}

void Output::DrawOR3(GraphicsInfo r_GfxInfo, bool selected, HighPins HoveredPin,int OffsetX,int OffsetY) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\3inputorSelected.jpg";
	else  
		GateImage="Images\\Gates\\3inputor.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1+OffsetX, r_GfxInfo.y1+OffsetY, UI.GATE_Width, UI.GATE_Height);
	DrawPins(r_GfxInfo,HoveredPin,3);
}

void Output::DrawXNOR3(GraphicsInfo r_GfxInfo, bool selected, HighPins HoveredPin,int OffsetX,int OffsetY) const
{
	string GateImage;
	if(selected)	//use image in the highlighted case
		GateImage="Images\\Gates\\3inputxnorSelected.jpg";
	else  
		GateImage="Images\\Gates\\3inputxnor.jpg";
	pWind->DrawImage(GateImage, r_GfxInfo.x1+OffsetX, r_GfxInfo.y1+OffsetY, UI.GATE_Width, UI.GATE_Height);
	DrawPins(r_GfxInfo,HoveredPin,3);
}

//End of Tarek's Draw functions

void Output::DrawConnection(const vector<Point>& points, bool selected,bool status,int OffsetX,int OffsetY) const
{
	if (selected)
		pWind->SetPen(RED,2);
	else 
		pWind->SetPen(BLACK,2);
	if(status)
		pWind->SetPen(GREEN,2);

	int size=points.size();
	
	for(int i=0;i<size-1;i++)
		pWind->DrawLine(points[i].x+OffsetX,points[i].y+OffsetY,points[i+1].x+OffsetX,points[i+1].y+OffsetY,FRAME);
}

void Output::DrawConnection(const Point& point1, const Point& point2, bool selected,bool status,int OffsetX,int OffsetY) const
{
	if (selected)
		pWind->SetPen(RED,2);
	else 
		pWind->SetPen(BLACK,2);
	if(status)
		pWind->SetPen(GREEN,2);

	pWind->DrawLine(point1.x+OffsetX,point1.y+OffsetY,point2.x+OffsetX,point2.y+OffsetY,FRAME);
}

//End of DrawConnections

void Output::DisplayTable(string **table,int rows,int columns)
{
	unsigned int max_length=0,maxi=0;
	int cell_width;
	int cell_height;

	int font_size=20;

	int xoffeset=5,yoffeset=5;

	int x=xoffeset,y=yoffeset;

	for(int i=0;i<columns;i++)
	{
		if(table[0][i].length()>max_length)
		{
			max_length=table[0][i].length();	
			maxi=i;
		}
	}
	
	pWind->SetFont(font_size, BOLD, BY_NAME, "Arial"); 
	pWind->GetStringSize(cell_width,cell_height,table[0][maxi]);

	//cell_width=max_length*font_size+10;
	//cell_height=font_size+10;
	cell_width+=10;
	cell_height+=10;

	//window wind(cell_width*(1+columns)+10,cell_height*(1+rows)+10);
	window wind(cell_width*columns+6*xoffeset,cell_height*rows+6*yoffeset);
	
	wind.SetFont(font_size, BOLD, BY_NAME, "Arial"); 
	wind.ChangeTitle("Truth Table");

	wind.SetPen(BLACK);
	
	for(int i=0;i<=rows;i++)
	{
		wind.DrawLine(x,y,x+cell_width*columns+1,y);
		y+=cell_height;
	}

	y=yoffeset;

	for(int i=0;i<=columns;i++)
	{
		wind.DrawLine(x,y,x,y+cell_height*rows);
		x+=cell_width;
	}

	for(int i=0;i<rows;i++)
	{
		x=xoffeset;
		for(int j=0;j<columns;j++)
		{
			wind.DrawString(x+5,y+5,table[i][j]);
			x+=cell_width;
		}
		y+=cell_height;
	}

	wind.WaitMouseClick(x,y);	
}

void Output::DrawTransparentRectangle(const GraphicsInfo& rect,int offsetX,int offsetY)
{
	pWind->SetPen(RED,2);
	pWind->DrawRectangle(rect.x1+offsetX,rect.y1+offsetY,rect.x2+offsetX,rect.y2+offsetY,FRAME);
}

void Output::DrawLine(int x1,int y1,int x2,int y2)
{
	pWind->SetPen(RED,1);
	pWind->DrawLine(x1,y1,x2,y2);
}


int Output::Display_MessageBox(string msg,string title,UINT Type)const
{
	return pWind->Display_MessageBox(msg,title,Type);
}

Output::~Output()
{
	delete pWind;
}
