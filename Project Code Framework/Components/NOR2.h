#ifndef _NOR2_H
#define _NOR2_H

/*
  Class NOR
  -----------
  represent the 2-input NOR gate
*/

#include "Gate.h"

class NOR2:public Gate
{
public:
	NOR2( int r_FanOut);
	NOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate()override;	//Calculates the output of the NOR gate
	virtual void Draw(Output* pOut)override;	//Draws 2-input NOR gate
	virtual void DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)override;
	virtual void Save(ofstream& out)override;
	virtual void Load(ifstream& in)override;

	virtual void HighlightPinsAT(int x,int y)override;
	virtual InputPin* ReturnInputPinAT(int& x,int& y)override;
	virtual void getInputPinLocation(InputPin* p,int&x,int&y)override;

	virtual Component* CreateCopy()override;
};

#endif