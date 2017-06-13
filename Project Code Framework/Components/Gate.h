#ifndef _GATE_H
#define _GATE_H

/*
  Class Gate
  -----------
  - Base class for all types of gates
  - Each gate has n inputs pins and one output pin
*/


#include "InputPin.h"
#include "OutputPin.h"
#include "Component.h"

class Gate:public Component
{
protected:
	InputPin* m_InputPins;	//Array of input pins of the Gate
	OutputPin m_OutputPin;	//The Gate output pin
	int m_Inputs;		//No. of input pins of that Gate. 
	HighPins hoveredpin;
	virtual void HighlightOutPinsAT(int x,int y);
	virtual void DrawLabel(Output* pOut);
public:
	Gate(int r_Inputs, int r_FanOut);
	virtual void getInputPinLocation(InputPin* p,int&x,int&y)override=0; 
	virtual void getOutputPinLocation(int&x,int&y)override; 
	virtual bool CheckSpaceVacancy_GATE(const GraphicsInfo &r_GfxInfo)const override;		//check if this gate wont conflict with ix and iy
	virtual bool set_selected(const GraphicsInfo &xy)override;
	virtual OutputPin* ReturnOutputPinAT(int& x,int& y)override;//All gates have there output at the middle
	virtual InputPin* ReturnInputPinAT(int& x,int& y)override=0;
	virtual void HighlightPinsAT(int x,int y)override=0;
	virtual int Validate()override;
	virtual void Reset()override;
	virtual bool isAt(int x,int y)override;
	virtual void Move(int deltaX,int deltaY)override;
	virtual void GetComponentCorners(GraphicsInfo &r_GfxInfo)override;
	virtual vector<Component*> Next()override;

	virtual void Save(ofstream& out)override=0;
	virtual void Load(ifstream& in)override;

	virtual STATUS GetOpStatus()override;

	virtual Component* CreateCopy()override=0;

	virtual vector<Connection*> GetAllConnections()override;

	virtual InputPin* GetInputPin(int n)override;
	virtual OutputPin* GetOutputPin()override;


	virtual STATUS GetOutPinStatus()override;	//returns status of outputpin if LED, return -1
	virtual STATUS GetInputPinStatus(int n)override;	//returns status of Inputpin # n if SWITCH, return -1
	virtual void setInputPinStatus(int n, STATUS s)override;	//set status of Inputpin # n, to be used by connection class.

	virtual ~Gate();
};

#endif
