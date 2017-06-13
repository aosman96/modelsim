#include "Gate.h"
#include "../Utility/PrecisionChecker.h"
#include "Connection.h"
#include <fstream>
using std::ifstream;
using std::ofstream;

//Gate Constructor
//Parameters:
//r_Inputs: no. of gate's input pins
//r_FanOut: Fan out of the gate's output pin
Gate::Gate(int r_Inputs, int r_FanOut):m_OutputPin(r_FanOut)
{
	hoveredpin=NO_PIN;
	//Allocate number of input pins (equals r_Inputs)
	m_InputPins = new InputPin[r_Inputs];
	m_OutputPin.setComponent(this);
	m_Inputs = r_Inputs;	//set no. of inputs of that gate
	//Associate all input pins to this gate
	for(int i=0; i<m_Inputs; i++)
	{
		m_InputPins[i].setComponent(this);
		m_InputPins[i].setPinNo(i+1);
	}
}

void Gate::HighlightOutPinsAT(int x,int y)
{
	if(WithinRange(x,m_GfxInfo.x2) && WithinRange(y,m_GfxInfo.y2-UI.GATE_Height/2))
		hoveredpin=OUTPUT1;

}

bool Gate::CheckSpaceVacancy_GATE(const GraphicsInfo &xy) const 
{
	if (xy.x1 < m_GfxInfo.x2 && xy.x2 > m_GfxInfo.x1 && xy.y1 < m_GfxInfo.y2 && xy.y2 > m_GfxInfo.y1) 
		return false;

	return true;
}


void Gate::Load(ifstream& in)
{
	Component::Load(in);
	in >> m_GfxInfo.x1 >> m_GfxInfo.y1;
	m_GfxInfo.x2=m_GfxInfo.x1+UI.GATE_Width;
	m_GfxInfo.y2=m_GfxInfo.y1+UI.GATE_Height;
}

void Gate::Save(ofstream& out)
{
	Component::Save(out);
	out << '\t' << m_GfxInfo.x1 << '\t' <<  m_GfxInfo.y1 << endl;
}

void Gate::DrawLabel(Output* pOut)
{
	if(!HasALabel()) return;
	string Label=GetLabel();
	pOut->DrawLabel(Label,m_GfxInfo.x1,m_GfxInfo.y1-25);
}

void Gate::getOutputPinLocation(int&x,int&y)
{
	x=m_GfxInfo.x2;
	y=m_GfxInfo.y2-UI.GATE_Height/2;
}

bool Gate::set_selected(const GraphicsInfo &xy)
{
	selected=(xy.x1 < m_GfxInfo.x2 && xy.x2 > m_GfxInfo.x1 && xy.y1 < m_GfxInfo.y2 && xy.y2 > m_GfxInfo.y1);
	return selected;
}

OutputPin* Gate::ReturnOutputPinAT(int& x,int& y)
{
	if(WithinRange(x,m_GfxInfo.x2) && WithinRange(y,m_GfxInfo.y2-UI.GATE_Height/2))
	{
		x=m_GfxInfo.x2;
		y=m_GfxInfo.y2-UI.GATE_Height/2;
		return &(this->m_OutputPin);
	}
	return NULL;
}

int Gate::Validate()
{
	int ERRORS=NO_ERRORS;
	int unconnectedpins=0;
	for(int i=0;i<m_Inputs;i++)
	{
		if(!m_InputPins[i].is_connected()){
			unconnectedpins++;
			ERRORS|=PIN_NOT_CONNECT;
		}
	}
	if(!m_OutputPin.is_connected())
		ERRORS|= (PIN_NOT_CONNECT|LAST_LEVEL_ERROR);

	if(unconnectedpins==m_Inputs)
		ERRORS|=FIRST_LEVEL_ERROR;

	return ERRORS;
}

vector<Component*> Gate::Next()
{
	return m_OutputPin.Next();
}

bool Gate::isAt(int x,int y)
{
	return (m_GfxInfo.x1<x && m_GfxInfo.x2>x && m_GfxInfo.y1<y && m_GfxInfo.y2>y);
}

void Gate::Move(int deltaX,int deltaY)
{
	Connection* c;
	vector<Connection*> conns=m_OutputPin.connections();
	m_GfxInfo.x1+=deltaX;
	m_GfxInfo.y1+=deltaY;
	m_GfxInfo.x2+=deltaX;
	m_GfxInfo.y2+=deltaY;
	
	for(auto connection:conns)
		if(!connection->is_selected())
			connection->UpdateStartPoint(deltaX,deltaY);

	for(int i=0;i<m_Inputs;i++){
		c=m_InputPins[i].get_connection();
		if(c)if(!c->is_selected())
			c->UpdateEndPoint(deltaX,deltaY,i+1);
	}

}

void Gate::GetComponentCorners(GraphicsInfo &r_GfxInfo)
{
	r_GfxInfo=m_GfxInfo;
}

InputPin* Gate::GetInputPin(int n)
{
	return (n>m_Inputs?NULL:&m_InputPins[n-1]);
}

OutputPin* Gate::GetOutputPin()
{
	return &m_OutputPin;
}

//returns status of outputpin
STATUS Gate::GetOutPinStatus()	
{
	return m_OutputPin.getStatus();
}

//Set status of an input pin ot HIGH or LOW
void Gate::setInputPinStatus(int n, STATUS s)
{
	m_InputPins[n-1].setStatus(s);
}

//returns status of Inputpin #n
STATUS Gate::GetInputPinStatus(int n)	
{
	return m_InputPins[n-1].getStatus();	//n starts from 1 but array index starts from 0.
}


void Gate::Reset()
{
	//No neccesary actions
}

STATUS Gate::GetOpStatus()
{
	return m_OutputPin.getStatus();
}

vector<Connection*> Gate::GetAllConnections()
{
	vector<Connection*> all=m_OutputPin.connections();
	Connection *c;
	for(int i=0;i<m_Inputs;i++){
		c=m_InputPins[i].get_connection();
		if(c)
		all.push_back(c);
	}
	return all;
}

Gate::~Gate()
{
	delete [] m_InputPins;
}