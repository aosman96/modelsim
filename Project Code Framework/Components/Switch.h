#ifndef _Switch_H
#define _Switch_H
#include "OutputPin.h"

/*
  Class Switch
  -----------
  represent the Switch
*/

#include "Component.h"

class Switch:public Component
{
	OutputPin m_OutputPin;
	bool switched;
	bool PinHovered;
	virtual void DrawLabel(Output* pOut);
	static int SwitchCount;
public:
	Switch();
	Switch(const GraphicsInfo &r_GfxInfo);
	static void resetSwitchCount();
	virtual void getInputPinLocation(InputPin* p,int&x,int&y)override; 
	virtual void getOutputPinLocation(int&x,int&y)override; 
	virtual void Operate()override;	
	virtual void Draw(Output* pOut)override;	
	virtual void DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)override;
	virtual void Save(ofstream& out)override;
	virtual void Load(ifstream& in)override;
	virtual STATUS GetOpStatus()override;
	void set_status(STATUS b);
	
	void toggle();

	virtual void Reset()override;

	virtual STATUS GetOutPinStatus()override;	
	virtual STATUS GetInputPinStatus(int n)override;	

	virtual void setInputPinStatus(int n, STATUS s)override;	

	virtual OutputPin* ReturnOutputPinAT(int& x,int& y)override;
	virtual InputPin* ReturnInputPinAT(int& x,int& y)override;
	virtual void HighlightPinsAT(int x,int y)override;
	virtual bool set_selected(const GraphicsInfo &xy)override;
	virtual int Validate()override;
	virtual bool isAt(int x,int y)override;
	virtual void GetComponentCorners(GraphicsInfo &r_GfxInfo)override;
	virtual void Move(int deltaX,int deltaY)override;
	virtual vector<Component*> Next()override;
	bool CheckSpaceVacancy_GATE(const GraphicsInfo &r_GfxInfo)const override;

	virtual InputPin* GetInputPin(int n)override;
	virtual OutputPin* GetOutputPin()override;
	virtual Component* CreateCopy()override;
	virtual vector<Connection*> GetAllConnections()override;
};

#endif