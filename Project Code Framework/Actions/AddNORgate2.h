#ifndef _ADD_NOR2_GATE_H
#define _ADD_NOR2_GATE_H

#include "AddGateBase.h"

class AddNORgate2 :	public AddGate
{
protected:
	virtual Component* CreateComponent(const GraphicsInfo& gfx);
	virtual void DrawDrag(const GraphicsInfo& gfx);
public:
	AddNORgate2(ApplicationManager *pApp);
	virtual ~AddNORgate2(void);	
};

#endif