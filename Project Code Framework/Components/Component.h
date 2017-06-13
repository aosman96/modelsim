#ifndef _COMPONENT_H
#define _COMPONENT_H

#include "..\Defs.h"
#include "..\GUI\Output.h"
#include "InputPin.h"
#include "OutputPin.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

class Connection;


//Base class for classes Gate, Switch, and LED.
class Component
{
private:
	string m_Label;
	static int count;
	int level;
	
protected:
	int ID;
	GraphicsInfo m_GfxInfo;	//The parameters required to draw a component
	bool selected;
	virtual void DrawLabel(Output* pOut)=0;

public:
	virtual void getInputPinLocation(InputPin* p,int&x,int&y)=0; //Function to get the input pin *p location (needed for load)
	virtual void getOutputPinLocation(int&x,int&y)=0;  //Function to get the output pin *p location (needed for load)
	virtual void Operate() = 0;	//Calculates the output according to the inputs
	virtual void Draw(Output* pOut) = 0;	//for each component to Draw itself
	virtual void DrawWithDisplacement(Output* pOut,int deltaX,int deltaY) = 0;	//for each component to Draw itself while being moved
	
	virtual void Save(ofstream& out) = 0; //for each componenet to save itself
	virtual void Load(ifstream& in) = 0; //for each componenet to load itself 

	virtual bool isAt(int x,int y)=0; //returns true if x and y are within the component
	virtual int GetID();
	virtual STATUS GetOutPinStatus()=0;	//returns status of outputpin if LED, return -1
	virtual STATUS GetInputPinStatus(int n)=0;	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s)=0;	//set status of Inputpin # n, to be used by connection class.
	
	virtual void setLevel(int l);		//For simulation , the level
	virtual void resetLevel();			//Reset Level at the end of the simulation
	virtual int  getLevel();			//For Gate level , to be able to sort them

	static void ResetCount();			//For Reseting App,,, 

	string GetLabel();					//Getting Component label
	void SetLabel(string s);			//Setting Component label
	bool HasALabel();					//Check if the component has a label

	void updateID();					//Updating the id of the component, needed in some cases to enforce unique ID
	
	virtual void Reset()=0;				//Resseting the Component after the end of the simulation
	
	virtual bool CheckSpaceVacancy_GATE(const GraphicsInfo &r_GfxInfo)const=0;	//check if the location is avaliable for other gates
	
	virtual bool set_selected(const GraphicsInfo &xy)=0;	//Selects the Component if the it is within the rectangle
	void un_select();										//Unselect the component
	virtual bool is_selected();
	virtual OutputPin* ReturnOutputPinAT(int& x,int& y)=0;	//Get the Output pin at location X and Y within the limited range, pass by ref to adjust them to the correct value
	virtual InputPin* ReturnInputPinAT(int& x,int& y)=0;	
	virtual void HighlightPinsAT(int x,int y)=0; //Hovering over the pin makes it highlighted
	virtual int Validate()=0;				//Validating the Gate
	virtual void Move(int deltaX,int deltaY)=0;   //Moving the component

	virtual STATUS GetOpStatus()=0;		//Get Output Status

	virtual Component* CreateCopy()=0;	//Creating the a Copy

	virtual vector<Component*> Next()=0; //Returns a vector containing the next componenets

	virtual vector<Connection*> GetAllConnections()=0; // Return the Connections 

	virtual void GetComponentCorners(GraphicsInfo &r_GfxInfo)=0;	//Geting Component Gfx info 
	virtual InputPin* GetInputPin(int n)=0;
	virtual OutputPin* GetOutputPin()=0;
	Component();	
	
	//Destructor must be virtual
	virtual ~Component();
};

#endif
