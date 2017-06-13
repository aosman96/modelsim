#ifndef _ADD_OR3_GATE_H
#define _ADD_OR3_GATE_H

#include "AddGateBase.h"

class AddORgate3 :	public AddGate
{
protected:
	virtual Component* CreateComponent(const GraphicsInfo& gfx);
	virtual void DrawDrag(const GraphicsInfo& gfx);
public:
	AddORgate3(ApplicationManager *pApp);
	virtual ~AddORgate3(void);	
};

#endif