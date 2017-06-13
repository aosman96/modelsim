#ifndef _XNOR2_H
#define _XNOR2_H

/*
  Class XNOR2
  -----------
  represent the 2-input XNOR gate
*/

#include "Gate.h"

class XNOR2:public Gate
{
public:
	XNOR2( int r_FanOut);
	XNOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate()override;	//Calculates the output of the XNOR gate
	virtual void Draw(Output* pOut)override;	//Draws 2-input XNOR gate
	virtual void DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)override;
	virtual void Save(ofstream& out)override;
	virtual void Load(ifstream& in)override;

	virtual void HighlightPinsAT(int x,int y)override;
	virtual InputPin* ReturnInputPinAT(int& x,int& y)override;
	virtual void getInputPinLocation(InputPin* p,int&x,int&y)override;

	virtual Component* CreateCopy()override;
};

#endif