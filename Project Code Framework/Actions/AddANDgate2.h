#ifndef _ADD_AND2_GATE_H
#define _ADD_AND2_GATE_H

#include "AddGateBase.h"

class AddANDgate2 :	public AddGate
{
protected:
	virtual Component* CreateComponent(const GraphicsInfo& gfx);
	virtual void DrawDrag(const GraphicsInfo& gfx);
public:
	AddANDgate2(ApplicationManager *pApp);
	virtual ~AddANDgate2(void);	
};

#endif