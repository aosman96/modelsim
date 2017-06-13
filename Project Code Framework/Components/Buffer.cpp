#include "Buffer.h"
#include "../Utility/PrecisionChecker.h"
#include <fstream>
using std::ifstream;
using std::ofstream;


Buffer::Buffer(int r_FanOut):Gate(1,r_FanOut)
{
}

Buffer::Buffer(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void Buffer::Save(ofstream& out)
{
	out << BUFFERType << '\t' ; 
	Gate::Save(out);
}

void Buffer::Load(ifstream& in)
{
	Gate::Load(in);
}

void Buffer::Operate()
{
	STATUS IN1=GetInputPinStatus(1);
	m_OutputPin.setStatus(IN1);
}


// Function Draw
// Draws Buffer gate
void Buffer::Draw(Output* pOut)
{
	pOut->DrawBuffer(m_GfxInfo,selected,hoveredpin);
	DrawLabel(pOut);
}

void Buffer::DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)
{
	pOut->DrawBuffer(m_GfxInfo,selected,hoveredpin,deltaX,deltaY);
}

InputPin* Buffer::ReturnInputPinAT(int& x,int& y)
{

	if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.GATE_Height/2))
	{
		x=m_GfxInfo.x1;
		y=m_GfxInfo.y1+UI.GATE_Height/2;
		return &(this->m_InputPins[0]);
	}
	
	return NULL;
}

void Buffer::getInputPinLocation(InputPin* p,int&x,int&y)
{
	x=m_GfxInfo.x1;
	y=m_GfxInfo.y1+UI.GATE_Height/2;
}

void Buffer::HighlightPinsAT(int x,int y)
{
	hoveredpin=NO_PIN;

	HighlightOutPinsAT(x,y);
	
	if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.GATE_Height/2))
		hoveredpin=INPUT1;

}

Component* Buffer::CreateCopy()
{
	GraphicsInfo newl;
	newl.x1 = m_GfxInfo.x2+5;
	newl.y1 = m_GfxInfo.y2+5;
	newl.x2 = m_GfxInfo.x2+5+UI.GATE_Width;
	newl.y2 = m_GfxInfo.y2+5+UI.GATE_Height;
	Buffer *n=new Buffer(newl,Buffer_FANOUT);
	n->selected=true;
	n->SetLabel(GetLabel());
	return n;
}
