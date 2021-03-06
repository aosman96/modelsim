#ifndef _NAND2_H
#define _NAND2_H

/*
  Class NAND2
  -----------
  represent the 2-input AND gate
*/

#include "Gate.h"

class NAND2:public Gate
{
public:
	NAND2( int r_FanOut);
	NAND2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate()override;	//Calculates the output of the AND gate
	virtual void Draw(Output* pOut)override;	//Draws 2-input gate
	virtual void DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)override;
	virtual void Save(ofstream& out)override;
	virtual void Load(ifstream& in)override;

	virtual void HighlightPinsAT(int x,int y)override;
	virtual InputPin* ReturnInputPinAT(int& x,int& y)override;
	virtual void getInputPinLocation(InputPin* p,int&x,int&y)override;

	virtual Component* CreateCopy()override;
};

#endif