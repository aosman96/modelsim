#ifndef _ADD_XNOR3_GATE_H
#define _ADD_XNOR3_GATE_H

#include "AddGateBase.h"

class AddXNORgate3 :	public AddGate
{
protected:
	virtual Component* CreateComponent(const GraphicsInfo& gfx);
	virtual void DrawDrag(const GraphicsInfo& gfx);
public:
	AddXNORgate3(ApplicationManager *pApp);
	virtual ~AddXNORgate3(void);	
};

#endif