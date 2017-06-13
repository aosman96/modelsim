#include "OutputPin.h"
#include "Connection.h"

OutputPin::OutputPin(int r_FanOut)
{
	m_Conn = 0;		//initially Pin is not connected to anything.
	m_FanOut = r_FanOut > MAX_CONNS ? MAX_CONNS: r_FanOut;	//set the fan out of the pin.
}

void OutputPin::setComponent(Component* pCmp)
{
	this->pComp=pCmp;
}

int OutputPin::GetGateID()
{
	return pComp->GetID();
}

void OutputPin::GetLocation(int& x,int &y)
{
	pComp->getOutputPinLocation(x,y);
}

//Functionn ConnectTo:
//Connects the ouput pin the the passed connection if the fan out permits
//if the no. of connections is already equals to the fan out, no more connections can be created.
bool OutputPin::ConnectTo(Connection *r_Conn)
{
	if(m_Conn < m_FanOut)
	{
		m_Connections[m_Conn++] = r_Conn;	//add a new connection the the array of connections
		return true;
	}
	
	return false;	//can't connect to any more connections
}

void OutputPin::RemoveConnection(Connection *r_Conn)
{
	for(int i=0;i<m_Conn;i++)
	{
		if(m_Connections[i]==r_Conn)
		{
			m_Connections[i]=NULL;
			swap(m_Connections[i],m_Connections[--m_Conn]);
			return;
		}
	}
}

bool OutputPin::Connectable()
{
	return (m_Conn < m_FanOut);
}

bool OutputPin::is_connected()
{
	return (m_Conn>0);
}

vector<Connection*> OutputPin::connections()
{
	vector<Connection*> cons;
	for(int i=0;i<m_Conn;i++)
		cons.push_back(m_Connections[i]);
	return cons;
}

vector<Component*> OutputPin::Next()
{
	vector<Component*> cons;
	for(int i=0;i<m_Conn;i++)
		cons.push_back(m_Connections[i]);
	return cons;
}

bool OutputPin::is_selected()
{
	return pComp->is_selected();
}

OutputPin::~OutputPin()
{}