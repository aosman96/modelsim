#ifndef _LED_H
#define _LED_H
#include "InputPin.h"

/*
  Class Led
  -----------
  represent the LED
*/

#include "Component.h"

class Led:public Component
{
	InputPin m_inputPin;
	bool lighted;
	bool PinHovered;
	virtual void DrawLabel(Output* pOut);
	static int LedCount;
public:
	Led();
	Led(const GraphicsInfo &r_GfxInfo);
	static void resetLedCount();
	virtual void Operate()override;	
	virtual void Draw(Output* pOut)override;	
	virtual void DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)override;
	
	virtual void Save(ofstream& out)override;
	virtual void Load(ifstream& in)override;

	virtual void getInputPinLocation(InputPin* p,int&x,int&y)override; 
	virtual void getOutputPinLocation(int&x,int&y)override; 

	virtual STATUS GetOutPinStatus()override;	
	virtual STATUS GetInputPinStatus(int n)override;	
	
	virtual void setInputPinStatus(int n, STATUS s)override;	
	virtual STATUS GetOpStatus()override;
	virtual void Reset()override;

	virtual OutputPin* ReturnOutputPinAT(int& x,int& y)override;
	virtual InputPin* ReturnInputPinAT(int& x,int& y)override;
	virtual void HighlightPinsAT(int x,int y)override;
	virtual bool set_selected(const GraphicsInfo &xy)override;
	virtual int Validate()override;

	virtual bool isAt(int x,int y)override;
	virtual void Move(int deltaX,int deltaY)override;
	virtual void GetComponentCorners(GraphicsInfo &r_GfxInfo)override;
	virtual vector<Component*> Next()override;
	bool CheckSpaceVacancy_GATE(const GraphicsInfo &r_GfxInfo)const override;
	virtual InputPin* GetInputPin(int n)override;
	virtual OutputPin* GetOutputPin()override;

	virtual Component* CreateCopy()override;
	
	virtual vector<Connection*> GetAllConnections()override;
};

#endif