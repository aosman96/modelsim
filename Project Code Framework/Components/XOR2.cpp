#include "XOR2.h"
#include "../Utility/PrecisionChecker.h"
#include <fstream>
using std::ifstream;
using std::ofstream;

XOR2::XOR2( int r_FanOut):Gate(2,r_FanOut)
{

}


XOR2::XOR2(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(2, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void XOR2::Save(ofstream& out)
{
	out << XOR2Type << '\t' ; 
	Gate::Save(out);
}

void XOR2::Load(ifstream& in)
{
	Gate::Load(in);
}


void XOR2::Operate()
{
	STATUS IN1=GetInputPinStatus(1);
	STATUS IN2=GetInputPinStatus(2);

	int sum = int(IN1) + int(IN2);

	STATUS OUT1=(sum%2==0 ? LOW : HIGH); //XOR is an odd function
	m_OutputPin.setStatus(OUT1);
}


// Function Draw
// Draws 2-input XOR gate
void XOR2::Draw(Output* pOut)
{
	pOut->DrawXOR2(m_GfxInfo,selected,hoveredpin);
	DrawLabel(pOut);
}

void XOR2::DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)
{
	pOut->DrawXOR2(m_GfxInfo,selected,hoveredpin,deltaX,deltaY);
}

void XOR2::HighlightPinsAT(int x,int y)
{
	hoveredpin=NO_PIN;

	HighlightOutPinsAT(x,y);
	

	if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.GATE_Height/4))
		hoveredpin=INPUT1;
	else if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.GATE_Height*3/4))
		hoveredpin=INPUT2;

}

InputPin* XOR2::ReturnInputPinAT(int& x,int& y)
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

void XOR2::getInputPinLocation(InputPin* p,int&x,int&y)
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


Component* XOR2::CreateCopy()
{
	GraphicsInfo newl;
	newl.x1 = m_GfxInfo.x2+5;
	newl.y1 = m_GfxInfo.y2+5;
	newl.x2 = m_GfxInfo.x2+5+UI.GATE_Width;
	newl.y2 = m_GfxInfo.y2+5+UI.GATE_Height;
	XOR2 *n=new XOR2(newl,XOR2_FANOUT);
	n->selected=true;
	n->SetLabel(GetLabel());
	return n;
}
