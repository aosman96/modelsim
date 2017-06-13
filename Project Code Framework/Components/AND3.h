#ifndef _AND3_H
#define _AND3_H

/*
  Class AND3
  -----------
  represent the 3-input AND gate
*/

#include "Gate.h"

class AND3:public Gate
{
public:
	AND3(int r_FanOut);
	AND3(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate()override;	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut)override;	//Draws 3-input gate
	virtual void DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)override;
	virtual void Save(ofstream& out)override;
	virtual void Load(ifstream& in)override;
	
	virtual void HighlightPinsAT(int x,int y)override;
	virtual InputPin* ReturnInputPinAT(int& x,int& y)override;
	virtual void getInputPinLocation(InputPin* p,int&x,int&y)override;

	virtual Component* CreateCopy()override;
};

#endif