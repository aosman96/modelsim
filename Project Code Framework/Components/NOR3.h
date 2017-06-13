#ifndef _NOR3_H
#define _NOR3_H

/*
  Class NOR
  -----------
  represent the 3-input NOR gate
*/

#include "Gate.h"

class NOR3:public Gate
{
public:
	NOR3( int r_FanOut);
	NOR3(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate()override;	//Calculates the output of the NOR gate
	virtual void Draw(Output* pOut)override;	//Draws 3-input NOR gate
	virtual void DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)override;
	virtual void Save(ofstream& out)override;
	virtual void Load(ifstream& in)override;

	virtual void HighlightPinsAT(int x,int y)override;
	virtual InputPin* ReturnInputPinAT(int& x,int& y)override;
	virtual void getInputPinLocation(InputPin* p,int&x,int&y)override;

	virtual Component* CreateCopy()override;

};

#endif