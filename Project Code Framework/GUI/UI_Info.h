#ifndef UI_INFO_H
#define UI_INFO_H

#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\Defs.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	MODE AppMode;		//Application Mode (design or simulation)
	
	Selected_Tab SelectedTab;	//Selected Tab for the toolbar

	SCROLL ScrollCount; //Toolbar scroll count (added by KARIM)

	bool enable_save,enable_copy_cut_delete,enable_paste,enable_undo,enable_redo,enable_edit,enable_editconn;

	static const int	width = 980, height = 700,	//Window width and height
						wx = 15 , wy = 15,			//Window starting coordinates
						StatusBarHeight = 50,	//Status Bar Height
						ToolItemWidth = 80,		//Width of each item in toolbar menu
						ToolBarHeight = 80,		//Tool Bar Height (distance from bottom of tabs to bottom line of toolbar)
						TabsHeight = 25,
						TabsItemWidth = 125,
						DrawingAreaYsrt=TabsHeight+ToolBarHeight;
						
			

	//====================>Added by karim
	static const int	disp_max=width/ToolItemWidth;	//Maximum number of items that can be displayed in 1 toolbar page

	color DrawColor;		//Drawing color
	color SelectColor;		//Highlighting color
	color ConnColor;		//Connector color
	color MsgColor;			//Messages color
	color PinHoveredColor;  //color when the mouse is over the PIN

	
	//====================>Added by karim
	
	color BkGrndColor;		//Back ground color


	//This should be calculated accurately because it will be used later to create connections between gates
	//For now, we will assume that rect width = 50 and height = 50
	static const int	GATE_Width = 50,		//Gate Image default width
						GATE_Height = 50,		//Gate Image default height
						Switch_Width = 50,
						Switch_Height = 50,
						Led_Width = 50,
						Led_Height = 50;

	string filename;	//To be displayed in the titlebar
}UI;	//create a single global object UI

#endif