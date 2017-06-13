#include "Switch.h"
#include "../Utility/PrecisionChecker.h"
#include "Connection.h"
#include <fstream>
using std::ifstream;
using std::ofstream;


int Switch::SwitchCount=0;

Switch::Switch():m_OutputPin(MAX_CONNS)
{
	switched=false;
	m_OutputPin.setComponent(this);
	PinHovered=false;
}

void Switch::DrawLabel(Output* pOut)
{
	if(!HasALabel()) return;
	string s;
	s=GetLabel();
	pOut->DrawLabel(s,m_GfxInfo.x1,m_GfxInfo.y1-10);
}

void Switch::getInputPinLocation(InputPin* p,int&x,int&y)
{}

void Switch::getOutputPinLocation(int&x,int&y)
{
	x=m_GfxInfo.x2;
	y=m_GfxInfo.y2-UI.Switch_Height/2;
}

Switch::Switch(const GraphicsInfo &r_GfxInfo):m_OutputPin(MAX_CONNS)
{
	string l("A");
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
	switched=false;
	PinHovered=false;
	m_OutputPin.setComponent(this);
	l[0]+=SwitchCount;
	++SwitchCount;
	SetLabel(l);
}

void Switch::resetSwitchCount()
{
	SwitchCount=0;
}

void Switch::Save(ofstream& out)
{
	out << SWITCHType << '\t' ; 
	Component::Save(out);
	out << '\t' << m_GfxInfo.x1 << '\t' <<  m_GfxInfo.y1 << endl;
}

void Switch::Load(ifstream& in)
{
	Component::Load(in);
	in >> m_GfxInfo.x1 >> m_GfxInfo.y1;
	m_GfxInfo.x2=m_GfxInfo.x1+UI.Switch_Width;
	m_GfxInfo.y2=m_GfxInfo.y1+UI.Switch_Height;
}

void Switch::Operate()
{
	STATUS out;
	out = switched ? HIGH:LOW;
	m_OutputPin.setStatus(out);
}

STATUS Switch::GetOpStatus()
{
	return STATUS(switched ? HIGH:LOW);
}

void Switch::toggle()
{
	switched=!switched;
}

bool Switch::set_selected(const GraphicsInfo &xy)
{
	selected=(xy.x1 < m_GfxInfo.x2 && xy.x2 > m_GfxInfo.x1 && xy.y1 < m_GfxInfo.y2 && xy.y2 > m_GfxInfo.y1);
	return selected;
}

void Switch::Reset()
{
	switched=false;
}

void Switch::Draw(Output* pOut)
{
	pOut->DrawSWITCH(m_GfxInfo,PinHovered,switched,selected);
	DrawLabel(pOut);
}

void Switch::DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)
{
	pOut->DrawSWITCH(m_GfxInfo,PinHovered,switched,selected,deltaX,deltaY);
}


bool Switch::isAt(int x,int y)
{
	return (m_GfxInfo.x1<x && m_GfxInfo.x2>x && m_GfxInfo.y1<y && m_GfxInfo.y2>y);
}

OutputPin* Switch::ReturnOutputPinAT(int& x,int& y)
{
	if(WithinRange(x,m_GfxInfo.x2) && WithinRange(y,m_GfxInfo.y2-UI.Switch_Height/2))
	{
		x=m_GfxInfo.x2;
		y=m_GfxInfo.y2-UI.Switch_Height/2;
		return &(this->m_OutputPin);
	}
	
	return NULL;
}

InputPin* Switch::ReturnInputPinAT(int& x,int& y)
{
	return NULL;
}

void Switch::HighlightPinsAT(int x,int y)
{
	PinHovered=WithinRange(x,m_GfxInfo.x2) && WithinRange(y,m_GfxInfo.y2-UI.Switch_Height/2);
}

int Switch::Validate()
{
	return (m_OutputPin.is_connected() ? NO_ERRORS : PIN_NOT_CONNECT);
}

//returns status of outputpin
STATUS Switch::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}

bool Switch::CheckSpaceVacancy_GATE(const GraphicsInfo &xy) const 
{
	if (xy.x1 < m_GfxInfo.x2 && xy.x2 > m_GfxInfo.x1 && xy.y1 < m_GfxInfo.y2 && xy.y2 > m_GfxInfo.y1) 
		return false;

	return true;
}

//returns status of Inputpin #n
STATUS Switch::GetInputPinStatus(int n)	
{
	return m_OutputPin.getStatus();	//n starts from 1 but array index starts from 0.
}

//Set status of an input pin 
void Switch::setInputPinStatus(int n, STATUS s)
{
	
}

void Switch::GetComponentCorners(GraphicsInfo &r_GfxInfo)
{
	r_GfxInfo=m_GfxInfo;
}


vector<Component*> Switch::Next()
{
	return m_OutputPin.Next();
}

void Switch::set_status(STATUS b)
{
	switched=(b==HIGH);
}

void Switch::Move(int deltaX,int deltaY)
{
	vector<Connection*> conns=m_OutputPin.connections();
	m_GfxInfo.x1+=deltaX;
	m_GfxInfo.y1+=deltaY;
	m_GfxInfo.x2+=deltaX;
	m_GfxInfo.y2+=deltaY;
	
	for(auto connection:conns)
		if(!connection->is_selected())
			connection->UpdateStartPoint(deltaX,deltaY);

}


InputPin* Switch::GetInputPin(int n)
{
	return NULL;
}

OutputPin* Switch::GetOutputPin()
{
	return &m_OutputPin;
}

Component* Switch::CreateCopy()
{
	GraphicsInfo newl;
	newl.x1 = m_GfxInfo.x2+5;
	newl.y1 = m_GfxInfo.y2+5;
	newl.x2 = m_GfxInfo.x2+5+UI.Switch_Width;
	newl.y2 = m_GfxInfo.y2+5+UI.Switch_Height;
	Switch *n=new Switch(newl);
	n->selected=true;
	n->SetLabel(GetLabel());
	return n;
}

vector<Connection*> Switch::GetAllConnections()
{
	return m_OutputPin.connections();
}