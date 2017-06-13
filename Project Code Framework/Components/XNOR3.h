#ifndef _XNOR3_H
#define _XNOR3_H

/*
  Class XNOR3
  -----------
  represent the 3-input XNOR gate
*/

#include "Gate.h"

class XNOR3:public Gate
{
public:
	XNOR3( int r_FanOut);
	XNOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate()override;	//Calculates the output of the XNOR gate
	virtual void Draw(Output* pOut)override;	//Draws 3-input XNOR gate
	virtual void DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)override;
	virtual void Save(ofstream& out)override;
	virtual void Load(ifstream& in)override;

	virtual void HighlightPinsAT(int x,int y)override;
	virtual InputPin* ReturnInputPinAT(int& x,int& y)override;
	virtual void getInputPinLocation(InputPin* p,int&x,int&y)override;

	virtual Component* CreateCopy()override;
};

#endif