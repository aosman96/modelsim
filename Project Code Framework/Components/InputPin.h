#ifndef _INPUTPIN_H
#define _INPUTPIN_H

#include "Pin.h"
class Component; //Forward class declaration
class Connection;

class InputPin: public Pin	//inherited from class Pin
{
	Component* pComp; //Component at which this pin is associated
	Connection* associated_conn;
	int pinNo;
public:
	InputPin();
	virtual void GetLocation(int& x,int &y);
	void setComponent(Component* pCmp);	//sets the component of this input pin
	Component* getComponent();	//returns the component of this input pin
	void set_connection(Connection* conn);
	Connection* get_connection();
	int GetGateID();
	bool is_connected();
	bool is_selected();
	void setPinNo(int n);
	int getPinNo();
	~InputPin();
};

#endif