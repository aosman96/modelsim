#pragma once
#include "..\Defs.h"
#include "Input.h"
#include <vector>
using std::vector;
class ApplicationManager;
class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
	void CreateDesignToolBar() const;	//Tool bar of the design mode
	void CreateSimulationToolBar() const;//Tool bar of the simulation mode
	void CreateOptionsToolbar() const; //Tool bar of Options
	void DrawPins(const GraphicsInfo& r_GfxInfo,HighPins HoveredPin,int nInput)const;
public:
	Output(); // Performs the Window Initialization
	Input* CreateInput() const; //creates a pointer to the Input object
	void ChangeTitle(string Title) const;

	void CreateTabToolbar();
	
	//void CreateSideToolBar() const;	//Draws the side toolbar. Note this toolbar is both design & simulation===>>Should be deleted. Doesnt exist ?
	void CreateStatusBar() const;	//Create Status bar		
	void DrawLabel(string s,int iX,int iY,bool selected=false);
	void ClearStatusBar() const;		//Clears the status bar
	void ClearDrawingArea() const;	//Clears the drawing area

	window* CreateWind(int wd, int h, int x, int y) const; //Creates user interface window

	//=======================>Added by karim
	void ReDrawUI();

	void UpdateBuffer();
	

	// Draws 2-input AND gate
	void DrawAND2(GraphicsInfo r_GfxInfo, bool selected = false,HighPins HoveredPin=NO_PIN,int OffsetX=0,int OffsetY=0) const; 

	//Added by Tarek DrawFunctions
	void DrawOR2(GraphicsInfo r_GfxInfo, bool selected = false,HighPins HoveredPin=NO_PIN,int OffsetX=0,int OffsetY=0) const; 
	void DrawNOT(GraphicsInfo r_GfxInfo, bool selected = false,HighPins HoveredPin=NO_PIN,int OffsetX=0,int OffsetY=0) const;
	void DrawXOR2(GraphicsInfo r_GfxInfo, bool selected = false,HighPins HoveredPin=NO_PIN,int OffsetX=0,int OffsetY=0) const;
	void DrawXNOR2(GraphicsInfo r_GfxInfo, bool selected = false,HighPins HoveredPin=NO_PIN,int OffsetX=0,int OffsetY=0) const;
	void DrawNOR2(GraphicsInfo r_GfxInfo, bool selected = false,HighPins HoveredPin=NO_PIN,int OffsetX=0,int OffsetY=0) const;
	void DrawNAND2(GraphicsInfo r_GfxInfo, bool selected = false,HighPins HoveredPin=NO_PIN,int OffsetX=0,int OffsetY=0) const;
	void DrawBuffer(GraphicsInfo r_GfxInfo, bool selected = false,HighPins HoveredPin=NO_PIN,int OffsetX=0,int OffsetY=0) const;
	void DrawAND3(GraphicsInfo r_GfxInfo, bool selected = false,HighPins HoveredPin=NO_PIN,int OffsetX=0,int OffsetY=0) const;
	void DrawNOR3(GraphicsInfo r_GfxInfo, bool selected = false,HighPins HoveredPin=NO_PIN,int OffsetX=0,int OffsetY=0) const;
	void DrawOR3(GraphicsInfo r_GfxInfo, bool selected = false,HighPins HoveredPin=NO_PIN,int OffsetX=0,int OffsetY=0) const;
	void DrawXOR3(GraphicsInfo r_GfxInfo, bool selected = false,HighPins HoveredPin=NO_PIN,int OffsetX=0,int OffsetY=0) const;
	void DrawXNOR3(GraphicsInfo r_GfxInfo, bool selected = false,HighPins HoveredPin=NO_PIN,int OffsetX=0,int OffsetY=0) const;
	void DrawLED(GraphicsInfo r_GfxInfo,bool pinHovered=false,bool lighted=false, bool selected=false,int OffsetX=0,int OffsetY=0) const;
	void DrawSWITCH(GraphicsInfo r_GfxInfo,bool pinHovered=false,bool swtiched=false, bool selected=false,int OffsetX=0,int OffsetY=0) const;
	//End DrawFunctions

	void DisplayTable(string **table,int rows,int columns);

	void DrawTransparentRectangle(const GraphicsInfo& r_GfxInfo,int offsetX=0,int offsetY=0);

	void DrawLine(int x1,int y1,int x2,int y2);

	///TODO: Make similar functions for drawing all other gates, switch, and LED, .. etc

	// Draws Connection
	void DrawConnection(const vector<Point>& points, bool selected = false,bool status = false,int OffsetX=0,int OffsetY=0) const;
	void DrawConnection(const Point& point1, const Point& point2, bool selected = false,bool status = false,int OffsetX=0,int OffsetY=0) const;
	
	void PrintMsg(string msg);	//Print a message on Status bar

	//Displays MessageBox (added by karim)
	int Display_MessageBox(string msg,string title,UINT Type)const;

	void ClearToolBar() const;

	~Output();
};
