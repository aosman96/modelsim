#ifndef _NOT_H
#define _NOT_H

/*
  Class NOT 
  -----------
  represent the NOT gate
*/

#include "Gate.h"

class NOT:public Gate
{
public:
	NOT( int r_FanOut);
	NOT(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate()override;	//Calculates the output of the NOT gate
	virtual void Draw(Output* pOut)override;	//Draws NOT gate
	virtual void DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)override;
	
	virtual void Save(ofstream& out)override;
	virtual void Load(ifstream& in)override;

	virtual void HighlightPinsAT(int x,int y)override;
	virtual InputPin* ReturnInputPinAT(int& x,int& y)override;
	virtual void getInputPinLocation(InputPin* p,int&x,int&y)override;

	virtual Component* CreateCopy()override;
};

#endif