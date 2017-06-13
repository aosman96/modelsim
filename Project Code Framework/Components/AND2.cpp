#include "AND2.h"
#include "../Utility/PrecisionChecker.h"
#include <fstream>
using std::ifstream;
using std::ofstream;

AND2::AND2(int r_FanOut):Gate(2,r_FanOut)
{
}

AND2::AND2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void AND2::Load(ifstream& in)
{
	Gate::Load(in);
}

void AND2::Save(ofstream& out)
{
	out << AND2Type << '\t'; 
	Gate::Save(out);
}

void AND2::Operate()
{
	STATUS IN1=GetInputPinStatus(1);
	STATUS IN2=GetInputPinStatus(2);

	STATUS OUT1=(IN1 && IN2 ? HIGH : LOW);
	m_OutputPin.setStatus(OUT1);
}


// Function Draw
// Draws 2-input AND gate
void AND2::Draw(Output* pOut)
{
	pOut->DrawAND2(m_GfxInfo,selected,hoveredpin);
	DrawLabel(pOut);
}

void AND2::DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)
{
	pOut->DrawAND2(m_GfxInfo,selected,hoveredpin,deltaX,deltaY);
}

void AND2::HighlightPinsAT(int x,int y)
{
	hoveredpin=NO_PIN;

	HighlightOutPinsAT(x,y);
	

	if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.GATE_Height/4))
		hoveredpin=INPUT1;
	else if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.GATE_Height*3/4))
		hoveredpin=INPUT2;

}

InputPin* AND2::ReturnInputPinAT(int& x,int& y)
{
	if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.GATE_Height/4))
	{
		x=m_GfxInfo.x1;
		y=m_GfxInfo.y1+UI.GATE_Height/4;
		return &(this->m_InputPins[0]);
	}
	else if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.GATE_Height*3/4))
	{
		x=m_GfxInfo.x1;
		y=m_GfxInfo.y1+UI.GATE_Height*3/4;
		return &(this->m_InputPins[1]);
	}

	
	return NULL;
}

void AND2::getInputPinLocation(InputPin* p,int&x,int&y)
{
	if(p==&m_InputPins[0])
	{
		x=m_GfxInfo.x1;
		y=m_GfxInfo.y1+UI.GATE_Height/4;
	}
	else if(p==&m_InputPins[1])
	{
		x=m_GfxInfo.x1;
		y=m_GfxInfo.y1+UI.GATE_Height*3/4;
	}
}

Component* AND2::CreateCopy()
{
	GraphicsInfo newl;
	newl.x1 = m_GfxInfo.x2+5;
	newl.y1 = m_GfxInfo.y2+5;
	newl.x2 = m_GfxInfo.x2+5+UI.GATE_Width;
	newl.y2 = m_GfxInfo.y2+5+UI.GATE_Height;
	AND2 *n=new AND2(newl,AND2_FANOUT);
	n->selected=true;

	n->SetLabel(GetLabel());

	return n;
}
