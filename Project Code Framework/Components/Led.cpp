#include "Led.h"
#include "../Utility/PrecisionChecker.h"
#include "Connection.h"
#include <fstream>
#include <string>
using std::ifstream;
using std::ofstream;

int Led::LedCount=0;

Led::Led()
{
	m_inputPin.setComponent(this);
	m_inputPin.setPinNo(1);
	lighted=false;
	PinHovered=false;
}

Led::Led(const GraphicsInfo &r_GfxInfo)
{
	string l("F");
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	m_inputPin.setComponent(this);
	m_inputPin.setPinNo(1);
	lighted=false;
	PinHovered=false;
	++LedCount;
	l.push_back(LedCount+'0');
	SetLabel(l);	
}

void Led::resetLedCount()
{
	LedCount=0;
}

void Led::getInputPinLocation(InputPin* p,int&x,int&y)
{
	x=m_GfxInfo.x1;
	y=m_GfxInfo.y1+UI.Led_Height/2;
}

void Led::getOutputPinLocation(int&x,int&y)
{}

void Led::DrawLabel(Output* pOut)
{
	if(!HasALabel()) return;
	string s;
	s=GetLabel();
	pOut->DrawLabel(s,m_GfxInfo.x1,m_GfxInfo.y1-18);
}

void Led::Save(ofstream& out)
{
	out << LEDType << '\t' ; 
	Component::Save(out);
	out << '\t' << m_GfxInfo.x1 << '\t' <<  m_GfxInfo.y1 << endl;
}

void Led::Load(ifstream& in)
{
	Component::Load(in);
	in >> m_GfxInfo.x1 >> m_GfxInfo.y1;
	m_GfxInfo.x2=m_GfxInfo.x1+UI.Led_Width;
	m_GfxInfo.y2=m_GfxInfo.y1+UI.Led_Height;
}

STATUS Led::GetOpStatus()
{
	return STATUS(lighted);
}

void Led::Reset()
{
	lighted=false;
}

void Led::Operate()
{
	lighted=(m_inputPin.getStatus() ? true:false);
}

bool Led::set_selected(const GraphicsInfo &xy)
{
	selected=(xy.x1 < m_GfxInfo.x2 && xy.x2 > m_GfxInfo.x1 && xy.y1 < m_GfxInfo.y2 && xy.y2 > m_GfxInfo.y1);
	return selected;
}

bool Led::isAt(int x,int y)
{
	return (m_GfxInfo.x1<x && m_GfxInfo.x2>x && m_GfxInfo.y1<y && m_GfxInfo.y2>y);
}

void Led::Draw(Output* pOut)
{
	pOut->DrawLED(m_GfxInfo,PinHovered,lighted,selected);
	DrawLabel(pOut);
}

void Led::DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)
{
	pOut->DrawLED(m_GfxInfo,PinHovered,lighted,selected,deltaX,deltaY);
}

OutputPin* Led::ReturnOutputPinAT(int& x,int& y)
{
	return NULL;
}
InputPin* Led::ReturnInputPinAT(int& x,int& y)
{
	if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.Led_Height/2))
	{
		x=m_GfxInfo.x1;
		y=m_GfxInfo.y1+UI.Led_Height/2;
		return &(this->m_inputPin);
	}
	return NULL;
}

void Led::HighlightPinsAT(int x,int y)
{
	PinHovered=(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.Led_Height/2));
}

int Led::Validate()
{
	return (m_inputPin.is_connected() ? NO_ERRORS : (PIN_NOT_CONNECT|FIRST_LEVEL_ERROR));
}

//returns status of outputpin
STATUS Led::GetOutPinStatus()	
{
	return m_inputPin.getStatus();
}


//returns status of Inputpin #n
STATUS Led::GetInputPinStatus(int n)	
{
	return m_inputPin.getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin 
void Led::setInputPinStatus(int n, STATUS s)
{
	m_inputPin.setStatus(s);
}

void Led::GetComponentCorners(GraphicsInfo &r_GfxInfo)
{
	r_GfxInfo=m_GfxInfo;
}


vector<Component*> Led::Next()
{
	vector<Component*> cons;
	return cons;
}

bool Led::CheckSpaceVacancy_GATE(const GraphicsInfo &xy) const 
{
	if (xy.x1 < m_GfxInfo.x2 && xy.x2 > m_GfxInfo.x1 && xy.y1 < m_GfxInfo.y2 && xy.y2 > m_GfxInfo.y1) 
		return false;

	return true;
}

void Led::Move(int deltaX,int deltaY)
{
	Connection* c;
	m_GfxInfo.x1+=deltaX;
	m_GfxInfo.y1+=deltaY;
	m_GfxInfo.x2+=deltaX;
	m_GfxInfo.y2+=deltaY;
	c=m_inputPin.get_connection();

	if(c)if(!c->is_selected())
		c->UpdateEndPoint(deltaX,deltaY,1);
}

InputPin* Led::GetInputPin(int n)
{
	return n==1?&m_inputPin:NULL;
}

OutputPin* Led::GetOutputPin()
{
	return NULL;
}

Component* Led::CreateCopy()
{
	GraphicsInfo newl;
	newl.x1 = m_GfxInfo.x2+5;
	newl.y1 = m_GfxInfo.y2+5;
	newl.x2 = m_GfxInfo.x2+5+UI.Led_Width;
	newl.y2 = m_GfxInfo.y2+5+UI.Led_Height;
	Led *n=new Led(newl);
	n->selected=true;
	n->SetLabel(GetLabel());
	return n;
}

vector<Connection*> Led::GetAllConnections()
{
	vector<Connection*> all;
	Connection *c;
	c=m_inputPin.get_connection();
	if(c)
	all.push_back(c);
	return all;
}