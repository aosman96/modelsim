#include "InputPin.h"
#include "Connection.h"
InputPin::InputPin()
{associated_conn=NULL;}

void InputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;
}

Component* InputPin::getComponent()
{
	return pComp;
}

void InputPin::GetLocation(int& x,int &y)
{
	pComp->getInputPinLocation(this,x,y);
}

void InputPin::set_connection(Connection* conn)
{
	associated_conn=conn;
}

int InputPin::GetGateID()
{
	return pComp->GetID();
}

void InputPin::setPinNo(int n)
{
	pinNo=n;
}

Connection* InputPin::get_connection()
{
	return associated_conn;
}

int InputPin::getPinNo()
{
	return pinNo;
}

bool InputPin::is_connected()
{
	return associated_conn!=NULL;
}

bool InputPin::is_selected()
{
	return pComp->is_selected();
}

InputPin::~InputPin()
{}