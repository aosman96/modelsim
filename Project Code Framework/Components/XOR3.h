#ifndef _XOR3_H
#define _XOR3_H

/*
  Class XOR3
  -----------
  represent the 3-input XOR gate
*/

#include "Gate.h"

class XOR3:public Gate
{
public:
	XOR3( int r_FanOut);
	XOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate()override;	//Calculates the output of the XOR gate
	virtual void Draw(Output* pOut)override;	//Draws 3-input XOR gate
	virtual void DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)override;
	virtual void Save(ofstream& out)override;
	virtual void Load(ifstream& in)override;
	
	virtual void HighlightPinsAT(int x,int y)override;
	virtual InputPin* ReturnInputPinAT(int& x,int& y)override;
	virtual void getInputPinLocation(InputPin* p,int&x,int&y)override;

	virtual Component* CreateCopy()override;
};

#endif