#ifndef _OUTPUTPIN_H
#define _OUTPUTPIN_H

/*class OutputPin 
  ---------------
 An output pin obtains its value as a result of calculating the outputs of
 a component. The output pin propagates its value immediately to the associated connections
*/

#include "Pin.h"
#include <vector>
using std::vector;
class Connection;	//Forward class declartion
class Component;

class OutputPin: public Pin	//inherited from class Pin
{
private:
	//Array of connections (poniters) to be connected to that OutputPin
	//For simplicity, we consider it a constant length
	Component* pComp;
	Connection* m_Connections[MAX_CONNS];	
	int m_FanOut;	//Maximum No. of connections connected to that output pin (depends on the component)
	int m_Conn;		//Actual No. of connections connected to that output pin
public:
	OutputPin(int r_FanOut);
	virtual void GetLocation(int& x,int &y);
	void setComponent(Component* pCmp);
	int GetGateID();
	bool ConnectTo(Connection *r_Conn);	//connect to a new connection
	bool Connectable();
	void RemoveConnection(Connection *r_Conn);
	bool is_connected();
	bool is_selected();
	vector<Component*> Next();
	vector<Connection*> connections();
	~OutputPin();
};

#endif