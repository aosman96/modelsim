#ifndef _XOR2_H
#define _XOR2_H

/*
  Class XOR2
  -----------
  represent the 2-input XOR gate
*/

#include "Gate.h"

class XOR2:public Gate
{
public:
	XOR2( int r_FanOut);
	XOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate()override;	//Calculates the output of the XOR gate
	virtual void Draw(Output* pOut)override;	//Draws 2-input XOR gate
	virtual void DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)override;
	virtual void Save(ofstream& out)override;
	virtual void Load(ifstream& in)override;

	virtual void HighlightPinsAT(int x,int y)override;
	virtual InputPin* ReturnInputPinAT(int& x,int& y)override;
	virtual void getInputPinLocation(InputPin* p,int&x,int&y)override;

	virtual Component* CreateCopy()override;
};

#endif