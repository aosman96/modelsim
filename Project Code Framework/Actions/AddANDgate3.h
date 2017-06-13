#ifndef _ADD_AND3_GATE_H
#define _ADD_AND3_GATE_H

#include "AddGateBase.h"

class AddANDgate3 :	public AddGate
{
protected:
	virtual Component* CreateComponent(const GraphicsInfo& gfx);
	virtual void DrawDrag(const GraphicsInfo& gfx);
public:
	AddANDgate3(ApplicationManager *pApp);
	virtual ~AddANDgate3(void);	
};

#endif