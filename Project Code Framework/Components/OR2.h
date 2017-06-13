#ifndef _OR2_H
#define _OR2_H

/*
  Class OR2
  -----------
  represent the 2-input OR gate
*/

#include "Gate.h"

class OR2:public Gate
{
public:
	OR2( int r_FanOut);
	OR2(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate()override;	//Calculates the output of the OR gate
	virtual void Draw(Output* pOut)override;	//Draws 2-input OR gate
	virtual void DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)override;
	
	virtual void Save(ofstream& out)override;
	virtual void Load(ifstream& in)override;
	
	virtual void HighlightPinsAT(int x,int y)override;
	virtual InputPin* ReturnInputPinAT(int& x,int& y)override;
	virtual void getInputPinLocation(InputPin* p,int&x,int&y)override;

	virtual Component* CreateCopy()override;
};

#endif