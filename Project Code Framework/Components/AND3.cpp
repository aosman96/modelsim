#include "AND3.h"
#include "../Utility/PrecisionChecker.h"
#include <fstream>
using std::ifstream;
using std::ofstream;


AND3::AND3(int r_FanOut):Gate(3,r_FanOut)
{

}

AND3::AND3(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(3, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void AND3::Save(ofstream& out)
{
	out << AND3Type << '\t' ; 
	Gate::Save(out);
}

void AND3::Load(ifstream& in)
{
	Gate::Load(in);
}

void AND3::Operate()
{
	STATUS IN1=GetInputPinStatus(1);
	STATUS IN2=GetInputPinStatus(2);
	STATUS IN3=GetInputPinStatus(3);

	STATUS OUT1=(IN1 && IN2 && IN3 ? HIGH : LOW);
	m_OutputPin.setStatus(OUT1);
}


// Function Draw
// Draws 3-input AND gate
void AND3::Draw(Output* pOut)
{
	pOut->DrawAND3(m_GfxInfo,selected,hoveredpin);
	DrawLabel(pOut);
}

void AND3::DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)
{
	pOut->DrawAND3(m_GfxInfo,selected,hoveredpin,deltaX,deltaY);
}

void AND3::HighlightPinsAT(int x,int y)
{
	hoveredpin=NO_PIN;

	HighlightOutPinsAT(x,y);
	
	if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.GATE_Height/4)) 
		hoveredpin=INPUT1;
	else if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.GATE_Height/2)) 
		hoveredpin=INPUT2;
	else if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.GATE_Height*3/4))
		hoveredpin=INPUT3;
	
}

InputPin* AND3::ReturnInputPinAT(int& x,int& y)
{
	if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.GATE_Height/4)) 
	{
		x=m_GfxInfo.x1;
		y=m_GfxInfo.y1+UI.GATE_Height/4;
		return &(this->m_InputPins[0]);
	}
	else if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.GATE_Height/2)) 
	{
		x=m_GfxInfo.x1;
		y=m_GfxInfo.y1+UI.GATE_Height/2;
		return &(this->m_InputPins[1]);
	}
	else if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.GATE_Height*3/4))
	{
		x=m_GfxInfo.x1;
		y=m_GfxInfo.y1+UI.GATE_Height*3/4;
		return &(this->m_InputPins[2]);
	}
	
	
	return NULL;
}

void AND3::getInputPinLocation(InputPin* p,int&x,int&y)
{
	if(p==&m_InputPins[0])
	{
		x=m_GfxInfo.x1;
		y=m_GfxInfo.y1+UI.GATE_Height/4;
		
	}
	else if(p==&m_InputPins[1]) 
	{
		x=m_GfxInfo.x1;
		y=m_GfxInfo.y1+UI.GATE_Height/2;
	}
	else if(p==&m_InputPins[2])
	{
		x=m_GfxInfo.x1;
		y=m_GfxInfo.y1+UI.GATE_Height*3/4;
	}
}

Component* AND3::CreateCopy()
{
	GraphicsInfo newl;
	newl.x1 = m_GfxInfo.x2+5;
	newl.y1 = m_GfxInfo.y2+5;
	newl.x2 = m_GfxInfo.x2+5+UI.GATE_Width;
	newl.y2 = m_GfxInfo.y2+5+UI.GATE_Height;
	AND3 *n=new AND3(newl,AND3_FANOUT);
	n->selected=true;
	n->SetLabel(GetLabel());
	return n;
}
