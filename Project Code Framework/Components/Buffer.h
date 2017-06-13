#ifndef _BUFFER_H
#define _BUFFER_H

/*
  Class Buffer
  -----------
  represent the Buffer
*/

#include "Gate.h"

class Buffer:public Gate
{
public:
	Buffer( int r_FanOut);
	Buffer(const GraphicsInfo &r_GfxInfo, int r_FanOut);
	virtual void Operate()override;	//Calculates the output of the BUffer
	virtual void Draw(Output* pOut)override;	//Draws the buffer
	virtual void DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)override;
	virtual void Save(ofstream& out)override;
	virtual void Load(ifstream& in)override;
	
	virtual void HighlightPinsAT(int x,int y)override;
	virtual InputPin* ReturnInputPinAT(int& x,int& y)override;
	virtual void getInputPinLocation(InputPin* p,int&x,int&y)override;

	virtual Component* CreateCopy()override;
};

#endif